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

void DropShadowStyle::operator() (Pixels destPixels, Pixels maskPixels)
{
  if (!active)
    return;

  int const width = maskPixels.getWidth ();
  int const height = maskPixels.getHeight ();


  // Calculate blur radius and dilate size from settings
  //
  LayerStyles::BoxBlurAndDilateSettings bd (size, spread);

  // Dilate 8-bit unsigned mask.
  // Output is 32-bit signed mask.
  //
  Map2D <int> dist (maskPixels.getWidth (), maskPixels.getHeight ());

  LayerStyles::GrayscaleDilation () (
    Pixels::Map2D (maskPixels),
    dist,
    maskPixels.getWidth (),
    maskPixels.getHeight (),
    bd.getDilatePixels ());

  // Blur 32-bit signed mask
  // Output is 32-bit signed with 8-bit fixed point.
  //
  Map2D <int> blur (maskPixels.getWidth (), maskPixels.getHeight ());

  BoxBlur () (dist, blur, blur.getCols (), blur.getRows (), bd.getBoxBlurRadius ());

  /*
  if (knockout)
    copyImage (
      shadow,
      Point <int> (0, 0),
      mask,
      mask.getBounds (),
      BlendMode::modeSubtract,
      1);
  */

  // Transform fixed point mask to 8-bit unsigned mask using contour curve
  //
  Image mask (Image::SingleChannel, width, height, false);
  {
    Pixels p (mask);
    for (int y = 0; y < height; ++y)
    {
      for (int x = 0; x < width; ++x)
      {
        int const alpha = blur (x, y);

        jassert (alpha < 65536);

        *p.getPixelPointer (x, y) = static_cast <uint8> ((alpha + 128) / 256);
      }
    }
  }

  // Colorize destination using mask
  {
    Pixels p (mask);

    unsigned char c [] = { 255, 128, 64 };
    unsigned char* dest = destPixels.getLinePointer (0);

    int const colBytes = destPixels.getColBytes () - 3;
    int const rowBytes = destPixels.getRowBytes () - destPixels.getCols () * destPixels.getColBytes ();

    for (int y = 0; y < height; ++y)
    {
      for (int x = 0; x < width; ++x)
      {
        int alpha = *p.getPixelPointer (x, y);

        // v = v0 + t * (v1 - v0)
        *dest = *dest + (alpha * (c [0] - *dest) + 128) / 255;
        ++dest;
        *dest = *dest + (alpha * (c [1] - *dest) + 128) / 255;
        ++dest;
        *dest = *dest + (alpha * (c [2] - *dest) + 128) / 255;
        ++dest;
        dest+=colBytes;
      }
      dest+=rowBytes;
    }
  }

  /*
  BlendMode::apply (
    mode,
    Pixels::Iterate2 (destImage, matteImage),
    BlendProc::RGB::MaskFill (colour, opacity));
  */
}
