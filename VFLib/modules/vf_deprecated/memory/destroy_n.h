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

#ifndef VF_DESTROY_N_H
#define VF_DESTROY_N_H

#if 0

#ifdef _MSC_VER
namespace tr1 = std::tr1;
#else
namespace tr1 = std;
#endif

namespace detail {

template<class Ty, bool hasTrivialDestructor>
struct destroyer
{
  static inline void destroy (Ty* p, std::size_t n)
  {
    while (n--)
      (*p++).~Ty();
  }
};

template<class Ty>
struct destroyer<Ty, true>
{
  static inline void destroy (Ty* p, std::size_t n)
  {
    // do nothing
  }
};

}

/** @internal

    @brief Destroy an array of objects, only if the destructor is non trivial

    @deprecated
*/

template<class Ty>
void destroy_n( Ty* p, std::size_t n )
{
  detail::destroyer<Ty, tr1::has_trivial_destructor<Ty>::value>::destroy (p, n);
}

#endif

#endif

