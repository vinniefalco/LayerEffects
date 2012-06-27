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

#ifndef VF_LABCOLOUR_VFHEADER
#define VF_LABCOLOUR_VFHEADER

#include "vf_XYZColour.h"

/*============================================================================*/
/**
    A colour specified in CIELAB coordinates.

    The Lab colour space is perceptually uniform, and device-independent.
    Incrementing the L, a, or b component by the same amount will produce
    the same perceptual change regardless of the starting colour.

    This can be very handy for doing visual effects. For example, hiliting
    a button on a mouseOver. By using the function withAddedLuminance(),
    you can increase or decrease the brightness of a colour by a fixed
    perceptual amount. This works correctly even if the starting colour
    was very dark or very bright (as long as it doesn't go out of range).

    A LabColour uses floats for the colour components, with L in the range [0,1]
    and a and b in the range [-1, 1].

    @code

    // Returns a Colour which is a bit brighter than the starting colour.

    Colour calculateHiliteColour (Colour const& startingColour)
    {
      return LabColour (startingColour).withAddedLuminance (0.1f).toRGB ();
    }

    @endcode

    @see http://en.wikipedia.org/wiki/Lab_color_space

    @ingroup vf_gui
*/
class LabColour
{
public:
  LabColour ();
  LabColour (float L, float a, float b);
  LabColour (float L, float a, float b, float alpha);
  LabColour (LabColour const& lab);
  explicit LabColour (Colour const& sRGB);
  explicit LabColour (XYZColour const& xyz);

  float getL () const { return m_L; }
  float getA () const { return m_a; }
  float getB () const { return m_b; }
  float getAlpha () const { return m_alpha; }

  XYZColour const toXYZ () const;
  Colour const toRGB () const;

  LabColour const withLuminance (float L) const; // L [0,1]
  LabColour const withAddedLuminance (float amount) const; // amount [0,1]
  LabColour const withMultipliedColour (float amount) const;

private:
  static LabColour const from (XYZColour const& xyz);

private:
  float m_L;
  float m_a;
  float m_b;
  float m_alpha;
};

#endif
