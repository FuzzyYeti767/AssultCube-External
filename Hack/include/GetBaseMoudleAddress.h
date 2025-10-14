#pragma once
#include<Windows.h>
#include<TlHelp32.h>

uintptr_t GetBaseModuleAddress(DWORD ProcessID, const wchar_t* ProcessName);


