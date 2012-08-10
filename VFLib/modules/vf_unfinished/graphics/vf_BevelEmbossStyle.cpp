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

void BevelEmbossStyle::render (
  Pixels destPixels, Pixels maskPixels, Options const& options)
{
  jassert (destPixels.isRGB ());
  jassert (maskPixels.getBounds () == destPixels.getBounds ());

  // Calculate the distance transform on the mask.
  //
  typedef double T;
  Map2D <T> distMap (maskPixels.getWidth (), maskPixels.getHeight ());
  switch (options.kind)
  {
  case kindOuterBevel:
    DistanceTransform::Meijster::calculate (
      DistanceTransform::OutputDistanceMap <Map2D <T> > (distMap, options.size),
      DistanceTransform::BlackTest (maskPixels),
      maskPixels.getWidth (),
      maskPixels.getHeight (),
      DistanceTransform::Meijster::EuclideanMetric ());
    break;

  case kindInnerBevel:
    DistanceTransform::Meijster::calculate (
      DistanceTransform::OutputDistanceMap <Map2D <T> > (distMap, options.size),
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
  if (options.technique == techniqueChiselSoft)
  {
    if (options.soften > 0)
    {
      RadialImageConvolutionKernel k (options.soften + 1);
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
    10 - options.depth,
    options.lightAngle,
    options.lightElevation);

  // Apply a softening to the masks.
  //
#if 0
  if (options.technique == techniqueSmooth)
  {
    if (options.soften > 0)
    {
      RadialImageConvolutionKernel k (options.soften + 1);
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
    options.hilightMode,
    Pixels::Iterate2 (destPixels, hiPixels),
    BlendProc::RGB::Fill (options.hilightColour, options.hilightOpacity));

  // Render shadows.
  //
  BlendMode::apply (
    options.shadowMode,
    Pixels::Iterate2 (destPixels, loPixels),
    BlendProc::RGB::Fill (options.shadowColour, options.shadowOpacity));
}

