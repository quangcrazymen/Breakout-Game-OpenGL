#pragma once

#include <core/types.h>
#include <glm/glm.hpp>
// ProcesBufferHeap ?
namespace DalatEngine {
	namespace Core {
		//template <typename T>
		class triangle3d {
		public:
			//template <typename T>
			triangle3d();

			//template <typename T>
			triangle3d(const glm::vec3& v1,
				const glm::vec3& v2,
				const glm::vec3& v3);
			//T dotProduct(const glm::vec3<T>)

			glm::vec3 PointA;
			glm::vec3 PointB;
			glm::vec3 PointC;
		};

		//! Typedef for a f32 3d triangle.
		//typedef triangle3d<f32> triangle3df;

		//! Typedef for an integer 3d triangle.
		//typedef triangle3d<s32> triangle3di;

		inline triangle3d::triangle3d() {

		}

		inline triangle3d::triangle3d(const glm::vec3& v1,
				const glm::vec3& v2,
				const glm::vec3& v3) 
			: PointA(v1)
			, PointB(v2)
			, PointC(v3) 	
		{
		}
	}
}
