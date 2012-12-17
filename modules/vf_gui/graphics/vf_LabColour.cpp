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

LabColour::LabColour ()
  : m_L (0)
  , m_a (0)
  , m_b (0)
  , m_alpha (0)
{
}

LabColour::LabColour (float L, float a, float b)
  : m_L (L)
  , m_a (a)
  , m_b (b)
  , m_alpha (1)
{
}

LabColour::LabColour (float L, float a, float b, float alpha)
  : m_L (L)
  , m_a (a)
  , m_b (b)
  , m_alpha (alpha)
{
}

LabColour::LabColour (LabColour const& lab)
  : m_L (lab.m_L)
  , m_a (lab.m_a)
  , m_b (lab.m_b)
  , m_alpha (lab.m_alpha)
{
}

LabColour::LabColour (Colour const& sRGB)
{
  *this = from (sRGB);
}

LabColour::LabColour (XYZColour const& xyz)
{
  *this = from (xyz);
}

XYZColour const LabColour::toXYZ () const
{
  // D65, Observer= 2°
  float const x0 = 95.047f;
  float const y0 = 100.000f;
  float const z0 = 108.883f;

  float y = (m_L + 16) / 116;
  float x = m_a / 500 + y;
  float z = y - m_b / 200;

  float t;

  if ((t = pow (x, 3.f)) > 0.008856f) x = t; else x = (x - 16.f/116.f) / 7.787f;
  if ((t = pow (y, 3.f)) > 0.008856f) y = t; else y = (y - 16.f/116.f) / 7.787f;
  if ((t = pow (z, 3.f)) > 0.008856f) z = t; else z = (z - 16.f/116.f) / 7.787f;

  x *= x0;
  y *= y0;
  z *= z0;

  return XYZColour (x, y, z, m_alpha);
}

Colour const LabColour::toRGB () const
{
  return toXYZ ().toRGB ();
}

LabColour const LabColour::from (XYZColour const& xyz)
{
  // D65, Observer= 2°
  float const x0 = 95.047f;
  float const y0 = 100.000f;
  float const z0 = 108.883f;

  float x = (xyz.getX () / x0);
  float y = (xyz.getY () / y0);
  float z = (xyz.getZ () / z0);

  x = (x > 0.008856f) ? pow (x, 1.f/3.f) : ((7.7787f * x) + 16.f/116.f);
  y = (y > 0.008856f) ? pow (y, 1.f/3.f) : ((7.7787f * y) + 16.f/116.f);
  z = (z > 0.008856f) ? pow (z, 1.f/3.f) : ((7.7787f * z) + 16.f/116.f);

  float const L = (116 * y) - 16;
  float const a = 500 * (x - y);
  float const b = 200 * (y - z);
 
  return LabColour (L, a, b, xyz.getAlpha ());
}

LabColour const LabColour::withLuminance (float L) const
{
  return LabColour (
    jlimit (0.f, 100.f, L),
    getA (),
    getB (),
    getAlpha ());
}

LabColour const LabColour::withAddedLuminance (float amount) const
{
  return LabColour (
    jlimit (0.f, 100.f, getL() + amount * 100),
    getA (),
    getB (),
    getAlpha ());
}

LabColour const LabColour::withMultipliedColour (float amount) const
{
  return LabColour (
    getL (),
    getA () * amount,
    getB () * amount,
    getAlpha ());
}
