#include "utils.h"

void startValorantApplication() {
	// additional information
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// start the program up
	char cmd[128];
	const char* valCmd = "\"C:/Riot Games/Riot Client/RiotClientServices.exe\" --launch-product=valorant --launch-patchline=live";
	strcpy_s(cmd, valCmd);

	if (!CreateProcessA
	(
		NULL,			// No module name (use command line)
		cmd,			// Command
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi				// Pointer to PROCESS_INFORMATION structure
	)) {
		//printf("CreateProcess failed (%d).\n", GetLastError());
		exit(-1);
	}

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}