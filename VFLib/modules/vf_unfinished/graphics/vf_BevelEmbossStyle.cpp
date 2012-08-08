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

//------------------------------------------------------------------------------

void BevelEmbossStyle::render (
  Pixels destPixels, Pixels maskPixels, BevelEmbossStyle::Options const& options)
{
#if 0
  jassert (maskPixels.getBounds () == destPixels.getBounds ());

  Vec3 <float> lightNormal (
     cos (options.lightElevation) * cos (options.lightAngle),
    -cos (options.lightElevation) * sin (options.lightAngle),
     sin (options.lightElevation));

  Image hilightImage (
    Image::SingleChannel,
    destPixels.getCols (),
    destPixels.getRows (),
    true);

  Image shadowImage (
    Image::SingleChannel,
    destPixels.getCols (),
    destPixels.getRows (),
    true);

  Pixels hilitePixels (hilightImage);
  Pixels shadowPixels (shadowImage);

  for (int y = 1; y < dest.getRows ()-1; ++y)
  {
    for (int x = 1; x < dest.getCols ()-1; ++x)
    {
      uint8* ps = maskPixels.getPixelPointer (x, y);

      Vec3 <float> n (
        float (ps [-src.getColBytes ()] - ps [src.getColBytes ()]),
        float (ps [-src.getRowBytes ()] - ps [src.getRowBytes ()]),
        float (1));

      float incidentLight = n.getDotProduct (lightNormal) / n.getNormal ();

      if (incidentLight > 0)
        *dest.getPixelPointer (x, y) = uint8 (255 * incidentLight);
      //else
      //  *dest.getPixelPointer (x, y) = uint8 (-255 * incidentLight);
    }
  }

  copyImage (destImage,
             Point <int> (0, 0),
             sourceImage,
             sourceImage.getBounds (),
             BlendMode::modeDarken,
             1);

  return destImage;
#endif
}

