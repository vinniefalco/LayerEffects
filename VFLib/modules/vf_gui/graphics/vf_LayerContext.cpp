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

LayerContext::LayerContext (BackgroundContext& destinationContext,
                            Rectangle <int> const& drawBounds)
  : ContextImageBase (destinationContext.getClipBounds ().getIntersection (drawBounds),
                      Image::ARGB)
  , Graphics (getImage ())
  , m_destinationContext (destinationContext)
{
  getImage ().clear (getImage ().getBounds (), Colour::fromRGBA (0, 0, 0, 0));
  
  setOrigin (-getImageBounds ().getX (), -getImageBounds ().getY ());
} 

LayerContext::~LayerContext ()
{
  applyDropShadow ();

  applyFill ();
}

LayerContext::Options& LayerContext::getOptions ()
{
  return m_options;
}

//------------------------------------------------------------------------------

void LayerContext::applyDropShadow ()
{
  if (!m_options.dropShadow.active)
    return;

#if 0
  Image image (Image::SingleChannel,  
               getImageBounds ().getWidth (),
               getImageBounds ().getHeight ());
#endif
  }

//------------------------------------------------------------------------------

void LayerContext::applyFill ()
{
  BlendImage (
    m_destinationContext.getImage (),
    getImageBounds ().getTopLeft () - m_destinationContext.getImageBounds ().getTopLeft (),
    getImage (),
    getImage ().getBounds (),
    m_options.fill.mode,
    m_options.fill.opacity);
}

//------------------------------------------------------------------------------
