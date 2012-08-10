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

struct RenderStroke
{
  RenderStroke (Pixels::Map2D dest, Colour colour, int radius)
    : m_dest (dest)
    , m_src (colour.getPixelARGB ())
    , m_radius (radius)
    , m_radiusSquared (radius * radius)
    , m_radiusMinusOneSquared ((radius - 1) * (radius - 1))
  {
  }

  void operator() (int x, int y, double distance)
  {
    PixelRGB& dest = *((PixelRGB *)&m_dest (x, y));

    if (distance > 0)
    {
      if (distance <= m_radiusMinusOneSquared)
      {
        dest.blend (m_src);
      }
      else if (distance < m_radiusSquared)
      {
        distance = sqrt (distance) - (m_radius - 1);
        uint8 const alpha = 255 - uint8 (255 * distance + 0.5);

        dest.blend (m_src, alpha);
      }
    }
  }

private:
  Pixels::Map2D m_dest;
  PixelARGB m_src;
  int m_radius;
  int m_radiusSquared;
  int m_radiusMinusOneSquared;
};

void StrokeStyle::render (
  Pixels destPixels, Pixels maskPixels, Options const& options)
{
  DistanceTransform::WangTan::calculate (
    RenderStroke (Pixels::Map2D (destPixels), options.colour, options.size),
    DistanceTransform::AlphaTest (maskPixels),
    maskPixels.getWidth (),
    maskPixels.getHeight (),
    DistanceTransform::Meijster::EuclideanMetric ());
}
