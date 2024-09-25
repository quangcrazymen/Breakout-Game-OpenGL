#pragma once
#include "CCommonGLDriverBase.h";
#include <memory>

namespace DalatEngine {
	namespace Video {
		//class CCommonGLDriver;
		//typedef std::shared_ptr<CCommonGLDriver> CCommonGLDriverPtr;

		class CCommonGLDriver : public CCommonGLDriverBase {
		public:
			// Temp constructor
			CCommonGLDriver() {

			};
			/*virtual*/ void flushImpl() {};
			/*virtual*/ void drawImpl() {
				glDrawArrays(GL_TRIANGLES, 0, 6);

			}
			static std::shared_ptr<CCommonGLDriver> createDriver() {
				 return std::make_shared<CCommonGLDriver>();
			}
		private:
		};
	}
}
