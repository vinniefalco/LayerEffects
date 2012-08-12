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

void OuterGlowStyle::operator() (Pixels destPixels, Pixels maskPixels)
{
  if (!active)
    return;

  SharedTable <Colour> table = colours.createLookupTable ();

#if 1
  DistanceTransform::Meijster::calculateAntiAliased (
    RenderPixelAntiAliased (
      destPixels,
      opacity,
      spread,
      size,
      table),
    DistanceMaskOutside (maskPixels),
    maskPixels.getWidth (),
    maskPixels.getHeight (),
    DistanceTransform::Meijster::EuclideanMetric ());
#else
  DistanceTransform::Meijster::calculate (
    RenderPixel (
      destPixels,
      opacity,
      spread,
      size,
      table),
    DistanceTransform::BlackTest (maskPixels),
    maskPixels.getWidth (),
    maskPixels.getHeight (),
    DistanceTransform::Meijster::ChessMetric ());
#endif
}
