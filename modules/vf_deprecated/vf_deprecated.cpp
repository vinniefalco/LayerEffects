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
