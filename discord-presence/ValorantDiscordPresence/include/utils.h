#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <fstream>
#include <format>

#include "httplib/httplib.h"

inline std::string valorantCmd;

DWORD getExistingExePID(std::string search);
void startValorantApplication();
bool isValorantClosed();
void popup(const char* text);
