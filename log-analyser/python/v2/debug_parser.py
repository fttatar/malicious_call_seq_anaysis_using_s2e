import re
from shutil import copyfile
#result = re.search("HOOK\].*_Hook$|    state", line)

def getImportantLogs(debugFile):
    with open('0_importantLogs.txt', 'w') as importantLogs:
        with open(debugFile,"r",encoding="utf8") as source:
            waitForQuotation = False
            checkNextTestCase = False
            for line in source:
                line =  re.sub("\n","",line)
                if(checkNextTestCase == True):
                    if("[State" not in line):
                        print(line,file=importantLogs)
                        continue
                    else:
                        checkNextTestCase = False

                result = re.search("HOOK\]|    state|Forking", line)
                if(result):
                    print(line,file=importantLogs)
                    if(("{[" in line)and("]}" in line)): ## {[API]} gibi satirlar
                        pass#print("[SINGLE LINE]"+line)
                    elif ("{[" in line): ##HOOK icerip {[ ile baslayan satir:
                        waitForQuotation = True
                        pass#print("[LINE  START]"+line)
                    elif ("]}" in line): ##HOOK icerip ]} ile biten satir:
                        waitForQuotation = False
                        pass#print("[LINE    END]"+line)
                    else: ##HOOK icerip ]} icermeyen normal satir
                        pass#print("[SINGLE LINE]"+line) 
                else:
                    if(waitForQuotation == True):
                        print(line,file=importantLogs)
                        if("]}" in line): ##HOOK icermeden ]} ile bitenler
                            waitForQuotation = False
                            pass#print("[LINE    END]"+line)
                        else:
                            pass#print("[LINE CONT]"+line)
                    elif(("TestCaseGenerator:" in line)):
                        print(line,file=importantLogs)
                        checkNextTestCase = True
                    else:
                        pass

                                         
def collectEvidences():
    with open('1_importantLogs_evidencesCollected.txt', 'w') as evidencesCollectedLog:
        with open("0_importantLogs.txt","r",encoding="utf8") as importantLogs:
            evidenceCollecting = False
            evidenceLine = ""
            evidenceData = ""
            for line in importantLogs:
                if(evidenceCollecting == True):
                    if("]}" in line):
                        evidenceCollecting = False
                        evidenceLine += evidenceData
                        index = line.rfind("HOOK]")
                        evidenceLine += line[index+6:]
                        evidenceLine = re.sub("\n","",evidenceLine)
                        print(evidenceLine,file=evidencesCollectedLog)
                        evidenceLine=""
                        evidenceData=""
                    else:
                        index = line.rfind("HOOK]")
                        data = line[index+6:]
                        data = re.sub("\n"," ",data) 
                        evidenceData += data
                    continue

                if("|evidence" in line):
                    evidenceCollecting = True
                    evidenceLine += line
                    if("]}" in line):
                        evidenceCollecting = False
                        evidenceLine = re.sub("\n","",evidenceLine)
                        print(evidenceLine,file=evidencesCollectedLog)
                        evidenceLine=""
                else:
                    #print(re.sub("\n","",line))
                    print(re.sub("\n","",line),file=evidencesCollectedLog)
                    

def collectForkMessages():
    with open('2_statesCollected.txt', 'w') as statesCollected:
        with open("1_importantLogs_evidencesCollected.txt","r",encoding="utf8") as evidencesCollected:
            forkData = ""
            remainingLine = 0
            for line in evidencesCollected:
                if (remainingLine != 0):
                    forkData += line
                    remainingLine = remainingLine-1
                    if(remainingLine == 0):
                        print(re.sub("\n","",forkData),file=statesCollected)
                        forkData=""
                    continue

                if("Forking state" in line):
                    forkData += re.sub("\n","",line)
                    remainingLine = 2                  
                else:
                    print(re.sub("\n","",line),file=statesCollected)
                        

def splitStateMessages():
    realStateCount = 0 #s2e state numaralarina 0'dan basliyor.
    MAX_STATE_COUNT = 500
    with open("2_statesCollected.txt","r",encoding="utf8") as statesCollected:
        for i in range(MAX_STATE_COUNT):
            with open('state{0}.txt'.format(i), 'a') as stateTXT:            
                statesCollected.seek(0) #her state dosyayi tekrar bastan okuyacak
                
                currentState = "[State {0}]".format(i)
                #print(currentState)

                for line in statesCollected:
                    if(currentState in line):
                        if("TestCaseGenerator" in line):
                            collectingTestCases = True

                        if("Forking state" in line):
                            realStateCount = realStateCount+1
                            
                            #detect new state number (tersten ariyoruz)
                            firstIndex = line.rfind("state")
                            secondIndex = line.rfind("state",0,firstIndex)
                            firstStateName = line[secondIndex:firstIndex]
                            firstStateName=re.sub(" ","",firstStateName)
                            firstStateName = int(line[secondIndex+6:firstIndex])

                            secondStateName = line[firstIndex:]
                            secondStateName=re.sub(" ","",secondStateName)
                            secondStateName = int(line[firstIndex+6:])

                            #use new state name! not the current one!
                            newState = firstStateName if firstStateName != i else secondStateName

                            #copy everything to there
                            stateTXT.flush()
                            copyfile('state{0}.txt'.format(i), 'state{0}.txt'.format(newState))
                        else:
                            #print(re.sub("\n","",line))        
                            print(re.sub("\n","",line),file=stateTXT)
                    else:
                        if(collectingTestCases == True):
                            if("[State" not in line):
                                print(re.sub("\n","",line),file=stateTXT)
                            else:
                                collectingTestCases = False

            if(realStateCount == i):
                print("States upto State {0} is splitted.".format(i))
                break
            


    #en bastan basla, state 0 ise git state0'in dokumanına yaz, fork diyorsa 
    #hangi state'e fork oldugunu gor, onun dosyasına kopyala.


def main():
    getImportantLogs("debug.txt")
    collectEvidences()
    collectForkMessages()
    splitStateMessages()

if __name__=='__main__':
    main()

