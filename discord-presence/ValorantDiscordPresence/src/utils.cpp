#include "utils.h"

namespace {
	PROCESS_INFORMATION pi;
	HANDLE valorantPHandle = 0;
}

bool openExistingValorantApplication() { //returns true if already open
	DWORD pid = 0;

	// Create toolhelp snapshot
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process;
	ZeroMemory(&process, sizeof(process));
	process.dwSize = sizeof(process);

	// Walkthrough all processes
	if (Process32First(snapshot, &process))
	{
		do
		{
			std::wstring ws(process.szExeFile);
			if (std::string(ws.begin(), ws.end()) == std::string("VALORANT.exe"))
			{
				pid = process.th32ProcessID;
				break;
			}
		} while (Process32Next(snapshot, &process));
	}

	CloseHandle(snapshot);

	if (pid == 0) return false; //Process not found

	valorantPHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	return true;
}

void startValorantApplication() {
	if (openExistingValorantApplication()) return;
	std::cout << "Launching valorant...\n";

	STARTUPINFOA si;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));


	std::ifstream configFile("config.txt");
	std::string cmd;
	std::getline(configFile, cmd);
	cmd = std::format("\"{}\" --launch-product=valorant --launch-patchline=live", cmd);

	if (!CreateProcessA
	(
		NULL,					// No module name (use command line)
		_strdup(cmd.c_str()),	// Command to launch application
		NULL,					// Process handle not inheritable
		NULL,					// Thread handle not inheritable
		FALSE,					// Set handle inheritance to FALSE
		0,						// No creation flags
		NULL,					// Use parent's environment block
		NULL,					// Use parent's starting directory
		&si,					// Pointer to STARTUPINFO structure
		&pi						// Pointer to PROCESS_INFORMATION structure
	)) {
		//printf("CreateProcess failed (%d).\n", GetLastError());
		exit(-1);
	}
	CloseHandle(pi.hThread);
	valorantPHandle = pi.hProcess;
}

bool isValorantClosed() {
	long wait = WaitForSingleObject(valorantPHandle, 0);
	if (wait == WAIT_FAILED || wait == WAIT_OBJECT_0) {
		CloseHandle(valorantPHandle);
		return true;
	}
	return false;
}