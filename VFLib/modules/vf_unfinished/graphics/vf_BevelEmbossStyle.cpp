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
  Pixels destPixels, Pixels maskPixels, BevelEmbossStyle::Options const& options)
{
  jassert (destPixels.isRGB ());
  jassert (maskPixels.getBounds () == destPixels.getBounds ());

  // Calculate the distance transform on the mask.
  //
  struct OutputDistance
  {
    OutputDistance (Pixels dest, int radius)
      : m_dest (dest)
      , m_radius (radius)
      , m_radiusSquared (radius * radius)
    {
    }

    void operator () (int const x, int const y, double distance)
    {
      if (distance <= m_radiusSquared && distance > 0)
      {
        distance = sqrt (distance);

        *m_dest.getPixelPointer (x, y) = uint8 (255 * distance / m_radius + 0.5);
      }
      else
      {
        *m_dest.getPixelPointer (x, y) = 0;
      }
    }

  private:
    Pixels m_dest;
    int m_radius;
    int m_radiusSquared;
  };

  Image distImage (Image::SingleChannel, maskPixels.getWidth (), maskPixels.getHeight (), false);
  Pixels distPixels (distImage);
  DistanceTransform::Meijster::calculate (distPixels, maskPixels);

  switch (options.kind)
  {
  case kindOuterBevel:
    DistanceTransform::Meijster::calculate (
      OutputDistance (distPixels, options.size),
      DistanceTransform::BlackTest (maskPixels),
      maskPixels.getWidth (),
      maskPixels.getHeight (),
      DistanceTransform::Meijster::EuclideanMetric ());
    break;

  case kindInnerBevel:
    DistanceTransform::Meijster::calculate (
      OutputDistance (distPixels, options.size),
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
  if (options.soften > 0)
  {
    RadialImageConvolutionKernel k (options.soften + 1);
    k.createGaussianBlur ();
    distImage = k.createConvolvedImage (distImage);
    distPixels = Pixels (distImage);
  }

  // Set up a few constants.
  //
  Vec3 <float> lightNormal (
     cos (options.lightElevation) * cos (options.lightAngle),
    -cos (options.lightElevation) * sin (options.lightAngle),
     sin (options.lightElevation));

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

  for (int y = 0; y < distPixels.getRows () - 1; ++y)
  {
    for (int x = 0; x < distPixels.getCols () - 1; ++x)
    {
      uint8* ps = distPixels.getPixelPointer (x, y);

      Vec3 <float> n (
        float (ps [distPixels.getColBytes ()] - ps [0]),
        float (ps [distPixels.getRowBytes ()] - ps [0]),
        float (1));

      float incidentLight = n.getDotProduct (lightNormal) / n.getNormal ();

      if (incidentLight > 0)
        *hiPixels.getPixelPointer (x, y) = uint8 ( 255 * incidentLight);
      else
      {
        //jassert (x > 50);
        *loPixels.getPixelPointer (x, y) = uint8 (-255 * incidentLight);
      }
    }
  }

#if 1
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

#else
  Pixels::Iterate2 (destPixels, distPixels) (BlendProc::RGB::CopyGray ());

#endif
}

