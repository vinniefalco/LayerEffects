/*============================================================================*/
/*
  VFLib: https://github.com/vinniefalco/VFLib

  Copyright (C) 2008 by Vinnie Falco <vinnie.falco@gmail.com>

  This library contains portions of other open source products covered by
  separate licenses. Please see the corresponding source files for specific
  terms.
  
  VFLib is provided under the terms of The MIT License (MIT):

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
*/
/*============================================================================*/

/** Add this to get the @ref vf_lua external module.

    @file vf_lua.cpp
    @ingroup vf_lua external
*/

#include "AppConfig.h"

#include "modules/juce_core/system/juce_TargetPlatform.h"

#ifndef NDEBUG
#ifndef LUA_USE_APICHECK
#define LUA_USE_APICHECK
#endif
#endif

#if JUCE_MSVC
#pragma push_macro("_CRT_SECURE_NO_WARNINGS")
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/* luaconf.h only declares some things if it is being included
   from certain source files. We define all the relevant macros
   and include luaconf.h once so we get all the declarations.
*/
#define lobject_c
#define lvm_c
#define LUA_CORE
#define LUA_LIB
#include "lua/luaconf.h"
#undef lobject_c
#undef lvm_c
#undef LUA_CORE
#undef LUA_LIB

#if JUCE_MSVC
#pragma warning (push)
#pragma warning (disable: 4244) /* Possible loss of data */
#pragma warning (disable: 4702) /* Unreachable code */
#endif

/* Include this early to prevent the conflict with luai_hashnum
   and supress the warning caused by #define lua_assert
*/
#include "lua/ltable.c"

#include "lua/lauxlib.c"
#include "lua/lbaselib.c"

#include "lua/lbitlib.c"
#include "lua/lcorolib.c"
#include "lua/ldblib.c"
#include "lua/linit.c"
#include "lua/liolib.c"
#include "lua/lmathlib.c"
#include "lua/loslib.c"
#include "lua/lstrlib.c"
#include "lua/ltablib.c"

#include "lua/lapi.c"
#include "lua/lcode.c"
#include "lua/lctype.c"
#include "lua/ldebug.c"
#include "lua/ldo.c"
#include "lua/ldump.c"
#include "lua/lfunc.c"
#include "lua/lgc.c"
#include "lua/llex.c"
#include "lua/lmem.c"
#include "lua/lobject.c"
#include "lua/lopcodes.c"
#include "lua/lparser.c"
#include "lua/lstate.c"
#include "lua/lstring.c"
#include "lua/ltm.c"
#include "lua/lundump.c"
#include "lua/lvm.c"
#include "lua/lzio.c"

/* loadlib.c includes Windows.h, which defines the LoadString macro,
   so include it last to prevent errors.
*/
#include "lua/loadlib.c"

#if JUCE_MSVC
#pragma warning (pop)
#endif

#ifdef __cplusplus
}
#endif

#if JUCE_MSVC
#pragma pop_macro("_CRT_SECURE_NO_WARNINGS")
#endif
