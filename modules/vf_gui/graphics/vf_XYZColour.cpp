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

XYZColour::XYZColour ()
  : m_x (0)
  , m_y (0)
  , m_z (0)
  , m_alpha (0)
{
}

XYZColour::XYZColour (float x, float y, float z)
  : m_x (x)
  , m_y (y)
  , m_z (z)
  , m_alpha (1)
{
}

XYZColour::XYZColour (float x, float y, float z, float alpha)
  : m_x (x)
  , m_y (y)
  , m_z (z)
  , m_alpha (alpha)
{
}

XYZColour::XYZColour (XYZColour const& xyz)
  : m_x (xyz.m_x)
  , m_y (xyz.m_y)
  , m_z (xyz.m_z)
  , m_alpha (xyz.m_alpha)
{
}

XYZColour::XYZColour (Colour const& sRGB)
{
  *this = from (sRGB);
}

XYZColour& XYZColour::operator= (XYZColour const& other)
{
  m_x = other.m_x;
  m_y = other.m_y;
  m_z = other.m_z;
  m_alpha = other.m_alpha;

  return *this;
}

XYZColour const XYZColour::from (Colour const& sRGB)
{
  float r = sRGB.getRed   () / 255.f;
  float g = sRGB.getGreen () / 255.f;
  float b = sRGB.getBlue  () / 255.f;

  if (r > 0.04045f) r = 100.f * pow ((r + 0.055f) / 1.055f, 2.4f); else r = r / 12.92f;
  if (g > 0.04045f) g = 100.f * pow ((g + 0.055f) / 1.055f, 2.4f); else g = g / 12.92f;
  if (b > 0.04045f) b = 100.f * pow ((b + 0.055f) / 1.055f, 2.4f); else b = b / 12.92f;

  // D65
  float x = r * 0.4124f + g * 0.3576f + b * 0.1805f;
  float y = r * 0.2126f + g * 0.7152f + b * 0.0722f;
  float z = r * 0.0193f + g * 0.1192f + b * 0.9505f;

  return XYZColour (x, y, z, sRGB.getAlpha() / 255.f);
}

Colour const XYZColour::toRGB () const
{
  float x = m_x / 100;
  float y = m_y / 100;
  float z = m_z / 100;

  float r = x *  3.2406f + y * -1.5372f + z * -0.4986f;
  float g = x * -0.9689f + y *  1.8758f + z *  0.0415f;
  float b = x *  0.0557f + y * -0.2040f + z *  1.0570f;

  if (r > 0.0031308f) r = 1.055f * pow (r, 1.f/2.4f) - 0.055f; else r = 12.92f * r;
  if (g > 0.0031308f) g = 1.055f * pow (g, 1.f/2.4f) - 0.055f; else g = 12.92f * g;
  if (b > 0.0031308f) b = 1.055f * pow (b, 1.f/2.4f) - 0.055f; else b = 12.92f * b;

  return Colour::fromFloatRGBA  (r, g, b, m_alpha);
}
