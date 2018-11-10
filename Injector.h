#pragma once
#include <Windows.h>
#include <vector>
#include <string>

namespace DLL
{
	class Injector
	{
	public:

		Injector()  {}
		~Injector() {}

		bool inject(const std::string& dllPath, DWORD processID);

	};
}