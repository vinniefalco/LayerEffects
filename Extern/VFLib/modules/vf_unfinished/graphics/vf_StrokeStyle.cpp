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

void StrokeStyle::operator () (Pixels destPixels, Pixels maskPixels)
{
  if (!active)
    return;

  if (type != typeGradient)// || gradient.style != GradientFill::styleShapeBurst)
  {
    //
    // Calculate mask using distance transform
    //

    Image matteImage (
      Image::SingleChannel,
      maskPixels.getBounds ().getWidth (),
      maskPixels.getBounds ().getHeight (),
      false);

    Pixels mattePixels (matteImage);

    switch (pos)
    {
    case posInner:
      DistanceTransform::Meijster::calculateAntiAliased (
        RenderMask (Pixels::Map2D (mattePixels), size),
        Inside (maskPixels),
        maskPixels.getWidth (),
        maskPixels.getHeight (),
        DistanceTransform::Meijster::EuclideanMetric ());
      break;

    case posOuter:
      DistanceTransform::Meijster::calculateAntiAliased (
        RenderMask (Pixels::Map2D (mattePixels), size),
        Outside (maskPixels),
        maskPixels.getWidth (),
        maskPixels.getHeight (),
        DistanceTransform::Meijster::EuclideanMetric ());
      break;

    case posCentre:
      break;

    default:
      jassertfalse;
      break;
    };

    //
    // Apply fill using mask
    //

    switch (type)
    {
    case typeColour:
      BlendMode::apply (
        mode,
        Pixels::Iterate2 (destPixels, mattePixels),
        BlendProc::RGB::MaskFill (colour, opacity));
      break;

    case typeGradient:
      break;

    case typePattern:
      break;

    default:
      jassertfalse;
      break;
    };
  }
  else
  {
    //
    // Special case for shape burst gradients
    //
    SharedTable <Colour> colourTable = gradient.colours.createLookupTable ();

    switch (pos)
    {
    case posInner:
      {
        DistanceTransform::Meijster::calculateAntiAliased (
          RenderShapeBurst (Pixels::Map2D (destPixels), size, colourTable),
          Inside (maskPixels),
          maskPixels.getWidth (),
          maskPixels.getHeight (),
          DistanceTransform::Meijster::EuclideanMetric ());
      }
      break;

    case posOuter:
      {
        DistanceTransform::Meijster::calculateAntiAliased (
          RenderShapeBurst (Pixels::Map2D (destPixels), size, colourTable),
          Outside (maskPixels),
          maskPixels.getWidth (),
          maskPixels.getHeight (),
          DistanceTransform::Meijster::EuclideanMetric ());
      }
      break;

    case posCentre:
      {
      }
      break;

    default:
      jassertfalse;
      break;
    };
  }
}
