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

#ifndef VF_MURMURHASH_VFHEADER
#define VF_MURMURHASH_VFHEADER

// Original source code links in .cpp file

// This file depends on some Juce declarations and defines

namespace Murmur {

extern void MurmurHash3_x86_32  (const void *key, int len, uint32 seed, void* out);
extern void MurmurHash3_x86_128 (const void *key, int len, uint32 seed, void* out);
extern void MurmurHash3_x64_128 (const void *key, int len, uint32 seed, void* out);

// Uses Juce to choose an appropriate routine

// This handy template deduces which size hash is desired
template <typename HashType>
inline void Hash (const void* key, int len, uint32 seed, HashType* out)
{
  switch (8*sizeof(HashType))
  {
  case 32:  MurmurHash3_x86_32 (key, len, seed, out); break;

#if JUCE_64BIT
  case 128: MurmurHash3_x64_128 (key, len, seed, out); break;
#else
  case 128: MurmurHash3_x86_128 (key, len, seed, out); break;
#endif

  default:
    Throw (std::runtime_error ("invalid key size in MurmurHash"));
    break;
  };
}

}

#endif
