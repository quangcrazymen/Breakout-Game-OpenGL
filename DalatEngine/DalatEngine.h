#pragma once
#include <iostream>
// this folder also has to be included in the project that use it
#include "core/types.h"
#include "core/util.h"
#include <string>

namespace DalatEngine {
	namespace Core
	{
		void WelcomeMessage(std::string filename) {
			u32 someNumber = 42;
			std::cout << "Hello this is "<<someNumber<<" from Dalat engine\n";
			std::string dest;
			std::cout << "Test function get extension" << cutFileNameExtension(dest,filename);
		}
	};
}


