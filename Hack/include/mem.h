#pragma once
#include<Windows.h>
namespace mem
{
	void PatchEx(BYTE* dst, BYTE* src, unsigned int Size_, HANDLE hProcess);
	void NopEx(BYTE* dst, unsigned int Size_, HANDLE hProcess);

}


