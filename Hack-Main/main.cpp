#include"GetProcessID.h"
#include"GetBaseMoudleAddress.h"
#include"FindDMAAddy.h"

#include <iostream>

constexpr auto BASE_ADDRESS_OFFSET = 0x10F4F;
constexpr auto BASE_ADDRESS_HEALTH_OFFSET = 0xF8;
int main()
{
	DWORD ProcessID = GetProcessID(L"ac_client.exe");
	uintptr_t BaseAddress = GetBaseModuleAddress(ProcessID, L"ac_client.exe");

	std::cout <<"Base Address " << std::hex << BaseAddress << '\n';

	HANDLE Hprocess = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessID);

	uintptr_t NewBaseAddress = BaseAddress + BASE_ADDRESS_OFFSET;

	uintptr_t current_ammo_address = FindDMAAddy(Hprocess, NewBaseAddress, { BASE_ADDRESS_HEALTH_OFFSET });


	int heatlh = 0;
	ReadProcessMemory(Hprocess, (BYTE*)current_ammo_address, &heatlh, sizeof(heatlh), 0);

	std::cout <<"Before Health " <<std::dec<< heatlh << '\n';

	int new_health = 6974;
	WriteProcessMemory(Hprocess, (BYTE*)current_ammo_address, &new_health, sizeof(new_health), 0);




}
