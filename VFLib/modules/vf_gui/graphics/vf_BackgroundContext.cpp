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

BackgroundContextBase::BackgroundContextBase (Rectangle <int> const& clipBounds,
                                              Rectangle <int> const& drawBounds)
  : m_bounds (clipBounds.getIntersection (drawBounds))
  , m_image (Image::RGB,
             jmax (m_bounds.getWidth (), 1),
             jmax (m_bounds.getHeight(), 1),
             false)
{
}

//------------------------------------------------------------------------------

BackgroundContext::BackgroundContext (Graphics& destinationContext,
                                      Rectangle <int> const& drawBounds)
  : BackgroundContextBase (destinationContext.getClipBounds (), drawBounds)
  , Graphics (m_image)
  , m_destinationContext (destinationContext)
{
  setOrigin (-m_bounds.getX (), -m_bounds.getY ());
}

BackgroundContext::~BackgroundContext ()
{
  m_destinationContext.drawImageAt (m_image, m_bounds.getX (), m_bounds.getY ());
}

Rectangle <int> BackgroundContext::getBounds () const
{
  return m_bounds;
}

Image BackgroundContext::getImage () const
{
  return m_image;
}
