#pragma once
#include <glm/glm.hpp>

namespace DalatEngine {
	namespace Core {
		class BoundingBox
		{
		public:
			BoundingBox()
			{
			}
			BoundingBox(const BoundingBox& aabb)
			{
				m_min = aabb.m_min;
				m_max = aabb.m_max;
				m_center = aabb.m_center;
			}
			void Calculate(glm::vec3* v, int numPoints)
			{
				if (v == NULL)
					return;
				for (int i = 0; i < numPoints; i++)
				{
					if (v[i].x < m_min.x) m_min.x = v[i].x;
					if (v[i].x > m_max.x) m_max.x = v[i].x;
					if (v[i].y < m_min.y) m_min.y = v[i].y;
					if (v[i].y > m_max.y) m_max.y = v[i].y;
					if (v[i].z < m_min.z) m_min.z = v[i].z;
					if (v[i].z > m_max.z) m_max.z = v[i].z;
				}
				m_center.x = (m_min.x + m_max.x) * 0.5f;
				m_center.y = (m_min.y + m_max.y) * 0.5f;
				m_center.z = (m_min.z + m_max.z) * 0.5f;
			}
			glm::vec3 m_min, m_max, m_center;
		};
	}
}
