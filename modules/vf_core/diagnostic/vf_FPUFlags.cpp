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

void FPUFlags::clearUnsetFlagsFrom (const FPUFlags& flags)
{
  if (!flags.getMaskNaNs().is_set ())         m_maskNaNs.clear ();
  if (!flags.getMaskDenormals().is_set ())    m_maskDenormals.clear ();
  if (!flags.getMaskZeroDivides().is_set ())  m_maskZeroDivides.clear ();
  if (!flags.getMaskOverflows().is_set ())    m_maskOverflows.clear ();
  if (!flags.getMaskUnderflows().is_set ())   m_maskUnderflows.clear ();
//if (!flags.getMaskInexacts().is_set ())     m_maskInexacts.clear ();
  if (!flags.getFlushDenormals().is_set ())   m_flushDenormals.clear ();
  if (!flags.getInfinitySigned().is_set ())   m_infinitySigned.clear ();
  if (!flags.getRounding().is_set ())         m_rounding.clear ();
  if (!flags.getPrecision().is_set ())        m_precision.clear ();
}
