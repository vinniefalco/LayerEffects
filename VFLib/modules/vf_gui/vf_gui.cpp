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
