#pragma once
#include <glm/glm.hpp>

namespace DalatEngine {
	namespace Core {
		enum PLANE_STATUS {
			PLANE_FRONT,
			PLANE_BACK,
			PLANE_ON_PLANE
		};
		//typedef std::basic_string<char, std::char_traits<char>, 
		class Plane {
		public:
			Plane() : a(0), b(0), c(0), d(0) { }
			Plane(float A, float B, float C, float D) :
				a(A), b(B), c(C), d(D) { }
			void Create(glm::vec3& t1, glm::vec3& t2, glm::vec3& t3)
			{
				glm::vec3 e1, e2, n;
				e1 = t2 - t1;
				e2 = t3 - t1;
				n = glm::cross(e1,e2);
				n = glm::normalize(n);
				a = n.x; b = n.y; c = n.z;
				d = -(a * t1.x + b * t1.y + c * t1.z);
			}

			bool Intersect(const glm::vec3& bbMin, const glm::vec3& bbMax) {
				glm::vec3 min, max;
				glm::vec3 normal(a, b, c);
				if (normal.x >= 0.0f)
				{
					min.x = bbMin.x; max.x = bbMax.x;
				}
				else
				{
					min.x = bbMax.x; max.x = bbMin.x;
				}
				if (normal.y >= 0.0f)
				{
					min.y = bbMin.y; max.y = bbMax.y;
				}
				else
				{
					min.y = bbMax.y; max.y = bbMin.y;
				}
				if (normal.z >= 0.0f)
				{
					min.z = bbMin.z; max.z = bbMax.z;
				}
				else
				{
					min.z = bbMax.z; max.z = bbMin.z;
				}
				if (glm::dot(normal,min) + d > 0.0f)
					return false;
				if (glm::dot(normal,max) + d >= 0.0f)
					return true;
				return false;
			}

			PLANE_STATUS ClassifyPoint(float x, float y, float z, float* dist) {
				float distance = a * x + b * y + c * z + d;
				if (dist != 0)
					*dist = distance;
				if (distance > 0.001)
					return PLANE_FRONT;
				if(distance < -0.001)
					return PLANE_BACK;
				return PLANE_ON_PLANE;

			}

			bool Intersect(const glm::vec3& position, float radius) {
				//float dp = fabs()
			}

			inline float GetDistance(float x, float y, float z)
			{
				return a * x + b * y + c * z + d;
			}

			float a, b, c, d;
		};

	}
}
