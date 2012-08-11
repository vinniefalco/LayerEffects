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

#ifndef VF_LIGHTINGTRANSFORM_VFHEADER
#define VF_LIGHTINGTRANSFORM_VFHEADER

/** Directional lighting transform.

    Calculates the incident highlights and shadows for each
    point in a discrete height map.
*/
struct LightingTransform
{
  /** Calculate the transform.

      @param shader     A functor called to shade each point.
      @param map        The height map.
      @param depth      Depth of the light source range [0, 10].
      @param angle      Light source angle, in radians.
      @param elevation  Light source elevation, in radians.

      @tparam T The underlying type to use for calculation (float or double)
  */
  template <class T, class Shader, class Map, class R1, class R2, class R3>
  static void calculate (
    Shader shader,
    Map map,
    R1 depth,
    R2 angle,
    R3 elevation)
  {
    Vec3 <T> lightNormal (
       cos (elevation) * cos (angle),
      -cos (elevation) * sin (angle),
       sin (elevation));

    for (int y = 1; y < map.getRows () - 1; ++y)
    {
      for (int x = 1; x < map.getCols () - 1; ++x)
      {
        // Calculate normal from height map.
#if 1
        Vec3 <T> n (
          T(map(x,y)) - .25*(2 * T(map(x+1,y)) + T(map(x+1,y-1)) + T(map(x+1,y+1))),
          T(map(x,y)) - .25*(2 * T(map(x,y+1)) + T(map(x-1,y+1)) + T(map(x+1,y+1))),
          T(depth));
#else
        Vec3 <T> n (T (map (x+1,y) - map (x-1,y)),
                    T (map (x,y+1) - map (x,y-1)),
                    T (depth));
#endif

        // Calculate incident light amount, range [-1, 1]
        T incidentLight = n.getDotProduct (lightNormal) / n.getNormal ();

        shader (x, y, incidentLight);
      }
    }
  }

  /** Shader for highlight and shadows Pixels map.
  */
  struct PixelShader
  {
    PixelShader (Pixels hi, Pixels lo) : m_hi (hi), m_lo (lo)
    {
    }

    template <class T>
    inline void operator() (int x, int y, T incidentLight)
    {
      if (incidentLight >= 0)
        m_hi (x, y) = uint8 (255 * incidentLight + T(.5));
      else
        m_lo (x, y) = uint8 (-255 * incidentLight + T(.5));
    }

  private:
    Pixels::Map2D m_hi;
    Pixels::Map2D m_lo;
  };
};

#endif
