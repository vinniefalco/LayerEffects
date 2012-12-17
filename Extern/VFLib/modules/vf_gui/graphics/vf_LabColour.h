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
