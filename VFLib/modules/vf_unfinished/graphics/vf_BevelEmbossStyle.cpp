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

/** Directional lighting transform.

    Calculates the incident highlights and shadows for each
    point in a discrete height map.
*/
struct LightingTransform
{
  template <class T, class Shader, class Map, class R1, class R2, class R3>
  static void calculate (
    Shader shader,
    Map map,
    R1 depth,
    R2 angle,
    R3 elevation)
  {
    Vec3 <T> lightNormal (
       cos (elevation) * cos (angle),
      -cos (elevation) * sin (angle),
       sin (elevation));

    for (int y = 1; y < map.getRows () - 1; ++y)
    {
      for (int x = 1; x < map.getCols () - 1; ++x)
      {
        if (map (x, y) != 0)
        {
          // Calculate normal from height map.
          Vec3 <T> n (T (map (x+1,y) - map (x-1,y)),
                      T (map (x,y+1) - map (x,y-1)),
                      T (depth));

          // Calculate incident light amount, range [-1, 1]
          T incidentLight = n.getDotProduct (lightNormal) / n.getNormal ();

          shader (x, y, incidentLight);
        }
        else
        {
          shader (x, y, 0);
        }
      }
    }
  }

  struct PixelShader
  {
    PixelShader (Pixels hi, Pixels lo) : m_hi (hi), m_lo (lo)
    {
    }

    template <class T>
    inline void operator() (int x, int y, T incidentLight)
    {
      if (incidentLight >= 0)
        m_hi (x, y) = uint8 (255 * incidentLight + T(.5));
      else
        m_lo (x, y) = uint8 (-255 * incidentLight + T(.5));
    }

  private:
    Pixels::Map2D m_hi;
    Pixels::Map2D m_lo;
  };

  struct PixelShader
  {
    PixelShader (Pixels hi, Pixels lo) : m_hi (hi), m_lo (lo)
    {
    }

    template <class T>
    inline void operator() (int x, int y, T incidentLight)
    {
      if (incidentLight >= 0)
        m_hi (x, y) = uint8 (255 * incidentLight + T(.5));
      else
        m_lo (x, y) = uint8 (-255 * incidentLight + T(.5));
    }

  private:
    Pixels::Map2D m_hi;
    Pixels::Map2D m_lo;
  };
};

//------------------------------------------------------------------------------

struct OutputDistancePixels
{
  OutputDistancePixels (Pixels dest, int radius)
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

//------------------------------------------------------------------------------

template <class T>
struct OutputDistanceMap
{
  OutputDistanceMap (Map2D <T>& map, int radius)
    : m_map (map)
    , m_radius (radius)
    , m_radiusSquared (radius * radius)
  {
  }

  void operator () (int const x, int const y, double distance)
  {
    if (distance <= m_radiusSquared && distance > 0)
      m_map (x, y) = T (std::sqrt (distance));
    else
      m_map (x, y) = 0;
  }

private:
  Map2D <T> m_map;
  int m_radius;
  int m_radiusSquared;
};

//------------------------------------------------------------------------------

void BevelEmbossStyle::render (
  Pixels destPixels, Pixels maskPixels, BevelEmbossStyle::Options const& options)
{
  jassert (destPixels.isRGB ());
  jassert (maskPixels.getBounds () == destPixels.getBounds ());

  // Calculate the distance transform on the mask.
  //
#if 1
  typedef double T;
  Map2D <T> distMap (maskPixels.getWidth (), maskPixels.getHeight ());
  switch (options.kind)
  {
  case kindOuterBevel:
    DistanceTransform::Meijster::calculate (
      OutputDistanceMap <T> (distMap, options.size),
      DistanceTransform::BlackTest (maskPixels),
      maskPixels.getWidth (),
      maskPixels.getHeight (),
      DistanceTransform::Meijster::EuclideanMetric ());
    break;

  case kindInnerBevel:
    DistanceTransform::Meijster::calculate (
      OutputDistanceMap <T> (distMap, options.size),
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

#else
  Image distImage (Image::SingleChannel, maskPixels.getWidth (), maskPixels.getHeight (), false);
  Pixels distPixels (distImage);

  switch (options.kind)
  {
  case kindOuterBevel:
    DistanceTransform::Meijster::calculate (
      OutputDistancePixels (distPixels, options.size),
      DistanceTransform::BlackTest (maskPixels),
      maskPixels.getWidth (),
      maskPixels.getHeight (),
      DistanceTransform::Meijster::EuclideanMetric ());
    break;

  case kindInnerBevel:
    DistanceTransform::Meijster::calculate (
      OutputDistancePixels (distPixels, options.size),
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
#endif

  // Apply a softening to the transform.
  //
#if 0
  if (options.technique == techinqueChiselSoft)
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

#if 1
  LightingTransform::calculate <T> (
    LightingTransform::PixelShader (hiPixels, loPixels),
    distMap,
    10 - options.depth,
    options.lightAngle,
    options.lightElevation);

#else
  LightingTransform::calculate <double> (
    LightingTransform::PixelShader (hiPixels, loPixels),
    Pixels::Map2D (distPixels),
    options.depth,
    options.lightAngle,
    options.lightElevation);

#endif

  // Apply a softening to the masks.
  //
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

