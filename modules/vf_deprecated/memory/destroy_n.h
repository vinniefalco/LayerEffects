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

