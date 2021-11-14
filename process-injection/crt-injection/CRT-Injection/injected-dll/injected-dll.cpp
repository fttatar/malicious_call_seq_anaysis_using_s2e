// injected-dll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "stdio.h"
#include "windows.h"
#include <shlobj.h>

#define THREAD_SOUND    700
#define PROCESS_SOUND   300
#define ATTACH_LENGTH   500
#define DEATTACH_LENGTH 1000

INT APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved) {
	/* open file */
	FILE *file;
	char logPath[MAX_PATH + 1] = { 0 };
	char* toBeLogged = "\\log.txt";

	if (SHGetSpecialFolderPathA(HWND_DESKTOP, logPath, CSIDL_DESKTOP, FALSE))
	{
		/* got desktop path */
	}
	else
	{
		exit(-1);
	}
	
	/* combine dllPath and dllName */
	#pragma warning(disable:4996)
	strncat(logPath, toBeLogged, MAX_PATH);

	fopen_s(&file, logPath, "a+");
	switch (Reason) {
	case DLL_PROCESS_ATTACH:
		fprintf(file, "DLL attach function called\n");
		Beep(PROCESS_SOUND, ATTACH_LENGTH);
		break;
	case DLL_PROCESS_DETACH:
		fprintf(file, "DLL detach function called\n");
		Beep(PROCESS_SOUND, DEATTACH_LENGTH);
		break;
	case DLL_THREAD_ATTACH:
		fprintf(file, "DLL thread attach function called\n");
		break;
	case DLL_THREAD_DETACH:
		fprintf(file, "DLL thread detach function called\n");
		break;
	}

	/* close file */
	fclose(file);
	return TRUE;
}

