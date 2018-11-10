#include <string>
#include <iostream>
#include <sstream>

#include "Injector.h"
#include "ProcessManager.h"

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		std::string dllPath = argv[1];
		ProcessManager manager;
		DLL::Injector injector;
		
		std::string processName = "";
		DWORD processID;

		do
		{
			std::cout << "Process Name: ";
			std::getline(std::cin, processName);

		} while ((processID = manager.getProcessID(processName)) == 0x0);

		if (!injector.inject(dllPath, processID))
			std::cout << "Failed to inject" << std::endl;
		else
			std::cout << "Successfully injected dll into: " << processName << std::endl;

		std::cin.get();
	}
}