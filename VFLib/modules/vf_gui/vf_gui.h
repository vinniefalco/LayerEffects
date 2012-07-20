/*============================================================================*/
//
// Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
// See the file GNU_GPL_v2.txt for full licensing terms.
// 
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or (at your option)
// any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
// 
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 51
// Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
// 
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

#include "graphics/vf_BackgroundContext.h"
#include "graphics/vf_BlendImage.h"
#include "graphics/vf_ChannelImageType.h"
#include "graphics/vf_LayerContext.h"
#include "graphics/vf_LabColour.h"
#include "graphics/vf_Pixels.h"
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

