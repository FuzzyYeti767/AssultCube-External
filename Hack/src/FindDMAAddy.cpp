#include "FindDMAAddy.h"
uintptr_t FindDMAAddy(HANDLE Process, uintptr_t ptr, std::vector<unsigned int>offset)
{
	uintptr_t BaseAddress = ptr;
	for (auto m : offset)
	{
		ReadProcessMemory(Process, (BYTE*)BaseAddress, &BaseAddress, sizeof(BaseAddress),0);
		//parameter Access Memory of Process 
		
		BaseAddress += m;
	}
	return BaseAddress;

}