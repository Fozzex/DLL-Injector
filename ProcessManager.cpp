#include "ProcessManager.h"

ProcessManager::ProcessManager()
{
	this->updateProcessList();
}

void ProcessManager::updateProcessList()
{
	HANDLE snapshotHandle;
	PROCESSENTRY32 processEntry;

	// Returns INVALID_HANDLE_VALUE when failed
	snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	
	if (snapshotHandle != INVALID_HANDLE_VALUE)
	{
		// Setting the size of the structure is necessary for some reason
		processEntry.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(snapshotHandle, &processEntry))
		{
			m_ProcessList.insert({ processEntry.szExeFile, processEntry.th32ProcessID });
			
			// Iterate through processes
			while (Process32Next(snapshotHandle, &processEntry))
			{
				m_ProcessList.insert({ processEntry.szExeFile, processEntry.th32ProcessID });
			}
		}
	}
}

DWORD ProcessManager::getProcessID(const std::string& processName)
{
	if (!m_ProcessList.empty())
	{
		try
		{
			return m_ProcessList.at(processName);
		}
		catch (std::out_of_range e)
		{
			return 0x0;
		}
	}

	return 0x0;
}