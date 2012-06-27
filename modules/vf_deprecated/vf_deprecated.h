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
