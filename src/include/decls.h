// Every source file includes this: the shared types, functions and globals.
#pragma once

namespace std
{
	template<class> struct char_traits;
	template<class> class allocator;
	template<class, class, class> class basic_string;
	typedef basic_string<char, char_traits<char>, allocator<char> > string;
	typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > wstring;
	template<class, class> class vector;
}
#include "shinobi.h"
#include "ninja.h"
#include "types.h"

// PLACEHOLDER: MAYBE_ASSERT: likely an assert, since the file includes the porting SDK's assert header; it makes no code but still counts toward the compiler's inline budget, and debug prints stay real calls.
#define MAYBE_ASSERT() ((void)0)

// PLACEHOLDER: UNKNOWN_NO_CODE: the original tests a condition here and then runs no code, so its body is unknown.
#define UNKNOWN_NO_CODE() ((void)0)

// PLACEHOLDER: UNKNOWN_MACRO: likely a macro, since the code is a do-while (0) block that fills an NJS_ARGB and passes it to ___njSetConstantMaterial.
#define UNKNOWN_MACRO(param_1, param_2, param_3, param_4) \
	do \
	{ \
		NJS_ARGB local_30; \
		local_30.a = (param_1); \
		local_30.r = (param_2); \
		local_30.g = (param_3); \
		local_30.b = (param_4); \
		___njSetConstantMaterial(&local_30); \
	} while (0)

// PLACEHOLDER: UNKNOWN_ZUPDATE_MACRO: likely a macro, since the code is a do-while (0) block of these two calls.
#define UNKNOWN_ZUPDATE_MACRO(param_1, param_2) \
	do \
	{ \
		FUN_00422560(param_1); \
		njSetZUpdateMode(param_2); \
	} while (0)

// PLACEHOLDER: UNKNOWN_ONESHOT_MACRO: likely a macro, since the code is a do-while (0) block that plays sound 0x51a when the player number is 6.
#define UNKNOWN_ONESHOT_MACRO() \
	do \
	{ \
		if (GetPlayerNumber() == 6) \
		{ \
			dsPlay_oneshot(0x51a, 0, 0, 0); \
		} \
	} while (0)

// PLACEHOLDER: UNKNOWN_ROTATE_X_MACRO: likely a macro, since the code tests the angle against 0 before it calls njRotateX, also when the angle is a constant.
#define UNKNOWN_ROTATE_X_MACRO(param_1, param_2) if ((param_2) != 0) njRotateX((param_1), (unsigned short)(param_2))

// PLACEHOLDER: UNKNOWN_ROTATE_Y_MACRO: likely a macro, since the code tests the angle against 0 before it calls njRotateY, also when the angle is a constant.
#define UNKNOWN_ROTATE_Y_MACRO(param_1, param_2) if ((param_2) != 0) njRotateY((param_1), (unsigned short)(param_2))

// PLACEHOLDER: UNKNOWN_DOUBLE_MACRO: the bytes do this math in double precision; the source form of the conversion is unknown.
#define UNKNOWN_DOUBLE_MACRO(param_1) (double)(param_1)

namespace Magic { namespace RenderCore { class Texture; class VertexBuffer; class Material; } }
#include "functions.h"
#include "globals.h"
