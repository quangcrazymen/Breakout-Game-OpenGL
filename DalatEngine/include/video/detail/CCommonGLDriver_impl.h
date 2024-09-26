#pragma once

#include "video/CCommonGLDriver.h"
// Load headers in here if cross platform, load glad and glfw for now
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "video/EDriverTypes.h" ;

namespace DalatEngine {
	namespace Video {
		// anonymous namespace to define some enum

		// class CCommonGLDriver<Tag>::CBuffer
		//template <E_DRIVER_TYPE Tag>
		//void CCommonGLDriver<Tag>::drawImpl() {
		//	//glDrawArrays(GL_TRIANGLES, 0, 6);
		//}

		//void CCommonGLDriver::flushImpl() {
		//	glFlush();
		//}

		namespace {
			struct SBasicDraw {
				
			};
		}

	}
}
