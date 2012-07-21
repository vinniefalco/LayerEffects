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
  @internal

  This contains deprecated code.

  This file is here for compatibility and should not be used.

  @file vf_deprecated.cpp
  @deprecated
*/

#include "AppConfig.h"

#include "vf_deprecated.h"

#if JUCE_MSVC
#pragma warning (push)
#pragma warning (disable: 4100) // unreferenced formal parmaeter
#pragma warning (disable: 4244) // conversion: possible loss of data
#pragma warning (disable: 4355) // 'this' used in base member
#endif

namespace vf
{
#include "containers/Array.cpp"

#include "memory/Pipe.cpp"

#include "gui/vf_Button.cpp"
#include "gui/vf_Static.cpp"
#include "gui/vf_UiBase.cpp"
#include "gui/vf_Control.cpp"
#include "gui/vf_Facade.cpp"
#include "gui/vf_Model.cpp"

#include "gui/Button.cpp"
#include "gui/ColouredImageMaskFacade.cpp"
#include "gui/Label.cpp"
#include "gui/Meter.cpp"
#include "gui/PopupButton.cpp"
#include "gui/ResizablePanel.cpp"
#include "gui/ResizingPanes.cpp"
#include "gui/Slider.cpp"
#include "gui/Static.cpp"
#include "gui/SolidColourFacade.cpp"

}

#if JUCE_MSVC
#pragma warning (pop)
#endif
