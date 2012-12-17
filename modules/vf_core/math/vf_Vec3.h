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

#ifndef VF_VEC3_VFHEADER
#define VF_VEC3_VFHEADER

/** A 3 dimensional vector.
*/
template <class T>
struct Vec3
{
  Vec3 ()
  {
  }

  Vec3 (T x_, T y_, T z_) : x (x_), y (y_), z (z_)
  {
  }

  T getNormal () const
  {
    return sqrt (x*x + y*y + z*z);
  }

  void normalize ()
  {
    T n = getNormal ();

    if (n != 0)
    {
      n = 1 / n;
      x *= n;
      y *= n;
      z *= n;
    }
  }

  template <class U>
  Vec3& operator+ (Vec3 <U> const& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  template <class U>
  Vec3& operator- (Vec3 <U> const& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  template <class U>
  T getDotProduct (Vec3 <U> const& t) const
  {
    return x * t.x + y * t.y + z * t.z;
  }

  template <class U>
  Vec3 <T> getCrossProduct (Vec3 <U> const& t) const
  {
    return Vec3 <T> (
       y * t.z - z * t.y,
      -x * t.z + z * t.x,
       x * t.y - y * t.x);
  }

  template <class U>
  T getCosAngle (Vec3 <U> const& t) const
  {
    return getDotProduct (t) / (getNormal () * t.getNormal ());
  }

  T x;
  T y;
  T z;
};

#endif

