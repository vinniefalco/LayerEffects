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

#ifndef VF_FIFOFREESTORE_VFHEADER
#define VF_FIFOFREESTORE_VFHEADER

#if VF_USE_BOOST
#include "vf_FifoFreeStoreWithTLS.h"

#else
#include "vf_FifoFreeStoreWithoutTLS.h"

#endif

/** Selected free store based on compilation settings.

    @internal
    @ingroup internal
*/
#if VF_USE_BOOST
typedef FifoFreeStoreWithTLS FifoFreeStoreType;
#else
typedef FifoFreeStoreWithoutTLS FifoFreeStoreType;
#endif

#endif
