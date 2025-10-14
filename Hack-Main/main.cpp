#include"GetProcessID.h"
#include"GetBaseMoudleAddress.h"
#include"FindDMAAddy.h"

#include <iostream>
int main()
{
	DWORD ProcessID = GetProcessID(L"ac_client.exe");
	uintptr_t BaseAddress = GetBaseModuleAddress(ProcessID, L"ac_client.exe");

	std::cout <<"Base Address " << std::hex << BaseAddress << '\n';

	HANDLE Hprocess = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessID);

	uintptr_t NewBaseAddress = BaseAddress + 0x10f4f4;

	uintptr_t current_ammo_address = FindDMAAddy(Hprocess, NewBaseAddress, { 0xF8 });

	int ammo=6974;

	ReadProcessMemory(Hprocess, (BYTE*)current_ammo_address, &ammo, sizeof(ammo), 0);

	std::cout <<std::dec<< ammo << '\n';

	int new_ammo = 6974;

	WriteProcessMemory(Hprocess, (BYTE*)current_ammo_address, &new_ammo, sizeof(new_ammo), 0);




}
