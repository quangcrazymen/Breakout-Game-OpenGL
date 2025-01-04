#pragma once
#include <glm/glm.hpp>

namespace DalatEngine {
	namespace Core {
		class Frustum {
			public:
				Frustum() {

				}

				void CalculateFrustum(float angle, float ratio, float near
					, float far, glm::vec3& camPos, glm::vec3& lookAt,
					glm::vec3& up) {

				}
		};
	}
}
