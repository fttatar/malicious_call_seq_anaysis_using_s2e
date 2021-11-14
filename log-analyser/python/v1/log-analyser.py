#ptrace'in icerisinde utf-8 olmayan karakterler sorun cikartti, sildim.
import csv
import re 
class MalwareSequence:
    name = ""
    sequence = []
    
    def __init__(self, name, sequence):
        self.name = name
        self.sequence = sequence.copy()  # copy yoksa sequence bos kaliyor
    
    def compareWithSelf(self,suspect):
        isEncountered = 0
        state=0
        for call in suspect:
            if(call in self.sequence[state]):
                state += 1
                if(self.sequence.__len__() == state):
                    print(f"{self.name} is encountered!\n")
                    isEncountered = 1
                    break
                else:
                    pass

        return isEncountered
 
class ModelInfo:
    name = ""
    translation = {}
    def __init__(self, name, translation):
        self.name = name
        self.translation = translation.copy()

    def translate(self,input):
        retVal = ""
        try:
            retVal = self.translation[str(input)]
        except:
            pass
        return retVal
             

def importSuspiciousSequence(logFile,modelInfo):
    callSequence=[]
    with open(logFile,"r") as source:
        for line in source: #klee log satirina bak
            isModelled = 0
            for model in modelInfo:
                if(line.find(model.name)!=-1):          # Modelledigimiz bir fonk. ait output.
                    if(model.name == "[ptrace]"):         # ptrace log'larina ozel bir call seq. topla
                        firstIndex = line.find("r:")+2
                        secondIndex = line.find(",")
                        subString = line[firstIndex:secondIndex]
                        call = model.translate(subString)   # fonksiyon parametresini translate et
                        callSequence.append(call)           # call'a ekle
                    else:
                        # sadece func name'i al
                        clearedLine = re.sub("\n","",line)  
                        clearedLine = re.sub("\[","",clearedLine)
                        clearedLine = re.sub("\]","",clearedLine)
                        callSequence.append(clearedLine)
                    isModelled = 1
                    break                               
            
            if (isModelled == 0):
                print("Modellenmemis bir satira denk geldik!")
                print(line)

    return callSequence  
        
def importKnownSequences(sourceFile):
    sequenceList = []
    tempName = ""
    tempSequence = []
    with open(sourceFile) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        for row in csv_reader:                  #every malware sequence
            tempName=""
            tempSequence.clear()
            for elem in row:                    #every elem seperated by comma
                if(elem == row[0]):             #malware sequence name 
                    tempName = elem
                else:                           #sequence itself
                    tempSequence.append(elem)
            sequenceList.append(MalwareSequence(tempName,tempSequence))
    return sequenceList

def createModelInfo():
    #klee output enumerations to meaningful strings 
    retVal = []
    ptraceTrans = {
        "0" : "PTRACE_TRACEME",
        "1" : "PTRACE_PEEKTEXT",
        "2" : "PTRACE_PEEKDATA",
        "3" : "PTRACE_PEEKUSER",
        "4" : "PTRACE_POKETEXT",
        "5" : "PTRACE_POKEDATA",
        "6" : "PTRACE_POKEUSER",
        "7" : "PTRACE_CONT",
        "8" : "PTRACE_KILL",
        "9" : "PTRACE_SINGLESTEP",
        "12" : "PTRACE_GETREGS",
        "13" : "PTRACE_SETREGS",
        "14" : "PTRACE_GETFPREGS",
        "15" : "PTRACE_SETFPREGS",
        "16" : "PTRACE_ATTACH",
        "17" : "PTRACE_DETACH",
        "18" : "PTRACE_GETFPXREGS",
        "19" : "PTRACE_SETFPXREGS",
        "24" : "PTRACE_SYSCALL",
    }
    retVal.append(ModelInfo("[OpenProcess]",{}))
    retVal.append(ModelInfo("[VirtualAllocEx]",{}))
    retVal.append(ModelInfo("[WriteProcessMemory]",{}))
    retVal.append(ModelInfo("[CreateRemoteThread]",{}))
    retVal.append(ModelInfo("[ptrace]",ptraceTrans))

    return retVal

def showProofs(attacks, logFile):
    with open(logFile,"r") as source:
        for line in source: #klee log satirina bak
            isModelled = 0
            for attack in attacks:
                print(f"{attack.name}")
                if(line.find(attack.name)!=-1):          # Modelledigimiz bir fonk. ait output.
                    if(model.name == "[ptrace]"):         # ptrace log'larina ozel bir call seq. topla
                        print("Ptrace proof")
                    else:
                        print("Baska proof")
                    isModelled = 1
                    break                               

def runAnalysis(suspiciousSequence, knownSequece):
    attacks = []
    for ks in knownSequece:
        isFound = ks.compareWithSelf(suspiciousSequence)
        if(isFound == 1):
            attacks.append(ks)
    return attacks
            

def main():
    ks = importKnownSequences("malware_sequences.csv")
    modelInfo = createModelInfo()
    ss = importSuspiciousSequence("test000010.ktest.ptrace",modelInfo)
    attacks = runAnalysis(ss,ks)
    #showProofs(attacks, modelInfo, "test000010.ktest.ptrace")

if __name__=='__main__':
    main()