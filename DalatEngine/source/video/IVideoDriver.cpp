#include "video/IVideoDriver.h"
#include <glad/glad.h>

namespace DalatEngine {
	namespace Video {
		void IVideoDriver::clearBuffers(int clearMask) {

		}

		//void IVideoDriver::flush() {
		//	flushImpl();
		//}

		f32* getVerticesStream(f32 *vertices, const Core::triangle3d& triangle) {
			vertices[0] = triangle.PointA[0];
			vertices[1] = triangle.PointA[1];
			vertices[2] = triangle.PointA[2];
			vertices[3] = triangle.PointB[0];
			vertices[4] = triangle.PointB[1];
			vertices[5] = triangle.PointB[2];
			vertices[6] = triangle.PointC[0];
			vertices[7] = triangle.PointC[1];
			vertices[8] = triangle.PointC[2];
			return vertices;
		}

		void IVideoDriver::draw3DTriangle(Core::triangle3d& triangle) {
			f32 vertices[9];
			getVerticesStream(vertices, triangle);
			u32 VBO, VAO;
			glGenVertexArrays(1, &VAO);
			triangle.setVAO(VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
			
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
			// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
			glBindVertexArray(0);

		}
	}
}
