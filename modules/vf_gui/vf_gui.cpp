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

/** Add this to get the @ref vf_gui module.

    @file vf_gui.cpp
    @ingroup vf_gui
*/

#include "AppConfig.h"

#include "vf_gui.h"

#if JUCE_MSVC
#pragma warning (push)
#pragma warning (disable: 4100) // unreferenced formal parmaeter
#pragma warning (disable: 4355) // 'this' used in base member

#endif

#if VF_USE_FREETYPE
#include "../vf_freetype/vf_freetype.h"
#endif

namespace vf
{
#include "components/vf_TransparentBorder.cpp"

#include "graphics/vf_BackgroundContext.cpp"
#include "graphics/vf_BlendImage.cpp"
#include "graphics/vf_ChannelImageType.cpp"
#include "graphics/vf_LayerContext.cpp"
#include "graphics/vf_LabColour.cpp"
#include "graphics/vf_XYZColour.cpp"
#include "graphics/vf_RadialImageConvolutionKernel.cpp"

#if VF_USE_FREETYPE
#include "graphics/vf_FreeTypeFaces.cpp"
#endif

#include "layout/vf_ResizableLayout.cpp"
#include "layout/vf_StackedLayout.cpp"

#include "mouse/vf_DragAndDropData.cpp"
#include "mouse/vf_MouseEnterEditable.cpp"
}

#if JUCE_MSVC
#pragma warning (pop)
#endif
