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

void BevelEmbossStyle::operator() (Pixels destPixels, Pixels maskPixels)
{
  jassert (destPixels.isRGB ());
  jassert (maskPixels.getBounds () == destPixels.getBounds ());

  if (!active)
    return;

  // Calculate the distance transform on the mask.
  //
  typedef double T;
  Map2D <T> distMap (maskPixels.getWidth (), maskPixels.getHeight ());
  switch (kind)
  {
  case kindOuterBevel:
    DistanceTransform::Meijster::calculate (
      DistanceTransform::OutputInverseDistanceMap <Map2D <T> > (distMap, size),
      DistanceTransform::BlackTest (maskPixels),
      maskPixels.getWidth (),
      maskPixels.getHeight (),
      DistanceTransform::Meijster::EuclideanMetric ());
    break;

  case kindInnerBevel:
    DistanceTransform::Meijster::calculate (
      DistanceTransform::OutputDistanceMap <Map2D <T> > (distMap, size),
      DistanceTransform::WhiteTest (maskPixels),
      maskPixels.getWidth (),
      maskPixels.getHeight (),
      DistanceTransform::Meijster::EuclideanMetric ());
    break;

  case kindEmboss:
  case kindPillowEmboss:
  case kindStrokeEmboss:
  default:
    jassertfalse;
    break;
  }

  // Apply a softening to the transform.
  //
#if 0
  if (technique == techniqueChiselSoft)
  {
    if (soften > 0)
    {
      RadialImageConvolutionKernel k (soften + 1);
      k.createGaussianBlur ();
      distImage = k.createConvolvedImage (distImage);
      distPixels = Pixels (distImage);
    }
  }
#endif

  Image hiImage (
    Image::SingleChannel,
    destPixels.getCols (),
    destPixels.getRows (),
    true);

  Image loImage (
    Image::SingleChannel,
    destPixels.getCols (),
    destPixels.getRows (),
    true);

  Pixels hiPixels (hiImage);
  Pixels loPixels (loImage);

  LightingTransform::calculate <T> (
    LightingTransform::PixelShader (hiPixels, loPixels),
    distMap,
    10 - depth,
    lightAngle,
    lightElevation);

  // Apply a softening to the masks.
  //
#if 0
  if (technique == techniqueSmooth)
  {
    if (soften > 0)
    {
      RadialImageConvolutionKernel k (soften + 1);
      k.createGaussianBlur ();
      
      hiImage = k.createConvolvedImage (hiImage);
      hiPixels = Pixels (hiImage);

      loImage = k.createConvolvedImage (loImage);
      loPixels = Pixels (loImage);

      Pixels::Iterate2 (hiPixels, maskPixels) (BlendProc::Gray::CopyMode <BlendMode::multiply> ());
      Pixels::Iterate2 (loPixels, maskPixels) (BlendProc::Gray::CopyMode <BlendMode::multiply> ());
    }
  }
#endif

  // Render highlights.
  //
  BlendMode::apply (
    hilightMode,
    Pixels::Iterate2 (destPixels, hiPixels),
    BlendProc::RGB::MaskFill (hilightColour, hilightOpacity));

  // Render shadows.
  //
  BlendMode::apply (
    shadowMode,
    Pixels::Iterate2 (destPixels, loPixels),
    BlendProc::RGB::MaskFill (shadowColour, shadowOpacity));
}

