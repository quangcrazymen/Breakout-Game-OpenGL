#pragma once
#include <memory>

namespace DalatEngine {
	namespace Video {
		class IVideoDriver;
		typedef std::shared_ptr<IVideoDriver> IVideoDriverPtr;
		typedef std::shared_ptr<const IVideoDriver> IVideoDriverConstPtr;
	}
}
