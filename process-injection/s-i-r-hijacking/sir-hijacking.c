#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <memoryapi.h>

//  Forward declarations:
BOOL GetProcessList( );
BOOL ListProcessModules( DWORD dwPID );
BOOL ListProcessThreads( DWORD dwOwnerPID );
BOOL SuspendRequest(int pid, int tid);
void printError( TCHAR* msg );
char gl_searchFor[256] = {'\0'};
int gl_pid = 0;
int gl_tid = 0;

int main( void )
{
  printf("Which process are you looking for?\n");
  scanf("%s",gl_searchFor);
  GetProcessList();

  printf("Enter a pid:tid combination (hex form, without 0x)\n");
  scanf("%x:%x",&gl_pid,&gl_tid);
  //ListProcessThreads(gl_pid);
  SuspendRequest(gl_pid, gl_tid);

  return 0;
}

BOOL SuspendRequest(int pid, int tid)
{
  HANDLE hThread = INVALID_HANDLE_VALUE; /* by ftt */
  HANDLE hThreadSnap = INVALID_HANDLE_VALUE; 
  DWORD dwTemp;
  THREADENTRY32 te32; 
 
  // Take a snapshot of all running threads of the given pid
  hThreadSnap = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, pid); 
  if( hThreadSnap == INVALID_HANDLE_VALUE ) 
  {
    printf("[FAIL] Failed to take thread snapshot!\n");
    return( FALSE ); 
  }
    
  // Fill in the size of the structure before using it. 
  te32.dwSize = sizeof(THREADENTRY32); 
 
  // Retrieve information about the first thread,
  // and exit if unsuccessful
  if( !Thread32First( hThreadSnap, &te32 ) ) 
  {
    printf("[FAIL] Couldn't retrieve an information for the first thread!\n");
    printError( TEXT("Thread32First") ); // show cause of failure
    CloseHandle( hThreadSnap );          // clean the snapshot object
    return( FALSE );
  }

  // Now walk the thread list of the system,
  // and display information about each thread
  // associated with the specified process
  do 
  { 
    if( te32.th32ThreadID == tid )
    {
      printf("[OK] Find\n"); 
      hThread = OpenThread( PROCESS_ALL_ACCESS, FALSE, te32.th32ThreadID );
      if( hThread == NULL )
      {
        printf("[FAIL] Couldn't open the thread!\n");
        printError( TEXT("OpenThread") );
      }
      else
      {
        printf("[OK] Open\n"); 
        dwTemp = SuspendThread(hThread);
        if(dwTemp != (DWORD)-1)
        {
          printf("[OK] Suspend\n");
        }
        else
        {
          printf("[FAIL] Suspend\n");
        }
        
        /* Virtual alloc ex */


        /* Write process memory */
        /*
        BOOL WriteProcessMemory(
          HANDLE  hProcess,
          LPVOID  lpBaseAddress,
          LPCVOID lpBuffer,
          SIZE_T  nSize,
          SIZE_T  *lpNumberOfBytesWritten
        );
        */

        /* Set thread context */


        dwTemp = ResumeThread(hThread);
        if(dwTemp != (DWORD)-1)
        {
          printf("[OK] Resume\n");
        }
        else
        {
          printf("[FAIL] Resume\n");
        }
      }
    }
  } while( Thread32Next(hThreadSnap, &te32 ) ); 

  CloseHandle( hThreadSnap );
  return( TRUE );
}

BOOL GetProcessList()
{
  HANDLE hProcessSnap;
  HANDLE hProcess;
  PROCESSENTRY32 pe32;
  DWORD dwPriorityClass;

  // Take a snapshot of all processes in the system.
  hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
  if( hProcessSnap == INVALID_HANDLE_VALUE )
  {
    printf("[Error] Invalid handle value!\n");
    printError( TEXT("CreateToolhelp32Snapshot (of processes)") );
    return( FALSE );
  }

  // Set the size of the structure before using it.
  pe32.dwSize = sizeof( PROCESSENTRY32 );

  // Retrieve information about the first process,
  // and exit if unsuccessful
  if( !Process32First( hProcessSnap, &pe32 ) )
  {
    printf("[Error] Failed to retrieve information for the first process!\n");
    printError( TEXT("Process32First") ); // show cause of failure
    CloseHandle( hProcessSnap );          // clean the snapshot object
    return( FALSE );
  }

  // Now walk the snapshot of processes, and
  // display information about each process in turn
  do
  {
    if(strcmp(pe32.szExeFile,gl_searchFor) == 0)
    {
      printf( TEXT("\n\n=====================================================" ));
      printf( TEXT("\nprocess:  %s"), pe32.szExeFile );
      printf( TEXT("\n------------------------------------------------------\n" ));

      // Retrieve the priority class.
      dwPriorityClass = 0;
      hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID );
      if( hProcess == NULL )
      {
        printf("[Error] Couldn't open the process!\n");
        printError( TEXT("OpenProcess") );
      }
      else
      {
        dwPriorityClass = GetPriorityClass( hProcess );
        if( !dwPriorityClass )
        {
          printf("[Error] Couldn't get priority class!\n");
          printError( TEXT("GetPriorityClass") );   
        }
        CloseHandle( hProcess );
      }

      printf( TEXT("\n  pid               = 0x%08X"), pe32.th32ProcessID );
      printf( TEXT("\n  # of threads      = %d"),   pe32.cntThreads );
      printf( TEXT("\n  parent pid        = 0x%08X"), pe32.th32ParentProcessID );
      printf( TEXT("\n  prio base         = %d"), pe32.pcPriClassBase );
      if( dwPriorityClass )
        printf( TEXT("\n  prio class      = %d"), dwPriorityClass );
      printf("\n");
      // List the modules and threads associated with this process
      //ListProcessModules( pe32.th32ProcessID );
      ListProcessThreads( pe32.th32ProcessID );

    }
    else
    {
      
    }
  } while( Process32Next( hProcessSnap, &pe32 ) );

  CloseHandle( hProcessSnap );
  return( TRUE );
}


