#include "mem.h"

void mem::PatchEx(BYTE* dst, BYTE* src, unsigned int Size_, HANDLE hProcess)
{
	DWORD oldprotect;
	VirtualProtectEx(hProcess, dst, Size_, PAGE_EXECUTE_READWRITE, &oldprotect);
	WriteProcessMemory(hProcess, dst, src, Size_, nullptr);
	VirtualProtectEx(hProcess, dst, Size_, oldprotect, &oldprotect);
}

void mem::NopEx(BYTE* dst, unsigned int Size_, HANDLE hProcess)
{
	BYTE* nopArray = new BYTE[Size_];
	memset(nopArray, 0x90, Size_);
	PatchEx(dst, nopArray, Size_, hProcess);
	delete[] nopArray;

}


