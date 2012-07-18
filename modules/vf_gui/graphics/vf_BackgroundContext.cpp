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

ContextImageBase::ContextImageBase (Rectangle <int> const& imageBounds,
                                    Image::PixelFormat pixelFormat)
  : m_imageBounds (imageBounds)
  , m_image (pixelFormat,
             jmax (m_imageBounds.getWidth (), 1),
             jmax (m_imageBounds.getHeight(), 1),
             false)
{
}

Rectangle <int> ContextImageBase::getImageBounds () const
{
  return m_imageBounds;
}

Image ContextImageBase::getImage () const
{
  return m_image;
}

//------------------------------------------------------------------------------

BackgroundContext::BackgroundContext (Graphics& destinationContext,
                                      Rectangle <int> const& drawBounds)
  : ContextImageBase (destinationContext.getClipBounds ().getIntersection (drawBounds),
                      Image::RGB)
  , Graphics (getImage ())
  , m_destinationContext (destinationContext)
{
  setOrigin (-getImageBounds ().getX (), -getImageBounds ().getY ());
} 

BackgroundContext::~BackgroundContext ()
{
  m_destinationContext.drawImageAt (
    getImage (),
    getImageBounds ().getX (),
    getImageBounds ().getY ());
}
