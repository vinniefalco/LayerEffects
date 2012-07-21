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

/**
  This contains deprecated code.

  This file is here for compatibility and should not be used.

  @file vf_deprecated.h
  @deprecated
*/

#ifndef VF_DEPRECATED_VFHEADER
#define VF_DEPRECATED_VFHEADER

#include "../vf_core/vf_core.h"
#include "../vf_gui/vf_gui.h"

#if JUCE_MSVC
#pragma warning (push)
#pragma warning (disable: 4100) // unreferenced formal parmaeter
#pragma warning (disable: 4244) // conversion: possible loss of data
#pragma warning (disable: 4355) // 'this' used in base member
#endif

namespace vf
{
#include "containers/binary_tree.h"
#include "containers/Array.h"

#include "memory/block_pool.h"
#include "memory/destroy_n.h"
#include "memory/fixed_pool.h"
#include "memory/page_pool.h"
#include "memory/Pipe.h"

#include "gui/vf_Button.h"
#include "gui/vf_Control.h"
#include "gui/vf_ConnectedEdges.h"
#include "gui/vf_Facade.h"
#include "gui/vf_Model.h"
#include "gui/vf_Static.h"
#include "gui/vf_UiBase.h"

#include "gui/Button.h"
#include "gui/ColouredImageMaskFacade.h"
#include "gui/Label.h"
#include "gui/Meter.h"
#include "gui/PopupButton.h"
#include "gui/ResizablePanel.h"
#include "gui/ResizingPanes.h"
#include "gui/Slider.h"
#include "gui/SolidColourFacade.h"
#include "gui/Static.h"
#include "gui/Value.h"
}

#if JUCE_MSVC
#pragma warning (pop)
#endif

#endif
