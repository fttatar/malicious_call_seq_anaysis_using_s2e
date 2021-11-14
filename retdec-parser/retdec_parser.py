import re

#txt = "The rain in Spain"
#x = re.search("^The.*Spain$",txt)
def clearHeaderFile(headerFileName,clearedHeaderFileName):
    source = open(headerFileName,"r")
    dest = open(clearedHeaderFileName,"w+")
    processed=""
    collect = False
    for line in source:
        # find functions
        if("Dynamically Linked Functions" in line):
            collect = True
        
        if("Meta-Information" in line):
            collect = False

        if((line.endswith(");\n")) and (collect == True)):    
            
            #remove WINBASEAPI or WINAPI like definitions
            #print(line)
            processed = line
            
            #clear API related headers
            processed = re.sub(r"\bWINAPI\b","",processed);
            processed = re.sub(r"\bWINBASEAPI\b","",processed);
            processed = re.sub(r"\bWINADVAPI\b","",processed);
            processed = re.sub(r"\bAPIENTRY\b","",processed);
            processed = re.sub(r"\bDECLSPEC_NORETURN\b","",processed);
            processed = re.sub(r"\ _ACRTIMP_ALT\b"," ",processed);
            processed = re.sub(r"\ restrict\b"," ",processed);
            
            #correct types
            processed = re.sub(r"\bWINBOOL\b","BOOL",processed);

            #clear comments
            processed = re.sub("//","",processed);

            #delete space of pointer signs
            processed = re.sub(" \*","*",processed);

            #clear leading spaces
            processed = processed.lstrip()

            #print(processed)
            dest.write(processed)
    source.close()
    dest.close()

