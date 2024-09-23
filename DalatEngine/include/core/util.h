#pragma once
#include <string>
#include <core/types.h>

namespace DalatEngine {
	namespace Core {
		inline std::string& cutFileNameExtension(std::string &dest, std::string& source) {
			s32 endPos = (s32)source.rfind(".");
			dest = source.substr(0, endPos < 0 ? s32(source.size()) : endPos);
			return dest;
		}
	}
}
