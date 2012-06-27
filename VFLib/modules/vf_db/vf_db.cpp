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

/** Add this to get the @ref vf_db module.

    @file vf_db.cpp
    @ingroup vf_db
*/

#include "AppConfig.h"

#include "vf_db.h"

#include "../vf_sqlite/vf_sqlite.h"

#if JUCE_MSVC
#pragma warning (push)
#pragma warning (disable: 4100) // unreferenced formal parmaeter
#pragma warning (disable: 4355) // 'this' used in base member
#endif

namespace vf
{
// implementation headers
#include "detail/error_codes.h"
#include "detail/statement_imp.h"
}

namespace vf
{
#include "source/blob.cpp"
#include "source/error_codes.cpp"
#include "source/into_type.cpp"
#include "source/once_temp_type.cpp"
#include "source/prepare_temp_type.cpp"
#include "source/ref_counted_prepare_info.cpp"
#include "source/ref_counted_statement.cpp"
#include "source/session.cpp"
#include "source/statement.cpp"
#include "source/statement_imp.cpp"
#include "source/transaction.cpp"
#include "source/use_type.cpp"
}

#if JUCE_MSVC
#pragma warning (pop)
#endif
