#include "GetBaseMoudleAddress.h"

uintptr_t GetBaseModuleAddress(DWORD ProcessID, const wchar_t* ProcessName)
{
	uintptr_t BASEADDRESS=0;

	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, ProcessID);

	if (hsnap!=INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 ModuleEntry;
		ModuleEntry.dwSize = sizeof(ModuleEntry);

		Module32First(hsnap, &ModuleEntry);
		do
		{
			if (!_wcsicmp(ProcessName, ModuleEntry.szModule) )
			{
				BASEADDRESS = (uintptr_t)ModuleEntry.modBaseAddr;
				break;
			}
		} while (Module32Next(hsnap, &ModuleEntry));


		
	}
	CloseHandle(hsnap);
	return BASEADDRESS;
}