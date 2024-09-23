#pragma once

// Include some config here

#include <cstdint>
namespace DalatEngine {
	typedef unsigned char	u8;         //! 8 bit unsigned variable.
	typedef signed char		s8;         //! 8 bit signed variable.
	typedef char			c8;         //! 8 bit character variable.

	typedef unsigned short	u16;        //! 16 bit unsigned variable.
	typedef signed short	s16;        //! 16 bit signed variable.

	typedef unsigned int	u32;        //! 32 bit unsigned variable.
	typedef signed int		s32;        //! 32 bit signed variable.
	typedef float			f32;        //! 32 bit floating point variable.

	typedef uint64_t        u64;        //! 64 bit unsigned variable
	typedef int64_t         s64;        //! 64 bit signed variable.
	typedef double			f64;        //! 64 bit floating point variable.

	enum E_TYPE
	{
		E_U8,
		E_C8 = E_U8,
		E_S8,

		E_U16,
		E_S16,

		E_U32,
		E_S32,
		E_F32,

		E_U64,
		E_S64,
		E_F64
	};

	inline s32 getSizeOf(E_TYPE type) {
		switch (type)
		{
		case E_U8: return sizeof(u8);
			//case E_C8: return sizeof(c8);
		case E_S8: return sizeof(s8);
		case E_U16: return sizeof(u16);
		case E_S16: return sizeof(u16);
		case E_U32: return sizeof(u32);
		case E_S32: return sizeof(s32);
		case E_F32: return sizeof(f32);
		case E_U64: return sizeof(u64);
		case E_S64: return sizeof(s64);
		case E_F64: return sizeof(f64);
		default: break;
		}
		return 0;
	}
}


