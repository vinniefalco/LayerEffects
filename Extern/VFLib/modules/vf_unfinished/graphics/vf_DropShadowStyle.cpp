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
/*
Outline:

Enlarge stencil
Dilate
Blur

*/

void DropShadowStyle::operator() (Pixels destPixels, Pixels stencilPixels)
{
  if (!active)
    return;

  int const width = stencilPixels.getWidth ();
  int const height = stencilPixels.getHeight ();

  int const xOffset = - static_cast <int> (cos (angle) * distance + 0.5);
  int const yOffset = static_cast <int> (sin (angle) * distance + 0.5);

  // Calculate blur radius and dilate size from settings
  //
  LayerStyles::BoxBlurAndDilateSettings bd (size, spread);

  // Create enlarged mask
  //
  /*
  Map2D <int> temp1 (width + size * 2, height + size * 2);
  for (int y = 0; y < temp1.getRows (); ++y)
  {
    for (int x = 0; x < temp1.getCols (); ++x)
    {
    }
  }
  */


  // Dilate 8-bit unsigned mask.
  //
  Map2D <int> dist (stencilPixels.getWidth (), stencilPixels.getHeight ());

  LayerStyles::GrayscaleDilation () (
    Pixels::Map2D (stencilPixels),
    dist,
    stencilPixels.getWidth (),
    stencilPixels.getHeight (),
    bd.getDilatePixels ());

  // Blur 32-bit signed mask
  // Output is 32-bit signed with 8-bit fixed point.
  //
  Map2D <int> blur (stencilPixels.getWidth (), stencilPixels.getHeight ());

  BoxBlur () (dist, blur, blur.getCols (), blur.getRows (), bd.getBoxBlurRadius ());

  // Transform fixed point mask to 8-bit unsigned mask using contour curve
  //
  Image mask (Image::SingleChannel, width, height, false);
  Pixels maskPixels (mask);
  {
    for (int y = 0; y < height; ++y)
    {
      for (int x = 0; x < width; ++x)
      {
        int const alpha = blur (x, y);

        jassert (alpha < 65536);

        *maskPixels.getPixelPointer (x, y) = static_cast <uint8> ((alpha + 128) / 256);
      }
    }
  }

  // Calculate compositing rectangles
  //
  Rectangle <int> srcRect;
  Rectangle <int> destRect;
  {
    srcRect = mask.getBounds ();
    destRect = destPixels.getBounds ();
    destRect.translate (xOffset, yOffset);
    destRect = destPixels.getBounds ().getIntersection (destRect);

    srcRect = destRect.translated (-xOffset, -yOffset);
  }
  jassert (srcRect.getWidth () == destRect.getWidth ());
  jassert (srcRect.getHeight () == destRect.getHeight ());
  jassert (mask.getBounds ().contains (srcRect));
  jassert (destPixels.getBounds ().contains (destRect));

  PixelProcs procs;

  if (knockout)
  {
    procs.copyGray (
      srcRect.getHeight (),
      srcRect.getWidth (),
      stencilPixels.getPixelPointer (destRect.getX (), destRect.getY ()),
      stencilPixels.getRowBytes (),
      stencilPixels.getColBytes (),
      maskPixels.getPixelPointer (srcRect.getX (), srcRect.getY ()),
      maskPixels.getRowBytes (),
      maskPixels.getColBytes (),
      BlendMode::subtract ());
  }

  // Colorize destination using mask
  {
    unsigned char c [] = { 0, 0, 0 };

#if 1
    procs.fillRGB (
      srcRect.getHeight (),
      srcRect.getWidth (),
      c,
      opacity,
      maskPixels.getPixelPointer (srcRect.getX (), srcRect.getY ()),
      maskPixels.getRowBytes (),
      maskPixels.getColBytes (),
      destPixels.getPixelPointer (destRect.getX (), destRect.getY ()),
      destPixels.getRowBytes (),
      destPixels.getColBytes (),
      BlendMode::normal ());

#else
    unsigned char* dest = destPixels.getPixelPointer (destRect.getX (), destRect.getY ());

    int const colBytes = destPixels.getColBytes () - 3;
    int const rowBytes = destPixels.getRowBytes () - destRect.getWidth () * destPixels.getColBytes ();

    for (int y = 0; y < srcRect.getHeight (); ++y)
    {
      for (int x = 0; x < srcRect.getWidth (); ++x)
      {
        int alpha = *maskPixels.getPixelPointer (x + srcRect.getX (), y + srcRect.getY ());

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
#endif
  }

  /*
  BlendMode::apply (
    mode,
    Pixels::Iterate2 (destImage, matteImage),
    BlendProc::RGB::MaskFill (colour, opacity));
  */
}
