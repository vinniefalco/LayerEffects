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

#ifndef VF_XYZCOLOUR_VFHEADER
#define VF_XYZCOLOUR_VFHEADER

/*============================================================================*/
/**
    A colour specified in the CIE XYZ colour space.

    See http://en.wikipedia.org/wiki/CIE_1931_color_space

    @ingroup vf_gui
*/
class XYZColour
{
public:
  XYZColour ();
  XYZColour (float x, float y, float z);
  XYZColour (float x, float y, float z, float alpha);
  XYZColour (XYZColour const& xyz);
  XYZColour (Colour const& sRGB);

  XYZColour& operator= (XYZColour const& other);

  float getX () const { return m_x; }
  float getY () const { return m_y; }
  float getZ () const { return m_z; }
  float getAlpha () const { return m_alpha; }

  Colour const toRGB () const;

private:
  static XYZColour const from (Colour const& sRGB);

private:
  float m_x;
  float m_y;
  float m_z;
  float m_alpha;
};

#endif
