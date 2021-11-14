// CRT-Injection.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "stdafx.h"
#include "Windows.h";
#include "stdio.h";
#include "strsafe.h";
#include <atlstr.h>
#include <shlobj.h>
#include <string>

void ErrorExit(LPTSTR lpszFunction)
{
	//// Retrieve the system error message for the last-error code
	//
	//LPVOID lpMsgBuf;
	//LPVOID lpDisplayBuf;
	//DWORD dw = GetLastError();
	//
	//FormatMessage(
	//	FORMAT_MESSAGE_ALLOCATE_BUFFER |
	//	FORMAT_MESSAGE_FROM_SYSTEM |
	//	FORMAT_MESSAGE_IGNORE_INSERTS,
	//	NULL,
	//	dw,
	//	MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
	//	(LPTSTR)&lpMsgBuf,
	//	0, NULL);
	//
	//// Display the error message and exit the process
	//
	//lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
	//	(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	//StringCchPrintf((LPTSTR)lpDisplayBuf,
	//	LocalSize(lpDisplayBuf) / sizeof(TCHAR),
	//	TEXT("%s failed with error %d: %s"),
	//	lpszFunction, dw, lpMsgBuf);
	////MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);
	//printf("%s", CW2A((LPCTSTR)lpDisplayBuf));
	//
	//LocalFree(lpMsgBuf);
	//LocalFree(lpDisplayBuf);
	//ExitProcess(dw);
	printf("%s\n", lpszFunction);
}

int _tmain(int argc, _TCHAR* argv[])
{

	#pragma warning(disable:4996)
	//char dllPath[MAX_PATH + 1] = {0};
	//char* toBeInjected = "\\injected-dll.dll";
	//
	//if (SHGetSpecialFolderPathA(HWND_DESKTOP, dllPath, CSIDL_DESKTOP,FALSE)) 
	//{
	//	/* got desktop path */
	//}
	//else
	//{
	//	exit(-1);
	//}
	//
	///* combine dllPath and dllName */
	//strncat(dllPath,toBeInjected,MAX_PATH);
	//
	///*
	//* Get process handle passing in the process ID.
	//*/
	char* dllPath = "burasi";
	if (argc != 2) 
	{
		printf("Wrong usage! give PID!\n");
		exit(-1);
	}

	//_SYSTEMTIME lTime;
	//GetLocalTime(&lTime);
	//if (lTime.wYear == 2021)
	//{
	//	if (lTime.wMonth == 5)
	//	{
	//		if (lTime.wDay == 2)
	//		{
	//			printf("Happy Birthday!\n");
	//		}			
	//		else
	//		{
	//			exit(-1);
	//		}
	//	}
	//	else
	//	{
	//		exit(-1);
	//	}
	//}
	//else
	//{
	//	exit(-1);
	//}

	int procID = std::stoi(argv[1]);
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
	if (process == NULL) 
	{
		ErrorExit(TEXT("OpenProcess"));
	}
	else
	{
		/*
		* Get address of the LoadLibrary function.
		*/
		LPVOID addr = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
		if (addr == NULL) {
			ErrorExit(TEXT("GetProcAddress"));
		}
		else
		{
			/*
			* Allocate new memory region inside the process’s address space.
			*/
			LPVOID arg = (LPVOID)VirtualAllocEx(process, NULL, strlen(dllPath), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
			if (arg == NULL) {
				ErrorExit(TEXT("VirtualAllocEx"));
			}
			else
			{
				/*
				* Write the argument to LoadLibraryA to the process’s newly allocated memory region.
				*/
				int n = WriteProcessMemory(process, arg, dllPath, strlen(dllPath), NULL);
				if (n == 0) 
				{
					ErrorExit(TEXT("WriteProcessMemory"));
				}
				else
				{
					/*
					* Inject our DLL into the process’s address space.
					*/
					HANDLE threadID = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE)addr, arg, NULL, NULL);
					if (threadID == NULL) {
						ErrorExit(TEXT("CreateRemoteThread"));
					}
					else {
						printf("Success: the remote thread was successfully created.\n");
					}

					/*
					* Close the handle to the process, becuase we’ve already injected the DLL.
					*/
					CloseHandle(process);
				}
			}		
		}
	}

	
	return 0;
}
