#include"GetProcessID.h"
#include"GetBaseMoudleAddress.h"
#include"FindDMAAddy.h"

#include <iostream>

#include "mem.h"

// TODO: Add a check to ensure that "ac_client.exe" is running before continuing.


constexpr auto BASE_ADDRESS_OFFSET = 0x10F4F4;
constexpr auto BASE_ADDRESS_HEALTH_OFFSET = 0xF8;
int main()
{
	
		//DWORD ProcessID = GetProcessID(L"ac_client.exe");
		//uintptr_t BaseAddress = GetBaseModuleAddress(ProcessID, L"ac_client.exe");

		//std::cout << "Base Address " << std::hex << BaseAddress << '\n';

		//HANDLE Hprocess = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessID);

		//uintptr_t NewBaseAddress = BaseAddress + BASE_ADDRESS_OFFSET;

		//uintptr_t current_ammo_address = FindDMAAddy(Hprocess, NewBaseAddress, { BASE_ADDRESS_HEALTH_OFFSET });


		//int heatlh = 0;
		//ReadProcessMemory(Hprocess, (BYTE*)current_ammo_address, &heatlh, sizeof(heatlh), 0);

		//std::cout << "Before Health " << std::dec << heatlh << '\n';

		//int new_health = 6974;
		//WriteProcessMemory(Hprocess, (BYTE*)current_ammo_address, &new_health, sizeof(new_health), 0);


	HANDLE     hProcess = 0;
	uintptr_t  BaseModuleAddress = 0;

	bool bhealth = false;
	bool bAmmo = false;
	bool bRecoil = false;
	uintptr_t LocalEntity = 0;
	DWORD ProcessID = GetProcessID(L"ac_client.exe");
	if (ProcessID != 0)
	{
		BaseModuleAddress = GetBaseModuleAddress(ProcessID, L"ac_client.exe");

		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);

		LocalEntity = BaseModuleAddress + 0x10F4F4;
	}
	else
	{
		std::cout << "Process Not Found You should open Process First " << '\n';
		return 0;
	}

	DWORD dwExit = 0;
		while (GetExitCodeProcess(hProcess,&dwExit) &&dwExit==STILL_ACTIVE)
		{

			if (GetAsyncKeyState(VK_NUMPAD1)&1)
			{
				bAmmo = !bAmmo;
				if (bAmmo==true)
				{
					// FF 06 is inc variable value
					mem::PatchEx((BYTE*)BaseModuleAddress + 0x637E9, (BYTE*)"\xFF\x06", 2, hProcess);
				}
				else
				{
					// FF 0E is dec variable value
					mem::PatchEx((BYTE*)BaseModuleAddress + 0x637E9, (BYTE*)"\xFF\x0E", 2, hProcess);
				}
			}

			if (GetAsyncKeyState(VK_NUMPAD2) & 1)
			{
				bhealth = !bhealth;

			}
			if (GetAsyncKeyState(VK_NUMPAD3) & 1)
			{
			
				bRecoil = !bRecoil;
				if (bRecoil==true)
				{
					std::cout << "No Recoil on !! " << '\n';
					mem::NopEx((BYTE*)BaseModuleAddress + 0x63786, 10, hProcess);
					
				}
				else
				{
					std::cout << "No Recoil off !! " << '\n';
					mem::PatchEx((BYTE*)BaseModuleAddress + 0x63786, (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10, hProcess);
				}
			}
			if (GetAsyncKeyState(VK_NUMPAD4) & 1)
			{
				return 0;
			}
		}



		
	

	

}
