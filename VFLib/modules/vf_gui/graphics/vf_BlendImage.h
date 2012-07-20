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

#ifndef VF_BLENDIMAGE_VFHEADER
#define VF_BLENDIMAGE_VFHEADER

enum BlendMode
{
  normal = 1,
  lighten,
  darken,
  multiply,
  average,
  add,
  subtract,
  difference,
  negation,
  screen,
  exclusion,
  overlay,
  softLight,
  hardLight,
  colorDodge,
  colorBurn,
  linearDodge,
  linearBurn,
  linearLight,
  vividLight,
  pinLight,
  hardMix,
  reflect,
  glow,
  phoenix,
};

/** Fill an image with colour.
*/
extern void fillImage (Image dest,
                       Point <int> destTopLeft,
                       Image mask,
                       Rectangle <int> maskBounds,
                       BlendMode mode,
                       double opacity,
                       Colour colour);

extern void copyImage (Image dest,
                       Point <int> destTopLeft,
                       Image source,
                       Rectangle <int> sourceBounds,
                       BlendMode mode,
                       double opacity);
#endif
