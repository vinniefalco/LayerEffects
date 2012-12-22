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

/** Common routines for Layer Styles.
*/
class LayerStyles
{
public:
  /** Calculate blur and dilate settings.
  */
  struct BoxBlurAndDilateSettings
  {
    BoxBlurAndDilateSettings (int sizeInPixels, float spread)
    {
      m_dilatePixels = int (sizeInPixels * spread + 0.5);

      int blurPixels = sizeInPixels - m_dilatePixels;

      // Photoshop fudge factor by Brian Fiete
      float const fudge = 1.85f - 0.45f * std::min (1.0f, blurPixels / 10.f);
      m_boxBlurRadius = std::max ((blurPixels - fudge) / 2.f, 0.f);
    }

    int getDilatePixels () const
    {
      return m_dilatePixels;
    }

    float getBoxBlurRadius () const
    {
      return m_boxBlurRadius;
    }

  private:
    int m_dilatePixels;
    float m_boxBlurRadius;
  };
};
