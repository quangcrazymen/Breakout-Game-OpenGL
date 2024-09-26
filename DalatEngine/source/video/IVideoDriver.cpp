#include "video/IVideoDriver.h"
#include <glad/glad.h>

namespace DalatEngine {
	namespace Video {
		void IVideoDriver::clearBuffers(int clearMask) {

		}

		//void IVideoDriver::flush() {
		//	flushImpl();
		//}
		void IVideoDriver::draw3DTriangle(const Core::triangle3d& triangle) {
			u32 VBO, VAO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			//glBufferData(GL_ARRAY_BUFFER,sizeof())

		}
	}
}
