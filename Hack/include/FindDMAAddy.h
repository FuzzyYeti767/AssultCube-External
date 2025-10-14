#pragma once
#include <vector>
#include"Windows.h"
#include"TlHelp32.h"

uintptr_t FindDMAAddy(HANDLE Process, uintptr_t ptr, std::vector<unsigned int>offset);