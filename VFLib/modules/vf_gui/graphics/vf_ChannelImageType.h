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

#ifndef VF_CHANNELIMAGETYPE_VFHEADER
#define VF_CHANNELIMAGETYPE_VFHEADER

/** Presents an Image channel as a separate Image.

    This creates a new @ref Image which references one channel in the
    specified @Image.

    @ingroup vf_gui
*/
class ChannelImageType : vf::Uncopyable
{
public:
  /** Create an Image that references a channel in the source image.

      The image type will be @ref Image::SingleChannel.
  */
  static Image fromImage (Image sourceImage, int channelNumber);

private:
  class ChannelPixelData : public ImagePixelData, vf::Uncopyable
  {
  public:
    ChannelPixelData (Image sourceImage, int channelNumber);

    ~ChannelPixelData ();

    LowLevelGraphicsContext* createLowLevelContext();

    ImagePixelData* clone ();

    ImageType* createType() const;

    void initialiseBitmapData (Image::BitmapData& bd,
                               int x,
                               int y,
                               Image::BitmapData::ReadWriteMode);

  private:
    Image::BitmapData m_bits;
    int const m_channelNumber;
  };
};

#endif
