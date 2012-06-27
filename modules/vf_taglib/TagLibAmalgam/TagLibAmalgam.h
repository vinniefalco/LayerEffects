/*
  ==============================================================================

  Copyright (c) 2002 Scott Wheeler, Lukas Lalinsky, Ismael Orenstein,
  Allan Sandfeld Jensen, Teemu Tervo, Mathias Panzenbock

  Official Project Location: http://developer.kde.org/~wheeler/taglib.html
  Amalgamated Project Location: https://github.com/vinniefalco/TagLibAmalgam

  ------------------------------------------------------------------------------

  TagLib is distributed under the GNU Lesser General Public License (LGPL) and
  Mozilla Public License (MPL). Essentially that means that it may be used in
  proprietary applications, but if changes are made to TagLib they must be
  contributed back to the project. Please review the licenses if you are
  considering using TagLib in your project. See COPYING.MPL and COPYING.GPL for
  more information on the licenses.

  ==============================================================================
*/

#define TAGLIB_NO_CONFIG
#define MAKE_TAGLIB_LIB
#define TAGLIB_STATIC


/*** Start of inlined file: TagLibAmalgamTemplatePublicHeaders.h ***/
/* Extracted from CMakeLists.txt */

/*** Start of inlined file: tag.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_TAG_H
#define TAGLIB_TAG_H


/*** Start of inlined file: taglib_export.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_EXPORT_H
#define TAGLIB_EXPORT_H

#if defined(TAGLIB_STATIC)
#define TAGLIB_EXPORT
#elif (defined(_WIN32) || defined(_WIN64))
#ifdef MAKE_TAGLIB_LIB
#define TAGLIB_EXPORT __declspec(dllexport)
#else
#define TAGLIB_EXPORT __declspec(dllimport)
#endif
#elif defined(__GNUC__) && (__GNUC__ > 4 || __GNUC__ == 4 && __GNUC_MINOR__ >= 1)
#define TAGLIB_EXPORT __attribute__ ((visibility("default")))
#else
#define TAGLIB_EXPORT
#endif

#ifndef TAGLIB_NO_CONFIG
#include "taglib_config.h"
#endif

#endif

/*** End of inlined file: taglib_export.h ***/


/*** Start of inlined file: tstring.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_STRING_H
#define TAGLIB_STRING_H


/*** Start of inlined file: taglib.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_H
#define TAGLIB_H

#define TAGLIB_MAJOR_VERSION 1
#define TAGLIB_MINOR_VERSION 7
#define TAGLIB_PATCH_VERSION 0

#if defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 1))
#define TAGLIB_IGNORE_MISSING_DESTRUCTOR _Pragma("GCC diagnostic ignored \"-Wnon-virtual-dtor\"")
#else
#define TAGLIB_IGNORE_MISSING_DESTRUCTOR
#endif

#if (defined(_MSC_VER) && _MSC_VER >= 1600)
#define TAGLIB_CONSTRUCT_BITSET(x) static_cast<unsigned long long>(x)
#else
#define TAGLIB_CONSTRUCT_BITSET(x) static_cast<unsigned long>(x)
#endif

#include <string>

#ifdef __APPLE__
#  include <libkern/OSAtomic.h>
#  define TAGLIB_ATOMIC_MAC
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#  define NOMINMAX
#  include <windows.h>
#  define TAGLIB_ATOMIC_WIN
#elif defined (__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__ >= 401)    \
	  && (defined(__i386__) || defined(__i486__) || defined(__i586__) || \
		  defined(__i686__) || defined(__x86_64) || defined(__ia64)) \
	  && !defined(__INTEL_COMPILER)
#  define TAGLIB_ATOMIC_GCC
#elif defined(__ia64) && defined(__INTEL_COMPILER)
#  include <ia64intrin.h>
#  define TAGLIB_ATOMIC_GCC
#endif

//! A namespace for all TagLib related classes and functions

/*!
 * This namespace contains everything in TagLib.  For projects working with
 * TagLib extensively it may be convenient to add a
 * \code
 * using namespace TagLib;
 * \endcode
 */

namespace TagLib {

  class String;

  typedef wchar_t wchar;
  typedef unsigned char  uchar;
  typedef unsigned short ushort;
  typedef unsigned int   uint;
  typedef unsigned long  ulong;

  /*!
   * Unfortunately std::wstring isn't defined on some systems, (i.e. GCC < 3)
   * so I'm providing something here that should be constant.
   */
  typedef std::basic_string<wchar> wstring;

#ifndef DO_NOT_DOCUMENT // Tell Doxygen to skip this class.
  /*!
   * \internal
   * This is just used as a base class for shared classes in TagLib.
   *
   * \warning This <b>is not</b> part of the TagLib public API!
   */

  class RefCounter
  {
  public:
	RefCounter() : refCount(1) {}

#ifdef TAGLIB_ATOMIC_MAC
	void ref() { OSAtomicIncrement32Barrier(const_cast<int32_t*>(&refCount)); }
	bool deref() { return ! OSAtomicDecrement32Barrier(const_cast<int32_t*>(&refCount)); }
	int32_t count() { return refCount; }
  private:
	volatile int32_t refCount;
#elif defined(TAGLIB_ATOMIC_WIN)
	void ref() { InterlockedIncrement(&refCount); }
	bool deref() { return ! InterlockedDecrement(&refCount); }
	long count() { return refCount; }
  private:
	volatile long refCount;
#elif defined(TAGLIB_ATOMIC_GCC)
	void ref() { __sync_add_and_fetch(&refCount, 1); }
	bool deref() { return ! __sync_sub_and_fetch(&refCount, 1); }
	int count() { return refCount; }
  private:
	volatile int refCount;
#else
	void ref() { refCount++; }
	bool deref() { return ! --refCount; }
	int count() { return refCount; }
  private:
	uint refCount;
#endif

  };

#endif // DO_NOT_DOCUMENT

}

/*!
 * \mainpage TagLib
 *
 * \section intro Introduction
 *
 * TagLib is a library for reading and editing audio meta data, commonly know as \e tags.
 *
 * Features:
 * - A clean, high level, C++ API to handling audio meta data.
 * - Format specific APIs for advanced API users.
 * - ID3v1, ID3v2, APE, FLAC, Xiph, iTunes-style MP4 and WMA tag formats.
 * - MP3, MPC, FLAC, MP4, ASF, AIFF, WAV, TrueAudio, WavPack, Ogg FLAC, Ogg Vorbis and Speex file formats.
 * - Basic audio file properties such as length, sample rate, etc.
 * - Long term binary and source compatibility.
 * - Extensible design, notably the ability to add other formats or extend current formats as a library user.
 * - Full support for unicode and internationalized tags.
 * - Dual <a href="http://www.mozilla.org/MPL/MPL-1.1.html">MPL</a> and
 *   <a href="http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html">LGPL</a> licenses.
 * - No external toolkit dependancies.
 *
 * \section why Why TagLib?
 *
 * TagLib originally was written to provide an updated and improved ID3v2 implementation in C++ for use
 * in a variety of Open Source projects.  Since development began in 2002 and the 1.0 release in 2004
 * it has expanded to cover a wide variety of tag and file formats and is used in a wide variety of
 * Open Source and proprietary applications.  It now supports a variety of UNIXes, including Apple's OS
 * X, as well as Microsoft Windows.
 *
 * \section commercial Usage in Commercial Applications
 *
 * TagLib's licenses \e do allow usage within propriety (\e closed) applications, however TagLib is \e not
 * public domain.  Please note the requirements of the LGPL or MPL, and adhere to at least one of them.
 * In simple terms, you must at a minimum note your usage of TagLib, note the licensing terms of TagLib and
 * if you make changes to TagLib publish them.  Please review the licenses above before using TagLib in your
 * software.  Note that you may choose either the MPL or the LGPL, you do not have to fulfill the
 * requirements of both.
 *
 * \section installing Installing TagLib
 *
 * Please see the <a href="http://developer.kde.org/~wheeler/taglib.html">TagLib website</a> for the latest
 * downloads.
 *
 * TagLib can be built using the CMake build system. TagLib installs a taglib-config and pkg-config file to
 * make it easier to integrate into various build systems.  Note that TagLib's include install directory \e must
 * be included in the header include path. Simply adding <taglib/tag.h> will \e not work.
 *
 * \section start Getting Started
 *
 * TagLib provides both simple, abstract APIs which make it possible to ignore the differences between tagging
 * formats and format specific APIs which allow programmers to work with the features of specific tagging
 * schemes.  There is a similar abstraction mechanism for AudioProperties.
 *
 * The best place to start is with the <b>Class Hierarchy</b> linked at the top of the page.  The File and
 * AudioProperties classes and their subclasses are the core of TagLib.  The FileRef class is also a convenient
 * way for using a value-based handle.
 *
 * \note When working with FileRef please consider that it has only the most basic (extension-based) file
 * type resolution.  Please see its documentation on how to plug in more advanced file type resolution.  (Such
 * resolution may be part of later TagLib releases by default.)
 *
 * Here's a very simple example with TagLib:
 *
 * \code
 *
 * TagLib::FileRef f("Latex Solar Beef.mp3");
 * TagLib::String artist = f.tag()->artist(); // artist == "Frank Zappa"
 *
 * f.tag()->setAlbum("Fillmore East");
 * f.save();
 *
 * TagLib::FileRef g("Free City Rhymes.ogg");
 * TagLib::String album = g.tag()->album(); // album == "NYC Ghosts & Flowers"
 *
 * g.tag()->setTrack(1);
 * g.save();
 *
 * \endcode
 *
 * More examples can be found in the \e examples directory of the source distribution.
 *
 * \section Contact
 *
 * Questions about TagLib should be directed to the TagLib mailing list, not directly to the author.
 *
 *  - <a href="http://developer.kde.org/~wheeler/taglib/">TagLib Homepage</a>
 *  - <a href="https://mail.kde.org/mailman/listinfo/taglib-devel">TagLib Mailing List (taglib-devel@kde.org)</a>
 *
 * \author Scott Wheeler <wheeler@kde.org> et al.
 *
 */

#endif

/*** End of inlined file: taglib.h ***/


/*** Start of inlined file: tbytevector.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_BYTEVECTOR_H
#define TAGLIB_BYTEVECTOR_H

#include <vector>
#include <iostream>

namespace TagLib {

  //! A byte vector

  /*!
   * This class provides a byte vector with some methods that are useful for
   * tagging purposes.  Many of the search functions are tailored to what is
   * useful for finding tag related paterns in a data array.
   */

  class TAGLIB_EXPORT ByteVector
  {
  public:
#ifndef DO_NOT_DOCUMENT
	typedef std::vector<char>::iterator Iterator;
	typedef std::vector<char>::const_iterator ConstIterator;
#endif

	/*!
	 * Constructs an empty byte vector.
	 */
	ByteVector();

	/*!
	 * Construct a vector of size \a size with all values set to \a value by
	 * default.
	 */
	ByteVector(uint size, char value = 0);

	/*!
	 * Contructs a byte vector that is a copy of \a v.
	 */
	ByteVector(const ByteVector &v);

	/*!
	 * Contructs a byte vector that contains \a c.
	 */
	ByteVector(char c);

	/*!
	 * Constructs a byte vector that copies \a data for up to \a length bytes.
	 */
	ByteVector(const char *data, uint length);

	/*!
	 * Constructs a byte vector that copies \a data up to the first null
	 * byte.  The behavior is undefined if \a data is not null terminated.
	 * This is particularly useful for constructing byte arrays from string
	 * constants.
	 */
	ByteVector(const char *data);

	/*!
	 * Destroys this ByteVector instance.
	 */
	virtual ~ByteVector();

	/*!
	 * Sets the data for the byte array using the first \a length bytes of \a data
	 */
	ByteVector &setData(const char *data, uint length);

	/*!
	 * Sets the data for the byte array copies \a data up to the first null
	 * byte.  The behavior is undefined if \a data is not null terminated.
	 */
	ByteVector &setData(const char *data);

	/*!
	 * Returns a pointer to the internal data structure.
	 *
	 * \warning Care should be taken when modifying this data structure as it is
	 * easy to corrupt the ByteVector when doing so.  Specifically, while the
	 * data may be changed, its length may not be.
	 */
	char *data();

	/*!
	 * Returns a pointer to the internal data structure which may not be modified.
	 */
	const char *data() const;

	/*!
	 * Returns a byte vector made up of the bytes starting at \a index and
	 * for \a length bytes.  If \a length is not specified it will return the bytes
	 * from \a index to the end of the vector.
	 */
	ByteVector mid(uint index, uint length = 0xffffffff) const;

	/*!
	 * This essentially performs the same as operator[](), but instead of causing
	 * a runtime error if the index is out of bounds, it will return a null byte.
	 */
	char at(uint index) const;

	/*!
	 * Searches the ByteVector for \a pattern starting at \a offset and returns
	 * the offset.  Returns -1 if the pattern was not found.  If \a byteAlign is
	 * specified the pattern will only be matched if it starts on a byte divisible
	 * by \a byteAlign (starting from \a offset).
	 */
	int find(const ByteVector &pattern, uint offset = 0, int byteAlign = 1) const;

	/*!
	 * Searches the ByteVector for \a pattern starting from either the end of the
	 * vector or \a offset and returns the offset.  Returns -1 if the pattern was
	 * not found.  If \a byteAlign is specified the pattern will only be matched
	 * if it starts on a byte divisible by \a byteAlign (starting from \a offset).
	 */
	int rfind(const ByteVector &pattern, uint offset = 0, int byteAlign = 1) const;

	/*!
	 * Checks to see if the vector contains the \a pattern starting at position
	 * \a offset.  Optionally, if you only want to search for part of the pattern
	 * you can specify an offset within the pattern to start from.  Also, you can
	 * specify to only check for the first \a patternLength bytes of \a pattern with
	 * the \a patternLength argument.
	 */
	bool containsAt(const ByteVector &pattern, uint offset, uint patternOffset = 0, uint patternLength = 0xffffffff) const;

	/*!
	 * Returns true if the vector starts with \a pattern.
	 */
	bool startsWith(const ByteVector &pattern) const;

	/*!
	 * Returns true if the vector ends with \a pattern.
	 */
	bool endsWith(const ByteVector &pattern) const;

	/*!
	 * Replaces \a pattern with \a with and returns a reference to the ByteVector
	 * after the operation.  This \e does modify the vector.
	 */
	ByteVector &replace(const ByteVector &pattern, const ByteVector &with);

	/*!
	 * Checks for a partial match of \a pattern at the end of the vector.  It
	 * returns the offset of the partial match within the vector, or -1 if the
	 * pattern is not found.  This method is particularly useful when searching for
	 * patterns that start in one vector and end in another.  When combined with
	 * startsWith() it can be used to find a pattern that overlaps two buffers.
	 *
	 * \note This will not match the complete pattern at the end of the string; use
	 * endsWith() for that.
	 */
	int endsWithPartialMatch(const ByteVector &pattern) const;

	/*!
	 * Appends \a v to the end of the ByteVector.
	 */
	ByteVector &append(const ByteVector &v);

	/*!
	 * Clears the data.
	 */
	ByteVector &clear();

	/*!
	 * Returns the size of the array.
	 */
	uint size() const;

	/*!
	 * Resize the vector to \a size.  If the vector is currently less than
	 * \a size, pad the remaining spaces with \a padding.  Returns a reference
	 * to the resized vector.
	 */
	ByteVector &resize(uint size, char padding = 0);

	/*!
	 * Returns an Iterator that points to the front of the vector.
	 */
	Iterator begin();

	/*!
	 * Returns a ConstIterator that points to the front of the vector.
	 */
	ConstIterator begin() const;

	/*!
	 * Returns an Iterator that points to the back of the vector.
	 */
	Iterator end();

	/*!
	 * Returns a ConstIterator that points to the back of the vector.
	 */
	ConstIterator end() const;

	/*!
	 * Returns true if the vector is null.
	 *
	 * \note A vector may be empty without being null.
	 * \see isEmpty()
	 */
	bool isNull() const;

	/*!
	 * Returns true if the ByteVector is empty.
	 *
	 * \see size()
	 * \see isNull()
	 */
	bool isEmpty() const;

	/*!
	 * Returns a CRC checksum of the byte vector's data.
	 */
	uint checksum() const;

	/*!
	 * Converts the first 4 bytes of the vector to an unsigned integer.
	 *
	 * If \a mostSignificantByteFirst is true this will operate left to right
	 * evaluating the integer.  For example if \a mostSignificantByteFirst is
	 * true then $00 $00 $00 $01 == 0x00000001 == 1, if false, $01 00 00 00 ==
	 * 0x01000000 == 1.
	 *
	 * \see fromUInt()
	 */
	uint toUInt(bool mostSignificantByteFirst = true) const;

	/*!
	 * Converts the first 2 bytes of the vector to a short.
	 *
	 * If \a mostSignificantByteFirst is true this will operate left to right
	 * evaluating the integer.  For example if \a mostSignificantByteFirst is
	 * true then $00 $01 == 0x0001 == 1, if false, $01 00 == 0x01000000 == 1.
	 *
	 * \see fromShort()
	 */
	short toShort(bool mostSignificantByteFirst = true) const;

	/*!
	 * Converts the first 2 bytes of the vector to a unsigned short.
	 *
	 * If \a mostSignificantByteFirst is true this will operate left to right
	 * evaluating the integer.  For example if \a mostSignificantByteFirst is
	 * true then $00 $01 == 0x0001 == 1, if false, $01 00 == 0x01000000 == 1.
	 *
	 * \see fromShort()
	 */
	unsigned short toUShort(bool mostSignificantByteFirst = true) const;

	/*!
	 * Converts the first 8 bytes of the vector to a (signed) long long.
	 *
	 * If \a mostSignificantByteFirst is true this will operate left to right
	 * evaluating the integer.  For example if \a mostSignificantByteFirst is
	 * true then $00 00 00 00 00 00 00 01 == 0x0000000000000001 == 1,
	 * if false, $01 00 00 00 00 00 00 00 == 0x0100000000000000 == 1.
	 *
	 * \see fromUInt()
	 */
	long long toLongLong(bool mostSignificantByteFirst = true) const;

	/*!
	 * Creates a 4 byte ByteVector based on \a value.  If
	 * \a mostSignificantByteFirst is true, then this will operate left to right
	 * in building the ByteVector.  For example if \a mostSignificantByteFirst is
	 * true then $00 00 00 01 == 0x00000001 == 1, if false, $01 00 00 00 ==
	 * 0x01000000 == 1.
	 *
	 * \see toUInt()
	 */
	static ByteVector fromUInt(uint value, bool mostSignificantByteFirst = true);

	/*!
	 * Creates a 2 byte ByteVector based on \a value.  If
	 * \a mostSignificantByteFirst is true, then this will operate left to right
	 * in building the ByteVector.  For example if \a mostSignificantByteFirst is
	 * true then $00 01 == 0x0001 == 1, if false, $01 00 == 0x0100 == 1.
	 *
	 * \see toShort()
	 */
	static ByteVector fromShort(short value, bool mostSignificantByteFirst = true);

	/*!
	 * Creates a 8 byte ByteVector based on \a value.  If
	 * \a mostSignificantByteFirst is true, then this will operate left to right
	 * in building the ByteVector.  For example if \a mostSignificantByteFirst is
	 * true then $00 00 00 01 == 0x0000000000000001 == 1, if false,
	 * $01 00 00 00 00 00 00 00 == 0x0100000000000000 == 1.
	 *
	 * \see toLongLong()
	 */
	static ByteVector fromLongLong(long long value, bool mostSignificantByteFirst = true);

	/*!
	 * Returns a ByteVector based on the CString \a s.
	 */
	static ByteVector fromCString(const char *s, uint length = 0xffffffff);

	/*!
	 * Returns a const refernence to the byte at \a index.
	 */
	const char &operator[](int index) const;

	/*!
	 * Returns a reference to the byte at \a index.
	 */
	char &operator[](int index);

	/*!
	 * Returns true if this ByteVector and \a v are equal.
	 */
	bool operator==(const ByteVector &v) const;

	/*!
	 * Returns true if this ByteVector and \a v are not equal.
	 */
	bool operator!=(const ByteVector &v) const;

	/*!
	 * Returns true if this ByteVector and the null terminated C string \a s
	 * contain the same data.
	 */
	bool operator==(const char *s) const;

	/*!
	 * Returns true if this ByteVector and the null terminated C string \a s
	 * do not contain the same data.
	 */
	bool operator!=(const char *s) const;

	/*!
	 * Returns true if this ByteVector is less than \a v.  The value of the
	 * vectors is determined by evaluating the character from left to right, and
	 * in the event one vector is a superset of the other, the size is used.
	 */
	bool operator<(const ByteVector &v) const;

	/*!
	 * Returns true if this ByteVector is greater than \a v.
	 */
	bool operator>(const ByteVector &v) const;

	/*!
	 * Returns a vector that is \a v appended to this vector.
	 */
	ByteVector operator+(const ByteVector &v) const;

	/*!
	 * Copies ByteVector \a v.
	 */
	ByteVector &operator=(const ByteVector &v);

	/*!
	 * Copies ByteVector \a v.
	 */
	ByteVector &operator=(char c);

	/*!
	 * Copies ByteVector \a v.
	 */
	ByteVector &operator=(const char *data);

	/*!
	 * A static, empty ByteVector which is convenient and fast (since returning
	 * an empty or "null" value does not require instantiating a new ByteVector).
	 */
	static ByteVector null;

	/*!
	 * Returns a hex-encoded copy of the byte vector.
	 */
	ByteVector toHex() const;

  protected:
	/*
	 * If this ByteVector is being shared via implicit sharing, do a deep copy
	 * of the data and separate from the shared members.  This should be called
	 * by all non-const subclass members.
	 */
	void detach();

  private:
	class ByteVectorPrivate;
	ByteVectorPrivate *d;
  };

}

/*!
 * \relates TagLib::ByteVector
 * Streams the ByteVector \a v to the output stream \a s.
 */
TAGLIB_EXPORT std::ostream &operator<<(std::ostream &s, const TagLib::ByteVector &v);

#endif

/*** End of inlined file: tbytevector.h ***/

#include <string>
#include <iostream>

/*!
 * \relates TagLib::String
 *
 * Converts a QString to a TagLib::String without a requirement to link to Qt.
 *
 * \note consider conversion via usual char-by-char for loop to avoid UTF16->UTF8->UTF16
 * conversion happening in the background
 */
#define QStringToTString(s) TagLib::String(s.utf8().data(), TagLib::String::UTF8)

/*!
 * \relates TagLib::String
 *
 * Converts a TagLib::String to a QString without a requirement to link to Qt.
 *
 * \note consider conversion via usual char-by-char for loop to avoid UTF16->UTF8->UTF16
 * conversion happening in the background
 *
 */
#define TStringToQString(s) QString::fromUtf8(s.toCString(true))

namespace TagLib {

  class StringList;

  //! A \e wide string class suitable for unicode.

  /*!
   * This is an implicitly shared \e wide string.  For storage it uses
   * TagLib::wstring, but as this is an <i>implementation detail</i> this of
   * course could change.  Strings are stored internally as UTF-16BE.  (Without
   * the BOM (Byte Order Mark)
   *
   * The use of implicit sharing means that copying a string is cheap, the only
   * \e cost comes into play when the copy is modified.  Prior to that the string
   * just has a pointer to the data of the \e parent String.  This also makes
   * this class suitable as a function return type.
   *
   * In addition to adding implicit sharing, this class keeps track of four
   * possible encodings, which are the four supported by the ID3v2 standard.
   */

  class TAGLIB_EXPORT String
  {
  public:

#ifndef DO_NOT_DOCUMENT
	typedef std::basic_string<wchar>::iterator Iterator;
	typedef std::basic_string<wchar>::const_iterator ConstIterator;
#endif

	/**
	 * The four types of string encodings supported by the ID3v2 specification.
	 * ID3v1 is assumed to be Latin1 and Ogg Vorbis comments use UTF8.
	 */
	enum Type {
	  /*!
	   * IS08859-1, or <i>Latin1</i> encoding.  8 bit characters.
	   */
	  Latin1 = 0,
	  /*!
	   * UTF16 with a <i>byte order mark</i>.  16 bit characters.
	   */
	  UTF16 = 1,
	  /*!
	   * UTF16 <i>big endian</i>.  16 bit characters.  This is the encoding used
	   * internally by TagLib.
	   */
	  UTF16BE = 2,
	  /*!
	   * UTF8 encoding.  Characters are usually 8 bits but can be up to 32.
	   */
	  UTF8 = 3,
	  /*!
	   * UTF16 <i>little endian</i>.  16 bit characters.
	   */
	  UTF16LE = 4
	};

	/*!
	 * Constructs an empty String.
	 */
	String();

	/*!
	 * Make a shallow, implicitly shared, copy of \a s.  Because this is
	 * implicitly shared, this method is lightweight and suitable for
	 * pass-by-value usage.
	 */
	String(const String &s);

	/*!
	 * Makes a deep copy of the data in \a s.
	 *
	 * \note This should only be used with the 8-bit codecs Latin1 and UTF8, when
	 * used with other codecs it will simply print a warning and exit.
	 */
	String(const std::string &s, Type t = Latin1);

	/*!
	 * Makes a deep copy of the data in \a s.
	 */
	String(const wstring &s, Type t = UTF16BE);

	/*!
	 * Makes a deep copy of the data in \a s.
	 */
	String(const wchar_t *s, Type t = UTF16BE);

	/*!
	 * Makes a deep copy of the data in \a c.
	 *
	 * \note This should only be used with the 8-bit codecs Latin1 and UTF8, when
	 * used with other codecs it will simply print a warning and exit.
	 */
	String(char c, Type t = Latin1);

	/*!
	 * Makes a deep copy of the data in \a c.
	 */
	String(wchar_t c, Type t = Latin1);

	/*!
	 * Makes a deep copy of the data in \a s.
	 *
	 * \note This should only be used with the 8-bit codecs Latin1 and UTF8, when
	 * used with other codecs it will simply print a warning and exit.
	 */
	String(const char *s, Type t = Latin1);

	/*!
	 * Makes a deep copy of the data in \a s.
	 *
	 * \note This should only be used with the 8-bit codecs Latin1 and UTF8, when
	 * used with other codecs it will simply print a warning and exit.
	 */
	String(const ByteVector &v, Type t = Latin1);

	/*!
	 * Destroys this String instance.
	 */
	virtual ~String();

	/*!
	 * If \a unicode if false (the default) this will return a \e Latin1 encoded
	 * std::string.  If it is true the returned std::wstring will be UTF-8
	 * encoded.
	 */
	std::string to8Bit(bool unicode = false) const;

	/*!
	 * Returns a wstring version of the TagLib string as a wide string.
	 */
	wstring toWString() const;

	/*!
	 * Creates and returns a C-String based on the data.  This string is still
	 * owned by the String (class) and as such should not be deleted by the user.
	 *
	 * If \a unicode if false (the default) this string will be encoded in
	 * \e Latin1.  If it is true the returned C-String will be UTF-8 encoded.
	 *
	 * This string remains valid until the String instance is destroyed or
	 * another export method is called.
	 *
	 * \warning This however has the side effect that this C-String will remain
	 * in memory <b>in addition to</b> other memory that is consumed by the
	 * String instance.  So, this method should not be used on large strings or
	 * where memory is critical.
	 */
	const char *toCString(bool unicode = false) const;

	/*!
	 * Returns an iterator pointing to the beginning of the string.
	 */
	Iterator begin();

	/*!
	 * Returns a const iterator pointing to the beginning of the string.
	 */
	ConstIterator begin() const;

	/*!
	 * Returns an iterator pointing to the end of the string (the position
	 * after the last character).
	 */
	Iterator end();

	/*!
	 * Returns a const iterator pointing to the end of the string (the position
	 * after the last character).
	 */
	ConstIterator end() const;

	/*!
	 * Finds the first occurrence of pattern \a s in this string starting from
	 * \a offset.  If the pattern is not found, -1 is returned.
	 */
	int find(const String &s, int offset = 0) const;

	/*!
	 * Finds the last occurrence of pattern \a s in this string, searched backwards,
	 * either from the end of the string or starting from \a offset. If the pattern
	 * is not found, -1 is returned.
	 */
	int rfind(const String &s, int offset = -1) const;

	/*!
	 * Splits the string on each occurrence of \a separator.
	 */
	StringList split(const String &separator = " ") const;

	/*!
	 * Returns true if the strings starts with the substring \a s.
	 */
	bool startsWith(const String &s) const;

	/*!
	 * Extract a substring from this string starting at \a position and
	 * continuing for \a n characters.
	 */
	String substr(uint position, uint n = 0xffffffff) const;

	/*!
	 * Append \a s to the current string and return a reference to the current
	 * string.
	 */
	String &append(const String &s);

	/*!
	 * Returns an upper case version of the string.
	 *
	 * \warning This only works for the characters in US-ASCII, i.e. A-Z.
	 */
	String upper() const;

	/*!
	 * Returns the size of the string.
	 */
	uint size() const;

	/*!
	 * Returns the length of the string.  Equivalent to size().
	 */
	uint length() const;

	/*!
	 * Returns true if the string is empty.
	 *
	 * \see isNull()
	 */
	bool isEmpty() const;

	/*!
	 * Returns true if this string is null -- i.e. it is a copy of the
	 * String::null string.
	 *
	 * \note A string can be empty and not null.
	 * \see isEmpty()
	 */
	bool isNull() const;

	/*!
	 * Returns a ByteVector containing the string's data.  If \a t is Latin1 or
	 * UTF8, this will return a vector of 8 bit characters, otherwise it will use
	 * 16 bit characters.
	 */
	ByteVector data(Type t) const;

	/*!
	 * Convert the string to an integer.
	 *
	 * Returns the integer if the conversion was successfull or 0 if the
	 * string does not represent a number.
	 */
	// BIC: merge with the method below
	int toInt() const;

	/*!
	 * Convert the string to an integer.
	 *
	 * If the conversion was successfull, it sets the value of \a *ok to
	 * true and returns the integer. Otherwise it sets \a *ok to false
	 * and the result is undefined.
	 */
	int toInt(bool *ok) const;

	/*!
	 * Returns a string with the leading and trailing whitespace stripped.
	 */
	String stripWhiteSpace() const;

	/*!
	 * Returns true if the file only uses characters required by Latin1.
	 */
	bool isLatin1() const;

	/*!
	 * Returns true if the file only uses characters required by (7-bit) ASCII.
	 */
	bool isAscii() const;

	/*!
	 * Converts the base-10 integer \a n to a string.
	 */
	static String number(int n);

	/*!
	 * Returns a reference to the character at position \a i.
	 */
	wchar &operator[](int i);

	/*!
	 * Returns a const reference to the character at position \a i.
	 */
	const wchar &operator[](int i) const;

	/*!
	 * Compares each character of the String with each character of \a s and
	 * returns true if the strings match.
	 */
	bool operator==(const String &s) const;

	/*!
	 * Compares each character of the String with each character of \a s and
	 * returns false if the strings match.
	 */
	bool operator!=(const String &s) const;

	/*!
	 * Appends \a s to the end of the String.
	 */
	String &operator+=(const String &s);

	/*!
	 * Appends \a s to the end of the String.
	 */
	String &operator+=(const wchar_t* s);

	/*!
	 * Appends \a s to the end of the String.
	 */
	String &operator+=(const char* s);

	/*!
	 * Appends \a s to the end of the String.
	 */
	String &operator+=(wchar_t c);

	/*!
	 * Appends \a c to the end of the String.
	 */
	String &operator+=(char c);

	/*!
	 * Performs a shallow, implicitly shared, copy of \a s, overwriting the
	 * String's current data.
	 */
	String &operator=(const String &s);

	/*!
	 * Performs a deep copy of the data in \a s.
	 */
	String &operator=(const std::string &s);

	/*!
	 * Performs a deep copy of the data in \a s.
	 */
	String &operator=(const wstring &s);

	/*!
	 * Performs a deep copy of the data in \a s.
	 */
	String &operator=(const wchar_t *s);

	/*!
	 * Performs a deep copy of the data in \a s.
	 */
	String &operator=(char c);

	/*!
	 * Performs a deep copy of the data in \a s.
	 */
	String &operator=(wchar_t c);

	/*!
	 * Performs a deep copy of the data in \a s.
	 */
	String &operator=(const char *s);

	/*!
	 * Performs a deep copy of the data in \a v.
	 */
	String &operator=(const ByteVector &v);

	/*!
	 * To be able to use this class in a Map, this operator needed to be
	 * implemented.  Returns true if \a s is less than this string in a bytewise
	 * comparison.
	 */
	bool operator<(const String &s) const;

	/*!
	 * A null string provided for convenience.
	 */
	static String null;

  protected:
	/*!
	 * If this String is being shared via implicit sharing, do a deep copy of the
	 * data and separate from the shared members.  This should be called by all
	 * non-const subclass members.
	 */
	void detach();

  private:
	/*!
	 * This checks to see if the string is in \e UTF-16 (with BOM) or \e UTF-8
	 * format and if so converts it to \e UTF-16BE for internal use.  \e Latin1
	 * does not require conversion since it is a subset of \e UTF-16BE and
	 * \e UTF16-BE requires no conversion since it is used internally.
	 */
	void prepare(Type t);

	class StringPrivate;
	StringPrivate *d;
  };

}

/*!
 * \relates TagLib::String
 *
 * Concatenates \a s1 and \a s2 and returns the result as a string.
 */
TAGLIB_EXPORT const TagLib::String operator+(const TagLib::String &s1, const TagLib::String &s2);

/*!
 * \relates TagLib::String
 *
 * Concatenates \a s1 and \a s2 and returns the result as a string.
 */
TAGLIB_EXPORT const TagLib::String operator+(const char *s1, const TagLib::String &s2);

/*!
 * \relates TagLib::String
 *
 * Concatenates \a s1 and \a s2 and returns the result as a string.
 */
TAGLIB_EXPORT const TagLib::String operator+(const TagLib::String &s1, const char *s2);

/*!
 * \relates TagLib::String
 *
 * Send the string to an output stream.
 */
TAGLIB_EXPORT std::ostream &operator<<(std::ostream &s, const TagLib::String &str);

#endif

/*** End of inlined file: tstring.h ***/

namespace TagLib {

  //! A simple, generic interface to common audio meta data fields

  /*!
   * This is an attempt to abstract away the difference in the meta data formats
   * of various audio codecs and tagging schemes.  As such it is generally a
   * subset of what is available in the specific formats but should be suitable
   * for most applications.  This is meant to compliment the generic APIs found
   * in TagLib::AudioProperties, TagLib::File and TagLib::FileRef.
   */

  class PropertyMap;

  class TAGLIB_EXPORT Tag
  {
  public:

	/*!
	 * Detroys this Tag instance.
	 */
	virtual ~Tag();

	/*!
	 * Exports the tags of the file as dictionary mapping (human readable) tag
	 * names (Strings) to StringLists of tag values.
	 * The default implementation in this class considers only the usual built-in
	 * tags (artist, album, ...) and only one value per key.
	 */
	PropertyMap properties() const;

	/*!
	 * Removes unsupported properties, or a subset of them, from the tag.
	 * The parameter \a properties must contain only entries from
	 * properties().unsupportedData().
	 * BIC: Will become virtual in future releases. Currently the non-virtual
	 * standard implementation of TagLib::Tag does nothing, since there are
	 * no unsupported elements.
	 */
	void removeUnsupportedProperties(const StringList& properties);

	/*!
	 * Sets the tags of this File to those specified in \a properties. This default
	 * implementation sets only the tags for which setter methods exist in this class
	 * (artist, album, ...), and only one value per key; the rest will be contained
	 * in the returned PropertyMap.
	 */
	PropertyMap setProperties(const PropertyMap &properties);

	/*!
	 * Returns the track name; if no track name is present in the tag
	 * String::null will be returned.
	 */
	virtual String title() const = 0;

	/*!
	 * Returns the artist name; if no artist name is present in the tag
	 * String::null will be returned.
	 */
	virtual String artist() const = 0;

	/*!
	 * Returns the album name; if no album name is present in the tag
	 * String::null will be returned.
	 */
	virtual String album() const = 0;

	/*!
	 * Returns the track comment; if no comment is present in the tag
	 * String::null will be returned.
	 */
	virtual String comment() const = 0;

	/*!
	 * Returns the genre name; if no genre is present in the tag String::null
	 * will be returned.
	 */
	virtual String genre() const = 0;

	/*!
	 * Returns the year; if there is no year set, this will return 0.
	 */
	virtual uint year() const = 0;

	/*!
	 * Returns the track number; if there is no track number set, this will
	 * return 0.
	 */
	virtual uint track() const = 0;

	/*!
	 * Sets the title to \a s.  If \a s is String::null then this value will be
	 * cleared.
	 */
	virtual void setTitle(const String &s) = 0;

	/*!
	 * Sets the artist to \a s.  If \a s is String::null then this value will be
	 * cleared.
	 */
	virtual void setArtist(const String &s) = 0;

	/*!
	 * Sets the album to \a s.  If \a s is String::null then this value will be
	 * cleared.
	 */
	virtual void setAlbum(const String &s) = 0;

	/*!
	 * Sets the comment to \a s.  If \a s is String::null then this value will be
	 * cleared.
	 */
	virtual void setComment(const String &s) = 0;

	/*!
	 * Sets the genre to \a s.  If \a s is String::null then this value will be
	 * cleared.  For tag formats that use a fixed set of genres, the appropriate
	 * value will be selected based on a string comparison.  A list of available
	 * genres for those formats should be available in that type's
	 * implementation.
	 */
	virtual void setGenre(const String &s) = 0;

	/*!
	 * Sets the year to \a i.  If \a s is 0 then this value will be cleared.
	 */
	virtual void setYear(uint i) = 0;

	/*!
	 * Sets the track to \a i.  If \a s is 0 then this value will be cleared.
	 */
	virtual void setTrack(uint i) = 0;

	/*!
	 * Returns true if the tag does not contain any data.  This should be
	 * reimplemented in subclasses that provide more than the basic tagging
	 * abilities in this class.
	 */
	virtual bool isEmpty() const;

	/*!
	 * Copies the generic data from one tag to another.
	 *
	 * \note This will no affect any of the lower level details of the tag.  For
	 * instance if any of the tag type specific data (maybe a URL for a band) is
	 * set, this will not modify or copy that.  This just copies using the API
	 * in this class.
	 *
	 * If \a overwrite is true then the values will be unconditionally copied.
	 * If false only empty values will be overwritten.
	 */
	static void duplicate(const Tag *source, Tag *target, bool overwrite = true);

  protected:
	/*!
	 * Construct a Tag.  This is protected since tags should only be instantiated
	 * through subclasses.
	 */
	Tag();

  private:
	Tag(const Tag &);
	Tag &operator=(const Tag &);

	class TagPrivate;
	TagPrivate *d;
  };
}

#endif

/*** End of inlined file: tag.h ***/



/*** Start of inlined file: fileref.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_FILEREF_H
#define TAGLIB_FILEREF_H


/*** Start of inlined file: tfile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_FILE_H
#define TAGLIB_FILE_H


/*** Start of inlined file: tiostream.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_IOSTREAM_H
#define TAGLIB_IOSTREAM_H

namespace TagLib {

#ifdef _WIN32
  class TAGLIB_EXPORT FileName
  {
  public:
	FileName(const wchar_t *name) : m_wname(name) {}
	FileName(const char *name) : m_name(name) {}
	operator const wchar_t *() const { return m_wname.c_str(); }
	operator const char *() const { return m_name.c_str(); }
  private:
	std::string m_name;
	std::wstring m_wname;
  };
#else
  typedef const char *FileName;
#endif

  //! An abstract class that provides operations on a sequence of bytes

  class TAGLIB_EXPORT IOStream
  {
  public:
	/*!
	 * Position in the file used for seeking.
	 */
	enum Position {
	  //! Seek from the beginning of the file.
	  Beginning,
	  //! Seek from the current position in the file.
	  Current,
	  //! Seek from the end of the file.
	  End
	};

	IOStream();

	/*!
	 * Destroys this IOStream instance.
	 */
	virtual ~IOStream();

	/*!
	 * Returns the stream name in the local file system encoding.
	 */
	virtual FileName name() const = 0;

	/*!
	 * Reads a block of size \a length at the current get pointer.
	 */
	virtual ByteVector readBlock(ulong length) = 0;

	/*!
	 * Attempts to write the block \a data at the current get pointer.  If the
	 * file is currently only opened read only -- i.e. readOnly() returns true --
	 * this attempts to reopen the file in read/write mode.
	 *
	 * \note This should be used instead of using the streaming output operator
	 * for a ByteVector.  And even this function is significantly slower than
	 * doing output with a char[].
	 */
	virtual void writeBlock(const ByteVector &data) = 0;

	/*!
	 * Insert \a data at position \a start in the file overwriting \a replace
	 * bytes of the original content.
	 *
	 * \note This method is slow since it requires rewriting all of the file
	 * after the insertion point.
	 */
	virtual void insert(const ByteVector &data, ulong start = 0, ulong replace = 0) = 0;

	/*!
	 * Removes a block of the file starting a \a start and continuing for
	 * \a length bytes.
	 *
	 * \note This method is slow since it involves rewriting all of the file
	 * after the removed portion.
	 */
	virtual void removeBlock(ulong start = 0, ulong length = 0) = 0;

	/*!
	 * Returns true if the file is read only (or if the file can not be opened).
	 */
	virtual bool readOnly() const = 0;

	/*!
	 * Since the file can currently only be opened as an argument to the
	 * constructor (sort-of by design), this returns if that open succeeded.
	 */
	virtual bool isOpen() const = 0;

	/*!
	 * Move the I/O pointer to \a offset in the stream from position \a p.  This
	 * defaults to seeking from the beginning of the stream.
	 *
	 * \see Position
	 */
	virtual void seek(long offset, Position p = Beginning) = 0;

	/*!
	 * Reset the end-of-stream and error flags on the stream.
	 */
	virtual void clear();

	/*!
	 * Returns the current offset within the stream.
	 */
	virtual long tell() const = 0;

	/*!
	 * Returns the length of the stream.
	 */
	virtual long length() = 0;

	/*!
	 * Truncates the stream to a \a length.
	 */
	virtual void truncate(long length) = 0;

  private:
	IOStream(const IOStream &);
	IOStream &operator=(const IOStream &);
  };

}

#endif

/*** End of inlined file: tiostream.h ***/

namespace TagLib {

  class String;
  class Tag;
  class AudioProperties;
  class PropertyMap;

  //! A file class with some useful methods for tag manipulation

  /*!
   * This class is a basic file class with some methods that are particularly
   * useful for tag editors.  It has methods to take advantage of
   * ByteVector and a binary search method for finding patterns in a file.
   */

  class TAGLIB_EXPORT File
  {
  public:
	/*!
	 * Position in the file used for seeking.
	 */
	enum Position {
	  //! Seek from the beginning of the file.
	  Beginning,
	  //! Seek from the current position in the file.
	  Current,
	  //! Seek from the end of the file.
	  End
	};

	/*!
	 * Destroys this File instance.
	 */
	virtual ~File();

	/*!
	 * Returns the file name in the local file system encoding.
	 */
	FileName name() const;

	/*!
	 * Returns a pointer to this file's tag.  This should be reimplemented in
	 * the concrete subclasses.
	 */
	virtual Tag *tag() const = 0;

	/*!
	 * Exports the tags of the file as dictionary mapping (human readable) tag
	 * names (Strings) to StringLists of tag values. Calls the according specialization
	 * in the File subclasses.
	 * For each metadata object of the file that could not be parsed into the PropertyMap
	 * format, the returend map's unsupportedData() list will contain one entry identifying
	 * that object (e.g. the frame type for ID3v2 tags). Use removeUnsupportedProperties()
	 * to remove (a subset of) them.
	 * BIC: Will be made virtual in future releases.
	 */
	PropertyMap properties() const;

	/*!
	 * Removes unsupported properties, or a subset of them, from the file's metadata.
	 * The parameter \a properties must contain only entries from
	 * properties().unsupportedData().
	 * BIC: Will be mad virtual in future releases.
	 */
	void removeUnsupportedProperties(const StringList& properties);

	/*!
	 * Sets the tags of this File to those specified in \a properties. Calls the
	 * according specialization method in the subclasses of File to do the translation
	 * into the format-specific details.
	 * If some value(s) could not be written imported to the specific metadata format,
	 * the returned PropertyMap will contain those value(s). Otherwise it will be empty,
	 * indicating that no problems occured.
	 * BIC: will become pure virtual in the future
	 */
	PropertyMap setProperties(const PropertyMap &properties);
	/*!
	 * Returns a pointer to this file's audio properties.  This should be
	 * reimplemented in the concrete subclasses.  If no audio properties were
	 * read then this will return a null pointer.
	 */
	virtual AudioProperties *audioProperties() const = 0;

	/*!
	 * Save the file and its associated tags.  This should be reimplemented in
	 * the concrete subclasses.  Returns true if the save succeeds.
	 *
	 * \warning On UNIX multiple processes are able to write to the same file at
	 * the same time.  This can result in serious file corruption.  If you are
	 * developing a program that makes use of TagLib from multiple processes you
	 * must insure that you are only doing writes to a particular file from one
	 * of them.
	 */
	virtual bool save() = 0;

	/*!
	 * Reads a block of size \a length at the current get pointer.
	 */
	ByteVector readBlock(ulong length);

	/*!
	 * Attempts to write the block \a data at the current get pointer.  If the
	 * file is currently only opened read only -- i.e. readOnly() returns true --
	 * this attempts to reopen the file in read/write mode.
	 *
	 * \note This should be used instead of using the streaming output operator
	 * for a ByteVector.  And even this function is significantly slower than
	 * doing output with a char[].
	 */
	void writeBlock(const ByteVector &data);

	/*!
	 * Returns the offset in the file that \a pattern occurs at or -1 if it can
	 * not be found.  If \a before is set, the search will only continue until the
	 * pattern \a before is found.  This is useful for tagging purposes to search
	 * for a tag before the synch frame.
	 *
	 * Searching starts at \a fromOffset, which defaults to the beginning of the
	 * file.
	 *
	 * \note This has the practial limitation that \a pattern can not be longer
	 * than the buffer size used by readBlock().  Currently this is 1024 bytes.
	 */
	long find(const ByteVector &pattern,
			  long fromOffset = 0,
			  const ByteVector &before = ByteVector::null);

	/*!
	 * Returns the offset in the file that \a pattern occurs at or -1 if it can
	 * not be found.  If \a before is set, the search will only continue until the
	 * pattern \a before is found.  This is useful for tagging purposes to search
	 * for a tag before the synch frame.
	 *
	 * Searching starts at \a fromOffset and proceeds from the that point to the
	 * beginning of the file and defaults to the end of the file.
	 *
	 * \note This has the practial limitation that \a pattern can not be longer
	 * than the buffer size used by readBlock().  Currently this is 1024 bytes.
	 */
	long rfind(const ByteVector &pattern,
			   long fromOffset = 0,
			   const ByteVector &before = ByteVector::null);

	/*!
	 * Insert \a data at position \a start in the file overwriting \a replace
	 * bytes of the original content.
	 *
	 * \note This method is slow since it requires rewriting all of the file
	 * after the insertion point.
	 */
	void insert(const ByteVector &data, ulong start = 0, ulong replace = 0);

	/*!
	 * Removes a block of the file starting a \a start and continuing for
	 * \a length bytes.
	 *
	 * \note This method is slow since it involves rewriting all of the file
	 * after the removed portion.
	 */
	void removeBlock(ulong start = 0, ulong length = 0);

	/*!
	 * Returns true if the file is read only (or if the file can not be opened).
	 */
	bool readOnly() const;

	/*!
	 * Since the file can currently only be opened as an argument to the
	 * constructor (sort-of by design), this returns if that open succeeded.
	 */
	bool isOpen() const;

	/*!
	 * Returns true if the file is open and readble.
	 */
	bool isValid() const;

	/*!
	 * Move the I/O pointer to \a offset in the file from position \a p.  This
	 * defaults to seeking from the beginning of the file.
	 *
	 * \see Position
	 */
	void seek(long offset, Position p = Beginning);

	/*!
	 * Reset the end-of-file and error flags on the file.
	 */
	void clear();

	/*!
	 * Returns the current offset within the file.
	 */
	long tell() const;

	/*!
	 * Returns the length of the file.
	 */
	long length();

	/*!
	 * Returns true if \a file can be opened for reading.  If the file does not
	 * exist, this will return false.
	 *
	 * \deprecated
	 */
	static bool isReadable(const char *file);

	/*!
	 * Returns true if \a file can be opened for writing.
	 *
	 * \deprecated
	 */
	static bool isWritable(const char *name);

  protected:
	/*!
	 * Construct a File object and opens the \a file.  \a file should be a
	 * be a C-string in the local file system encoding.
	 *
	 * \note Constructor is protected since this class should only be
	 * instantiated through subclasses.
	 */
	File(FileName file);

	/*!
	 * Construct a File object and use the \a stream instance.
	 *
	 * \note Constructor is protected since this class should only be
	 * instantiated through subclasses.
	 */
	File(IOStream *stream);

	/*!
	 * Marks the file as valid or invalid.
	 *
	 * \see isValid()
	 */
	void setValid(bool valid);

	/*!
	 * Truncates the file to a \a length.
	 */
	void truncate(long length);

	/*!
	 * Returns the buffer size that is used for internal buffering.
	 */
	static uint bufferSize();

  private:
	File(const File &);
	File &operator=(const File &);

	class FilePrivate;
	FilePrivate *d;
  };

}

#endif

/*** End of inlined file: tfile.h ***/


/*** Start of inlined file: tstringlist.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_STRINGLIST_H
#define TAGLIB_STRINGLIST_H


/*** Start of inlined file: tlist.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_LIST_H
#define TAGLIB_LIST_H

#include <list>

namespace TagLib {

  //! A generic, implicitly shared list.

  /*!
   * This is basic generic list that's somewhere between a std::list and a
   * QValueList.  This class is implicitly shared.  For example:
   *
   * \code
   *
   * TagLib::List<int> l = someOtherIntList;
   *
   * \endcode
   *
   * The above example is very cheap.  This also makes lists suitable for the
   * return types of functions.  The above example will just copy a pointer rather
   * than copying the data in the list.  When your \e shared list's data changes,
   * only \e then will the data be copied.
   */

  template <class T> class List
  {
  public:
#ifndef DO_NOT_DOCUMENT
	typedef typename std::list<T>::iterator Iterator;
	typedef typename std::list<T>::const_iterator ConstIterator;
#endif

	/*!
	 * Constructs an empty list.
	 */
	List();

	/*!
	 * Make a shallow, implicitly shared, copy of \a l.  Because this is
	 * implicitly shared, this method is lightweight and suitable for
	 * pass-by-value usage.
	 */
	List(const List<T> &l);

	/*!
	 * Destroys this List instance.  If auto deletion is enabled and this list
	 * contains a pointer type all of the memebers are also deleted.
	 */
	virtual ~List();

	/*!
	 * Returns an STL style iterator to the beginning of the list.  See
	 * std::list::const_iterator for the semantics.
	 */
	Iterator begin();

	/*!
	 * Returns an STL style constant iterator to the beginning of the list.  See
	 * std::list::iterator for the semantics.
	 */
	ConstIterator begin() const;

	/*!
	 * Returns an STL style iterator to the end of the list.  See
	 * std::list::iterator for the semantics.
	 */
	Iterator end();

	/*!
	 * Returns an STL style constant iterator to the end of the list.  See
	 * std::list::const_iterator for the semantics.
	 */
	ConstIterator end() const;

	/*!
	 * Inserts a copy of \a value before \a it.
	 */
	Iterator insert(Iterator it, const T &value);

	/*!
	 * Inserts the \a value into the list.  This assumes that the list is
	 * currently sorted.  If \a unique is true then the value will not
	 * be inserted if it is already in the list.
	 */
	List<T> &sortedInsert(const T &value, bool unique = false);

	/*!
	 * Appends \a item to the end of the list and returns a reference to the
	 * list.
	 */
	List<T> &append(const T &item);

	/*!
	 * Appends all of the values in \a l to the end of the list and returns a
	 * reference to the list.
	 */
	List<T> &append(const List<T> &l);

	/*!
	 * Prepends \a item to the beginning list and returns a reference to the
	 * list.
	 */
	List<T> &prepend(const T &item);

	/*!
	 * Prepends all of the items in \a l to the beginning list and returns a
	 * reference to the list.
	 */
	List<T> &prepend(const List<T> &l);

	/*!
	 * Clears the list.  If auto deletion is enabled and this list contains a
	 * pointer type the members are also deleted.
	 *
	 * \see setAutoDelete()
	 */
	List<T> &clear();

	/*!
	 * Returns the number of elements in the list.
	 */
	uint size() const;
	bool isEmpty() const;

	/*!
	 * Find the first occurrence of \a value.
	 */
	Iterator find(const T &value);

	/*!
	 * Find the first occurrence of \a value.
	 */
	ConstIterator find(const T &value) const;

	/*!
	 * Returns true if the list contains \a value.
	 */
	bool contains(const T &value) const;

	/*!
	 * Erase the item at \a it from the list.
	 */
	Iterator erase(Iterator it);

	/*!
	 * Returns a reference to the first item in the list.
	 */
	const T &front() const;

	/*!
	 * Returns a reference to the first item in the list.
	 */
	T &front();

	/*!
	 * Returns a reference to the last item in the list.
	 */
	const T &back() const;

	/*!
	 * Returns a reference to the last item in the list.
	 */
	T &back();

	/*!
	 * Auto delete the members of the list when the last reference to the list
	 * passes out of scope.  This will have no effect on lists which do not
	 * contain a pointer type.
	 *
	 * \note This relies on partial template instantiation -- most modern C++
	 * compilers should now support this.
	 */
	void setAutoDelete(bool autoDelete);

	/*!
	 * Returns a reference to item \a i in the list.
	 *
	 * \warning This method is slow.  Use iterators to loop through the list.
	 */
	T &operator[](uint i);

	/*!
	 * Returns a const reference to item \a i in the list.
	 *
	 * \warning This method is slow.  Use iterators to loop through the list.
	 */
	const T &operator[](uint i) const;

	/*!
	 * Make a shallow, implicitly shared, copy of \a l.  Because this is
	 * implicitly shared, this method is lightweight and suitable for
	 * pass-by-value usage.
	 */
	List<T> &operator=(const List<T> &l);

	/*!
	 * Compares this list with \a l and returns true if all of the elements are
	 * the same.
	 */
	bool operator==(const List<T> &l) const;

	/*!
	 * Compares this list with \a l and returns true if the lists differ.
	 */
	bool operator!=(const List<T> &l) const;

  protected:
	/*
	 * If this List is being shared via implicit sharing, do a deep copy of the
	 * data and separate from the shared members.  This should be called by all
	 * non-const subclass members.
	 */
	void detach();

  private:
#ifndef DO_NOT_DOCUMENT
	template <class TP> class ListPrivate;
	ListPrivate<T> *d;
#endif
  };

}

// Since GCC doesn't support the "export" keyword, we have to include the
// implementation.


/*** Start of inlined file: tlist.tcc ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#include <algorithm>

namespace TagLib {

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

// The functionality of List<T>::setAutoDelete() is implemented here partial
// template specialization.  This is implemented in such a way that calling
// setAutoDelete() on non-pointer types will simply have no effect.

// A base for the generic and specialized private class types.  New
// non-templatized members should be added here.

class ListPrivateBase : public RefCounter
{
public:
  ListPrivateBase() : autoDelete(false) {}
  bool autoDelete;
};

// A generic implementation

template <class T>
template <class TP> class List<T>::ListPrivate  : public ListPrivateBase
{
public:
  ListPrivate() : ListPrivateBase() {}
  ListPrivate(const std::list<TP> &l) : ListPrivateBase(), list(l) {}
  void clear() {
	list.clear();
  }
  std::list<TP> list;
};

// A partial specialization for all pointer types that implements the
// setAutoDelete() functionality.

template <class T>
template <class TP> class List<T>::ListPrivate<TP *>  : public ListPrivateBase
{
public:
  ListPrivate() : ListPrivateBase() {}
  ListPrivate(const std::list<TP *> &l) : ListPrivateBase(), list(l) {}
  ~ListPrivate() {
	clear();
  }
  void clear() {
	if(autoDelete) {
	  typename std::list<TP *>::const_iterator it = list.begin();
	  for(; it != list.end(); ++it)
		delete *it;
	}
	list.clear();
  }
  std::list<TP *> list;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

template <class T>
List<T>::List()
{
  d = new ListPrivate<T>;
}

template <class T>
List<T>::List(const List<T> &l) : d(l.d)
{
  d->ref();
}

template <class T>
List<T>::~List()
{
  if(d->deref())
	delete d;
}

template <class T>
typename List<T>::Iterator List<T>::begin()
{
  detach();
  return d->list.begin();
}

template <class T>
typename List<T>::ConstIterator List<T>::begin() const
{
  return d->list.begin();
}

template <class T>
typename List<T>::Iterator List<T>::end()
{
  detach();
  return d->list.end();
}

template <class T>
typename List<T>::ConstIterator List<T>::end() const
{
  return d->list.end();
}

template <class T>
typename List<T>::Iterator List<T>::insert(Iterator it, const T &item)
{
  detach();
  return d->list.insert(it, item);
}

template <class T>
List<T> &List<T>::sortedInsert(const T &value, bool unique)
{
  detach();
  Iterator it = begin();
  while(it != end() && *it < value)
	++it;
  if(unique && it != end() && *it == value)
	return *this;
  insert(it, value);
  return *this;
}

template <class T>
List<T> &List<T>::append(const T &item)
{
  detach();
  d->list.push_back(item);
  return *this;
}

template <class T>
List<T> &List<T>::append(const List<T> &l)
{
  detach();
  d->list.insert(d->list.end(), l.begin(), l.end());
  return *this;
}

template <class T>
List<T> &List<T>::prepend(const T &item)
{
  detach();
  d->list.push_front(item);
  return *this;
}

template <class T>
List<T> &List<T>::prepend(const List<T> &l)
{
  detach();
  d->list.insert(d->list.begin(), l.begin(), l.end());
  return *this;
}

template <class T>
List<T> &List<T>::clear()
{
  detach();
  d->clear();
  return *this;
}

template <class T>
TagLib::uint List<T>::size() const
{
  return d->list.size();
}

template <class T>
bool List<T>::isEmpty() const
{
  return d->list.empty();
}

template <class T>
typename List<T>::Iterator List<T>::find(const T &value)
{
  return std::find(d->list.begin(), d->list.end(), value);
}

template <class T>
typename List<T>::ConstIterator List<T>::find(const T &value) const
{
  return std::find(d->list.begin(), d->list.end(), value);
}

template <class T>
bool List<T>::contains(const T &value) const
{
  return std::find(d->list.begin(), d->list.end(), value) != d->list.end();
}

template <class T>
typename List<T>::Iterator List<T>::erase(Iterator it)
{
  return d->list.erase(it);
}

template <class T>
const T &List<T>::front() const
{
  return d->list.front();
}

template <class T>
T &List<T>::front()
{
  detach();
  return d->list.front();
}

template <class T>
const T &List<T>::back() const
{
  return d->list.back();
}

template <class T>
void List<T>::setAutoDelete(bool autoDelete)
{
  d->autoDelete = autoDelete;
}

template <class T>
T &List<T>::back()
{
  detach();
  return d->list.back();
}

template <class T>
T &List<T>::operator[](uint i)
{
  Iterator it = d->list.begin();

  for(uint j = 0; j < i; j++)
	++it;

  return *it;
}

template <class T>
const T &List<T>::operator[](uint i) const
{
  ConstIterator it = d->list.begin();

  for(uint j = 0; j < i; j++)
	++it;

  return *it;
}

template <class T>
List<T> &List<T>::operator=(const List<T> &l)
{
  if(&l == this)
	return *this;

  if(d->deref())
	delete d;
  d = l.d;
  d->ref();
  return *this;
}

template <class T>
bool List<T>::operator==(const List<T> &l) const
{
  return d->list == l.d->list;
}

template <class T>
bool List<T>::operator!=(const List<T> &l) const
{
  return d->list != l.d->list;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

template <class T>
void List<T>::detach()
{
  if(d->count() > 1) {
	d->deref();
	d = new ListPrivate<T>(d->list);
  }
}

} // namespace TagLib

/*** End of inlined file: tlist.tcc ***/

#endif

/*** End of inlined file: tlist.h ***/


/*** Start of inlined file: tbytevectorlist.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_BYTEVECTORLIST_H
#define TAGLIB_BYTEVECTORLIST_H

namespace TagLib {

  //! A list of ByteVectors

  /*!
   * A List specialization with some handy features useful for ByteVectors.
   */

  class TAGLIB_EXPORT ByteVectorList : public List<ByteVector>
  {
  public:

	/*!
	 * Construct an empty ByteVectorList.
	 */
	ByteVectorList();

	/*!
	 * Destroys this ByteVectorList instance.
	 */
	virtual ~ByteVectorList();

	/*!
	 * Make a shallow, implicitly shared, copy of \a l.  Because this is
	 * implicitly shared, this method is lightweight and suitable for
	 * pass-by-value usage.
	 */
	ByteVectorList(const ByteVectorList &l);

	/*!
	 * Convert the ByteVectorList to a ByteVector separated by \a separator.  By
	 * default a space is used.
	 */
	ByteVector toByteVector(const ByteVector &separator = " ") const;

	/*!
	 * Splits the ByteVector \a v into several strings at \a pattern.  This will
	 * not include the pattern in the returned ByteVectors.
	 */
	static ByteVectorList split(const ByteVector &v, const ByteVector &pattern,
								int byteAlign = 1);
	/*!
	 * Splits the ByteVector \a v into several strings at \a pattern.  This will
	 * not include the pattern in the returned ByteVectors.  \a max is the
	 * maximum number of entries that will be separated.  If \a max for instance
	 * is 2 then a maximum of 1 match will be found and the vector will be split
	 * on that match.
	 */
	// BIC: merge with the function above
	static ByteVectorList split(const ByteVector &v, const ByteVector &pattern,
								int byteAlign, int max);
  private:
	class ByteVectorListPrivate;
	ByteVectorListPrivate *d;
  };

}

#endif

/*** End of inlined file: tbytevectorlist.h ***/

#include <iostream>

namespace TagLib {

  //! A list of strings

  /*!
   * This is a spcialization of the List class with some members convention for
   * string operations.
   */

  class TAGLIB_EXPORT StringList : public List<String>
  {
  public:

	/*!
	 * Constructs an empty StringList.
	 */
	StringList();

	/*!
	 * Make a shallow, implicitly shared, copy of \a l.  Because this is
	 * implicitly shared, this method is lightweight and suitable for
	 * pass-by-value usage.
	 */
	StringList(const StringList &l);

	/*!
	 * Constructs a StringList with \a s as a member.
	 */
	StringList(const String &s);

	/*!
	 * Makes a deep copy of the data in \a vl.
	 *
	 * \note This should only be used with the 8-bit codecs Latin1 and UTF8, when
	 * used with other codecs it will simply print a warning and exit.
	 */
	StringList(const ByteVectorList &vl, String::Type t = String::Latin1);

	/*!
	 * Destroys this StringList instance.
	 */
	virtual ~StringList();

	/*!
	 * Concatenate the list of strings into one string separated by \a separator.
	 */
	String toString(const String &separator = " ") const;

	/*!
	 * Appends \a s to the end of the list and returns a reference to the
	 * list.
	 */
	StringList &append(const String &s);

	/*!
	 * Appends all of the values in \a l to the end of the list and returns a
	 * reference to the list.
	 */
	StringList &append(const StringList &l);

	/*!
	 * Splits the String \a s into several strings at \a pattern.  This will not include
	 * the pattern in the returned strings.
	 */
	static StringList split(const String &s, const String &pattern);

  private:
	class StringListPrivate;
	StringListPrivate *d;
  };

}

/*!
 * \related TagLib::StringList
 * Send the StringList to an output stream.
 */
std::ostream &operator<<(std::ostream &s, const TagLib::StringList &l);

#endif

/*** End of inlined file: tstringlist.h ***/


/*** Start of inlined file: audioproperties.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_AUDIOPROPERTIES_H
#define TAGLIB_AUDIOPROPERTIES_H

namespace TagLib {

  //! A simple, abstract interface to common audio properties

  /*!
   * The values here are common to most audio formats.  For more specific, codec
   * dependant values, please see see the subclasses APIs.  This is meant to
   * compliment the TagLib::File and TagLib::Tag APIs in providing a simple
   * interface that is sufficient for most applications.
   */

  class TAGLIB_EXPORT AudioProperties
  {
  public:

	/*!
	 * Reading audio properties from a file can sometimes be very time consuming
	 * and for the most accurate results can often involve reading the entire
	 * file.  Because in many situations speed is critical or the accuracy of the
	 * values is not particularly important this allows the level of desired
	 * accuracy to be set.
	 */
	enum ReadStyle {
	  //! Read as little of the file as possible
	  Fast,
	  //! Read more of the file and make better values guesses
	  Average,
	  //! Read as much of the file as needed to report accurate values
	  Accurate
	};

	/*!
	 * Destroys this AudioProperties instance.
	 */
	virtual ~AudioProperties();

	/*!
	 * Returns the length of the file in seconds.
	 */
	virtual int length() const = 0;

	/*!
	 * Returns the most appropriate bit rate for the file in kb/s.  For constant
	 * bitrate formats this is simply the bitrate of the file.  For variable
	 * bitrate formats this is either the average or nominal bitrate.
	 */
	virtual int bitrate() const = 0;

	/*!
	 * Returns the sample rate in Hz.
	 */
	virtual int sampleRate() const = 0;

	/*!
	 * Returns the number of audio channels.
	 */
	virtual int channels() const = 0;

  protected:

	/*!
	 * Construct an audio properties instance.  This is protected as this class
	 * should not be instantiated directly, but should be instantiated via its
	 * subclasses and can be fetched from the FileRef or File APIs.
	 *
	 * \see ReadStyle
	 */
	AudioProperties(ReadStyle style);

  private:
	AudioProperties(const AudioProperties &);
	AudioProperties &operator=(const AudioProperties &);

	class AudioPropertiesPrivate;
	AudioPropertiesPrivate *d;
  };

}

#endif

/*** End of inlined file: audioproperties.h ***/

namespace TagLib {

  class Tag;

  //! This class provides a simple abstraction for creating and handling files

  /*!
   * FileRef exists to provide a minimal, generic and value-based wrapper around
   * a File.  It is lightweight and implicitly shared, and as such suitable for
   * pass-by-value use.  This hides some of the uglier details of TagLib::File
   * and the non-generic portions of the concrete file implementations.
   *
   * This class is useful in a "simple usage" situation where it is desirable
   * to be able to get and set some of the tag information that is similar
   * across file types.
   *
   * Also note that it is probably a good idea to plug this into your mime
   * type system rather than using the constructor that accepts a file name using
   * the FileTypeResolver.
   *
   * \see FileTypeResolver
   * \see addFileTypeResolver()
   */

  class TAGLIB_EXPORT FileRef
  {
  public:

  //! A class for pluggable file type resolution.

  /*!
   * This class is used to add extend TagLib's very basic file name based file
   * type resolution.
   *
   * This can be accomplished with:
   *
   * \code
   *
   * class MyFileTypeResolver : FileTypeResolver
   * {
   *   TagLib::File *createFile(TagLib::FileName *fileName, bool, AudioProperties::ReadStyle)
   *   {
   *     if(someCheckForAnMP3File(fileName))
   *       return new TagLib::MPEG::File(fileName);
   *     return 0;
   *   }
   * }
   *
   * FileRef::addFileTypeResolver(new MyFileTypeResolver);
   *
   * \endcode
   *
   * Naturally a less contrived example would be slightly more complex.  This
   * can be used to plug in mime-type detection systems or to add new file types
   * to TagLib.
   */

	class TAGLIB_EXPORT FileTypeResolver
	{
	  TAGLIB_IGNORE_MISSING_DESTRUCTOR
	public:
	  /*!
	   * This method must be overridden to provide an additional file type
	   * resolver.  If the resolver is able to determine the file type it should
	   * return a valid File object; if not it should return 0.
	   *
	   * \note The created file is then owned by the FileRef and should not be
	   * deleted.  Deletion will happen automatically when the FileRef passes
	   * out of scope.
	   */
	  virtual File *createFile(FileName fileName,
							   bool readAudioProperties = true,
							   AudioProperties::ReadStyle
							   audioPropertiesStyle = AudioProperties::Average) const = 0;
	};

	/*!
	 * Creates a null FileRef.
	 */
	FileRef();

	/*!
	 * Create a FileRef from \a fileName.  If \a readAudioProperties is true then
	 * the audio properties will be read using \a audioPropertiesStyle.  If
	 * \a readAudioProperties is false then \a audioPropertiesStyle will be
	 * ignored.
	 *
	 * Also see the note in the class documentation about why you may not want to
	 * use this method in your application.
	 */
	explicit FileRef(FileName fileName,
					 bool readAudioProperties = true,
					 AudioProperties::ReadStyle
					 audioPropertiesStyle = AudioProperties::Average);

	/*!
	 * Contruct a FileRef using \a file.  The FileRef now takes ownership of the
	 * pointer and will delete the File when it passes out of scope.
	 */
	explicit FileRef(File *file);

	/*!
	 * Make a copy of \a ref.
	 */
	FileRef(const FileRef &ref);

	/*!
	 * Destroys this FileRef instance.
	 */
	virtual ~FileRef();

	/*!
	 * Returns a pointer to represented file's tag.
	 *
	 * \warning This pointer will become invalid when this FileRef and all
	 * copies pass out of scope.
	 *
	 * \warning Do not cast it to any subclasses of \class Tag.
	 * Use tag returning methods of appropriate subclasses of \class File instead.
	 *
	 * \see File::tag()
	 */
	Tag *tag() const;

	/*!
	 * Returns the audio properties for this FileRef.  If no audio properties
	 * were read then this will returns a null pointer.
	 */
	AudioProperties *audioProperties() const;

	/*!
	 * Returns a pointer to the file represented by this handler class.
	 *
	 * As a general rule this call should be avoided since if you need to work
	 * with file objects directly, you are probably better served instantiating
	 * the File subclasses (i.e. MPEG::File) manually and working with their APIs.
	 *
	 * This <i>handle</i> exists to provide a minimal, generic and value-based
	 * wrapper around a File.  Accessing the file directly generally indicates
	 * a moving away from this simplicity (and into things beyond the scope of
	 * FileRef).
	 *
	 * \warning This pointer will become invalid when this FileRef and all
	 * copies pass out of scope.
	 */
	File *file() const;

	/*!
	 * Saves the file.  Returns true on success.
	 */
	bool save();

	/*!
	 * Adds a FileTypeResolver to the list of those used by TagLib.  Each
	 * additional FileTypeResolver is added to the front of a list of resolvers
	 * that are tried.  If the FileTypeResolver returns zero the next resolver
	 * is tried.
	 *
	 * Returns a pointer to the added resolver (the same one that's passed in --
	 * this is mostly so that static inialializers have something to use for
	 * assignment).
	 *
	 * \see FileTypeResolver
	 */
	static const FileTypeResolver *addFileTypeResolver(const FileTypeResolver *resolver);

	/*!
	 * As is mentioned elsewhere in this class's documentation, the default file
	 * type resolution code provided by TagLib only works by comparing file
	 * extensions.
	 *
	 * This method returns the list of file extensions that are used by default.
	 *
	 * The extensions are all returned in lowercase, though the comparison used
	 * by TagLib for resolution is case-insensitive.
	 *
	 * \note This does not account for any additional file type resolvers that
	 * are plugged in.  Also note that this is not intended to replace a propper
	 * mime-type resolution system, but is just here for reference.
	 *
	 * \see FileTypeResolver
	 */
	static StringList defaultFileExtensions();

	/*!
	 * Returns true if the file (and as such other pointers) are null.
	 */
	bool isNull() const;

	/*!
	 * Assign the file pointed to by \a ref to this FileRef.
	 */
	FileRef &operator=(const FileRef &ref);

	/*!
	 * Returns true if this FileRef and \a ref point to the same File object.
	 */
	bool operator==(const FileRef &ref) const;

	/*!
	 * Returns true if this FileRef and \a ref do not point to the same File
	 * object.
	 */
	bool operator!=(const FileRef &ref) const;

	/*!
	 * A simple implementation of file type guessing.  If \a readAudioProperties
	 * is true then the audio properties will be read using
	 * \a audioPropertiesStyle.  If \a readAudioProperties is false then
	 * \a audioPropertiesStyle will be ignored.
	 *
	 * \note You generally shouldn't use this method, but instead the constructor
	 * directly.
	 *
	 * \deprecated
	 */
	static File *create(FileName fileName,
						bool readAudioProperties = true,
						AudioProperties::ReadStyle audioPropertiesStyle = AudioProperties::Average);

  private:
	class FileRefPrivate;
	FileRefPrivate *d;
  };

} // namespace TagLib

#endif

/*** End of inlined file: fileref.h ***/

#ifndef TAGLIB_NO_CONFIG
//#include "${CMAKE_BINARY_DIR}/taglib_config.h"
#endif

//#include "toolkit/tlist.tcc" // included by tlist.h


/*** Start of inlined file: tbytevectorstream.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_BYTEVECTORSTREAM_H
#define TAGLIB_BYTEVECTORSTREAM_H

namespace TagLib {

  class String;
  class Tag;
  class AudioProperties;

  //! In-memory Stream class using ByteVector for its storage.

  class TAGLIB_EXPORT ByteVectorStream : public IOStream
  {
  public:
	/*!
	 * Construct a File object and opens the \a file.  \a file should be a
	 * be a C-string in the local file system encoding.
	 */
	ByteVectorStream(const ByteVector &data);

	/*!
	 * Destroys this ByteVectorStream instance.
	 */
	virtual ~ByteVectorStream();

	/*!
	 * Returns the file name in the local file system encoding.
	 */
	FileName name() const;

	/*!
	 * Reads a block of size \a length at the current get pointer.
	 */
	ByteVector readBlock(ulong length);

	/*!
	 * Attempts to write the block \a data at the current get pointer.  If the
	 * file is currently only opened read only -- i.e. readOnly() returns true --
	 * this attempts to reopen the file in read/write mode.
	 *
	 * \note This should be used instead of using the streaming output operator
	 * for a ByteVector.  And even this function is significantly slower than
	 * doing output with a char[].
	 */
	void writeBlock(const ByteVector &data);

	/*!
	 * Insert \a data at position \a start in the file overwriting \a replace
	 * bytes of the original content.
	 *
	 * \note This method is slow since it requires rewriting all of the file
	 * after the insertion point.
	 */
	void insert(const ByteVector &data, ulong start = 0, ulong replace = 0);

	/*!
	 * Removes a block of the file starting a \a start and continuing for
	 * \a length bytes.
	 *
	 * \note This method is slow since it involves rewriting all of the file
	 * after the removed portion.
	 */
	void removeBlock(ulong start = 0, ulong length = 0);

	/*!
	 * Returns true if the file is read only (or if the file can not be opened).
	 */
	bool readOnly() const;

	/*!
	 * Since the file can currently only be opened as an argument to the
	 * constructor (sort-of by design), this returns if that open succeeded.
	 */
	bool isOpen() const;

	/*!
	 * Move the I/O pointer to \a offset in the file from position \a p.  This
	 * defaults to seeking from the beginning of the file.
	 *
	 * \see Position
	 */
	void seek(long offset, Position p = Beginning);

	/*!
	 * Reset the end-of-file and error flags on the file.
	 */
	void clear();

	/*!
	 * Returns the current offset within the file.
	 */
	long tell() const;

	/*!
	 * Returns the length of the file.
	 */
	long length();

	/*!
	 * Truncates the file to a \a length.
	 */
	void truncate(long length);

	ByteVector *data();

  protected:

  private:
	class ByteVectorStreamPrivate;
	ByteVectorStreamPrivate *d;
  };

}

#endif

/*** End of inlined file: tbytevectorstream.h ***/


/*** Start of inlined file: tfilestream.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_FILESTREAM_H
#define TAGLIB_FILESTREAM_H

namespace TagLib {

  class String;
  class Tag;
  class AudioProperties;

  //! A file class with some useful methods for tag manipulation

  /*!
   * This class is a basic file class with some methods that are particularly
   * useful for tag editors.  It has methods to take advantage of
   * ByteVector and a binary search method for finding patterns in a file.
   */

  class TAGLIB_EXPORT FileStream : public IOStream
  {
  public:
	/*!
	 * Construct a File object and opens the \a file.  \a file should be a
	 * be a C-string in the local file system encoding.
	 */
	FileStream(FileName file, bool openReadOnly = false);

	/*!
	 * Destroys this FileStream instance.
	 */
	virtual ~FileStream();

	/*!
	 * Returns the file name in the local file system encoding.
	 */
	FileName name() const;

	/*!
	 * Reads a block of size \a length at the current get pointer.
	 */
	ByteVector readBlock(ulong length);

	/*!
	 * Attempts to write the block \a data at the current get pointer.  If the
	 * file is currently only opened read only -- i.e. readOnly() returns true --
	 * this attempts to reopen the file in read/write mode.
	 *
	 * \note This should be used instead of using the streaming output operator
	 * for a ByteVector.  And even this function is significantly slower than
	 * doing output with a char[].
	 */
	void writeBlock(const ByteVector &data);

	/*!
	 * Insert \a data at position \a start in the file overwriting \a replace
	 * bytes of the original content.
	 *
	 * \note This method is slow since it requires rewriting all of the file
	 * after the insertion point.
	 */
	void insert(const ByteVector &data, ulong start = 0, ulong replace = 0);

	/*!
	 * Removes a block of the file starting a \a start and continuing for
	 * \a length bytes.
	 *
	 * \note This method is slow since it involves rewriting all of the file
	 * after the removed portion.
	 */
	void removeBlock(ulong start = 0, ulong length = 0);

	/*!
	 * Returns true if the file is read only (or if the file can not be opened).
	 */
	bool readOnly() const;

	/*!
	 * Since the file can currently only be opened as an argument to the
	 * constructor (sort-of by design), this returns if that open succeeded.
	 */
	bool isOpen() const;

	/*!
	 * Move the I/O pointer to \a offset in the file from position \a p.  This
	 * defaults to seeking from the beginning of the file.
	 *
	 * \see Position
	 */
	void seek(long offset, Position p = Beginning);

	/*!
	 * Reset the end-of-file and error flags on the file.
	 */
	void clear();

	/*!
	 * Returns the current offset within the file.
	 */
	long tell() const;

	/*!
	 * Returns the length of the file.
	 */
	long length();

	/*!
	 * Truncates the file to a \a length.
	 */
	void truncate(long length);

  protected:

	/*!
	 * Returns the buffer size that is used for internal buffering.
	 */
	static uint bufferSize();

  private:
	class FileStreamPrivate;
	FileStreamPrivate *d;
  };

}

#endif

/*** End of inlined file: tfilestream.h ***/


/*** Start of inlined file: tmap.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_MAP_H
#define TAGLIB_MAP_H

#include <map>

namespace TagLib {

  //! A generic, implicitly shared map.

  /*!
   * This implements a standard map container that associates a key with a value
   * and has fast key-based lookups.  This map is also implicitly shared making
   * it suitable for pass-by-value usage.
   */

  template <class Key, class T> class Map
  {
  public:
#ifndef DO_NOT_DOCUMENT
#ifdef WANT_CLASS_INSTANTIATION_OF_MAP
	// Some STL implementations get snippy over the use of the
	// class keyword to distinguish different templates; Sun Studio
	// in particular finds multiple specializations in certain rare
	// cases and complains about that. GCC doesn't seem to mind,
	// and uses the typedefs further below without the class keyword.
	// Not all the specializations of Map can use the class keyword
	// (when T is not actually a class type), so don't apply this
	// generally.
	typedef typename std::map<class Key, class T>::iterator Iterator;
	typedef typename std::map<class Key, class T>::const_iterator ConstIterator;
#else
	typedef typename std::map<Key, T>::iterator Iterator;
	typedef typename std::map<Key, T>::const_iterator ConstIterator;
#endif
#endif

	/*!
	 * Constructs an empty Map.
	 */
	Map();

	/*!
	 * Make a shallow, implicitly shared, copy of \a m.  Because this is
	 * implicitly shared, this method is lightweight and suitable for
	 * pass-by-value usage.
	 */
	Map(const Map<Key, T> &m);

	/*!
	 * Destroys this instance of the Map.
	 */
	virtual ~Map();

	/*!
	 * Returns an STL style iterator to the beginning of the map.  See
	 * std::map::iterator for the semantics.
	 */
	Iterator begin();

	/*!
	 * Returns an STL style iterator to the beginning of the map.  See
	 * std::map::const_iterator for the semantics.
	 */
	ConstIterator begin() const;

	/*!
	 * Returns an STL style iterator to the end of the map.  See
	 * std::map::iterator for the semantics.
	 */
	Iterator end();

	/*!
	 * Returns an STL style iterator to the end of the map.  See
	 * std::map::const_iterator for the semantics.
	 */
	ConstIterator end() const;

	/*!
	 * Inserts \a value under \a key in the map.  If a value for \a key already
	 * exists it will be overwritten.
	 */
	Map<Key, T> &insert(const Key &key, const T &value);

	/*!
	 * Removes all of the elements from elements from the map.  This however
	 * will not delete pointers if the mapped type is a pointer type.
	 */
	Map<Key, T> &clear();

	/*!
	 * The number of elements in the map.
	 *
	 * \see isEmpty()
	 */
	uint size() const;

	/*!
	 * Returns true if the map is empty.
	 *
	 * \see size()
	 */
	bool isEmpty() const;

	/*!
	 * Find the first occurrence of \a key.
	 */
	Iterator find(const Key &key);

	/*!
	 * Find the first occurrence of \a key.
	 */
	ConstIterator find(const Key &key) const;

	/*!
	 * Returns true if the map contains an instance of \a key.
	 */
	bool contains(const Key &key) const;

	/*!
	 * Erase the item at \a it from the list.
	 */
	Map<Key, T> &erase(Iterator it);

	/*!
	 * Erase the item with \a key from the list.
	 */
	Map<Key, T> &erase(const Key &key);

	/*!
	 * Returns a reference to the value associated with \a key.
	 *
	 * \note This has undefined behavior if the key is not present in the map.
	 */
	const T &operator[](const Key &key) const;

	/*!
	 * Returns a reference to the value associated with \a key.
	 *
	 * \note This has undefined behavior if the key is not present in the map.
	 */
	T &operator[](const Key &key);

	/*!
	 * Make a shallow, implicitly shared, copy of \a m.  Because this is
	 * implicitly shared, this method is lightweight and suitable for
	 * pass-by-value usage.
	 */
	Map<Key, T> &operator=(const Map<Key, T> &m);

  protected:
	/*
	 * If this List is being shared via implicit sharing, do a deep copy of the
	 * data and separate from the shared members.  This should be called by all
	 * non-const subclass members.
	 */
	void detach();

  private:
#ifndef DO_NOT_DOCUMENT
	template <class KeyP, class TP> class MapPrivate;
	MapPrivate<Key, T> *d;
#endif
  };

}

// Since GCC doesn't support the "export" keyword, we have to include the
// implementation.


/*** Start of inlined file: tmap.tcc ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

namespace TagLib {

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

template <class Key, class T>
template <class KeyP, class TP>
class Map<Key, T>::MapPrivate : public RefCounter
{
public:
  MapPrivate() : RefCounter() {}
#ifdef WANT_CLASS_INSTANTIATION_OF_MAP
  MapPrivate(const std::map<class KeyP, class TP>& m) : RefCounter(), map(m) {}
  std::map<class KeyP, class TP> map;
#else
  MapPrivate(const std::map<KeyP, TP>& m) : RefCounter(), map(m) {}
  std::map<KeyP, TP> map;
#endif
};

template <class Key, class T>
Map<Key, T>::Map()
{
  d = new MapPrivate<Key, T>;
}

template <class Key, class T>
Map<Key, T>::Map(const Map<Key, T> &m) : d(m.d)
{
  d->ref();
}

template <class Key, class T>
Map<Key, T>::~Map()
{
  if(d->deref())
	delete(d);
}

template <class Key, class T>
typename Map<Key, T>::Iterator Map<Key, T>::begin()
{
  detach();
  return d->map.begin();
}

template <class Key, class T>
typename Map<Key, T>::ConstIterator Map<Key, T>::begin() const
{
  return d->map.begin();
}

template <class Key, class T>
typename Map<Key, T>::Iterator Map<Key, T>::end()
{
  detach();
  return d->map.end();
}

template <class Key, class T>
typename Map<Key, T>::ConstIterator Map<Key, T>::end() const
{
  return d->map.end();
}

template <class Key, class T>
Map<Key, T> &Map<Key, T>::insert(const Key &key, const T &value)
{
  detach();
  d->map[key] = value;
  return *this;
}

template <class Key, class T>
Map<Key, T> &Map<Key, T>::clear()
{
  detach();
  d->map.clear();
  return *this;
}

template <class Key, class T>
bool Map<Key, T>::isEmpty() const
{
  return d->map.empty();
}

template <class Key, class T>
typename Map<Key, T>::Iterator Map<Key, T>::find(const Key &key)
{
  detach();
  return d->map.find(key);
}

template <class Key, class T>
typename Map<Key,T>::ConstIterator Map<Key, T>::find(const Key &key) const
{
  return d->map.find(key);
}

template <class Key, class T>
bool Map<Key, T>::contains(const Key &key) const
{
  return d->map.find(key) != d->map.end();
}

template <class Key, class T>
Map<Key, T> &Map<Key,T>::erase(Iterator it)
{
  detach();
  d->map.erase(it);
  return *this;
}

template <class Key, class T>
Map<Key, T> &Map<Key,T>::erase(const Key &key)
{
  detach();
  Iterator it = d->map.find(key);
  if(it != d->map.end())
	d->map.erase(it);
  return *this;
}

template <class Key, class T>
TagLib::uint Map<Key, T>::size() const
{
  return d->map.size();
}

template <class Key, class T>
const T &Map<Key, T>::operator[](const Key &key) const
{
  return d->map[key];
}

template <class Key, class T>
T &Map<Key, T>::operator[](const Key &key)
{
  detach();
  return d->map[key];
}

template <class Key, class T>
Map<Key, T> &Map<Key, T>::operator=(const Map<Key, T> &m)
{
  if(&m == this)
	return *this;

  if(d->deref())
	delete(d);
  d = m.d;
  d->ref();
  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

template <class Key, class T>
void Map<Key, T>::detach()
{
  if(d->count() > 1) {
	d->deref();
	d = new MapPrivate<Key, T>(d->map);
  }
}

} // namespace TagLib

/*** End of inlined file: tmap.tcc ***/

#endif

/*** End of inlined file: tmap.h ***/

// #include "toolkit/tmap.tcc" // included by tmap.h

/*** Start of inlined file: tpropertymap.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it  under the terms of the GNU Lesser General Public License version  *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,            *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#ifndef PROPERTYMAP_H_
#define PROPERTYMAP_H_

namespace TagLib {

  typedef Map<String,StringList> SimplePropertyMap;

  //! A map for format-independent <key,valuelist> tag representations.

  /*!
   * This map implements a generic representation of textual audio metadata
   * ("tags") realized as pairs of a case-insensitive key
   * and a nonempty list of corresponding values, each value being an an arbitrary
   * unicode String.
   * The key has the same restrictions as in the vorbis comment specification,
   * i.e. it must contain at least one character; all printable ASCII characters
   * except '=' and '~' are allowed.
   *
   * In order to be safe with other formats, keep these additional restrictions in mind:
   *
   * - APE only allows keys from 2 to 16 printable ASCII characters (including space),
   *   with the exception of these strings: ID3, TAG, OggS, MP+
   *
   */

  class TAGLIB_EXPORT PropertyMap: public SimplePropertyMap
  {
  public:

	typedef SimplePropertyMap::Iterator Iterator;
	typedef SimplePropertyMap::ConstIterator ConstIterator;

	PropertyMap();

	PropertyMap(const PropertyMap &m);

	/*!
	 * Creates a PropertyMap initialized from a SimplePropertyMap. Copies all
	 * entries from \a m that have valid keys.
	 * Invalid keys will be appended to the unsupportedData() list.
	 */
	PropertyMap(const SimplePropertyMap &m);

	virtual ~PropertyMap();

	/*!
	 * Inserts \a values under \a key in the map.  If \a key already exists,
	 * then \values will be appended to the existing StringList.
	 * The returned value indicates success, i.e. whether \a key is a
	 * valid key.
	 */
	bool insert(const String &key, const StringList &values);

	/*!
	 * Replaces any existing values for \a key with the given \a values,
	 * and simply insert them if \a key did not exist before.
	 * The returned value indicates success, i.e. whether \a key is a
	 * valid key.
	 */
	bool replace(const String &key, const StringList &values);

	/*!
	 * Find the first occurrence of \a key.
	 */
	Iterator find(const String &key);

	/*!
	 * Find the first occurrence of \a key.
	 */
	ConstIterator find(const String &key) const;

	/*!
	 * Returns true if the map contains values for \a key.
	 */
	bool contains(const String &key) const;

	/*!
	 * Returns true if this map contains all keys of \a other
	 * and the values coincide for that keys. Does not take
	 * the unsupportedData list into account.
	 */
	bool contains(const PropertyMap &other) const;

	/*!
	 * Erase the \a key and its values from the map.
	 */
	PropertyMap &erase(const String &key);

	/*!
	 * Erases from this map all keys that appear in \a other.
	 */
	PropertyMap &erase(const PropertyMap &other);

	/*!
	 * Merge the contents of \a other into this PropertyMap.
	 * If a key is contained in both maps, the values of the second
	 * are appended to that of the first.
	 * The unsupportedData() lists are concatenated as well.
	 */
	PropertyMap &merge(const PropertyMap &other);

	/*!
	 * Returns a reference to the value associated with \a key.
	 *
	 * \note: This has undefined behavior if the key is not valid or not
	 * present in the map.
	 */
	const StringList &operator[](const String &key) const;

	/*!
	 * Returns a reference to the value associated with \a key.
	 *
	 * \note: This has undefined behavior if the key is not valid or not
	 * present in the map.
	 */
	StringList &operator[](const String &key);

	/*!
	 * Returns true if and only if \other has the same contents as this map.
	 */
	bool operator==(const PropertyMap &other) const;

	/*!
	 * Returns false if and only \other has the same contents as this map.
	 */
	bool operator!=(const PropertyMap &other) const;

	/*!
	 * If a PropertyMap is read from a File object using File::properties(),
	 * the StringList returned from this function will represent metadata
	 * that could not be parsed into the PropertyMap representation. This could
	 * be e.g. binary data, unknown ID3 frames, etc.
	 * You can remove items from the returned list, which tells TagLib to remove
	 * those unsupported elements if you call File::setProperties() with the
	 * same PropertyMap as argument.
	 */
	StringList &unsupportedData();
	const StringList &unsupportedData() const;

	/*!
	 * Removes all entries which have an empty value list.
	 */
	void removeEmpty();

	String toString() const;

	/*!
	 * Converts \a proposed into another String suitable to be used as
	 * a key, or returns String::null if this is not possible.
	 */
	static String prepareKey(const String &proposed);

  private:

	StringList unsupported;
  };

}
#endif /* PROPERTYMAP_H_ */

/*** End of inlined file: tpropertymap.h ***/



/*** Start of inlined file: mpegfile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_MPEGFILE_H
#define TAGLIB_MPEGFILE_H


/*** Start of inlined file: mpegproperties.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_MPEGPROPERTIES_H
#define TAGLIB_MPEGPROPERTIES_H


/*** Start of inlined file: mpegheader.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_MPEGHEADER_H
#define TAGLIB_MPEGHEADER_H

namespace TagLib {

  class ByteVector;

  namespace MPEG {

	//! An implementation of MP3 frame headers

	/*!
	 * This is an implementation of MPEG Layer III headers.  The API follows more
	 * or less the binary format of these headers.  I've used
	 * <a href="http://www.mp3-tech.org/programmer/frame_header.html">this</a>
	 * document as a reference.
	 */

	class TAGLIB_EXPORT Header
	{
	public:
	  /*!
	   * Parses an MPEG header based on \a data.
	   */
	  Header(const ByteVector &data);

	  /*!
	   * Does a shallow copy of \a h.
	   */
	  Header(const Header &h);

	  /*!
	   * Destroys this Header instance.
	   */
	  virtual ~Header();

	  /*!
	   * Returns true if the frame is at least an appropriate size and has
	   * legal values.
	   */
	  bool isValid() const;

	  /*!
	   * The MPEG Version.
	   */
	  enum Version {
		//! MPEG Version 1
		Version1 = 0,
		//! MPEG Version 2
		Version2 = 1,
		//! MPEG Version 2.5
		Version2_5 = 2
	  };

	  /*!
	   * Returns the MPEG Version of the header.
	   */
	  Version version() const;

	  /*!
	   * Returns the layer version.  This will be between the values 1-3.
	   */
	  int layer() const;

	  /*!
	   * Returns true if the MPEG protection bit is enabled.
	   */
	  bool protectionEnabled() const;

	  /*!
	   * Returns the bitrate encoded in the header.
	   */
	  int bitrate() const;

	  /*!
	   * Returns the sample rate in Hz.
	   */
	  int sampleRate() const;

	  /*!
	   * Returns true if the frame is padded.
	   */
	  bool isPadded() const;

	  /*!
	   * There are a few combinations or one or two channel audio that are
	   * possible:
	   */
	  enum ChannelMode {
		//! Stereo
		Stereo        = 0,
		//! Stereo
		JointStereo   = 1,
		//! Dual Mono
		DualChannel   = 2,
		//! Mono
		SingleChannel = 3
	  };

	  /*!
	   * Returns the channel mode for this frame.
	   */
	  ChannelMode channelMode() const;

	  /*!
	   * Returns true if the copyrighted bit is set.
	   */
	  bool isCopyrighted() const;

	  /*!
	   * Returns true if the "original" bit is set.
	   */
	  bool isOriginal() const;

	  /*!
	   * Returns the frame length.
	   */
	  int frameLength() const;

	  /*!
	   * Returns the number of frames per sample.
	   */
	  int samplesPerFrame() const;

	  /*!
	   * Makes a shallow copy of the header.
	   */
	  Header &operator=(const Header &h);

	private:
	  void parse(const ByteVector &data);

	  class HeaderPrivate;
	  HeaderPrivate *d;
	};
  }
}

#endif

/*** End of inlined file: mpegheader.h ***/

namespace TagLib {

  namespace MPEG {

	class File;
	class XingHeader;

	//! An implementation of audio property reading for MP3

	/*!
	 * This reads the data from an MPEG Layer III stream found in the
	 * AudioProperties API.
	 */

	class TAGLIB_EXPORT Properties : public AudioProperties
	{
	public:
	  /*!
	   * Create an instance of MPEG::Properties with the data read from the
	   * MPEG::File \a file.
	   */
	  Properties(File *file, ReadStyle style = Average);

	  /*!
	   * Destroys this MPEG Properties instance.
	   */
	  virtual ~Properties();

	  // Reimplementations.

	  virtual int length() const;
	  virtual int bitrate() const;
	  virtual int sampleRate() const;
	  virtual int channels() const;

	  /*!
	   * Returns a pointer to the XingHeader if one exists or null if no
	   * XingHeader was found.
	   */

	  const XingHeader *xingHeader() const;

	  /*!
	   * Returns the MPEG Version of the file.
	   */
	  Header::Version version() const;

	  /*!
	   * Returns the layer version.  This will be between the values 1-3.
	   */
	  int layer() const;

	  /*!
	   * Returns true if the MPEG protection bit is enabled.
	   */
	  bool protectionEnabled() const;

	  /*!
	   * Returns the channel mode for this frame.
	   */
	  Header::ChannelMode channelMode() const;

	  /*!
	   * Returns true if the copyrighted bit is set.
	   */
	  bool isCopyrighted() const;

	  /*!
	   * Returns true if the "original" bit is set.
	   */
	  bool isOriginal() const;

	private:
	  Properties(const Properties &);
	  Properties &operator=(const Properties &);

	  void read();

	  class PropertiesPrivate;
	  PropertiesPrivate *d;
	};
  }
}

#endif

/*** End of inlined file: mpegproperties.h ***/

namespace TagLib {

  namespace ID3v2 { class Tag; class FrameFactory; }
  namespace ID3v1 { class Tag; }
  namespace APE { class Tag; }

  //! An implementation of TagLib::File with MPEG (MP3) specific methods

  namespace MPEG {

	//! An MPEG file class with some useful methods specific to MPEG

	/*!
	 * This implements the generic TagLib::File API and additionally provides
	 * access to properties that are distinct to MPEG files, notably access
	 * to the different ID3 tags.
	 */

	class TAGLIB_EXPORT File : public TagLib::File
	{
	public:
	  /*!
	   * This set of flags is used for various operations and is suitable for
	   * being OR-ed together.
	   */
	  enum TagTypes {
		//! Empty set.  Matches no tag types.
		NoTags  = 0x0000,
		//! Matches ID3v1 tags.
		ID3v1   = 0x0001,
		//! Matches ID3v2 tags.
		ID3v2   = 0x0002,
		//! Matches APE tags.
		APE     = 0x0004,
		//! Matches all tag types.
		AllTags = 0xffff
	  };

	  /*!
	   * Contructs an MPEG file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   *
	   * \deprecated This constructor will be dropped in favor of the one below
	   * in a future version.
	   */
	  File(FileName file, bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Contructs an MPEG file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.  The frames will be created using
	   * \a frameFactory.
	   *
	   * \deprecated This constructor will be dropped in favor of the one below
	   * in a future version.
	   */
	  File(FileName file, ID3v2::FrameFactory *frameFactory,
		   bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Contructs an MPEG file from \a stream.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.  The frames will be created using
	   * \a frameFactory.
	   */
	  // BIC: merge with the above constructor
	  File(IOStream *stream, ID3v2::FrameFactory *frameFactory,
		   bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Destroys this instance of the File.
	   */
	  virtual ~File();

	  /*!
	   * Returns a pointer to a tag that is the union of the ID3v2 and ID3v1
	   * tags. The ID3v2 tag is given priority in reading the information -- if
	   * requested information exists in both the ID3v2 tag and the ID3v1 tag,
	   * the information from the ID3v2 tag will be returned.
	   *
	   * If you would like more granular control over the content of the tags,
	   * with the concession of generality, use the tag-type specific calls.
	   *
	   * \note As this tag is not implemented as an ID3v2 tag or an ID3v1 tag,
	   * but a union of the two this pointer may not be cast to the specific
	   * tag types.
	   *
	   * \see ID3v1Tag()
	   * \see ID3v2Tag()
	   * \see APETag()
	   */
	  virtual Tag *tag() const;

	  /*!
	   * Implements the unified property interface -- export function.
	   * If the file contains more than one tag, only the
	   * first one (in the order ID3v2, APE, ID3v1) will be converted to the
	   * PropertyMap.
	   */
	  PropertyMap properties() const;

	  void removeUnsupportedProperties(const StringList &properties);

	  /*!
	   * Implements the unified tag dictionary interface -- import function.
	   * As with the export, only one tag is taken into account. If the file
	   * has no tag at all, ID3v2 will be created.
	   */
	  PropertyMap setProperties(const PropertyMap &);

	  /*!
	   * Returns the MPEG::Properties for this file.  If no audio properties
	   * were read then this will return a null pointer.
	   */
	  virtual Properties *audioProperties() const;

	  /*!
	   * Save the file.  If at least one tag -- ID3v1 or ID3v2 -- exists this
	   * will duplicate its content into the other tag.  This returns true
	   * if saving was successful.
	   *
	   * If neither exists or if both tags are empty, this will strip the tags
	   * from the file.
	   *
	   * This is the same as calling save(AllTags);
	   *
	   * If you would like more granular control over the content of the tags,
	   * with the concession of generality, use paramaterized save call below.
	   *
	   * \see save(int tags)
	   */
	  virtual bool save();

	  /*!
	   * Save the file.  This will attempt to save all of the tag types that are
	   * specified by OR-ing together TagTypes values.  The save() method above
	   * uses AllTags.  This returns true if saving was successful.
	   *
	   * This strips all tags not included in the mask, but does not modify them
	   * in memory, so later calls to save() which make use of these tags will
	   * remain valid.  This also strips empty tags.
	   */
	  bool save(int tags);

	  /*!
	   * Save the file.  This will attempt to save all of the tag types that are
	   * specified by OR-ing together TagTypes values.  The save() method above
	   * uses AllTags.  This returns true if saving was successful.
	   *
	   * If \a stripOthers is true this strips all tags not included in the mask,
	   * but does not modify them in memory, so later calls to save() which make
	   * use of these tags will remain valid.  This also strips empty tags.
	   */
	  // BIC: combine with the above method
	  bool save(int tags, bool stripOthers);

	  /*!
	   * Save the file.  This will attempt to save all of the tag types that are
	   * specified by OR-ing together TagTypes values.  The save() method above
	   * uses AllTags.  This returns true if saving was successful.
	   *
	   * If \a stripOthers is true this strips all tags not included in the mask,
	   * but does not modify them in memory, so later calls to save() which make
	   * use of these tags will remain valid.  This also strips empty tags.
	   *
	   * The \a id3v2Version parameter specifies the version of the saved
	   * ID3v2 tag. It can be either 4 or 3.
	   */
	  // BIC: combine with the above method
	  bool save(int tags, bool stripOthers, int id3v2Version);

	  /*!
	   * Returns a pointer to the ID3v2 tag of the file.
	   *
	   * If \a create is false (the default) this will return a null pointer
	   * if there is no valid ID3v2 tag.  If \a create is true it will create
	   * an ID3v2 tag if one does not exist.
	   *
	   * \note The Tag <b>is still</b> owned by the MPEG::File and should not be
	   * deleted by the user.  It will be deleted when the file (object) is
	   * destroyed.
	   */
	  ID3v2::Tag *ID3v2Tag(bool create = false);

	  /*!
	   * Returns a pointer to the ID3v1 tag of the file.
	   *
	   * If \a create is false (the default) this will return a null pointer
	   * if there is no valid ID3v1 tag.  If \a create is true it will create
	   * an ID3v1 tag if one does not exist.
	   *
	   * \note The Tag <b>is still</b> owned by the MPEG::File and should not be
	   * deleted by the user.  It will be deleted when the file (object) is
	   * destroyed.
	   */
	  ID3v1::Tag *ID3v1Tag(bool create = false);

	  /*!
	   * Returns a pointer to the APE tag of the file.
	   *
	   * If \a create is false (the default) this will return a null pointer
	   * if there is no valid APE tag.  If \a create is true it will create
	   * an APE tag if one does not exist.
	   *
	   * \note The Tag <b>is still</b> owned by the MPEG::File and should not be
	   * deleted by the user.  It will be deleted when the file (object) is
	   * destroyed.
	   */
	  APE::Tag *APETag(bool create = false);

	  /*!
	   * This will strip the tags that match the OR-ed together TagTypes from the
	   * file.  By default it strips all tags.  It returns true if the tags are
	   * successfully stripped.
	   *
	   * This is equivalent to strip(tags, true)
	   *
	   * \note This will also invalidate pointers to the ID3 and APE tags
	   * as their memory will be freed.
	   */
	  bool strip(int tags = AllTags);

	  /*!
	   * This will strip the tags that match the OR-ed together TagTypes from the
	   * file.  By default it strips all tags.  It returns true if the tags are
	   * successfully stripped.
	   *
	   * If \a freeMemory is true the ID3 and APE tags will be deleted and
	   * pointers to them will be invalidated.
	   */
	  // BIC: merge with the method above
	  bool strip(int tags, bool freeMemory);

	  /*!
	   * Set the ID3v2::FrameFactory to something other than the default.
	   *
	   * \see ID3v2FrameFactory
	   */
	  void setID3v2FrameFactory(const ID3v2::FrameFactory *factory);

	  /*!
	   * Returns the position in the file of the first MPEG frame.
	   */
	  long firstFrameOffset();

	  /*!
	   * Returns the position in the file of the next MPEG frame,
	   * using the current position as start
	   */
	  long nextFrameOffset(long position);

	  /*!
	   * Returns the position in the file of the previous MPEG frame,
	   * using the current position as start
	   */
	  long previousFrameOffset(long position);

	  /*!
	   * Returns the position in the file of the last MPEG frame.
	   */
	  long lastFrameOffset();

	private:
	  File(const File &);
	  File &operator=(const File &);

	  void read(bool readProperties, Properties::ReadStyle propertiesStyle);
	  long findID3v2();
	  long findID3v1();
	  void findAPE();

	  /*!
	   * MPEG frames can be recognized by the bit pattern 11111111 111, so the
	   * first byte is easy to check for, however checking to see if the second byte
	   * starts with \e 111 is a bit more tricky, hence this member function.
	   */
	  static bool secondSynchByte(char byte);

	  class FilePrivate;
	  FilePrivate *d;
	};
  }
}

#endif

/*** End of inlined file: mpegfile.h ***/


/*** Start of inlined file: xingheader.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_XINGHEADER_H
#define TAGLIB_XINGHEADER_H

namespace TagLib {

  class ByteVector;

  namespace MPEG {

	//! An implementation of the Xing VBR headers

	/*!
	 * This is a minimalistic implementation of the Xing VBR headers.  Xing
	 * headers are often added to VBR (variable bit rate) MP3 streams to make it
	 * easy to compute the length and quality of a VBR stream.  Our implementation
	 * is only concerned with the total size of the stream (so that we can
	 * calculate the total playing time and the average bitrate).  It uses
	 * <a href="http://home.pcisys.net/~melanson/codecs/mp3extensions.txt">this text</a>
	 * and the XMMS sources as references.
	 */

	class TAGLIB_EXPORT XingHeader
	{
	public:
	  /*!
	   * Parses a Xing header based on \a data.  The data must be at least 16
	   * bytes long (anything longer than this is discarded).
	   */
	  XingHeader(const ByteVector &data);

	  /*!
	   * Destroy this XingHeader instance.
	   */
	  virtual ~XingHeader();

	  /*!
	   * Returns true if the data was parsed properly and if there is a valid
	   * Xing header present.
	   */
	  bool isValid() const;

	  /*!
	   * Returns the total number of frames.
	   */
	  uint totalFrames() const;

	  /*!
	   * Returns the total size of stream in bytes.
	   */
	  uint totalSize() const;

	  /*!
	   * Returns the offset for the start of this Xing header, given the
	   * version and channels of the frame
	   */
	  // BIC: rename to offset()
	  static int xingHeaderOffset(TagLib::MPEG::Header::Version v,
								  TagLib::MPEG::Header::ChannelMode c);

	private:
	  XingHeader(const XingHeader &);
	  XingHeader &operator=(const XingHeader &);

	  void parse(const ByteVector &data);

	  class XingHeaderPrivate;
	  XingHeaderPrivate *d;
	};
  }
}

#endif

/*** End of inlined file: xingheader.h ***/


/*** Start of inlined file: id3v1tag.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_ID3V1TAG_H
#define TAGLIB_ID3V1TAG_H

namespace TagLib {

  class File;

  //! An ID3v1 implementation

  namespace ID3v1 {

	//! A abstraction for the string to data encoding in ID3v1 tags.

	/*!
	 * ID3v1 should in theory always contain ISO-8859-1 (Latin1) data.  In
	 * practice it does not.  TagLib by default only supports ISO-8859-1 data
	 * in ID3v1 tags.
	 *
	 * However by subclassing this class and reimplementing parse() and render()
	 * and setting your reimplementation as the default with
	 * ID3v1::Tag::setStringHandler() you can define how you would like these
	 * transformations to be done.
	 *
	 * \warning It is advisable <b>not</b> to write non-ISO-8859-1 data to ID3v1
	 * tags.  Please consider disabling the writing of ID3v1 tags in the case
	 * that the data is not ISO-8859-1.
	 *
	 * \see ID3v1::Tag::setStringHandler()
	 */

	class TAGLIB_EXPORT StringHandler
	{
	  TAGLIB_IGNORE_MISSING_DESTRUCTOR
	public:
	  // BIC: Add virtual destructor.
	  StringHandler();

	  /*!
	   * Decode a string from \a data.  The default implementation assumes that
	   * \a data is an ISO-8859-1 (Latin1) character array.
	   */
	  virtual String parse(const ByteVector &data) const;

	  /*!
	   * Encode a ByteVector with the data from \a s.  The default implementation
	   * assumes that \a s is an ISO-8859-1 (Latin1) string.  If the string is
	   * does not conform to ISO-8859-1, no value is written.
	   *
	   * \warning It is recommended that you <b>not</b> override this method, but
	   * instead do not write an ID3v1 tag in the case that the data is not
	   * ISO-8859-1.
	   */
	  virtual ByteVector render(const String &s) const;
	};

	//! The main class in the ID3v1 implementation

	/*!
	 * This is an implementation of the ID3v1 format.  ID3v1 is both the simplist
	 * and most common of tag formats but is rather limited.  Because of its
	 * pervasiveness and the way that applications have been written around the
	 * fields that it provides, the generic TagLib::Tag API is a mirror of what is
	 * provided by ID3v1.
	 *
	 * ID3v1 tags should generally only contain Latin1 information.  However because
	 * many applications do not follow this rule there is now support for overriding
	 * the ID3v1 string handling using the ID3v1::StringHandler class.  Please see
	 * the documentation for that class for more information.
	 *
	 * \see StringHandler
	 *
	 * \note Most fields are truncated to a maximum of 28-30 bytes.  The
	 * truncation happens automatically when the tag is rendered.
	 */

	class TAGLIB_EXPORT Tag : public TagLib::Tag
	{
	public:
	  /*!
	   * Create an ID3v1 tag with default values.
	   */
	  Tag();

	  /*!
	   * Create an ID3v1 tag and parse the data in \a file starting at
	   * \a tagOffset.
	   */
	  Tag(File *file, long tagOffset);

	  /*!
	   * Destroys this Tag instance.
	   */
	  virtual ~Tag();

	  /*!
	   * Renders the in memory values to a ByteVector suitable for writing to
	   * the file.
	   */
	  ByteVector render() const;

	  /*!
	   * Returns the string "TAG" suitable for usage in locating the tag in a
	   * file.
	   */
	  static ByteVector fileIdentifier();

	  // Reimplementations.

	  virtual String title() const;
	  virtual String artist() const;
	  virtual String album() const;
	  virtual String comment() const;
	  virtual String genre() const;
	  virtual uint year() const;
	  virtual uint track() const;

	  virtual void setTitle(const String &s);
	  virtual void setArtist(const String &s);
	  virtual void setAlbum(const String &s);
	  virtual void setComment(const String &s);
	  virtual void setGenre(const String &s);
	  virtual void setYear(uint i);
	  virtual void setTrack(uint i);

	  /*!
	   * Sets the string handler that decides how the ID3v1 data will be
	   * converted to and from binary data.
	   *
	   * \see StringHandler
	   */
	  static void setStringHandler(const StringHandler *handler);

	protected:
	  /*!
	   * Reads from the file specified in the constructor.
	   */
	  void read();
	  /*!
	   * Pareses the body of the tag in \a data.
	   */
	  void parse(const ByteVector &data);

	private:
	  Tag(const Tag &);
	  Tag &operator=(const Tag &);

	  class TagPrivate;
	  TagPrivate *d;
	};
  }
}

#endif

/*** End of inlined file: id3v1tag.h ***/


/*** Start of inlined file: id3v1genres.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_ID3V1GENRE_H
#define TAGLIB_ID3V1GENRE_H

namespace TagLib {
  namespace ID3v1 {

	typedef Map<String, int> GenreMap;

	/*!
	 * Returns the list of canonical ID3v1 genre names in the order that they
	 * are listed in the standard.
	 */
	StringList TAGLIB_EXPORT genreList();

	/*!
	 * A "reverse mapping" that goes from the canonical ID3v1 genre name to the
	 * respective genre number.   genreMap()["Rock"] ==
	 */
	GenreMap TAGLIB_EXPORT genreMap();

	/*!
	 * Returns the name of the genre at \a index in the ID3v1 genre list.  If
	 * \a index is out of range -- less than zero or greater than 146 -- a null
	 * string will be returned.
	 */
	String TAGLIB_EXPORT genre(int index);

	/*!
	 * Returns the genre index for the (case sensitive) genre \a name.  If the
	 * genre is not in the list 255 (which signifies an unknown genre in ID3v1)
	 * will be returned.
	 */
	int TAGLIB_EXPORT genreIndex(const String &name);
  }
}

#endif

/*** End of inlined file: id3v1genres.h ***/


/*** Start of inlined file: id3v2extendedheader.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_ID3V2EXTENDEDHEADER_H
#define TAGLIB_ID3V2EXTENDEDHEADER_H

namespace TagLib {

  namespace ID3v2 {

	//! ID3v2 extended header implementation

	/*!
	 * This class implements ID3v2 extended headers.  It attempts to follow,
	 * both  semantically and programatically, the structure specified in
	 * the ID3v2 standard.  The API is based on the properties of ID3v2 extended
	 * headers specified there.  If any of the terms used in this documentation
	 * are unclear please check the specification in the linked section.
	 * (Structure, <a href="id3v2-structure.html#3.2">3.2</a>)
	 */

	class TAGLIB_EXPORT ExtendedHeader
	{
	public:
	  /*!
	   * Constructs an empty ID3v2 extended header.
	   */
	  ExtendedHeader();

	  /*!
	   * Destroys the extended header.
	   */
	  virtual ~ExtendedHeader();

	  /*!
	   * Returns the size of the extended header.  This is variable for the
	   * extended header.
	   */
	  uint size() const;

	  /*!
	   * Sets the data that will be used as the extended header.  Since the
	   * length is not known before the extended header has been parsed, this
	   * should just be a pointer to the first byte of the extended header.  It
	   * will determine the length internally and make that available through
	   * size().
	   */
	  void setData(const ByteVector &data);

	protected:
	  /*!
	   * Called by setData() to parse the extended header data.  It makes this
	   * information available through the public API.
	   */
	  void parse(const ByteVector &data);

	private:
	  ExtendedHeader(const ExtendedHeader &);
	  ExtendedHeader &operator=(const ExtendedHeader &);

	  class ExtendedHeaderPrivate;
	  ExtendedHeaderPrivate *d;
	};

  }
}
#endif

/*** End of inlined file: id3v2extendedheader.h ***/


/*** Start of inlined file: id3v2frame.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_ID3V2FRAME_H
#define TAGLIB_ID3V2FRAME_H

namespace TagLib {

  class StringList;
  class PropertyMap;

  namespace ID3v2 {

	class Tag;
	class FrameFactory;

	//! ID3v2 frame implementation

	/*!
	 * This class is the main ID3v2 frame implementation.  In ID3v2, a tag is
	 * split between a collection of frames (which are in turn split into fields
	 * (Structure, <a href="id3v2-structure.html#4">4</a>)
	 * (<a href="id3v2-frames.html">Frames</a>).  This class provides an API for
	 * gathering information about and modifying ID3v2 frames.  Funtionallity
	 * specific to a given frame type is handed in one of the many subclasses.
	 */

	class TAGLIB_EXPORT Frame
	{
	  friend class Tag;
	  friend class FrameFactory;

	public:

	  /*!
	   * Creates a textual frame which corresponds to a single key in the PropertyMap
	   * interface. These are all (User)TextIdentificationFrames except TIPL and TMCL,
	   * all (User)URLLinkFrames, CommentsFrames, and UnsynchronizedLyricsFrame.
	   */
	  static Frame *createTextualFrame(const String &key, const StringList &values);

	  /*!
	   * Destroys this Frame instance.
	   */
	  virtual ~Frame();

	  /*!
	   * Returns the Frame ID (Structure, <a href="id3v2-structure.html#4">4</a>)
	   * (Frames, <a href="id3v2-frames.html#4">4</a>)
	   */
	  ByteVector frameID() const;

	  /*!
	   * Returns the size of the frame.
	   */
	  uint size() const;

	  /*!
	   * Returns the size of the frame header
	   *
	   * \deprecated This is only accurate for ID3v2.3 or ID3v2.4.  Please use
	   * the call below which accepts an ID3v2 version number.  In the next
	   * non-binary compatible release this will be made into a non-static
	   * member that checks the internal ID3v2 version.
	   */
	  static uint headerSize(); // BIC: remove and make non-static

	  /*!
	   * Returns the size of the frame header for the given ID3v2 version.
	   *
	   * \deprecated Please see the explanation above.
	   */
	  static uint headerSize(uint version); // BIC: remove and make non-static

	  /*!
	   * Sets the data that will be used as the frame.  Since the length is not
	   * known before the frame has been parsed, this should just be a pointer to
	   * the first byte of the frame.  It will determine the length internally
	   * and make that available through size().
	   */
	  void setData(const ByteVector &data);

	  /*!
	   * Set the text of frame in the sanest way possible.  This should only be
	   * reimplemented in frames where there is some logical mapping to text.
	   *
	   * \note If the frame type supports multiple text encodings, this will not
	   * change the text encoding of the frame; the string will be converted to
	   * that frame's encoding.  Please use the specific APIs of the frame types
	   * to set the encoding if that is desired.
	   */
	  virtual void setText(const String &text);

	  /*!
	   * This returns the textual representation of the data in the frame.
	   * Subclasses must reimplement this method to provide a string
	   * representation of the frame's data.
	   */
	  virtual String toString() const = 0;

	  /*!
	   * Render the frame back to its binary format in a ByteVector.
	   */
	  ByteVector render() const;

	  /*!
	   * Returns the text delimiter that is used between fields for the string
	   * type \a t.
	   */
	  static ByteVector textDelimiter(String::Type t);

	  /*!
	   * The string with which an instrument name is prefixed to build a key in a PropertyMap;
	   * used to translate PropertyMaps to TMCL frames. In the current implementation, this
	   * is "PERFORMER:".
	   */
	  static const String instrumentPrefix;
	  /*!
	   * The PropertyMap key prefix which triggers the use of a COMM frame instead of a TXXX
	   * frame for a non-standard key. In the current implementation, this is "COMMENT:".
	   */
	  static const String commentPrefix;
	  /*!
	   * The PropertyMap key prefix which triggers the use of a USLT frame instead of a TXXX
	   * frame for a non-standard key. In the current implementation, this is "LYRICS:".
	   */
	  static const String lyricsPrefix;
	  /*!
	   * The PropertyMap key prefix which triggers the use of a WXXX frame instead of a TXX
	   * frame for a non-standard key. In the current implementation, this is "URL:".
	   */
	  static const String urlPrefix;

	protected:
	  class Header;

	  /*!
	   * Constructs an ID3v2 frame using \a data to read the header information.
	   * All other processing of \a data should be handled in a subclass.
	   *
	   * \note This need not contain anything more than a frame ID, but
	   * \e must constain at least that.
	   */
	  explicit Frame(const ByteVector &data);

	  /*!
	   * This creates an Frame using the header \a h.
	   *
	   * The ownership of this header will be assigned to the frame and the
	   * header will be deleted when the frame is destroyed.
	   */
	  Frame(Header *h);

	  /*!
	   * Returns a pointer to the frame header.
	   */
	  Header *header() const;

	  /*!
	   * Sets the header to \a h.  If \a deleteCurrent is true, this will free
	   * the memory of the current header.
	   *
	   * The ownership of this header will be assigned to the frame and the
	   * header will be deleted when the frame is destroyed.
	   */
	  void setHeader(Header *h, bool deleteCurrent = true);

	  /*!
	   * Called by setData() to parse the frame data.  It makes this information
	   * available through the public API.
	   */
	  void parse(const ByteVector &data);

	  /*!
	   * Called by parse() to parse the field data.  It makes this information
	   * available through the public API.  This must be overridden by the
	   * subclasses.
	   */
	  virtual void parseFields(const ByteVector &data) = 0;

	  /*!
	   * Render the field data back to a binary format in a ByteVector.  This
	   * must be overridden by subclasses.
	   */
	  virtual ByteVector renderFields() const = 0;

	  /*!
	   * Returns a ByteVector containing the field data given the frame data.
	   * This correctly adjusts for the header size plus any additional frame
	   * data that's specified in the frame header flags.
	   */
	  ByteVector fieldData(const ByteVector &frameData) const;

	  /*!
	   * Reads a String of type \a encodiong from the ByteVector \a data.  If \a
	   * position is passed in it is used both as the starting point and is
	   * updated to replect the position just after the string that has been read.
	   * This is useful for reading strings sequentially.
	   */
	  String readStringField(const ByteVector &data, String::Type encoding,
							 int *positon = 0);

	  /*!
	   * Checks a the list of string values to see if they can be used with the
	   * specified encoding and returns the recommended encoding.
	   */
	  // BIC: remove and make non-static
	  static String::Type checkEncoding(const StringList &fields,
										String::Type encoding);

	  /*!
	   * Checks a the list of string values to see if they can be used with the
	   * specified encoding and returns the recommended encoding. This method
	   * also checks the ID3v2 version and makes sure the encoding can be used
	   * in the specified version.
	   */
	  // BIC: remove and make non-static
	  static String::Type checkEncoding(const StringList &fields,
										String::Type encoding, uint version);

	  /*!
	   * Checks a the list of string values to see if they can be used with the
	   * specified encoding and returns the recommended encoding. This method
	   * also checks the ID3v2 version and makes sure the encoding can be used
	   * in the version specified by the frame's header.
	   */
	  String::Type checkTextEncoding(const StringList &fields,
									 String::Type encoding) const;

	  /*!
	   * Parses the contents of this frame as PropertyMap. If that fails, the returend
	   * PropertyMap will be empty, and its unsupportedData() will contain this frame's
	   * ID.
	   * BIC: Will be a virtual function in future releases.
	   */
	  PropertyMap asProperties() const;

	  /*!
	   * Returns an appropriate ID3 frame ID for the given free-form tag key. This method
	   * will return ByteVector::null if no specialized translation is found.
	   */
	  static ByteVector keyToFrameID(const String &);

	  /*!
	   * Returns a free-form tag name for the given ID3 frame ID. Note that this does not work
	   * for general frame IDs such as TXXX or WXXX; in such a case String::null is returned.
	   */
	  static String frameIDToKey(const ByteVector &);

	  /*!
	   * This helper function splits the PropertyMap \a original into three ProperytMaps
	   * \a singleFrameProperties, \a tiplProperties, and \a tmclProperties, such that:
	   * - \a singleFrameProperties contains only of keys which can be represented with
	   *   exactly one ID3 frame per key. In the current implementation
	   *   this is everything except for the fixed "involved people" keys and keys of the
	   *   form "TextIdentificationFrame::instrumentPrefix" + "instrument", which are
	   *   mapped to a TMCL frame.
	   * - \a tiplProperties will consist of those keys that are present in
	   *   TextIdentificationFrame::involvedPeopleMap()
	   * - \a tmclProperties contains the "musician credits" keys which should be mapped
	   *   to a TMCL frame
	   */
	  static void splitProperties(const PropertyMap &original, PropertyMap &singleFrameProperties,
		  PropertyMap &tiplProperties, PropertyMap &tmclProperties);

	private:
	  Frame(const Frame &);
	  Frame &operator=(const Frame &);

	  class FramePrivate;
	  friend class FramePrivate;
	  FramePrivate *d;
	};

	//! ID3v2 frame header implementation

	/*!
	 * The ID3v2 Frame Header (Structure, <a href="id3v2-structure.html#4">4</a>)
	 *
	 * Every ID3v2::Frame has an associated header that gives some general
	 * properties of the frame and also makes it possible to identify the frame
	 * type.
	 *
	 * As such when reading an ID3v2 tag ID3v2::FrameFactory first creates the
	 * frame headers and then creates the appropriate Frame subclass based on
	 * the type and attaches the header.
	 */

	class TAGLIB_EXPORT Frame::Header
	{
	public:
	  /*!
	   * Construct a Frame Header based on \a data.  \a data must at least
	   * contain a 4 byte frame ID, and optionally can contain flag data and the
	   * frame size.  i.e. Just the frame id -- "TALB" -- is a valid value.
	   *
	   * \deprecated Please use the constructor below that accepts a version
	   * number.
	   */
	  Header(const ByteVector &data, bool synchSafeInts);

	  /*!
	   * Construct a Frame Header based on \a data.  \a data must at least
	   * contain a 4 byte frame ID, and optionally can contain flag data and the
	   * frame size.  i.e. Just the frame id -- "TALB" -- is a valid value.
	   *
	   * \a version should be the ID3v2 version of the tag.
	   */
	  explicit Header(const ByteVector &data, uint version = 4);

	  /*!
	   * Destroys this Header instance.
	   */
	  virtual ~Header();

	  /*!
	   * Sets the data for the Header.
	   *
	   * \deprecated Please use the version below that accepts an ID3v2 version
	   * number.
	   */
	  void setData(const ByteVector &data, bool synchSafeInts);

	  /*!
	   * Sets the data for the Header.  \a version should indicate the ID3v2
	   * version number of the tag that this frame is contained in.
	   */
	  void setData(const ByteVector &data, uint version = 4);

	  /*!
	   * Returns the Frame ID (Structure, <a href="id3v2-structure.html#4">4</a>)
	   * (Frames, <a href="id3v2-frames.html#4">4</a>)
	   */
	  ByteVector frameID() const;

	  /*!
	   * Sets the frame's ID to \a id.  Only the first four bytes of \a id will
	   * be used.
	   *
	   * \warning This method should in general be avoided.  It exists simply to
	   * provide a mechanism for transforming frames from a deprecated frame type
	   * to a newer one -- i.e. TYER to TDRC from ID3v2.3 to ID3v2.4.
	   */
	  void setFrameID(const ByteVector &id);

	  /*!
	   * Returns the size of the frame data portion, as set when setData() was
	   * called or set explicitly via setFrameSize().
	   */
	  uint frameSize() const;

	  /*!
	   * Sets the size of the frame data portion.
	   */
	  void setFrameSize(uint size);

	  /*!
	   * Returns the ID3v2 version of the header, as passed in from the
	   * construction of the header or set via setVersion().
	   */
	  uint version() const;

	  /*!
	   * Sets the ID3v2 version of the header, changing has impact on the
	   * correct parsing/rendering of frame data.
	   */
	  void setVersion(uint version);

	  /*!
	   * Returns the size of the frame header in bytes.
	   *
	   * \deprecated Please use the version of this method that accepts a
	   * version.  This is only accurate for ID3v2.3 and ID3v2.4.  This will be
	   * removed in the next binary incompatible release (2.0) and will be
	   * replaced with a non-static method that checks the frame version.
	   */
	  static uint size();

	  /*!
	   * Returns the size of the frame header in bytes for the ID3v2 version
	   * that's given.
	   *
	   * \deprecated Please see the explanation in the version above.
	   */
	  static uint size(uint version);

	  /*!
	   * Returns true if the flag for tag alter preservation is set.
	   *
	   * The semantics are a little backwards from what would seem natural
	   * (setting the preservation flag to throw away the frame), but this
	   * follows the ID3v2 standard.
	   *
	   * \see setTagAlterPreservation()
	   */
	  bool tagAlterPreservation() const;

	  /*!
	   * Sets the flag for preservation of this frame if the tag is set.  If
	   * this is set to true the frame will not be written when the tag is
	   * saved.
	   *
	   * The semantics are a little backwards from what would seem natural
	   * (setting the preservation flag to throw away the frame), but this
	   * follows the ID3v2 standard.
	   *
	   * \see tagAlterPreservation()
	   */
	  void setTagAlterPreservation(bool discard);

	  /*!
	   * Returns true if the flag for file alter preservation is set.
	   *
	   * \note This flag is currently ignored internally in TagLib.
	   */
	  bool fileAlterPreservation() const;

	  /*!
	   * Returns true if the frame is meant to be read only.
	   *
	   * \note This flag is currently ignored internally in TagLib.
	   */
	  bool readOnly() const;

	  /*!
	   * Returns true if the flag for the grouping identifity is set.
	   *
	   * \note This flag is currently ignored internally in TagLib.
	   */
	  bool groupingIdentity() const;

	  /*!
	   * Returns true if compression is enabled for this frame.
	   *
	   * \note This flag is currently ignored internally in TagLib.
	   */
	  bool compression() const;

	  /*!
	   * Returns true if encryption is enabled for this frame.
	   *
	   * \note This flag is currently ignored internally in TagLib.
	   */
	  bool encryption() const;

#ifndef DO_NOT_DOCUMENT
	  bool unsycronisation() const;
#endif

	  /*!
	   * Returns true if unsynchronisation is enabled for this frame.
	   */
	  bool unsynchronisation() const;

	  /*!
	   * Returns true if the flag for a data length indicator is set.
	   */
	  bool dataLengthIndicator() const;

	  /*!
	   * Render the Header back to binary format in a ByteVector.
	   */
	  ByteVector render() const;

	  /*!
	   * \deprecated
	   */
	  bool frameAlterPreservation() const;

	private:
	  Header(const Header &);
	  Header &operator=(const Header &);

	  class HeaderPrivate;
	  HeaderPrivate *d;
	};

  }
}

#endif

/*** End of inlined file: id3v2frame.h ***/


/*** Start of inlined file: id3v2header.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_ID3V2HEADER_H
#define TAGLIB_ID3V2HEADER_H

namespace TagLib {

  namespace ID3v2 {

	//! An implementation of ID3v2 headers

	/*!
	 * This class implements ID3v2 headers.  It attempts to follow, both
	 * semantically and programatically, the structure specified in
	 * the ID3v2 standard.  The API is based on the properties of ID3v2 headers
	 * specified there.  If any of the terms used in this documentation are
	 * unclear please check the specification in the linked section.
	 * (Structure, <a href="id3v2-structure.html#3.1">3.1</a>)
	 */

	class TAGLIB_EXPORT Header
	{
	public:
	  /*!
	   * Constructs an empty ID3v2 header.
	   */
	  Header();

	  /*!
	   * Constructs an ID3v2 header based on \a data.  parse() is called
	   * immediately.
	   */
	  Header(const ByteVector &data);

	  /*!
	   * Destroys the header.
	   */
	  virtual ~Header();

	  /*!
	   * Returns the major version number.  (Note: This is the 4, not the 2 in
	   * ID3v2.4.0.  The 2 is implied.)
	   */
	  uint majorVersion() const;

	  /*!
	   * Set the the major version number to \a version.  (Note: This is
	   * the 4, not the 2 in ID3v2.4.0.  The 2 is implied.)
	   * \see majorVersion()
	   *
	   * \note This is used by the internal parser; this will not change the
	   * version which is written and in general should not be called by API
	   * users.
	   */
	  void setMajorVersion(uint version);

	  /*!
	   * Returns the revision number.  (Note: This is the 0, not the 4 in
	   * ID3v2.4.0.  The 2 is implied.)
	   */
	  uint revisionNumber() const;

	  /*!
	   * Returns true if unsynchronisation has been applied to all frames.
	   */
	  bool unsynchronisation() const;

	  /*!
	   * Returns true if an extended header is present in the tag.
	   */
	  bool extendedHeader() const;

	  /*!
	   * Returns true if the experimental indicator flag is set.
	   */
	  bool experimentalIndicator() const;

	  /*!
	   * Returns true if a footer is present in the tag.
	   */
	  bool footerPresent() const;
	  /*!
	   * Returns the tag size in bytes.  This is the size of the frame content.
	   * The size of the \e entire tag will be this plus the header size (10
	   * bytes) and, if present, the footer size (potentially another 10 bytes).
	   *
	   * \note This is the value as read from the header to which TagLib attempts
	   * to provide an API to; it was not a design decision on the part of TagLib
	   * to not include the mentioned portions of the tag in the \e size.
	   *
	   * \see completeTagSize()
	   */
	  uint tagSize() const;

	  /*!
	   * Returns the tag size, including the header and, if present, the footer
	   * size.
	   *
	   * \see tagSize()
	   */
	  uint completeTagSize() const;

	  /*!
	   * Set the tag size to \a s.
	   * \see tagSize()
	   */
	  void setTagSize(uint s);

	  /*!
	   * Returns the size of the header.  Presently this is always 10 bytes.
	   */
	  static uint size();

	  /*!
	   * Returns the string used to identify and ID3v2 tag inside of a file.
	   * Presently this is always "ID3".
	   */
	  static ByteVector fileIdentifier();

	  /*!
	   * Sets the data that will be used as the header.  10 bytes, starting from
	   * the beginning of \a data are used.
	   */
	  void setData(const ByteVector &data);

	  /*!
	   * Renders the Header back to binary format.
	   */
	  ByteVector render() const;

	protected:
	  /*!
	   * Called by setData() to parse the header data.  It makes this information
	   * available through the public API.
	   */
	  void parse(const ByteVector &data);

	private:
	  Header(const Header &);
	  Header &operator=(const Header &);

	  class HeaderPrivate;
	  HeaderPrivate *d;
	};

  }
}

#endif

/*** End of inlined file: id3v2header.h ***/


/*** Start of inlined file: id3v2synchdata.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_ID3V2SYNCHDATA_H
#define TAGLIB_ID3V2SYNCHDATA_H

namespace TagLib {

  namespace ID3v2 {

	//! A few functions for ID3v2 synch safe integer conversion

	/*!
	 * In the ID3v2.4 standard most integer values are encoded as "synch safe"
	 * integers which are encoded in such a way that they will not give false
	 * MPEG syncs and confuse MPEG decoders.  This namespace provides some
	 * methods for converting to and from these values to ByteVectors for
	 * things rendering and parsing ID3v2 data.
	 */

	namespace SynchData
	{
	  /*!
	   * This returns the unsigned integer value of \a data where \a data is a
	   * ByteVector that contains a \e synchsafe integer (Structure,
	   * <a href="id3v2-structure.html#6.2">6.2</a>).  The default \a length of
	   * 4 is used if another value is not specified.
	   */
	  TAGLIB_EXPORT uint toUInt(const ByteVector &data);

	  /*!
	   * Returns a 4 byte (32 bit) synchsafe integer based on \a value.
	   */
	  TAGLIB_EXPORT ByteVector fromUInt(uint value);

	  /*!
	   * Convert the data from unsynchronized data to its original format.
	   */
	  TAGLIB_EXPORT ByteVector decode(const ByteVector &input);
	}

  }
}

#endif

/*** End of inlined file: id3v2synchdata.h ***/


/*** Start of inlined file: id3v2footer.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_ID3V2FOOTER_H
#define TAGLIB_ID3V2FOOTER_H

namespace TagLib {

  namespace ID3v2 {

	class Header;

	//! ID3v2 footer implementation

	/*!
	 * Per the ID3v2 specification, the tag's footer is just a copy of the
	 * information in the header.  As such there is no API for reading the
	 * data from the header, it can just as easily be done from the header.
	 *
	 * In fact, at this point, TagLib does not even parse the footer since
	 * it is not useful internally.  However, if the flag to include a footer
	 * has been set in the ID3v2::Tag, TagLib will render a footer.
	 */

	class TAGLIB_EXPORT Footer
	{
	public:
	  /*!
	   * Constructs an empty ID3v2 footer.
	   */
	  Footer();
	  /*!
	   * Destroys the footer.
	   */
	  virtual ~Footer();

	  /*!
	   * Returns the size of the footer.  Presently this is always 10 bytes.
	   */
	  static uint size();

	  /*!
	   * Renders the footer based on the data in \a header.
	   */
	  ByteVector render(const Header *header) const;

	private:
	  Footer(const Footer &);
	  Footer &operator=(const Footer &);

	  class FooterPrivate;
	  FooterPrivate *d;
	};

  }
}
#endif

/*** End of inlined file: id3v2footer.h ***/


/*** Start of inlined file: id3v2framefactory.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_ID3V2FRAMEFACTORY_H
#define TAGLIB_ID3V2FRAMEFACTORY_H

namespace TagLib {

  namespace ID3v2 {

	class TextIdentificationFrame;

	//! A factory for creating ID3v2 frames during parsing

	/*!
	 * This factory abstracts away the frame creation process and instantiates
	 * the appropriate ID3v2::Frame subclasses based on the contents of the
	 * data.
	 *
	 * Reimplementing this factory is the key to adding support for frame types
	 * not directly supported by TagLib to your application.  To do so you would
	 * subclass this factory reimplement createFrame().  Then by setting your
	 * factory to be the default factory in ID3v2::Tag constructor or with
	 * MPEG::File::setID3v2FrameFactory() you can implement behavior that will
	 * allow for new ID3v2::Frame subclasses (also provided by you) to be used.
	 *
	 * This implements both <i>abstract factory</i> and <i>singleton</i> patterns
	 * of which more information is available on the web and in software design
	 * textbooks (Notably <i>Design Patters</i>).
	 *
	 * \note You do not need to use this factory to create new frames to add to
	 * an ID3v2::Tag.  You can instantiate frame subclasses directly (with new)
	 * and add them to a tag using ID3v2::Tag::addFrame()
	 *
	 * \see ID3v2::Tag::addFrame()
	 */

	class TAGLIB_EXPORT FrameFactory
	{
	public:
	  static FrameFactory *instance();
	  /*!
	   * Create a frame based on \a data.  \a synchSafeInts should only be set
	   * false if we are parsing an old tag (v2.3 or older) that does not support
	   * synchsafe ints.
	   *
	   * \deprecated Please use the method below that accepts a ID3v2::Header
	   * instance in new code.
	   */
	  Frame *createFrame(const ByteVector &data, bool synchSafeInts) const;

	  /*!
	   * Create a frame based on \a data.  \a version should indicate the ID3v2
	   * version of the tag.  As ID3v2.4 is the most current version of the
	   * standard 4 is the default.
	   *
	   * \deprecated Please use the method below that accepts a ID3v2::Header
	   * instance in new code.
	   */
	  Frame *createFrame(const ByteVector &data, uint version = 4) const;

	  /*!
	   * Create a frame based on \a data.  \a tagHeader should be a valid
	   * ID3v2::Header instance.
	   */
	  // BIC: make virtual
	  Frame *createFrame(const ByteVector &data, Header *tagHeader) const;

	  /*!
	   * Returns the default text encoding for text frames.  If setTextEncoding()
	   * has not been explicitly called this will only be used for new text
	   * frames.  However, if this value has been set explicitly all frames will be
	   * converted to this type (unless it's explitly set differently for the
	   * individual frame) when being rendered.
	   *
	   * \see setDefaultTextEncoding()
	   */
	  String::Type defaultTextEncoding() const;

	  /*!
	   * Set the default text encoding for all text frames that are created to
	   * \a encoding.  If no value is set the frames with either default to the
	   * encoding type that was parsed and new frames default to Latin1.
	   *
	   * Valid string types for ID3v2 tags are Latin1, UTF8, UTF16 and UTF16BE.
	   *
	   * \see defaultTextEncoding()
	   */
	  void setDefaultTextEncoding(String::Type encoding);

	protected:
	  /*!
	   * Constructs a frame factory.  Because this is a singleton this method is
	   * protected, but may be used for subclasses.
	   */
	  FrameFactory();

	  /*!
	   * Destroys the frame factory.  In most cases this will never be called (as
	   * is typical of singletons).
	   */
	  virtual ~FrameFactory();

	  /*!
	   * This method checks for compliance to the current ID3v2 standard (2.4)
	   * and does nothing in the common case.  However if a frame is found that
	   * is not compatible with the current standard, this method either updates
	   * the frame or indicates that it should be discarded.
	   *
	   * This method with return true (with or without changes to the frame) if
	   * this frame should be kept or false if it should be discarded.
	   *
	   * See the id3v2.4.0-changes.txt document for further information.
	   */
	  virtual bool updateFrame(Frame::Header *header) const;

	private:
	  FrameFactory(const FrameFactory &);
	  FrameFactory &operator=(const FrameFactory &);

	  /*!
	   * This method is used internally to convert a frame from ID \a from to ID
	   * \a to.  If the frame matches the \a from pattern and converts the frame
	   * ID in the \a header or simply does nothing if the frame ID does not match.
	   */
	  void convertFrame(const char *from, const char *to,
						Frame::Header *header) const;

	  void updateGenre(TextIdentificationFrame *frame) const;

	  static FrameFactory factory;

	  class FrameFactoryPrivate;
	  FrameFactoryPrivate *d;
	};

  }
}

#endif

/*** End of inlined file: id3v2framefactory.h ***/


/*** Start of inlined file: id3v2tag.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_ID3V2TAG_H
#define TAGLIB_ID3V2TAG_H

namespace TagLib {

  class File;

  //! An ID3v2 implementation

  /*!
   * This is a relatively complete and flexible framework for working with ID3v2
   * tags.
   *
   * \see ID3v2::Tag
   */

  namespace ID3v2 {

	class Header;
	class ExtendedHeader;
	class Footer;

	typedef List<Frame *> FrameList;
	typedef Map<ByteVector, FrameList> FrameListMap;

	//! The main class in the ID3v2 implementation

	/*!
	 * This is the main class in the ID3v2 implementation.  It serves two
	 * functions.  This first, as is obvious from the public API, is to provide a
	 * container for the other ID3v2 related classes.  In addition, through the
	 * read() and parse() protected methods, it provides the most basic level of
	 * parsing.  In these methods the ID3v2 tag is extracted from the file and
	 * split into data components.
	 *
	 * ID3v2 tags have several parts, TagLib attempts to provide an interface
	 * for them all.  header(), footer() and extendedHeader() corespond to those
	 * data structures in the ID3v2 standard and the APIs for the classes that
	 * they return attempt to reflect this.
	 *
	 * Also ID3v2 tags are built up from a list of frames, which are in turn
	 * have a header and a list of fields.  TagLib provides two ways of accessing
	 * the list of frames that are in a given ID3v2 tag.  The first is simply
	 * via the frameList() method.  This is just a list of pointers to the frames.
	 * The second is a map from the frame type -- i.e. "COMM" for comments -- and
	 * a list of frames of that type.  (In some cases ID3v2 allows for multiple
	 * frames of the same type, hence this being a map to a list rather than just
	 * a map to an individual frame.)
	 *
	 * More information on the structure of frames can be found in the ID3v2::Frame
	 * class.
	 *
	 * read() and parse() pass binary data to the other ID3v2 class structures,
	 * they do not handle parsing of flags or fields, for instace.  Those are
	 * handled by similar functions within those classes.
	 *
	 * \note All pointers to data structures within the tag will become invalid
	 * when the tag is destroyed.
	 *
	 * \warning Dealing with the nasty details of ID3v2 is not for the faint of
	 * heart and should not be done without much meditation on the spec.  It's
	 * rather long, but if you're planning on messing with this class and others
	 * that deal with the details of ID3v2 (rather than the nice, safe, abstract
	 * TagLib::Tag and friends), it's worth your time to familiarize yourself
	 * with said spec (which is distrubuted with the TagLib sources).  TagLib
	 * tries to do most of the work, but with a little luck, you can still
	 * convince it to generate invalid ID3v2 tags.  The APIs for ID3v2 assume a
	 * working knowledge of ID3v2 structure.  You're been warned.
	 */

	class TAGLIB_EXPORT Tag : public TagLib::Tag
	{
	public:
	  /*!
	   * Constructs an empty ID3v2 tag.
	   *
	   * \note You must create at least one frame for this tag to be valid.
	   */
	  Tag();

	  /*!
	   * Constructs an ID3v2 tag read from \a file starting at \a tagOffset.
	   * \a factory specifies which FrameFactory will be used for the
	   * construction of new frames.
	   *
	   * \note You should be able to ignore the \a factory parameter in almost
	   * all situations.  You would want to specify your own FrameFactory
	   * subclass in the case that you are extending TagLib to support additional
	   * frame types, which would be incorperated into your factory.
	   *
	   * \see FrameFactory
	   */
	  Tag(File *file, long tagOffset,
		  const FrameFactory *factory = FrameFactory::instance());

	  /*!
	   * Destroys this Tag instance.
	   */
	  virtual ~Tag();

	  // Reimplementations.

	  virtual String title() const;
	  virtual String artist() const;
	  virtual String album() const;
	  virtual String comment() const;
	  virtual String genre() const;
	  virtual uint year() const;
	  virtual uint track() const;

	  virtual void setTitle(const String &s);
	  virtual void setArtist(const String &s);
	  virtual void setAlbum(const String &s);
	  virtual void setComment(const String &s);
	  virtual void setGenre(const String &s);
	  virtual void setYear(uint i);
	  virtual void setTrack(uint i);

	  virtual bool isEmpty() const;

	  /*!
	   * Returns a pointer to the tag's header.
	   */
	  Header *header() const;

	  /*!
	   * Returns a pointer to the tag's extended header or null if there is no
	   * extended header.
	   */
	  ExtendedHeader *extendedHeader() const;

	  /*!
	   * Returns a pointer to the tag's footer or null if there is no footer.
	   *
	   * \deprecated I don't see any reason to keep this around since there's
	   * nothing useful to be retrieved from the footer, but well, again, I'm
	   * prone to change my mind, so this gets to stay around until near a
	   * release.
	   */
	  Footer *footer() const;

	  /*!
	   * Returns a reference to the frame list map.  This is an FrameListMap of
	   * all of the frames in the tag.
	   *
	   * This is the most convenient structure for accessing the tag's frames.
	   * Many frame types allow multiple instances of the same frame type so this
	   * is a map of lists.  In most cases however there will only be a single
	   * frame of a certain type.
	   *
	   * Let's say for instance that you wanted to access the frame for total
	   * beats per minute -- the TBPM frame.
	   *
	   * \code
	   * TagLib::MPEG::File f("foo.mp3");
	   *
	   * // Check to make sure that it has an ID3v2 tag
	   *
	   * if(f.ID3v2Tag()) {
	   *
	   *   // Get the list of frames for a specific frame type
	   *
	   *   TagLib::ID3v2::FrameList l = f.ID3v2Tag()->frameListMap()["TBPM"];
	   *
	   *   if(!l.isEmpty())
	   *     std::cout << l.front()->toString() << std::endl;
	   * }
	   *
	   * \endcode
	   *
	   * \warning You should not modify this data structure directly, instead
	   * use addFrame() and removeFrame().
	   *
	   * \see frameList()
	   */
	  const FrameListMap &frameListMap() const;

	  /*!
	   * Returns a reference to the frame list.  This is an FrameList of all of
	   * the frames in the tag in the order that they were parsed.
	   *
	   * This can be useful if for example you want iterate over the tag's frames
	   * in the order that they occur in the tag.
	   *
	   * \warning You should not modify this data structure directly, instead
	   * use addFrame() and removeFrame().
	   */
	  const FrameList &frameList() const;

	  /*!
	   * Returns the frame list for frames with the id \a frameID or an empty
	   * list if there are no frames of that type.  This is just a convenience
	   * and is equivalent to:
	   *
	   * \code
	   * frameListMap()[frameID];
	   * \endcode
	   *
	   * \see frameListMap()
	   */
	  const FrameList &frameList(const ByteVector &frameID) const;

	  /*!
	   * Add a frame to the tag.  At this point the tag takes ownership of
	   * the frame and will handle freeing its memory.
	   *
	   * \note Using this method will invalidate any pointers on the list
	   * returned by frameList()
	   */
	  void addFrame(Frame *frame);

	  /*!
	   * Remove a frame from the tag.  If \a del is true the frame's memory
	   * will be freed; if it is false, it must be deleted by the user.
	   *
	   * \note Using this method will invalidate any pointers on the list
	   * returned by frameList()
	   */
	  void removeFrame(Frame *frame, bool del = true);

	  /*!
	   * Remove all frames of type \a id from the tag and free their memory.
	   *
	   * \note Using this method will invalidate any pointers on the list
	   * returned by frameList()
	   */
	  void removeFrames(const ByteVector &id);

	  /*!
	   * Implements the unified property interface -- export function.
	   * This function does some work to translate the hard-specified ID3v2
	   * frame types into a free-form string-to-stringlist PropertyMap:
	   *  - if ID3v2 frame ID is known by Frame::frameIDToKey(), the returned
	   *    key is used
	   *  - if the frame ID is "TXXX" (user text frame), the description() is
	   *    used as key
	   *  - if the frame ID is "WXXX" (user url frame),
	   *    - if the description is empty or "URL", the key "URL" is used
	   *    - otherwise, the key "URL:<description>" is used;
	   *  - if the frame ID is "COMM" (comments frame),
	   *    - if the description is empty or "COMMENT", the key "COMMENT"
	   *      is used
	   *    - otherwise, the key "COMMENT:<description>" is used;
	   *  - if the frame ID is "USLT" (unsynchronized lyrics),
	   *    - if the description is empty or "LYRICS", the key "LYRICS" is used
	   *    - otherwise, the key "LYRICS:<description>" is used;
	   *  - if the frame ID is "TIPL" (involved peoples list), and if all the
	   *    roles defined in the frame are known in TextIdentificationFrame::involvedPeopleMap(),
	   *    then "<role>=<name>" will be contained in the returned obejct for each
	   *  - if the frame ID is "TMCL" (musician credit list), then
	   *    "PERFORMER:<instrument>=<name>" will be contained in the returned
	   *    PropertyMap for each defined musician
	   *  In any other case, the unsupportedData() of the returned object will contain
	   *  the frame's ID and, in case of a frame ID which is allowed to appear more than
	   *  once, the description, separated by a "/".
	   *
	   */
	  PropertyMap properties() const;

	  /*!
	   * Removes unsupported frames given by \a properties. The elements of
	   * \a properties must be taken from properties().unsupportedData(); they
	   * are of one of the following forms:
	   *  - a four-character frame ID, if the ID3 specification allows only one
	   *    frame with that ID (thus, the frame is uniquely determined)
	   *  - frameID + "/" + description(), when the ID is one of "TXXX", "WXXX",
	   *    "COMM", or "USLT",
	   *  - "UNKNOWN/" + frameID, for frames that could not be parsed by TagLib.
	   *    In that case, *all* unknown frames with the given ID will be removed.
	   */
	  void removeUnsupportedProperties(const StringList &properties);

	  /*!
	   * Implements the unified property interface -- import function.
	   * See the comments in properties().
	   */
	  PropertyMap setProperties(const PropertyMap &);

	  /*!
	   * Render the tag back to binary data, suitable to be written to disk.
	   */
	  ByteVector render() const;

	  /*!
	   * Render the tag back to binary data, suitable to be written to disk.
	   *
	   * The \a version parameter specifies the version of the rendered
	   * ID3v2 tag. It can be either 4 or 3.
	   */
	  // BIC: combine with the above method
	  ByteVector render(int version) const;

	protected:
	  /*!
	   * Reads data from the file specified in the constructor.  It does basic
	   * parsing of the data in the largest chunks.  It partitions the tag into
	   * the Header, the body of the tag  (which contains the ExtendedHeader and
	   * frames) and Footer.
	   */
	  void read();

	  /*!
	   * This is called by read to parse the body of the tag.  It determines if an
	   * extended header exists and adds frames to the FrameListMap.
	   */
	  void parse(const ByteVector &data);

	  /*!
	   * Sets the value of the text frame with the Frame ID \a id to \a value.
	   * If the frame does not exist, it is created.
	   */
	  void setTextFrame(const ByteVector &id, const String &value);

	  void downgradeFrames(FrameList *existingFrames, FrameList *newFrames) const;

	private:
	  Tag(const Tag &);
	  Tag &operator=(const Tag &);

	  class TagPrivate;
	  TagPrivate *d;
	};

  }
}

#endif

/*** End of inlined file: id3v2tag.h ***/


/*** Start of inlined file: attachedpictureframe.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_ATTACHEDPICTUREFRAME_H
#define TAGLIB_ATTACHEDPICTUREFRAME_H

namespace TagLib {

  namespace ID3v2 {

	//! An ID3v2 attached picture frame implementation

	/*!
	 * This is an implementation of ID3v2 attached pictures.  Pictures may be
	 * included in tags, one per APIC frame (but there may be multiple APIC
	 * frames in a single tag).  These pictures are usually in either JPEG or
	 * PNG format.
	 */

	class TAGLIB_EXPORT AttachedPictureFrame : public Frame
	{
	  friend class FrameFactory;

	public:

	  /*!
	   * This describes the function or content of the picture.
	   */
	  enum Type {
		//! A type not enumerated below
		Other              = 0x00,
		//! 32x32 PNG image that should be used as the file icon
		FileIcon           = 0x01,
		//! File icon of a different size or format
		OtherFileIcon      = 0x02,
		//! Front cover image of the album
		FrontCover         = 0x03,
		//! Back cover image of the album
		BackCover          = 0x04,
		//! Inside leaflet page of the album
		LeafletPage        = 0x05,
		//! Image from the album itself
		Media              = 0x06,
		//! Picture of the lead artist or soloist
		LeadArtist         = 0x07,
		//! Picture of the artist or performer
		Artist             = 0x08,
		//! Picture of the conductor
		Conductor          = 0x09,
		//! Picture of the band or orchestra
		Band               = 0x0A,
		//! Picture of the composer
		Composer           = 0x0B,
		//! Picture of the lyricist or text writer
		Lyricist           = 0x0C,
		//! Picture of the recording location or studio
		RecordingLocation  = 0x0D,
		//! Picture of the artists during recording
		DuringRecording    = 0x0E,
		//! Picture of the artists during performance
		DuringPerformance  = 0x0F,
		//! Picture from a movie or video related to the track
		MovieScreenCapture = 0x10,
		//! Picture of a large, coloured fish
		ColouredFish       = 0x11,
		//! Illustration related to the track
		Illustration       = 0x12,
		//! Logo of the band or performer
		BandLogo           = 0x13,
		//! Logo of the publisher (record company)
		PublisherLogo      = 0x14
	  };

	  /*!
	   * Constructs an empty picture frame.  The description, content and text
	   * encoding should be set manually.
	   */
	  AttachedPictureFrame();

	  /*!
	   * Constructs an AttachedPicture frame based on \a data.
	   */
	  explicit AttachedPictureFrame(const ByteVector &data);

	  /*!
	   * Destroys the AttahcedPictureFrame instance.
	   */
	  virtual ~AttachedPictureFrame();

	  /*!
	   * Returns a string containing the description and mime-type
	   */
	  virtual String toString() const;

	  /*!
	   * Returns the text encoding used for the description.
	   *
	   * \see setTextEncoding()
	   * \see description()
	   */
	  String::Type textEncoding() const;

	  /*!
	   * Set the text encoding used for the description.
	   *
	   * \see description()
	   */
	  void setTextEncoding(String::Type t);

	  /*!
	   * Returns the mime type of the image.  This should in most cases be
	   * "image/png" or "image/jpeg".
	   */
	  String mimeType() const;

	  /*!
	   * Sets the mime type of the image.  This should in most cases be
	   * "image/png" or "image/jpeg".
	   */
	  void setMimeType(const String &m);

	  /*!
	   * Returns the type of the image.
	   *
	   * \see Type
	   * \see setType()
	   */
	  Type type() const;

	  /*!
	   * Sets the type for the image.
	   *
	   * \see Type
	   * \see type()
	   */
	  void setType(Type t);

	  /*!
	   * Returns a text description of the image.
	   *
	   * \see setDescription()
	   * \see textEncoding()
	   * \see setTextEncoding()
	   */

	  String description() const;

	  /*!
	   * Sets a textual description of the image to \a desc.
	   *
	   * \see description()
	   * \see textEncoding()
	   * \see setTextEncoding()
	   */

	  void setDescription(const String &desc);

	  /*!
	   * Returns the image data as a ByteVector.
	   *
	   * \note ByteVector has a data() method that returns a const char * which
	   * should make it easy to export this data to external programs.
	   *
	   * \see setPicture()
	   * \see mimeType()
	   */
	  ByteVector picture() const;

	  /*!
	   * Sets the image data to \a p.  \a p should be of the type specified in
	   * this frame's mime-type specification.
	   *
	   * \see picture()
	   * \see mimeType()
	   * \see setMimeType()
	   */
	  void setPicture(const ByteVector &p);

	protected:
	  virtual void parseFields(const ByteVector &data);
	  virtual ByteVector renderFields() const;
	  class AttachedPictureFramePrivate;
	  AttachedPictureFramePrivate *d;

	private:
	  AttachedPictureFrame(const AttachedPictureFrame &);
	  AttachedPictureFrame &operator=(const AttachedPictureFrame &);
	  AttachedPictureFrame(const ByteVector &data, Header *h);

	};

	//! support for ID3v2.2 PIC frames
	class TAGLIB_EXPORT AttachedPictureFrameV22 : public AttachedPictureFrame
	{
	protected:
	  virtual void parseFields(const ByteVector &data);
	private:
	  AttachedPictureFrameV22(const ByteVector &data, Header *h);
	  friend class FrameFactory;
	};
  }
}

#endif

/*** End of inlined file: attachedpictureframe.h ***/


/*** Start of inlined file: commentsframe.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_COMMENTSFRAME_H
#define TAGLIB_COMMENTSFRAME_H

namespace TagLib {

  namespace ID3v2 {

	//! An implementation of ID3v2 comments

	/*!
	 * This implements the ID3v2 comment format.  An ID3v2 comment concists of
	 * a language encoding, a description and a single text field.
	 */

	class TAGLIB_EXPORT CommentsFrame : public Frame
	{
	  friend class FrameFactory;

	public:
	  /*!
	   * Construct an empty comment frame that will use the text encoding
	   * \a encoding.
	   */
	  explicit CommentsFrame(String::Type encoding = String::Latin1);

	  /*!
	   * Construct a comment based on the data in \a data.
	   */
	  explicit CommentsFrame(const ByteVector &data);

	  /*!
	   * Destroys this CommentFrame instance.
	   */
	  virtual ~CommentsFrame();

	  /*!
	   * Returns the text of this comment.
	   *
	   * \see text()
	   */
	  virtual String toString() const;

	  /*!
	   * Returns the language encoding as a 3 byte encoding as specified by
	   * <a href="http://en.wikipedia.org/wiki/ISO_639">ISO-639-2</a>.
	   *
	   * \note Most taggers simply ignore this value.
	   *
	   * \see setLanguage()
	   */
	  ByteVector language() const;

	  /*!
	   * Returns the description of this comment.
	   *
	   * \note Most taggers simply ignore this value.
	   *
	   * \see setDescription()
	   */
	  String description() const;

	  /*!
	   * Returns the text of this comment.
	   *
	   * \see setText()
	   */
	  String text() const;

	  /*!
	   * Set the language using the 3 byte language code from
	   * <a href="http://en.wikipedia.org/wiki/ISO_639">ISO-639-2</a> to
	   * \a languageCode.
	   *
	   * \see language()
	   */
	  void setLanguage(const ByteVector &languageCode);

	  /*!
	   * Sets the description of the comment to \a s.
	   *
	   * \see decription()
	   */
	  void setDescription(const String &s);

	  /*!
	   * Sets the text portion of the comment to \a s.
	   *
	   * \see text()
	   */
	  virtual void setText(const String &s);

	  /*!
	   * Returns the text encoding that will be used in rendering this frame.
	   * This defaults to the type that was either specified in the constructor
	   * or read from the frame when parsed.
	   *
	   * \see setTextEncoding()
	   * \see render()
	   */
	  String::Type textEncoding() const;

	  /*!
	   * Sets the text encoding to be used when rendering this frame to
	   * \a encoding.
	   *
	   * \see textEncoding()
	   * \see render()
	   */
	  void setTextEncoding(String::Type encoding);

	  /*!
	   * Parses this frame as PropertyMap with a single key.
	   * - if description() is empty or "COMMENT", the key will be "COMMENT"
	   * - if description() is not a valid PropertyMap key, the frame will be
	   *   marked unsupported by an entry "COMM/<description>" in the unsupportedData()
	   *   attribute of the returned map.
	   * - otherwise, the key will be "COMMENT:<description>"
	   * - The single value will be the frame's text().
	   */
	  PropertyMap asProperties() const;

	  /*!
	   * Comments each have a unique description.  This searches for a comment
	   * frame with the decription \a d and returns a pointer to it.  If no
	   * frame is found that matches the given description null is returned.
	   *
	   * \see description()
	   */
	  static CommentsFrame *findByDescription(const Tag *tag, const String &d);

	protected:
	  // Reimplementations.

	  virtual void parseFields(const ByteVector &data);
	  virtual ByteVector renderFields() const;

	private:
	  /*!
	   * The constructor used by the FrameFactory.
	   */
	  CommentsFrame(const ByteVector &data, Header *h);
	  CommentsFrame(const CommentsFrame &);
	  CommentsFrame &operator=(const CommentsFrame &);

	  class CommentsFramePrivate;
	  CommentsFramePrivate *d;
	};

  }
}
#endif

/*** End of inlined file: commentsframe.h ***/


/*** Start of inlined file: generalencapsulatedobjectframe.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_GENERALENCAPSULATEDOBJECT_H
#define TAGLIB_GENERALENCAPSULATEDOBJECT_H

namespace TagLib {

  namespace ID3v2 {

	//! An ID3v2 general encapsulated object frame implementation

	/*!
	 * This is an implementation of ID3v2 general encapsulated objects.
	 * Arbitrary binary data may be included in tags, stored in GEOB frames.
	 * There may be multiple GEOB frames in a single tag.  Each GEOB it
	 * labelled with a content description (which may be blank), a required
	 * mime-type, and a file name (may be blank).  The content description
	 * uniquely identifies the GEOB frame in the tag.
	 */

	class TAGLIB_EXPORT GeneralEncapsulatedObjectFrame : public Frame
	{
	  friend class FrameFactory;

	public:

	  /*!
	   * Constructs an empty object frame.  The description, file name and text
	   * encoding should be set manually.
	   */
	  GeneralEncapsulatedObjectFrame();

	  /*!
	   * Constructs a GeneralEncapsulatedObjectFrame frame based on \a data.
	   *
	   * \warning This is \em not data for the encapsulated object, for that use
	   * setObject().  This constructor is used when reading the frame from the
	   * disk.
	   */
	  explicit GeneralEncapsulatedObjectFrame(const ByteVector &data);

	  /*!
	   * Destroys the GeneralEncapsulatedObjectFrame instance.
	   */
	  virtual ~GeneralEncapsulatedObjectFrame();

	  /*!
	   * Returns a string containing the description, file name and mime-type
	   */
	  virtual String toString() const;

	  /*!
	   * Returns the text encoding used for the description and file name.
	   *
	   * \see setTextEncoding()
	   * \see description()
	   * \see fileName()
	   */
	  String::Type textEncoding() const;

	  /*!
	   * Set the text encoding used for the description and file name.
	   *
	   * \see description()
	   * \see fileName()
	   */
	  void setTextEncoding(String::Type encoding);

	  /*!
	   * Returns the mime type of the object.
	   */
	  String mimeType() const;

	  /*!
	   * Sets the mime type of the object.
	   */
	  void setMimeType(const String &type);

	  /*!
	   * Returns the file name of the object.
	   *
	   * \see setFileName()
	   */
	  String fileName() const;

	  /*!
	   * Sets the file name for the object.
	   *
	   * \see fileName()
	   */
	  void setFileName(const String &name);

	  /*!
	   * Returns the content description of the object.
	   *
	   * \see setDescription()
	   * \see textEncoding()
	   * \see setTextEncoding()
	   */

	  String description() const;

	  /*!
	   * Sets the content description of the object to \a desc.
	   *
	   * \see description()
	   * \see textEncoding()
	   * \see setTextEncoding()
	   */

	  void setDescription(const String &desc);

	  /*!
	   * Returns the object data as a ByteVector.
	   *
	   * \note ByteVector has a data() method that returns a const char * which
	   * should make it easy to export this data to external programs.
	   *
	   * \see setObject()
	   * \see mimeType()
	   */
	  ByteVector object() const;

	  /*!
	   * Sets the object data to \a data.  \a data should be of the type specified in
	   * this frame's mime-type specification.
	   *
	   * \see object()
	   * \see mimeType()
	   * \see setMimeType()
	   */
	  void setObject(const ByteVector &object);

	protected:
	  virtual void parseFields(const ByteVector &data);
	  virtual ByteVector renderFields() const;

	private:
	  GeneralEncapsulatedObjectFrame(const ByteVector &data, Header *h);
	  GeneralEncapsulatedObjectFrame(const GeneralEncapsulatedObjectFrame &);
	  GeneralEncapsulatedObjectFrame &operator=(const GeneralEncapsulatedObjectFrame &);

	  class GeneralEncapsulatedObjectFramePrivate;
	  GeneralEncapsulatedObjectFramePrivate *d;
	};
  }
}

#endif

/*** End of inlined file: generalencapsulatedobjectframe.h ***/


/*** Start of inlined file: popularimeterframe.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_POPULARIMETERFRAME_H
#define TAGLIB_POPULARIMETERFRAME_H

namespace TagLib {

  namespace ID3v2 {

	//! An implementation of ID3v2 "popularimeter"

	/*!
	 * This implements the ID3v2 popularimeter (POPM frame).  It concists of
	 * an email, a rating and an optional counter.
	 */

	class TAGLIB_EXPORT PopularimeterFrame : public Frame
	{
	  friend class FrameFactory;

	public:
	  /*!
	   * Construct an empty popularimeter frame.
	   */
	  explicit PopularimeterFrame();

	  /*!
	   * Construct a popularimeter based on the data in \a data.
	   */
	  explicit PopularimeterFrame(const ByteVector &data);

	  /*!
	   * Destroys this PopularimeterFrame instance.
	   */
	  virtual ~PopularimeterFrame();

	  /*!
	   * Returns the text of this popularimeter.
	   *
	   * \see text()
	   */
	  virtual String toString() const;

	  /*!
	   * Returns the email.
	   *
	   * \see setEmail()
	   */
	  String email() const;

	  /*!
	   * Set the email.
	   *
	   * \see email()
	   */
	  void setEmail(const String &email);

	  /*!
	   * Returns the rating.
	   *
	   * \see setRating()
	   */
	  int rating() const;

	  /*!
	   * Set the rating.
	   *
	   * \see rating()
	   */
	  void setRating(int rating);

	  /*!
	   * Returns the counter.
	   *
	   * \see setCounter()
	   */
	  uint counter() const;

	  /*!
	   * Set the counter.
	   *
	   * \see counter()
	   */
	  void setCounter(uint counter);

	protected:
	  // Reimplementations.

	  virtual void parseFields(const ByteVector &data);
	  virtual ByteVector renderFields() const;

	private:
	  /*!
	   * The constructor used by the FrameFactory.
	   */
	  PopularimeterFrame(const ByteVector &data, Header *h);
	  PopularimeterFrame(const PopularimeterFrame &);
	  PopularimeterFrame &operator=(const PopularimeterFrame &);

	  class PopularimeterFramePrivate;
	  PopularimeterFramePrivate *d;
	};

  }
}
#endif

/*** End of inlined file: popularimeterframe.h ***/


/*** Start of inlined file: privateframe.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_PRIVATEFRAME_H
#define TAGLIB_PRIVATEFRAME_H

namespace TagLib {

  namespace ID3v2 {

	//! An implementation of ID3v2 privateframe

	class TAGLIB_EXPORT PrivateFrame : public Frame
	{
	  friend class FrameFactory;

	public:
	  /*!
	   * Construct an empty private frame.
	   */
	  PrivateFrame();

	  /*!
	   * Construct a private frame based on the data in \a data.
	   *
	   * \note This is the constructor used when parsing the frame from a file.
	   */
	  explicit PrivateFrame(const ByteVector &data);

	  /*!
	   * Destroys this private frame instance.
	   */
	  virtual ~PrivateFrame();

	  /*!
	   * Returns the text of this private frame, currently just the owner.
	   *
	   * \see text()
	   */
	  virtual String toString() const;

	  /*!
	   * \return The owner of the private frame.
	   * \note This should contain an email address or link to a website.
	   */
	  String owner() const;

	  /*!
	   *
	   */
	  ByteVector data() const;

	  /*!
	   * Sets the owner of the frame to \a s.
	   * \note This should contain an email address or link to a website.
	   */
	  void setOwner(const String &s);

	  /*!
	   *
	   */
	  void setData(const ByteVector &v);

	protected:
	  // Reimplementations.

	  virtual void parseFields(const ByteVector &data);
	  virtual ByteVector renderFields() const;

	private:
	  /*!
	   * The constructor used by the FrameFactory.
	   */
	  PrivateFrame(const ByteVector &data, Header *h);

	  PrivateFrame(const PrivateFrame &);
	  PrivateFrame &operator=(const PrivateFrame &);

	  class PrivateFramePrivate;
	  PrivateFramePrivate *d;
	};

  }
}
#endif

/*** End of inlined file: privateframe.h ***/


/*** Start of inlined file: relativevolumeframe.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_RELATIVEVOLUMEFRAME_H
#define TAGLIB_RELATIVEVOLUMEFRAME_H

namespace TagLib {

  namespace ID3v2 {

	//! An ID3v2 relative volume adjustment frame implementation

	/*!
	 * This is an implementation of ID3v2 relative volume adjustment.  The
	 * presence of this frame makes it possible to specify an increase in volume
	 * for an audio file or specific audio tracks in that file.
	 *
	 * Multiple relative volume adjustment frames may be present in the tag
	 * each with a unique identification and describing volume adjustment for
	 * different channel types.
	 */

	class TAGLIB_EXPORT RelativeVolumeFrame : public Frame
	{
	  friend class FrameFactory;

	public:

	  /*!
	   * This indicates the type of volume adjustment that should be applied.
	   */
	  enum ChannelType {
		//! A type not enumerated below
		Other        = 0x00,
		//! The master volume for the track
		MasterVolume = 0x01,
		//! The front right audio channel
		FrontRight   = 0x02,
		//! The front left audio channel
		FrontLeft    = 0x03,
		//! The back right audio channel
		BackRight    = 0x04,
		//! The back left audio channel
		BackLeft     = 0x05,
		//! The front center audio channel
		FrontCentre  = 0x06,
		//! The back center audio channel
		BackCentre   = 0x07,
		//! The subwoofer audio channel
		Subwoofer    = 0x08
	  };

	  //! Struct that stores the relevant values for ID3v2 peak volume

	  /*!
	   * The peak volume is described as a series of bits that is padded to fill
	   * a block of bytes.  These two values should always be updated in tandem.
	   */
	  struct PeakVolume
	  {
		/*!
		 * Constructs an empty peak volume description.
		 */
		PeakVolume() : bitsRepresentingPeak(0) {}
		/*!
		 * The number of bits (in the range of 0 to 255) used to describe the
		 * peak volume.
		 */
		unsigned char bitsRepresentingPeak;
		/*!
		 * The array of bits (represented as a series of bytes) used to describe
		 * the peak volume.
		 */
		ByteVector peakVolume;
	  };

	  /*!
	   * Constructs a RelativeVolumeFrame.  The relevant data should be set
	   * manually.
	   */
	  RelativeVolumeFrame();

	  /*!
	   * Constructs a RelativeVolumeFrame based on the contents of \a data.
	   */
	  RelativeVolumeFrame(const ByteVector &data);

	  /*!
	   * Destroys the RelativeVolumeFrame instance.
	   */
	  virtual ~RelativeVolumeFrame();

	  /*!
	   * Returns the frame's identification.
	   *
	   * \see identification()
	   */
	  virtual String toString() const;

	  /*!
	   * Returns a list of channels with information currently in the frame.
	   */
	  List<ChannelType> channels() const;

	  /*!
	   * \deprecated Always returns master volume.
	   */
	  ChannelType channelType() const;

	  /*!
	   * \deprecated This method no longer has any effect.
	   */
	  void setChannelType(ChannelType t);

	  /*
	   * There was a terrible API goof here, and while this can't be changed to
	   * the way it appears below for binary compaibility reasons, let's at
	   * least pretend that it looks clean.
	   */

#ifdef DOXYGEN

	  /*!
	   * Returns the relative volume adjustment "index".  As indicated by the
	   * ID3v2 standard this is a 16-bit signed integer that reflects the
	   * decibils of adjustment when divided by 512.
	   *
	   * This defaults to returning the value for the master volume channel if
	   * available and returns 0 if the specified channel does not exist.
	   *
	   * \see setVolumeAdjustmentIndex()
	   * \see volumeAjustment()
	   */
	  short volumeAdjustmentIndex(ChannelType type = MasterVolume) const;

	  /*!
	   * Set the volume adjustment to \a index.  As indicated by the ID3v2
	   * standard this is a 16-bit signed integer that reflects the decibils of
	   * adjustment when divided by 512.
	   *
	   * By default this sets the value for the master volume.
	   *
	   * \see volumeAdjustmentIndex()
	   * \see setVolumeAjustment()
	   */
	  void setVolumeAdjustmentIndex(short index, ChannelType type = MasterVolume);

	  /*!
	   * Returns the relative volume adjustment in decibels.
	   *
	   * \note Because this is actually stored internally as an "index" to this
	   * value the value returned by this method may not be identical to the
	   * value set using setVolumeAdjustment().
	   *
	   * This defaults to returning the value for the master volume channel if
	   * available and returns 0 if the specified channel does not exist.
	   *
	   * \see setVolumeAdjustment()
	   * \see volumeAdjustmentIndex()
	   */
	  float volumeAdjustment(ChannelType type = MasterVolume) const;

	  /*!
	   * Set the relative volume adjustment in decibels to \a adjustment.
	   *
	   * By default this sets the value for the master volume.
	   *
	   * \note Because this is actually stored internally as an "index" to this
	   * value the value set by this method may not be identical to the one
	   * returned by volumeAdjustment().
	   *
	   * \see setVolumeAdjustment()
	   * \see volumeAdjustmentIndex()
	   */
	  void setVolumeAdjustment(float adjustment, ChannelType type = MasterVolume);

	  /*!
	   * Returns the peak volume (represented as a length and a string of bits).
	   *
	   * This defaults to returning the value for the master volume channel if
	   * available and returns 0 if the specified channel does not exist.
	   *
	   * \see setPeakVolume()
	   */
	  PeakVolume peakVolume(ChannelType type = MasterVolume) const;

	  /*!
	   * Sets the peak volume to \a peak.
	   *
	   * By default this sets the value for the master volume.
	   *
	   * \see peakVolume()
	   */
	  void setPeakVolume(const PeakVolume &peak, ChannelType type = MasterVolume);

#else

	  // BIC: Combine each of the following pairs of functions (or maybe just
	  // rework this junk altogether).

	  short volumeAdjustmentIndex(ChannelType type) const;
	  short volumeAdjustmentIndex() const;

	  void setVolumeAdjustmentIndex(short index, ChannelType type);
	  void setVolumeAdjustmentIndex(short index);

	  float volumeAdjustment(ChannelType type) const;
	  float volumeAdjustment() const;

	  void setVolumeAdjustment(float adjustment, ChannelType type);
	  void setVolumeAdjustment(float adjustment);

	  PeakVolume peakVolume(ChannelType type) const;
	  PeakVolume peakVolume() const;

	  void setPeakVolume(const PeakVolume &peak, ChannelType type);
	  void setPeakVolume(const PeakVolume &peak);

#endif

	  /*!
	   * Returns the identification for this frame.
	   */
	  String identification() const;

	  /*!
	   * Sets the identification of the frame to \a s. The string
	   * is used to identify the situation and/or device where this
	   * adjustment should apply.
	   */
	  void setIdentification(const String &s);

	protected:
	  virtual void parseFields(const ByteVector &data);
	  virtual ByteVector renderFields() const;

	private:
	  RelativeVolumeFrame(const ByteVector &data, Header *h);
	  RelativeVolumeFrame(const RelativeVolumeFrame &);
	  RelativeVolumeFrame &operator=(const RelativeVolumeFrame &);

	  class RelativeVolumeFramePrivate;
	  RelativeVolumeFramePrivate *d;
	};

  }
}
#endif

/*** End of inlined file: relativevolumeframe.h ***/


/*** Start of inlined file: textidentificationframe.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_TEXTIDENTIFICATIONFRAME_H
#define TAGLIB_TEXTIDENTIFICATIONFRAME_H

namespace TagLib {

  namespace ID3v2 {

	class Tag;
	typedef Map<String, String> KeyConversionMap;

	//! An ID3v2 text identification frame implementation

	/*!
	 * This is an implementation of the most common type of ID3v2 frame -- text
	 * identification frames.  There are a number of variations on this.  Those
	 * enumerated in the ID3v2.4 standard are:
	 *
	 * <ul>
	 *   <li><b>TALB</b> Album/Movie/Show title</li>
	 *   <li><b>TBPM</b> BPM (beats per minute)</li>
	 *   <li><b>TCOM</b> Composer</li>
	 *   <li><b>TCON</b> Content type</li>
	 *   <li><b>TCOP</b> Copyright message</li>
	 *   <li><b>TDEN</b> Encoding time</li>
	 *   <li><b>TDLY</b> Playlist delay</li>
	 *   <li><b>TDOR</b> Original release time</li>
	 *   <li><b>TDRC</b> Recording time</li>
	 *   <li><b>TDRL</b> Release time</li>
	 *   <li><b>TDTG</b> Tagging time</li>
	 *   <li><b>TENC</b> Encoded by</li>
	 *   <li><b>TEXT</b> Lyricist/Text writer</li>
	 *   <li><b>TFLT</b> File type</li>
	 *   <li><b>TIPL</b> Involved people list</li>
	 *   <li><b>TIT1</b> Content group description</li>
	 *   <li><b>TIT2</b> Title/songname/content description</li>
	 *   <li><b>TIT3</b> Subtitle/Description refinement</li>
	 *   <li><b>TKEY</b> Initial key</li>
	 *   <li><b>TLAN</b> Language(s)</li>
	 *   <li><b>TLEN</b> Length</li>
	 *   <li><b>TMCL</b> Musician credits list</li>
	 *   <li><b>TMED</b> Media type</li>
	 *   <li><b>TMOO</b> Mood</li>
	 *   <li><b>TOAL</b> Original album/movie/show title</li>
	 *   <li><b>TOFN</b> Original filename</li>
	 *   <li><b>TOLY</b> Original lyricist(s)/text writer(s)</li>
	 *   <li><b>TOPE</b> Original artist(s)/performer(s)</li>
	 *   <li><b>TOWN</b> File owner/licensee</li>
	 *   <li><b>TPE1</b> Lead performer(s)/Soloist(s)</li>
	 *   <li><b>TPE2</b> Band/orchestra/accompaniment</li>
	 *   <li><b>TPE3</b> Conductor/performer refinement</li>
	 *   <li><b>TPE4</b> Interpreted, remixed, or otherwise modified by</li>
	 *   <li><b>TPOS</b> Part of a set</li>
	 *   <li><b>TPRO</b> Produced notice</li>
	 *   <li><b>TPUB</b> Publisher</li>
	 *   <li><b>TRCK</b> Track number/Position in set</li>
	 *   <li><b>TRSN</b> Internet radio station name</li>
	 *   <li><b>TRSO</b> Internet radio station owner</li>
	 *   <li><b>TSOA</b> Album sort order</li>
	 *   <li><b>TSOP</b> Performer sort order</li>
	 *   <li><b>TSOT</b> Title sort order</li>
	 *   <li><b>TSRC</b> ISRC (international standard recording code)</li>
	 *   <li><b>TSSE</b> Software/Hardware and settings used for encoding</li>
	 *   <li><b>TSST</b> Set subtitle</li>
	 * </ul>
	 *
	 * The ID3v2 Frames document gives a description of each of these formats
	 * and the expected order of strings in each.  ID3v2::Header::frameID() can
	 * be used to determine the frame type.
	 *
	 * \note If non-Latin1 compatible strings are used with this class, even if
	 * the text encoding is set to Latin1, the frame will be written using UTF8
	 * (with the encoding flag appropriately set in the output).
	 */

	class TAGLIB_EXPORT TextIdentificationFrame : public Frame
	{
	  friend class FrameFactory;

	public:
	  /*!
	   * Construct an empty frame of type \a type.  Uses \a encoding as the
	   * default text encoding.
	   *
	   * \note In this case you must specify the text encoding as it
	   * resolves the ambiguity between constructors.
	   *
	   * \note Please see the note in the class description regarding Latin1.
	   */
	  TextIdentificationFrame(const ByteVector &type, String::Type encoding);

	  /*!
	   * This is a dual purpose constructor.  \a data can either be binary data
	   * that should be parsed or (at a minimum) the frame ID.
	   */
	  explicit TextIdentificationFrame(const ByteVector &data);

	  /*!
	   * This is a special factory method to create a TIPL (involved people list)
	   * frame from the given \a properties. Will parse key=[list of values] data
	   * into the TIPL format as specified in the ID3 standard.
	   */
	  static TextIdentificationFrame *createTIPLFrame(const PropertyMap &properties);

	  /*!
	   * This is a special factory method to create a TMCL (musician credits list)
	   * frame from the given \a properties. Will parse key=[list of values] data
	   * into the TMCL format as specified in the ID3 standard, where key should be
	   * of the form instrumentPrefix:instrument.
	   */
	  static TextIdentificationFrame *createTMCLFrame(const PropertyMap &properties);
	  /*!
	   * Destroys this TextIdentificationFrame instance.
	   */
	  virtual ~TextIdentificationFrame();

	  /*!
	   * Text identification frames are a list of string fields.
	   *
	   * This function will accept either a StringList or a String (using the
	   * StringList constructor that accepts a single String).
	   *
	   * \note This will not change the text encoding of the frame even if the
	   * strings passed in are not of the same encoding.  Please use
	   * setEncoding(s.type()) if you wish to change the encoding of the frame.
	   */
	  void setText(const StringList &l);

	  // Reimplementations.

	  virtual void setText(const String &s);
	  virtual String toString() const;

	  /*!
	   * Returns the text encoding that will be used in rendering this frame.
	   * This defaults to the type that was either specified in the constructor
	   * or read from the frame when parsed.
	   *
	   * \note Please see the note in the class description regarding Latin1.
	   *
	   * \see setTextEncoding()
	   * \see render()
	   */
	  String::Type textEncoding() const;

	  /*!
	   * Sets the text encoding to be used when rendering this frame to
	   * \a encoding.
	   *
	   * \note Please see the note in the class description regarding Latin1.
	   *
	   * \see textEncoding()
	   * \see render()
	   */
	  void setTextEncoding(String::Type encoding);

	  /*!
	   * Returns a list of the strings in this frame.
	   */
	  StringList fieldList() const;

	  /*!
	   * Returns a KeyConversionMap mapping a role as it would be  used in a PropertyMap
	   * to the corresponding key used in a TIPL ID3 frame to describe that role.
	   */
	  static const KeyConversionMap &involvedPeopleMap();

	  PropertyMap asProperties() const;

	protected:
	  // Reimplementations.

	  virtual void parseFields(const ByteVector &data);
	  virtual ByteVector renderFields() const;

	  /*!
	   * The constructor used by the FrameFactory.
	   */
	  TextIdentificationFrame(const ByteVector &data, Header *h);

	private:
	  TextIdentificationFrame(const TextIdentificationFrame &);
	  TextIdentificationFrame &operator=(const TextIdentificationFrame &);

	  /*!
	   * Parses the special structure of a TIPL frame
	   * Only the whitelisted roles "ARRANGER", "ENGINEER", "PRODUCER",
	   * "DJMIXER" (ID3: "DJ-MIX") and "MIXER" (ID3: "MIX") are allowed.
	   */
	  PropertyMap makeTIPLProperties() const;
	  /*!
	   * Parses the special structure of a TMCL frame.
	   */
	  PropertyMap makeTMCLProperties() const;
	  class TextIdentificationFramePrivate;
	  TextIdentificationFramePrivate *d;
	};

	/*!
	 * This is a specialization of text identification frames that allows for
	 * user defined entries.  Each entry has a description in addition to the
	 * normal list of fields that a text identification frame has.
	 *
	 * This description identifies the frame and must be unique.
	 */

	//! An ID3v2 custom text identification frame implementationx

	class TAGLIB_EXPORT UserTextIdentificationFrame : public TextIdentificationFrame
	{
	  friend class FrameFactory;

	public:
	  /*!
	   * Constructs an empty user defined text identification frame.  For this to be
	   * a useful frame both a description and text must be set.
	   */
	  explicit UserTextIdentificationFrame(String::Type encoding = String::Latin1);

	  /*!
	   * Creates a frame based on \a data.
	   */
	  explicit UserTextIdentificationFrame(const ByteVector &data);

	  /*!
	   * Creates a user defined text identification frame with the given \a description
	   * and \a values.
	   */
	  UserTextIdentificationFrame(const String &description, const StringList &values, String::Type encoding = String::UTF8);

	  virtual String toString() const;

	  /*!
	   * Returns the description for this frame.
	   */
	  String description() const;

	  /*!
	   * Sets the description of the frame to \a s.  \a s must be unique.  You can
	   * check for the presence of another user defined text frame of the same type
	   * using find() and testing for null.
	   */
	  void setDescription(const String &s);

	  StringList fieldList() const;
	  void setText(const String &text);
	  void setText(const StringList &fields);

	  /*!
	   * A UserTextIdentificationFrame is parsed into a PropertyMap as follows:
	   * - the key is the frame's description, uppercased
	   * - if the description contains '::', only the substring after that
	   *   separator is considered as key (compatibility with exfalso)
	   * - if the above rules don't yield a valid key (e.g. containing non-ASCII
	   *   characters), the returned map will contain an entry "TXXX/<description>"
	   *   in its unsupportedData() list.
	   * - The values will be copies of the fieldList().
	   * - If the description() appears as value in fieldList(), it will be omitted
	   *   in the value list, in order to be compatible with TagLib which copies
	   *   the description() into the fieldList().
	   */
	  PropertyMap asProperties() const;

	  /*!
	   * Searches for the user defined text frame with the description \a description
	   * in \a tag.  This returns null if no matching frames were found.
	   */
	  static UserTextIdentificationFrame *find(Tag *tag, const String &description);

	private:
	  UserTextIdentificationFrame(const ByteVector &data, Header *h);
	  UserTextIdentificationFrame(const TextIdentificationFrame &);
	  UserTextIdentificationFrame &operator=(const UserTextIdentificationFrame &);

	  void checkFields();

	  class UserTextIdentificationFramePrivate;
	  UserTextIdentificationFramePrivate *d;
	};

  }
}
#endif

/*** End of inlined file: textidentificationframe.h ***/


/*** Start of inlined file: uniquefileidentifierframe.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_UNIQUEFILEIDENTIFIERFRAME
#define TAGLIB_UNIQUEFILEIDENTIFIERFRAME

namespace TagLib {

  namespace ID3v2 {

	/*!
	 * This is an implementation of ID3v2 unique file identifier frames.  This
	 * frame is used to identify the file in an arbitrary database identified
	 * by the owner field.
	 */

	//! An implementation of ID3v2 unique identifier frames

	class TAGLIB_EXPORT UniqueFileIdentifierFrame : public ID3v2::Frame
	{
	  friend class FrameFactory;

	public:
	  /*!
	   * Creates a uniqe file identifier frame based on \a data.
	   */
	  UniqueFileIdentifierFrame(const ByteVector &data);

	  /*!
	   * Creates a unique file identifier frame with the owner \a owner and
	   * the identification \a id.
	   */
	  UniqueFileIdentifierFrame(const String &owner, const ByteVector &id);

	  /*!
	   * Destroys the frame.
	   */
	  ~UniqueFileIdentifierFrame();

	  /*!
	   * Returns the owner for the frame; essentially this is the key for
	   * determining which identification scheme this key belongs to.  This
	   * will usually either be an email address or URL for the person or tool
	   * used to create the unique identifier.
	   *
	   * \see setOwner()
	   */
	  String owner() const;

	  /*!
	   * Returns the unique identifier.  Though sometimes this is a text string
	   * it also may be binary data and as much should be assumed when handling
	   * it.
	   */
	  ByteVector identifier() const;

	  /*!
	   * Sets the owner of the identification scheme to \a s.
	   *
	   * \see owner()
	   */
	  void setOwner(const String &s);

	  /*!
	   * Sets the unique file identifier to \a v.
	   *
	   * \see identifier()
	   */
	  void setIdentifier(const ByteVector &v);

	  virtual String toString() const;

	protected:
	  virtual void parseFields(const ByteVector &data);
	  virtual ByteVector renderFields() const;

	private:
	  UniqueFileIdentifierFrame(const UniqueFileIdentifierFrame &);
	  UniqueFileIdentifierFrame &operator=(const UniqueFileIdentifierFrame &);

	  UniqueFileIdentifierFrame(const ByteVector &data, Header *h);

	  class UniqueFileIdentifierFramePrivate;
	  UniqueFileIdentifierFramePrivate *d;
	};
  }
}

#endif

/*** End of inlined file: uniquefileidentifierframe.h ***/


/*** Start of inlined file: unknownframe.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_UNKNOWNFRAME_H
#define TAGLIB_UNKNOWNFRAME_H

namespace TagLib {

  namespace ID3v2 {

	//! A frame type \e unknown to TagLib.

	/*!
	 * This class represents a frame type not known (or more often simply
	 * unimplemented) in TagLib.  This is here provide a basic API for
	 * manipulating the binary data of unknown frames and to provide a means
	 * of rendering such \e unknown frames.
	 *
	 * Please note that a cleaner way of handling frame types that TagLib
	 * does not understand is to subclass ID3v2::Frame and ID3v2::FrameFactory
	 * to have your frame type supported through the standard ID3v2 mechanism.
	 */

	class TAGLIB_EXPORT UnknownFrame : public Frame
	{
	  friend class FrameFactory;

	public:
	  UnknownFrame(const ByteVector &data);
	  virtual ~UnknownFrame();

	  virtual String toString() const;

	  /*!
	   * Returns the field data (everything but the header) for this frame.
	   */
	  ByteVector data() const;

	protected:
	  virtual void parseFields(const ByteVector &data);
	  virtual ByteVector renderFields() const;

	private:
	  UnknownFrame(const ByteVector &data, Header *h);
	  UnknownFrame(const UnknownFrame &);
	  UnknownFrame &operator=(const UnknownFrame &);

	  class UnknownFramePrivate;
	  UnknownFramePrivate *d;
	};

  }
}
#endif

/*** End of inlined file: unknownframe.h ***/


/*** Start of inlined file: unsynchronizedlyricsframe.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it  under the terms of the GNU Lesser General Public License version  *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_UNSYNCHRONIZEDLYRICSFRAME_H
#define TAGLIB_UNSYNCHRONIZEDLYRICSFRAME_H

namespace TagLib {

  namespace ID3v2 {

	//! ID3v2 unsynchronized lyrics frame
	/*!
	 * An implementation of ID3v2 unsynchronized lyrics.
	 */
	class TAGLIB_EXPORT UnsynchronizedLyricsFrame : public Frame
	{
	  friend class FrameFactory;

	public:
	  /*!
	   * Construct an empty unsynchronized lyrics frame that will use the text encoding
	   * \a encoding.
	   */
	  explicit UnsynchronizedLyricsFrame(String::Type encoding = String::Latin1);

	  /*!
	   * Construct a unsynchronized lyrics frame based on the data in \a data.
	   */
	  explicit UnsynchronizedLyricsFrame(const ByteVector &data);

	  /*!
	   * Destroys this UnsynchronizedLyricsFrame instance.
	   */
	  virtual ~UnsynchronizedLyricsFrame();

	  /*!
	   * Returns the text of this unsynchronized lyrics frame.
	   *
	   * \see text()
	   */
	  virtual String toString() const;

	  /*!
	   * Returns the language encoding as a 3 byte encoding as specified by
	   * <a href="http://en.wikipedia.org/wiki/ISO_639">ISO-639-2</a>.
	   *
	   * \note Most taggers simply ignore this value.
	   *
	   * \see setLanguage()
	   */
	  ByteVector language() const;

	  /*!
	   * Returns the description of this unsynchronized lyrics frame.
	   *
	   * \note Most taggers simply ignore this value.
	   *
	   * \see setDescription()
	   */
	  String description() const;

	  /*!
	   * Returns the text of this unsynchronized lyrics frame.
	   *
	   * \see setText()
	   */
	  String text() const;

	  /*!
	   * Set the language using the 3 byte language code from
	   * <a href="http://en.wikipedia.org/wiki/ISO_639">ISO-639-2</a> to
	   * \a languageCode.
	   *
	   * \see language()
	   */
	  void setLanguage(const ByteVector &languageCode);

	  /*!
	   * Sets the description of the unsynchronized lyrics frame to \a s.
	   *
	   * \see decription()
	   */
	  void setDescription(const String &s);

	  /*!
	   * Sets the text portion of the unsynchronized lyrics frame to \a s.
	   *
	   * \see text()
	   */
	  virtual void setText(const String &s);

	  /*!
	   * Returns the text encoding that will be used in rendering this frame.
	   * This defaults to the type that was either specified in the constructor
	   * or read from the frame when parsed.
	   *
	   * \see setTextEncoding()
	   * \see render()
	   */
	  String::Type textEncoding() const;

	  /*!
	   * Sets the text encoding to be used when rendering this frame to
	   * \a encoding.
	   *
	   * \see textEncoding()
	   * \see render()
	   */
	  void setTextEncoding(String::Type encoding);

	  /*! Parses this frame as PropertyMap with a single key.
	   * - if description() is empty or "LYRICS", the key will be "LYRICS"
	   * - if description() is not a valid PropertyMap key, the frame will be
	   *   marked unsupported by an entry "USLT/<description>" in the unsupportedData()
	   *   attribute of the returned map.
	   * - otherwise, the key will be "LYRICS:<description>"
	   * - The single value will be the frame's text().
	   * Note that currently the language() field is not supported by the PropertyMap
	   * interface.
	   */
	  PropertyMap asProperties() const;

	  /*!
	   * LyricsFrames each have a unique description.  This searches for a lyrics
	   * frame with the decription \a d and returns a pointer to it.  If no
	   * frame is found that matches the given description null is returned.
	   *
	   * \see description()
	   */
	  static UnsynchronizedLyricsFrame *findByDescription(const Tag *tag, const String &d);

	protected:
	  // Reimplementations.

	  virtual void parseFields(const ByteVector &data);
	  virtual ByteVector renderFields() const;

	private:
	  /*!
	   * The constructor used by the FrameFactory.
	   */
	  UnsynchronizedLyricsFrame(const ByteVector &data, Header *h);
	  UnsynchronizedLyricsFrame(const UnsynchronizedLyricsFrame &);
	  UnsynchronizedLyricsFrame &operator=(const UnsynchronizedLyricsFrame &);

	  class UnsynchronizedLyricsFramePrivate;
	  UnsynchronizedLyricsFramePrivate *d;
	};

  }
}
#endif

/*** End of inlined file: unsynchronizedlyricsframe.h ***/


/*** Start of inlined file: urllinkframe.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_URLLINKFRAME_H
#define TAGLIB_URLLINKFRAME_H

namespace TagLib {

  namespace ID3v2 {

	//! ID3v2 URL frame
	/*!
	 * An implementation of ID3v2 URL link frames.
	 */
	class TAGLIB_EXPORT UrlLinkFrame : public Frame
	{
	  friend class FrameFactory;

	public:
	  /*!
	   * This is a dual purpose constructor.  \a data can either be binary data
	   * that should be parsed or (at a minimum) the frame ID.
	   */
	  explicit UrlLinkFrame(const ByteVector &data);

	  /*!
	   * Destroys this UrlLinkFrame instance.
	   */
	  virtual ~UrlLinkFrame();

	  /*!
	   * Returns the URL.
	   */
	  virtual String url() const;

	  /*!
	   * Sets the URL to \a s.
	   */
	  virtual void setUrl(const String &s);

	  // Reimplementations.

	  virtual void setText(const String &s);
	  virtual String toString() const;
	  PropertyMap asProperties() const;

	protected:
	  virtual void parseFields(const ByteVector &data);
	  virtual ByteVector renderFields() const;

	  /*!
	   * The constructor used by the FrameFactory.
	   */
	  UrlLinkFrame(const ByteVector &data, Header *h);

	private:
	  UrlLinkFrame(const UrlLinkFrame &);
	  UrlLinkFrame &operator=(const UrlLinkFrame &);

	  class UrlLinkFramePrivate;
	  UrlLinkFramePrivate *d;
	};

	//! ID3v2 User defined URL frame

	/*!
	 * This is a specialization of URL link frames that allows for
	 * user defined entries.  Each entry has a description in addition to the
	 * normal list of fields that a URL link frame has.
	 *
	 * This description identifies the frame and must be unique.
	 */
	class TAGLIB_EXPORT UserUrlLinkFrame : public UrlLinkFrame
	{
	  friend class FrameFactory;

	public:
	  /*!
	   * Constructs an empty user defined URL link frame.  For this to be
	   * a useful frame both a description and text must be set.
	   */
	  explicit UserUrlLinkFrame(String::Type encoding = String::Latin1);

	  /*!
	   * This is a dual purpose constructor.  \a data can either be binary data
	   * that should be parsed or (at a minimum) the frame ID.
	   */
	  explicit UserUrlLinkFrame(const ByteVector &data);

	  /*!
	   * Destroys this UserUrlLinkFrame instance.
	   */
	  virtual ~UserUrlLinkFrame();

	  // Reimplementations.

	  virtual String toString() const;

	  /*!
	   * Returns the text encoding that will be used in rendering this frame.
	   * This defaults to the type that was either specified in the constructor
	   * or read from the frame when parsed.
	   *
	   * \see setTextEncoding()
	   * \see render()
	   */
	  String::Type textEncoding() const;

	  /*!
	   * Sets the text encoding to be used when rendering this frame to
	   * \a encoding.
	   *
	   * \see textEncoding()
	   * \see render()
	   */
	  void setTextEncoding(String::Type encoding);

	  /*!
	   * Returns the description for this frame.
	   */
	  String description() const;

	  /*!
	   * Sets the description of the frame to \a s.  \a s must be unique.
	   */
	  void setDescription(const String &s);

	  /*!
	   * Parses the UserUrlLinkFrame as PropertyMap. The description() is taken as key,
	   * and the URL as single value.
	   * - if description() is empty, the key will be "URL".
	   * - otherwise, if description() is not a valid key (e.g. containing non-ASCII
	   *   characters), the returned map will contain an entry "WXXX/<description>"
	   *   in its unsupportedData() list.
	   */
	  PropertyMap asProperties() const;

	  /*!
	   * Searches for the user defined url frame with the description \a description
	   * in \a tag.  This returns null if no matching frames were found.
	   */
	  static UserUrlLinkFrame *find(Tag *tag, const String &description);

	protected:
	  virtual void parseFields(const ByteVector &data);
	  virtual ByteVector renderFields() const;

	  /*!
	   * The constructor used by the FrameFactory.
	   */
	  UserUrlLinkFrame(const ByteVector &data, Header *h);

	private:
	  UserUrlLinkFrame(const UserUrlLinkFrame &);
	  UserUrlLinkFrame &operator=(const UserUrlLinkFrame &);

	  class UserUrlLinkFramePrivate;
	  UserUrlLinkFramePrivate *d;
	};

  }
}
#endif

/*** End of inlined file: urllinkframe.h ***/


/*** Start of inlined file: oggfile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_OGGFILE_H
#define TAGLIB_OGGFILE_H

namespace TagLib {

  //! A namespace for the classes used by Ogg-based metadata files

  namespace Ogg {

	class PageHeader;

	//! An implementation of TagLib::File with some helpers for Ogg based formats

	/*!
	 * This is an implementation of Ogg file page and packet rendering and is of
	 * use to Ogg based formats.  While the API is small this handles the
	 * non-trivial details of breaking up an Ogg stream into packets and makes
	 * these available (via subclassing) to the codec meta data implementations.
	 */

	class TAGLIB_EXPORT File : public TagLib::File
	{
	public:
	  virtual ~File();

	  /*!
	   * Returns the packet contents for the i-th packet (starting from zero)
	   * in the Ogg bitstream.
	   *
	   * \warning The requires reading at least the packet header for every page
	   * up to the requested page.
	   */
	  ByteVector packet(uint i);

	  /*!
	   * Sets the packet with index \a i to the value \a p.
	   */
	  void setPacket(uint i, const ByteVector &p);

	  /*!
	   * Returns a pointer to the PageHeader for the first page in the stream or
	   * null if the page could not be found.
	   */
	  const PageHeader *firstPageHeader();

	  /*!
	   * Returns a pointer to the PageHeader for the last page in the stream or
	   * null if the page could not be found.
	   */
	  const PageHeader *lastPageHeader();

	  virtual bool save();

	protected:
	  /*!
	   * Contructs an Ogg file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   *
	   * \note This constructor is protected since Ogg::File shouldn't be
	   * instantiated directly but rather should be used through the codec
	   * specific subclasses.
	   */
	  File(FileName file);

	  /*!
	   * Contructs an Ogg file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   *
	   * \note This constructor is protected since Ogg::File shouldn't be
	   * instantiated directly but rather should be used through the codec
	   * specific subclasses.
	   */
	  File(IOStream *stream);

	private:
	  File(const File &);
	  File &operator=(const File &);

	  /*!
	   * Reads the next page and updates the internal "current page" pointer.
	   */
	  bool nextPage();
	  void writePageGroup(const List<int> &group);

	  class FilePrivate;
	  FilePrivate *d;
	};

  }
}

#endif

/*** End of inlined file: oggfile.h ***/


/*** Start of inlined file: oggpage.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_OGGPAGE_H
#define TAGLIB_OGGPAGE_H

namespace TagLib {

  namespace Ogg {

	class File;
	class PageHeader;

	//! An implementation of Ogg pages

	/*!
	 * This is an implementation of the pages that make up an Ogg stream.
	 * This handles parsing pages and breaking them down into packets and handles
	 * the details of packets spanning multiple pages and pages that contiain
	 * multiple packets.
	 *
	 * In most Xiph.org formats the comments are found in the first few packets,
	 * this however is a reasonably complete implementation of Ogg pages that
	 * could potentially be useful for non-meta data purposes.
	 */

	class TAGLIB_EXPORT Page
	{
	public:
	  /*!
	   * Read an Ogg page from the \a file at the position \a pageOffset.
	   */
	  Page(File *file, long pageOffset);

	  virtual ~Page();

	  /*!
	   * Returns the page's position within the file (in bytes).
	   */
	  long fileOffset() const;

	  /*!
	   * Returns a pointer to the header for this page.  This pointer will become
	   * invalid when the page is deleted.
	   */
	  const PageHeader *header() const;

	  /*!
	   * Returns a copy of the page with \a sequenceNumber set as sequence number.
	   *
	   * \see header()
	   * \see PageHeader::setPageSequenceNumber()
	   */
	  Page* getCopyWithNewPageSequenceNumber(int sequenceNumber);

	  /*!
	   * Returns the index of the first packet wholly or partially contained in
	   * this page.
	   *
	   * \see setFirstPacketIndex()
	   */
	  int firstPacketIndex() const;

	  /*!
	   * Sets the index of the first packet in the page.
	   *
	   * \see firstPacketIndex()
	   */
	  void setFirstPacketIndex(int index);

	  /*!
	   * When checking to see if a page contains a given packet this set of flags
	   * represents the possible values for that packets status in the page.
	   *
	   * \see containsPacket()
	   */
	  enum ContainsPacketFlags {
		//! No part of the packet is contained in the page
		DoesNotContainPacket = 0x0000,
		//! The packet is wholly contained in the page
		CompletePacket       = 0x0001,
		//! The page starts with the given packet
		BeginsWithPacket     = 0x0002,
		//! The page ends with the given packet
		EndsWithPacket       = 0x0004
	  };

	  /*!
	   * Checks to see if the specified \a packet is contained in the current
	   * page.
	   *
	   * \see ContainsPacketFlags
	   */
	  ContainsPacketFlags containsPacket(int index) const;

	  /*!
	   * Returns the number of packets (whole or partial) in this page.
	   */
	  uint packetCount() const;

	  /*!
	   * Returns a list of the packets in this page.
	   *
	   * \note Either or both the first and last packets may be only partial.
	   * \see PageHeader::firstPacketContinued()
	   */
	  ByteVectorList packets() const;

	  /*!
	   * Returns the size of the page in bytes.
	   */
	  int size() const;

	  ByteVector render() const;

	  /*!
	   * Defines a strategy for pagination, or grouping pages into Ogg packets,
	   * for use with pagination methods.
	   *
	   * \note Yes, I'm aware that this is not a canonical "Strategy Pattern",
	   * the term was simply convenient.
	   */
	  enum PaginationStrategy {
		/*!
		 * Attempt to put the specified set of packets into a single Ogg packet.
		 * If the sum of the packet data is greater than will fit into a single
		 * Ogg page -- 65280 bytes -- this will fall back to repagination using
		 * the recommended page sizes.
		 */
		SinglePagePerGroup,
		/*!
		 * Split the packet or group of packets into pages that conform to the
		 * sizes recommended in the Ogg standard.
		 */
		Repaginate
	  };

	  /*!
	   * Pack \a packets into Ogg pages using the \a strategy for pagination.
	   * The page number indicater inside of the rendered packets will start
	   * with \a firstPage and be incremented for each page rendered.
	   * \a containsLastPacket should be set to true if \a packets contains the
	   * last page in the stream and will set the appropriate flag in the last
	   * rendered Ogg page's header.  \a streamSerialNumber should be set to
	   * the serial number for this stream.
	   *
	   * \note The "absolute granule position" is currently always zeroed using
	   * this method as this suffices for the comment headers.
	   *
	   * \warning The pages returned by this method must be deleted by the user.
	   * You can use List<T>::setAutoDelete(true) to set these pages to be
	   * automatically deleted when this list passes out of scope.
	   *
	   * \see PaginationStrategy
	   * \see List::setAutoDelete()
	   */
	  static List<Page *> paginate(const ByteVectorList &packets,
								   PaginationStrategy strategy,
								   uint streamSerialNumber,
								   int firstPage,
								   bool firstPacketContinued = false,
								   bool lastPacketCompleted = true,
								   bool containsLastPacket = false);

	protected:
	  /*!
	   * Creates an Ogg packet based on the data in \a packets.  The page number
	   * for each page will be set to \a pageNumber.
	   */
	  Page(const ByteVectorList &packets,
		   uint streamSerialNumber,
		   int pageNumber,
		   bool firstPacketContinued = false,
		   bool lastPacketCompleted = true,
		   bool containsLastPacket = false);

	private:
	  Page(const Page &);
	  Page &operator=(const Page &);

	  class PagePrivate;
	  PagePrivate *d;
	};
  }
}
#endif

/*** End of inlined file: oggpage.h ***/


/*** Start of inlined file: oggpageheader.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_OGGPAGEHEADER_H
#define TAGLIB_OGGPAGEHEADER_H

namespace TagLib {

  namespace Ogg {

	class File;

	//! An implementation of the page headers associated with each Ogg::Page

	/*!
	 * This class implements Ogg page headers which contain the information
	 * about Ogg pages needed to break them into packets which can be passed on
	 * to the codecs.
	 */

	class TAGLIB_EXPORT PageHeader
	{
	public:
	  /*!
	   * Reads a PageHeader from \a file starting at \a pageOffset.  The defaults
	   * create a page with no (and as such, invalid) data that must be set
	   * later.
	   */
	  PageHeader(File *file = 0, long pageOffset = -1);

	  /*!
	   * Deletes this instance of the PageHeader.
	   */
	  virtual ~PageHeader();

	  /*!
	   * Returns true if the header parsed properly and is valid.
	   */
	  bool isValid() const;

	  /*!
	   * Ogg pages contain a list of packets (which are used by the contained
	   * codecs).  The sizes of these pages is encoded in the page header.  This
	   * returns a list of the packet sizes in bytes.
	   *
	   * \see setPacketSizes()
	   */
	  List<int> packetSizes() const;

	  /*!
	   * Sets the sizes of the packets in this page to \a sizes.  Internally this
	   * updates the lacing values in the header.
	   *
	   * \see packetSizes()
	   */
	  void setPacketSizes(const List<int> &sizes);

	  /*!
	   * Some packets can be <i>continued</i> across multiple pages.  If the
	   * first packet in the current page is a continuation this will return
	   * true.  If this is page starts with a new packet this will return false.
	   *
	   * \see lastPacketCompleted()
	   * \see setFirstPacketContinued()
	   */
	  bool firstPacketContinued() const;

	  /*!
	   * Sets the internal flag indicating if the first packet in this page is
	   * continued to \a continued.
	   *
	   * \see firstPacketContinued()
	   */
	  void setFirstPacketContinued(bool continued);

	  /*!
	   * Returns true if the last packet of this page is completely contained in
	   * this page.
	   *
	   * \see firstPacketContinued()
	   * \see setLastPacketCompleted()
	   */
	  bool lastPacketCompleted() const;

	  /*!
	   * Sets the internal flag indicating if the last packet in this page is
	   * complete to \a completed.
	   *
	   * \see lastPacketCompleted()
	   */
	  void setLastPacketCompleted(bool completed);

	  /*!
	   * This returns true if this is the first page of the Ogg (logical) stream.
	   *
	   * \see setFirstPageOfStream()
	   */
	  bool firstPageOfStream() const;

	  /*!
	   * Marks this page as the first page of the Ogg stream.
	   *
	   * \see firstPageOfStream()
	   */
	  void setFirstPageOfStream(bool first);

	  /*!
	   * This returns true if this is the last page of the Ogg (logical) stream.
	   *
	   * \see setLastPageOfStream()
	   */
	  bool lastPageOfStream() const;

	  /*!
	   * Marks this page as the last page of the Ogg stream.
	   *
	   * \see lastPageOfStream()
	   */
	  void setLastPageOfStream(bool last);

	  /*!
	   * A special value of containing the position of the packet to be
	   * interpreted by the codec.  In the case of Vorbis this contains the PCM
	   * value and is used to calculate the length of the stream.
	   *
	   * \see setAbsoluteGranularPosition()
	   */
	  long long absoluteGranularPosition() const;

	  /*!
	   * A special value of containing the position of the packet to be
	   * interpreted by the codec.  It is only supported here so that it may be
	   * coppied from one page to another.
	   *
	   * \see absoluteGranularPosition()
	   */
	  void setAbsoluteGranularPosition(long long agp);

	  /*!
	   * Every Ogg logical stream is given a random serial number which is common
	   * to every page in that logical stream.  This returns the serial number of
	   * the stream associated with this packet.
	   *
	   * \see setStreamSerialNumber()
	   */
	  uint streamSerialNumber() const;

	  /*!
	   * Every Ogg logical stream is given a random serial number which is common
	   * to every page in that logical stream.  This sets this pages serial
	   * number.  This method should be used when adding new pages to a logical
	   * stream.
	   *
	   * \see streamSerialNumber()
	   */
	  void setStreamSerialNumber(uint n);

	  /*!
	   * Returns the index of the page within the Ogg stream.  This helps make it
	   * possible to determine if pages have been lost.
	   *
	   * \see setPageSequenceNumber()
	   */
	  int pageSequenceNumber() const;

	  /*!
	   * Sets the page's position in the stream to \a sequenceNumber.
	   *
	   * \see pageSequenceNumber()
	   */
	  void setPageSequenceNumber(int sequenceNumber);

	  /*!
	   * Returns the complete header size.
	   */
	  int size() const;

	  /*!
	   * Returns the size of the data portion of the page -- i.e. the size of the
	   * page less the header size.
	   */
	  int dataSize() const;

	  /*!
	   * Render the page header to binary data.
	   *
	   * \note The checksum -- bytes 22 - 25 -- will be left empty and must be
	   * filled in when rendering the entire page.
	   */
	  ByteVector render() const;

	private:
	  PageHeader(const PageHeader &);
	  PageHeader &operator=(const PageHeader &);

	  void read();
	  ByteVector lacingValues() const;

	  class PageHeaderPrivate;
	  PageHeaderPrivate *d;
	};

  }
}

#endif

/*** End of inlined file: oggpageheader.h ***/


/*** Start of inlined file: xiphcomment.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_VORBISCOMMENT_H
#define TAGLIB_VORBISCOMMENT_H

namespace TagLib {

  namespace Ogg {

	/*!
	 * A mapping between a list of field names, or keys, and a list of values
	 * associated with that field.
	 *
	 * \see XiphComment::fieldListMap()
	 */
	typedef Map<String, StringList> FieldListMap;

	//! Ogg Vorbis comment implementation

	/*!
	 * This class is an implementation of the Ogg Vorbis comment specification,
	 * to be found in section 5 of the Ogg Vorbis specification.  Because this
	 * format is also used in other (currently unsupported) Xiph.org formats, it
	 * has been made part of a generic implementation rather than being limited
	 * to strictly Vorbis.
	 *
	 * Vorbis comments are a simple vector of keys and values, called fields.
	 * Multiple values for a given key are supported.
	 *
	 * \see fieldListMap()
	 */

	class TAGLIB_EXPORT XiphComment : public TagLib::Tag
	{
	public:
	  /*!
	   * Constructs an empty Vorbis comment.
	   */
	  XiphComment();

	  /*!
	   * Constructs a Vorbis comment from \a data.
	   */
	  XiphComment(const ByteVector &data);

	  /*!
	   * Destroys this instance of the XiphComment.
	   */
	  virtual ~XiphComment();

	  virtual String title() const;
	  virtual String artist() const;
	  virtual String album() const;
	  virtual String comment() const;
	  virtual String genre() const;
	  virtual uint year() const;
	  virtual uint track() const;

	  virtual void setTitle(const String &s);
	  virtual void setArtist(const String &s);
	  virtual void setAlbum(const String &s);
	  virtual void setComment(const String &s);
	  virtual void setGenre(const String &s);
	  virtual void setYear(uint i);
	  virtual void setTrack(uint i);

	  virtual bool isEmpty() const;

	  /*!
	   * Returns the number of fields present in the comment.
	   */
	  uint fieldCount() const;

	  /*!
	   * Returns a reference to the map of field lists.  Because Xiph comments
	   * support multiple fields with the same key, a pure Map would not work.
	   * As such this is a Map of string lists, keyed on the comment field name.
	   *
	   * The standard set of Xiph/Vorbis fields (which may or may not be
	   * contained in any specific comment) is:
	   *
	   * <ul>
	   *   <li>TITLE</li>
	   *   <li>VERSION</li>
	   *   <li>ALBUM</li>
	   *   <li>ARTIST</li>
	   *   <li>PERFORMER</li>
	   *   <li>COPYRIGHT</li>
	   *   <li>ORGANIZATION</li>
	   *   <li>DESCRIPTION</li>
	   *   <li>GENRE</li>
	   *   <li>DATE</li>
	   *   <li>LOCATION</li>
	   *   <li>CONTACT</li>
	   *   <li>ISRC</li>
	   * </ul>
	   *
	   * For a more detailed description of these fields, please see the Ogg
	   * Vorbis specification, section 5.2.2.1.
	   *
	   * \note The Ogg Vorbis comment specification does allow these key values
	   * to be either upper or lower case.  However, it is conventional for them
	   * to be upper case.  As such, TagLib, when parsing a Xiph/Vorbis comment,
	   * converts all fields to uppercase.  When you are using this data
	   * structure, you will need to specify the field name in upper case.
	   *
	   * \warning You should not modify this data structure directly, instead
	   * use addField() and removeField().
	   */
	  const FieldListMap &fieldListMap() const;

	  /*!
	   * Implements the unified property interface -- export function.
	   * The result is a one-to-one match of the Xiph comment, since it is
	   * completely compatible with the property interface (in fact, a Xiph
	   * comment is nothing more than a map from tag names to list of values,
	   * as is the dict interface).
	   */
	  PropertyMap properties() const;

	  /*!
	   * Implements the unified property interface -- import function.
	   * The tags from the given map will be stored one-to-one in the file.
	   */
	  PropertyMap setProperties(const PropertyMap&);

	  /*!
	   * Returns the vendor ID of the Ogg Vorbis encoder.  libvorbis 1.0 as the
	   * most common case always returns "Xiph.Org libVorbis I 20020717".
	   */
	  String vendorID() const;

	  /*!
	   * Add the field specified by \a key with the data \a value.  If \a replace
	   * is true, then all of the other fields with the same key will be removed
	   * first.
	   *
	   * If the field value is empty, the field will be removed.
	   */
	  void addField(const String &key, const String &value, bool replace = true);

	  /*!
	   * Remove the field specified by \a key with the data \a value.  If
	   * \a value is null, all of the fields with the given key will be removed.
	   */
	  void removeField(const String &key, const String &value = String::null);

	  /*!
	   * Returns true if the field is contained within the comment.
	   *
	   * \note This is safer than checking for membership in the FieldListMap.
	   */
	  bool contains(const String &key) const;

	  /*!
	   * Renders the comment to a ByteVector suitable for inserting into a file.
	   */
	  ByteVector render() const; // BIC: remove and merge with below

	  /*!
	   * Renders the comment to a ByteVector suitable for inserting into a file.
	   *
	   * If \a addFramingBit is true the standard Vorbis comment framing bit will
	   * be appended.  However some formats (notably FLAC) do not work with this
	   * in place.
	   */
	  ByteVector render(bool addFramingBit) const;

	protected:
	  /*!
	   * Reads the tag from the file specified in the constructor and fills the
	   * FieldListMap.
	   */
	  void parse(const ByteVector &data);

	private:
	  XiphComment(const XiphComment &);
	  XiphComment &operator=(const XiphComment &);

	  class XiphCommentPrivate;
	  XiphCommentPrivate *d;
	};
  }
}

#endif

/*** End of inlined file: xiphcomment.h ***/


/*** Start of inlined file: vorbisfile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_VORBISFILE_H
#define TAGLIB_VORBISFILE_H


/*** Start of inlined file: oggfile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_OGGFILE_H
#define TAGLIB_OGGFILE_H

namespace TagLib {

  //! A namespace for the classes used by Ogg-based metadata files

  namespace Ogg {

	class PageHeader;

	//! An implementation of TagLib::File with some helpers for Ogg based formats

	/*!
	 * This is an implementation of Ogg file page and packet rendering and is of
	 * use to Ogg based formats.  While the API is small this handles the
	 * non-trivial details of breaking up an Ogg stream into packets and makes
	 * these available (via subclassing) to the codec meta data implementations.
	 */

	class TAGLIB_EXPORT File : public TagLib::File
	{
	public:
	  virtual ~File();

	  /*!
	   * Returns the packet contents for the i-th packet (starting from zero)
	   * in the Ogg bitstream.
	   *
	   * \warning The requires reading at least the packet header for every page
	   * up to the requested page.
	   */
	  ByteVector packet(uint i);

	  /*!
	   * Sets the packet with index \a i to the value \a p.
	   */
	  void setPacket(uint i, const ByteVector &p);

	  /*!
	   * Returns a pointer to the PageHeader for the first page in the stream or
	   * null if the page could not be found.
	   */
	  const PageHeader *firstPageHeader();

	  /*!
	   * Returns a pointer to the PageHeader for the last page in the stream or
	   * null if the page could not be found.
	   */
	  const PageHeader *lastPageHeader();

	  virtual bool save();

	protected:
	  /*!
	   * Contructs an Ogg file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   *
	   * \note This constructor is protected since Ogg::File shouldn't be
	   * instantiated directly but rather should be used through the codec
	   * specific subclasses.
	   */
	  File(FileName file);

	  /*!
	   * Contructs an Ogg file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   *
	   * \note This constructor is protected since Ogg::File shouldn't be
	   * instantiated directly but rather should be used through the codec
	   * specific subclasses.
	   */
	  File(IOStream *stream);

	private:
	  File(const File &);
	  File &operator=(const File &);

	  /*!
	   * Reads the next page and updates the internal "current page" pointer.
	   */
	  bool nextPage();
	  void writePageGroup(const List<int> &group);

	  class FilePrivate;
	  FilePrivate *d;
	};

  }
}

#endif

/*** End of inlined file: oggfile.h ***/


/*** Start of inlined file: vorbisproperties.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_VORBISPROPERTIES_H
#define TAGLIB_VORBISPROPERTIES_H

namespace TagLib {

/*
 * This is just to make this appear to be in the Ogg namespace in the
 * documentation.  The typedef below will make this work with the current code.
 * In the next BIC version of TagLib this will be really moved into the Ogg
 * namespace.
 */

#ifdef DOXYGEN
  namespace Ogg {
#endif

  namespace Vorbis {

	class File;

	//! An implementation of audio property reading for Ogg Vorbis

	/*!
	 * This reads the data from an Ogg Vorbis stream found in the AudioProperties
	 * API.
	 */

	class TAGLIB_EXPORT Properties : public AudioProperties
	{
	public:
	  /*!
	   * Create an instance of Vorbis::Properties with the data read from the
	   * Vorbis::File \a file.
	   */
	  Properties(File *file, ReadStyle style = Average);

	  /*!
	   * Destroys this VorbisProperties instance.
	   */
	  virtual ~Properties();

	  // Reimplementations.

	  virtual int length() const;
	  virtual int bitrate() const;
	  virtual int sampleRate() const;
	  virtual int channels() const;

	  /*!
	   * Returns the Vorbis version, currently "0" (as specified by the spec).
	   */
	  int vorbisVersion() const;

	  /*!
	   * Returns the maximum bitrate as read from the Vorbis identification
	   * header.
	   */
	  int bitrateMaximum() const;

	  /*!
	   * Returns the nominal bitrate as read from the Vorbis identification
	   * header.
	   */
	  int bitrateNominal() const;

	  /*!
	   * Returns the minimum bitrate as read from the Vorbis identification
	   * header.
	   */
	  int bitrateMinimum() const;

	private:
	  Properties(const Properties &);
	  Properties &operator=(const Properties &);

	  void read();

	  class PropertiesPrivate;
	  PropertiesPrivate *d;
	};
  }

/*
 * To keep compatibility with the current version put Vorbis in the Ogg namespace
 * only in the docs and provide a typedef to make it work.  In the next BIC
 * version this will be removed and it will only exist in the Ogg namespace.
 */

#ifdef DOXYGEN
  }
#else
  namespace Ogg { namespace Vorbis { typedef TagLib::AudioProperties AudioProperties; } }
#endif

}

#endif

/*** End of inlined file: vorbisproperties.h ***/

namespace TagLib {

/*
 * This is just to make this appear to be in the Ogg namespace in the
 * documentation.  The typedef below will make this work with the current code.
 * In the next BIC version of TagLib this will be really moved into the Ogg
 * namespace.
 */

#ifdef DOXYGEN
  namespace Ogg {
#endif

  //! A namespace containing classes for Vorbis metadata

  namespace Vorbis {

	//! An implementation of Ogg::File with Vorbis specific methods

	/*!
	 * This is the central class in the Ogg Vorbis metadata processing collection
	 * of classes.  It's built upon Ogg::File which handles processing of the Ogg
	 * logical bitstream and breaking it down into pages which are handled by
	 * the codec implementations, in this case Vorbis specifically.
	 */

	class TAGLIB_EXPORT File : public Ogg::File
	{
	public:
	  /*!
	   * Contructs a Vorbis file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   */
	  File(FileName file, bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Contructs a Vorbis file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   */
	  File(IOStream *stream, bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Destroys this instance of the File.
	   */
	  virtual ~File();

	  /*!
	   * Returns the XiphComment for this file.  XiphComment implements the tag
	   * interface, so this serves as the reimplementation of
	   * TagLib::File::tag().
	   */
	  virtual Ogg::XiphComment *tag() const;

	  /*!
	   * Implements the unified property interface -- export function.
	   * This forwards directly to XiphComment::properties().
	   */
	  PropertyMap properties() const;

	  /*!
	   * Implements the unified tag dictionary interface -- import function.
	   * Like properties(), this is a forwarder to the file's XiphComment.
	   */
	  PropertyMap setProperties(const PropertyMap &);

	  /*!
	   * Returns the Vorbis::Properties for this file.  If no audio properties
	   * were read then this will return a null pointer.
	   */
	  virtual Properties *audioProperties() const;

	  virtual bool save();

	private:
	  File(const File &);
	  File &operator=(const File &);

	  void read(bool readProperties, Properties::ReadStyle propertiesStyle);

	  class FilePrivate;
	  FilePrivate *d;
	};
  }

/*
 * To keep compatibility with the current version put Vorbis in the Ogg namespace
 * only in the docs and provide a typedef to make it work.  In the next BIC
 * version this will be removed and it will only exist in the Ogg namespace.
 */

#ifdef DOXYGEN
  }
#else
  namespace Ogg { namespace Vorbis { typedef TagLib::Vorbis::File File; } }
#endif

}

#endif

/*** End of inlined file: vorbisfile.h ***/


/*** Start of inlined file: oggflacfile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_OGGFLACFILE_H
#define TAGLIB_OGGFLACFILE_H


/*** Start of inlined file: oggfile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_OGGFILE_H
#define TAGLIB_OGGFILE_H

namespace TagLib {

  //! A namespace for the classes used by Ogg-based metadata files

  namespace Ogg {

	class PageHeader;

	//! An implementation of TagLib::File with some helpers for Ogg based formats

	/*!
	 * This is an implementation of Ogg file page and packet rendering and is of
	 * use to Ogg based formats.  While the API is small this handles the
	 * non-trivial details of breaking up an Ogg stream into packets and makes
	 * these available (via subclassing) to the codec meta data implementations.
	 */

	class TAGLIB_EXPORT File : public TagLib::File
	{
	public:
	  virtual ~File();

	  /*!
	   * Returns the packet contents for the i-th packet (starting from zero)
	   * in the Ogg bitstream.
	   *
	   * \warning The requires reading at least the packet header for every page
	   * up to the requested page.
	   */
	  ByteVector packet(uint i);

	  /*!
	   * Sets the packet with index \a i to the value \a p.
	   */
	  void setPacket(uint i, const ByteVector &p);

	  /*!
	   * Returns a pointer to the PageHeader for the first page in the stream or
	   * null if the page could not be found.
	   */
	  const PageHeader *firstPageHeader();

	  /*!
	   * Returns a pointer to the PageHeader for the last page in the stream or
	   * null if the page could not be found.
	   */
	  const PageHeader *lastPageHeader();

	  virtual bool save();

	protected:
	  /*!
	   * Contructs an Ogg file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   *
	   * \note This constructor is protected since Ogg::File shouldn't be
	   * instantiated directly but rather should be used through the codec
	   * specific subclasses.
	   */
	  File(FileName file);

	  /*!
	   * Contructs an Ogg file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   *
	   * \note This constructor is protected since Ogg::File shouldn't be
	   * instantiated directly but rather should be used through the codec
	   * specific subclasses.
	   */
	  File(IOStream *stream);

	private:
	  File(const File &);
	  File &operator=(const File &);

	  /*!
	   * Reads the next page and updates the internal "current page" pointer.
	   */
	  bool nextPage();
	  void writePageGroup(const List<int> &group);

	  class FilePrivate;
	  FilePrivate *d;
	};

  }
}

#endif

/*** End of inlined file: oggfile.h ***/


/*** Start of inlined file: flacproperties.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_FLACPROPERTIES_H
#define TAGLIB_FLACPROPERTIES_H

namespace TagLib {

  namespace FLAC {

	class File;

	//! An implementation of audio property reading for FLAC

	/*!
	 * This reads the data from an FLAC stream found in the AudioProperties
	 * API.
	 */

	class TAGLIB_EXPORT Properties : public AudioProperties
	{
	public:
	  /*!
	   * Create an instance of FLAC::Properties with the data read from the
	   * ByteVector \a data.
	   */
	   // BIC: switch to const reference
	  Properties(ByteVector data, long streamLength, ReadStyle style = Average);

	  /*!
	   * Create an instance of FLAC::Properties with the data read from the
	   * FLAC::File \a file.
	   */
	   // BIC: remove
	  Properties(File *file, ReadStyle style = Average);

	  /*!
	   * Destroys this FLAC::Properties instance.
	   */
	  virtual ~Properties();

	  // Reimplementations.

	  virtual int length() const;
	  virtual int bitrate() const;
	  virtual int sampleRate() const;
	  virtual int channels() const;

	  /*!
	   * Returns the sample width as read from the FLAC identification
	   * header.
	   */
	  int sampleWidth() const;

	  /*!
	   * Return the number of sample frames
	   */
	  unsigned long long sampleFrames() const;

	  /*!
	   * Returns the MD5 signature of the uncompressed audio stream as read
	   * from the stream info header header.
	   */
	  ByteVector signature() const;

	private:
	  Properties(const Properties &);
	  Properties &operator=(const Properties &);

	  void read();

	  class PropertiesPrivate;
	  PropertiesPrivate *d;
	};
  }
}

#endif

/*** End of inlined file: flacproperties.h ***/

namespace TagLib {

  class Tag;

  namespace Ogg {

  //! An implementation of Ogg FLAC metadata

  /*!
   * This is implementation of FLAC metadata for Ogg FLAC files.  For "pure"
   * FLAC files look under the FLAC hiearchy.
   *
   * Unlike "pure" FLAC-files, Ogg FLAC only supports Xiph-comments,
   * while the audio-properties are the same.
   */
  namespace FLAC {

	using TagLib::FLAC::Properties;

	//! An implementation of TagLib::File with Ogg/FLAC specific methods

	/*!
	 * This implements and provides an interface for Ogg/FLAC files to the
	 * TagLib::Tag and TagLib::AudioProperties interfaces by way of implementing
	 * the abstract TagLib::File API as well as providing some additional
	 * information specific to Ogg FLAC files.
	 */

	class TAGLIB_EXPORT File : public Ogg::File
	{
	public:
	  /*!
	   * Contructs an Ogg/FLAC file from \a file.  If \a readProperties is true
	   * the file's audio properties will also be read using \a propertiesStyle.
	   * If false, \a propertiesStyle is ignored.
	   */
	  File(FileName file, bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Contructs an Ogg/FLAC file from \a file.  If \a readProperties is true
	   * the file's audio properties will also be read using \a propertiesStyle.
	   * If false, \a propertiesStyle is ignored.
	   */
	  File(IOStream *stream, bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Destroys this instance of the File.
	   */
	  virtual ~File();

	  /*!
	   * Returns the Tag for this file.  This will always be a XiphComment.
	   */
	  virtual XiphComment *tag() const;

	  /*!
	   * Returns the FLAC::Properties for this file.  If no audio properties
	   * were read then this will return a null pointer.
	   */
	  virtual Properties *audioProperties() const;

	  /*!
	   * Save the file.  This will primarily save and update the XiphComment.
	   * Returns true if the save is successful.
	   */
	  virtual bool save();

	  /*!
	   * Returns the length of the audio-stream, used by FLAC::Properties for
	   * calculating the bitrate.
	   */
	  long streamLength();

	private:
	  File(const File &);
	  File &operator=(const File &);

	  void read(bool readProperties, Properties::ReadStyle propertiesStyle);
	  void scan();
	  ByteVector streamInfoData();
	  ByteVector xiphCommentData();

	  class FilePrivate;
	  FilePrivate *d;
	};
  } // namespace FLAC
  } // namespace Ogg
} // namespace TagLib

#endif

/*** End of inlined file: oggflacfile.h ***/


/*** Start of inlined file: speexfile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_SPEEXFILE_H
#define TAGLIB_SPEEXFILE_H


/*** Start of inlined file: oggfile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_OGGFILE_H
#define TAGLIB_OGGFILE_H

namespace TagLib {

  //! A namespace for the classes used by Ogg-based metadata files

  namespace Ogg {

	class PageHeader;

	//! An implementation of TagLib::File with some helpers for Ogg based formats

	/*!
	 * This is an implementation of Ogg file page and packet rendering and is of
	 * use to Ogg based formats.  While the API is small this handles the
	 * non-trivial details of breaking up an Ogg stream into packets and makes
	 * these available (via subclassing) to the codec meta data implementations.
	 */

	class TAGLIB_EXPORT File : public TagLib::File
	{
	public:
	  virtual ~File();

	  /*!
	   * Returns the packet contents for the i-th packet (starting from zero)
	   * in the Ogg bitstream.
	   *
	   * \warning The requires reading at least the packet header for every page
	   * up to the requested page.
	   */
	  ByteVector packet(uint i);

	  /*!
	   * Sets the packet with index \a i to the value \a p.
	   */
	  void setPacket(uint i, const ByteVector &p);

	  /*!
	   * Returns a pointer to the PageHeader for the first page in the stream or
	   * null if the page could not be found.
	   */
	  const PageHeader *firstPageHeader();

	  /*!
	   * Returns a pointer to the PageHeader for the last page in the stream or
	   * null if the page could not be found.
	   */
	  const PageHeader *lastPageHeader();

	  virtual bool save();

	protected:
	  /*!
	   * Contructs an Ogg file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   *
	   * \note This constructor is protected since Ogg::File shouldn't be
	   * instantiated directly but rather should be used through the codec
	   * specific subclasses.
	   */
	  File(FileName file);

	  /*!
	   * Contructs an Ogg file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   *
	   * \note This constructor is protected since Ogg::File shouldn't be
	   * instantiated directly but rather should be used through the codec
	   * specific subclasses.
	   */
	  File(IOStream *stream);

	private:
	  File(const File &);
	  File &operator=(const File &);

	  /*!
	   * Reads the next page and updates the internal "current page" pointer.
	   */
	  bool nextPage();
	  void writePageGroup(const List<int> &group);

	  class FilePrivate;
	  FilePrivate *d;
	};

  }
}

#endif

/*** End of inlined file: oggfile.h ***/


/*** Start of inlined file: speexproperties.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_SPEEXPROPERTIES_H
#define TAGLIB_SPEEXPROPERTIES_H

namespace TagLib {

  namespace Ogg {

	namespace Speex {

	  class File;

	  //! An implementation of audio property reading for Ogg Speex

	  /*!
	   * This reads the data from an Ogg Speex stream found in the AudioProperties
	   * API.
	   */

	  class TAGLIB_EXPORT Properties : public AudioProperties
	  {
	  public:
		/*!
		 * Create an instance of Speex::Properties with the data read from the
		 * Speex::File \a file.
		 */
		Properties(File *file, ReadStyle style = Average);

		/*!
		 * Destroys this Speex::Properties instance.
		 */
		virtual ~Properties();

		// Reimplementations.

		virtual int length() const;
		virtual int bitrate() const;
		virtual int sampleRate() const;
		virtual int channels() const;

		/*!
		 * Returns the Speex version, currently "0" (as specified by the spec).
		 */
		int speexVersion() const;

	  private:
		Properties(const Properties &);
		Properties &operator=(const Properties &);

		void read();

		class PropertiesPrivate;
		PropertiesPrivate *d;
	  };
	}
  }
}

#endif

/*** End of inlined file: speexproperties.h ***/

namespace TagLib {

  namespace Ogg {

	//! A namespace containing classes for Speex metadata

	namespace Speex {

	  //! An implementation of Ogg::File with Speex specific methods

	  /*!
	   * This is the central class in the Ogg Speex metadata processing collection
	   * of classes.  It's built upon Ogg::File which handles processing of the Ogg
	   * logical bitstream and breaking it down into pages which are handled by
	   * the codec implementations, in this case Speex specifically.
	   */

	  class TAGLIB_EXPORT File : public Ogg::File
	  {
	  public:
		/*!
		 * Contructs a Speex file from \a file.  If \a readProperties is true the
		 * file's audio properties will also be read using \a propertiesStyle.  If
		 * false, \a propertiesStyle is ignored.
		 */
		File(FileName file, bool readProperties = true,
			 Properties::ReadStyle propertiesStyle = Properties::Average);

		/*!
		 * Contructs a Speex file from \a file.  If \a readProperties is true the
		 * file's audio properties will also be read using \a propertiesStyle.  If
		 * false, \a propertiesStyle is ignored.
		 */
		File(IOStream *stream, bool readProperties = true,
			 Properties::ReadStyle propertiesStyle = Properties::Average);

		/*!
		 * Destroys this instance of the File.
		 */
		virtual ~File();

		/*!
		 * Returns the XiphComment for this file.  XiphComment implements the tag
		 * interface, so this serves as the reimplementation of
		 * TagLib::File::tag().
		 */
		virtual Ogg::XiphComment *tag() const;

		/*!
		 * Returns the Speex::Properties for this file.  If no audio properties
		 * were read then this will return a null pointer.
		 */
		virtual Properties *audioProperties() const;

		virtual bool save();

	  private:
		File(const File &);
		File &operator=(const File &);

		void read(bool readProperties, Properties::ReadStyle propertiesStyle);

		class FilePrivate;
		FilePrivate *d;
	  };
	}
  }
}

#endif

/*** End of inlined file: speexfile.h ***/


/*** Start of inlined file: flacfile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_FLACFILE_H
#define TAGLIB_FLACFILE_H


/*** Start of inlined file: flacpicture.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_FLACPICTURE_H
#define TAGLIB_FLACPICTURE_H


/*** Start of inlined file: flacmetadatablock.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_FLACMETADATABLOCK_H
#define TAGLIB_FLACMETADATABLOCK_H

namespace TagLib {

  namespace FLAC {

	class TAGLIB_EXPORT MetadataBlock
	{
	public:
	  MetadataBlock();
	  virtual ~MetadataBlock();

	  enum BlockType {
		StreamInfo = 0,
		Padding,
		Application,
		SeekTable,
		VorbisComment,
		CueSheet,
		Picture
	  };

	  /*!
	   * Returns the FLAC metadata block type.
	   */
	  virtual int code() const = 0;

	  /*!
	   * Render the content of the block.
	   */
	  virtual ByteVector render() const = 0;

	private:
	  MetadataBlock(const MetadataBlock &item);
	  MetadataBlock &operator=(const MetadataBlock &item);

	  class MetadataBlockPrivate;
	  MetadataBlockPrivate *d;
	};

  }

}

#endif

/*** End of inlined file: flacmetadatablock.h ***/

namespace TagLib {

  namespace FLAC {

	class TAGLIB_EXPORT Picture : public MetadataBlock
	{
	public:

	  /*!
	   * This describes the function or content of the picture.
	   */
	  enum Type {
		//! A type not enumerated below
		Other              = 0x00,
		//! 32x32 PNG image that should be used as the file icon
		FileIcon           = 0x01,
		//! File icon of a different size or format
		OtherFileIcon      = 0x02,
		//! Front cover image of the album
		FrontCover         = 0x03,
		//! Back cover image of the album
		BackCover          = 0x04,
		//! Inside leaflet page of the album
		LeafletPage        = 0x05,
		//! Image from the album itself
		Media              = 0x06,
		//! Picture of the lead artist or soloist
		LeadArtist         = 0x07,
		//! Picture of the artist or performer
		Artist             = 0x08,
		//! Picture of the conductor
		Conductor          = 0x09,
		//! Picture of the band or orchestra
		Band               = 0x0A,
		//! Picture of the composer
		Composer           = 0x0B,
		//! Picture of the lyricist or text writer
		Lyricist           = 0x0C,
		//! Picture of the recording location or studio
		RecordingLocation  = 0x0D,
		//! Picture of the artists during recording
		DuringRecording    = 0x0E,
		//! Picture of the artists during performance
		DuringPerformance  = 0x0F,
		//! Picture from a movie or video related to the track
		MovieScreenCapture = 0x10,
		//! Picture of a large, coloured fish
		ColouredFish       = 0x11,
		//! Illustration related to the track
		Illustration       = 0x12,
		//! Logo of the band or performer
		BandLogo           = 0x13,
		//! Logo of the publisher (record company)
		PublisherLogo      = 0x14
	  };

	  Picture();
	  Picture(const ByteVector &data);
	  ~Picture();

	  /*!
	   * Returns the type of the image.
	   */
	  Type type() const;

	  /*!
	   * Sets the type of the image.
	   */
	  void setType(Type type);

	  /*!
	   * Returns the mime type of the image.  This should in most cases be
	   * "image/png" or "image/jpeg".
	   */
	  String mimeType() const;

	  /*!
	   * Sets the mime type of the image.  This should in most cases be
	   * "image/png" or "image/jpeg".
	   */
	  void setMimeType(const String &m);

	  /*!
	   * Returns a text description of the image.
	   */

	  String description() const;

	  /*!
	   * Sets a textual description of the image to \a desc.
	   */

	  void setDescription(const String &desc);

	  /*!
	   * Returns the width of the image.
	   */
	  int width() const;

	  /*!
	   * Sets the width of the image.
	   */
	  void setWidth(int w);

	  /*!
	   * Returns the height of the image.
	   */
	  int height() const;

	  /*!
	   * Sets the height of the image.
	   */
	  void setHeight(int h);

	  /*!
	   * Returns the color depth (in bits-per-pixel) of the image.
	   */
	  int colorDepth() const;

	  /*!
	   * Sets the color depth (in bits-per-pixel) of the image.
	   */
	  void setColorDepth(int depth);

	  /*!
	   * Returns the number of colors used on the image..
	   */
	  int numColors() const;

	  /*!
	   * Sets the number of colors used on the image (for indexed images).
	   */
	  void setNumColors(int numColors);

	  /*!
	   * Returns the image data.
	   */
	  ByteVector data() const;

	  /*!
	   * Sets the image data.
	   */
	  void setData(const ByteVector &data);

	  /*!
	   * Returns the FLAC metadata block type.
	   */
	  int code() const;

	  /*!
	   * Render the content to the FLAC picture block format.
	   */
	  ByteVector render() const;

	  /*!
	   * Parse the picture data in the FLAC picture block format.
	   */
	  bool parse(const ByteVector &rawData);

	private:
	  Picture(const Picture &item);
	  Picture &operator=(const Picture &item);

	  class PicturePrivate;
	  PicturePrivate *d;
	};

	typedef List<Picture> PictureList;

  }

}

#endif

/*** End of inlined file: flacpicture.h ***/

namespace TagLib {

  class Tag;
  namespace ID3v2 { class FrameFactory; class Tag; }
  namespace ID3v1 { class Tag; }
  namespace Ogg { class XiphComment; }

  //! An implementation of FLAC metadata

  /*!
   * This is implementation of FLAC metadata for non-Ogg FLAC files.  At some
   * point when Ogg / FLAC is more common there will be a similar implementation
   * under the Ogg hiearchy.
   *
   * This supports ID3v1, ID3v2 and Xiph style comments as well as reading stream
   * properties from the file.
   */

  namespace FLAC {

	//! An implementation of TagLib::File with FLAC specific methods

	/*!
	 * This implements and provides an interface for FLAC files to the
	 * TagLib::Tag and TagLib::AudioProperties interfaces by way of implementing
	 * the abstract TagLib::File API as well as providing some additional
	 * information specific to FLAC files.
	 */

	class TAGLIB_EXPORT File : public TagLib::File
	{
	public:
	  /*!
	   * Contructs a FLAC file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   *
	   * \deprecated This constructor will be dropped in favor of the one below
	   * in a future version.
	   */
	  File(FileName file, bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Contructs a FLAC file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   *
	   * If this file contains and ID3v2 tag the frames will be created using
	   * \a frameFactory.
	   */
	  // BIC: merge with the above constructor
	  File(FileName file, ID3v2::FrameFactory *frameFactory,
		   bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Contructs a FLAC file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   *
	   * If this file contains and ID3v2 tag the frames will be created using
	   * \a frameFactory.
	   */
	  // BIC: merge with the above constructor
	  File(IOStream *stream, ID3v2::FrameFactory *frameFactory,
		   bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Destroys this instance of the File.
	   */
	  virtual ~File();

	  /*!
	   * Returns the Tag for this file.  This will be a union of XiphComment,
	   * ID3v1 and ID3v2 tags.
	   *
	   * \see ID3v2Tag()
	   * \see ID3v1Tag()
	   * \see XiphComment()
	   */
	  virtual TagLib::Tag *tag() const;

	  /*!
	   * Implements the unified property interface -- export function.
	   * If the file contains more than one tag (e.g. XiphComment and ID3v1),
	   * only the first one (in the order XiphComment, ID3v2, ID3v1) will be
	   * converted to the PropertyMap.
	   */
	  PropertyMap properties() const;

	  void removeUnsupportedProperties(const StringList &);

	  /*!
	   * Implements the unified property interface -- import function.
	   * As with the export, only one tag is taken into account. If the file
	   * has no tag at all, a XiphComment will be created.
	   */
	  PropertyMap setProperties(const PropertyMap &);

	  /*!
	   * Returns the FLAC::Properties for this file.  If no audio properties
	   * were read then this will return a null pointer.
	   */
	  virtual Properties *audioProperties() const;

	  /*!
	   * Save the file.  This will primarily save the XiphComment, but
	   * will also keep any old ID3-tags up to date. If the file
	   * has no XiphComment, one will be constructed from the ID3-tags.
	   *
	   * This returns true if the save was successful.
	   */
	  virtual bool save();

	  /*!
	   * Returns a pointer to the ID3v2 tag of the file.
	   *
	   * If \a create is false (the default) this will return a null pointer
	   * if there is no valid ID3v2 tag.  If \a create is true it will create
	   * an ID3v2 tag if one does not exist.
	   *
	   * \note The Tag <b>is still</b> owned by the FLAC::File and should not be
	   * deleted by the user.  It will be deleted when the file (object) is
	   * destroyed.
	   */
	  ID3v2::Tag *ID3v2Tag(bool create = false);

	  /*!
	   * Returns a pointer to the ID3v1 tag of the file.
	   *
	   * If \a create is false (the default) this will return a null pointer
	   * if there is no valid ID3v1 tag.  If \a create is true it will create
	   * an ID3v1 tag if one does not exist.
	   *
	   * \note The Tag <b>is still</b> owned by the FLAC::File and should not be
	   * deleted by the user.  It will be deleted when the file (object) is
	   * destroyed.
	   */
	  ID3v1::Tag *ID3v1Tag(bool create = false);

	  /*!
	   * Returns a pointer to the XiphComment for the file.
	   *
	   * If \a create is false (the default) this will return a null pointer
	   * if there is no valid XiphComment.  If \a create is true it will create
	   * a XiphComment if one does not exist.
	   *
	   * \note The Tag <b>is still</b> owned by the FLAC::File and should not be
	   * deleted by the user.  It will be deleted when the file (object) is
	   * destroyed.
	   */
	  Ogg::XiphComment *xiphComment(bool create = false);

	  /*!
	   * Set the ID3v2::FrameFactory to something other than the default.  This
	   * can be used to specify the way that ID3v2 frames will be interpreted
	   * when
	   *
	   * \see ID3v2FrameFactory
	   */
	  void setID3v2FrameFactory(const ID3v2::FrameFactory *factory);

	  /*!
	   * Returns the block of data used by FLAC::Properties for parsing the
	   * stream properties.
	   *
	   * \deprecated This method will not be public in a future release.
	   */
	  ByteVector streamInfoData(); // BIC: remove

	  /*!
	   * Returns the length of the audio-stream, used by FLAC::Properties for
	   * calculating the bitrate.
	   *
	   * \deprecated This method will not be public in a future release.
	   */
	  long streamLength();  // BIC: remove

	  /*!
	   * Returns a list of pictures attached to the FLAC file.
	   */
	  List<Picture *> pictureList();

	  /*!
	   * Removes an attached picture. If \a del is true the picture's memory
	   * will be freed; if it is false, it must be deleted by the user.
	   */
	  void removePicture(Picture *picture, bool del = true);

	  /*!
	   * Remove all attached images.
	   */
	  void removePictures();

	  /*!
	   * Add a new picture to the file. The file takes ownership of the
	   * picture and will handle freeing its memory.
	   *
	   * \note The file will be saved only after calling save().
	   */
	  void addPicture(Picture *picture);

	private:
	  File(const File &);
	  File &operator=(const File &);

	  void read(bool readProperties, Properties::ReadStyle propertiesStyle);
	  void scan();
	  long findID3v2();
	  long findID3v1();
	  ByteVector xiphCommentData() const;
	  long findPaddingBreak(long nextPageOffset, long targetOffset, bool *isLast);

	  class FilePrivate;
	  FilePrivate *d;
	};
  }
}

#endif

/*** End of inlined file: flacfile.h ***/


/*** Start of inlined file: apefile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_APEFILE_H
#define TAGLIB_APEFILE_H


/*** Start of inlined file: apeproperties.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_APEPROPERTIES_H
#define TAGLIB_APEPROPERTIES_H

namespace TagLib {

  namespace APE {

	class File;

	//! An implementation of audio property reading for APE

	/*!
	 * This reads the data from an APE stream found in the AudioProperties
	 * API.
	 */

	class TAGLIB_EXPORT Properties : public AudioProperties
	{
	public:
	  /*!
	   * Create an instance of APE::Properties with the data read from the
	   * ByteVector \a data.
	   */
	  Properties(File *f, ReadStyle style = Average);

	  /*!
	   * Destroys this APE::Properties instance.
	   */
	  virtual ~Properties();

	  // Reimplementations.

	  virtual int length() const;
	  virtual int bitrate() const;
	  virtual int sampleRate() const;
	  virtual int channels() const;

	  /*!
	   * Returns number of bits per sample.
	   */
	  int bitsPerSample() const;
	  uint sampleFrames() const;

	  /*!
	   * Returns APE version.
	   */
	  int version() const;

	private:
	  Properties(const Properties &);
	  Properties &operator=(const Properties &);

	  void read();

	  long findDescriptor();
	  long findID3v2();

	  void analyzeCurrent();
	  void analyzeOld();

	  class PropertiesPrivate;
	  PropertiesPrivate *d;
	};
  }
}

#endif

/*** End of inlined file: apeproperties.h ***/

namespace TagLib {

  class Tag;

  namespace ID3v1 { class Tag; }
  namespace APE { class Tag; }

  //! An implementation of APE metadata

  /*!
   * This is implementation of APE metadata.
   *
   * This supports ID3v1 and APE (v1 and v2) style comments as well as reading stream
   * properties from the file.
   */

  namespace APE {

	//! An implementation of TagLib::File with APE specific methods

	/*!
	 * This implements and provides an interface APE WavPack files to the
	 * TagLib::Tag and TagLib::AudioProperties interfaces by way of implementing
	 * the abstract TagLib::File API as well as providing some additional
	 * information specific to APE files.
	 */

	class TAGLIB_EXPORT File : public TagLib::File
	{
	public:
	  /*!
	   * This set of flags is used for various operations and is suitable for
	   * being OR-ed together.
	   */
	  enum TagTypes {
		//! Empty set.  Matches no tag types.
		NoTags  = 0x0000,
		//! Matches ID3v1 tags.
		ID3v1   = 0x0001,
		//! Matches APE tags.
		APE     = 0x0002,
		//! Matches all tag types.
		AllTags = 0xffff
	  };

	  /*!
	   * Contructs an WavPack file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   */
	  File(FileName file, bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Contructs an WavPack file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   */
	  File(IOStream *stream, bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Destroys this instance of the File.
	   */
	  virtual ~File();

	  /*!
	   * Returns the Tag for this file.  This will be an APE tag, an ID3v1 tag
	   * or a combination of the two.
	   */
	  virtual TagLib::Tag *tag() const;

	  /*!
	   * Implements the unified property interface -- export function.
	   * If the file contains both an APE and an ID3v1 tag, only APE
	   * will be converted to the PropertyMap.
	   */
	  PropertyMap properties() const;

	  /*!
	   * Removes unsupported properties. Forwards to the actual Tag's
	   * removeUnsupportedProperties() function.
	   */
	  void removeUnsupportedProperties(const StringList &properties);

	  /*!
	   * Implements the unified property interface -- import function.
	   * As for the export, only one tag is taken into account. If the file
	   * has no tag at all, APE will be created.
	   */
	  PropertyMap setProperties(const PropertyMap &);
	  /*!
	   * Returns the APE::Properties for this file.  If no audio properties
	   * were read then this will return a null pointer.
	   */
	  virtual Properties *audioProperties() const;

	  /*!
	   * Saves the file.
	   *
	   * \note According to the official Monkey's Audio SDK, an APE file
	   * can only have either ID3V1 or APE tags, so a parameter is used here.
	   */
	  virtual bool save();

	  /*!
	   * Returns a pointer to the ID3v1 tag of the file.
	   *
	   * If \a create is false (the default) this will return a null pointer
	   * if there is no valid ID3v1 tag.  If \a create is true it will create
	   * an ID3v1 tag if one does not exist. If there is already an APE tag, the
	   * new ID3v1 tag will be placed after it.
	   *
	   * \note The Tag <b>is still</b> owned by the APE::File and should not be
	   * deleted by the user.  It will be deleted when the file (object) is
	   * destroyed.
	   */
	  ID3v1::Tag *ID3v1Tag(bool create = false);

	  /*!
	   * Returns a pointer to the APE tag of the file.
	   *
	   * If \a create is false (the default) this will return a null pointer
	   * if there is no valid APE tag.  If \a create is true it will create
	   * a APE tag if one does not exist.
	   *
	   * \note The Tag <b>is still</b> owned by the APE::File and should not be
	   * deleted by the user.  It will be deleted when the file (object) is
	   * destroyed.
	   */
	  APE::Tag *APETag(bool create = false);

	  /*!
	   * This will remove the tags that match the OR-ed together TagTypes from the
	   * file.  By default it removes all tags.
	   *
	   * \note This will also invalidate pointers to the tags
	   * as their memory will be freed.
	   * \note In order to make the removal permanent save() still needs to be called
	   */
	  void strip(int tags = AllTags);

	private:
	  File(const File &);
	  File &operator=(const File &);

	  void read(bool readProperties, Properties::ReadStyle propertiesStyle);
	  void scan();
	  long findID3v1();
	  long findAPE();

	  class FilePrivate;
	  FilePrivate *d;
	};
  }
}

#endif

/*** End of inlined file: apefile.h ***/


/*** Start of inlined file: apetag.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_APETAG_H
#define TAGLIB_APETAG_H


/*** Start of inlined file: apeitem.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_APEITEM_H
#define TAGLIB_APEITEM_H

namespace TagLib {

  namespace APE {

	//! An implementation of APE-items

	/*!
	 * This class provides the features of items in the APEv2 standard.
	 */
	class TAGLIB_EXPORT Item
	{
	public:
	  /*!
	   * Enum of types an Item can have. The value of 3 is reserved.
	   */
	  enum ItemTypes {
		//! Item contains text information coded in UTF-8
		Text = 0,
		//! Item contains binary information
		Binary = 1,
		//! Item is a locator of external stored information
		Locator = 2
	  };
	  /*!
	   * Constructs an empty item.
	   */
	  Item();

	  /*!
	   * Constructs a text item with \a key and \a value.
	   */
	  // BIC: Remove this, StringList has a constructor from a single string
	  Item(const String &key, const String &value);

	  /*!
	   * Constructs a text item with \a key and \a values.
	   */
	  Item(const String &key, const StringList &values);

	  /*!
	   * Constructs an item with \a key and \a value.
	   * If \a binary is true a Binary item will be created, otherwise \a value will be interpreted as text
	   */
	  Item(const String &key, const ByteVector &value, bool binary);

	  /*!
	   * Construct an item as a copy of \a item.
	   */
	  Item(const Item &item);

	  /*!
	   * Destroys the item.
	   */
	  virtual ~Item();

	  /*!
	   * Copies the contents of \a item into this item.
	   */
	  Item &operator=(const Item &item);

	  /*!
	   * Returns the key.
	   */
	  String key() const;

	  /*!
	   * Returns the binary value.
	   * If the item type is not \a Binary, the returned contents are undefined
	   */
	  ByteVector binaryData() const;

	 /*!
	  * Set the binary value to \a value
	  * The item's type will also be set to \a Binary
	  */
	  void setBinaryData(const ByteVector &value);

#ifndef DO_NOT_DOCUMENT
	  /* Remove in next binary incompatible release */
	  ByteVector value() const;
#endif

	  /*!
	   * Sets the key for the item to \a key.
	   */
	  void setKey(const String &key);

	  /*!
	   * Sets the text value of the item to \a value and clears any previous contents.
	   *
	   * \see toString()
	   */
	  void setValue(const String &value);

	  /*!
	   * Sets the text value of the item to the list of values in \a value and clears
	   * any previous contents.
	   *
	   * \see toStringList()
	   */
	  void setValues(const StringList &values);

	  /*!
	   * Appends \a value to create (or extend) the current list of text values.
	   *
	   * \see toString()
	   */
	  void appendValue(const String &value);

	  /*!
	   * Appends \a values to extend the current list of text values.
	   *
	   * \see toStringList()
	   */
	  void appendValues(const StringList &values);

	  /*!
	   * Returns the size of the full item.
	   */
	  int size() const;

	  /*!
	   * Returns the value as a single string. In case of multiple strings,
	   * the first is returned.
	   */
	  String toString() const;

#ifndef DO_NOT_DOCUMENT
	  /* Remove in next binary incompatible release */
	  StringList toStringList() const;
#endif

	  /*!
	   * Returns the list of text values.
	   */
	  StringList values() const;

	  /*!
	   * Render the item to a ByteVector.
	   */
	  ByteVector render() const;

	  /*!
	   * Parse the item from the ByteVector \a data.
	   */
	  void parse(const ByteVector& data);

	  /*!
	   * Set the item to read-only.
	   */
	  void setReadOnly(bool readOnly);

	  /*!
	   * Return true if the item is read-only.
	   */
	  bool isReadOnly() const;

	  /*!
	   * Sets the type of the item to \a type.
	   *
	   * \see ItemTypes
	   */
	  void setType(ItemTypes type);

	  /*!
	   * Returns the type of the item.
	   */
	  ItemTypes type() const;

	  /*!
	   * Returns if the item has any real content.
	   */
	  bool isEmpty() const;

	private:
	  class ItemPrivate;
	  ItemPrivate *d;
	};
  }

}

#endif

/*** End of inlined file: apeitem.h ***/

namespace TagLib {

  class File;

  //! An implementation of the APE tagging format

  namespace APE {

	class Footer;

	/*!
	 * A mapping between a list of item names, or keys, and the associated item.
	 *
	 * \see APE::Tag::itemListMap()
	 */
	typedef Map<const String, Item> ItemListMap;

	//! An APE tag implementation

	class TAGLIB_EXPORT Tag : public TagLib::Tag
	{
	public:
	  /*!
	   * Create an APE tag with default values.
	   */
	  Tag();

	  /*!
	   * Create an APE tag and parse the data in \a file with APE footer at
	   * \a tagOffset.
	   */
	  Tag(TagLib::File *file, long footerLocation);

	  /*!
	   * Destroys this Tag instance.
	   */
	  virtual ~Tag();

	  /*!
	   * Renders the in memory values to a ByteVector suitable for writing to
	   * the file.
	   */
	  ByteVector render() const;

	  /*!
	   * Returns the string "APETAGEX" suitable for usage in locating the tag in a
	   * file.
	   */
	  static ByteVector fileIdentifier();

	  // Reimplementations.

	  virtual String title() const;
	  virtual String artist() const;
	  virtual String album() const;
	  virtual String comment() const;
	  virtual String genre() const;
	  virtual uint year() const;
	  virtual uint track() const;

	  virtual void setTitle(const String &s);
	  virtual void setArtist(const String &s);
	  virtual void setAlbum(const String &s);
	  virtual void setComment(const String &s);
	  virtual void setGenre(const String &s);
	  virtual void setYear(uint i);
	  virtual void setTrack(uint i);

	  /*!
	   * Implements the unified tag dictionary interface -- export function.
	   * APE tags are perfectly compatible with the dictionary interface because they
	   * support both arbitrary tag names and multiple values. Currently only
	   * APE items of type *Text* are handled by the dictionary interface; all *Binary*
	   * and *Locator* items will be put into the unsupportedData list and can be
	   * deleted on request using removeUnsupportedProperties(). The same happens
	   * to Text items if their key is invalid for PropertyMap (which should actually
	   * never happen).
	   *
	   * The only conversion done by this export function is to rename the APE tags
	   * TRACK to TRACKNUMBER, YEAR to DATE, and ALBUM ARTIST to ALBUMARTIST, respectively,
	   * in order to be compliant with the names used in other formats.
	   */
	  PropertyMap properties() const;

	  void removeUnsupportedProperties(const StringList &properties);

	  /*!
	   * Implements the unified tag dictionary interface -- import function. The same
	   * comments as for the export function apply.
	   */
	  PropertyMap setProperties(const PropertyMap &);

	  /*!
	   * Returns a pointer to the tag's footer.
	   */
	  Footer *footer() const;

	  /*!
	   * Returns a reference to the item list map.  This is an ItemListMap of
	   * all of the items in the tag.
	   *
	   * This is the most powerfull structure for accessing the items of the tag.
	   *
	   * APE tags are case-insensitive, all keys in this map have been converted
	   * to upper case.
	   *
	   * \warning You should not modify this data structure directly, instead
	   * use setItem() and removeItem().
	   */
	  const ItemListMap &itemListMap() const;

	  /*!
	   * Removes the \a key item from the tag
	   */
	  void removeItem(const String &key);

	  /*!
	   * Adds to the text item specified by \a key the data \a value.  If \a replace
	   * is true, then all of the other values on the same key will be removed
	   * first.  If a binary item exists for \a key it will be removed first.
	   */
	  void addValue(const String &key, const String &value, bool replace = true);

	 /*!
	  * Set the binary data for the key specified by \a item to \a value
	  * This will convert the item to type \a Binary if it isn't already and
	  * all of the other values on the same key will be removed.
	  */
	  void setData(const String &key, const ByteVector &value);

	  /*!
	   * Sets the \a key item to the value of \a item. If an item with the \a key is already
	   * present, it will be replaced.
	   */
	  void setItem(const String &key, const Item &item);

	  /*!
	   * Returns true if the tag does not contain any data.
	   */
	  bool isEmpty() const;

	protected:

	  /*!
	   * Reads from the file specified in the constructor.
	   */
	  void read();

	  /*!
	   * Parses the body of the tag in \a data.
	   */
	  void parse(const ByteVector &data);

	private:
	  Tag(const Tag &);
	  Tag &operator=(const Tag &);

	  class TagPrivate;
	  TagPrivate *d;
	};
  }
}

#endif

/*** End of inlined file: apetag.h ***/


/*** Start of inlined file: apefooter.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_APEFOOTER_H
#define TAGLIB_APEFOOTER_H

namespace TagLib {

  namespace APE {

	//! An implementation of APE footers

	/*!
	 * This class implements APE footers (and headers). It attempts to follow, both
	 * semantically and programatically, the structure specified in
	 * the APE v2.0 standard.  The API is based on the properties of APE footer and
	 * headers specified there.
	 */

	class TAGLIB_EXPORT Footer
	{
	public:
	  /*!
	   * Constructs an empty APE footer.
	   */
	  Footer();

	  /*!
	   * Constructs an APE footer based on \a data.  parse() is called
	   * immediately.
	   */
	  Footer(const ByteVector &data);

	  /*!
	   * Destroys the footer.
	   */
	  virtual ~Footer();

	  /*!
	   * Returns the version number.  (Note: This is the 1000 or 2000.)
	   */
	  uint version() const;

	  /*!
	   * Returns true if a header is present in the tag.
	   */
	  bool headerPresent() const;

	  /*!
	   * Returns true if a footer is present in the tag.
	   */
	  bool footerPresent() const;

	  /*!
	   * Returns true this is actually the header.
	   */
	  bool isHeader() const;

	  /*!
	   * Sets whether the header should be rendered or not
	   */
	  void setHeaderPresent(bool b) const;

	  /*!
	   * Returns the number of items in the tag.
	   */
	  uint itemCount() const;

	  /*!
	   * Set the item count to \a s.
	   * \see itemCount()
	   */
	  void setItemCount(uint s);

	  /*!
	   * Returns the tag size in bytes.  This is the size of the frame content and footer.
	   * The size of the \e entire tag will be this plus the header size, if present.
	   *
	   * \see completeTagSize()
	   */
	  uint tagSize() const;

	  /*!
	   * Returns the tag size, including if present, the header
	   * size.
	   *
	   * \see tagSize()
	   */
	  uint completeTagSize() const;

	  /*!
	   * Set the tag size to \a s.
	   * \see tagSize()
	   */
	  void setTagSize(uint s);

	  /*!
	   * Returns the size of the footer.  Presently this is always 32 bytes.
	   */
	  static uint size();

	  /*!
	   * Returns the string used to identify an APE tag inside of a file.
	   * Presently this is always "APETAGEX".
	   */
	  static ByteVector fileIdentifier();

	  /*!
	   * Sets the data that will be used as the footer.  32 bytes,
	   * starting from \a data will be used.
	   */
	  void setData(const ByteVector &data);

	  /*!
	   * Renders the footer back to binary format.
	   */
	  ByteVector renderFooter() const;

	  /*!
	   * Renders the header corresponding to the footer. If headerPresent is
	   * set to false, it returns an empty ByteVector.
	   */
	  ByteVector renderHeader() const;

	protected:
	  /*!
	   * Called by setData() to parse the footer data.  It makes this information
	   * available through the public API.
	   */
	  void parse(const ByteVector &data);

	  /*!
	   * Called by renderFooter and renderHeader
	   */
	  ByteVector render(bool isHeader) const;

	private:
	  Footer(const Footer &);
	  Footer &operator=(const Footer &);

	  class FooterPrivate;
	  FooterPrivate *d;
	};

  }
}

#endif

/*** End of inlined file: apefooter.h ***/


/*** Start of inlined file: mpcfile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_MPCFILE_H
#define TAGLIB_MPCFILE_H


/*** Start of inlined file: mpcproperties.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_MPCPROPERTIES_H
#define TAGLIB_MPCPROPERTIES_H

namespace TagLib {

  namespace MPC {

	class File;

	static const uint HeaderSize = 8*7;

	//! An implementation of audio property reading for MPC

	/*!
	 * This reads the data from an MPC stream found in the AudioProperties
	 * API.
	 */

	class TAGLIB_EXPORT Properties : public AudioProperties
	{
	public:
	  /*!
	   * Create an instance of MPC::Properties with the data read from the
	   * ByteVector \a data.
	   */
	  Properties(const ByteVector &data, long streamLength, ReadStyle style = Average);

	  /*!
	   * Destroys this MPC::Properties instance.
	   */
	  virtual ~Properties();

	  // Reimplementations.

	  virtual int length() const;
	  virtual int bitrate() const;
	  virtual int sampleRate() const;
	  virtual int channels() const;

	  /*!
	   * Returns the version of the bitstream (SV4-SV7)
	   */
	  int mpcVersion() const;
	  uint totalFrames() const;
	  uint sampleFrames() const;

	private:
	  Properties(const Properties &);
	  Properties &operator=(const Properties &);

	  void read();

	  class PropertiesPrivate;
	  PropertiesPrivate *d;
	};
  }
}

#endif

/*** End of inlined file: mpcproperties.h ***/

namespace TagLib {

  class Tag;

  namespace ID3v1 { class Tag; }
  namespace APE { class Tag; }

  //! An implementation of MPC metadata

  /*!
   * This is implementation of MPC metadata.
   *
   * This supports ID3v1 and APE (v1 and v2) style comments as well as reading stream
   * properties from the file. ID3v2 tags are invalid in MPC-files, but will be skipped
   * and ignored.
   */

  namespace MPC {

	//! An implementation of TagLib::File with MPC specific methods

	/*!
	 * This implements and provides an interface for MPC files to the
	 * TagLib::Tag and TagLib::AudioProperties interfaces by way of implementing
	 * the abstract TagLib::File API as well as providing some additional
	 * information specific to MPC files.
	 * The only invalid tag combination supported is an ID3v1 tag after an APE tag.
	 */

	class TAGLIB_EXPORT File : public TagLib::File
	{
	public:
	  /*!
	   * This set of flags is used for various operations and is suitable for
	   * being OR-ed together.
	   */
	  enum TagTypes {
		//! Empty set.  Matches no tag types.
		NoTags  = 0x0000,
		//! Matches ID3v1 tags.
		ID3v1   = 0x0001,
		//! Matches ID3v2 tags.
		ID3v2   = 0x0002,
		//! Matches APE tags.
		APE     = 0x0004,
		//! Matches all tag types.
		AllTags = 0xffff
	  };

	  /*!
	   * Contructs an MPC file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   */
	  File(FileName file, bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Contructs an MPC file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   */
	  File(IOStream *stream, bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Destroys this instance of the File.
	   */
	  virtual ~File();

	  /*!
	   * Returns the Tag for this file.  This will be an APE tag, an ID3v1 tag
	   * or a combination of the two.
	   */
	  virtual TagLib::Tag *tag() const;

	  /*!
	   * Implements the unified property interface -- export function.
	   * If the file contains both an APE and an ID3v1 tag, only the APE
	   * tag  will be converted to the PropertyMap.
	   */
	  PropertyMap properties() const;

	  void removeUnsupportedProperties(const StringList &properties);

	  /*!
	   * Implements the unified property interface -- import function.
	   * As with the export, only one tag is taken into account. If the file
	   * has no tag at all, an APE tag will be created.
	   */
	  PropertyMap setProperties(const PropertyMap &);

	  /*!
	   * Returns the MPC::Properties for this file.  If no audio properties
	   * were read then this will return a null pointer.
	   */
	  virtual Properties *audioProperties() const;

	  /*!
	   * Saves the file.
	   */
	  virtual bool save();

	  /*!
	   * Returns a pointer to the ID3v1 tag of the file.
	   *
	   * If \a create is false (the default) this will return a null pointer
	   * if there is no valid ID3v1 tag.  If \a create is true it will create
	   * an ID3v1 tag if one does not exist. If there is already an APE tag, the
	   * new ID3v1 tag will be placed after it.
	   *
	   * \note The Tag <b>is still</b> owned by the APE::File and should not be
	   * deleted by the user.  It will be deleted when the file (object) is
	   * destroyed.
	   */
	  ID3v1::Tag *ID3v1Tag(bool create = false);

	  /*!
	   * Returns a pointer to the APE tag of the file.
	   *
	   * If \a create is false (the default) this will return a null pointer
	   * if there is no valid APE tag.  If \a create is true it will create
	   * a APE tag if one does not exist. If there is already an ID3v1 tag, thes
	   * new APE tag will be placed before it.
	   *
	   * \note The Tag <b>is still</b> owned by the APE::File and should not be
	   * deleted by the user.  It will be deleted when the file (object) is
	   * destroyed.
	   */
	  APE::Tag *APETag(bool create = false);

	  /*!
	   * This will remove the tags that match the OR-ed together TagTypes from the
	   * file.  By default it removes all tags.
	   *
	   * \warning This will also invalidate pointers to the tags
	   * as their memory will be freed.
	   *
	   * \note In order to make the removal permanent save() still needs to be called.
	   */
	  void strip(int tags = AllTags);

	  /*!
	   * \deprecated
	   * \see strip
	   */
	  void remove(int tags = AllTags);

	private:
	  File(const File &);
	  File &operator=(const File &);

	  void read(bool readProperties, Properties::ReadStyle propertiesStyle);
	  void scan();
	  long findAPE();
	  long findID3v1();
	  long findID3v2();

	  class FilePrivate;
	  FilePrivate *d;
	};
  }
}

#endif

/*** End of inlined file: mpcfile.h ***/


/*** Start of inlined file: wavpackfile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_WVFILE_H
#define TAGLIB_WVFILE_H


/*** Start of inlined file: wavpackproperties.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_WVPROPERTIES_H
#define TAGLIB_WVPROPERTIES_H

namespace TagLib {

  namespace WavPack {

	class File;

	static const uint HeaderSize = 32;

	//! An implementation of audio property reading for WavPack

	/*!
	 * This reads the data from an WavPack stream found in the AudioProperties
	 * API.
	 */

	class TAGLIB_EXPORT Properties : public AudioProperties
	{
	public:
	  /*!
	   * Create an instance of WavPack::Properties with the data read from the
	   * ByteVector \a data.
	   *
	   * \deprecated This constructor will be dropped in favor of the one below
	   * in a future version.
	   */
	  Properties(const ByteVector &data, long streamLength, ReadStyle style = Average);

	  /*!
	   * Create an instance of WavPack::Properties.
	   */
	  // BIC: merge with the above constructor
	  Properties(File *file, long streamLength, ReadStyle style = Average);

	  /*!
	   * Destroys this WavPack::Properties instance.
	   */
	  virtual ~Properties();

	  // Reimplementations.

	  virtual int length() const;
	  virtual int bitrate() const;
	  virtual int sampleRate() const;
	  virtual int channels() const;

	  /*!
	   * Returns number of bits per sample.
	   */
	  int bitsPerSample() const;
	  uint sampleFrames() const;

	  /*!
	   * Returns WavPack version.
	   */
	  int version() const;

	private:
	  Properties(const Properties &);
	  Properties &operator=(const Properties &);

	  void read();
	  unsigned int seekFinalIndex();

	  class PropertiesPrivate;
	  PropertiesPrivate *d;
	};
  }
}

#endif

/*** End of inlined file: wavpackproperties.h ***/

namespace TagLib {

  class Tag;

  namespace ID3v1 { class Tag; }
  namespace APE { class Tag; }

  //! An implementation of WavPack metadata

  /*!
   * This is implementation of WavPack metadata.
   *
   * This supports ID3v1 and APE (v1 and v2) style comments as well as reading stream
   * properties from the file.
   */

  namespace WavPack {

	//! An implementation of TagLib::File with WavPack specific methods

	/*!
	 * This implements and provides an interface for WavPack files to the
	 * TagLib::Tag and TagLib::AudioProperties interfaces by way of implementing
	 * the abstract TagLib::File API as well as providing some additional
	 * information specific to WavPack files.
	 */

	class TAGLIB_EXPORT File : public TagLib::File
	{
	public:
	  /*!
	   * This set of flags is used for various operations and is suitable for
	   * being OR-ed together.
	   */
	  enum TagTypes {
		//! Empty set.  Matches no tag types.
		NoTags  = 0x0000,
		//! Matches ID3v1 tags.
		ID3v1   = 0x0001,
		//! Matches APE tags.
		APE     = 0x0002,
		//! Matches all tag types.
		AllTags = 0xffff
	  };

	  /*!
	   * Contructs an WavPack file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   */
	  File(FileName file, bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Contructs an WavPack file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   */
	  File(IOStream *stream, bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Destroys this instance of the File.
	   */
	  virtual ~File();

	  /*!
	   * Returns the Tag for this file.  This will be an APE tag, an ID3v1 tag
	   * or a combination of the two.
	   */
	  virtual TagLib::Tag *tag() const;

	  /*!
	   * Implements the unified property interface -- export function.
	   * If the file contains both an APE and an ID3v1 tag, only APE
	   * will be converted to the PropertyMap.
	   */
	  PropertyMap properties() const;

	  /*!
	   * Implements the unified property interface -- import function.
	   * As for the export, only one tag is taken into account. If the file
	   * has no tag at all, APE will be created.
	   */
	  PropertyMap setProperties(const PropertyMap&);

	  /*!
	   * Returns the MPC::Properties for this file.  If no audio properties
	   * were read then this will return a null pointer.
	   */
	  virtual Properties *audioProperties() const;

	  /*!
	   * Saves the file.
	   */
	  virtual bool save();

	  /*!
	   * Returns a pointer to the ID3v1 tag of the file.
	   *
	   * If \a create is false (the default) this will return a null pointer
	   * if there is no valid ID3v1 tag.  If \a create is true it will create
	   * an ID3v1 tag if one does not exist. If there is already an APE tag, the
	   * new ID3v1 tag will be placed after it.
	   *
	   * \note The Tag <b>is still</b> owned by the APE::File and should not be
	   * deleted by the user.  It will be deleted when the file (object) is
	   * destroyed.
	   */
	  ID3v1::Tag *ID3v1Tag(bool create = false);

	  /*!
	   * Returns a pointer to the APE tag of the file.
	   *
	   * If \a create is false (the default) this will return a null pointer
	   * if there is no valid APE tag.  If \a create is true it will create
	   * a APE tag if one does not exist.
	   *
	   * \note The Tag <b>is still</b> owned by the APE::File and should not be
	   * deleted by the user.  It will be deleted when the file (object) is
	   * destroyed.
	   */
	  APE::Tag *APETag(bool create = false);

	  /*!
	   * This will remove the tags that match the OR-ed together TagTypes from the
	   * file.  By default it removes all tags.
	   *
	   * \note This will also invalidate pointers to the tags
	   * as their memory will be freed.
	   * \note In order to make the removal permanent save() still needs to be called
	   */
	  void strip(int tags = AllTags);

	private:
	  File(const File &);
	  File &operator=(const File &);

	  void read(bool readProperties, Properties::ReadStyle propertiesStyle);
	  void scan();
	  long findID3v1();
	  long findAPE();

	  class FilePrivate;
	  FilePrivate *d;
	};
  }
}

#endif

/*** End of inlined file: wavpackfile.h ***/


/*** Start of inlined file: trueaudiofile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_TRUEAUDIOFILE_H
#define TAGLIB_TRUEAUDIOFILE_H


/*** Start of inlined file: trueaudioproperties.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_TRUEAUDIOPROPERTIES_H
#define TAGLIB_TRUEAUDIOPROPERTIES_H

namespace TagLib {

  namespace TrueAudio {

	class File;

	static const uint HeaderSize = 18;

	//! An implementation of audio property reading for TrueAudio

	/*!
	 * This reads the data from an TrueAudio stream found in the AudioProperties
	 * API.
	 */

	class TAGLIB_EXPORT Properties : public AudioProperties
	{
	public:
	  /*!
	   * Create an instance of TrueAudio::Properties with the data read from the
	   * ByteVector \a data.
	   */
	  Properties(const ByteVector &data, long streamLength, ReadStyle style = Average);

	  /*!
	   * Destroys this TrueAudio::Properties instance.
	   */
	  virtual ~Properties();

	  // Reimplementations.

	  virtual int length() const;
	  virtual int bitrate() const;
	  virtual int sampleRate() const;
	  virtual int channels() const;

	  /*!
	   * Returns number of bits per sample.
	   */
	  int bitsPerSample() const;

	  /*!
	   * Returns the total number of sample frames
	   */
	  uint sampleFrames() const;

	  /*!
	   * Returns the major version number.
	   */
	  int ttaVersion() const;

	private:
	  Properties(const Properties &);
	  Properties &operator=(const Properties &);

	  void read();

	  class PropertiesPrivate;
	  PropertiesPrivate *d;
	};
  }
}

#endif

/*** End of inlined file: trueaudioproperties.h ***/

namespace TagLib {

  class Tag;

  namespace ID3v2 { class Tag; class FrameFactory; }
  namespace ID3v1 { class Tag; }

  //! An implementation of TrueAudio metadata

  /*!
   * This is implementation of TrueAudio metadata.
   *
   * This supports ID3v1 and ID3v2 tags as well as reading stream
   * properties from the file.
   */

  namespace TrueAudio {

	//! An implementation of TagLib::File with TrueAudio specific methods

	/*!
	 * This implements and provides an interface for TrueAudio files to the
	 * TagLib::Tag and TagLib::AudioProperties interfaces by way of implementing
	 * the abstract TagLib::File API as well as providing some additional
	 * information specific to TrueAudio files.
	 */

	class TAGLIB_EXPORT File : public TagLib::File
	{
	public:
	  /*!
	   * This set of flags is used for various operations and is suitable for
	   * being OR-ed together.
	   */
	  enum TagTypes {
		//! Empty set.  Matches no tag types.
		NoTags  = 0x0000,
		//! Matches ID3v1 tags.
		ID3v1   = 0x0001,
		//! Matches ID3v2 tags.
		ID3v2   = 0x0002,
		//! Matches all tag types.
		AllTags = 0xffff
	  };

	  /*!
	   * Contructs an TrueAudio file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   */
	  File(FileName file, bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Contructs an TrueAudio file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored. The frames will be created using
	   * \a frameFactory.
	   */
	  File(FileName file, ID3v2::FrameFactory *frameFactory,
		   bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Contructs an TrueAudio file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   */
	  File(IOStream *stream, bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Contructs an TrueAudio file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored. The frames will be created using
	   * \a frameFactory.
	   */
	  File(IOStream *stream, ID3v2::FrameFactory *frameFactory,
		   bool readProperties = true,
		   Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Destroys this instance of the File.
	   */
	  virtual ~File();

	  /*!
	   * Returns the Tag for this file.
	   */
	  virtual TagLib::Tag *tag() const;

	  /*!
	   * Implements the unified property interface -- export function.
	   * If the file contains both ID3v1 and v2 tags, only ID3v2 will be
	   * converted to the PropertyMap.
	   */
	  PropertyMap properties() const;

	  /*!
	   * Implements the unified property interface -- import function.
	   * As with the export, only one tag is taken into account. If the file
	   * has no tag at all, ID3v2 will be created.
	   */
	  PropertyMap setProperties(const PropertyMap &);

	  /*!
	   * Returns the TrueAudio::Properties for this file.  If no audio properties
	   * were read then this will return a null pointer.
	   */
	  virtual Properties *audioProperties() const;

	  /*!
	   * Set the ID3v2::FrameFactory to something other than the default.
	   *
	   * \see ID3v2FrameFactory
	   */
	  void setID3v2FrameFactory(const ID3v2::FrameFactory *factory);

	  /*!
	   * Saves the file.
	   */
	  virtual bool save();

	  /*!
	   * Returns a pointer to the ID3v2 tag of the file.
	   *
	   * If \a create is false (the default) this will return a null pointer
	   * if there is no valid ID3v2 tag.  If \a create is true it will create
	   * an ID3v1 tag if one does not exist. If there is already an APE tag, the
	   * new ID3v1 tag will be placed after it.
	   *
	   * \note The Tag <b>is still</b> owned by the TrueAudio::File and should not be
	   * deleted by the user.  It will be deleted when the file (object) is
	   * destroyed.
	   */
	  ID3v1::Tag *ID3v1Tag(bool create = false);

	  /*!
	   * Returns a pointer to the ID3v1 tag of the file.
	   *
	   * If \a create is false (the default) this will return a null pointer
	   * if there is no valid ID3v1 tag.  If \a create is true it will create
	   * an ID3v1 tag if one does not exist. If there is already an APE tag, the
	   * new ID3v1 tag will be placed after it.
	   *
	   * \note The Tag <b>is still</b> owned by the TrueAudio::File and should not be
	   * deleted by the user.  It will be deleted when the file (object) is
	   * destroyed.
	   */
	  ID3v2::Tag *ID3v2Tag(bool create = false);

	  /*!
	   * This will remove the tags that match the OR-ed together TagTypes from the
	   * file.  By default it removes all tags.
	   *
	   * \note This will also invalidate pointers to the tags
	   * as their memory will be freed.
	   * \note In order to make the removal permanent save() still needs to be called
	   */
	  void strip(int tags = AllTags);

	private:
	  File(const File &);
	  File &operator=(const File &);

	  void read(bool readProperties, Properties::ReadStyle propertiesStyle);
	  void scan();
	  long findID3v1();
	  long findID3v2();

	  class FilePrivate;
	  FilePrivate *d;
	};
  }
}

#endif

/*** End of inlined file: trueaudiofile.h ***/


/*** Start of inlined file: rifffile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_RIFFFILE_H
#define TAGLIB_RIFFFILE_H

namespace TagLib {

  //! An implementation of TagLib::File with RIFF specific methods

  namespace RIFF {

	//! An RIFF file class with some useful methods specific to RIFF

	/*!
	 * This implements the generic TagLib::File API and additionally provides
	 * access to properties that are distinct to RIFF files, notably access
	 * to the different ID3 tags.
	 */

	class TAGLIB_EXPORT File : public TagLib::File
	{
	public:
	  /*!
	   * Destroys this instance of the File.
	   */
	  virtual ~File();

	protected:

	  enum Endianness { BigEndian, LittleEndian };

	  File(FileName file, Endianness endianness);
	  File(IOStream *stream, Endianness endianness);

	  /*!
	   * \return The size of the main RIFF chunk.
	   */
	  uint riffSize() const;

	  /*!
	   * \return The number of chunks in the file.
	   */
	  uint chunkCount() const;

	  /*!
	   * \return The offset within the file for the selected chunk number.
	   */
	  uint chunkOffset(uint i) const;

	  /*!
	   * \return The size of the chunk data.
	   */
	  uint chunkDataSize(uint i) const;

	  /*!
	   * \return The size of the padding after the chunk (can be either 0 or 1).
	   */
	  uint chunkPadding(uint i) const;

	  /*!
	   * \return The name of the specified chunk, for instance, "COMM" or "ID3 "
	   */
	  ByteVector chunkName(uint i) const;

	  /*!
	   * Reads the chunk data from the file and returns it.
	   *
	   * \note This \e will move the read pointer for the file.
	   */
	  ByteVector chunkData(uint i);

	  /*!
	   * Sets the data for the chunk \a name to \a data.  If a chunk with the
	   * given name already exists it will be overwritten, otherwise it will be
	   * created after the existing chunks.
	   *
	   * \warning This will update the file immediately.
	   */
	  void setChunkData(const ByteVector &name, const ByteVector &data);

	private:
	  File(const File &);
	  File &operator=(const File &);

	  void read();
	  void writeChunk(const ByteVector &name, const ByteVector &data,
					  ulong offset, ulong replace = 0,
					  uint leadingPadding = 0);

	  class FilePrivate;
	  FilePrivate *d;
	};
  }
}

#endif

/*** End of inlined file: rifffile.h ***/


/*** Start of inlined file: aifffile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_AIFFFILE_H
#define TAGLIB_AIFFFILE_H


/*** Start of inlined file: aiffproperties.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_AIFFPROPERTIES_H
#define TAGLIB_AIFFPROPERTIES_H

namespace TagLib {

  namespace RIFF {

	namespace AIFF {

	  class File;

	  //! An implementation of audio property reading for AIFF

	  /*!
	   * This reads the data from an AIFF stream found in the AudioProperties
	   * API.
	   */

	  class TAGLIB_EXPORT Properties : public AudioProperties
	  {
	  public:
		/*!
		 * Create an instance of AIFF::Properties with the data read from the
		 * ByteVector \a data.
		 */
		Properties(const ByteVector &data, ReadStyle style);

		/*!
		 * Destroys this AIFF::Properties instance.
		 */
		virtual ~Properties();

		// Reimplementations.

		virtual int length() const;
		virtual int bitrate() const;
		virtual int sampleRate() const;
		virtual int channels() const;

		int sampleWidth() const;
		uint sampleFrames() const;

	  private:
		Properties(const Properties &);
		Properties &operator=(const Properties &);

		void read(const ByteVector &data);

		class PropertiesPrivate;
		PropertiesPrivate *d;
	  };
	}
  }
}

#endif

/*** End of inlined file: aiffproperties.h ***/

namespace TagLib {

  namespace RIFF {

	//! An implementation of AIFF metadata

	/*!
	 * This is implementation of AIFF metadata.
	 *
	 * This supports an ID3v2 tag as well as reading stream from the ID3 RIFF
	 * chunk as well as properties from the file.
	 */

	namespace AIFF {

	  //! An implementation of TagLib::File with AIFF specific methods

	  /*!
	   * This implements and provides an interface for AIFF files to the
	   * TagLib::Tag and TagLib::AudioProperties interfaces by way of implementing
	   * the abstract TagLib::File API as well as providing some additional
	   * information specific to AIFF files.
	   */

	  class TAGLIB_EXPORT File : public TagLib::RIFF::File
	  {
	  public:
		/*!
		 * Contructs an AIFF file from \a file.  If \a readProperties is true the
		 * file's audio properties will also be read using \a propertiesStyle.  If
		 * false, \a propertiesStyle is ignored.
		 */
		File(FileName file, bool readProperties = true,
			 Properties::ReadStyle propertiesStyle = Properties::Average);

		/*!
		 * Contructs an AIFF file from \a file.  If \a readProperties is true the
		 * file's audio properties will also be read using \a propertiesStyle.  If
		 * false, \a propertiesStyle is ignored.
		 */
		File(IOStream *stream, bool readProperties = true,
			 Properties::ReadStyle propertiesStyle = Properties::Average);

		/*!
		 * Destroys this instance of the File.
		 */
		virtual ~File();

		/*!
		 * Returns the Tag for this file.
		 */
		virtual ID3v2::Tag *tag() const;

		/*!
		 * Implements the unified property interface -- export function.
		 * This method forwards to ID3v2::Tag::properties().
		 */
		PropertyMap properties() const;

		/*!
		 * Implements the unified property interface -- import function.
		 * This method forwards to ID3v2::Tag::setProperties().
		 */
		PropertyMap setProperties(const PropertyMap &);

		/*!
		 * Returns the AIFF::Properties for this file.  If no audio properties
		 * were read then this will return a null pointer.
		 */
		virtual Properties *audioProperties() const;

		/*!
		 * Saves the file.
		 */
		virtual bool save();

	  private:
		File(const File &);
		File &operator=(const File &);

		void read(bool readProperties, Properties::ReadStyle propertiesStyle);

		class FilePrivate;
		FilePrivate *d;
	  };
	}
  }
}

#endif

/*** End of inlined file: aifffile.h ***/


/*** Start of inlined file: wavfile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_WAVFILE_H
#define TAGLIB_WAVFILE_H


/*** Start of inlined file: wavproperties.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_WAVPROPERTIES_H
#define TAGLIB_WAVPROPERTIES_H

namespace TagLib {

  class ByteVector;

  namespace RIFF {

	namespace WAV {

	  class File;

	  //! An implementation of audio property reading for WAV

	  /*!
	   * This reads the data from an WAV stream found in the AudioProperties
	   * API.
	   */

	  class TAGLIB_EXPORT Properties : public AudioProperties
	  {
	  public:
		/*!
		 * Create an instance of WAV::Properties with the data read from the
		 * ByteVector \a data.
		 */
		Properties(const ByteVector &data, ReadStyle style);

		/*!
		 * Create an instance of WAV::Properties with the data read from the
		 * ByteVector \a data and the length calculated using \a streamLength.
		 */
		Properties(const ByteVector &data, uint streamLength, ReadStyle style);

		/*!
		 * Destroys this WAV::Properties instance.
		 */
		virtual ~Properties();

		// Reimplementations.

		virtual int length() const;
		virtual int bitrate() const;
		virtual int sampleRate() const;
		virtual int channels() const;

		int sampleWidth() const;
		uint sampleFrames() const;

	  private:
		Properties(const Properties &);
		Properties &operator=(const Properties &);

		void read(const ByteVector &data);

		class PropertiesPrivate;
		PropertiesPrivate *d;
	  };
	}
  }
}

#endif

/*** End of inlined file: wavproperties.h ***/

namespace TagLib {

  namespace RIFF {

	//! An implementation of WAV metadata

	/*!
	 * This is implementation of WAV metadata.
	 *
	 * This supports an ID3v2 tag as well as reading stream from the ID3 RIFF
	 * chunk as well as properties from the file.
	 */

	namespace WAV {

	  //! An implementation of TagLib::File with WAV specific methods

	  /*!
	   * This implements and provides an interface for WAV files to the
	   * TagLib::Tag and TagLib::AudioProperties interfaces by way of implementing
	   * the abstract TagLib::File API as well as providing some additional
	   * information specific to WAV files.
	   */

	  class TAGLIB_EXPORT File : public TagLib::RIFF::File
	  {
	  public:
		/*!
		 * Contructs an WAV file from \a file.  If \a readProperties is true the
		 * file's audio properties will also be read using \a propertiesStyle.  If
		 * false, \a propertiesStyle is ignored.
		 */
		File(FileName file, bool readProperties = true,
			 Properties::ReadStyle propertiesStyle = Properties::Average);

		/*!
		 * Contructs an WAV file from \a file.  If \a readProperties is true the
		 * file's audio properties will also be read using \a propertiesStyle.  If
		 * false, \a propertiesStyle is ignored.
		 */
		File(IOStream *stream, bool readProperties = true,
			 Properties::ReadStyle propertiesStyle = Properties::Average);

		/*!
		 * Destroys this instance of the File.
		 */
		virtual ~File();

		/*!
		 * Returns the Tag for this file.
		 */
		virtual ID3v2::Tag *tag() const;

		/*!
		 * Implements the unified property interface -- export function.
		 * This method forwards to ID3v2::Tag::properties().
		 */
		PropertyMap properties() const;

		/*!
		 * Implements the unified property interface -- import function.
		 * This method forwards to ID3v2::Tag::setProperties().
		 */
		PropertyMap setProperties(const PropertyMap &);

		/*!
		 * Returns the WAV::Properties for this file.  If no audio properties
		 * were read then this will return a null pointer.
		 */
		virtual Properties *audioProperties() const;

		/*!
		 * Saves the file.
		 */
		virtual bool save();

	  private:
		File(const File &);
		File &operator=(const File &);

		void read(bool readProperties, Properties::ReadStyle propertiesStyle);

		class FilePrivate;
		FilePrivate *d;
	  };
	}
  }
}

#endif

/*** End of inlined file: wavfile.h ***/


/*** Start of inlined file: asffile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_ASFFILE_H
#define TAGLIB_ASFFILE_H


/*** Start of inlined file: asfproperties.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_ASFPROPERTIES_H
#define TAGLIB_ASFPROPERTIES_H

namespace TagLib {

  namespace ASF {

	//! An implementation of ASF audio properties
	class TAGLIB_EXPORT Properties : public AudioProperties
	{
	public:

	  /*!
	   * Create an instance of ASF::Properties.
	   */
	  Properties();

	  /*!
	   * Destroys this ASF::Properties instance.
	   */
	  virtual ~Properties();

	  // Reimplementations.
	  virtual int length() const;
	  virtual int bitrate() const;
	  virtual int sampleRate() const;
	  virtual int channels() const;
	  bool isEncrypted() const;

#ifndef DO_NOT_DOCUMENT
	  void setLength(int value);
	  void setBitrate(int value);
	  void setSampleRate(int value);
	  void setChannels(int value);
	  void setEncrypted(bool value);
#endif

	private:
	  class PropertiesPrivate;
	  PropertiesPrivate *d;
	};

  }

}

#endif

/*** End of inlined file: asfproperties.h ***/


/*** Start of inlined file: asftag.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_ASFTAG_H
#define TAGLIB_ASFTAG_H


/*** Start of inlined file: asfattribute.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_ASFATTRIBUTE_H
#define TAGLIB_ASFATTRIBUTE_H


/*** Start of inlined file: asfpicture.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef ASFPICTURE_H
#define ASFPICTURE_H

namespace TagLib
{
  namespace ASF
  {

	//! An ASF attached picture interface implementation

	/*!
	 * This is an implementation of ASF attached pictures interface.  Pictures may be
	 * included in attributes, one per WM/Picture attribute (but there may be multiple WM/Picture
	 * attribute in a single tag).  These pictures are usually in either JPEG or
	 * PNG format.
	 * \see Attribute::toPicture()
	 * \see Attribute::Attribute(const Picture& picture)
	 */
	class TAGLIB_EXPORT Picture {
	public:

	  /*!
	   * This describes the function or content of the picture.
	   */
	  enum Type {
		//! A type not enumerated below
		Other              = 0x00,
		//! 32x32 PNG image that should be used as the file icon
		FileIcon           = 0x01,
		//! File icon of a different size or format
		OtherFileIcon      = 0x02,
		//! Front cover image of the album
		FrontCover         = 0x03,
		//! Back cover image of the album
		BackCover          = 0x04,
		//! Inside leaflet page of the album
		LeafletPage        = 0x05,
		//! Image from the album itself
		Media              = 0x06,
		//! Picture of the lead artist or soloist
		LeadArtist         = 0x07,
		//! Picture of the artist or performer
		Artist             = 0x08,
		//! Picture of the conductor
		Conductor          = 0x09,
		//! Picture of the band or orchestra
		Band               = 0x0A,
		//! Picture of the composer
		Composer           = 0x0B,
		//! Picture of the lyricist or text writer
		Lyricist           = 0x0C,
		//! Picture of the recording location or studio
		RecordingLocation  = 0x0D,
		//! Picture of the artists during recording
		DuringRecording    = 0x0E,
		//! Picture of the artists during performance
		DuringPerformance  = 0x0F,
		//! Picture from a movie or video related to the track
		MovieScreenCapture = 0x10,
		//! Picture of a large, coloured fish
		ColouredFish       = 0x11,
		//! Illustration related to the track
		Illustration       = 0x12,
		//! Logo of the band or performer
		BandLogo           = 0x13,
		//! Logo of the publisher (record company)
		PublisherLogo      = 0x14
	  };

	  /*!
	   * Constructs an empty picture.
	   */
	  Picture();

	  /*!
	   * Construct an picture as a copy of \a other.
	   */
	  Picture(const Picture& other);

	  /*!
	   * Destroys the picture.
	   */
	  virtual ~Picture();

	  /*!
	   * Copies the contents of \a other into this picture.
	   */
	  Picture& operator=(const Picture& other);

	  /*!
	   * Returns true if Picture stores valid picture
	   */
	  bool isValid() const;

	  /*!
	   * Returns the mime type of the image. This should in most cases be
	   * "image/png" or "image/jpeg".
	   * \see setMimeType(const String &)
	   * \see picture()
	   * \see setPicture(const ByteArray&)
	   */
	  String mimeType() const;

	  /*!
	   * Sets the mime type of the image.  This should in most cases be
	   * "image/png" or "image/jpeg".
	   * \see setMimeType(const String &)
	   * \see picture()
	   * \see setPicture(const ByteArray&)
	   */
	  void setMimeType(const String &value);

	  /*!
	   * Returns the type of the image.
	   *
	   * \see Type
	   * \see setType()
	   */
	  Type type() const;

	  /*!
	   * Sets the type for the image.
	   *
	   * \see Type
	   * \see type()
	   */
	  void setType(const ASF::Picture::Type& t);

	  /*!
	   * Returns a text description of the image.
	   *
	   * \see setDescription()
	   */
	  String description() const;

	  /*!
	   * Sets a textual description of the image to \a desc.
	   *
	   * \see description()
	   */
	  void setDescription(const String &desc);

	  /*!
	   * Returns the image data as a ByteVector.
	   *
	   * \note ByteVector has a data() method that returns a const char * which
	   * should make it easy to export this data to external programs.
	   *
	   * \see setPicture()
	   * \see mimeType()
	   */
	  ByteVector picture() const;

	  /*!
	   * Sets the image data to \a p.  \a p should be of the type specified in
	   * this frame's mime-type specification.
	   *
	   * \see picture()
	   * \see mimeType()
	   * \see setMimeType()
	   */
	  void setPicture(const ByteVector &p);

	  /*!
	   * Returns picture as binary raw data \a value
	   */
	  ByteVector render() const;

	  /*!
	   * Returns picture as binary raw data \a value
	   */
	  int dataSize() const;

#ifndef DO_NOT_DOCUMENT
	  /* THIS IS PRIVATE, DON'T TOUCH IT! */
	  void parse(const ByteVector& );
	  static Picture fromInvalid();
	  friend class Attribute;
#endif
	  private:
		class PicturePrivate;
		PicturePrivate *d;
	  };
  }
}

#endif // ASFPICTURE_H

/*** End of inlined file: asfpicture.h ***/

namespace TagLib
{

  namespace ASF
  {

	class File;
	class Picture;

	class TAGLIB_EXPORT Attribute
	{
	public:

	  /*!
	   * Enum of types an Attribute can have.
	   */
	  enum AttributeTypes {
		UnicodeType = 0,
		BytesType   = 1,
		BoolType    = 2,
		DWordType   = 3,
		QWordType   = 4,
		WordType    = 5,
		GuidType    = 6
	  };

	  /*!
	   * Constructs an empty attribute.
	   */
	  Attribute();

	  /*!
	   * Constructs an attribute with \a key and a UnicodeType \a value.
	   */
	  Attribute(const String &value);

	  /*!
	   * Constructs an attribute with \a key and a BytesType \a value.
	   */
	  Attribute(const ByteVector &value);

	  /*!
	   * Constructs an attribute with \a key and a Picture \a value.
	   *
	   * This attribute is compatible with the ID3 frame, APIC. The ID3 specification for the APIC frame stipulates that,
	   * while there may be any number of APIC frames associated with a file,
	   * only one may be of type 1 and only one may be of type 2.
	   *
	   * The specification also states that the description of the picture can be no longer than 64 characters, but can be empty.
	   * WM/Picture attributes added with TagLib::ASF are not automatically validated to conform to ID3 specifications.
	   * You must add code in your application to perform validations if you want to maintain complete compatibility with ID3.
	   */
	  Attribute(const Picture &value);

	  /*!
	   * Constructs an attribute with \a key and a DWordType \a value.
	   */
	  Attribute(unsigned int value);

	  /*!
	   * Constructs an attribute with \a key and a QWordType \a value.
	   */
	  Attribute(unsigned long long value);

	  /*!
	   * Constructs an attribute with \a key and a WordType \a value.
	   */
	  Attribute(unsigned short value);

	  /*!
	   * Constructs an attribute with \a key and a BoolType \a value.
	   */
	  Attribute(bool value);

	  /*!
	   * Construct an attribute as a copy of \a other.
	   */
	  Attribute(const Attribute &item);

	  /*!
	   * Copies the contents of \a other into this item.
	   */
	  ASF::Attribute &operator=(const Attribute &other);

	  /*!
	   * Destroys the attribute.
	   */
	  virtual ~Attribute();

	  /*!
	   * Returns type of the value.
	   */
	  AttributeTypes type() const;

	  /*!
	   * Returns the BoolType \a value.
	   */
	  unsigned short toBool() const;

	  /*!
	   * Returns the WordType \a value.
	   */
	  unsigned short toUShort() const;

	  /*!
	   * Returns the DWordType \a value.
	   */
	  unsigned int toUInt() const;

	  /*!
	   * Returns the QWordType \a value.
	   */
	  unsigned long long toULongLong() const;

	  /*!
	   * Returns the UnicodeType \a value.
	   */
	  String toString() const;

	  /*!
	   * Returns the BytesType \a value.
	   */
	  ByteVector toByteVector() const;

	  /*!
	   * Returns the Picture \a value.
	   */
	  Picture toPicture() const;

	  /*!
	   * Returns the language number, or 0 is no stream number was set.
	   */
	  int language() const;

	  /*!
	   * Sets the language number.
	   */
	  void setLanguage(int value);

	  /*!
	   * Returns the stream number, or 0 is no stream number was set.
	   */
	  int stream() const;

	  /*!
	   * Sets the stream number.
	   */
	  void setStream(int value);

#ifndef DO_NOT_DOCUMENT
	  /* THIS IS PRIVATE, DON'T TOUCH IT! */
	  String parse(ASF::File &file, int kind = 0);
#endif

	  //! Returns the size of the stored data
	  int dataSize() const;

	private:
	  friend class File;

	  ByteVector render(const String &name, int kind = 0) const;

	  class AttributePrivate;
	  AttributePrivate *d;
	};
  }

}

#endif

/*** End of inlined file: asfattribute.h ***/

namespace TagLib {

  namespace ASF {

	typedef List<Attribute> AttributeList;
	typedef Map<String, AttributeList> AttributeListMap;

	class TAGLIB_EXPORT Tag : public TagLib::Tag {

	  friend class File;

	public:

	  Tag();

	  virtual ~Tag();

	  /*!
	   * Returns the track name.
	   */
	  virtual String title() const;

	  /*!
	   * Returns the artist name.
	   */
	  virtual String artist() const;

	  /*!
	   * Returns the album name; if no album name is present in the tag
	   * String::null will be returned.
	   */
	  virtual String album() const;

	  /*!
	   * Returns the track comment.
	   */
	  virtual String comment() const;

	  /*!
	   * Returns the genre name; if no genre is present in the tag String::null
	   * will be returned.
	   */
	  virtual String genre() const;

	  /*!
	   * Returns the rating.
	   */
	  virtual String rating() const;

	  /*!
	   * Returns the genre name; if no genre is present in the tag String::null
	   * will be returned.
	   */
	  virtual String copyright() const;

	  /*!
	   * Returns the year; if there is no year set, this will return 0.
	   */
	  virtual uint year() const;

	  /*!
	   * Returns the track number; if there is no track number set, this will
	   * return 0.
	   */
	  virtual uint track() const;

	  /*!
	   * Sets the title to \a s.
	   */
	  virtual void setTitle(const String &s);

	  /*!
	   * Sets the artist to \a s.
	   */
	  virtual void setArtist(const String &s);

	  /*!
	   * Sets the album to \a s.  If \a s is String::null then this value will be
	   * cleared.
	   */
	  virtual void setAlbum(const String &s);

	  /*!
	   * Sets the comment to \a s.
	   */
	  virtual void setComment(const String &s);

	  /*!
	   * Sets the rating to \a s.
	   */
	  virtual void setRating(const String &s);

	  /*!
	   * Sets the copyright to \a s.
	   */
	  virtual void setCopyright(const String &s);

	  /*!
	   * Sets the genre to \a s.
	   */
	  virtual void setGenre(const String &s);

	  /*!
	   * Sets the year to \a i.  If \a s is 0 then this value will be cleared.
	   */
	  virtual void setYear(uint i);

	  /*!
	   * Sets the track to \a i.  If \a s is 0 then this value will be cleared.
	   */
	  virtual void setTrack(uint i);

	  /*!
	   * Returns true if the tag does not contain any data.  This should be
	   * reimplemented in subclasses that provide more than the basic tagging
	   * abilities in this class.
	   */
	  virtual bool isEmpty() const;

	  /*!
	   * Returns a reference to the item list map.  This is an AttributeListMap of
	   * all of the items in the tag.
	   *
	   * This is the most powerfull structure for accessing the items of the tag.
	   */
	  AttributeListMap &attributeListMap();

	  /*!
	   * Removes the \a key attribute from the tag
	   */
	  void removeItem(const String &name);

	  /*!
	   * Sets the \a key attribute to the value of \a attribute. If an attribute
	   * with the \a key is already present, it will be replaced.
	   */
	  void setAttribute(const String &name, const Attribute &attribute);

	  /*!
	   * Sets the \a key attribute to the value of \a attribute. If an attribute
	   * with the \a key is already present, it will be added to the list.
	   */
	  void addAttribute(const String &name, const Attribute &attribute);

	private:

	  class TagPrivate;
	  TagPrivate *d;
	};
  }
}
#endif

/*** End of inlined file: asftag.h ***/

namespace TagLib {

  //! An implementation of ASF (WMA) metadata
  namespace ASF {

	/*!
	 * This implements and provides an interface for ASF files to the
	 * TagLib::Tag and TagLib::AudioProperties interfaces by way of implementing
	 * the abstract TagLib::File API as well as providing some additional
	 * information specific to ASF files.
	 */
	class TAGLIB_EXPORT File : public TagLib::File
	{
	public:

	  /*!
	   * Contructs an ASF file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   *
	   * \note In the current implementation, both \a readProperties and
	   * \a propertiesStyle are ignored.
	   */
	  File(FileName file, bool readProperties = true, Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Contructs an ASF file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   *
	   * \note In the current implementation, both \a readProperties and
	   * \a propertiesStyle are ignored.
	   */
	  File(IOStream *stream, bool readProperties = true, Properties::ReadStyle propertiesStyle = Properties::Average);

	  /*!
	   * Destroys this instance of the File.
	   */
	  virtual ~File();

	  /*!
	   * Returns a pointer to the ASF tag of the file.
	   *
	   * ASF::Tag implements the tag interface, so this serves as the
	   * reimplementation of TagLib::File::tag().
	   *
	   * \note The Tag <b>is still</b> owned by the ASF::File and should not be
	   * deleted by the user.  It will be deleted when the file (object) is
	   * destroyed.
	   */
	  virtual Tag *tag() const;

	  /*!
	   * Returns the ASF audio properties for this file.
	   */
	  virtual Properties *audioProperties() const;

	  /*!
	   * Save the file.
	   *
	   * This returns true if the save was successful.
	   */
	  virtual bool save();

	private:

	  int readBYTE(bool *ok = 0);
	  unsigned short readWORD(bool *ok = 0);
	  unsigned int readDWORD(bool *ok = 0);
	  long long readQWORD(bool *ok = 0);
	  static ByteVector renderString(const String &str, bool includeLength = false);
	  String readString(int len);
	  void read(bool readProperties, Properties::ReadStyle propertiesStyle);

	  friend class Attribute;
	  friend class Picture;

	  class BaseObject;
	  class UnknownObject;
	  class FilePropertiesObject;
	  class StreamPropertiesObject;
	  class ContentDescriptionObject;
	  class ExtendedContentDescriptionObject;
	  class HeaderExtensionObject;
	  class MetadataObject;
	  class MetadataLibraryObject;

	  class FilePrivate;
	  FilePrivate *d;
	};

  }

}

#endif

/*** End of inlined file: asffile.h ***/


/*** Start of inlined file: mp4file.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_MP4FILE_H
#define TAGLIB_MP4FILE_H


/*** Start of inlined file: mp4properties.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_MP4PROPERTIES_H
#define TAGLIB_MP4PROPERTIES_H

namespace TagLib {

  namespace MP4 {

	class Atoms;
	class File;

	//! An implementation of MP4 audio properties
	class TAGLIB_EXPORT Properties : public AudioProperties
	{
	public:
	  Properties(File *file, Atoms *atoms, ReadStyle style = Average);
	  virtual ~Properties();

	  virtual int length() const;
	  virtual int bitrate() const;
	  virtual int sampleRate() const;
	  virtual int channels() const;
	  virtual int bitsPerSample() const;
	  bool isEncrypted() const;

	private:
	  class PropertiesPrivate;
	  PropertiesPrivate *d;
	};

  }

}

#endif

/*** End of inlined file: mp4properties.h ***/


/*** Start of inlined file: mp4tag.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_MP4TAG_H
#define TAGLIB_MP4TAG_H


/*** Start of inlined file: mp4atom.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

// This file is not part of the public API!

#ifndef DO_NOT_DOCUMENT

#ifndef TAGLIB_MP4ATOM_H
#define TAGLIB_MP4ATOM_H

namespace TagLib {

  namespace MP4 {

	class Atom;
	typedef TagLib::List<Atom *> AtomList;

	enum AtomDataType
	{
	  TypeImplicit  = 0,  // for use with tags for which no type needs to be indicated because only one type is allowed
	  TypeUTF8      = 1,  // without any count or null terminator
	  TypeUTF16     = 2,  // also known as UTF-16BE
	  TypeSJIS      = 3,  // deprecated unless it is needed for special Japanese characters
	  TypeHTML      = 6,  // the HTML file header specifies which HTML version
	  TypeXML       = 7,  // the XML header must identify the DTD or schemas
	  TypeUUID      = 8,  // also known as GUID; stored as 16 bytes in binary (valid as an ID)
	  TypeISRC      = 9,  // stored as UTF-8 text (valid as an ID)
	  TypeMI3P      = 10, // stored as UTF-8 text (valid as an ID)
	  TypeGIF       = 12, // (deprecated) a GIF image
	  TypeJPEG      = 13, // a JPEG image
	  TypePNG       = 14, // a PNG image
	  TypeURL       = 15, // absolute, in UTF-8 characters
	  TypeDuration  = 16, // in milliseconds, 32-bit integer
	  TypeDateTime  = 17, // in UTC, counting seconds since midnight, January 1, 1904; 32 or 64-bits
	  TypeGenred    = 18, // a list of enumerated values
	  TypeInteger   = 21, // a signed big-endian integer with length one of { 1,2,3,4,8 } bytes
	  TypeRIAAPA    = 24, // RIAA parental advisory; { -1=no, 1=yes, 0=unspecified }, 8-bit ingteger
	  TypeUPC       = 25, // Universal Product Code, in text UTF-8 format (valid as an ID)
	  TypeBMP       = 27, // Windows bitmap image
	  TypeUndefined = 255 // undefined
	};

	struct AtomData {
	  AtomData(AtomDataType type, ByteVector data) : type(type), locale(0), data(data) {}
	  AtomDataType type;
	  int locale;
	  ByteVector data;
	};

	typedef TagLib::List<AtomData> AtomDataList;

	class Atom
	{
	public:
		Atom(File *file);
		~Atom();
		Atom *find(const char *name1, const char *name2 = 0, const char *name3 = 0, const char *name4 = 0);
		bool path(AtomList &path, const char *name1, const char *name2 = 0, const char *name3 = 0);
		AtomList findall(const char *name, bool recursive = false);
		long offset;
		long length;
		TagLib::ByteVector name;
		AtomList children;
	private:
		static const int numContainers = 11;
		static const char *containers[11];
	};

	//! Root-level atoms
	class Atoms
	{
	public:
		Atoms(File *file);
		~Atoms();
		Atom *find(const char *name1, const char *name2 = 0, const char *name3 = 0, const char *name4 = 0);
		AtomList path(const char *name1, const char *name2 = 0, const char *name3 = 0, const char *name4 = 0);
		AtomList atoms;
	};

  }

}

#endif

#endif

/*** End of inlined file: mp4atom.h ***/


/*** Start of inlined file: mp4item.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_MP4ITEM_H
#define TAGLIB_MP4ITEM_H


/*** Start of inlined file: mp4coverart.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_MP4COVERART_H
#define TAGLIB_MP4COVERART_H


/*** Start of inlined file: mp4atom.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

// This file is not part of the public API!

#ifndef DO_NOT_DOCUMENT

#ifndef TAGLIB_MP4ATOM_H
#define TAGLIB_MP4ATOM_H

namespace TagLib {

  namespace MP4 {

	class Atom;
	typedef TagLib::List<Atom *> AtomList;

	enum AtomDataType
	{
	  TypeImplicit  = 0,  // for use with tags for which no type needs to be indicated because only one type is allowed
	  TypeUTF8      = 1,  // without any count or null terminator
	  TypeUTF16     = 2,  // also known as UTF-16BE
	  TypeSJIS      = 3,  // deprecated unless it is needed for special Japanese characters
	  TypeHTML      = 6,  // the HTML file header specifies which HTML version
	  TypeXML       = 7,  // the XML header must identify the DTD or schemas
	  TypeUUID      = 8,  // also known as GUID; stored as 16 bytes in binary (valid as an ID)
	  TypeISRC      = 9,  // stored as UTF-8 text (valid as an ID)
	  TypeMI3P      = 10, // stored as UTF-8 text (valid as an ID)
	  TypeGIF       = 12, // (deprecated) a GIF image
	  TypeJPEG      = 13, // a JPEG image
	  TypePNG       = 14, // a PNG image
	  TypeURL       = 15, // absolute, in UTF-8 characters
	  TypeDuration  = 16, // in milliseconds, 32-bit integer
	  TypeDateTime  = 17, // in UTC, counting seconds since midnight, January 1, 1904; 32 or 64-bits
	  TypeGenred    = 18, // a list of enumerated values
	  TypeInteger   = 21, // a signed big-endian integer with length one of { 1,2,3,4,8 } bytes
	  TypeRIAAPA    = 24, // RIAA parental advisory; { -1=no, 1=yes, 0=unspecified }, 8-bit ingteger
	  TypeUPC       = 25, // Universal Product Code, in text UTF-8 format (valid as an ID)
	  TypeBMP       = 27, // Windows bitmap image
	  TypeUndefined = 255 // undefined
	};

	struct AtomData {
	  AtomData(AtomDataType type, ByteVector data) : type(type), locale(0), data(data) {}
	  AtomDataType type;
	  int locale;
	  ByteVector data;
	};

	typedef TagLib::List<AtomData> AtomDataList;

	class Atom
	{
	public:
		Atom(File *file);
		~Atom();
		Atom *find(const char *name1, const char *name2 = 0, const char *name3 = 0, const char *name4 = 0);
		bool path(AtomList &path, const char *name1, const char *name2 = 0, const char *name3 = 0);
		AtomList findall(const char *name, bool recursive = false);
		long offset;
		long length;
		TagLib::ByteVector name;
		AtomList children;
	private:
		static const int numContainers = 11;
		static const char *containers[11];
	};

	//! Root-level atoms
	class Atoms
	{
	public:
		Atoms(File *file);
		~Atoms();
		Atom *find(const char *name1, const char *name2 = 0, const char *name3 = 0, const char *name4 = 0);
		AtomList path(const char *name1, const char *name2 = 0, const char *name3 = 0, const char *name4 = 0);
		AtomList atoms;
	};

  }

}

#endif

#endif

/*** End of inlined file: mp4atom.h ***/

namespace TagLib {

  namespace MP4 {

	class TAGLIB_EXPORT CoverArt
	{
	public:
	  /*!
	   * This describes the image type.
	   */
	  enum Format {
		JPEG = TypeJPEG,
		PNG  = TypePNG,
		BMP  = TypeBMP,
		GIF  = TypeGIF
	  };

	  CoverArt(Format format, const ByteVector &data);
	  ~CoverArt();

	  CoverArt(const CoverArt &item);
	  CoverArt &operator=(const CoverArt &item);

	  //! Format of the image
	  Format format() const;

	  //! The image data
	  ByteVector data() const;

	private:
	  class CoverArtPrivate;
	  CoverArtPrivate *d;
	};

	typedef List<CoverArt> CoverArtList;

  }

}

#endif

/*** End of inlined file: mp4coverart.h ***/

namespace TagLib {

  namespace MP4 {

	class TAGLIB_EXPORT Item
	{
	public:
	  struct IntPair {
		int first, second;
	  };

	  Item();
	  Item(const Item &item);
	  Item &operator=(const Item &item);
	  ~Item();

	  Item(int value);
	  Item(uchar value);
	  Item(uint value);
	  Item(long long value);
	  Item(bool value);
	  Item(int first, int second);
	  Item(const StringList &value);
	  Item(const ByteVectorList &value);
	  Item(const CoverArtList &value);

	  void setAtomDataType(AtomDataType type);
	  AtomDataType atomDataType() const;

	  int toInt() const;
	  uchar toByte() const;
	  uint toUInt() const;
	  long long toLongLong() const;
	  bool toBool() const;
	  IntPair toIntPair() const;
	  StringList toStringList() const;
	  ByteVectorList toByteVectorList() const;
	  CoverArtList toCoverArtList() const;

	  bool isValid() const;

	private:
	  class ItemPrivate;
	  ItemPrivate *d;
	};

  }

}

#endif

/*** End of inlined file: mp4item.h ***/

namespace TagLib {

  namespace MP4 {

	typedef TagLib::Map<String, Item> ItemListMap;

	class TAGLIB_EXPORT Tag: public TagLib::Tag
	{
	public:
		Tag();
		Tag(TagLib::File *file, Atoms *atoms);
		~Tag();
		bool save();

		String title() const;
		String artist() const;
		String album() const;
		String comment() const;
		String genre() const;
		uint year() const;
		uint track() const;

		void setTitle(const String &value);
		void setArtist(const String &value);
		void setAlbum(const String &value);
		void setComment(const String &value);
		void setGenre(const String &value);
		void setYear(uint value);
		void setTrack(uint value);

		ItemListMap &itemListMap();

	private:
		AtomDataList parseData2(Atom *atom, TagLib::File *file, int expectedFlags = -1, bool freeForm = false);
		TagLib::ByteVectorList parseData(Atom *atom, TagLib::File *file, int expectedFlags = -1, bool freeForm = false);
		void parseText(Atom *atom, TagLib::File *file, int expectedFlags = 1);
		void parseFreeForm(Atom *atom, TagLib::File *file);
		void parseInt(Atom *atom, TagLib::File *file);
		void parseByte(Atom *atom, TagLib::File *file);
		void parseUInt(Atom *atom, TagLib::File *file);
		void parseLongLong(Atom *atom, TagLib::File *file);
		void parseGnre(Atom *atom, TagLib::File *file);
		void parseIntPair(Atom *atom, TagLib::File *file);
		void parseBool(Atom *atom, TagLib::File *file);
		void parseCovr(Atom *atom, TagLib::File *file);

		TagLib::ByteVector padIlst(const ByteVector &data, int length = -1);
		TagLib::ByteVector renderAtom(const ByteVector &name, const TagLib::ByteVector &data);
		TagLib::ByteVector renderData(const ByteVector &name, int flags, const TagLib::ByteVectorList &data);
		TagLib::ByteVector renderText(const ByteVector &name, Item &item, int flags = TypeUTF8);
		TagLib::ByteVector renderFreeForm(const String &name, Item &item);
		TagLib::ByteVector renderBool(const ByteVector &name, Item &item);
		TagLib::ByteVector renderInt(const ByteVector &name, Item &item);
		TagLib::ByteVector renderByte(const ByteVector &name, Item &item);
		TagLib::ByteVector renderUInt(const ByteVector &name, Item &item);
		TagLib::ByteVector renderLongLong(const ByteVector &name, Item &item);
		TagLib::ByteVector renderIntPair(const ByteVector &name, Item &item);
		TagLib::ByteVector renderIntPairNoTrailing(const ByteVector &name, Item &item);
		TagLib::ByteVector renderCovr(const ByteVector &name, Item &item);

		void updateParents(AtomList &path, long delta, int ignore = 0);
		void updateOffsets(long delta, long offset);

		void saveNew(TagLib::ByteVector &data);
		void saveExisting(TagLib::ByteVector &data, AtomList &path);

		class TagPrivate;
		TagPrivate *d;
	};

  }

}

#endif

/*** End of inlined file: mp4tag.h ***/

namespace TagLib {

  //! An implementation of MP4 (AAC, ALAC, ...) metadata
  namespace MP4 {

	class Atoms;

	/*!
	 * This implements and provides an interface for MP4 files to the
	 * TagLib::Tag and TagLib::AudioProperties interfaces by way of implementing
	 * the abstract TagLib::File API as well as providing some additional
	 * information specific to MP4 files.
	 */
	class TAGLIB_EXPORT File : public TagLib::File
	{
	public:
	  /*!
	   * Contructs a MP4 file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   *
	   * \note In the current implementation, both \a readProperties and
	   * \a propertiesStyle are ignored.
	   */
	  File(FileName file, bool readProperties = true, Properties::ReadStyle audioPropertiesStyle = Properties::Average);

	  /*!
	   * Contructs a MP4 file from \a file.  If \a readProperties is true the
	   * file's audio properties will also be read using \a propertiesStyle.  If
	   * false, \a propertiesStyle is ignored.
	   *
	   * \note In the current implementation, both \a readProperties and
	   * \a propertiesStyle are ignored.
	   */
	  File(IOStream *stream, bool readProperties = true, Properties::ReadStyle audioPropertiesStyle = Properties::Average);

	  /*!
	   * Destroys this instance of the File.
	   */
	  virtual ~File();

	  /*!
	   * Returns a pointer to the MP4 tag of the file.
	   *
	   * MP4::Tag implements the tag interface, so this serves as the
	   * reimplementation of TagLib::File::tag().
	   *
	   * \note The Tag <b>is still</b> owned by the MP4::File and should not be
	   * deleted by the user.  It will be deleted when the file (object) is
	   * destroyed.
	   */
	  Tag *tag() const;

	  /*!
	   * Returns the MP4 audio properties for this file.
	   */
	  Properties *audioProperties() const;

	  /*!
	   * Save the file.
	   *
	   * This returns true if the save was successful.
	   */
	  bool save();

	private:

	  void read(bool readProperties, Properties::ReadStyle audioPropertiesStyle);
	  bool checkValid(const MP4::AtomList &list);

	  class FilePrivate;
	  FilePrivate *d;
	};

  }

}

#endif

/*** End of inlined file: mp4file.h ***/


/*** Start of inlined file: mp4atom.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

// This file is not part of the public API!

#ifndef DO_NOT_DOCUMENT

#ifndef TAGLIB_MP4ATOM_H
#define TAGLIB_MP4ATOM_H

namespace TagLib {

  namespace MP4 {

	class Atom;
	typedef TagLib::List<Atom *> AtomList;

	enum AtomDataType
	{
	  TypeImplicit  = 0,  // for use with tags for which no type needs to be indicated because only one type is allowed
	  TypeUTF8      = 1,  // without any count or null terminator
	  TypeUTF16     = 2,  // also known as UTF-16BE
	  TypeSJIS      = 3,  // deprecated unless it is needed for special Japanese characters
	  TypeHTML      = 6,  // the HTML file header specifies which HTML version
	  TypeXML       = 7,  // the XML header must identify the DTD or schemas
	  TypeUUID      = 8,  // also known as GUID; stored as 16 bytes in binary (valid as an ID)
	  TypeISRC      = 9,  // stored as UTF-8 text (valid as an ID)
	  TypeMI3P      = 10, // stored as UTF-8 text (valid as an ID)
	  TypeGIF       = 12, // (deprecated) a GIF image
	  TypeJPEG      = 13, // a JPEG image
	  TypePNG       = 14, // a PNG image
	  TypeURL       = 15, // absolute, in UTF-8 characters
	  TypeDuration  = 16, // in milliseconds, 32-bit integer
	  TypeDateTime  = 17, // in UTC, counting seconds since midnight, January 1, 1904; 32 or 64-bits
	  TypeGenred    = 18, // a list of enumerated values
	  TypeInteger   = 21, // a signed big-endian integer with length one of { 1,2,3,4,8 } bytes
	  TypeRIAAPA    = 24, // RIAA parental advisory; { -1=no, 1=yes, 0=unspecified }, 8-bit ingteger
	  TypeUPC       = 25, // Universal Product Code, in text UTF-8 format (valid as an ID)
	  TypeBMP       = 27, // Windows bitmap image
	  TypeUndefined = 255 // undefined
	};

	struct AtomData {
	  AtomData(AtomDataType type, ByteVector data) : type(type), locale(0), data(data) {}
	  AtomDataType type;
	  int locale;
	  ByteVector data;
	};

	typedef TagLib::List<AtomData> AtomDataList;

	class Atom
	{
	public:
		Atom(File *file);
		~Atom();
		Atom *find(const char *name1, const char *name2 = 0, const char *name3 = 0, const char *name4 = 0);
		bool path(AtomList &path, const char *name1, const char *name2 = 0, const char *name3 = 0);
		AtomList findall(const char *name, bool recursive = false);
		long offset;
		long length;
		TagLib::ByteVector name;
		AtomList children;
	private:
		static const int numContainers = 11;
		static const char *containers[11];
	};

	//! Root-level atoms
	class Atoms
	{
	public:
		Atoms(File *file);
		~Atoms();
		Atom *find(const char *name1, const char *name2 = 0, const char *name3 = 0, const char *name4 = 0);
		AtomList path(const char *name1, const char *name2 = 0, const char *name3 = 0, const char *name4 = 0);
		AtomList atoms;
	};

  }

}

#endif

#endif

/*** End of inlined file: mp4atom.h ***/


/*** Start of inlined file: modfilebase.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it  under the terms of the GNU Lesser General Public License version  *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,            *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#ifndef TAGLIB_MODFILEBASE_H
#define TAGLIB_MODFILEBASE_H

#include <algorithm>

namespace TagLib {

  namespace Mod {

	class TAGLIB_EXPORT FileBase : public TagLib::File
	{
	protected:
	  FileBase(FileName file);
	  FileBase(IOStream *stream);

	  void writeString(const String &s, ulong size, char padding = 0);
	  void writeByte(uchar byte);
	  void writeU16L(ushort number);
	  void writeU32L(ulong number);
	  void writeU16B(ushort number);
	  void writeU32B(ulong number);

	  bool readString(String &s, ulong size);
	  bool readByte(uchar &byte);
	  bool readU16L(ushort &number);
	  bool readU32L(ulong &number);
	  bool readU16B(ushort &number);
	  bool readU32B(ulong &number);
	};

  }

}

#endif

/*** End of inlined file: modfilebase.h ***/


/*** Start of inlined file: modfile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it  under the terms of the GNU Lesser General Public License version  *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,            *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#ifndef TAGLIB_MODFILE_H
#define TAGLIB_MODFILE_H


/*** Start of inlined file: modtag.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it  under the terms of the GNU Lesser General Public License version  *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,            *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#ifndef TAGLIB_MODTAG_H
#define TAGLIB_MODTAG_H

namespace TagLib {

  namespace Mod {

	/*!
	 * Tags for module files (Mod, S3M, IT, XM).
	 *
	 * Note that only the \a title is supported as such by most
	 * module file formats.  Except for XM files the \a trackerName
	 * is derived from the file format or the flavour of the file
	 * format.  For XM files it is stored in the file.
	 *
	 * The \a comment tag is not strictly supported by module files,
	 * but it is common practice to abuse instrument/sample/pattern
	 * names as multiline comments.  TagLib does so as well.
	 */
	class TAGLIB_EXPORT Tag : public TagLib::Tag
	{
	public:
	  Tag();
	  virtual ~Tag();

	  /*!
	   * Returns the track name; if no track name is present in the tag
	   * String::null will be returned.
	   */
	  String title() const;

	  /*!
	   * Not supported by module files.  Therefore always returns String::null.
	   */
	  String artist() const;

	  /*!
	   * Not supported by module files.  Therefore always returns String::null.
	   */
	  String album() const;

	  /*!
	   * Returns the track comment derived from the instrument/sample/pattern
	   * names; if no comment is present in the tag String::null will be
	   * returned.
	   */
	  String comment() const;

	  /*!
	   * Not supported by module files.  Therefore always returns String::null.
	   */
	  String genre() const;

	  /*!
	   * Not supported by module files.  Therefore always returns 0.
	   */
	  uint year() const;

	  /*!
	   * Not supported by module files.  Therefore always returns 0.
	   */
	  uint track() const;

	  /*!
	   * Returns the name of the tracker used to create/edit the module file.
	   * Only XM files store this tag to the file as such, for other formats
	   * (Mod, S3M, IT) this is derived from the file type or the flavour of
	   * the file type.  Therefore only XM files might have an empty
	   * (String::null) tracker name.
	   */
	  String trackerName() const;

	  /*!
	   * Sets the title to \a title.  If \a title is String::null then this
	   * value will be cleared.
	   *
	   * The length limits per file type are (1 characetr = 1 byte):
	   * Mod 20 characters, S3M 27 characters, IT 25 characters and XM 20
	   * characters.
	   */
	  void setTitle(const String &title);

	  /*!
	   * Not supported by module files and therefore ignored.
	   */
	  void setArtist(const String &artist);

	  /*!
	   * Not supported by module files and therefore ignored.
	   */
	  void setAlbum(const String &album);

	  /*!
	   * Sets the comment to \a comment.  If \a comment is String::null then
	   * this value will be cleared.
	   *
	   * Note that module file formats don't actually support a comment tag.
	   * Instead the names of instruments/patterns/samples are abused as
	   * a multiline comment. Because of this the number of lines in a
	   * module file is fixed to the number of instruments/patterns/samples.
	   *
	   * Also note that the instrument/pattern/sample name length is limited
	   * an thus the line length in comments are limited. Too big comments
	   * will be truncated.
	   *
	   * The line length limits per file type are (1 characetr = 1 byte):
	   * Mod 22 characters, S3M 27 characters, IT 25 characters and XM 22
	   * characters.
	   */
	  void setComment(const String &comment);

	  /*!
	   * Not supported by module files and therefore ignored.
	   */
	  void setGenre(const String &genre);

	  /*!
	   * Not supported by module files and therefore ignored.
	   */
	  void setYear(uint year);

	  /*!
	   * Not supported by module files and therefore ignored.
	   */
	  void setTrack(uint track);

	  /*!
	   * Sets the tracker name to \a trackerName.  If \a trackerName is
	   * String::null then this value will be cleared.
	   *
	   * Note that only XM files support this tag.  Setting the
	   * tracker name for other module file formats will be ignored.
	   *
	   * The length of this tag is limited to 20 characters (1 character
	   * = 1 byte).
	   */
	  void setTrackerName(const String &trackerName);

	  /*!
	   * Implements the unified property interface -- export function.
	   * Since the module tag is very limited, the exported map is as well.
	   */
	  PropertyMap properties() const;

	  /*!
	   * Implements the unified property interface -- import function.
	   * Because of the limitations of the module file tag, any tags besides
	   * COMMENT, TITLE and, if it is an XM file, TRACKERNAME, will be
	   * returened. Additionally, if the map contains tags with multiple values,
	   * all but the first will be contained in the returned map of unsupported
	   * properties.
	   */
	  PropertyMap setProperties(const PropertyMap &);

	private:
	  Tag(const Tag &);
	  Tag &operator=(const Tag &);

	  class TagPrivate;
	  TagPrivate *d;
	};

  }

}

#endif

/*** End of inlined file: modtag.h ***/


/*** Start of inlined file: modproperties.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it  under the terms of the GNU Lesser General Public License version  *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,            *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#ifndef TAGLIB_MODPROPERTIES_H
#define TAGLIB_MODPROPERTIES_H

namespace TagLib {

  namespace Mod {

	class TAGLIB_EXPORT Properties : public AudioProperties
	{
	public:
	  Properties(AudioProperties::ReadStyle propertiesStyle);
	  virtual ~Properties();

	  int length() const;
	  int bitrate() const;
	  int sampleRate() const;
	  int channels() const;

	  uint instrumentCount() const;
	  uchar lengthInPatterns() const;

	  void setChannels(int channels);

	  void setInstrumentCount(uint sampleCount);
	  void setLengthInPatterns(uchar lengthInPatterns);

	private:
	  friend class File;

	  Properties(const Properties&);
	  Properties &operator=(const Properties&);

	  class PropertiesPrivate;
	  PropertiesPrivate *d;
	};

  }

}

#endif

/*** End of inlined file: modproperties.h ***/

namespace TagLib {

  namespace Mod {

	class TAGLIB_EXPORT File : public TagLib::Mod::FileBase
	{
	public:
	  /*!
	   * Contructs a Protracker file from \a file. If \a readProperties
	   * is true the file's audio properties will also be read using
	   * \a propertiesStyle. If false, \a propertiesStyle is ignored.
	   */
	  File(FileName file, bool readProperties = true,
		   AudioProperties::ReadStyle propertiesStyle =
		   AudioProperties::Average);

	  /*!
	   * Contructs a Protracker file from \a stream. If \a readProperties
	   * is true the file's audio properties will also be read using
	   * \a propertiesStyle. If false, \a propertiesStyle is ignored.
	   */
	  File(IOStream *stream, bool readProperties = true,
		   AudioProperties::ReadStyle propertiesStyle =
		   AudioProperties::Average);

	  /*!
	   * Destroys this instance of the File.
	   */
	  virtual ~File();

	  Mod::Tag *tag() const;

	  /*!
	   * Implements the unified property interface -- export function.
	   * Forwards to Mod::Tag::properties().
	   */
	  PropertyMap properties() const;

	  /*!
	   * Implements the unified property interface -- import function.
	   * Forwards to Mod::Tag::setProperties().
	   */
	  PropertyMap setProperties(const PropertyMap &);
	  /*!
	   * Returns the Mod::Properties for this file. If no audio properties
	   * were read then this will return a null pointer.
	   */
	  Mod::Properties *audioProperties() const;

	  /*!
	   * Save the file.
	   * This is the same as calling save(AllTags);
	   *
	   * \note Saving Protracker tags is not supported.
	   */
	  bool save();

	private:
	  File(const File &);
	  File &operator=(const File &);

	  void read(bool readProperties);

	  class FilePrivate;
	  FilePrivate *d;
	};

  }

}

#endif

/*** End of inlined file: modfile.h ***/


/*** Start of inlined file: itfile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it  under the terms of the GNU Lesser General Public License version  *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,            *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#ifndef TAGLIB_ITFILE_H
#define TAGLIB_ITFILE_H


/*** Start of inlined file: itproperties.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it  under the terms of the GNU Lesser General Public License version  *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,            *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#ifndef TAGLIB_ITPROPERTIES_H
#define TAGLIB_ITPROPERTIES_H

namespace TagLib {
  namespace IT {
	class TAGLIB_EXPORT Properties : public AudioProperties {
	  friend class File;
	public:
	  /*! Flag bits. */
	  enum {
		Stereo                  =   1,
		Vol0MixOptimizations    =   2,
		UseInstruments          =   4,
		LinearSlides            =   8,
		OldEffects              =  16,
		LinkEffects             =  32,
		UseMidiPitchController  =  64,
		RequestEmbeddedMidiConf = 128
	  };

	  /*! Special bits. */
	  enum {
		MessageAttached  = 1,
		MidiConfEmbedded = 8
	  };

	  Properties(AudioProperties::ReadStyle propertiesStyle);
	  virtual ~Properties();

	  int length()     const;
	  int bitrate()    const;
	  int sampleRate() const;
	  int channels()   const;

	  ushort lengthInPatterns()  const;
	  bool   stereo()            const;
	  ushort instrumentCount()   const;
	  ushort sampleCount()       const;
	  ushort patternCount()      const;
	  ushort version()           const;
	  ushort compatibleVersion() const;
	  ushort flags()             const;
	  ushort special()           const;
	  uchar  globalVolume()      const;
	  uchar  mixVolume()         const;
	  uchar  tempo()             const;
	  uchar  bpmSpeed()          const;
	  uchar  panningSeparation() const;
	  uchar  pitchWheelDepth()   const;

	  void setChannels(int channels);
	  void setLengthInPatterns(ushort lengthInPatterns);
	  void setInstrumentCount(ushort instrumentCount);
	  void setSampleCount (ushort sampleCount);
	  void setPatternCount(ushort patternCount);
	  void setVersion     (ushort version);
	  void setCompatibleVersion(ushort compatibleVersion);
	  void setFlags       (ushort flags);
	  void setSpecial     (ushort special);
	  void setGlobalVolume(uchar globalVolume);
	  void setMixVolume   (uchar mixVolume);
	  void setTempo       (uchar tempo);
	  void setBpmSpeed    (uchar bpmSpeed);
	  void setPanningSeparation(uchar panningSeparation);
	  void setPitchWheelDepth  (uchar pitchWheelDepth);

	private:
	  Properties(const Properties&);
	  Properties &operator=(const Properties&);

	  class PropertiesPrivate;
	  PropertiesPrivate *d;
	};
  }
}

#endif

/*** End of inlined file: itproperties.h ***/

namespace TagLib {

  namespace IT {

	class TAGLIB_EXPORT File : public Mod::FileBase {
	  public:
		/*!
		 * Contructs a Impulse Tracker file from \a file. If \a readProperties
		 * is true the file's audio properties will also be read using
		 * \a propertiesStyle. If false, \a propertiesStyle is ignored.
		 */
		File(FileName file, bool readProperties = true,
			 AudioProperties::ReadStyle propertiesStyle =
			 AudioProperties::Average);

		/*!
		 * Contructs a Impulse Tracker file from \a stream. If \a readProperties
		 * is true the file's audio properties will also be read using
		 * \a propertiesStyle. If false, \a propertiesStyle is ignored.
		 */
		File(IOStream *stram, bool readProperties = true,
			 AudioProperties::ReadStyle propertiesStyle =
			 AudioProperties::Average);

		/*!
		 * Destroys this instance of the File.
		 */
		virtual ~File();

		Mod::Tag *tag() const;

		/*!
		 * Forwards to Mod::Tag::properties().
		 * BIC: will be removed once File::toDict() is made virtual
		 */
		PropertyMap properties() const;

		/*!
		 * Forwards to Mod::Tag::setProperties().
		 * BIC: will be removed once File::setProperties() is made virtual
		 */
		PropertyMap setProperties(const PropertyMap &);

		/*!
		 * Returns the IT::Properties for this file. If no audio properties
		 * were read then this will return a null pointer.
		 */
		IT::Properties *audioProperties() const;

		/*!
		 * Save the file.
		 * This is the same as calling save(AllTags);
		 *
		 * \note Saving Impulse Tracker tags is not supported.
		 */
		bool save();

	  private:
		File(const File &);
		File &operator=(const File &);

		void read(bool readProperties);

		class FilePrivate;
		FilePrivate *d;
	};
  }
}

#endif

/*** End of inlined file: itfile.h ***/


/*** Start of inlined file: s3mfile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it  under the terms of the GNU Lesser General Public License version  *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,            *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#ifndef TAGLIB_S3MFILE_H
#define TAGLIB_S3MFILE_H


/*** Start of inlined file: s3mproperties.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it  under the terms of the GNU Lesser General Public License version  *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,            *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#ifndef TAGLIB_S3MPROPERTIES_H
#define TAGLIB_S3MPROPERTIES_H

namespace TagLib {
  namespace S3M {
	class TAGLIB_EXPORT Properties : public AudioProperties {
	  friend class File;
	public:
	  /*! Flag bits. */
	  enum {
		ST2Vibrato           =   1,
		ST2Tempo             =   2,
		AmigaSlides          =   4,
		Vol0MixOptimizations =   8,
		AmigaLimits          =  16,
		EnableFilter         =  32,
		CustomData           = 128
	  };

	  Properties(AudioProperties::ReadStyle propertiesStyle);
	  virtual ~Properties();

	  int length()     const;
	  int bitrate()    const;
	  int sampleRate() const;
	  int channels()   const;

	  ushort lengthInPatterns()  const;
	  bool   stereo()            const;
	  ushort sampleCount()       const;
	  ushort patternCount()      const;
	  ushort flags()             const;
	  ushort trackerVersion()    const;
	  ushort fileFormatVersion() const;
	  uchar  globalVolume()      const;
	  uchar  masterVolume()      const;
	  uchar  tempo()             const;
	  uchar  bpmSpeed()          const;

	  void setChannels(int channels);

	  void setLengthInPatterns (ushort lengthInPatterns);
	  void setStereo           (bool stereo);
	  void setSampleCount      (ushort sampleCount);
	  void setPatternCount     (ushort patternCount);
	  void setFlags            (ushort flags);
	  void setTrackerVersion   (ushort trackerVersion);
	  void setFileFormatVersion(ushort fileFormatVersion);
	  void setGlobalVolume     (uchar globalVolume);
	  void setMasterVolume     (uchar masterVolume);
	  void setTempo            (uchar tempo);
	  void setBpmSpeed         (uchar bpmSpeed);

	private:
	  Properties(const Properties&);
	  Properties &operator=(const Properties&);

	  class PropertiesPrivate;
	  PropertiesPrivate *d;
	};
  }
}

#endif

/*** End of inlined file: s3mproperties.h ***/

namespace TagLib {

  namespace S3M {

	class TAGLIB_EXPORT File : public Mod::FileBase {
	  public:
		/*!
		 * Contructs a ScreamTracker III file from \a file. If \a readProperties
		 * is true the file's audio properties will also be read using
		 * \a propertiesStyle. If false, \a propertiesStyle is ignored.
		 */
		File(FileName file, bool readProperties = true,
			 AudioProperties::ReadStyle propertiesStyle =
			 AudioProperties::Average);

		/*!
		 * Contructs a ScreamTracker III file from \a stream. If \a readProperties
		 * is true the file's audio properties will also be read using
		 * \a propertiesStyle. If false, \a propertiesStyle is ignored.
		 */
		File(IOStream *stream, bool readProperties = true,
			 AudioProperties::ReadStyle propertiesStyle =
			 AudioProperties::Average);

		/*!
		 * Destroys this instance of the File.
		 */
		virtual ~File();

		Mod::Tag *tag() const;

		/*!
		 * Implements the unified property interface -- export function.
		 * Forwards to Mod::Tag::properties().
		 */
		PropertyMap properties() const;

		/*!
		 * Implements the unified property interface -- import function.
		 * Forwards to Mod::Tag::setProperties().
		 */
		PropertyMap setProperties(const PropertyMap &);

		/*!
		 * Returns the S3M::Properties for this file. If no audio properties
		 * were read then this will return a null pointer.
		 */
		S3M::Properties *audioProperties() const;

		/*!
		 * Save the file.
		 * This is the same as calling save(AllTags);
		 *
		 * \note Saving ScreamTracker III tags is not supported.
		 */
		bool save();

	  private:
		File(const File &);
		File &operator=(const File &);

		void read(bool readProperties);

		class FilePrivate;
		FilePrivate *d;
	};
  }
}

#endif

/*** End of inlined file: s3mfile.h ***/


/*** Start of inlined file: xmfile.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it  under the terms of the GNU Lesser General Public License version  *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,            *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#ifndef TAGLIB_XMFILE_H
#define TAGLIB_XMFILE_H


/*** Start of inlined file: xmproperties.h ***/
/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it  under the terms of the GNU Lesser General Public License version  *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,            *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#ifndef TAGLIB_XMPROPERTIES_H
#define TAGLIB_XMPROPERTIES_H

namespace TagLib {
  namespace XM {
	class Properties : public AudioProperties {
	  friend class File;
	public:
	  /*! Flag bits. */
	  enum {
		LinearFreqTable = 1 // otherwise its the amiga freq. table
	  };

	  Properties(AudioProperties::ReadStyle propertiesStyle);
	  virtual ~Properties();

	  int length()     const;
	  int bitrate()    const;
	  int sampleRate() const;
	  int channels()   const;

	  ushort lengthInPatterns() const;
	  ushort version()          const;
	  ushort restartPosition()  const;
	  ushort patternCount()     const;
	  ushort instrumentCount()  const;
	  uint   sampleCount()      const;
	  ushort flags()            const;
	  ushort tempo()            const;
	  ushort bpmSpeed()         const;

	  void setChannels(int channels);

	  void setLengthInPatterns(ushort lengthInPatterns);
	  void setVersion(ushort version);
	  void setRestartPosition(ushort restartPosition);
	  void setPatternCount(ushort patternCount);
	  void setInstrumentCount(ushort instrumentCount);
	  void setSampleCount(uint sampleCount);
	  void setFlags(ushort flags);
	  void setTempo(ushort tempo);
	  void setBpmSpeed(ushort bpmSpeed);

	private:
	  Properties(const Properties&);
	  Properties &operator=(const Properties&);

	  class PropertiesPrivate;
	  PropertiesPrivate *d;
	};
  }
}

#endif

/*** End of inlined file: xmproperties.h ***/

namespace TagLib {

  namespace XM {

	class TAGLIB_EXPORT File : public Mod::FileBase {
	  public:
		/*!
		 * Contructs a Extended Module file from \a file. If \a readProperties
		 * is true the file's audio properties will also be read using
		 * \a propertiesStyle. If false, \a propertiesStyle is ignored.
		 */
		File(FileName file, bool readProperties = true,
			 AudioProperties::ReadStyle propertiesStyle =
			 AudioProperties::Average);

		/*!
		 * Contructs a Extended Module file from \a stream. If \a readProperties
		 * is true the file's audio properties will also be read using
		 * \a propertiesStyle. If false, \a propertiesStyle is ignored.
		 */
		File(IOStream *stream, bool readProperties = true,
			 AudioProperties::ReadStyle propertiesStyle =
			 AudioProperties::Average);

		/*!
		 * Destroys this instance of the File.
		 */
		virtual ~File();

		Mod::Tag *tag() const;

		/*!
		 * Implements the unified property interface -- export function.
		 * Forwards to Mod::Tag::properties().
		 */
		PropertyMap properties() const;

		/*!
		 * Implements the unified property interface -- import function.
		 * Forwards to Mod::Tag::setProperties().
		 */
		PropertyMap setProperties(const PropertyMap &);

		/*!
		 * Returns the XM::Properties for this file. If no audio properties
		 * were read then this will return a null pointer.
		 */
		XM::Properties *audioProperties() const;

		/*!
		 * Save the file.
		 * This is the same as calling save(AllTags);
		 *
		 * \note Saving Extended Module tags is not supported.
		 */
		bool save();

	  private:
		File(const File &);
		File &operator=(const File &);

		void read(bool readProperties);

		class FilePrivate;
		FilePrivate *d;
	};
  }
}

#endif

/*** End of inlined file: xmfile.h ***/

/*** End of inlined file: TagLibAmalgamTemplatePublicHeaders.h ***/