def createCFileFromHeaderFile(headerFileName,cFileName):
    source = open(headerFileName,"r")
    dest = open(cFileName,"w+")
    processed=""
    
    #read line
    for line in source:

        #create a comment field
        processed = line
        #dest.write("/*\n")
        #dest.write("[.]\n")
        #dest.write("*/\n")
        
        #delete ;
        processed = re.sub(r";","",processed);

        #add _Model keyword
        processed = re.sub(r"\(","_Model(",processed);

        #print it
        dest.write("static "+processed)
        
        #start function body
        dest.write("{\n")

        #get return type
        returnType = processed.split(None,1)[0]

        #get only function name
        res = re.search("\s.*\s?\(",processed)          #find function name
        res = res.group()                               #get regex match
        res = re.sub("\(","",res)                       #clear regex remainders
        res = res.lstrip()                              #clear leading space

        #print function name in the method body
        dest.write("\tMessage(\""+res+"\\n\");\n")
        
        #print evidences
        dest.write("\tMessage(\"["+res+"|evidence]{[ EDIT HERE! ]}\\n\");\n")

        #print info
        dest.write("\tMessage(\"["+res+"|info]{[CONCRETE]}\\n\");\n")

        #add method return
        returnCode = "invalid things written here"
        if(("VOID" == returnType) or ("void" == returnType)):
            returnCode = ";\n"
        elif(("BOOL" == returnType) or ("BOOLEAN" == returnType)):
            returnCode = "TRUE;\n"
        elif("HANDLE" == returnType):
            returnCode = "NULL;\n"
        elif("HGLOBAL" == returnType):
            returnCode = "NULL;\n"
        elif("HRESULT" == returnType):
            returnCode = "NULL;\n"
        elif("HRSRC" == returnType):
            returnCode = "NULL;\n"
        elif("SC_HANDLE" == returnType):
            returnCode = "NULL;\n"
        elif("char*" == returnType):
            returnCode = "NULL;\n"
        elif("char***" == returnType):
            returnCode = "NULL;\n"
        elif("DWORD" == returnType):
            returnCode = "1;\n"
        elif("WCHAR" == returnType):
            returnCode = "0x48;\n" # taniyabilmek icin H harfi.
        elif("wchar_t*" == returnType):
            returnCode = "NULL;\n" 
        elif("LPVOID" == returnType):
            returnCode = "NULL;\n"
        elif("LPSTR" == returnType):
            returnCode = "NULL;\n"
        elif("LSTATUS" == returnType):
            returnCode = "4;\n" # access denied from winerror.h
        elif("LPCH" == returnType):
            returnCode = "NULL;\n"
        elif("LPWCH" == returnType):
            returnCode = "NULL;\n"
        elif("LPWSTR" == returnType):
            returnCode = "NULL;\n"
        elif("PCWSTR" == returnType):
            returnCode = "NULL;\n"
        elif("PDEVICE_OBJECT" == returnType):
            returnCode = "NULL;\n"
        elif("LPTOP_LEVEL_EXCEPTION_FILTER" == returnType):
            returnCode = "NULL;\n"
        elif("PVOID" == returnType):
            returnCode = "NULL;\n"
        elif("PIO_WORKITEM" == returnType):
            returnCode = "NULL;\n"
        elif("PKTHREAD" == returnType):
            returnCode = "NULL;\n"
        elif("PHYSICAL_ADDRESS" == returnType):
            returnCode = "0;\n"
        elif(("SIZE_T" == returnType) or "size_t" == returnType):
            returnCode = "1;\n"
        elif("UINT" == returnType):
            returnCode = "1u;\n"
        elif("unsigned" == returnType):
            returnCode = "1u; /* Hopefully types continues with int, char..etc. */\n"            
        elif("int32_t" == returnType):
            returnCode = "1u;\n"
        elif("int" == returnType):
            returnCode = "1;\n"
        elif("int*" == returnType):
            returnCode = "NULL;\n"
        elif("KIRQL" == returnType):
            returnCode = "0;\n"
        elif("HMODULE" == returnType):
            returnCode = "NULL;\n"
        elif(("long" == returnType) or "LONG" == returnType):
            returnCode = "1;\n"
        elif("LONG_PTR" == returnType):
            returnCode = "NULL;\n"
        elif("NOT_BUILD_WINDOWS_DEPRECATE" == returnType):
            returnCode = "0;\n" # zero means error
        elif("NTSTATUS" == returnType):
            returnCode = "0;\n" # 0 success
        elif("FARPROC" == returnType):
            returnCode = "NULL;\n"
        elif("FILE*" == returnType):
            returnCode = "NULL;\n"
        elif("EXCEPTION_DISPOSITION" == returnType):
            returnCode = "NULL; /* cok emin degilim */\n"
        elif("void*" == returnType):
            returnCode = "NULL;\n"
        else:
            returnCode = " -1;\t/*Correct me!*/\n"
            print("Unhandled return type "+returnType)
        
        #print function name in the method body
        if(returnType != "void"):
            dest.write("\t"+returnType+" retVal = "+returnCode)
        
        dest.write("\tif(detail.compare(\"all\") == 0)\n\t{\n")
        dest.write("\t\t//S2EMakeSymbolic(&retVal, sizeof(retVal),\""+res+"\");\n\t}\n")
        dest.write("\telse\n\t{\n")
        dest.write("\t\t/* Concrete output */\n\t}\n")
        
        if(returnType != "void"):    
            dest.write("\treturn retVal;\n")
        else:
            dest.write("\treturn;\n")

        #dest.write(returnCode)

        #close function body
        dest.write("}\n\n")
    source.close()
    dest.close()

def findAnalysisFile(extension):
    import re
    dir_path = os.path.abspath(__file__)
    dir_path = re.sub("retdec_parser.py","",dir_path)
    source = ""
    for file in os.listdir(dir_path):
        if file.endswith(extension):
            return os.path.join(dir_path, file)          
            
import os
def main():
    print("Starting")
    clearHeaderFile(findAnalysisFile(".exe.c"),"temp.h")
    createCFileFromHeaderFile("temp.h","temp.c")
    print("Finished")

if __name__ == '__main__':
    main()        


