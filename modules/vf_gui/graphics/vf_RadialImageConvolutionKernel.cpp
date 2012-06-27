/*============================================================================*/
/*
  Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
  See the file GNU_GPL_v2.txt for full licensing terms.

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the Free
  Software Foundation; either version 2 of the License, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
  details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc., 51
  Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
/*============================================================================*/

RadialImageConvolutionKernel::RadialImageConvolutionKernel (int radiusInSamples)
  : m_radius (radiusInSamples)
{
  jassert (radiusInSamples >= 2);

  m_kernel.allocate (radiusInSamples, false);
}

RadialImageConvolutionKernel::~RadialImageConvolutionKernel()
{
}

void RadialImageConvolutionKernel::createGaussianBlur ()
{
  const double blurRadius = double(m_radius-1) / 2;
  const double radiusFactor = -1 / (2 * blurRadius * blurRadius);

  for (int r = 0; r < m_radius; ++r)
    m_kernel[r] = float( exp( radiusFactor * (r * r)));

  setOverallSum (1.0f);
}

void RadialImageConvolutionKernel::setOverallSum (float desiredTotalSum)
{
  double currentTotal = 0.0;

  for (int r = m_radius; --r >= 1; )
    currentTotal += m_kernel[r];
  currentTotal *= 2; // for symmetry
  currentTotal += m_kernel[0];

  rescaleAllValues (float (desiredTotalSum / currentTotal));
}

void RadialImageConvolutionKernel::rescaleAllValues (float multiplier)
{
  for (int r = m_radius; --r >= 0; )
    m_kernel[r] *= multiplier;
}

Image RadialImageConvolutionKernel::createConvolvedImage (Image const& sourceImage) const
{
  Image result (sourceImage.getFormat(),
                         sourceImage.getWidth(),
                         sourceImage.getHeight(),
                         true);

  Image full = createConvolvedImageFull (sourceImage);

  Graphics g (result);

  g.drawImageAt (full, -(m_radius - 1), -(m_radius - 1));

  return result;
}

Image RadialImageConvolutionKernel::createConvolvedImageFull (Image const& sourceImage) const
{
  // calc destination size based on kernel radius
  int dw = sourceImage.getWidth() + 2 * m_radius - 1;
  int dh = sourceImage.getHeight() + 2 * m_radius - 1;
  Image result (sourceImage.getFormat(), dw, dh, false);

  // calc size of edge-replicated source dimensions
  int sw = dw + 2 * m_radius - 1;
  int sh = dh + 2 * m_radius - 1;

  // temp buffer is big enough for the largest edge-replicated line
  HeapBlock <uint8> temp;
  temp.allocate (jmax (sw, sh), false);

  const Image::BitmapData srcData (sourceImage,
                                            Image::BitmapData::readOnly);

  const Image::BitmapData destData (result, 0, 0, dw, dh,
                                             Image::BitmapData::readWrite);

  int ci[4];
  int nc = srcData.pixelStride;
  bool alpha = false;

  switch (srcData.pixelFormat)
  {
  case Image::RGB:
    ci[0] = PixelRGB::indexR;
    ci[1] = PixelRGB::indexG;
    ci[2] = PixelRGB::indexB;
    nc = 3;
    alpha = false;
    break;

  case Image::ARGB:
    ci[0] = PixelARGB::indexR;
    ci[1] = PixelARGB::indexG;
    ci[2] = PixelARGB::indexB;
    ci[3] = PixelARGB::indexA;
    nc = 3;
    alpha = true;
    break;

  case Image::SingleChannel:
    ci[0] = 0;
    nc = 0;
    alpha = true;
    break;

  default:
    Throw (Error ().fail (__FILE__, __LINE__));
    break;
  }

  // edge-replicate each row in source to temp, and convolve into dest
  for (int y = 0; y < srcData.height; ++y)
  {
    for (int c = 0; c < nc; ++c)
    {
      copy (srcData.width,
            temp,
            1,
            srcData.getLinePointer (y) + ci[c],
            srcData.pixelStride,
            2 * (m_radius - 1));

      convolve (destData.width,
                destData.getPixelPointer (0, y + m_radius - 1) + ci[c],
                destData.pixelStride,
                temp,
                1,
                m_radius,
                m_kernel);
    }

    if (alpha)
    {
      copy_alpha (srcData.width,
                  temp,
                  1,
                  srcData.getLinePointer (y) + ci[nc],
                  srcData.pixelStride,
                  2 * (m_radius - 1));

      convolve (destData.width,
                destData.getPixelPointer (0, y + m_radius - 1) + ci[nc],
                destData.pixelStride,
                temp,
                1,
                m_radius,
                m_kernel);
    }
  }

  // edge-replicate each intermediate column from dest to temp, and convolve into dest
  for (int x = 0; x < destData.width; ++x)
  {
    for (int c = 0; c < nc; ++c)
    {
      copy (srcData.height,
            temp,
            1,
            destData.getPixelPointer (x, m_radius - 1) + ci[c],
            destData.lineStride,
            2 * (m_radius - 1));

      convolve (destData.height,
                destData.getPixelPointer (x, 0) + ci[c],
                destData.lineStride,
                temp,
                1,
                m_radius,
                m_kernel);
    }

    if (alpha)
    {
      copy_alpha (srcData.height,
                  temp,
                  1,
                  destData.getPixelPointer (x, m_radius - 1) + ci[nc],
                  destData.lineStride,
                  2 * (m_radius - 1));

      convolve (destData.height,
                destData.getPixelPointer (x, 0) + ci[nc],
                destData.lineStride,
                temp,
                1,
                m_radius,
                m_kernel);
    }
  }

  return result;
}

void RadialImageConvolutionKernel::copy (int pixels,
                                         uint8* dest,
                                         int destSkip,
                                         const uint8* src,
                                         int srcSkip,
                                         int replicas)
{
  jassert (pixels > 0);

  for (int i = replicas; --i >= 0;)
  {
    *dest = *src;
    dest += destSkip;
  }

  for (int i = pixels; --i > 0;) // pixels-1 iterations
  {
    *dest = *src;
    src += srcSkip;
    dest += destSkip;
  }

  for (int i = replicas + 1; --i >= 0;) // extra iteration
  {
    *dest = *src;
    dest += destSkip;
  }
}

void RadialImageConvolutionKernel::copy_alpha (int pixels,
                                               uint8* dest,
                                               int destSkip,
                                               const uint8* src,
                                               int srcSkip,
                                               int replicas)
{
  jassert (pixels > 0);

  for (int i = replicas; --i >= 0;)
  {
    *dest = 0;
    dest += destSkip;
  }

  for (int i = pixels; --i >= 0;)
  {
    *dest = *src;
    src += srcSkip;
    dest += destSkip;
  }

  for (int i = replicas; --i >= 0;)
  {
    *dest = 0;
    dest += destSkip;
  }
}

void RadialImageConvolutionKernel::convolve (int pixels,
                                             uint8* dest,
                                             int destSkip,
                                             const uint8* src,
                                             int srcSkip,
                                             int radius,
                                             const float* kernel)
{
  for (int n = pixels; --n >= 0;)
  {
    const uint8* in = src;
    const float* k = kernel + radius;
    float tot = 0;

    for (int i = radius; --i >= 0;)
    {
      tot += *--k * *in;
      in += srcSkip;
    }

    for (int i = radius; --i > 0;)
    {
      tot += *++k * *in;
      in += srcSkip;
    }

    *dest = uint8(tot);//uint8 (jmin (0xff, roundToInt (tot)));
    dest += destSkip;

    src += srcSkip;
  }
}
