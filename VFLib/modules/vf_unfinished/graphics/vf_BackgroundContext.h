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
