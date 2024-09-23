#pragma once
#include <iostream>
#include "core/types.h"
#include "core/util.h"
#include "video/IVideoDriver.h"

namespace DalatEngine {
	namespace Core
	{
		void WelcomeMessage(std::string filename) {
			u32 someNumber = 42;
			std::cout << "Hello this is " << someNumber << " from Dalat engine\n";
			std::string dest;
			std::cout << "Test function get extension" << cutFileNameExtension(dest, filename);
			std::cout << Video::init << " " << Video::clear << Video::rendering<< '\n';
		}
	};
}


