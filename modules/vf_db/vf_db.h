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

/** Include this to get the @ref vf_db module.

    @file vf_db.h
    @ingroup vf_db
*/

#ifndef VF_DB_VFHEADER
#define VF_DB_VFHEADER

/*============================================================================*/
/**
  An embedded database wrapper with an intuitive, type-safe interface.

  This collection of classes let's you access embedded SQLite databases
  using C++ syntax that is very similar to regular SQL.

  This module requires the @ref vf_sqlite external module.

  @defgroup vf_db vf_db
*/

#include "../vf_core/vf_core.h"

// forward declares
struct sqlite3;
struct sqlite3_blob;
struct sqlite3_stmt;
namespace vf {
namespace db {
namespace detail {
class prepare_temp_type;
class ref_counted_statement; // statement.h
class statement_imp;         // into_type.h, use_type.h
}
class blob;                  // exchange_traits.h
class session;               // statement.h
}
}

#if JUCE_MSVC
#pragma warning (push)
#pragma warning (disable: 4355) // 'this' : used in base member initializer list
#endif

namespace vf
{

#include "api/backend.h"
#include "api/transaction.h"
#include "detail/type_ptr.h"

#include "api/blob.h"
#include "api/type_conversion_traits.h"

#include "detail/exchange_traits.h"

#include "detail/into_type.h"
#include "detail/use_type.h"

#include "api/statement.h"
#include "detail/type_conversion.h"

#include "detail/ref_counted_statement.h"

#include "api/into.h"
#include "api/use.h"
#include "detail/ref_counted_prepare_info.h"

#include "detail/prepare_temp_type.h"

#include "detail/once_temp_type.h"

#include "api/session.h"

}

#if JUCE_MSVC
#pragma warning (pop)
#endif

#endif
