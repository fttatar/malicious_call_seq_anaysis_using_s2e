package tr.edu.metu.e194318;

import javax.sound.midi.Soundbank;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Main {
    public static void isProjecssInjection(ArrayList<String> functionCalls){

        /* processInjectionRule:
            1) attach cagirilacak.
            2) get regs yapilacak.
            3) poke text yapilacak.
            4) setregs yapilacak.
         */

        int state=0;
        for(String call: functionCalls)
        {
            if((state==0) && call.contains("PTRACE_ATTACH"))
            {
                System.out.println("PTRACE_ATTACH encountered");
                state=1;
            }
            else if((state==1) && call.contains("PTRACE_GETREGS"))
            {
                System.out.println("PTRACE_GETREGS encountered");
                state=2;
            }
            else if((state==2) && (call.contains("PTRACE_POKETEXT")||
                                   call.contains("PTRACE_POKEDATA")||
                                   call.contains("PTRACE_POKEUSER")))
            {
                System.out.println("PTRACE_POKEXXXX encountered");
                state=3;
            }
            else if((state==3) && call.contains("PTRACE_SETREGS"))
            {
                System.out.println("PTRACE_SETREGS encountered");
                state=4;
                System.out.println("Process injection detected!");
            }
            else
            {
                /* other work */
            }

        }
    }
    public static void main(String[] args) {
        System.out.println("Analysis started\n");

        BufferedReader reader;
        ArrayList<String> called = new ArrayList<String>();

        /* read what needs to be parsed */
        try {
            reader = new BufferedReader(new FileReader(
                    "sample/test000014.ktest.ptrace"));
            String line = reader.readLine();
            while (line != null) {
                /* get ptrace line */
                if(line.contains("[ptrace]"))
                {
                    /* get ptrace option */
                    String option = line.substring(line.indexOf("r:") + 2, line.indexOf(","));
                    //TODO: r: outputu güzel değil, bunu option: şeklinde yapalım.

                    switch(Integer.parseInt(option)){
                        /* PTRACE_TRACEME */
                        case 0:
                        {
                            called.add("PTRACE_TRACEME");
                            break;
                        }

                        /* PTRACE_PEEKTEXT  */
                        case 1:
                        {
                            called.add("PTRACE_PEEKTEXT");
                            break;
                        }

                        /* PTRACE_PEEKDATA  */
                        case 2:
                        {
                            called.add("PTRACE_PEEKDATA");
                            break;
                        }

                        /* PTRACE_PEEKUSER  */
                        case 3:
                        {
                            called.add("PTRACE_PEEKUSER");
                            break;
                        }

                        /* PTRACE_POKETEXT  */
                        case 4:
                        {
                            called.add("PTRACE_POKETEXT");
                            break;
                        }

                        /* PTRACE_POKEDATA  */
                        case 5:
                        {
                            called.add("PTRACE_POKEDATA");
                            break;
                        }

                        /* PTRACE_POKEUSER  */
                        case 6:
                        {
                            called.add("PTRACE_POKEUSER");
                            break;
                        }

                        /* PTRACE_CONT */
                        case 7:
                        {
                            called.add("PTRACE_CONT");
                            break;
                        }

                        /* PTRACE_KILL */
                        case 8:
                        {
                            called.add("PTRACE_KILL");
                            break;
                        }

                        /* PTRACE_SINGLESTEP */
                        case 9:
                        {
                            called.add("PTRACE_SINGLESTEP");
                            break;
                        }

                        /* PTRACE_GETREGS */
                        case 12:
                        {
                            called.add("PTRACE_GETREGS");
                            break;
                        }

                        /* PTRACE_SETREGS  */
                        case 13:
                        {
                            called.add("PTRACE_SETREGS");
                            break;
                        }

                        /* PTRACE_GETFPREGS   */
                        case 14:
                        {
                            called.add("PTRACE_GETFPREGS");
                            break;
                        }

                        /* PTRACE_SETFPREGS   */
                        case 15:
                        {
                            called.add("PTRACE_SETFPREGS");
                            break;
                        }

                        /* PTRACE_ATTACH  */
                        case 16:
                        {
                            called.add("PTRACE_ATTACH");
                            break;
                        }

                        /* PTRACE_DETACH  */
                        case 17:
                        {
                            called.add("PTRACE_DETACH");
                            break;
                        }

                        /* PTRACE_GETFPXREGS  */
                        case 18:
                        {
                            called.add("PTRACE_GETFPXREGS");
                            break;
                        }

                        /* PTRACE_SETFPXREGS */
                        case 19:
                        {
                            called.add("PTRACE_SETFPXREGS");
                            break;
                        }

                        /* PTRACE_SYSCALL */
                        case 24:
                        {
                            called.add("PTRACE_SYSCALL");
                            break;
                        }

                        default:
                        {
                            System.out.println("Unexpected ptrace option: "+option);
                            break;
                        }

                    }
                }
                else if(line.contains("[someOtherFunctionModel]"))
                {

                }
                else
                {
                    System.out.println("Unexpected line is enountered!");
                }
                line = reader.readLine();
            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        isProjecssInjection(called);
    }
}