BOOL ListProcessModules( DWORD dwPID )
{
  HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
  MODULEENTRY32 me32;

  // Take a snapshot of all modules in the specified process.
  printf("Now taking snapshot of the process modules..\n");
  hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, dwPID );
  if( hModuleSnap == INVALID_HANDLE_VALUE )
  {
    printf("Failed to take snapshot!\n");
    printError( TEXT("CreateToolhelp32Snapshot (of modules)") );
    return( FALSE );
  }

  // Set the size of the structure before using it.
  me32.dwSize = sizeof( MODULEENTRY32 );

  // Retrieve information about the first module,
  // and exit if unsuccessful
  if( !Module32First( hModuleSnap, &me32 ) )
  {
    printf("Failed to retrieve first module!\n");
    printError( TEXT("Module32First") );  // show cause of failure
    CloseHandle( hModuleSnap );           // clean the snapshot object
    return( FALSE );
  }

  // Now walk the module list of the process,
  // and display information about each module
  do
  {
    printf( TEXT("\n\n   MODULE :         %s"),   me32.szModule );
    printf( TEXT("\n     Executable       = %s"),     me32.szExePath );
    printf( TEXT("\n     pid              = 0x%08X\n"),         me32.th32ProcessID );
    //printf( TEXT("\n     Ref count (g)  = 0x%04X"),     me32.GlblcntUsage );
    //printf( TEXT("\n     Ref count (p)  = 0x%04X"),     me32.ProccntUsage );
    //printf( TEXT("\n     Base address   = 0x%08X"), (DWORD) me32.modBaseAddr );
    //printf( TEXT("\n     Base size      = %d"),             me32.modBaseSize );

  } while( Module32Next( hModuleSnap, &me32 ) );

  CloseHandle( hModuleSnap );
  return( TRUE );
}

BOOL ListProcessThreads( DWORD dwOwnerPID ) 
{ 
  HANDLE hThreadSnap = INVALID_HANDLE_VALUE; 
  THREADENTRY32 te32; 
 
  // Take a snapshot of all running threads  
  hThreadSnap = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, 0 ); 
  if( hThreadSnap == INVALID_HANDLE_VALUE ) 
  {
    printf("[Error] Failed to take thread snapshot!\n");
    return( FALSE ); 
  }
    
 
  // Fill in the size of the structure before using it. 
  te32.dwSize = sizeof(THREADENTRY32); 
 
  // Retrieve information about the first thread,
  // and exit if unsuccessful
  if( !Thread32First( hThreadSnap, &te32 ) ) 
  {
    printf("[Error] Couldn't retrieve an information for the first thread!\n");
    printError( TEXT("Thread32First") ); // show cause of failure
    CloseHandle( hThreadSnap );          // clean the snapshot object
    return( FALSE );
  }

  // Now walk the thread list of the system,
  // and display information about each thread
  // associated with the specified process
  do 
  { 
    if( te32.th32OwnerProcessID == dwOwnerPID )
    {
      printf( TEXT("    tid             = 0x%08X"), te32.th32ThreadID );  
      printf( TEXT("\n"));
    }
  } while( Thread32Next(hThreadSnap, &te32 ) ); 

  CloseHandle( hThreadSnap );
  return( TRUE );
}

void printError( TCHAR* msg )
{
  DWORD eNum;
  TCHAR sysMsg[256];
  TCHAR* p;

  eNum = GetLastError( );
  FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
         NULL, eNum,
         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
         sysMsg, 256, NULL );

  // Trim the end of the line and terminate it with a null
  p = sysMsg;
  while( ( *p > 31 ) || ( *p == 9 ) )
    ++p;
  do { *p-- = 0; } while( ( p >= sysMsg ) &&
                          ( ( *p == '.' ) || ( *p < 33 ) ) );

  // Display the message
  printf( TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg );
}