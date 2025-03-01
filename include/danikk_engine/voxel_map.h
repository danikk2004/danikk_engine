#pragma once

#include <default.h>
#include <danikk_framework/assert.h>
#include <danikk_framework/glm.h>
#include <danikk_framework/assert.h>

namespace danikk_engime
{
	template<class value_t, uvec3 m_size> class FixedVoxelMap
	{
		static constexpr size_t data_size = m_size.x * m_size.y * m_size.z;

		value_t m_data[data_size];
	public:
		index_t posToIndex(uvec3 pos)
		{
			assert(pos.x < m_size.x);
			assert(pos.y < m_size.y);
			assert(pos.x < m_size.z);

			return
			  pos.x +
			  pos.y * m_size.x +
			  pos.z * m_size.x * m_size.y;
		}

		value_t& operator[](uvec2 pos)
		{
			return m_data[posToIndex(pos)];
		}
		value_t& operator[](index_t index)
		{
			assert(index < data_size);
			return m_data[index];
		}

		uvec2 size() const
		{
			return m_size;
		}
	};
}
