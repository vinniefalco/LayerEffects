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

float DistanceTransform::calcDistancePixel (Pixels mask, int x, int y, int radius)
{
  float dist = float ((radius + 1) * (radius + 1));

  int const x0 = jmax (x - radius, 0);
  int const x1 = jmin (x + radius, mask.getCols ());
  int const y0 = jmax (y - radius, 0);
  int const y1 = jmin (y + radius, mask.getRows ());

  if (*mask.getPixelPointer (x, y) > 127)
  {
    for (int py = y0; py < y1; ++py)
    {
      float const dy = float (y-py);
      float const dys = dy * dy;

      for (int px = x0; px < x1; ++px)
      {
        uint8 const m = *mask.getPixelPointer (px, py);

        if (m < 127)
        {
          float const dx = float (x-px);
          float d = dx * dx + dys;
          if (d < dist)
            dist = d;
        }
      }
    }

    dist = sqrt (dist) / float (radius + 1);

    if (dist > 1)
      dist = 1;
  }
  else
  {
    dist = 1;
  }

  return dist;
}

//------------------------------------------------------------------------------

Image DistanceTransform::calculate (Pixels mask, int radius)
{
  Image destImage (
    Image::SingleChannel,
    mask.getWidth (),
    mask.getHeight (),
    true);

  Pixels dest (destImage, destImage.getBounds ());

  for (int y = 0; y < dest.getRows (); ++y)
  {
    for (int x = 0; x < dest.getCols (); ++x)
    {
      float df = calcDistancePixel (mask, x, y, radius);
      uint8 dist = static_cast <uint8> (255 * (1 - df) + 0.5);

      *dest.getPixelPointer (x, y) = dist;
    }
  }

  return destImage;
}

//------------------------------------------------------------------------------
