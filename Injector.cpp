#include "Injector.h"

namespace DLL
{
	bool Injector::inject(const std::string& dllPath, DWORD processID)
	{
		HANDLE processHandle;
		processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

		LPVOID memLocation;
		memLocation = VirtualAllocEx(processHandle, 0, dllPath.length() + 1, MEM_COMMIT, PAGE_READWRITE);

		if (!WriteProcessMemory(processHandle, memLocation, (LPVOID)dllPath.data(), dllPath.length() + 1, 0))
			return false;

		HMODULE moduleHandle = GetModuleHandleA("Kernel32.dll");
		LPVOID loadLibraryAddr = (LPVOID)GetProcAddress(moduleHandle, "LoadLibraryA");
		CloseHandle(moduleHandle);

		HANDLE threadHandle;
		threadHandle = CreateRemoteThread(processHandle, 0, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddr, memLocation, 0, 0);

		CloseHandle(processHandle);
		return true;
	}
}