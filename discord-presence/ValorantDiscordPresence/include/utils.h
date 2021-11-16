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

inline std::string valorantCmd;

void startValorantApplication();
bool isValorantClosed();
void popup(const char* text);
