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

LayerContext::LayerContext (BackgroundContext& g)
  : m_base (g)
  , m_bounds (g.getBounds ())
  , m_image (Image::ARGB, m_bounds.getWidth (), m_bounds.getHeight (), true)
  , m_context (m_image)
{
  m_context.setOrigin (-m_bounds.getX (), -m_bounds.getY ());
}

LayerContext::~LayerContext ()
{
  // replace this with the fancy compositor
  m_base.getContext().drawImageAt (m_image, m_bounds.getX (), m_bounds.getY ());
}

Graphics& LayerContext::getContext ()
{
  return m_context;
}

