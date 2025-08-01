// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include <tga2d/drawers/debug_drawer.h>
#include <tga2d/error/error_manager.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#define PARAMPACKCOUNT(...) \
	std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value;

// TODO: reference additional headers your program requires here
