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

#ifndef VF_MATH_VFHEADER
#define VF_MATH_VFHEADER

//
// Miscellaneous mathematical calculations
//

// Calculate the bin for a value given the bin size.
// This correctly handles negative numbers. For example
// if value == -1 then calc_bin returns -1.
template <typename Ty>
inline Ty calc_bin (Ty value, int size)
{
  if (value >= 0)
    return value / size;
  else
    return (value - size + 1) / size;
}

// Given a number and a bin size, this returns the first
// corresponding value of the bin associated with the given number.
// It correctly handles negative numbers. For example,
// if value == -1 then calc_bin always returns -size
template <typename Ty>
inline Ty calc_bin_start (Ty value, int size)
{
  return calc_bin (value, size) * size;
}

#endif
