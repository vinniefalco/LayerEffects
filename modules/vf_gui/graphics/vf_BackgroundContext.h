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

#ifndef VF_BACKGROUNDCONTEXT_VFHEADER
#define VF_BACKGROUNDCONTEXT_VFHEADER

//------------------------------------------------------------------------------

/** Context Image container base.

    This holds the image and bounding rectangle used for our custom
    contexts, to resolve the order of construction issues.

    @ingroup vf_gui

    @internal
*/
class ContextImageBase : vf::Uncopyable
{
protected:
  ContextImageBase (Rectangle <int> const& imageBounds,
                    Image::PixelFormat pixelFormat);

public:
  Rectangle <int> getImageBounds () const;

  Image getImage () const;

private:
  Rectangle <int> const m_imageBounds;
  Image m_image;
};

//------------------------------------------------------------------------------

/** Graphics context for image compositing.

    This wraps a Graphics context with an image to provide a background
    for compositing layers.

    @ingroup vf_gui
*/
class BackgroundContext : public ContextImageBase, public Graphics
{
public:
  BackgroundContext (Graphics& destinationContext,
                     Rectangle <int> const& drawBounds);

  ~BackgroundContext ();

private:
  Graphics& m_destinationContext;
};

#endif
