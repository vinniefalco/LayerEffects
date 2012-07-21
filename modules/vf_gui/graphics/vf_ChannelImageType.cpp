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

ChannelImageType::ChannelPixelData::ChannelPixelData (Image sourceImage, int channelNumber)
  : ImagePixelData ((channelNumber < 0) ? Image::RGB : Image::SingleChannel,
                    sourceImage.getWidth (),
                    sourceImage.getHeight ())
  , m_bits (sourceImage,
            0,
            0,
            sourceImage.getWidth(),
            sourceImage.getHeight ())
  , m_channelNumber (channelNumber)
{
  jassert (sourceImage.getFormat () == Image::RGB || sourceImage.getFormat () == Image::ARGB);
}

ChannelImageType::ChannelPixelData::~ChannelPixelData ()
{
}

LowLevelGraphicsContext* ChannelImageType::ChannelPixelData::createLowLevelContext ()
{
  return new LowLevelGraphicsSoftwareRenderer (Image (this));
}

ImagePixelData* ChannelImageType::ChannelPixelData::clone ()
{
  return this;
}

ImageType* ChannelImageType::ChannelPixelData::createType() const
{
  jassertfalse;
  return nullptr;
}

void ChannelImageType::ChannelPixelData::initialiseBitmapData (
  Image::BitmapData& bd, int x, int y, Image::BitmapData::ReadWriteMode)
{
  if (m_channelNumber >= 0)
  {
    bd.data = m_bits.getPixelPointer (x, y) + m_channelNumber;
    bd.pixelFormat = Image::SingleChannel;
    bd.lineStride  = m_bits.lineStride;
    bd.pixelStride = m_bits.pixelStride;
  }
  else
  {
    bd.data = m_bits.getPixelPointer (x, y) + 0;
    bd.pixelFormat = Image::RGB;
    bd.lineStride  = m_bits.lineStride;
    bd.pixelStride = m_bits.pixelStride;
  }
}

//------------------------------------------------------------------------------

Image ChannelImageType::fromImage (Image sourceImage, int channelNumber)
{
  return Image (new ChannelPixelData (sourceImage, channelNumber));
}
