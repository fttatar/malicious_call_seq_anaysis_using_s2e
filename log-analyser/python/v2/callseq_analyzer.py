#ptrace'in icerisinde utf-8 olmayan karakterler sorun cikartti, sildim.
import csv
import re 
from os import path
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
                    print(f"WARNING :: {self.name} is encountered.\n")
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
             

def importSuspiciousSequence(logFile):
    callSequence=[]
    with open(logFile,"r",encoding="utf8") as source:
        for line in source: 
            if(("_Model" in line) and ("|evidence" not in line) and ("|info" not in line)):
                try:
                    index=line.index("|HOOK]")
                except:
                    print("There is a line with no |HOOK] in it")
                    continue
                clearedLine=line[index:]
                clearedLine = re.sub("\|HOOK] ","",clearedLine)
                clearedLine = re.sub("_Model","",clearedLine)
                clearedLine = re.sub("\n","",clearedLine)  
                callSequence.append(clearedLine)                               

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

def runAnalysis(suspiciousSequence, knownSequece):
    attacks = []
    for ks in knownSequece:
        isFound = ks.compareWithSelf(suspiciousSequence)
        if(isFound == 1):
            attacks.append(ks)
    return attacks

def showEvidence(logFile):
    print("SEQUENCE :: << BURAYA MANUAL OLARAK SEQUENCE'I YAZ >>")
    with open(logFile,"r",encoding="utf8") as source:
        testCaseEncountered=False
        for line in source: 
            if("[State" not in line):
                if(testCaseEncountered==True):
                    clearedLine = re.sub("\n","",line) 
                    print(clearedLine) 
                    testCaseEncountered=False 
                    continue
            if("|evidence" in line):
                index= line.index("|HOOK]")
                clearedLine=line[index:]
                clearedLine = re.sub("\|HOOK] ","",clearedLine)
                clearedLine = re.sub("_Model","",clearedLine)
                clearedLine = re.sub("\n","",clearedLine)  
                print(clearedLine)        
            elif(("TestCaseGenerator" in line)and("= {" in line)):
                index= line.index("TestCaseGenerator:")
                clearedLine=line[index:]
                clearedLine = re.sub("\n","",clearedLine) 
                testCaseEncountered=True 
                print(clearedLine) 

def main():
    ks = importKnownSequences("malware_sequences.csv")
    for i in range(100):
        fileName = "state{0}.txt".format(i)
        if(path.isfile(fileName)): 
            print("\n\nAnalyzing the call sequence ending with [State {0}]\n".format(i))   
            ss = importSuspiciousSequence(fileName)
            #print(ss)
            attacks = runAnalysis(ss,ks)
            if(attacks != []):
                showEvidence(fileName)


if __name__=='__main__':
    main()