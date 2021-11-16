#include "utils.h"

namespace {
	PROCESS_INFORMATION pi;
	HANDLE valorantPHandle = 0;

	std::wstring regCmd;
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

LONG getRiotClientPath(){
	HKEY hKey;
	LONG lRes = RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Riot Game valorant.live", 0, KEY_READ, &hKey);
	if (ERROR_SUCCESS != lRes) return lRes;

	WCHAR szBuffer[512];
	DWORD dwBufferSize = sizeof(szBuffer);
	ULONG nError;
	nError = RegQueryValueExW(hKey, L"UninstallString", 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
	if (ERROR_SUCCESS == nError) regCmd = szBuffer;
	return nError;
 }

void startValorantApplication() {
	if (openExistingValorantApplication()) return;
	std::cout << "Launching valorant...\n";

	LONG regReadRes = getRiotClientPath();
	if (ERROR_SUCCESS != regReadRes) {
		popup("Unable to find VALORANT application. Please ensure the game is installed and attempt to launch the application again.");
		exit(0);
	}
	regCmd = regCmd.substr(0, regCmd.find(L" --uninstall"));

	valorantCmd = std::string(regCmd.begin(),regCmd.end());
	valorantCmd = std::format("{} --launch-product=valorant --launch-patchline=live", valorantCmd);

	STARTUPINFOA si;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcessA
	(
		NULL,							// No module name (use command line)
		_strdup(valorantCmd.c_str()),	// Command to launch application
		NULL,							// Process handle not inheritable
		NULL,							// Thread handle not inheritable
		FALSE,							// Set handle inheritance to FALSE
		0,								// No creation flags
		NULL,							// Use parent's environment block
		NULL,							// Use parent's starting directory
		&si,							// Pointer to STARTUPINFO structure
		&pi								// Pointer to PROCESS_INFORMATION structure
	)) {
		popup("Unable to start VALORANT.exe. Please try to launch the application again.");
		printf("CreateProcess failed (%d)\n", GetLastError());
		exit(0);
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

void popup(const char* text) {
	std::string finalText = std::format("{}\n\nIf the problem persists, please report this issue to the developer.", text);
	MessageBox(nullptr, std::wstring(finalText.begin(),finalText.end()).c_str(), L"VALORANT Discord Presence", MB_OK);
}