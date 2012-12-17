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

/** Include this to get the @ref vf_gui module.

    @file vf_gui.h
    @ingroup vf_gui
*/

#ifndef VF_GUI_VFHEADER
#define VF_GUI_VFHEADER

/*============================================================================*/
/**
    Classes for appearance and graphical display.

    This module offers classes that assist with the development and presentation
    of user interface components.

    @defgroup vf_gui vf_gui
*/

#include "../vf_core/vf_core.h"

#include "modules/juce_gui_basics/juce_gui_basics.h"

#if JUCE_MSVC
#pragma warning (push)
#pragma warning (disable: 4100) // unreferenced formal parameter
#pragma warning (disable: 4355) // 'this' : used in base member initializer list
#endif

namespace vf
{

#include "components/vf_ComponentBroadcast.h"
#include "components/vf_ComponentNotifyParent.h"
#include "components/vf_TransparentBorder.h"

#include "graphics/vf_ChannelImageType.h"
#include "graphics/vf_LabColour.h"
#include "graphics/vf_XYZColour.h"
#include "graphics/vf_RadialImageConvolutionKernel.h"
#include "graphics/vf_VerticalGradient.h"

#if VF_USE_FREETYPE
#include "graphics/vf_FreeTypeFaces.h"
#endif

#include "layout/vf_ContentComponentConstrainer.h"
#include "layout/vf_ResizableLayout.h"
#include "layout/vf_StackedLayout.h"

#include "mouse/vf_DragAndDropData.h"
#include "mouse/vf_MouseEnterEditable.h"
#include "mouse/vf_MouseEnterGroup.h"

}

#if JUCE_MSVC
#pragma warning (pop)
#endif

#endif

