/*============================================================================*/
/*
  Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
  See the file GNU_GPL_v2.txt for full licensing terms.

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the Free
  Software Foundation; either version 2 of the License, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
  details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc., 51
  Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
/*============================================================================*/

/** Include this to get the @ref vf_luabridge external module.

    @file vf_luabridge.h
    @ingroup vf_luabridge external
*/

#ifndef VF_LUABRIDGE_VFHEADER
#define VF_LUABRIDGE_VFHEADER

/*============================================================================*/
/**
    A lightweight, dependency-free library for binding Lua to C++.

    This external module provides the LuaBridge external library.

    This module depends on the @ref vf_lua external module.

    LuaBridge is licensed separately, please visit
    https://github.com/vinniefalco/LuaBridge

    @see vf_lua

    @defgroup vf_luabridge vf_luabridge
    @ingroup external
*/

#include "../vf_lua/vf_lua.h"

#include "LuaBridge/LuaBridge.h"

#endif
