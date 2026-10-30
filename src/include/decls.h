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
namespace Magic { namespace RenderCore { class Texture; class VertexBuffer; class Material; } }
#include "functions.h"
#include "globals.h"
