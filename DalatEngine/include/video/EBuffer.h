#pragma once

namespace DalatEngine
{
	namespace Video
	{
		//! Type of buffer.
		enum E_BUFFER_TYPE
		{
			//! Buffer used to store vertex data.
			EBT_VERTEX,

			//! Buffer used to store index data.
			EBT_INDEX,

			//! Buffer used to store pixel data written by GPU, read back by CPU.
			EBT_PIXEL_PACK,

			//! Buffer used to store pixel data written by CPU, read back by GPU.
			EBT_PIXEL_UNPACK,

			//! Buffer used to store raw content of a texture.
			EBT_TEXTURE_REFERENCE,

			EBT_COUNT,
			EBT_UNKNOWN = u8(-1)
		};
	}
}
