#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <map>

class ProcessManager
{
public:

	ProcessManager();
	~ProcessManager() {}

	void updateProcessList();

	DWORD getProcessID(const std::string& procName);

private:

	std::map<std::string, DWORD> m_ProcessList;

};