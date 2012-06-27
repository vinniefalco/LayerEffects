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
