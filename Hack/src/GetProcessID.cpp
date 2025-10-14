
#include"GetProcessID.h"

DWORD GetProcessID(const wchar_t* ProcessName)
{
	DWORD ProcessID = 0;

	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (snap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 ProcessEntry;
		ProcessEntry.dwSize = sizeof(ProcessEntry);

		Process32First(snap, &ProcessEntry);
		do
		{
			if (!_wcsicmp(ProcessName, ProcessEntry.szExeFile))
			{
				ProcessID = ProcessEntry.th32ProcessID;
				break;
			}
		} while (Process32Next(snap, &ProcessEntry));

	}
	CloseHandle(snap);
	return ProcessID;
}
