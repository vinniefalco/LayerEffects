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

/** Include this to get the @ref vf_lua external module.

    @file vf_lua.h
    @ingroup vf_lua external
*/

#ifndef VF_LUA_VFHEADER
#define VF_LUA_VFHEADER

/*============================================================================*/
/**
    A powerful, fast, lightweight, embeddable scripting language.

    This external module provides the Lua external library.

    Lua is licensed separately, please visit
    http://www.lua.org/

    @defgroup vf_lua vf_lua
    @ingroup external
*/

#ifndef NDEBUG
#ifndef LUA_USE_APICHECK
#define LUA_USE_APICHECK
#endif
#endif

#include "lua/lua.hpp"

#endif
