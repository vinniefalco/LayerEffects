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

Experimental notes:

- The outer border of the glow has a fade, in addition to the alpha of the
  interpolated gradient colour.

- For Precise, the fade starts at radius = 76% of the size, rounded up.

- Range, Contour, and Jitter do not affect alpha of the fade (Softer and Precise)

- Spread affects fade. Increasing spread reduces the amount of fade for Softer and Precise.

- There is no fade at 100% spread

- Contour accepts "Adjusted Distance" as x and outputs position in gradient as Y

- Previewing Range changes is very fast for "Softer" at 0% spread.

- Fade extends 1 pixel past "size". 99% Spread at 250px yields fade at 251 distance

- Range has no effect when the gradient is a single solid colour at both ends.

- Varying the Size when Spread = 0% is very fast. It gets slower as spread tends
  towards 100%.

Data

Technique   Size    Spread    Fade (px)   (1-Spread)*Size   Fade%
-----------------------------------------------------------------
Precise     250     0         60          250               24%
Precise     250     25        44          188               23%
Precise     250     50        30          125               24%
Precise     250     75        14          63                22%
Precise     250     100       0           0
Precise     100     0         24          100               24%
Precise     100     25        18          75                24%
Precise     100     50        12          50                24%
Precise     100     75        6           25                24%
Precise     100     100       0           0

Softer      250


*/

//------------------------------------------------------------------------------

void OuterGlowStyle::operator() (Pixels destPixels, Pixels stencilPixels)
{
  if (!active)
    return;

  //int const width = stencilPixels.getWidth ();
  //int const height = stencilPixels.getHeight ();

  SharedTable <Colour> table = colours.createLookupTable ();

  Map2D <int> dist (stencilPixels.getWidth (), stencilPixels.getHeight ());
  Map2D <int> temp (stencilPixels.getWidth (), stencilPixels.getHeight ());

  if (precise)
  {
    LayerStyles::DistanceMap () (
      Pixels::Map2D (stencilPixels),
      temp,
      stencilPixels.getWidth (),
      stencilPixels.getHeight (),
      size);

  #if 0
    DistanceTransform::Meijster::calculateAntiAliased (
      RenderPixelAntiAliased (
        destPixels,
        opacity,
        spread,
        size,
        table),
      GetMask (stencilPixels),
      stencilPixels.getWidth (),
      stencilPixels.getHeight (),
      DistanceTransform::Meijster::EuclideanMetric ());
  #endif
    for (int y = 0; y < temp.getRows (); ++y)
    {
      for (int x = 0; x < temp.getCols (); ++x)
      {
        int const v = temp (x, y);
        if (v > 0)
          temp (x, y) = (255 - v) * 256;
      }
    }
  }
  else
  {
    // "Softer"

    LayerStyles::BoxBlurAndDilateSettings bd (size, spread);

    LayerStyles::GrayscaleDilation () (
      Pixels::Map2D (stencilPixels),
      dist,
      stencilPixels.getWidth (),
      stencilPixels.getHeight (),
      bd.getDilatePixels ());

    BoxBlur () (dist, temp, temp.getCols (), temp.getRows (), bd.getBoxBlurRadius ());
  }

  // Fill
  //
  PixelARGB c (0);
  for (int y = 0; y < temp.getRows (); ++y)
  {
    for (int x = 0; x < temp.getCols (); ++x)
    {
      int const v = (temp (x, y) + 128) / 256;

      PixelRGB& dest (*((PixelRGB*)destPixels.getPixelPointer (x, y)));

      c.setAlpha (uint8(v));
      dest.blend (c);
    }
  }
}
