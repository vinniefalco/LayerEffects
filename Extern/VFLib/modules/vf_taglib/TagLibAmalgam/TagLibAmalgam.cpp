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


/*** Start of inlined file: TagLibAmalgamTemplateHeaderGlue.h ***/
// This file provides an extra level of indirection for the @remap in the template
#include "TagLibAmalgam.h"

/*** End of inlined file: TagLibAmalgamTemplateHeaderGlue.h ***/

// disable warnings about unsafe standard library calls
#ifdef _MSC_VER
#pragma push_macro ("_CRT_SECURE_NO_WARNINGS")
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#pragma warning (push)
#pragma warning (disable: 4996) // deprecated POSIX names
#endif

//#include "TagLibConfig.h"


/*** Start of inlined file: tpropertymap.cpp ***/
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

using namespace TagLib;

PropertyMap::PropertyMap() : SimplePropertyMap()
{
}

PropertyMap::PropertyMap(const PropertyMap &m) : SimplePropertyMap(m), unsupported(m.unsupported)
{
}

PropertyMap::PropertyMap(const SimplePropertyMap &m)
{
  for(SimplePropertyMap::ConstIterator it = m.begin(); it != m.end(); ++it){
	String key = prepareKey(it->first);
	if(!key.isNull())
	  insert(it->first, it->second);
	else
	  unsupported.append(it->first);
  }
}

PropertyMap::~PropertyMap()
{
}

bool PropertyMap::insert(const String &key, const StringList &values)
{
  String realKey = prepareKey(key);
  if(realKey.isNull())
	return false;

  Iterator result = SimplePropertyMap::find(realKey);
  if(result == end())
	SimplePropertyMap::insert(realKey, values);
  else
	SimplePropertyMap::operator[](realKey).append(values);
  return true;
}

bool PropertyMap::replace(const String &key, const StringList &values)
{
  String realKey = prepareKey(key);
  if(realKey.isNull())
	return false;
  SimplePropertyMap::erase(realKey);
  SimplePropertyMap::insert(realKey, values);
  return true;
}

PropertyMap::Iterator PropertyMap::find(const String &key)
{
  String realKey = prepareKey(key);
  if(realKey.isNull())
	return end();
  return SimplePropertyMap::find(realKey);
}

PropertyMap::ConstIterator PropertyMap::find(const String &key) const
{
  String realKey = prepareKey(key);
  if(realKey.isNull())
	return end();
  return SimplePropertyMap::find(realKey);
}

bool PropertyMap::contains(const String &key) const
{
  String realKey = prepareKey(key);
  if(realKey.isNull())
	return false;
  return SimplePropertyMap::contains(realKey);
}

bool PropertyMap::contains(const PropertyMap &other) const
{
  for(ConstIterator it = other.begin(); it != other.end(); ++it) {
	if(!SimplePropertyMap::contains(it->first))
	  return false;
	if ((*this)[it->first] != it->second)
	  return false;
  }
  return true;
}

PropertyMap &PropertyMap::erase(const String &key)
{
  String realKey = prepareKey(key);
  if(!realKey.isNull())
	SimplePropertyMap::erase(realKey);
  return *this;
}

PropertyMap &PropertyMap::erase(const PropertyMap &other)
{
  for(ConstIterator it = other.begin(); it != other.end(); ++it)
	erase(it->first);
  return *this;
}

PropertyMap &PropertyMap::merge(const PropertyMap &other)
{
  for(PropertyMap::ConstIterator it = other.begin(); it != other.end(); ++it) {
	insert(it->first, it->second);
  }
  unsupported.append(other.unsupported);
  return *this;
}

const StringList &PropertyMap::operator[](const String &key) const
{
  String realKey = prepareKey(key);
  return SimplePropertyMap::operator[](realKey);
}

StringList &PropertyMap::operator[](const String &key)
{
  String realKey = prepareKey(key);
  return SimplePropertyMap::operator[](realKey);
}

bool PropertyMap::operator==(const PropertyMap &other) const
{
  for(ConstIterator it = other.begin(); it != other.end(); ++it) {
	ConstIterator thisFind = find(it->first);
	if( thisFind == end() || (thisFind->second != it->second) )
	  return false;
  }
  for(ConstIterator it = begin(); it != end(); ++it) {
	ConstIterator otherFind = other.find(it->first);
	if( otherFind == other.end() || (otherFind->second != it->second) )
	  return false;
  }
  return unsupported == other.unsupported;
}

bool PropertyMap::operator!=(const PropertyMap &other) const
{
  return !(*this == other);
}

String PropertyMap::toString() const
{
  String ret = "";
  for(ConstIterator it = begin(); it != end(); ++it)
	ret += it->first+"="+it->second.toString(", ") + "\n";
  if(!unsupported.isEmpty())
	ret += "Unsupported Data: " + unsupported.toString(", ") + "\n";
  return ret;
}

void PropertyMap::removeEmpty()
{
  StringList emptyKeys;
  for(Iterator it = begin(); it != end(); ++it)
	if(it->second.isEmpty())
	  emptyKeys.append(it->first);
  for(StringList::Iterator emptyIt = emptyKeys.begin(); emptyIt != emptyKeys.end(); emptyIt++ )
	erase(*emptyIt);
}

StringList &PropertyMap::unsupportedData()
{
  return unsupported;
}

const StringList &PropertyMap::unsupportedData() const
{
  return unsupported;
}

String PropertyMap::prepareKey(const String &proposed) {
  if(proposed.isEmpty())
	return String::null;
  for (String::ConstIterator it = proposed.begin(); it != proposed.end(); it++)
	// forbid non-printable, non-ascii, '=' (#61) and '~' (#126)
	if (*it < 32 || *it >= 128 || *it == 61 || *it == 126)
	  return String::null;
  return proposed.upper();
}

/*** End of inlined file: tpropertymap.cpp ***/


/*** Start of inlined file: tstring.cpp ***/
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


/*** Start of inlined file: unicode.h ***/
#ifndef TAGLIB_UNICODE_H
#define TAGLIB_UNICODE_H

/*******************************************************************************
 *                                                                             *
 * THIS FILE IS INCLUDED IN TAGLIB, BUT IS NOT COPYRIGHTED BY THE TAGLIB       *
 * AUTHORS, NOT PART OF THE TAGLIB API AND COULD GO AWAY AT ANY POINT IN TIME. *
 * AS SUCH IT SHOULD BE CONSIERED FOR INTERNAL USE ONLY.                       *
 *                                                                             *
 *******************************************************************************/

#ifndef DO_NOT_DOCUMENT  // tell Doxygen not to document this header

/*
 * Copyright 2001 Unicode, Inc.
 *
 * Disclaimer
 *
 * This source code is provided as is by Unicode, Inc. No claims are
 * made as to fitness for any particular purpose. No warranties of any
 * kind are expressed or implied. The recipient agrees to determine
 * applicability of information provided. If this file has been
 * purchased on magnetic or optical media from Unicode, Inc., the
 * sole remedy for any claim will be exchange of defective media
 * within 90 days of receipt.
 *
 * Limitations on Rights to Redistribute This Code
 *
 * Unicode, Inc. hereby grants the right to freely use the information
 * supplied in this file in the creation of products supporting the
 * Unicode Standard, and to make copies of this file in any form
 * for internal or external distribution as long as this notice
 * remains attached.
 */

/*
 * This file has been modified by Scott Wheeler <wheeler@kde.org> to remove
 * the UTF32 conversion functions and to place the appropriate functions
 * in their own C++ namespace.
 */

/* ---------------------------------------------------------------------

	Conversions between UTF32, UTF-16, and UTF-8.  Header file.

	Several functions are included here, forming a complete set of
	conversions between the three formats.  UTF-7 is not included
	here, but is handled in a separate source file.

	Each of these routines takes pointers to input buffers and output
	buffers.  The input buffers are const.

	Each routine converts the text between *sourceStart and sourceEnd,
	putting the result into the buffer between *targetStart and
	targetEnd. Note: the end pointers are *after* the last item: e.g.
	*(sourceEnd - 1) is the last item.

	The return result indicates whether the conversion was successful,
	and if not, whether the problem was in the source or target buffers.
	(Only the first encountered problem is indicated.)

	After the conversion, *sourceStart and *targetStart are both
	updated to point to the end of last text successfully converted in
	the respective buffers.

	Input parameters:
	sourceStart - pointer to a pointer to the source buffer.
		The contents of this are modified on return so that
		it points at the next thing to be converted.
	targetStart - similarly, pointer to pointer to the target buffer.
	sourceEnd, targetEnd - respectively pointers to the ends of the
		two buffers, for overflow checking only.

	These conversion functions take a ConversionFlags argument. When this
	flag is set to strict, both irregular sequences and isolated surrogates
	will cause an error.  When the flag is set to lenient, both irregular
	sequences and isolated surrogates are converted.

	Whether the flag is strict or lenient, all illegal sequences will cause
	an error return. This includes sequences such as: <F4 90 80 80>, <C0 80>,
	or <A0> in UTF-8, and values above 0x10FFFF in UTF-32. Conformant code
	must check for illegal sequences.

	When the flag is set to lenient, characters over 0x10FFFF are converted
	to the replacement character; otherwise (when the flag is set to strict)
	they constitute an error.

	Output parameters:
	The value "sourceIllegal" is returned from some routines if the input
	sequence is malformed.  When "sourceIllegal" is returned, the source
	value will point to the illegal value that caused the problem. E.g.,
	in UTF-8 when a sequence is malformed, it points to the start of the
	malformed sequence.

	Author: Mark E. Davis, 1994.
	Rev History: Rick McGowan, fixes & updates May 2001.
		 Fixes & updates, Sept 2001.

------------------------------------------------------------------------ */

/* ---------------------------------------------------------------------
	The following 4 definitions are compiler-specific.
	The C standard does not guarantee that wchar_t has at least
	16 bits, so wchar_t is no less portable than unsigned short!
	All should be unsigned values to avoid sign extension during
	bit mask & shift operations.
------------------------------------------------------------------------ */

/* Some fundamental constants */
#define UNI_REPLACEMENT_CHAR (UTF32)0x0000FFFD
#define UNI_MAX_BMP (UTF32)0x0000FFFF
#define UNI_MAX_UTF16 (UTF32)0x0010FFFF
#define UNI_MAX_UTF32 (UTF32)0x7FFFFFFF

namespace Unicode {

typedef unsigned long	UTF32;	/* at least 32 bits */
typedef unsigned short	UTF16;	/* at least 16 bits */
typedef unsigned char	UTF8;	/* typically 8 bits */
typedef unsigned char	Boolean; /* 0 or 1 */

typedef enum {
	conversionOK = 0,	/* conversion successful */
	sourceExhausted = 1,	/* partial character in source, but hit end */
	targetExhausted = 2,	/* insuff. room in target for conversion */
	sourceIllegal = 3	/* source sequence is illegal/malformed */
} ConversionResult;

typedef enum {
	strictConversion = 0,
	lenientConversion
} ConversionFlags;

ConversionResult ConvertUTF8toUTF16 (
		const UTF8** sourceStart, const UTF8* sourceEnd,
		UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF16toUTF8 (
		const UTF16** sourceStart, const UTF16* sourceEnd,
		UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags);

Boolean isLegalUTF8Sequence(const UTF8 *source, const UTF8 *sourceEnd);

} // namespace Unicode

/* --------------------------------------------------------------------- */

#endif
#endif

/*** End of inlined file: unicode.h ***/


/*** Start of inlined file: tdebug.h ***/
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

#ifndef TAGLIB_DEBUG_H
#define TAGLIB_DEBUG_H

namespace TagLib {

  class String;
  class ByteVector;

#ifndef DO_NOT_DOCUMENT
#ifndef NDEBUG

  /*!
   * A simple function that prints debugging output to cerr if debugging is
   * not disabled.
   *
   * \warning Do not use this outside of TagLib, it could lead to undefined
   * symbols in your build if TagLib is built with NDEBUG defined and your
   * application is not.
   *
   * \internal
   */
  void debug(const String &s);

  /*!
   * For debugging binary data.
   *
   * \warning Do not use this outside of TagLib, it could lead to undefined
   * symbols in your build if TagLib is built with NDEBUG defined and your
   * application is not.
   *
   * \internal
   */
  void debugData(const ByteVector &v);

#else

  // Define these to an empty statement if debugging is disabled.

#define debug(x)
#define debugData(x)

#endif
#endif
}

#endif

/*** End of inlined file: tdebug.h ***/

#include <iostream>

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4996) // Deprecated POSIX names
#pragma push_macro ("_CRT_SECURE_NO_WARNINGS")
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif
#include <string.h>
#ifdef MSC_VER
#pragma pop_macro ("_CRT_SECURE_NO_WARNINGS")
#pragma warning (pop)
#endif

namespace TagLib {

  inline unsigned short byteSwap(unsigned short x)
  {
	return (((x) >> 8) & 0xff) | (((x) & 0xff) << 8);
  }

  inline unsigned short combine(unsigned char c1, unsigned char c2)
  {
	return (c1 << 8) | c2;
  }
}

using namespace TagLib;

class String::StringPrivate : public RefCounter
{
public:
  StringPrivate(const wstring &s) :
	RefCounter(),
	data(s),
	CString(0) {}

  StringPrivate() :
	RefCounter(),
	CString(0) {}

  ~StringPrivate() {
	delete [] CString;
  }

  wstring data;

  /*!
   * This is only used to hold the a pointer to the most recent value of
   * toCString.
   */
  char *CString;
};

String String::null;

////////////////////////////////////////////////////////////////////////////////

String::String()
{
  d = new StringPrivate;
}

String::String(const String &s) : d(s.d)
{
  d->ref();
}

String::String(const std::string &s, Type t)
{
  d = new StringPrivate;

  if(t == UTF16 || t == UTF16BE || t == UTF16LE) {
	debug("String::String() -- A std::string should not contain UTF16.");
	return;
  }

  int length = s.length();
  d->data.resize(length);
  wstring::iterator targetIt = d->data.begin();

  for(std::string::const_iterator it = s.begin(); it != s.end(); it++) {
	*targetIt = uchar(*it);
	++targetIt;
  }

  prepare(t);
}

String::String(const wstring &s, Type t)
{
  d = new StringPrivate(s);
  prepare(t);
}

String::String(const wchar_t *s, Type t)
{
  d = new StringPrivate(s);
  prepare(t);
}

String::String(const char *s, Type t)
{
  d = new StringPrivate;

  if(t == UTF16 || t == UTF16BE || t == UTF16LE) {
	debug("String::String() -- A const char * should not contain UTF16.");
	return;
  }

  int length = ::strlen(s);
  d->data.resize(length);

  wstring::iterator targetIt = d->data.begin();

  for(int i = 0; i < length; i++) {
	*targetIt = uchar(s[i]);
	++targetIt;
  }

  prepare(t);
}

String::String(wchar_t c, Type t)
{
  d = new StringPrivate;
  d->data += c;
  prepare(t);
}

String::String(char c, Type t)
{
  d = new StringPrivate;

  if(t == UTF16 || t == UTF16BE || t == UTF16LE) {
	debug("String::String() -- A std::string should not contain UTF16.");
	return;
  }

  d->data += uchar(c);
  prepare(t);
}

String::String(const ByteVector &v, Type t)
{
  d = new StringPrivate;

  if(v.isEmpty())
	return;

  if(t == Latin1 || t == UTF8) {

	int length = 0;
	d->data.resize(v.size());
	wstring::iterator targetIt = d->data.begin();
	for(ByteVector::ConstIterator it = v.begin(); it != v.end() && (*it); ++it) {
	  *targetIt = uchar(*it);
	  ++targetIt;
	  ++length;
	}
	d->data.resize(length);
  }
  else  {
	d->data.resize(v.size() / 2);
	wstring::iterator targetIt = d->data.begin();

	for(ByteVector::ConstIterator it = v.begin();
		it != v.end() && it + 1 != v.end() && combine(*it, *(it + 1));
		it += 2)
	{
	  *targetIt = combine(*it, *(it + 1));
	  ++targetIt;
	}
  }
  prepare(t);
}

////////////////////////////////////////////////////////////////////////////////

String::~String()
{
  if(d->deref())
	delete d;
}

std::string String::to8Bit(bool unicode) const
{
  std::string s;
  s.resize(d->data.size());

  if(!unicode) {
	std::string::iterator targetIt = s.begin();
	for(wstring::const_iterator it = d->data.begin(); it != d->data.end(); it++) {
	  *targetIt = char(*it);
	  ++targetIt;
	}
	return s;
  }

  const int outputBufferSize = d->data.size() * 3 + 1;

  Unicode::UTF16 *sourceBuffer = new Unicode::UTF16[d->data.size() + 1];
  Unicode::UTF8  *targetBuffer = new Unicode::UTF8[outputBufferSize];

  for(unsigned int i = 0; i < d->data.size(); i++)
	sourceBuffer[i] = Unicode::UTF16(d->data[i]);

  const Unicode::UTF16 *source = sourceBuffer;
  Unicode::UTF8 *target = targetBuffer;

  Unicode::ConversionResult result =
	Unicode::ConvertUTF16toUTF8(&source, sourceBuffer + d->data.size(),
								&target, targetBuffer + outputBufferSize,
								Unicode::lenientConversion);

  if(result != Unicode::conversionOK)
	debug("String::to8Bit() - Unicode conversion error.");

  int newSize = target - targetBuffer;
  s.resize(newSize);
  targetBuffer[newSize] = 0;

  s = (char *) targetBuffer;

  delete [] sourceBuffer;
  delete [] targetBuffer;

  return s;
}

TagLib::wstring String::toWString() const
{
  return d->data;
}

const char *String::toCString(bool unicode) const
{
  delete [] d->CString;

  std::string buffer = to8Bit(unicode);
  d->CString = new char[buffer.size() + 1];
  strcpy(d->CString, buffer.c_str());

  return d->CString;
}

String::Iterator String::begin()
{
  return d->data.begin();
}

String::ConstIterator String::begin() const
{
  return d->data.begin();
}

String::Iterator String::end()
{
  return d->data.end();
}

String::ConstIterator String::end() const
{
  return d->data.end();
}

int String::find(const String &s, int offset) const
{
  wstring::size_type position = d->data.find(s.d->data, offset);

  if(position != wstring::npos)
	return position;
  else
	return -1;
}

int String::rfind(const String &s, int offset) const
{
  wstring::size_type position =
	d->data.rfind(s.d->data, offset == -1 ? wstring::npos : offset);

  if(position != wstring::npos)
	return position;
  else
	return -1;
}

StringList String::split(const String &separator) const
{
  StringList list;
  for(int index = 0;;)
  {
	int sep = find(separator, index);
	if(sep < 0)
	{
	  list.append(substr(index, size() - index));
	  break;
	}
	else
	{
	  list.append(substr(index, sep - index));
	  index = sep + separator.size();
	}
  }
  return list;
}

bool String::startsWith(const String &s) const
{
  if(s.length() > length())
	return false;

  return substr(0, s.length()) == s;
}

String String::substr(uint position, uint n) const
{
  if(n > position + d->data.size())
	n = d->data.size() - position;

  String s;
  s.d->data = d->data.substr(position, n);
  return s;
}

String &String::append(const String &s)
{
  detach();
  d->data += s.d->data;
  return *this;
}

String String::upper() const
{
  String s;

  static int shift = 'A' - 'a';

  for(wstring::const_iterator it = d->data.begin(); it != d->data.end(); ++it) {
	if(*it >= 'a' && *it <= 'z')
	  s.d->data.push_back(static_cast<wchar_t>(*it + shift));
	else
	  s.d->data.push_back(*it);
  }

  return s;
}

TagLib::uint String::size() const
{
  return d->data.size();
}

TagLib::uint String::length() const
{
  return size();
}

bool String::isEmpty() const
{
  return d->data.size() == 0;
}

bool String::isNull() const
{
  return d == null.d;
}

ByteVector String::data(Type t) const
{
  ByteVector v;

  switch(t) {

  case Latin1:
  {
	for(wstring::const_iterator it = d->data.begin(); it != d->data.end(); it++)
	  v.append(char(*it));
	break;
  }
  case UTF8:
  {
	std::string s = to8Bit(true);
	v.setData(s.c_str(), s.length());
	break;
  }
  case UTF16:
  {
	// Assume that if we're doing UTF16 and not UTF16BE that we want little
	// endian encoding.  (Byte Order Mark)

	v.append(char(0xff));
	v.append(char(0xfe));

	for(wstring::const_iterator it = d->data.begin(); it != d->data.end(); it++) {

	  char c1 = *it & 0xff;
	  char c2 = *it >> 8;

	  v.append(c1);
	  v.append(c2);
	}
	break;
  }
  case UTF16BE:
  {
	for(wstring::const_iterator it = d->data.begin(); it != d->data.end(); it++) {

	  char c1 = *it >> 8;
	  char c2 = *it & 0xff;

	  v.append(c1);
	  v.append(c2);
	}
	break;
  }
  case UTF16LE:
  {
	for(wstring::const_iterator it = d->data.begin(); it != d->data.end(); it++) {

	  char c1 = *it & 0xff;
	  char c2 = *it >> 8;

	  v.append(c1);
	  v.append(c2);
	}
	break;
  }
  }

  return v;
}

int String::toInt() const
{
  return toInt(0);
}

int String::toInt(bool *ok) const
{
  int value = 0;

  uint size = d->data.size();
  bool negative = size > 0 && d->data[0] == '-';
  uint start = negative ? 1 : 0;
  uint i = start;

  for(; i < size && d->data[i] >= '0' && d->data[i] <= '9'; i++)
	value = value * 10 + (d->data[i] - '0');

  if(negative)
	value = value * -1;

  if(ok)
	*ok = (size > start && i == size);

  return value;
}

String String::stripWhiteSpace() const
{
  wstring::const_iterator begin = d->data.begin();
  wstring::const_iterator end = d->data.end();

  while(begin != end &&
		(*begin == '\t' || *begin == '\n' || *begin == '\f' ||
		 *begin == '\r' || *begin == ' '))
  {
	++begin;
  }

  if(begin == end)
	return null;

  // There must be at least one non-whitespace character here for us to have
  // gotten this far, so we should be safe not doing bounds checking.

  do {
	--end;
  } while(*end == '\t' || *end == '\n' ||
		  *end == '\f' || *end == '\r' || *end == ' ');

  return String(wstring(begin, end + 1));
}

bool String::isLatin1() const
{
  for(wstring::const_iterator it = d->data.begin(); it != d->data.end(); it++) {
	if(*it >= 256)
	  return false;
  }
  return true;
}

bool String::isAscii() const
{
  for(wstring::const_iterator it = d->data.begin(); it != d->data.end(); it++) {
	if(*it >= 128)
	  return false;
  }
  return true;
}

String String::number(int n) // static
{
  if(n == 0)
	return String("0");

  String charStack;

  bool negative = n < 0;

  if(negative)
	n = n * -1;

  while(n > 0) {
	int remainder = n % 10;
	charStack += char(remainder + '0');
	n = (n - remainder) / 10;
  }

  String s;

  if(negative)
	s += '-';

  for(int i = charStack.d->data.size() - 1; i >= 0; i--)
	s += charStack.d->data[i];

  return s;
}

TagLib::wchar &String::operator[](int i)
{
  detach();

  return d->data[i];
}

const TagLib::wchar &String::operator[](int i) const
{
  return d->data[i];
}

bool String::operator==(const String &s) const
{
  return d == s.d || d->data == s.d->data;
}

bool String::operator!=(const String &s) const
{
  return !operator==(s);
}

String &String::operator+=(const String &s)
{
  detach();

  d->data += s.d->data;
  return *this;
}

String &String::operator+=(const wchar_t *s)
{
  detach();

  d->data += s;
  return *this;
}

String &String::operator+=(const char *s)
{
  detach();

  for(int i = 0; s[i] != 0; i++)
	d->data += uchar(s[i]);
  return *this;
}

String &String::operator+=(wchar_t c)
{
  detach();

  d->data += c;
  return *this;
}

String &String::operator+=(char c)
{
  detach();

  d->data += uchar(c);
  return *this;
}

String &String::operator=(const String &s)
{
  if(&s == this)
	return *this;

  if(d->deref())
	delete d;
  d = s.d;
  d->ref();
  return *this;
}

String &String::operator=(const std::string &s)
{
  if(d->deref())
	delete d;

  d = new StringPrivate;

  d->data.resize(s.size());

  wstring::iterator targetIt = d->data.begin();
  for(std::string::const_iterator it = s.begin(); it != s.end(); it++) {
	*targetIt = uchar(*it);
	++targetIt;
  }

  return *this;
}

String &String::operator=(const wstring &s)
{
  if(d->deref())
	delete d;
  d = new StringPrivate(s);
  return *this;
}

String &String::operator=(const wchar_t *s)
{
  if(d->deref())
	delete d;
  d = new StringPrivate(s);
  return *this;
}

String &String::operator=(char c)
{
  if(d->deref())
	delete d;
  d = new StringPrivate;
  d->data += uchar(c);
  return *this;
}

String &String::operator=(wchar_t c)
{
  if(d->deref())
	delete d;
  d = new StringPrivate;
  d->data += c;
  return *this;
}

String &String::operator=(const char *s)
{
  if(d->deref())
	delete d;

  d = new StringPrivate;

  int length = ::strlen(s);
  d->data.resize(length);

  wstring::iterator targetIt = d->data.begin();
  for(int i = 0; i < length; i++) {
	*targetIt = uchar(s[i]);
	++targetIt;
  }

  return *this;
}

String &String::operator=(const ByteVector &v)
{
  if(d->deref())
	delete d;

  d = new StringPrivate;
  d->data.resize(v.size());
  wstring::iterator targetIt = d->data.begin();

  uint i = 0;

  for(ByteVector::ConstIterator it = v.begin(); it != v.end() && (*it); ++it) {
	*targetIt = uchar(*it);
	++targetIt;
	++i;
  }

  // If we hit a null in the ByteVector, shrink the string again.

  d->data.resize(i);

  return *this;
}

bool String::operator<(const String &s) const
{
  return d->data < s.d->data;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

void String::detach()
{
  if(d->count() > 1) {
	d->deref();
	d = new StringPrivate(d->data);
  }
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void String::prepare(Type t)
{
  switch(t) {
  case UTF16:
  {
	if(d->data.size() >= 1 && (d->data[0] == 0xfeff || d->data[0] == 0xfffe)) {
	  bool swap = d->data[0] != 0xfeff;
	  d->data.erase(d->data.begin(), d->data.begin() + 1);
	  if(swap) {
		for(uint i = 0; i < d->data.size(); i++)
		  d->data[i] = byteSwap((unsigned short)d->data[i]);
	  }
	}
	else {
	  debug("String::prepare() - Invalid UTF16 string.");
	  d->data.erase(d->data.begin(), d->data.end());
	}
	break;
  }
  case UTF8:
  {
	int bufferSize = d->data.size() + 1;
	Unicode::UTF8  *sourceBuffer = new Unicode::UTF8[bufferSize];
	Unicode::UTF16 *targetBuffer = new Unicode::UTF16[bufferSize];

	unsigned int i = 0;
	for(; i < d->data.size(); i++)
	  sourceBuffer[i] = Unicode::UTF8(d->data[i]);
	sourceBuffer[i] = 0;

	const Unicode::UTF8 *source = sourceBuffer;
	Unicode::UTF16 *target = targetBuffer;

	Unicode::ConversionResult result =
	  Unicode::ConvertUTF8toUTF16(&source, sourceBuffer + bufferSize,
								  &target, targetBuffer + bufferSize,
								  Unicode::lenientConversion);

	if(result != Unicode::conversionOK)
	  debug("String::prepare() - Unicode conversion error.");

	int newSize = target != targetBuffer ? target - targetBuffer - 1 : 0;
	d->data.resize(newSize);

	for(int i = 0; i < newSize; i++)
	  d->data[i] = targetBuffer[i];

	delete [] sourceBuffer;
	delete [] targetBuffer;

	break;
  }
  case UTF16LE:
  {
	for(uint i = 0; i < d->data.size(); i++)
	  d->data[i] = byteSwap((unsigned short)d->data[i]);
	break;
  }
  default:
	break;
  }
}

////////////////////////////////////////////////////////////////////////////////
// related functions
////////////////////////////////////////////////////////////////////////////////

const TagLib::String operator+(const TagLib::String &s1, const TagLib::String &s2)
{
  String s(s1);
  s.append(s2);
  return s;
}

const TagLib::String operator+(const char *s1, const TagLib::String &s2)
{
  String s(s1);
  s.append(s2);
  return s;
}

const TagLib::String operator+(const TagLib::String &s1, const char *s2)
{
  String s(s1);
  s.append(s2);
  return s;
}

std::ostream &operator<<(std::ostream &s, const String &str)
{
  s << str.to8Bit();
  return s;
}

/*** End of inlined file: tstring.cpp ***/


/*** Start of inlined file: tfile.cpp ***/
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

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
# include <wchar.h>
# include <windows.h>
# include <io.h>
# define ftruncate _chsize
#else
# include <unistd.h>
#endif

#include <stdlib.h>

#ifndef R_OK
# define R_OK 4
#endif
#ifndef W_OK
# define W_OK 2
#endif

using namespace TagLib;

class File::FilePrivate
{
public:
  FilePrivate(IOStream *stream);

  IOStream *stream;
  bool valid;
  static const uint bufferSize = 1024;
};

File::FilePrivate::FilePrivate(IOStream *stream) :
  stream(stream),
  valid(true)
{
}

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

File::File(FileName fileName)
{
  IOStream *stream = new FileStream(fileName);
  d = new FilePrivate(stream);
}

File::File(IOStream *stream)
{
  d = new FilePrivate(stream);
}

File::~File()
{
  if(d->stream)
	delete d->stream;
  delete d;
}

FileName File::name() const
{
  return d->stream->name();
}

PropertyMap File::properties() const
{
  // ugly workaround until this method is virtual
  if(dynamic_cast<const APE::File* >(this))
	return dynamic_cast<const APE::File* >(this)->properties();
  if(dynamic_cast<const FLAC::File* >(this))
	return dynamic_cast<const FLAC::File* >(this)->properties();
  if(dynamic_cast<const IT::File* >(this))
	return dynamic_cast<const IT::File* >(this)->properties();
  if(dynamic_cast<const Mod::File* >(this))
	return dynamic_cast<const Mod::File* >(this)->properties();
  if(dynamic_cast<const MPC::File* >(this))
	return dynamic_cast<const MPC::File* >(this)->properties();
  if(dynamic_cast<const MPEG::File* >(this))
	return dynamic_cast<const MPEG::File* >(this)->properties();
  if(dynamic_cast<const Ogg::FLAC::File* >(this))
	return dynamic_cast<const Ogg::FLAC::File* >(this)->properties();
  if(dynamic_cast<const Ogg::Speex::File* >(this))
	return dynamic_cast<const Ogg::Speex::File* >(this)->properties();
  if(dynamic_cast<const Ogg::Vorbis::File* >(this))
	return dynamic_cast<const Ogg::Vorbis::File* >(this)->properties();
  if(dynamic_cast<const RIFF::AIFF::File* >(this))
	return dynamic_cast<const RIFF::AIFF::File* >(this)->properties();
  if(dynamic_cast<const RIFF::WAV::File* >(this))
	return dynamic_cast<const RIFF::WAV::File* >(this)->properties();
  if(dynamic_cast<const S3M::File* >(this))
	return dynamic_cast<const S3M::File* >(this)->properties();
  if(dynamic_cast<const TrueAudio::File* >(this))
	return dynamic_cast<const TrueAudio::File* >(this)->properties();
  if(dynamic_cast<const WavPack::File* >(this))
	return dynamic_cast<const WavPack::File* >(this)->properties();
  if(dynamic_cast<const XM::File* >(this))
	return dynamic_cast<const XM::File* >(this)->properties();
  // no specialized implementation available -> use generic one
  // - ASF: ugly format, largely undocumented, not worth implementing
  //   dict interface ...
  // - MP4: taglib's MP4::Tag does not really support anything beyond
  //   the basic implementation, therefor we use just the default Tag
  //   interface
  return tag()->properties();
}

void File::removeUnsupportedProperties(const StringList &properties)
{
  // here we only consider those formats that could possibly contain
  // unsupported properties
  if(dynamic_cast<APE::File* >(this))
	dynamic_cast<APE::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<FLAC::File* >(this))
	dynamic_cast<FLAC::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<MPC::File* >(this))
	dynamic_cast<MPC::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<MPEG::File* >(this))
	dynamic_cast<MPEG::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<Ogg::FLAC::File* >(this))
	dynamic_cast<Ogg::FLAC::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<Ogg::Speex::File* >(this))
	dynamic_cast<Ogg::Speex::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<Ogg::Vorbis::File* >(this))
	dynamic_cast<Ogg::Vorbis::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<RIFF::AIFF::File* >(this))
	dynamic_cast<RIFF::AIFF::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<RIFF::WAV::File* >(this))
	dynamic_cast<RIFF::WAV::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<S3M::File* >(this))
	dynamic_cast<S3M::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<TrueAudio::File* >(this))
	dynamic_cast<TrueAudio::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<WavPack::File* >(this))
	dynamic_cast<WavPack::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<XM::File* >(this))
	dynamic_cast<XM::File* >(this)->removeUnsupportedProperties(properties);
  else
	tag()->removeUnsupportedProperties(properties);
}

PropertyMap File::setProperties(const PropertyMap &properties)
{
  if(dynamic_cast<APE::File* >(this))
	return dynamic_cast<APE::File* >(this)->setProperties(properties);
  else if(dynamic_cast<FLAC::File* >(this))
	return dynamic_cast<FLAC::File* >(this)->setProperties(properties);
  else if(dynamic_cast<IT::File* >(this))
	return dynamic_cast<IT::File* >(this)->setProperties(properties);
  else if(dynamic_cast<Mod::File* >(this))
	return dynamic_cast<Mod::File* >(this)->setProperties(properties);
  else if(dynamic_cast<MPC::File* >(this))
	return dynamic_cast<MPC::File* >(this)->setProperties(properties);
  else if(dynamic_cast<MPEG::File* >(this))
	return dynamic_cast<MPEG::File* >(this)->setProperties(properties);
  else if(dynamic_cast<Ogg::FLAC::File* >(this))
	return dynamic_cast<Ogg::FLAC::File* >(this)->setProperties(properties);
  else if(dynamic_cast<Ogg::Speex::File* >(this))
	return dynamic_cast<Ogg::Speex::File* >(this)->setProperties(properties);
  else if(dynamic_cast<Ogg::Vorbis::File* >(this))
	return dynamic_cast<Ogg::Vorbis::File* >(this)->setProperties(properties);
  else if(dynamic_cast<RIFF::AIFF::File* >(this))
	return dynamic_cast<RIFF::AIFF::File* >(this)->setProperties(properties);
  else if(dynamic_cast<RIFF::WAV::File* >(this))
	return dynamic_cast<RIFF::WAV::File* >(this)->setProperties(properties);
  else if(dynamic_cast<S3M::File* >(this))
	return dynamic_cast<S3M::File* >(this)->setProperties(properties);
  else if(dynamic_cast<TrueAudio::File* >(this))
	return dynamic_cast<TrueAudio::File* >(this)->setProperties(properties);
  else if(dynamic_cast<WavPack::File* >(this))
	return dynamic_cast<WavPack::File* >(this)->setProperties(properties);
  else if(dynamic_cast<XM::File* >(this))
	return dynamic_cast<XM::File* >(this)->setProperties(properties);
  else
	return tag()->setProperties(properties);
}

ByteVector File::readBlock(ulong length)
{
  return d->stream->readBlock(length);
}

void File::writeBlock(const ByteVector &data)
{
  d->stream->writeBlock(data);
}

long File::find(const ByteVector &pattern, long fromOffset, const ByteVector &before)
{
  if(!d->stream || pattern.size() > d->bufferSize)
	  return -1;

  // The position in the file that the current buffer starts at.

  long bufferOffset = fromOffset;
  ByteVector buffer;

  // These variables are used to keep track of a partial match that happens at
  // the end of a buffer.

  int previousPartialMatch = -1;
  int beforePreviousPartialMatch = -1;

  // Save the location of the current read pointer.  We will restore the
  // position using seek() before all returns.

  long originalPosition = tell();

  // Start the search at the offset.

  seek(fromOffset);

  // This loop is the crux of the find method.  There are three cases that we
  // want to account for:
  //
  // (1) The previously searched buffer contained a partial match of the search
  // pattern and we want to see if the next one starts with the remainder of
  // that pattern.
  //
  // (2) The search pattern is wholly contained within the current buffer.
  //
  // (3) The current buffer ends with a partial match of the pattern.  We will
  // note this for use in the next itteration, where we will check for the rest
  // of the pattern.
  //
  // All three of these are done in two steps.  First we check for the pattern
  // and do things appropriately if a match (or partial match) is found.  We
  // then check for "before".  The order is important because it gives priority
  // to "real" matches.

  for(buffer = readBlock(d->bufferSize); buffer.size() > 0; buffer = readBlock(d->bufferSize)) {

	// (1) previous partial match

	if(previousPartialMatch >= 0 && int(d->bufferSize) > previousPartialMatch) {
	  const int patternOffset = (d->bufferSize - previousPartialMatch);
	  if(buffer.containsAt(pattern, 0, patternOffset)) {
		seek(originalPosition);
		return bufferOffset - d->bufferSize + previousPartialMatch;
	  }
	}

	if(!before.isNull() && beforePreviousPartialMatch >= 0 && int(d->bufferSize) > beforePreviousPartialMatch) {
	  const int beforeOffset = (d->bufferSize - beforePreviousPartialMatch);
	  if(buffer.containsAt(before, 0, beforeOffset)) {
		seek(originalPosition);
		return -1;
	  }
	}

	// (2) pattern contained in current buffer

	long location = buffer.find(pattern);
	if(location >= 0) {
	  seek(originalPosition);
	  return bufferOffset + location;
	}

	if(!before.isNull() && buffer.find(before) >= 0) {
	  seek(originalPosition);
	  return -1;
	}

	// (3) partial match

	previousPartialMatch = buffer.endsWithPartialMatch(pattern);

	if(!before.isNull())
	  beforePreviousPartialMatch = buffer.endsWithPartialMatch(before);

	bufferOffset += d->bufferSize;
  }

  // Since we hit the end of the file, reset the status before continuing.

  clear();

  seek(originalPosition);

  return -1;
}

long File::rfind(const ByteVector &pattern, long fromOffset, const ByteVector &before)
{
  if(!d->stream || pattern.size() > d->bufferSize)
	  return -1;

  // The position in the file that the current buffer starts at.

  ByteVector buffer;

  // These variables are used to keep track of a partial match that happens at
  // the end of a buffer.

  /*
  int previousPartialMatch = -1;
  int beforePreviousPartialMatch = -1;
  */

  // Save the location of the current read pointer.  We will restore the
  // position using seek() before all returns.

  long originalPosition = tell();

  // Start the search at the offset.

  long bufferOffset;
  if(fromOffset == 0) {
	seek(-1 * int(d->bufferSize), End);
	bufferOffset = tell();
  }
  else {
	seek(fromOffset + -1 * int(d->bufferSize), Beginning);
	bufferOffset = tell();
  }

  // See the notes in find() for an explanation of this algorithm.

  for(buffer = readBlock(d->bufferSize); buffer.size() > 0; buffer = readBlock(d->bufferSize)) {

	// TODO: (1) previous partial match

	// (2) pattern contained in current buffer

	long location = buffer.rfind(pattern);
	if(location >= 0) {
	  seek(originalPosition);
	  return bufferOffset + location;
	}

	if(!before.isNull() && buffer.find(before) >= 0) {
	  seek(originalPosition);
	  return -1;
	}

	// TODO: (3) partial match

	bufferOffset -= d->bufferSize;
	seek(bufferOffset);
  }

  // Since we hit the end of the file, reset the status before continuing.

  clear();

  seek(originalPosition);

  return -1;
}

void File::insert(const ByteVector &data, ulong start, ulong replace)
{
  d->stream->insert(data, start, replace);
}

void File::removeBlock(ulong start, ulong length)
{
  d->stream->removeBlock(start, length);
}

bool File::readOnly() const
{
  return d->stream->readOnly();
}

bool File::isOpen() const
{
  return d->stream->isOpen();
}

bool File::isValid() const
{
  return isOpen() && d->valid;
}

void File::seek(long offset, Position p)
{
  d->stream->seek(offset, IOStream::Position(p));
}

void File::truncate(long length)
{
  d->stream->truncate(length);
}

void File::clear()
{
  d->stream->clear();
}

long File::tell() const
{
  return d->stream->tell();
}

long File::length()
{
  return d->stream->length();
}

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4996) // Deprecated POSIX name
#endif

bool File::isReadable(const char *file)
{
  return access(file, R_OK) == 0;
}

bool File::isWritable(const char *file)
{
  return access(file, W_OK) == 0;
}

#ifdef _MSC_VER
#pragma warning (pop)
#endif

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

TagLib::uint File::bufferSize()
{
  return FilePrivate::bufferSize;
}

void File::setValid(bool valid)
{
  d->valid = valid;
}

/*** End of inlined file: tfile.cpp ***/


/*** Start of inlined file: tag.cpp ***/
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

using namespace TagLib;

class Tag::TagPrivate
{

};

Tag::Tag()
{

}

Tag::~Tag()
{

}

bool Tag::isEmpty() const
{
  return (title().isEmpty() &&
		  artist().isEmpty() &&
		  album().isEmpty() &&
		  comment().isEmpty() &&
		  genre().isEmpty() &&
		  year() == 0 &&
		  track() == 0);
}

PropertyMap Tag::properties() const
{
  PropertyMap map;
  if(!(title().isNull()))
	map["TITLE"].append(title());
  if(!(artist().isNull()))
	map["ARTIST"].append(artist());
  if(!(album().isNull()))
	map["ALBUM"].append(album());
  if(!(comment().isNull()))
	map["COMMENT"].append(comment());
  if(!(genre().isNull()))
	map["GENRE"].append(genre());
  if(!(year() == 0))
	map["DATE"].append(String::number(year()));
  if(!(track() == 0))
	map["TRACKNUMBER"].append(String::number(track()));
  return map;
}

void Tag::removeUnsupportedProperties(const StringList&)
{
}

PropertyMap Tag::setProperties(const PropertyMap &origProps)
{
  PropertyMap properties(origProps);
  properties.removeEmpty();
  StringList oneValueSet;
  // can this be simplified by using some preprocessor defines / function pointers?
  if(properties.contains("TITLE")) {
	setTitle(properties["TITLE"].front());
	oneValueSet.append("TITLE");
  } else
	setTitle(String::null);

  if(properties.contains("ARTIST")) {
	setArtist(properties["ARTIST"].front());
	oneValueSet.append("ARTIST");
  } else
	setArtist(String::null);

  if(properties.contains("ALBUM")) {
	setAlbum(properties["ALBUM"].front());
	oneValueSet.append("ALBUM");
  } else
	setAlbum(String::null);

  if(properties.contains("COMMENT")) {
	setComment(properties["COMMENT"].front());
	oneValueSet.append("COMMENT");
  } else
	setComment(String::null);

  if(properties.contains("GENRE")) {
	setGenre(properties["GENRE"].front());
	oneValueSet.append("GENRE");
  } else
	setGenre(String::null);

  if(properties.contains("DATE")) {
	bool ok;
	int date = properties["DATE"].front().toInt(&ok);
	if(ok) {
	  setYear(date);
	  oneValueSet.append("DATE");
	} else
	  setYear(0);
  }
  else
	setYear(0);

  if(properties.contains("TRACKNUMBER")) {
	bool ok;
	int track = properties["TRACKNUMBER"].front().toInt(&ok);
	if(ok) {
	  setTrack(track);
	  oneValueSet.append("TRACKNUMBER");
	} else
	  setTrack(0);
  }
  else
	setYear(0);

  // for each tag that has been set above, remove the first entry in the corresponding
  // value list. The others will be returned as unsupported by this format.
  for(StringList::Iterator it = oneValueSet.begin(); it != oneValueSet.end(); ++it) {
	if(properties[*it].size() == 1)
	  properties.erase(*it);
	else
	  properties[*it].erase( properties[*it].begin() );
  }
  return properties;
}

void Tag::duplicate(const Tag *source, Tag *target, bool overwrite) // static
{
  if(overwrite) {
	target->setTitle(source->title());
	target->setArtist(source->artist());
	target->setAlbum(source->album());
	target->setComment(source->comment());
	target->setGenre(source->genre());
	target->setYear(source->year());
	target->setTrack(source->track());
  }
  else {
	if(target->title().isEmpty())
	  target->setTitle(source->title());
	if(target->artist().isEmpty())
	  target->setArtist(source->artist());
	if(target->album().isEmpty())
	  target->setAlbum(source->album());
	if(target->comment().isEmpty())
	  target->setComment(source->comment());
	if(target->genre().isEmpty())
	  target->setGenre(source->genre());
	if(target->year() <= 0)
	  target->setYear(source->year());
	if(target->track() <= 0)
	  target->setTrack(source->track());
  }
}

/*** End of inlined file: tag.cpp ***/


/*** Start of inlined file: tagunion.cpp ***/
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


/*** Start of inlined file: tagunion.h ***/
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

#ifndef TAGLIB_TAGUNION_H
#define TAGLIB_TAGUNION_H

#ifndef DO_NOT_DOCUMENT

namespace TagLib {

  /*!
   * \internal
   */

  class TagUnion : public Tag
  {
  public:

	enum AccessType { Read, Write };

	/*!
	 * Creates a TagLib::Tag that is the union of \a first, \a second, and
	 * \a third.  The TagUnion takes ownership of these tags and will handle
	 * their deletion.
	 */
	TagUnion(Tag *first = 0, Tag *second = 0, Tag *third = 0);

	virtual ~TagUnion();

	Tag *operator[](int index) const;
	Tag *tag(int index) const;

	void set(int index, Tag *tag);

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

	template <class T> T *access(int index, bool create)
	{
	  if(!create || tag(index))
		return static_cast<T *>(tag(index));

	  set(index, new T);
	  return static_cast<T *>(tag(index));
	}

  private:
	TagUnion(const Tag &);
	TagUnion &operator=(const Tag &);

	class TagUnionPrivate;
	TagUnionPrivate *d;
  };
}

#endif
#endif

/*** End of inlined file: tagunion.h ***/

using namespace TagLib;

#define stringUnion(method)                                          \
  if(tag(0) && !tag(0)->method().isEmpty())                          \
	return tag(0)->method();                                         \
  if(tag(1) && !tag(1)->method().isEmpty())                          \
	return tag(1)->method();                                         \
  if(tag(2) && !tag(2)->method().isEmpty())                          \
	return tag(2)->method();                                         \
  return String::null                                                \

#define numberUnion(method)                                          \
  if(tag(0) && tag(0)->method() > 0)                                 \
	return tag(0)->method();                                         \
  if(tag(1) && tag(1)->method() > 0)                                 \
	return tag(1)->method();                                         \
  if(tag(2) && tag(2)->method() > 0)                                 \
	return tag(2)->method();                                         \
  return 0

#define setUnion(method, value)                                      \
  if(tag(0))                                                         \
	tag(0)->set##method(value);                                      \
  if(tag(1))                                                         \
	tag(1)->set##method(value);                                      \
  if(tag(2))                                                         \
	tag(2)->set##method(value);                                      \

class TagUnion::TagUnionPrivate
{
public:
  TagUnionPrivate() : tags(3, static_cast<Tag *>(0))
  {

  }

  ~TagUnionPrivate()
  {
	delete tags[0];
	delete tags[1];
	delete tags[2];
  }

  std::vector<Tag *> tags;
};

TagUnion::TagUnion(Tag *first, Tag *second, Tag *third)
{
  d = new TagUnionPrivate;

  d->tags[0] = first;
  d->tags[1] = second;
  d->tags[2] = third;
}

TagUnion::~TagUnion()
{
  delete d;
}

Tag *TagUnion::operator[](int index) const
{
  return tag(index);
}

Tag *TagUnion::tag(int index) const
{
  return d->tags[index];
}

void TagUnion::set(int index, Tag *tag)
{
  delete d->tags[index];
  d->tags[index] = tag;
}

String TagUnion::title() const
{
  stringUnion(title);
}

String TagUnion::artist() const
{
  stringUnion(artist);
}

String TagUnion::album() const
{
  stringUnion(album);
}

String TagUnion::comment() const
{
  stringUnion(comment);
}

String TagUnion::genre() const
{
  stringUnion(genre);
}

TagLib::uint TagUnion::year() const
{
  numberUnion(year);
}

TagLib::uint TagUnion::track() const
{
  numberUnion(track);
}

void TagUnion::setTitle(const String &s)
{
  setUnion(Title, s);
}

void TagUnion::setArtist(const String &s)
{
  setUnion(Artist, s);
}

void TagUnion::setAlbum(const String &s)
{
  setUnion(Album, s);
}

void TagUnion::setComment(const String &s)
{
  setUnion(Comment, s);
}

void TagUnion::setGenre(const String &s)
{
  setUnion(Genre, s);
}

void TagUnion::setYear(uint i)
{
  setUnion(Year, i);
}

void TagUnion::setTrack(uint i)
{
  setUnion(Track, i);
}

bool TagUnion::isEmpty() const
{
  if(d->tags[0] && !d->tags[0]->isEmpty())
	return false;
  if(d->tags[1] && !d->tags[1]->isEmpty())
	return false;
  if(d->tags[2] && !d->tags[2]->isEmpty())
	return false;

  return true;
}

/*** End of inlined file: tagunion.cpp ***/


/*** Start of inlined file: fileref.cpp ***/
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace TagLib;

class FileRef::FileRefPrivate : public RefCounter
{
public:
  FileRefPrivate(File *f) : RefCounter(), file(f) {}
  ~FileRefPrivate() {
	delete file;
  }

  File *file;
  static List<const FileTypeResolver *> fileTypeResolvers;
};

List<const FileRef::FileTypeResolver *> FileRef::FileRefPrivate::fileTypeResolvers;

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

FileRef::FileRef()
{
  d = new FileRefPrivate(0);
}

FileRef::FileRef(FileName fileName, bool readAudioProperties,
				 AudioProperties::ReadStyle audioPropertiesStyle)
{
  d = new FileRefPrivate(create(fileName, readAudioProperties, audioPropertiesStyle));
}

FileRef::FileRef(File *file)
{
  d = new FileRefPrivate(file);
}

FileRef::FileRef(const FileRef &ref) : d(ref.d)
{
  d->ref();
}

FileRef::~FileRef()
{
  if(d->deref())
	delete d;
}

Tag *FileRef::tag() const
{
  if(isNull()) {
	debug("FileRef::tag() - Called without a valid file.");
	return 0;
  }
  return d->file->tag();
}

AudioProperties *FileRef::audioProperties() const
{
  if(isNull()) {
	debug("FileRef::audioProperties() - Called without a valid file.");
	return 0;
  }
  return d->file->audioProperties();
}

File *FileRef::file() const
{
  return d->file;
}

bool FileRef::save()
{
  if(isNull()) {
	debug("FileRef::save() - Called without a valid file.");
	return false;
  }
  return d->file->save();
}

const FileRef::FileTypeResolver *FileRef::addFileTypeResolver(const FileRef::FileTypeResolver *resolver) // static
{
  FileRefPrivate::fileTypeResolvers.prepend(resolver);
  return resolver;
}

StringList FileRef::defaultFileExtensions()
{
  StringList l;

  l.append("ogg");
  l.append("flac");
  l.append("oga");
  l.append("mp3");
  l.append("mpc");
  l.append("wv");
  l.append("spx");
  l.append("tta");
  l.append("m4a");
  l.append("m4r");
  l.append("m4b");
  l.append("m4p");
  l.append("3g2");
  l.append("mp4");
  l.append("wma");
  l.append("asf");
  l.append("aif");
  l.append("aiff");
  l.append("wav");
  l.append("ape");
  l.append("mod");
  l.append("module"); // alias for "mod"
  l.append("nst"); // alias for "mod"
  l.append("wow"); // alias for "mod"
  l.append("s3m");
  l.append("it");
  l.append("xm");

  return l;
}

bool FileRef::isNull() const
{
  return !d->file || !d->file->isValid();
}

FileRef &FileRef::operator=(const FileRef &ref)
{
  if(&ref == this)
	return *this;

  if(d->deref())
	delete d;

  d = ref.d;
  d->ref();

  return *this;
}

bool FileRef::operator==(const FileRef &ref) const
{
  return ref.d->file == d->file;
}

bool FileRef::operator!=(const FileRef &ref) const
{
  return ref.d->file != d->file;
}

File *FileRef::create(FileName fileName, bool readAudioProperties,
					  AudioProperties::ReadStyle audioPropertiesStyle) // static
{

  List<const FileTypeResolver *>::ConstIterator it = FileRefPrivate::fileTypeResolvers.begin();

  for(; it != FileRefPrivate::fileTypeResolvers.end(); ++it) {
	File *file = (*it)->createFile(fileName, readAudioProperties, audioPropertiesStyle);
	if(file)
	  return file;
  }

  // Ok, this is really dumb for now, but it works for testing.

  String s;

#ifdef _WIN32
  s = (wcslen((const wchar_t *) fileName) > 0) ? String((const wchar_t *) fileName) : String((const char *) fileName);
#else
  s = fileName;
#endif

  // If this list is updated, the method defaultFileExtensions() should also be
  // updated.  However at some point that list should be created at the same time
  // that a default file type resolver is created.

  int pos = s.rfind(".");
  if(pos != -1) {
	String ext = s.substr(pos + 1).upper();
	if(ext == "MP3")
	  return new MPEG::File(fileName, readAudioProperties, audioPropertiesStyle);
	if(ext == "OGG")
	  return new Ogg::Vorbis::File(fileName, readAudioProperties, audioPropertiesStyle);
	if(ext == "OGA") {
	  /* .oga can be any audio in the Ogg container. First try FLAC, then Vorbis. */
	  File *file = new Ogg::FLAC::File(fileName, readAudioProperties, audioPropertiesStyle);
	  if (file->isValid())
		return file;
	  delete file;
	  return new Ogg::Vorbis::File(fileName, readAudioProperties, audioPropertiesStyle);
	}
	if(ext == "FLAC")
	  return new FLAC::File(fileName, readAudioProperties, audioPropertiesStyle);
	if(ext == "MPC")
	  return new MPC::File(fileName, readAudioProperties, audioPropertiesStyle);
	if(ext == "WV")
	  return new WavPack::File(fileName, readAudioProperties, audioPropertiesStyle);
	if(ext == "SPX")
	  return new Ogg::Speex::File(fileName, readAudioProperties, audioPropertiesStyle);
	if(ext == "TTA")
	  return new TrueAudio::File(fileName, readAudioProperties, audioPropertiesStyle);
	if(ext == "M4A" || ext == "M4R" || ext == "M4B" || ext == "M4P" || ext == "MP4" || ext == "3G2")
	  return new MP4::File(fileName, readAudioProperties, audioPropertiesStyle);
	if(ext == "WMA" || ext == "ASF")
	  return new ASF::File(fileName, readAudioProperties, audioPropertiesStyle);
	if(ext == "AIF" || ext == "AIFF")
	  return new RIFF::AIFF::File(fileName, readAudioProperties, audioPropertiesStyle);
	if(ext == "WAV")
	  return new RIFF::WAV::File(fileName, readAudioProperties, audioPropertiesStyle);
	if(ext == "APE")
	  return new APE::File(fileName, readAudioProperties, audioPropertiesStyle);
	// module, nst and wow are possible but uncommon extensions
	if(ext == "MOD" || ext == "MODULE" || ext == "NST" || ext == "WOW")
	  return new Mod::File(fileName, readAudioProperties, audioPropertiesStyle);
	if(ext == "S3M")
	  return new S3M::File(fileName, readAudioProperties, audioPropertiesStyle);
	if(ext == "IT")
	  return new IT::File(fileName, readAudioProperties, audioPropertiesStyle);
	if(ext == "XM")
	  return new XM::File(fileName, readAudioProperties, audioPropertiesStyle);
  }

  return 0;
}

/*** End of inlined file: fileref.cpp ***/


/*** Start of inlined file: audioproperties.cpp ***/
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

using namespace TagLib;

class AudioProperties::AudioPropertiesPrivate
{

};

////////////////////////////////////////////////////////////////////////////////
// public methods
////////////////////////////////////////////////////////////////////////////////

AudioProperties::~AudioProperties()
{

}

////////////////////////////////////////////////////////////////////////////////
// protected methods
////////////////////////////////////////////////////////////////////////////////

AudioProperties::AudioProperties(ReadStyle)
{

}

/*** End of inlined file: audioproperties.cpp ***/


/*** Start of inlined file: mpegfile.cpp ***/
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

#include <bitset>

using namespace TagLib;

namespace
{
  enum { ID3v2Index = 0, APEIndex = 1, ID3v1Index = 2 };
}

class MPEG::File::FilePrivate
{
public:
  FilePrivate(ID3v2::FrameFactory *frameFactory = ID3v2::FrameFactory::instance()) :
	ID3v2FrameFactory(frameFactory),
	ID3v2Location(-1),
	ID3v2OriginalSize(0),
	APELocation(-1),
	APEFooterLocation(-1),
	APEOriginalSize(0),
	ID3v1Location(-1),
	hasID3v2(false),
	hasID3v1(false),
	hasAPE(false),
	properties(0)
  {

  }

  ~FilePrivate()
  {
	delete properties;
  }

  const ID3v2::FrameFactory *ID3v2FrameFactory;

  long ID3v2Location;
  uint ID3v2OriginalSize;

  long APELocation;
  long APEFooterLocation;
  uint APEOriginalSize;

  long ID3v1Location;

  TagUnion tag;

  // These indicate whether the file *on disk* has these tags, not if
  // this data structure does.  This is used in computing offsets.

  bool hasID3v2;
  bool hasID3v1;
  bool hasAPE;

  Properties *properties;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

MPEG::File::File(FileName file, bool readProperties,
				 Properties::ReadStyle propertiesStyle) : TagLib::File(file)
{
  d = new FilePrivate;

  if(isOpen())
	read(readProperties, propertiesStyle);
}

MPEG::File::File(FileName file, ID3v2::FrameFactory *frameFactory,
				 bool readProperties, Properties::ReadStyle propertiesStyle) :
  TagLib::File(file)
{
  d = new FilePrivate(frameFactory);

  if(isOpen())
	read(readProperties, propertiesStyle);
}

MPEG::File::File(IOStream *stream, ID3v2::FrameFactory *frameFactory,
				 bool readProperties, Properties::ReadStyle propertiesStyle) :
  TagLib::File(stream)
{
  d = new FilePrivate(frameFactory);

  if(isOpen())
	read(readProperties, propertiesStyle);
}

MPEG::File::~File()
{
  delete d;
}

TagLib::Tag *MPEG::File::tag() const
{
  return &d->tag;
}

PropertyMap MPEG::File::properties() const
{
  // once Tag::properties() is virtual, this case distinction could actually be done
  // within TagUnion.
  if(d->hasID3v2)
	return d->tag.access<ID3v2::Tag>(ID3v2Index, false)->properties();
  if(d->hasAPE)
	return d->tag.access<APE::Tag>(APEIndex, false)->properties();
  if(d->hasID3v1)
	return d->tag.access<ID3v1::Tag>(ID3v1Index, false)->properties();
  return PropertyMap();
}

void MPEG::File::removeUnsupportedProperties(const StringList &properties)
{
  if(d->hasID3v2)
	d->tag.access<ID3v2::Tag>(ID3v2Index, false)->removeUnsupportedProperties(properties);
  else if(d->hasAPE)
	d->tag.access<APE::Tag>(APEIndex, false)->removeUnsupportedProperties(properties);
  else if(d->hasID3v1)
	d->tag.access<ID3v1::Tag>(ID3v1Index, false)->removeUnsupportedProperties(properties);
}
PropertyMap MPEG::File::setProperties(const PropertyMap &properties)
{
  if(d->hasID3v2)
	return d->tag.access<ID3v2::Tag>(ID3v2Index, false)->setProperties(properties);
  else if(d->hasAPE)
	return d->tag.access<APE::Tag>(APEIndex, false)->setProperties(properties);
  else if(d->hasID3v1)
	return d->tag.access<ID3v1::Tag>(ID3v1Index, false)->setProperties(properties);
  else
	return d->tag.access<ID3v2::Tag>(ID3v2Index, true)->setProperties(properties);
}

MPEG::Properties *MPEG::File::audioProperties() const
{
  return d->properties;
}

bool MPEG::File::save()
{
  return save(AllTags);
}

bool MPEG::File::save(int tags)
{
  return save(tags, true);
}

bool MPEG::File::save(int tags, bool stripOthers)
{
  return save(tags, stripOthers, 4);
}

bool MPEG::File::save(int tags, bool stripOthers, int id3v2Version)
{
  if(tags == NoTags && stripOthers)
	return strip(AllTags);

  if(!ID3v2Tag() && !ID3v1Tag() && !APETag()) {

	if((d->hasID3v1 || d->hasID3v2 || d->hasAPE) && stripOthers)
	  return strip(AllTags);

	return true;
  }

  if(readOnly()) {
	debug("MPEG::File::save() -- File is read only.");
	return false;
  }

  // Create the tags if we've been asked to.  Copy the values from the tag that
  // does exist into the new tag.

  if((tags & ID3v2) && ID3v1Tag())
	Tag::duplicate(ID3v1Tag(), ID3v2Tag(true), false);

  if((tags & ID3v1) && d->tag[ID3v2Index])
	Tag::duplicate(ID3v2Tag(), ID3v1Tag(true), false);

  bool success = true;

  if(ID3v2 & tags) {

	if(ID3v2Tag() && !ID3v2Tag()->isEmpty()) {

	  if(!d->hasID3v2)
		d->ID3v2Location = 0;

	  insert(ID3v2Tag()->render(id3v2Version), d->ID3v2Location, d->ID3v2OriginalSize);

	  d->hasID3v2 = true;

	  // v1 tag location has changed, update if it exists

	  if(ID3v1Tag())
		d->ID3v1Location = findID3v1();

	  // APE tag location has changed, update if it exists

	  if(APETag())
		findAPE();
	}
	else if(stripOthers)
	  success = strip(ID3v2, false) && success;
  }
  else if(d->hasID3v2 && stripOthers)
	success = strip(ID3v2) && success;

  if(ID3v1 & tags) {
	if(ID3v1Tag() && !ID3v1Tag()->isEmpty()) {
	  int offset = d->hasID3v1 ? -128 : 0;
	  seek(offset, End);
	  writeBlock(ID3v1Tag()->render());
	  d->hasID3v1 = true;
	  d->ID3v1Location = findID3v1();
	}
	else if(stripOthers)
	  success = strip(ID3v1) && success;
  }
  else if(d->hasID3v1 && stripOthers)
	success = strip(ID3v1, false) && success;

  // Dont save an APE-tag unless one has been created

  if((APE & tags) && APETag()) {
	if(d->hasAPE)
	  insert(APETag()->render(), d->APELocation, d->APEOriginalSize);
	else {
	  if(d->hasID3v1) {
		insert(APETag()->render(), d->ID3v1Location, 0);
		d->APEOriginalSize = APETag()->footer()->completeTagSize();
		d->hasAPE = true;
		d->APELocation = d->ID3v1Location;
		d->ID3v1Location += d->APEOriginalSize;
	  }
	  else {
		seek(0, End);
		d->APELocation = tell();
		APE::Tag *apeTag = d->tag.access<APE::Tag>(APEIndex, false);
		d->APEFooterLocation = d->APELocation
							   + apeTag->footer()->completeTagSize()
							   - APE::Footer::size();
		writeBlock(APETag()->render());
		d->APEOriginalSize = APETag()->footer()->completeTagSize();
		d->hasAPE = true;
	  }
	}
  }
  else if(d->hasAPE && stripOthers)
	success = strip(APE, false) && success;

  return success;
}

ID3v2::Tag *MPEG::File::ID3v2Tag(bool create)
{
  return d->tag.access<ID3v2::Tag>(ID3v2Index, create);
}

ID3v1::Tag *MPEG::File::ID3v1Tag(bool create)
{
  return d->tag.access<ID3v1::Tag>(ID3v1Index, create);
}

APE::Tag *MPEG::File::APETag(bool create)
{
  return d->tag.access<APE::Tag>(APEIndex, create);
}

bool MPEG::File::strip(int tags)
{
  return strip(tags, true);
}

bool MPEG::File::strip(int tags, bool freeMemory)
{
  if(readOnly()) {
	debug("MPEG::File::strip() - Cannot strip tags from a read only file.");
	return false;
  }

  if((tags & ID3v2) && d->hasID3v2) {
	removeBlock(d->ID3v2Location, d->ID3v2OriginalSize);
	d->ID3v2Location = -1;
	d->ID3v2OriginalSize = 0;
	d->hasID3v2 = false;

	if(freeMemory)
	  d->tag.set(ID3v2Index, 0);

	// v1 tag location has changed, update if it exists

	if(ID3v1Tag())
	  d->ID3v1Location = findID3v1();

	// APE tag location has changed, update if it exists

   if(APETag())
	  findAPE();
  }

  if((tags & ID3v1) && d->hasID3v1) {
	truncate(d->ID3v1Location);
	d->ID3v1Location = -1;
	d->hasID3v1 = false;

	if(freeMemory)
	  d->tag.set(ID3v1Index, 0);
  }

  if((tags & APE) && d->hasAPE) {
	removeBlock(d->APELocation, d->APEOriginalSize);
	d->APELocation = -1;
	d->APEFooterLocation = -1;
	d->hasAPE = false;
	if(d->hasID3v1) {
	  if(d->ID3v1Location > d->APELocation)
		d->ID3v1Location -= d->APEOriginalSize;
	}

	if(freeMemory)
	  d->tag.set(APEIndex, 0);
  }

  return true;
}

void MPEG::File::setID3v2FrameFactory(const ID3v2::FrameFactory *factory)
{
  d->ID3v2FrameFactory = factory;
}

long MPEG::File::nextFrameOffset(long position)
{
  bool foundLastSyncPattern = false;

  ByteVector buffer;

  for(;;) {
	seek(position);
	buffer = readBlock(bufferSize());

	if(buffer.size() <= 0)
	  return -1;

	if(foundLastSyncPattern && secondSynchByte(buffer[0]))
	  return position - 1;

	for(uint i = 0; i < buffer.size() - 1; i++) {
	  if(uchar(buffer[i]) == 0xff && secondSynchByte(buffer[i + 1]))
		return position + i;
	}

	foundLastSyncPattern = uchar(buffer[buffer.size() - 1]) == 0xff;
	position += buffer.size();
  }
}

long MPEG::File::previousFrameOffset(long position)
{
  bool foundFirstSyncPattern = false;
  ByteVector buffer;

  while (position > 0) {
	long size = ulong(position) < bufferSize() ? position : bufferSize();
	position -= size;

	seek(position);
	buffer = readBlock(size);

	if(buffer.size() <= 0)
	  break;

	if(foundFirstSyncPattern && uchar(buffer[buffer.size() - 1]) == 0xff)
	  return position + buffer.size() - 1;

	for(int i = buffer.size() - 2; i >= 0; i--) {
	  if(uchar(buffer[i]) == 0xff && secondSynchByte(buffer[i + 1]))
		return position + i;
	}

	foundFirstSyncPattern = secondSynchByte(buffer[0]);
  }
  return -1;
}

long MPEG::File::firstFrameOffset()
{
  long position = 0;

  if(ID3v2Tag())
	position = d->ID3v2Location + ID3v2Tag()->header()->completeTagSize();

  return nextFrameOffset(position);
}

long MPEG::File::lastFrameOffset()
{
  return previousFrameOffset(ID3v1Tag() ? d->ID3v1Location - 1 : length());
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void MPEG::File::read(bool readProperties, Properties::ReadStyle propertiesStyle)
{
  // Look for an ID3v2 tag

  d->ID3v2Location = findID3v2();

  if(d->ID3v2Location >= 0) {

	d->tag.set(ID3v2Index, new ID3v2::Tag(this, d->ID3v2Location, d->ID3v2FrameFactory));

	d->ID3v2OriginalSize = ID3v2Tag()->header()->completeTagSize();

	if(ID3v2Tag()->header()->tagSize() <= 0)
	  d->tag.set(ID3v2Index, 0);
	else
	  d->hasID3v2 = true;
  }

  // Look for an ID3v1 tag

  d->ID3v1Location = findID3v1();

  if(d->ID3v1Location >= 0) {
	d->tag.set(ID3v1Index, new ID3v1::Tag(this, d->ID3v1Location));
	d->hasID3v1 = true;
  }

  // Look for an APE tag

  findAPE();

  if(d->APELocation >= 0) {

	d->tag.set(APEIndex, new APE::Tag(this, d->APEFooterLocation));
	d->APEOriginalSize = APETag()->footer()->completeTagSize();
	d->hasAPE = true;
  }

  if(readProperties)
	d->properties = new Properties(this, propertiesStyle);

  // Make sure that we have our default tag types available.

  ID3v2Tag(true);
  ID3v1Tag(true);
}

long MPEG::File::findID3v2()
{
  // This method is based on the contents of TagLib::File::find(), but because
  // of some subtlteies -- specifically the need to look for the bit pattern of
  // an MPEG sync, it has been modified for use here.

  if(isValid() && ID3v2::Header::fileIdentifier().size() <= bufferSize()) {

	// The position in the file that the current buffer starts at.

	long bufferOffset = 0;
	ByteVector buffer;

	// These variables are used to keep track of a partial match that happens at
	// the end of a buffer.

	int previousPartialMatch = -1;
	bool previousPartialSynchMatch = false;

	// Save the location of the current read pointer.  We will restore the
	// position using seek() before all returns.

	long originalPosition = tell();

	// Start the search at the beginning of the file.

	seek(0);

	// This loop is the crux of the find method.  There are three cases that we
	// want to account for:
	// (1) The previously searched buffer contained a partial match of the search
	// pattern and we want to see if the next one starts with the remainder of
	// that pattern.
	//
	// (2) The search pattern is wholly contained within the current buffer.
	//
	// (3) The current buffer ends with a partial match of the pattern.  We will
	// note this for use in the next itteration, where we will check for the rest
	// of the pattern.

	for(buffer = readBlock(bufferSize()); buffer.size() > 0; buffer = readBlock(bufferSize())) {

	  // (1) previous partial match

	  if(previousPartialSynchMatch && secondSynchByte(buffer[0]))
		return -1;

	  if(previousPartialMatch >= 0 && int(bufferSize()) > previousPartialMatch) {
		const int patternOffset = (bufferSize() - previousPartialMatch);
		if(buffer.containsAt(ID3v2::Header::fileIdentifier(), 0, patternOffset)) {
		  seek(originalPosition);
		  return bufferOffset - bufferSize() + previousPartialMatch;
		}
	  }

	  // (2) pattern contained in current buffer

	  long location = buffer.find(ID3v2::Header::fileIdentifier());
	  if(location >= 0) {
		seek(originalPosition);
		return bufferOffset + location;
	  }

	  int firstSynchByte = buffer.find(char(uchar(255)));

	  // Here we have to loop because there could be several of the first
	  // (11111111) byte, and we want to check all such instances until we find
	  // a full match (11111111 111) or hit the end of the buffer.

	  while(firstSynchByte >= 0) {

		// if this *is not* at the end of the buffer

		if(firstSynchByte < int(buffer.size()) - 1) {
		  if(secondSynchByte(buffer[firstSynchByte + 1])) {
			// We've found the frame synch pattern.
			seek(originalPosition);
			return -1;
		  }
		  else {

			// We found 11111111 at the end of the current buffer indicating a
			// partial match of the synch pattern.  The find() below should
			// return -1 and break out of the loop.

			previousPartialSynchMatch = true;
		  }
		}

		// Check in the rest of the buffer.

		firstSynchByte = buffer.find(char(uchar(255)), firstSynchByte + 1);
	  }

	  // (3) partial match

	  previousPartialMatch = buffer.endsWithPartialMatch(ID3v2::Header::fileIdentifier());

	  bufferOffset += bufferSize();
	}

	// Since we hit the end of the file, reset the status before continuing.

	clear();

	seek(originalPosition);
  }

  return -1;
}

long MPEG::File::findID3v1()
{
  if(isValid()) {
	seek(-128, End);
	long p = tell();

	if(readBlock(3) == ID3v1::Tag::fileIdentifier())
	  return p;
  }
  return -1;
}

void MPEG::File::findAPE()
{
  if(isValid()) {
	seek(d->hasID3v1 ? -160 : -32, End);

	long p = tell();

	if(readBlock(8) == APE::Tag::fileIdentifier()) {
	  d->APEFooterLocation = p;
	  seek(d->APEFooterLocation);
	  APE::Footer footer(readBlock(APE::Footer::size()));
	  d->APELocation = d->APEFooterLocation - footer.completeTagSize()
					   + APE::Footer::size();
	  return;
	}
  }

  d->APELocation = -1;
  d->APEFooterLocation = -1;
}

bool MPEG::File::secondSynchByte(char byte)
{
  if(uchar(byte) == 0xff)
	return false;

  std::bitset<8> b(byte);

  // check to see if the byte matches 111xxxxx
  return b.test(7) && b.test(6) && b.test(5);
}

/*** End of inlined file: mpegfile.cpp ***/


/*** Start of inlined file: mpegproperties.cpp ***/
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

using namespace TagLib;

class MPEG::Properties::PropertiesPrivate
{
public:
  PropertiesPrivate(File *f, ReadStyle s) :
	file(f),
	xingHeader(0),
	style(s),
	length(0),
	bitrate(0),
	sampleRate(0),
	channels(0),
	layer(0),
	version(Header::Version1),
	channelMode(Header::Stereo),
	protectionEnabled(false),
	isCopyrighted(false),
	isOriginal(false) {}

  ~PropertiesPrivate()
  {
	delete xingHeader;
  }

  File *file;
  XingHeader *xingHeader;
  ReadStyle style;
  int length;
  int bitrate;
  int sampleRate;
  int channels;
  int layer;
  Header::Version version;
  Header::ChannelMode channelMode;
  bool protectionEnabled;
  bool isCopyrighted;
  bool isOriginal;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

MPEG::Properties::Properties(File *file, ReadStyle style) : AudioProperties(style)
{
  d = new PropertiesPrivate(file, style);

  if(file && file->isOpen())
	read();
}

MPEG::Properties::~Properties()
{
  delete d;
}

int MPEG::Properties::length() const
{
  return d->length;
}

int MPEG::Properties::bitrate() const
{
  return d->bitrate;
}

int MPEG::Properties::sampleRate() const
{
  return d->sampleRate;
}

int MPEG::Properties::channels() const
{
  return d->channels;
}

const MPEG::XingHeader *MPEG::Properties::xingHeader() const
{
  return d->xingHeader;
}

MPEG::Header::Version MPEG::Properties::version() const
{
  return d->version;
}

int MPEG::Properties::layer() const
{
  return d->layer;
}

bool MPEG::Properties::protectionEnabled() const
{
  return d->protectionEnabled;
}

MPEG::Header::ChannelMode MPEG::Properties::channelMode() const
{
  return d->channelMode;
}

bool MPEG::Properties::isCopyrighted() const
{
  return d->isCopyrighted;
}

bool MPEG::Properties::isOriginal() const
{
  return d->isOriginal;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void MPEG::Properties::read()
{
  // Since we've likely just looked for the ID3v1 tag, start at the end of the
  // file where we're least likely to have to have to move the disk head.

  long last = d->file->lastFrameOffset();

  if(last < 0) {
	debug("MPEG::Properties::read() -- Could not find a valid last MPEG frame in the stream.");
	return;
  }

  d->file->seek(last);
  Header lastHeader(d->file->readBlock(4));

  long first = d->file->firstFrameOffset();

  if(first < 0) {
	debug("MPEG::Properties::read() -- Could not find a valid first MPEG frame in the stream.");
	return;
  }

  if(!lastHeader.isValid()) {

	long pos = last;

	while(pos > first) {

	  pos = d->file->previousFrameOffset(pos);

	  if(pos < 0)
		break;

	  d->file->seek(pos);
	  Header header(d->file->readBlock(4));

	  if(header.isValid()) {
		lastHeader = header;
		last = pos;
		break;
	  }
	}
  }

  // Now jump back to the front of the file and read what we need from there.

  d->file->seek(first);
  Header firstHeader(d->file->readBlock(4));

  if(!firstHeader.isValid() || !lastHeader.isValid()) {
	debug("MPEG::Properties::read() -- Page headers were invalid.");
	return;
  }

  // Check for a Xing header that will help us in gathering information about a
  // VBR stream.

  int xingHeaderOffset = MPEG::XingHeader::xingHeaderOffset(firstHeader.version(),
															firstHeader.channelMode());

  d->file->seek(first + xingHeaderOffset);
  d->xingHeader = new XingHeader(d->file->readBlock(16));

  // Read the length and the bitrate from the Xing header.

  if(d->xingHeader->isValid() &&
	 firstHeader.sampleRate() > 0 &&
	 d->xingHeader->totalFrames() > 0)
  {
	  double timePerFrame =
		double(firstHeader.samplesPerFrame()) / firstHeader.sampleRate();

	  double length = timePerFrame * d->xingHeader->totalFrames();

	  d->length = int(length);
	  d->bitrate = d->length > 0 ? static_cast<int>(d->xingHeader->totalSize() * 8 / length / 1000) : 0;
  }
  else {
	// Since there was no valid Xing header found, we hope that we're in a constant
	// bitrate file.

	delete d->xingHeader;
	d->xingHeader = 0;

	// TODO: Make this more robust with audio property detection for VBR without a
	// Xing header.

	if(firstHeader.frameLength() > 0 && firstHeader.bitrate() > 0) {
	  int frames = (last - first) / firstHeader.frameLength() + 1;

	  d->length = int(float(firstHeader.frameLength() * frames) /
					  float(firstHeader.bitrate() * 125) + 0.5);
	  d->bitrate = firstHeader.bitrate();
	}
  }

  d->sampleRate = firstHeader.sampleRate();
  d->channels = firstHeader.channelMode() == Header::SingleChannel ? 1 : 2;
  d->version = firstHeader.version();
  d->layer = firstHeader.layer();
  d->protectionEnabled = firstHeader.protectionEnabled();
  d->channelMode = firstHeader.channelMode();
  d->isCopyrighted = firstHeader.isCopyrighted();
  d->isOriginal = firstHeader.isOriginal();
}

/*** End of inlined file: mpegproperties.cpp ***/


/*** Start of inlined file: mpegheader.cpp ***/
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

#include <bitset>

using namespace TagLib;

class MPEG::Header::HeaderPrivate : public RefCounter
{
public:
  HeaderPrivate() :
	isValid(false),
	version(Version1),
	layer(0),
	protectionEnabled(false),
	sampleRate(0),
	isPadded(false),
	channelMode(Stereo),
	isCopyrighted(false),
	isOriginal(false),
	frameLength(0),
	samplesPerFrame(0) {}

  bool isValid;
  Version version;
  int layer;
  bool protectionEnabled;
  int bitrate;
  int sampleRate;
  bool isPadded;
  ChannelMode channelMode;
  bool isCopyrighted;
  bool isOriginal;
  int frameLength;
  int samplesPerFrame;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

MPEG::Header::Header(const ByteVector &data)
{
  d = new HeaderPrivate;
  parse(data);
}

MPEG::Header::Header(const Header &h) : d(h.d)
{
  d->ref();
}

MPEG::Header::~Header()
{
  if (d->deref())
	delete d;
}

bool MPEG::Header::isValid() const
{
  return d->isValid;
}

MPEG::Header::Version MPEG::Header::version() const
{
  return d->version;
}

int MPEG::Header::layer() const
{
  return d->layer;
}

bool MPEG::Header::protectionEnabled() const
{
  return d->protectionEnabled;
}

int MPEG::Header::bitrate() const
{
  return d->bitrate;
}

int MPEG::Header::sampleRate() const
{
  return d->sampleRate;
}

bool MPEG::Header::isPadded() const
{
  return d->isPadded;
}

MPEG::Header::ChannelMode MPEG::Header::channelMode() const
{
  return d->channelMode;
}

bool MPEG::Header::isCopyrighted() const
{
  return d->isCopyrighted;
}

bool MPEG::Header::isOriginal() const
{
  return d->isOriginal;
}

int MPEG::Header::frameLength() const
{
  return d->frameLength;
}

int MPEG::Header::samplesPerFrame() const
{
  return d->samplesPerFrame;
}

MPEG::Header &MPEG::Header::operator=(const Header &h)
{
  if(&h == this)
	return *this;

  if(d->deref())
	delete d;

  d = h.d;
  d->ref();
  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void MPEG::Header::parse(const ByteVector &data)
{
  if(data.size() < 4 || uchar(data[0]) != 0xff) {
	debug("MPEG::Header::parse() -- First byte did not match MPEG synch.");
	return;
  }

  std::bitset<32> flags(TAGLIB_CONSTRUCT_BITSET(data.toUInt()));

  // Check for the second byte's part of the MPEG synch

  if(!flags[23] || !flags[22] || !flags[21]) {
	debug("MPEG::Header::parse() -- Second byte did not match MPEG synch.");
	return;
  }

  // Set the MPEG version

  if(!flags[20] && !flags[19])
	d->version = Version2_5;
  else if(flags[20] && !flags[19])
	d->version = Version2;
  else if(flags[20] && flags[19])
	d->version = Version1;

  // Set the MPEG layer

  if(!flags[18] && flags[17])
	d->layer = 3;
  else if(flags[18] && !flags[17])
	d->layer = 2;
  else if(flags[18] && flags[17])
	d->layer = 1;

  d->protectionEnabled = !flags[16];

  // Set the bitrate

  static const int bitrates[2][3][16] = {
	{ // Version 1
	  { 0, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 0 }, // layer 1
	  { 0, 32, 48, 56, 64,  80,  96,  112, 128, 160, 192, 224, 256, 320, 384, 0 }, // layer 2
	  { 0, 32, 40, 48, 56,  64,  80,  96,  112, 128, 160, 192, 224, 256, 320, 0 }  // layer 3
	},
	{ // Version 2 or 2.5
	  { 0, 32, 48, 56, 64, 80, 96, 112, 128, 144, 160, 176, 192, 224, 256, 0 }, // layer 1
	  { 0, 8,  16, 24, 32, 40, 48, 56,  64,  80,  96,  112, 128, 144, 160, 0 }, // layer 2
	  { 0, 8,  16, 24, 32, 40, 48, 56,  64,  80,  96,  112, 128, 144, 160, 0 }  // layer 3
	}
  };

  const int versionIndex = d->version == Version1 ? 0 : 1;
  const int layerIndex = d->layer > 0 ? d->layer - 1 : 0;

  // The bitrate index is encoded as the first 4 bits of the 3rd byte,
  // i.e. 1111xxxx

  int i = uchar(data[2]) >> 4;

  d->bitrate = bitrates[versionIndex][layerIndex][i];

  // Set the sample rate

  static const int sampleRates[3][4] = {
	{ 44100, 48000, 32000, 0 }, // Version 1
	{ 22050, 24000, 16000, 0 }, // Version 2
	{ 11025, 12000, 8000,  0 }  // Version 2.5
  };

  // The sample rate index is encoded as two bits in the 3nd byte, i.e. xxxx11xx

  i = uchar(data[2]) >> 2 & 0x03;

  d->sampleRate = sampleRates[d->version][i];

  if(d->sampleRate == 0) {
	debug("MPEG::Header::parse() -- Invalid sample rate.");
	return;
  }

  // The channel mode is encoded as a 2 bit value at the end of the 3nd byte,
  // i.e. xxxxxx11

  d->channelMode = ChannelMode((uchar(data[3]) & 0xC0) >> 6);

  // TODO: Add mode extension for completeness

  d->isOriginal = flags[2];
  d->isCopyrighted = flags[3];
  d->isPadded = flags[9];

  // Calculate the frame length

  if(d->layer == 1)
	d->frameLength = 24000 * 2 * d->bitrate / d->sampleRate + int(d->isPadded);
  else
	d->frameLength = 72000 * d->bitrate / d->sampleRate + int(d->isPadded);

  // Samples per frame

  static const int samplesPerFrame[3][2] = {
	// MPEG1, 2/2.5
	{  384,   384 }, // Layer I
	{ 1152,  1152 }, // Layer II
	{ 1152,   576 }  // Layer III
  };

  d->samplesPerFrame = samplesPerFrame[layerIndex][versionIndex];

  // Now that we're done parsing, set this to be a valid frame.

  d->isValid = true;
}

/*** End of inlined file: mpegheader.cpp ***/


/*** Start of inlined file: xingheader.cpp ***/
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

using namespace TagLib;

class MPEG::XingHeader::XingHeaderPrivate
{
public:
  XingHeaderPrivate() :
	frames(0),
	size(0),
	valid(false)
	{}

  uint frames;
  uint size;
  bool valid;
};

MPEG::XingHeader::XingHeader(const ByteVector &data)
{
  d = new XingHeaderPrivate;
  parse(data);
}

MPEG::XingHeader::~XingHeader()
{
  delete d;
}

bool MPEG::XingHeader::isValid() const
{
  return d->valid;
}

TagLib::uint MPEG::XingHeader::totalFrames() const
{
  return d->frames;
}

TagLib::uint MPEG::XingHeader::totalSize() const
{
  return d->size;
}

int MPEG::XingHeader::xingHeaderOffset(TagLib::MPEG::Header::Version v,
									   TagLib::MPEG::Header::ChannelMode c)
{
  if(v == MPEG::Header::Version1) {
	if(c == MPEG::Header::SingleChannel)
	  return 0x15;
	else
	  return 0x24;
  }
  else {
	if(c == MPEG::Header::SingleChannel)
	  return 0x0D;
	else
	  return 0x15;
  }
}

void MPEG::XingHeader::parse(const ByteVector &data)
{
  // Check to see if a valid Xing header is available.

  if(!data.startsWith("Xing") && !data.startsWith("Info"))
	return;

  // If the XingHeader doesn't contain the number of frames and the total stream
  // info it's invalid.

  if(!(data[7] & 0x01)) {
	debug("MPEG::XingHeader::parse() -- Xing header doesn't contain the total number of frames.");
	return;
  }

  if(!(data[7] & 0x02)) {
	debug("MPEG::XingHeader::parse() -- Xing header doesn't contain the total stream size.");
	return;
  }

  d->frames = data.mid(8, 4).toUInt();
  d->size = data.mid(12, 4).toUInt();

  d->valid = true;
}

/*** End of inlined file: xingheader.cpp ***/


/*** Start of inlined file: id3v1tag.cpp ***/
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

using namespace TagLib;
using namespace ID3v1;

class ID3v1::Tag::TagPrivate
{
public:
  TagPrivate() : file(0), tagOffset(-1), track(0), genre(255) {}

  File *file;
  long tagOffset;

  String title;
  String artist;
  String album;
  String year;
  String comment;
  uchar track;
  uchar genre;

  static const StringHandler *stringHandler;
};

static const StringHandler defaultStringHandler;
const ID3v1::StringHandler *ID3v1::Tag::TagPrivate::stringHandler = &defaultStringHandler;

////////////////////////////////////////////////////////////////////////////////
// StringHandler implementation
////////////////////////////////////////////////////////////////////////////////

StringHandler::StringHandler()
{
}

String ID3v1::StringHandler::parse(const ByteVector &data) const
{
  return String(data, String::Latin1).stripWhiteSpace();
}

ByteVector ID3v1::StringHandler::render(const String &s) const
{
  if(!s.isLatin1())
  {
	return ByteVector();
  }

  return s.data(String::Latin1);
}

////////////////////////////////////////////////////////////////////////////////
// public methods
////////////////////////////////////////////////////////////////////////////////

ID3v1::Tag::Tag() : TagLib::Tag()
{
  d = new TagPrivate;
}

ID3v1::Tag::Tag(File *file, long tagOffset) : TagLib::Tag()
{
  d = new TagPrivate;
  d->file = file;
  d->tagOffset = tagOffset;

  read();
}

ID3v1::Tag::~Tag()
{
  delete d;
}

ByteVector ID3v1::Tag::render() const
{
  ByteVector data;

  data.append(fileIdentifier());
  data.append(TagPrivate::stringHandler->render(d->title).resize(30));
  data.append(TagPrivate::stringHandler->render(d->artist).resize(30));
  data.append(TagPrivate::stringHandler->render(d->album).resize(30));
  data.append(TagPrivate::stringHandler->render(d->year).resize(4));
  data.append(TagPrivate::stringHandler->render(d->comment).resize(28));
  data.append(char(0));
  data.append(char(d->track));
  data.append(char(d->genre));

  return data;
}

ByteVector ID3v1::Tag::fileIdentifier()
{
  return ByteVector::fromCString("TAG");
}

String ID3v1::Tag::title() const
{
  return d->title;
}

String ID3v1::Tag::artist() const
{
  return d->artist;
}

String ID3v1::Tag::album() const
{
  return d->album;
}

String ID3v1::Tag::comment() const
{
  return d->comment;
}

String ID3v1::Tag::genre() const
{
  return ID3v1::genre(d->genre);
}

TagLib::uint ID3v1::Tag::year() const
{
  return d->year.toInt();
}

TagLib::uint ID3v1::Tag::track() const
{
  return d->track;
}

void ID3v1::Tag::setTitle(const String &s)
{
  d->title = s;
}

void ID3v1::Tag::setArtist(const String &s)
{
  d->artist = s;
}

void ID3v1::Tag::setAlbum(const String &s)
{
  d->album = s;
}

void ID3v1::Tag::setComment(const String &s)
{
  d->comment = s;
}

void ID3v1::Tag::setGenre(const String &s)
{
  d->genre = static_cast<uchar>(ID3v1::genreIndex(s));
}

void ID3v1::Tag::setYear(uint i)
{
  d->year = i > 0 ? String::number(i) : String::null;
}

void ID3v1::Tag::setTrack(uint i)
{
  d->track = i < 256 ? static_cast<uchar>(i) : 0;
}

void ID3v1::Tag::setStringHandler(const StringHandler *handler)
{
  if(TagPrivate::stringHandler != &defaultStringHandler)
	delete TagPrivate::stringHandler;

  TagPrivate::stringHandler = handler;
}

////////////////////////////////////////////////////////////////////////////////
// protected methods
////////////////////////////////////////////////////////////////////////////////

void ID3v1::Tag::read()
{
  if(d->file && d->file->isValid()) {
	d->file->seek(d->tagOffset);
	// read the tag -- always 128 bytes
	ByteVector data = d->file->readBlock(128);

	// some initial sanity checking
	if(data.size() == 128 && data.startsWith("TAG"))
	  parse(data);
	else
	  debug("ID3v1 tag is not valid or could not be read at the specified offset.");
  }
}

void ID3v1::Tag::parse(const ByteVector &data)
{
  int offset = 3;

  d->title = TagPrivate::stringHandler->parse(data.mid(offset, 30));
  offset += 30;

  d->artist = TagPrivate::stringHandler->parse(data.mid(offset, 30));
  offset += 30;

  d->album = TagPrivate::stringHandler->parse(data.mid(offset, 30));
  offset += 30;

  d->year = TagPrivate::stringHandler->parse(data.mid(offset, 4));
  offset += 4;

  // Check for ID3v1.1 -- Note that ID3v1 *does not* support "track zero" -- this
  // is not a bug in TagLib.  Since a zeroed byte is what we would expect to
  // indicate the end of a C-String, specifically the comment string, a value of
  // zero must be assumed to be just that.

  if(data[offset + 28] == 0 && data[offset + 29] != 0) {
	// ID3v1.1 detected

	d->comment = TagPrivate::stringHandler->parse(data.mid(offset, 28));
	d->track = uchar(data[offset + 29]);
  }
  else
	d->comment = data.mid(offset, 30);

  offset += 30;

  d->genre = uchar(data[offset]);
}

/*** End of inlined file: id3v1tag.cpp ***/


/*** Start of inlined file: id3v1genres.cpp ***/
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

using namespace TagLib;

namespace TagLib {
  namespace ID3v1 {

	static const int genresSize = 148;
	static const String genres[] = {
	  "Blues",
	  "Classic Rock",
	  "Country",
	  "Dance",
	  "Disco",
	  "Funk",
	  "Grunge",
	  "Hip-Hop",
	  "Jazz",
	  "Metal",
	  "New Age",
	  "Oldies",
	  "Other",
	  "Pop",
	  "R&B",
	  "Rap",
	  "Reggae",
	  "Rock",
	  "Techno",
	  "Industrial",
	  "Alternative",
	  "Ska",
	  "Death Metal",
	  "Pranks",
	  "Soundtrack",
	  "Euro-Techno",
	  "Ambient",
	  "Trip-Hop",
	  "Vocal",
	  "Jazz+Funk",
	  "Fusion",
	  "Trance",
	  "Classical",
	  "Instrumental",
	  "Acid",
	  "House",
	  "Game",
	  "Sound Clip",
	  "Gospel",
	  "Noise",
	  "Alternative Rock",
	  "Bass",
	  "Soul",
	  "Punk",
	  "Space",
	  "Meditative",
	  "Instrumental Pop",
	  "Instrumental Rock",
	  "Ethnic",
	  "Gothic",
	  "Darkwave",
	  "Techno-Industrial",
	  "Electronic",
	  "Pop-Folk",
	  "Eurodance",
	  "Dream",
	  "Southern Rock",
	  "Comedy",
	  "Cult",
	  "Gangsta",
	  "Top 40",
	  "Christian Rap",
	  "Pop/Funk",
	  "Jungle",
	  "Native American",
	  "Cabaret",
	  "New Wave",
	  "Psychedelic",
	  "Rave",
	  "Showtunes",
	  "Trailer",
	  "Lo-Fi",
	  "Tribal",
	  "Acid Punk",
	  "Acid Jazz",
	  "Polka",
	  "Retro",
	  "Musical",
	  "Rock & Roll",
	  "Hard Rock",
	  "Folk",
	  "Folk/Rock",
	  "National Folk",
	  "Swing",
	  "Fusion",
	  "Bebob",
	  "Latin",
	  "Revival",
	  "Celtic",
	  "Bluegrass",
	  "Avantgarde",
	  "Gothic Rock",
	  "Progressive Rock",
	  "Psychedelic Rock",
	  "Symphonic Rock",
	  "Slow Rock",
	  "Big Band",
	  "Chorus",
	  "Easy Listening",
	  "Acoustic",
	  "Humour",
	  "Speech",
	  "Chanson",
	  "Opera",
	  "Chamber Music",
	  "Sonata",
	  "Symphony",
	  "Booty Bass",
	  "Primus",
	  "Porn Groove",
	  "Satire",
	  "Slow Jam",
	  "Club",
	  "Tango",
	  "Samba",
	  "Folklore",
	  "Ballad",
	  "Power Ballad",
	  "Rhythmic Soul",
	  "Freestyle",
	  "Duet",
	  "Punk Rock",
	  "Drum Solo",
	  "A Cappella",
	  "Euro-House",
	  "Dance Hall",
	  "Goa",
	  "Drum & Bass",
	  "Club-House",
	  "Hardcore",
	  "Terror",
	  "Indie",
	  "BritPop",
	  "Negerpunk",
	  "Polsk Punk",
	  "Beat",
	  "Christian Gangsta Rap",
	  "Heavy Metal",
	  "Black Metal",
	  "Crossover",
	  "Contemporary Christian",
	  "Christian Rock",
	  "Merengue",
	  "Salsa",
	  "Thrash Metal",
	  "Anime",
	  "Jpop",
	  "Synthpop"
	};
  }
}

StringList ID3v1::genreList()
{
  static StringList l;
  if(l.isEmpty()) {
	for(int i = 0; i < genresSize; i++)
	  l.append(genres[i]);
  }
  return l;
}

ID3v1::GenreMap ID3v1::genreMap()
{
  static GenreMap m;
  if(m.isEmpty()) {
	for(int i = 0; i < genresSize; i++)
	  m.insert(genres[i], i);
  }
  return m;
}

String ID3v1::genre(int i)
{
  if(i >= 0 && i < genresSize)
	return genres[i] + String::null; // always make a copy
  return String::null;
}

int ID3v1::genreIndex(const String &name)
{
  if(genreMap().contains(name))
	return genreMap()[name];
  return 255;
}

/*** End of inlined file: id3v1genres.cpp ***/


/*** Start of inlined file: id3v2framefactory.cpp ***/
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace TagLib;
using namespace ID3v2;

class FrameFactory::FrameFactoryPrivate
{
public:
  FrameFactoryPrivate() :
	defaultEncoding(String::Latin1),
	useDefaultEncoding(false) {}

  String::Type defaultEncoding;
  bool useDefaultEncoding;

  template <class T> void setTextEncoding(T *frame)
  {
	if(useDefaultEncoding)
	  frame->setTextEncoding(defaultEncoding);
  }
};

FrameFactory FrameFactory::factory;

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

FrameFactory *FrameFactory::instance()
{
  return &factory;
}

Frame *FrameFactory::createFrame(const ByteVector &data, bool synchSafeInts) const
{
  return createFrame(data, uint(synchSafeInts ? 4 : 3));
}

Frame *FrameFactory::createFrame(const ByteVector &data, uint version) const
{
  Header tagHeader;
  tagHeader.setMajorVersion(version);
  return createFrame(data, &tagHeader);
}

Frame *FrameFactory::createFrame(const ByteVector &origData, Header *tagHeader) const
{
  ByteVector data = origData;
  uint version = tagHeader->majorVersion();
  Frame::Header *header = new Frame::Header(data, version);
  ByteVector frameID = header->frameID();

  // A quick sanity check -- make sure that the frameID is 4 uppercase Latin1
  // characters.  Also make sure that there is data in the frame.

  if(!frameID.size() == (version < 3 ? 3 : 4) ||
	 header->frameSize() <= uint(header->dataLengthIndicator() ? 4 : 0) ||
	 header->frameSize() > data.size())
  {
	delete header;
	return 0;
  }

  for(ByteVector::ConstIterator it = frameID.begin(); it != frameID.end(); it++) {
	if( (*it < 'A' || *it > 'Z') && (*it < '1' || *it > '9') ) {
	  delete header;
	  return 0;
	}
  }

  if(version > 3 && (tagHeader->unsynchronisation() || header->unsynchronisation())) {
	// Data lengths are not part of the encoded data, but since they are synch-safe
	// integers they will be never actually encoded.
	ByteVector frameData = data.mid(Frame::Header::size(version), header->frameSize());
	frameData = SynchData::decode(frameData);
	data = data.mid(0, Frame::Header::size(version)) + frameData;
  }

  // TagLib doesn't mess with encrypted frames, so just treat them
  // as unknown frames.

#if HAVE_ZLIB == 0
  if(header->compression()) {
	debug("Compressed frames are currently not supported.");
	return new UnknownFrame(data, header);
  }
#endif
  if(header->encryption()) {
	debug("Encrypted frames are currently not supported.");
	return new UnknownFrame(data, header);
  }

  if(!updateFrame(header)) {
	header->setTagAlterPreservation(true);
	return new UnknownFrame(data, header);
  }

  // updateFrame() might have updated the frame ID.

  frameID = header->frameID();

  // This is where things get necissarily nasty.  Here we determine which
  // Frame subclass (or if none is found simply an Frame) based
  // on the frame ID.  Since there are a lot of possibilities, that means
  // a lot of if blocks.

  // Text Identification (frames 4.2)

  if(frameID.startsWith("T")) {

	TextIdentificationFrame *f = frameID != "TXXX"
	  ? new TextIdentificationFrame(data, header)
	  : new UserTextIdentificationFrame(data, header);

	d->setTextEncoding(f);

	if(frameID == "TCON")
	  updateGenre(f);

	return f;
  }

  // Comments (frames 4.10)

  if(frameID == "COMM") {
	CommentsFrame *f = new CommentsFrame(data, header);
	d->setTextEncoding(f);
	return f;
  }

  // Attached Picture (frames 4.14)

  if(frameID == "APIC") {
	AttachedPictureFrame *f = new AttachedPictureFrame(data, header);
	d->setTextEncoding(f);
	return f;
  }

  // ID3v2.2 Attached Picture

  if(frameID == "PIC") {
	AttachedPictureFrame *f = new AttachedPictureFrameV22(data, header);
	d->setTextEncoding(f);
	return f;
  }

  // Relative Volume Adjustment (frames 4.11)

  if(frameID == "RVA2")
	return new RelativeVolumeFrame(data, header);

  // Unique File Identifier (frames 4.1)

  if(frameID == "UFID")
	return new UniqueFileIdentifierFrame(data, header);

  // General Encapsulated Object (frames 4.15)

  if(frameID == "GEOB") {
	GeneralEncapsulatedObjectFrame *f = new GeneralEncapsulatedObjectFrame(data, header);
	d->setTextEncoding(f);
	return f;
  }

  // URL link (frames 4.3)

  if(frameID.startsWith("W")) {
	if(frameID != "WXXX") {
	  return new UrlLinkFrame(data, header);
	}
	else {
	  UserUrlLinkFrame *f = new UserUrlLinkFrame(data, header);
	  d->setTextEncoding(f);
	  return f;
	}
  }

  // Unsynchronized lyric/text transcription (frames 4.8)

  if(frameID == "USLT") {
	UnsynchronizedLyricsFrame *f = new UnsynchronizedLyricsFrame(data, header);
	if(d->useDefaultEncoding)
	  f->setTextEncoding(d->defaultEncoding);
	return f;
  }

  // Popularimeter (frames 4.17)

  if(frameID == "POPM")
	return new PopularimeterFrame(data, header);

  // Private (frames 4.27)

  if(frameID == "PRIV")
	return new PrivateFrame(data, header);

  return new UnknownFrame(data, header);
}

String::Type FrameFactory::defaultTextEncoding() const
{
  return d->defaultEncoding;
}

void FrameFactory::setDefaultTextEncoding(String::Type encoding)
{
  d->useDefaultEncoding = true;
  d->defaultEncoding = encoding;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

FrameFactory::FrameFactory()
{
  d = new FrameFactoryPrivate;
}

FrameFactory::~FrameFactory()
{
  delete d;
}

bool FrameFactory::updateFrame(Frame::Header *header) const
{
  TagLib::ByteVector frameID = header->frameID();

  switch(header->version()) {

  case 2: // ID3v2.2
  {
	if(frameID == "CRM" ||
	   frameID == "EQU" ||
	   frameID == "LNK" ||
	   frameID == "RVA" ||
	   frameID == "TIM" ||
	   frameID == "TSI" ||
	   frameID == "TDA")
	{
	  debug("ID3v2.4 no longer supports the frame type " + String(frameID) +
			".  It will be discarded from the tag.");
	  return false;
	}

	// ID3v2.2 only used 3 bytes for the frame ID, so we need to convert all of
	// the frames to their 4 byte ID3v2.4 equivalent.

	convertFrame("BUF", "RBUF", header);
	convertFrame("CNT", "PCNT", header);
	convertFrame("COM", "COMM", header);
	convertFrame("CRA", "AENC", header);
	convertFrame("ETC", "ETCO", header);
	convertFrame("GEO", "GEOB", header);
	convertFrame("IPL", "TIPL", header);
	convertFrame("MCI", "MCDI", header);
	convertFrame("MLL", "MLLT", header);
	convertFrame("POP", "POPM", header);
	convertFrame("REV", "RVRB", header);
	convertFrame("SLT", "SYLT", header);
	convertFrame("STC", "SYTC", header);
	convertFrame("TAL", "TALB", header);
	convertFrame("TBP", "TBPM", header);
	convertFrame("TCM", "TCOM", header);
	convertFrame("TCO", "TCON", header);
	convertFrame("TCP", "TCMP", header);
	convertFrame("TCR", "TCOP", header);
	convertFrame("TDY", "TDLY", header);
	convertFrame("TEN", "TENC", header);
	convertFrame("TFT", "TFLT", header);
	convertFrame("TKE", "TKEY", header);
	convertFrame("TLA", "TLAN", header);
	convertFrame("TLE", "TLEN", header);
	convertFrame("TMT", "TMED", header);
	convertFrame("TOA", "TOAL", header);
	convertFrame("TOF", "TOFN", header);
	convertFrame("TOL", "TOLY", header);
	convertFrame("TOR", "TDOR", header);
	convertFrame("TOT", "TOAL", header);
	convertFrame("TP1", "TPE1", header);
	convertFrame("TP2", "TPE2", header);
	convertFrame("TP3", "TPE3", header);
	convertFrame("TP4", "TPE4", header);
	convertFrame("TPA", "TPOS", header);
	convertFrame("TPB", "TPUB", header);
	convertFrame("TRC", "TSRC", header);
	convertFrame("TRD", "TDRC", header);
	convertFrame("TRK", "TRCK", header);
	convertFrame("TS2", "TSO2", header);
	convertFrame("TSA", "TSOA", header);
	convertFrame("TSC", "TSOC", header);
	convertFrame("TSP", "TSOP", header);
	convertFrame("TSS", "TSSE", header);
	convertFrame("TST", "TSOT", header);
	convertFrame("TT1", "TIT1", header);
	convertFrame("TT2", "TIT2", header);
	convertFrame("TT3", "TIT3", header);
	convertFrame("TXT", "TOLY", header);
	convertFrame("TXX", "TXXX", header);
	convertFrame("TYE", "TDRC", header);
	convertFrame("UFI", "UFID", header);
	convertFrame("ULT", "USLT", header);
	convertFrame("WAF", "WOAF", header);
	convertFrame("WAR", "WOAR", header);
	convertFrame("WAS", "WOAS", header);
	convertFrame("WCM", "WCOM", header);
	convertFrame("WCP", "WCOP", header);
	convertFrame("WPB", "WPUB", header);
	convertFrame("WXX", "WXXX", header);

	break;
  }

  case 3: // ID3v2.3
  {
	if(frameID == "EQUA" ||
	   frameID == "RVAD" ||
	   frameID == "TIME" ||
	   frameID == "TRDA" ||
	   frameID == "TSIZ" ||
	   frameID == "TDAT")
	{
	  debug("ID3v2.4 no longer supports the frame type " + String(frameID) +
			".  It will be discarded from the tag.");
	  return false;
	}

	convertFrame("TORY", "TDOR", header);
	convertFrame("TYER", "TDRC", header);
	convertFrame("IPLS", "TIPL", header);

	break;
  }

  default:

	// This should catch a typo that existed in TagLib up to and including
	// version 1.1 where TRDC was used for the year rather than TDRC.

	convertFrame("TRDC", "TDRC", header);
	break;
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void FrameFactory::convertFrame(const char *from, const char *to,
								Frame::Header *header) const
{
  if(header->frameID() != from)
	return;

  // debug("ID3v2.4 no longer supports the frame type " + String(from) + "  It has" +
  //       "been converted to the type " + String(to) + ".");

  header->setFrameID(to);
}

void FrameFactory::updateGenre(TextIdentificationFrame *frame) const
{
  StringList fields = frame->fieldList();
  StringList newfields;

  for(StringList::Iterator it = fields.begin(); it != fields.end(); ++it) {
	String s = *it;
	int end = s.find(")");

	if(s.startsWith("(") && end > 0) {
	  // "(12)Genre"
	  String text = s.substr(end + 1);
	  bool ok;
	  int number = s.substr(1, end - 1).toInt(&ok);
	  if(ok && number >= 0 && number <= 255 && !(ID3v1::genre(number) == text))
		newfields.append(s.substr(1, end - 1));
	  if(!text.isEmpty())
		newfields.append(text);
	}
	else {
	  // "Genre" or "12"
	  newfields.append(s);
	}
  }

  if(newfields.isEmpty())
	fields.append(String::null);

  frame->setText(newfields);

}

/*** End of inlined file: id3v2framefactory.cpp ***/


/*** Start of inlined file: id3v2synchdata.cpp ***/
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

#include <iostream>

using namespace TagLib;
using namespace ID3v2;

TagLib::uint SynchData::toUInt(const ByteVector &data)
{
  uint sum = 0;
  bool notSynchSafe = false;
  int last = data.size() > 4 ? 3 : data.size() - 1;

  for(int i = 0; i <= last; i++) {
	if(data[i] & 0x80) {
	  notSynchSafe = true;
	  break;
	}

	sum |= (data[i] & 0x7f) << ((last - i) * 7);
  }

  if(notSynchSafe) {
	// Invalid data; assume this was created by some buggy software that just
	// put normal integers here rather than syncsafe ones, and try it that
	// way.
	sum = (data.size() > 4) ? data.mid(0, 4).toUInt() : data.toUInt();
  }

  return sum;
}

ByteVector SynchData::fromUInt(uint value)
{
  ByteVector v(4, 0);

  for(int i = 0; i < 4; i++)
	v[i] = uchar(value >> ((3 - i) * 7) & 0x7f);

  return v;
}

ByteVector SynchData::decode(const ByteVector &data)
{
  ByteVector result = data;

  ByteVector pattern(2, char(0));
  pattern[0] = '\xFF';
  pattern[1] = '\x00';

  return result.replace(pattern, '\xFF');
}

/*** End of inlined file: id3v2synchdata.cpp ***/


/*** Start of inlined file: id3v2tag.cpp ***/
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

using namespace TagLib;
using namespace ID3v2;

class ID3v2::Tag::TagPrivate
{
public:
  TagPrivate() : file(0), tagOffset(-1), extendedHeader(0), footer(0), paddingSize(0)
  {
	frameList.setAutoDelete(true);
  }
  ~TagPrivate()
  {
	delete extendedHeader;
	delete footer;
  }

  File *file;
  long tagOffset;
  const FrameFactory *factory;

  Header header;
  ExtendedHeader *extendedHeader;
  Footer *footer;

  int paddingSize;

  FrameListMap frameListMap;
  FrameList frameList;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

ID3v2::Tag::Tag() : TagLib::Tag()
{
  d = new TagPrivate;
  d->factory = FrameFactory::instance();
}

ID3v2::Tag::Tag(File *file, long tagOffset, const FrameFactory *factory) :
  TagLib::Tag()
{
  d = new TagPrivate;

  d->file = file;
  d->tagOffset = tagOffset;
  d->factory = factory;

  read();
}

ID3v2::Tag::~Tag()
{
  delete d;
}

String ID3v2::Tag::title() const
{
  if(!d->frameListMap["TIT2"].isEmpty())
	return d->frameListMap["TIT2"].front()->toString();
  return String::null;
}

String ID3v2::Tag::artist() const
{
  if(!d->frameListMap["TPE1"].isEmpty())
	return d->frameListMap["TPE1"].front()->toString();
  return String::null;
}

String ID3v2::Tag::album() const
{
  if(!d->frameListMap["TALB"].isEmpty())
	return d->frameListMap["TALB"].front()->toString();
  return String::null;
}

String ID3v2::Tag::comment() const
{
  const FrameList &comments = d->frameListMap["COMM"];

  if(comments.isEmpty())
	return String::null;

  for(FrameList::ConstIterator it = comments.begin(); it != comments.end(); ++it)
  {
	CommentsFrame *frame = dynamic_cast<CommentsFrame *>(*it);

	if(frame && frame->description().isEmpty())
	  return (*it)->toString();
  }

  return comments.front()->toString();
}

String ID3v2::Tag::genre() const
{
  // TODO: In the next major version (TagLib 2.0) a list of multiple genres
  // should be separated by " / " instead of " ".  For the moment to keep
  // the behavior the same as released versions it is being left with " ".

  if(d->frameListMap["TCON"].isEmpty() ||
	 !dynamic_cast<TextIdentificationFrame *>(d->frameListMap["TCON"].front()))
  {
	return String::null;
  }

  // ID3v2.4 lists genres as the fields in its frames field list.  If the field
  // is simply a number it can be assumed that it is an ID3v1 genre number.
  // Here was assume that if an ID3v1 string is present that it should be
  // appended to the genre string.  Multiple fields will be appended as the
  // string is built.

  TextIdentificationFrame *f = static_cast<TextIdentificationFrame *>(
	d->frameListMap["TCON"].front());

  StringList fields = f->fieldList();

  StringList genres;

  for(StringList::Iterator it = fields.begin(); it != fields.end(); ++it) {

	if((*it).isEmpty())
	  continue;

	bool ok;
	int number = (*it).toInt(&ok);
	if(ok && number >= 0 && number <= 255) {
	  *it = ID3v1::genre(number);
	}

	if(std::find(genres.begin(), genres.end(), *it) == genres.end())
	  genres.append(*it);
  }

  return genres.toString();
}

TagLib::uint ID3v2::Tag::year() const
{
  if(!d->frameListMap["TDRC"].isEmpty())
	return d->frameListMap["TDRC"].front()->toString().substr(0, 4).toInt();
  return 0;
}

TagLib::uint ID3v2::Tag::track() const
{
  if(!d->frameListMap["TRCK"].isEmpty())
	return d->frameListMap["TRCK"].front()->toString().toInt();
  return 0;
}

void ID3v2::Tag::setTitle(const String &s)
{
  setTextFrame("TIT2", s);
}

void ID3v2::Tag::setArtist(const String &s)
{
  setTextFrame("TPE1", s);
}

void ID3v2::Tag::setAlbum(const String &s)
{
  setTextFrame("TALB", s);
}

void ID3v2::Tag::setComment(const String &s)
{
  if(s.isEmpty()) {
	removeFrames("COMM");
	return;
  }

  if(!d->frameListMap["COMM"].isEmpty())
	d->frameListMap["COMM"].front()->setText(s);
  else {
	CommentsFrame *f = new CommentsFrame(d->factory->defaultTextEncoding());
	addFrame(f);
	f->setText(s);
  }
}

void ID3v2::Tag::setGenre(const String &s)
{
  if(s.isEmpty()) {
	removeFrames("TCON");
	return;
  }

  // iTunes can't handle correctly encoded ID3v2.4 numerical genres.  Just use
  // strings until iTunes sucks less.

#ifdef NO_ITUNES_HACKS

  int index = ID3v1::genreIndex(s);

  if(index != 255)
	setTextFrame("TCON", String::number(index));
  else
	setTextFrame("TCON", s);

#else

  setTextFrame("TCON", s);

#endif
}

void ID3v2::Tag::setYear(uint i)
{
  if(i <= 0) {
	removeFrames("TDRC");
	return;
  }
  setTextFrame("TDRC", String::number(i));
}

void ID3v2::Tag::setTrack(uint i)
{
  if(i <= 0) {
	removeFrames("TRCK");
	return;
  }
  setTextFrame("TRCK", String::number(i));
}

bool ID3v2::Tag::isEmpty() const
{
  return d->frameList.isEmpty();
}

Header *ID3v2::Tag::header() const
{
  return &(d->header);
}

ExtendedHeader *ID3v2::Tag::extendedHeader() const
{
  return d->extendedHeader;
}

Footer *ID3v2::Tag::footer() const
{
  return d->footer;
}

const FrameListMap &ID3v2::Tag::frameListMap() const
{
  return d->frameListMap;
}

const FrameList &ID3v2::Tag::frameList() const
{
  return d->frameList;
}

const FrameList &ID3v2::Tag::frameList(const ByteVector &frameID) const
{
  return d->frameListMap[frameID];
}

void ID3v2::Tag::addFrame(Frame *frame)
{
  d->frameList.append(frame);
  d->frameListMap[frame->frameID()].append(frame);
}

void ID3v2::Tag::removeFrame(Frame *frame, bool del)
{
  // remove the frame from the frame list
  FrameList::Iterator it = d->frameList.find(frame);
  d->frameList.erase(it);

  // ...and from the frame list map
  it = d->frameListMap[frame->frameID()].find(frame);
  d->frameListMap[frame->frameID()].erase(it);

  // ...and delete as desired
  if(del)
	delete frame;
}

void ID3v2::Tag::removeFrames(const ByteVector &id)
{
  FrameList l = d->frameListMap[id];
  for(FrameList::Iterator it = l.begin(); it != l.end(); ++it)
	removeFrame(*it, true);
}

PropertyMap ID3v2::Tag::properties() const
{
  PropertyMap properties;
  for(FrameList::ConstIterator it = frameList().begin(); it != frameList().end(); ++it) {
	PropertyMap props = (*it)->asProperties();
	properties.merge(props);
  }
  return properties;
}

void ID3v2::Tag::removeUnsupportedProperties(const StringList &properties)
{
  for(StringList::ConstIterator it = properties.begin(); it != properties.end(); ++it){
	if(it->startsWith("UNKNOWN/")) {
	  String frameID = it->substr(String("UNKNOWN/").size());
	  if(frameID.size() != 4)
		continue; // invalid specification
	  ByteVector id = frameID.data(String::Latin1);
	  // delete all unknown frames of given type
	  FrameList l = frameList(id);
	  for(FrameList::ConstIterator fit = l.begin(); fit != l.end(); fit++)
		if (dynamic_cast<const UnknownFrame *>(*fit) != NULL)
		  removeFrame(*fit);
	} else if(it->size() == 4){
	  ByteVector id = it->data(String::Latin1);
	  removeFrames(id);
	} else {
	  ByteVector id = it->substr(0,4).data(String::Latin1);
	  if(it->size() <= 5)
		continue; // invalid specification
	  String description = it->substr(5);
	  Frame *frame = NULL;
	  if(id == "TXXX")
		frame = UserTextIdentificationFrame::find(this, description);
	  else if(id == "WXXX")
		frame = UserUrlLinkFrame::find(this, description);
	  else if(id == "COMM")
		frame = CommentsFrame::findByDescription(this, description);
	  else if(id == "USLT")
		frame = UnsynchronizedLyricsFrame::findByDescription(this, description);
	  if(frame)
		removeFrame(frame);
	}
  }
}

PropertyMap ID3v2::Tag::setProperties(const PropertyMap &origProps)
{
  FrameList framesToDelete;
  // we split up the PropertyMap into the "normal" keys and the "complicated" ones,
  // which are those according to TIPL or TMCL frames.
  PropertyMap properties;
  PropertyMap tiplProperties;
  PropertyMap tmclProperties;
  Frame::splitProperties(origProps, properties, tiplProperties, tmclProperties);
  for(FrameListMap::ConstIterator it = frameListMap().begin(); it != frameListMap().end(); ++it){
	for(FrameList::ConstIterator lit = it->second.begin(); lit != it->second.end(); ++lit){
	  PropertyMap frameProperties = (*lit)->asProperties();
	  if(it->first == "TIPL") {
		if (tiplProperties != frameProperties)
		  framesToDelete.append(*lit);
		else
		  tiplProperties.erase(frameProperties);
	  } else if(it->first == "TMCL") {
		if (tmclProperties != frameProperties)
		  framesToDelete.append(*lit);
		else
		  tmclProperties.erase(frameProperties);
	  } else if(!properties.contains(frameProperties))
		framesToDelete.append(*lit);
	  else
		properties.erase(frameProperties);
	}
  }
  for(FrameList::ConstIterator it = framesToDelete.begin(); it != framesToDelete.end(); ++it)
	removeFrame(*it);

  // now create remaining frames:
  // start with the involved people list (TIPL)
  if(!tiplProperties.isEmpty())
	  addFrame(TextIdentificationFrame::createTIPLFrame(tiplProperties));
  // proceed with the musician credit list (TMCL)
  if(!tmclProperties.isEmpty())
	  addFrame(TextIdentificationFrame::createTMCLFrame(tmclProperties));
  // now create the "one key per frame" frames
  for(PropertyMap::ConstIterator it = properties.begin(); it != properties.end(); ++it)
	addFrame(Frame::createTextualFrame(it->first, it->second));
  return PropertyMap(); // ID3 implements the complete PropertyMap interface, so an empty map is returned
}

ByteVector ID3v2::Tag::render() const
{
  return render(4);
}

void ID3v2::Tag::downgradeFrames(FrameList *frames, FrameList *newFrames) const
{
  const char *unsupportedFrames[] = {
	"ASPI", "EQU2", "RVA2", "SEEK", "SIGN", "TDRL", "TDTG",
	"TMOO", "TPRO", "TSOA", "TSOT", "TSST", "TSOP", 0
  };
  ID3v2::TextIdentificationFrame *frameTDOR = 0;
  ID3v2::TextIdentificationFrame *frameTDRC = 0;
  ID3v2::TextIdentificationFrame *frameTIPL = 0;
  ID3v2::TextIdentificationFrame *frameTMCL = 0;
  for(FrameList::Iterator it = d->frameList.begin(); it != d->frameList.end(); it++) {
	ID3v2::Frame *frame = *it;
	ByteVector frameID = frame->header()->frameID();
	for(int i = 0; unsupportedFrames[i]; i++) {
	  if(frameID == unsupportedFrames[i]) {
		debug("A frame that is not supported in ID3v2.3 \'"
		  + String(frameID) + "\' has been discarded");
		frame = 0;
		break;
	  }
	}
	if(frame && frameID == "TDOR") {
	  frameTDOR = dynamic_cast<ID3v2::TextIdentificationFrame *>(frame);
	  frame = 0;
	}
	if(frame && frameID == "TDRC") {
	  frameTDRC = dynamic_cast<ID3v2::TextIdentificationFrame *>(frame);
	  frame = 0;
	}
	if(frame && frameID == "TIPL") {
	  frameTIPL = dynamic_cast<ID3v2::TextIdentificationFrame *>(frame);
	  frame = 0;
	}
	if(frame && frameID == "TMCL") {
	  frameTMCL = dynamic_cast<ID3v2::TextIdentificationFrame *>(frame);
	  frame = 0;
	}
	if(frame) {
	  frames->append(frame);
	}
  }
  if(frameTDOR) {
	String content = frameTDOR->toString();
	if(content.size() >= 4) {
	  ID3v2::TextIdentificationFrame *frameTORY = new ID3v2::TextIdentificationFrame("TORY", String::Latin1);
	  frameTORY->setText(content.substr(0, 4));
	  frames->append(frameTORY);
	  newFrames->append(frameTORY);
	}
  }
  if(frameTDRC) {
	String content = frameTDRC->toString();
	if(content.size() >= 4) {
	  ID3v2::TextIdentificationFrame *frameTYER = new ID3v2::TextIdentificationFrame("TYER", String::Latin1);
	  frameTYER->setText(content.substr(0, 4));
	  frames->append(frameTYER);
	  newFrames->append(frameTYER);
	  if(content.size() >= 10 && content[4] == '-' && content[7] == '-') {
		ID3v2::TextIdentificationFrame *frameTDAT = new ID3v2::TextIdentificationFrame("TDAT", String::Latin1);
		frameTDAT->setText(content.substr(8, 2) + content.substr(5, 2));
		frames->append(frameTDAT);
		newFrames->append(frameTDAT);
		if(content.size() >= 16 && content[10] == 'T' && content[13] == ':') {
		  ID3v2::TextIdentificationFrame *frameTIME = new ID3v2::TextIdentificationFrame("TIME", String::Latin1);
		  frameTIME->setText(content.substr(11, 2) + content.substr(14, 2));
		  frames->append(frameTIME);
		  newFrames->append(frameTIME);
		}
	  }
	}
  }
  if(frameTIPL || frameTMCL) {
	ID3v2::TextIdentificationFrame *frameIPLS = new ID3v2::TextIdentificationFrame("IPLS", String::Latin1);
	StringList people;
	if(frameTMCL) {
	  StringList v24People = frameTMCL->fieldList();
	  for(uint i = 0; i + 1 < v24People.size(); i += 2) {
		people.append(v24People[i]);
		people.append(v24People[i+1]);
	  }
	}
	if(frameTIPL) {
	  StringList v24People = frameTIPL->fieldList();
	  for(uint i = 0; i + 1 < v24People.size(); i += 2) {
		people.append(v24People[i]);
		people.append(v24People[i+1]);
	  }
	}
	frameIPLS->setText(people);
	frames->append(frameIPLS);
	newFrames->append(frameIPLS);
  }
}

ByteVector ID3v2::Tag::render(int version) const
{
  // We need to render the "tag data" first so that we have to correct size to
  // render in the tag's header.  The "tag data" -- everything that is included
  // in ID3v2::Header::tagSize() -- includes the extended header, frames and
  // padding, but does not include the tag's header or footer.

  ByteVector tagData;

  if(version != 3 && version != 4) {
	debug("Unknown ID3v2 version, using ID3v2.4");
	version = 4;
  }

  // TODO: Render the extended header.

  // Loop through the frames rendering them and adding them to the tagData.

  FrameList newFrames;
  newFrames.setAutoDelete(true);

  FrameList frameList;
  if(version == 4) {
	frameList = d->frameList;
  }
  else {
	downgradeFrames(&frameList, &newFrames);
  }

  for(FrameList::Iterator it = frameList.begin(); it != frameList.end(); it++) {
	(*it)->header()->setVersion(version);
	if((*it)->header()->frameID().size() != 4) {
	  debug("A frame of unsupported or unknown type \'"
		  + String((*it)->header()->frameID()) + "\' has been discarded");
	  continue;
	}
	if(!(*it)->header()->tagAlterPreservation())
	  tagData.append((*it)->render());
  }

  // Compute the amount of padding, and append that to tagData.

  uint paddingSize = 0;
  uint originalSize = d->header.tagSize();

  if(tagData.size() < originalSize)
	paddingSize = originalSize - tagData.size();
  else
	paddingSize = 1024;

  tagData.append(ByteVector(paddingSize, char(0)));

  // Set the version and data size.
  d->header.setMajorVersion(version);
  d->header.setTagSize(tagData.size());

  // TODO: This should eventually include d->footer->render().
  return d->header.render() + tagData;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

void ID3v2::Tag::read()
{
  if(d->file && d->file->isOpen()) {

	d->file->seek(d->tagOffset);
	d->header.setData(d->file->readBlock(Header::size()));

	// if the tag size is 0, then this is an invalid tag (tags must contain at
	// least one frame)

	if(d->header.tagSize() == 0)
	  return;

	parse(d->file->readBlock(d->header.tagSize()));
  }
}

void ID3v2::Tag::parse(const ByteVector &origData)
{
  ByteVector data = origData;

  if(d->header.unsynchronisation() && d->header.majorVersion() <= 3)
	data = SynchData::decode(data);

  uint frameDataPosition = 0;
  uint frameDataLength = data.size();

  // check for extended header

  if(d->header.extendedHeader()) {
	if(!d->extendedHeader)
	  d->extendedHeader = new ExtendedHeader;
	d->extendedHeader->setData(data);
	if(d->extendedHeader->size() <= data.size()) {
	  frameDataPosition += d->extendedHeader->size();
	  frameDataLength -= d->extendedHeader->size();
	}
  }

  // check for footer -- we don't actually need to parse it, as it *must*
  // contain the same data as the header, but we do need to account for its
  // size.

  if(d->header.footerPresent() && Footer::size() <= frameDataLength)
	frameDataLength -= Footer::size();

  // parse frames

  // Make sure that there is at least enough room in the remaining frame data for
  // a frame header.

  while(frameDataPosition < frameDataLength - Frame::headerSize(d->header.majorVersion())) {

	// If the next data is position is 0, assume that we've hit the padding
	// portion of the frame data.

	if(data.at(frameDataPosition) == 0) {
	  if(d->header.footerPresent())
		debug("Padding *and* a footer found.  This is not allowed by the spec.");

	  d->paddingSize = frameDataLength - frameDataPosition;
	  return;
	}

	Frame *frame = d->factory->createFrame(data.mid(frameDataPosition),
										   &d->header);

	if(!frame)
	  return;

	// Checks to make sure that frame parsed correctly.

	if(frame->size() <= 0) {
	  delete frame;
	  return;
	}

	frameDataPosition += frame->size() + Frame::headerSize(d->header.majorVersion());
	addFrame(frame);
  }
}

void ID3v2::Tag::setTextFrame(const ByteVector &id, const String &value)
{
  if(value.isEmpty()) {
	removeFrames(id);
	return;
  }

  if(!d->frameListMap[id].isEmpty())
	d->frameListMap[id].front()->setText(value);
  else {
	const String::Type encoding = d->factory->defaultTextEncoding();
	TextIdentificationFrame *f = new TextIdentificationFrame(id, encoding);
	addFrame(f);
	f->setText(value);
  }
}

/*** End of inlined file: id3v2tag.cpp ***/


/*** Start of inlined file: id3v2header.cpp ***/
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

#include <iostream>
#include <bitset>

using namespace TagLib;
using namespace ID3v2;

class Header::HeaderPrivate
{
public:
  HeaderPrivate() : majorVersion(4),
					revisionNumber(0),
					unsynchronisation(false),
					extendedHeader(false),
					experimentalIndicator(false),
					footerPresent(false),
					tagSize(0) {}

  ~HeaderPrivate() {}

  uint majorVersion;
  uint revisionNumber;

  bool unsynchronisation;
  bool extendedHeader;
  bool experimentalIndicator;
  bool footerPresent;

  uint tagSize;

  static const uint size = 10;
};

////////////////////////////////////////////////////////////////////////////////
// static members
////////////////////////////////////////////////////////////////////////////////

TagLib::uint Header::size()
{
  return HeaderPrivate::size;
}

ByteVector Header::fileIdentifier()
{
  return ByteVector::fromCString("ID3");
}

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

Header::Header()
{
  d = new HeaderPrivate;
}

Header::Header(const ByteVector &data)
{
  d = new HeaderPrivate;
  parse(data);
}

Header::~Header()
{
  delete d;
}

TagLib::uint Header::majorVersion() const
{
  return d->majorVersion;
}

void Header::setMajorVersion(TagLib::uint version)
{
  d->majorVersion = version;
}

TagLib::uint Header::revisionNumber() const
{
  return d->revisionNumber;
}

bool Header::unsynchronisation() const
{
  return d->unsynchronisation;
}

bool Header::extendedHeader() const
{
  return d->extendedHeader;
}

bool Header::experimentalIndicator() const
{
  return d->experimentalIndicator;
}

bool Header::footerPresent() const
{
  return d->footerPresent;
}

TagLib::uint Header::tagSize() const
{
  return d->tagSize;
}

TagLib::uint Header::completeTagSize() const
{
  if(d->footerPresent)
	return d->tagSize + d->size + Footer::size();
  else
	return d->tagSize + d->size;
}

void Header::setTagSize(uint s)
{
  d->tagSize = s;
}

void Header::setData(const ByteVector &data)
{
  parse(data);
}

ByteVector Header::render() const
{
  ByteVector v;

  // add the file identifier -- "ID3"
  v.append(fileIdentifier());

  // add the version number -- we always render a 2.4.0 tag regardless of what
  // the tag originally was.

  v.append(char(majorVersion()));
  v.append(char(0));

  // Currently we don't actually support writing extended headers, footers or
  // unsynchronized tags, make sure that the flags are set accordingly.

  d->extendedHeader = false;
  d->footerPresent = false;
  d->unsynchronisation = false;

  // render and add the flags
  std::bitset<8> flags;

  flags[7] = d->unsynchronisation;
  flags[6] = d->extendedHeader;
  flags[5] = d->experimentalIndicator;
  flags[4] = d->footerPresent;

  v.append(char(flags.to_ulong()));

  // add the size
  v.append(SynchData::fromUInt(d->tagSize));

  return v;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

void Header::parse(const ByteVector &data)
{
  if(data.size() < size())
	return;

  // do some sanity checking -- even in ID3v2.3.0 and less the tag size is a
  // synch-safe integer, so all bytes must be less than 128.  If this is not
  // true then this is an invalid tag.

  // note that we're doing things a little out of order here -- the size is
  // later in the bytestream than the version

  ByteVector sizeData = data.mid(6, 4);

  if(sizeData.size() != 4) {
	d->tagSize = 0;
	debug("TagLib::ID3v2::Header::parse() - The tag size as read was 0 bytes!");
	return;
  }

  for(ByteVector::Iterator it = sizeData.begin(); it != sizeData.end(); it++) {
	if(uchar(*it) >= 128) {
	  d->tagSize = 0;
	  debug("TagLib::ID3v2::Header::parse() - One of the size bytes in the id3v2 header was greater than the allowed 128.");
	  return;
	}
  }

  // The first three bytes, data[0..2], are the File Identifier, "ID3". (structure 3.1 "file identifier")

  // Read the version number from the fourth and fifth bytes.
  d->majorVersion = data[3];   // (structure 3.1 "major version")
  d->revisionNumber = data[4]; // (structure 3.1 "revision number")

  // Read the flags, the first four bits of the sixth byte.
  std::bitset<8> flags(data[5]);

  d->unsynchronisation     = flags[7]; // (structure 3.1.a)
  d->extendedHeader        = flags[6]; // (structure 3.1.b)
  d->experimentalIndicator = flags[5]; // (structure 3.1.c)
  d->footerPresent         = flags[4]; // (structure 3.1.d)

  // Get the size from the remaining four bytes (read above)

  d->tagSize = SynchData::toUInt(sizeData); // (structure 3.1 "size")
}

/*** End of inlined file: id3v2header.cpp ***/


/*** Start of inlined file: id3v2frame.cpp ***/
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#if HAVE_ZLIB
#include <zlib.h>
#endif

#include <bitset>

using namespace TagLib;
using namespace ID3v2;

class Frame::FramePrivate
{
public:
  FramePrivate() :
	header(0)
	{}

  ~FramePrivate()
  {
	delete header;
  }

  Frame::Header *header;
};

namespace
{
  bool isValidFrameID(const ByteVector &frameID)
  {
	if(frameID.size() != 4)
	  return false;

	for(ByteVector::ConstIterator it = frameID.begin(); it != frameID.end(); it++) {
	  if( (*it < 'A' || *it > 'Z') && (*it < '1' || *it > '9') ) {
		return false;
	  }
	}
	return true;
  }
}

////////////////////////////////////////////////////////////////////////////////
// static methods
////////////////////////////////////////////////////////////////////////////////

TagLib::uint Frame::headerSize()
{
  return Header::size();
}

TagLib::uint Frame::headerSize(uint version)
{
  return Header::size(version);
}

ByteVector Frame::textDelimiter(String::Type t)
{
  ByteVector d = char(0);
  if(t == String::UTF16 || t == String::UTF16BE || t == String::UTF16LE)
	d.append(char(0));
  return d;
}

const String Frame::instrumentPrefix("PERFORMER:");
const String Frame::commentPrefix("COMMENT:");
const String Frame::lyricsPrefix("LYRICS:");
const String Frame::urlPrefix("URL:");

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

Frame *Frame::createTextualFrame(const String &key, const StringList &values) //static
{
  // check if the key is contained in the key<=>frameID mapping
  ByteVector frameID = keyToFrameID(key);
  if(!frameID.isNull()) {
	if(frameID[0] == 'T'){ // text frame
	  TextIdentificationFrame *frame = new TextIdentificationFrame(frameID, String::UTF8);
	  frame->setText(values);
	  return frame;
	} else if(values.size() == 1){  // URL frame (not WXXX); support only one value
		UrlLinkFrame* frame = new UrlLinkFrame(frameID);
		frame->setUrl(values.front());
		return frame;
	}
  }
  // now we check if it's one of the "special" cases:
  // -LYRICS: depending on the number of values, use USLT or TXXX (with description=LYRICS)
  if((key == "LYRICS" || key.startsWith(lyricsPrefix)) && values.size() == 1){
	UnsynchronizedLyricsFrame *frame = new UnsynchronizedLyricsFrame();
	frame->setDescription(key == "LYRICS" ? key : key.substr(lyricsPrefix.size()));
	frame->setText(values.front());
	return frame;
  }
  // -URL: depending on the number of values, use WXXX or TXXX (with description=URL)
  if((key == "URL" || key.startsWith(urlPrefix)) && values.size() == 1){
	UserUrlLinkFrame *frame = new UserUrlLinkFrame(String::UTF8);
	frame->setDescription(key == "URL" ? key : key.substr(urlPrefix.size()));
	frame->setUrl(values.front());
	return frame;
  }
  // -COMMENT: depending on the number of values, use COMM or TXXX (with description=COMMENT)
  if((key == "COMMENT" || key.startsWith(commentPrefix)) && values.size() == 1){
	CommentsFrame *frame = new CommentsFrame(String::UTF8);
	frame->setDescription(key == "COMMENT" ? key : key.substr(commentPrefix.size()));
	frame->setText(values.front());
	return frame;
  }
  // if non of the above cases apply, we use a TXXX frame with the key as description
  return new UserTextIdentificationFrame(key, values, String::UTF8);
}

Frame::~Frame()
{
  delete d;
}

ByteVector Frame::frameID() const
{
  if(d->header)
	return d->header->frameID();
  else
	return ByteVector::null;
}

TagLib::uint Frame::size() const
{
  if(d->header)
	return d->header->frameSize();
  else
	return 0;
}

void Frame::setData(const ByteVector &data)
{
  parse(data);
}

void Frame::setText(const String &)
{

}

ByteVector Frame::render() const
{
  ByteVector fieldData = renderFields();
  d->header->setFrameSize(fieldData.size());
  ByteVector headerData = d->header->render();

  return headerData + fieldData;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

Frame::Frame(const ByteVector &data)
{
  d = new FramePrivate;
  d->header = new Header(data);
}

Frame::Frame(Header *h)
{
  d = new FramePrivate;
  d->header = h;
}

Frame::Header *Frame::header() const
{
  return d->header;
}

void Frame::setHeader(Header *h, bool deleteCurrent)
{
  if(deleteCurrent)
	delete d->header;

  d->header = h;
}

void Frame::parse(const ByteVector &data)
{
  if(d->header)
	d->header->setData(data);
  else
	d->header = new Header(data);

  parseFields(fieldData(data));
}

ByteVector Frame::fieldData(const ByteVector &frameData) const
{
  uint headerSize = Header::size(d->header->version());

  uint frameDataOffset = headerSize;
  uint frameDataLength = size();

  if(d->header->compression() || d->header->dataLengthIndicator()) {
	frameDataLength = SynchData::toUInt(frameData.mid(headerSize, 4));
	frameDataOffset += 4;
  }

#if HAVE_ZLIB
  if(d->header->compression() &&
	 !d->header->encryption())
  {
	ByteVector data(frameDataLength);
	uLongf uLongTmp = frameDataLength;
	::uncompress((Bytef *) data.data(),
				 (uLongf *) &uLongTmp,
				 (Bytef *) frameData.data() + frameDataOffset,
				 size());
	return data;
  }
  else
#endif
	return frameData.mid(frameDataOffset, frameDataLength);
}

String Frame::readStringField(const ByteVector &data, String::Type encoding, int *position)
{
  int start = 0;

  if(!position)
	position = &start;

  ByteVector delimiter = textDelimiter(encoding);

  int end = data.find(delimiter, *position, delimiter.size());

  if(end < *position)
	return String::null;

  String str = String(data.mid(*position, end - *position), encoding);

  *position = end + delimiter.size();

  return str;
}

String::Type Frame::checkEncoding(const StringList &fields, String::Type encoding) // static
{
  return checkEncoding(fields, encoding, 4);
}

String::Type Frame::checkEncoding(const StringList &fields, String::Type encoding, uint version) // static
{
  if((encoding == String::UTF8 || encoding == String::UTF16BE) && version != 4)
	return String::UTF16;

  if(encoding != String::Latin1)
	return encoding;

  for(StringList::ConstIterator it = fields.begin(); it != fields.end(); ++it) {
	if(!(*it).isLatin1()) {
	  if(version == 4) {
		debug("Frame::checkEncoding() -- Rendering using UTF8.");
		return String::UTF8;
	  }
	  else {
		debug("Frame::checkEncoding() -- Rendering using UTF16.");
		return String::UTF16;
	  }
	}
  }

  return String::Latin1;
}

String::Type Frame::checkTextEncoding(const StringList &fields, String::Type encoding) const
{
  return checkEncoding(fields, encoding, header()->version());
}

static const TagLib::uint frameTranslationSize = 51;
static const char *frameTranslation[][2] = {
  // Text information frames
  { "TALB", "ALBUM"},
  { "TBPM", "BPM" },
  { "TCOM", "COMPOSER" },
  { "TCON", "GENRE" },
  { "TCOP", "COPYRIGHT" },
  { "TDEN", "ENCODINGTIME" },
  { "TDLY", "PLAYLISTDELAY" },
  { "TDOR", "ORIGINALDATE" },
  { "TDRC", "DATE" },
  // { "TRDA", "DATE" }, // id3 v2.3, replaced by TDRC in v2.4
  // { "TDAT", "DATE" }, // id3 v2.3, replaced by TDRC in v2.4
  // { "TYER", "DATE" }, // id3 v2.3, replaced by TDRC in v2.4
  // { "TIME", "DATE" }, // id3 v2.3, replaced by TDRC in v2.4
  { "TDRL", "RELEASEDATE" },
  { "TDTG", "TAGGINGDATE" },
  { "TENC", "ENCODEDBY" },
  { "TEXT", "LYRICIST" },
  { "TFLT", "FILETYPE" },
  //{ "TIPL", "INVOLVEDPEOPLE" }, handled separately
  { "TIT1", "CONTENTGROUP" },
  { "TIT2", "TITLE"},
  { "TIT3", "SUBTITLE" },
  { "TKEY", "INITIALKEY" },
  { "TLAN", "LANGUAGE" },
  { "TLEN", "LENGTH" },
  //{ "TMCL", "MUSICIANCREDITS" }, handled separately
  { "TMED", "MEDIATYPE" },
  { "TMOO", "MOOD" },
  { "TOAL", "ORIGINALALBUM" },
  { "TOFN", "ORIGINALFILENAME" },
  { "TOLY", "ORIGINALLYRICIST" },
  { "TOPE", "ORIGINALARTIST" },
  { "TOWN", "OWNER" },
  { "TPE1", "ARTIST"},
  { "TPE2", "ALBUMARTIST" }, // id3's spec says 'PERFORMER', but most programs use 'ALBUMARTIST'
  { "TPE3", "CONDUCTOR" },
  { "TPE4", "REMIXER" }, // could also be ARRANGER
  { "TPOS", "DISCNUMBER" },
  { "TPRO", "PRODUCEDNOTICE" },
  { "TPUB", "PUBLISHER" },
  { "TRCK", "TRACKNUMBER" },
  { "TRSN", "RADIOSTATION" },
  { "TRSO", "RADIOSTATIONOWNER" },
  { "TSOA", "ALBUMSORT" },
  { "TSOP", "ARTISTSORT" },
  { "TSOT", "TITLESORT" },
  { "TSO2", "ALBUMARTISTSORT" }, // non-standard, used by iTunes
  { "TSRC", "ISRC" },
  { "TSSE", "ENCODING" },
  // URL frames
  { "WCOP", "COPYRIGHTURL" },
  { "WOAF", "FILEWEBPAGE" },
  { "WOAR", "ARTISTWEBPAGE" },
  { "WOAS", "AUDIOSOURCEWEBPAGE" },
  { "WORS", "RADIOSTATIONWEBPAGE" },
  { "WPAY", "PAYMENTWEBPAGE" },
  { "WPUB", "PUBLISHERWEBPAGE" },
  //{ "WXXX", "URL"}, handled specially
  // Other frames
  { "COMM", "COMMENT" },
  //{ "USLT", "LYRICS" }, handled specially
};

Map<ByteVector, String> &idMap()
{
  static Map<ByteVector, String> m;
  if(m.isEmpty())
	for(size_t i = 0; i < frameTranslationSize; ++i)
	  m[frameTranslation[i][0]] = frameTranslation[i][1];
  return m;
}

// list of deprecated frames and their successors
static const TagLib::uint deprecatedFramesSize = 4;
static const char *deprecatedFrames[][2] = {
  {"TRDA", "TDRC"}, // 2.3 -> 2.4 (http://en.wikipedia.org/wiki/ID3)
  {"TDAT", "TDRC"}, // 2.3 -> 2.4
  {"TYER", "TDRC"}, // 2.3 -> 2.4
  {"TIME", "TDRC"}, // 2.3 -> 2.4
};

Map<ByteVector,ByteVector> &deprecationMap()
{
  static Map<ByteVector,ByteVector> depMap;
  if(depMap.isEmpty())
	for(TagLib::uint i = 0; i < deprecatedFramesSize; ++i)
	  depMap[deprecatedFrames[i][0]] = deprecatedFrames[i][1];
  return depMap;
}

String Frame::frameIDToKey(const ByteVector &id)
{
  Map<ByteVector, String> &m = idMap();
  if(m.contains(id))
	return m[id];
  if(deprecationMap().contains(id))
	return m[deprecationMap()[id]];
  return String::null;
}

ByteVector Frame::keyToFrameID(const String &s)
{
  static Map<String, ByteVector> m;
  if(m.isEmpty())
	for(size_t i = 0; i < frameTranslationSize; ++i)
	  m[frameTranslation[i][1]] = frameTranslation[i][0];
  if(m.contains(s.upper()))
	return m[s];
  return ByteVector::null;
}

PropertyMap Frame::asProperties() const
{
  if(dynamic_cast< const UnknownFrame *>(this)) {
	PropertyMap m;
	m.unsupportedData().append("UNKNOWN/" + frameID());
	return m;
  }
  const ByteVector &id = frameID();
  // workaround until this function is virtual
  if(id == "TXXX")
	return dynamic_cast< const UserTextIdentificationFrame* >(this)->asProperties();
  else if(id[0] == 'T')
	return dynamic_cast< const TextIdentificationFrame* >(this)->asProperties();
  else if(id == "WXXX")
	return dynamic_cast< const UserUrlLinkFrame* >(this)->asProperties();
  else if(id[0] == 'W')
	return dynamic_cast< const UrlLinkFrame* >(this)->asProperties();
  else if(id == "COMM")
	return dynamic_cast< const CommentsFrame* >(this)->asProperties();
  else if(id == "USLT")
	return dynamic_cast< const UnsynchronizedLyricsFrame* >(this)->asProperties();
  PropertyMap m;
  m.unsupportedData().append(id);
  return m;
}

void Frame::splitProperties(const PropertyMap &original, PropertyMap &singleFrameProperties,
		  PropertyMap &tiplProperties, PropertyMap &tmclProperties)
{

  singleFrameProperties.clear();
  tiplProperties.clear();
  tmclProperties.clear();
  for(PropertyMap::ConstIterator it = original.begin(); it != original.end(); ++it) {
	if(TextIdentificationFrame::involvedPeopleMap().contains(it->first))
	  tiplProperties.insert(it->first, it->second);
	else if(it->first.startsWith(TextIdentificationFrame::instrumentPrefix))
	  tmclProperties.insert(it->first, it->second);
	else
	  singleFrameProperties.insert(it->first, it->second);
  }
}

////////////////////////////////////////////////////////////////////////////////
// Frame::Header class
////////////////////////////////////////////////////////////////////////////////

class Frame::Header::HeaderPrivate
{
public:
  HeaderPrivate() :
	frameSize(0),
	version(4),
	tagAlterPreservation(false),
	fileAlterPreservation(false),
	readOnly(false),
	groupingIdentity(false),
	compression(false),
	encryption(false),
	unsynchronisation(false),
	dataLengthIndicator(false)
	{}

  ByteVector frameID;
  uint frameSize;
  uint version;

  // flags

  bool tagAlterPreservation;
  bool fileAlterPreservation;
  bool readOnly;
  bool groupingIdentity;
  bool compression;
  bool encryption;
  bool unsynchronisation;
  bool dataLengthIndicator;
};

////////////////////////////////////////////////////////////////////////////////
// static members (Frame::Header)
////////////////////////////////////////////////////////////////////////////////

TagLib::uint Frame::Header::size()
{
  return size(4);
}

TagLib::uint Frame::Header::size(uint version)
{
  switch(version) {
  case 0:
  case 1:
  case 2:
	return 6;
  case 3:
  case 4:
  default:
	return 10;
  }
}

////////////////////////////////////////////////////////////////////////////////
// public members (Frame::Header)
////////////////////////////////////////////////////////////////////////////////

Frame::Header::Header(const ByteVector &data, bool synchSafeInts)
{
  d = new HeaderPrivate;
  setData(data, synchSafeInts);
}

Frame::Header::Header(const ByteVector &data, uint version)
{
  d = new HeaderPrivate;
  setData(data, version);
}

Frame::Header::~Header()
{
  delete d;
}

void Frame::Header::setData(const ByteVector &data, bool synchSafeInts)
{
  setData(data, uint(synchSafeInts ? 4 : 3));
}

void Frame::Header::setData(const ByteVector &data, uint version)
{
  d->version = version;

  switch(version) {
  case 0:
  case 1:
  case 2:
  {
	// ID3v2.2

	if(data.size() < 3) {
	  debug("You must at least specify a frame ID.");
	  return;
	}

	// Set the frame ID -- the first three bytes

	d->frameID = data.mid(0, 3);

	// If the full header information was not passed in, do not continue to the
	// steps to parse the frame size and flags.

	if(data.size() < 6) {
	  d->frameSize = 0;
	  return;
	}

	d->frameSize = data.mid(3, 3).toUInt();

	break;
  }
  case 3:
  {
	// ID3v2.3

	if(data.size() < 4) {
	  debug("You must at least specify a frame ID.");
	  return;
	}

	// Set the frame ID -- the first four bytes

	d->frameID = data.mid(0, 4);

	// If the full header information was not passed in, do not continue to the
	// steps to parse the frame size and flags.

	if(data.size() < 10) {
	  d->frameSize = 0;
	  return;
	}

	// Set the size -- the frame size is the four bytes starting at byte four in
	// the frame header (structure 4)

	d->frameSize = data.mid(4, 4).toUInt();

	{ // read the first byte of flags
	  std::bitset<8> flags(data[8]);
	  d->tagAlterPreservation  = flags[7]; // (structure 3.3.1.a)
	  d->fileAlterPreservation = flags[6]; // (structure 3.3.1.b)
	  d->readOnly              = flags[5]; // (structure 3.3.1.c)
	}

	{ // read the second byte of flags
	  std::bitset<8> flags(data[9]);
	  d->compression         = flags[7]; // (structure 3.3.1.i)
	  d->encryption          = flags[6]; // (structure 3.3.1.j)
	  d->groupingIdentity    = flags[5]; // (structure 3.3.1.k)
	}
	break;
  }
  case 4:
  default:
  {
	// ID3v2.4

	if(data.size() < 4) {
	  debug("You must at least specify a frame ID.");
	  return;
	}

	// Set the frame ID -- the first four bytes

	d->frameID = data.mid(0, 4);

	// If the full header information was not passed in, do not continue to the
	// steps to parse the frame size and flags.

	if(data.size() < 10) {
	  d->frameSize = 0;
	  return;
	}

	// Set the size -- the frame size is the four bytes starting at byte four in
	// the frame header (structure 4)

	d->frameSize = SynchData::toUInt(data.mid(4, 4));
#ifndef NO_ITUNES_HACKS
	// iTunes writes v2.4 tags with v2.3-like frame sizes
	if(d->frameSize > 127) {
	  if(!isValidFrameID(data.mid(d->frameSize + 10, 4))) {
		unsigned int uintSize = data.mid(4, 4).toUInt();
		if(isValidFrameID(data.mid(uintSize + 10, 4))) {
		  d->frameSize = uintSize;
		}
	  }
	}
#endif

	{ // read the first byte of flags
	  std::bitset<8> flags(data[8]);
	  d->tagAlterPreservation  = flags[6]; // (structure 4.1.1.a)
	  d->fileAlterPreservation = flags[5]; // (structure 4.1.1.b)
	  d->readOnly              = flags[4]; // (structure 4.1.1.c)
	}

	{ // read the second byte of flags
	  std::bitset<8> flags(data[9]);
	  d->groupingIdentity    = flags[6]; // (structure 4.1.2.h)
	  d->compression         = flags[3]; // (structure 4.1.2.k)
	  d->encryption          = flags[2]; // (structure 4.1.2.m)
	  d->unsynchronisation   = flags[1]; // (structure 4.1.2.n)
	  d->dataLengthIndicator = flags[0]; // (structure 4.1.2.p)
	}
	break;
  }
  }
}

ByteVector Frame::Header::frameID() const
{
  return d->frameID;
}

void Frame::Header::setFrameID(const ByteVector &id)
{
  d->frameID = id.mid(0, 4);
}

TagLib::uint Frame::Header::frameSize() const
{
  return d->frameSize;
}

void Frame::Header::setFrameSize(uint size)
{
  d->frameSize = size;
}

TagLib::uint Frame::Header::version() const
{
  return d->version;
}

void Frame::Header::setVersion(TagLib::uint version)
{
  d->version = version;
}

bool Frame::Header::tagAlterPreservation() const
{
  return d->tagAlterPreservation;
}

void Frame::Header::setTagAlterPreservation(bool preserve)
{
  d->tagAlterPreservation = preserve;
}

bool Frame::Header::fileAlterPreservation() const
{
  return d->fileAlterPreservation;
}

bool Frame::Header::readOnly() const
{
  return d->readOnly;
}

bool Frame::Header::groupingIdentity() const
{
  return d->groupingIdentity;
}

bool Frame::Header::compression() const
{
  return d->compression;
}

bool Frame::Header::encryption() const
{
  return d->encryption;
}

bool Frame::Header::unsycronisation() const
{
  return unsynchronisation();
}

bool Frame::Header::unsynchronisation() const
{
  return d->unsynchronisation;
}

bool Frame::Header::dataLengthIndicator() const
{
  return d->dataLengthIndicator;
}

ByteVector Frame::Header::render() const
{
  ByteVector flags(2, char(0)); // just blank for the moment

  ByteVector v = d->frameID +
	(d->version == 3
	  ? ByteVector::fromUInt(d->frameSize)
	  : SynchData::fromUInt(d->frameSize)) +
	flags;

  return v;
}

bool Frame::Header::frameAlterPreservation() const
{
  return fileAlterPreservation();
}

/*** End of inlined file: id3v2frame.cpp ***/


/*** Start of inlined file: id3v2footer.cpp ***/
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

using namespace TagLib;
using namespace ID3v2;

class Footer::FooterPrivate
{
public:
  static const uint size = 10;
};

Footer::Footer()
{

}

Footer::~Footer()
{

}

TagLib::uint Footer::size()
{
  return FooterPrivate::size;
}

ByteVector Footer::render(const Header *header) const
{
	ByteVector headerData = header->render();
	headerData[0] = '3';
	headerData[1] = 'D';
	headerData[2] = 'I';
	return headerData;
}

/*** End of inlined file: id3v2footer.cpp ***/


/*** Start of inlined file: id3v2extendedheader.cpp ***/
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

using namespace TagLib;
using namespace ID3v2;

class ExtendedHeader::ExtendedHeaderPrivate
{
public:
  ExtendedHeaderPrivate() : size(0) {}

  uint size;
};

////////////////////////////////////////////////////////////////////////////////
// public methods
////////////////////////////////////////////////////////////////////////////////

ExtendedHeader::ExtendedHeader()
{
  d = new ExtendedHeaderPrivate();
}

ExtendedHeader::~ExtendedHeader()
{
  delete d;
}

TagLib::uint ExtendedHeader::size() const
{
  return d->size;
}

void ExtendedHeader::setData(const ByteVector &data)
{
  parse(data);
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

void ExtendedHeader::parse(const ByteVector &data)
{
  d->size = SynchData::toUInt(data.mid(0, 4)); // (structure 3.2 "Extended header size")
}

/*** End of inlined file: id3v2extendedheader.cpp ***/


/*** Start of inlined file: attachedpictureframe.cpp ***/
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

using namespace TagLib;
using namespace ID3v2;

class AttachedPictureFrame::AttachedPictureFramePrivate
{
public:
  AttachedPictureFramePrivate() : textEncoding(String::Latin1),
								  type(AttachedPictureFrame::Other) {}

  String::Type textEncoding;
  String mimeType;
  AttachedPictureFrame::Type type;
  String description;
  ByteVector data;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

AttachedPictureFrame::AttachedPictureFrame() : Frame("APIC")
{
  d = new AttachedPictureFramePrivate;
}

AttachedPictureFrame::AttachedPictureFrame(const ByteVector &data) : Frame(data)
{
  d = new AttachedPictureFramePrivate;
  setData(data);
}

AttachedPictureFrame::~AttachedPictureFrame()
{
  delete d;
}

String AttachedPictureFrame::toString() const
{
  String s = "[" + d->mimeType + "]";
  return d->description.isEmpty() ? s : d->description + " " + s;
}

String::Type AttachedPictureFrame::textEncoding() const
{
  return d->textEncoding;
}

void AttachedPictureFrame::setTextEncoding(String::Type t)
{
  d->textEncoding = t;
}

String AttachedPictureFrame::mimeType() const
{
  return d->mimeType;
}

void AttachedPictureFrame::setMimeType(const String &m)
{
  d->mimeType = m;
}

AttachedPictureFrame::Type AttachedPictureFrame::type() const
{
  return d->type;
}

void AttachedPictureFrame::setType(Type t)
{
  d->type = t;
}

String AttachedPictureFrame::description() const
{
  return d->description;
}

void AttachedPictureFrame::setDescription(const String &desc)
{
  d->description = desc;
}

ByteVector AttachedPictureFrame::picture() const
{
  return d->data;
}

void AttachedPictureFrame::setPicture(const ByteVector &p)
{
  d->data = p;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

void AttachedPictureFrame::parseFields(const ByteVector &data)
{
  if(data.size() < 5) {
	debug("A picture frame must contain at least 5 bytes.");
	return;
  }

  d->textEncoding = String::Type(data[0]);

  int pos = 1;

  d->mimeType = readStringField(data, String::Latin1, &pos);
  /* Now we need at least two more bytes available */
  if (uint(pos) + 1 >= data.size()) {
	debug("Truncated picture frame.");
	return;
  }

  d->type = (TagLib::ID3v2::AttachedPictureFrame::Type)data[pos++];
  d->description = readStringField(data, d->textEncoding, &pos);

  d->data = data.mid(pos);
}

ByteVector AttachedPictureFrame::renderFields() const
{
  ByteVector data;

  String::Type encoding = checkTextEncoding(d->description, d->textEncoding);

  data.append(char(encoding));
  data.append(d->mimeType.data(String::Latin1));
  data.append(textDelimiter(String::Latin1));
  data.append(char(d->type));
  data.append(d->description.data(encoding));
  data.append(textDelimiter(encoding));
  data.append(d->data);

  return data;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

AttachedPictureFrame::AttachedPictureFrame(const ByteVector &data, Header *h) : Frame(h)
{
  d = new AttachedPictureFramePrivate;
  parseFields(fieldData(data));
}

////////////////////////////////////////////////////////////////////////////////
// support for ID3v2.2 PIC frames
////////////////////////////////////////////////////////////////////////////////

void AttachedPictureFrameV22::parseFields(const ByteVector &data)
{
  if(data.size() < 5) {
	debug("A picture frame must contain at least 5 bytes.");
	return;
  }

  d->textEncoding = String::Type(data[0]);

  int pos = 1;

  String fixedString = String(data.mid(pos, 3), String::Latin1);
  pos += 3;
  // convert fixed string image type to mime string
  if (fixedString.upper() == "JPG") {
	d->mimeType = "image/jpeg";
  } else if (fixedString.upper() == "PNG") {
	d->mimeType = "image/png";
  } else {
	debug("probably unsupported image type");
	d->mimeType = "image/" + fixedString;
  }

  d->type = (TagLib::ID3v2::AttachedPictureFrame::Type)data[pos++];
  d->description = readStringField(data, d->textEncoding, &pos);

  d->data = data.mid(pos);
}

AttachedPictureFrameV22::AttachedPictureFrameV22(const ByteVector &data, Header *h)
{
  // set v2.2 header to make fieldData work correctly
  setHeader(h, true);

  parseFields(fieldData(data));

  // now set the v2.4 header
  Frame::Header *newHeader = new Frame::Header("APIC");
  newHeader->setFrameSize(h->frameSize());
  setHeader(newHeader, true);
}

/*** End of inlined file: attachedpictureframe.cpp ***/


/*** Start of inlined file: commentsframe.cpp ***/
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

using namespace TagLib;
using namespace ID3v2;

class CommentsFrame::CommentsFramePrivate
{
public:
  CommentsFramePrivate() : textEncoding(String::Latin1) {}
  String::Type textEncoding;
  ByteVector language;
  String description;
  String text;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

CommentsFrame::CommentsFrame(String::Type encoding) : Frame("COMM")
{
  d = new CommentsFramePrivate;
  d->textEncoding = encoding;
}

CommentsFrame::CommentsFrame(const ByteVector &data) : Frame(data)
{
  d = new CommentsFramePrivate;
  setData(data);
}

CommentsFrame::~CommentsFrame()
{
  delete d;
}

String CommentsFrame::toString() const
{
  return d->text;
}

ByteVector CommentsFrame::language() const
{
  return d->language;
}

String CommentsFrame::description() const
{
  return d->description;
}

String CommentsFrame::text() const
{
  return d->text;
}

void CommentsFrame::setLanguage(const ByteVector &languageEncoding)
{
  d->language = languageEncoding.mid(0, 3);
}

void CommentsFrame::setDescription(const String &s)
{
  d->description = s;
}

void CommentsFrame::setText(const String &s)
{
  d->text = s;
}

String::Type CommentsFrame::textEncoding() const
{
  return d->textEncoding;
}

void CommentsFrame::setTextEncoding(String::Type encoding)
{
  d->textEncoding = encoding;
}

PropertyMap CommentsFrame::asProperties() const
{
  String key = PropertyMap::prepareKey(description());
  PropertyMap map;
  if(key.isEmpty() || key == "COMMENT")
	map.insert("COMMENT", text());
  else if(key.isNull())
	map.unsupportedData().append(L"COMM/" + description());
  else
	map.insert("COMMENT:" + key, text());
  return map;
}

CommentsFrame *CommentsFrame::findByDescription(const ID3v2::Tag *tag, const String &d) // static
{
  ID3v2::FrameList comments = tag->frameList("COMM");

  for(ID3v2::FrameList::ConstIterator it = comments.begin();
	  it != comments.end();
	  ++it)
  {
	CommentsFrame *frame = dynamic_cast<CommentsFrame *>(*it);
	if(frame && frame->description() == d)
	  return frame;
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

void CommentsFrame::parseFields(const ByteVector &data)
{
  if(data.size() < 5) {
	debug("A comment frame must contain at least 5 bytes.");
	return;
  }

  d->textEncoding = String::Type(data[0]);
  d->language = data.mid(1, 3);

  int byteAlign = d->textEncoding == String::Latin1 || d->textEncoding == String::UTF8 ? 1 : 2;

  ByteVectorList l = ByteVectorList::split(data.mid(4), textDelimiter(d->textEncoding), byteAlign, 2);

  if(l.size() == 2) {
	d->description = String(l.front(), d->textEncoding);
	d->text = String(l.back(), d->textEncoding);
  }
}

ByteVector CommentsFrame::renderFields() const
{
  ByteVector v;

  String::Type encoding = d->textEncoding;

  encoding = checkTextEncoding(d->description, encoding);
  encoding = checkTextEncoding(d->text, encoding);

  v.append(char(encoding));
  v.append(d->language.size() == 3 ? d->language : "XXX");
  v.append(d->description.data(encoding));
  v.append(textDelimiter(encoding));
  v.append(d->text.data(encoding));

  return v;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

CommentsFrame::CommentsFrame(const ByteVector &data, Header *h) : Frame(h)
{
  d = new CommentsFramePrivate();
  parseFields(fieldData(data));
}

/*** End of inlined file: commentsframe.cpp ***/


/*** Start of inlined file: generalencapsulatedobjectframe.cpp ***/
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

using namespace TagLib;
using namespace ID3v2;

class GeneralEncapsulatedObjectFrame::GeneralEncapsulatedObjectFramePrivate
{
public:
  GeneralEncapsulatedObjectFramePrivate() : textEncoding(String::Latin1) {}

  String::Type textEncoding;
  String mimeType;
  String fileName;
  String description;
  ByteVector data;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

GeneralEncapsulatedObjectFrame::GeneralEncapsulatedObjectFrame() : Frame("GEOB")
{
	d = new GeneralEncapsulatedObjectFramePrivate;
}

GeneralEncapsulatedObjectFrame::GeneralEncapsulatedObjectFrame(const ByteVector &data) : Frame(data)
{
  d = new GeneralEncapsulatedObjectFramePrivate;
  setData(data);
}

GeneralEncapsulatedObjectFrame::~GeneralEncapsulatedObjectFrame()
{
  delete d;
}

String GeneralEncapsulatedObjectFrame::toString() const
{
  String text = "[" + d->mimeType + "]";

  if(!d->fileName.isEmpty())
	text += " " + d->fileName;

  if(!d->description.isEmpty())
	text += " \"" + d->description + "\"";

  return text;
}

String::Type GeneralEncapsulatedObjectFrame::textEncoding() const
{
  return d->textEncoding;
}

void GeneralEncapsulatedObjectFrame::setTextEncoding(String::Type encoding)
{
  d->textEncoding = encoding;
}

String GeneralEncapsulatedObjectFrame::mimeType() const
{
  return d->mimeType;
}

void GeneralEncapsulatedObjectFrame::setMimeType(const String &type)
{
  d->mimeType = type;
}

String GeneralEncapsulatedObjectFrame::fileName() const
{
  return d->fileName;
}

void GeneralEncapsulatedObjectFrame::setFileName(const String &name)
{
  d->fileName = name;
}

String GeneralEncapsulatedObjectFrame::description() const
{
  return d->description;
}

void GeneralEncapsulatedObjectFrame::setDescription(const String &desc)
{
  d->description = desc;
}

ByteVector GeneralEncapsulatedObjectFrame::object() const
{
  return d->data;
}

void GeneralEncapsulatedObjectFrame::setObject(const ByteVector &data)
{
  d->data = data;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

void GeneralEncapsulatedObjectFrame::parseFields(const ByteVector &data)
{
  if(data.size() < 4) {
	debug("An object frame must contain at least 4 bytes.");
	return;
  }

  d->textEncoding = String::Type(data[0]);

  int pos = 1;

  d->mimeType = readStringField(data, String::Latin1, &pos);
  d->fileName = readStringField(data, d->textEncoding, &pos);
  d->description = readStringField(data, d->textEncoding, &pos);

  d->data = data.mid(pos);
}

ByteVector GeneralEncapsulatedObjectFrame::renderFields() const
{
  ByteVector data;

  data.append(char(d->textEncoding));
  data.append(d->mimeType.data(String::Latin1));
  data.append(textDelimiter(String::Latin1));
  data.append(d->fileName.data(d->textEncoding));
  data.append(textDelimiter(d->textEncoding));
  data.append(d->description.data(d->textEncoding));
  data.append(textDelimiter(d->textEncoding));
  data.append(d->data);

  return data;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

GeneralEncapsulatedObjectFrame::GeneralEncapsulatedObjectFrame(const ByteVector &data, Header *h) : Frame(h)
{
  d = new GeneralEncapsulatedObjectFramePrivate;
  parseFields(fieldData(data));
}

/*** End of inlined file: generalencapsulatedobjectframe.cpp ***/


/*** Start of inlined file: popularimeterframe.cpp ***/
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

using namespace TagLib;
using namespace ID3v2;

class PopularimeterFrame::PopularimeterFramePrivate
{
public:
  PopularimeterFramePrivate() : rating(0), counter(0) {}
  String email;
  int rating;
  TagLib::uint counter;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

PopularimeterFrame::PopularimeterFrame() : Frame("POPM")
{
  d = new PopularimeterFramePrivate;
}

PopularimeterFrame::PopularimeterFrame(const ByteVector &data) : Frame(data)
{
  d = new PopularimeterFramePrivate;
  setData(data);
}

PopularimeterFrame::~PopularimeterFrame()
{
  delete d;
}

String PopularimeterFrame::toString() const
{
  return d->email + " rating=" + String::number(d->rating) + " counter=" + String::number(d->counter);
}

String PopularimeterFrame::email() const
{
  return d->email;
}

void PopularimeterFrame::setEmail(const String &s)
{
  d->email = s;
}

int PopularimeterFrame::rating() const
{
  return d->rating;
}

void PopularimeterFrame::setRating(int s)
{
  d->rating = s;
}

TagLib::uint PopularimeterFrame::counter() const
{
  return d->counter;
}

void PopularimeterFrame::setCounter(TagLib::uint s)
{
  d->counter = s;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

void PopularimeterFrame::parseFields(const ByteVector &data)
{
  int pos = 0, size = int(data.size());

  d->email = readStringField(data, String::Latin1, &pos);

  d->rating = 0;
  d->counter = 0;
  if(pos < size) {
	d->rating = (unsigned char)(data[pos++]);
	if(pos < size) {
	  d->counter = data.mid(pos, 4).toUInt();
	}
  }
}

ByteVector PopularimeterFrame::renderFields() const
{
  ByteVector data;

  data.append(d->email.data(String::Latin1));
  data.append(textDelimiter(String::Latin1));
  data.append(char(d->rating));
  data.append(ByteVector::fromUInt(d->counter));

  return data;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

PopularimeterFrame::PopularimeterFrame(const ByteVector &data, Header *h) : Frame(h)
{
  d = new PopularimeterFramePrivate;
  parseFields(fieldData(data));
}

/*** End of inlined file: popularimeterframe.cpp ***/


/*** Start of inlined file: privateframe.cpp ***/
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

using namespace TagLib;
using namespace ID3v2;

class PrivateFrame::PrivateFramePrivate
{
public:
  ByteVector data;
  String owner;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

PrivateFrame::PrivateFrame() : Frame("PRIV")
{
  d = new PrivateFramePrivate;
}

PrivateFrame::PrivateFrame(const ByteVector &data) : Frame(data)
{
  d = new PrivateFramePrivate;
  setData(data);
}

PrivateFrame::~PrivateFrame()
{
  delete d;
}

String PrivateFrame::toString() const
{
  return d->owner;
}

String PrivateFrame::owner() const
{
  return d->owner;
}

ByteVector PrivateFrame::data() const
{
  return d->data;
}

void PrivateFrame::setOwner(const String &s)
{
  d->owner = s;
}

void PrivateFrame::setData(const ByteVector & data)
{
  d->data = data;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

void PrivateFrame::parseFields(const ByteVector &data)
{
  if(data.size() < 2) {
	debug("A private frame must contain at least 2 bytes.");
	return;
  }

  // Owner identifier is assumed to be Latin1

  const int byteAlign =  1;
  const int endOfOwner = data.find(textDelimiter(String::Latin1), 0, byteAlign);

  d->owner =  String(data.mid(0, endOfOwner));
  d->data = data.mid(endOfOwner + 1);
}

ByteVector PrivateFrame::renderFields() const
{
  ByteVector v;

  v.append(d->owner.data(String::Latin1));
  v.append(textDelimiter(String::Latin1));
  v.append(d->data);

  return v;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

PrivateFrame::PrivateFrame(const ByteVector &data, Header *h) : Frame(h)
{
  d = new PrivateFramePrivate();
  parseFields(fieldData(data));
}

/*** End of inlined file: privateframe.cpp ***/


/*** Start of inlined file: relativevolumeframe.cpp ***/
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

using namespace TagLib;
using namespace ID3v2;

static inline int bitsToBytes(int i)
{
  return i % 8 == 0 ? i / 8 : (i - i % 8) / 8 + 1;
}

struct ChannelData
{
  ChannelData() : channelType(RelativeVolumeFrame::Other), volumeAdjustment(0) {}

  RelativeVolumeFrame::ChannelType channelType;
  short volumeAdjustment;
  RelativeVolumeFrame::PeakVolume peakVolume;
};

class RelativeVolumeFrame::RelativeVolumeFramePrivate
{
public:
  String identification;
  Map<ChannelType, ChannelData> channels;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

RelativeVolumeFrame::RelativeVolumeFrame() : Frame("RVA2")
{
  d = new RelativeVolumeFramePrivate;
}

RelativeVolumeFrame::RelativeVolumeFrame(const ByteVector &data) : Frame(data)
{
  d = new RelativeVolumeFramePrivate;
  setData(data);
}

RelativeVolumeFrame::~RelativeVolumeFrame()
{
  delete d;
}

String RelativeVolumeFrame::toString() const
{
  return d->identification;
}

List<RelativeVolumeFrame::ChannelType> RelativeVolumeFrame::channels() const
{
  List<ChannelType> l;

  Map<ChannelType, ChannelData>::ConstIterator it = d->channels.begin();
  for(; it != d->channels.end(); ++it)
	l.append((*it).first);

  return l;
}

// deprecated

RelativeVolumeFrame::ChannelType RelativeVolumeFrame::channelType() const
{
  return MasterVolume;
}

// deprecated

void RelativeVolumeFrame::setChannelType(ChannelType)
{

}

short RelativeVolumeFrame::volumeAdjustmentIndex(ChannelType type) const
{
  return d->channels.contains(type) ? d->channels[type].volumeAdjustment : 0;
}

short RelativeVolumeFrame::volumeAdjustmentIndex() const
{
  return volumeAdjustmentIndex(MasterVolume);
}

void RelativeVolumeFrame::setVolumeAdjustmentIndex(short index, ChannelType type)
{
  d->channels[type].volumeAdjustment = index;
}

void RelativeVolumeFrame::setVolumeAdjustmentIndex(short index)
{
  setVolumeAdjustmentIndex(index, MasterVolume);
}

float RelativeVolumeFrame::volumeAdjustment(ChannelType type) const
{
  return d->channels.contains(type) ? float(d->channels[type].volumeAdjustment) / float(512) : 0;
}

float RelativeVolumeFrame::volumeAdjustment() const
{
  return volumeAdjustment(MasterVolume);
}

void RelativeVolumeFrame::setVolumeAdjustment(float adjustment, ChannelType type)
{
  d->channels[type].volumeAdjustment = short(adjustment * float(512));
}

void RelativeVolumeFrame::setVolumeAdjustment(float adjustment)
{
  setVolumeAdjustment(adjustment, MasterVolume);
}

RelativeVolumeFrame::PeakVolume RelativeVolumeFrame::peakVolume(ChannelType type) const
{
  return d->channels.contains(type) ? d->channels[type].peakVolume : PeakVolume();
}

RelativeVolumeFrame::PeakVolume RelativeVolumeFrame::peakVolume() const
{
  return peakVolume(MasterVolume);
}

void RelativeVolumeFrame::setPeakVolume(const PeakVolume &peak, ChannelType type)
{
  d->channels[type].peakVolume = peak;
}

void RelativeVolumeFrame::setPeakVolume(const PeakVolume &peak)
{
  setPeakVolume(peak, MasterVolume);
}

String RelativeVolumeFrame::identification() const
{
  return d->identification;
}

void RelativeVolumeFrame::setIdentification(const String &s)
{
  d->identification = s;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

void RelativeVolumeFrame::parseFields(const ByteVector &data)
{
  int pos = 0;
  d->identification = readStringField(data, String::Latin1, &pos);

  // Each channel is at least 4 bytes.

  while(pos <= (int)data.size() - 4) {

	ChannelType type = ChannelType(data[pos]);
	pos += 1;

	ChannelData &channel = d->channels[type];

	channel.volumeAdjustment = data.mid(pos, 2).toShort();
	pos += 2;

	channel.peakVolume.bitsRepresentingPeak = data[pos];
	pos += 1;

	int bytes = bitsToBytes(channel.peakVolume.bitsRepresentingPeak);
	channel.peakVolume.peakVolume = data.mid(pos, bytes);
	pos += bytes;
  }
}

ByteVector RelativeVolumeFrame::renderFields() const
{
  ByteVector data;

  data.append(d->identification.data(String::Latin1));
  data.append(textDelimiter(String::Latin1));

  Map<ChannelType, ChannelData>::ConstIterator it = d->channels.begin();

  for(; it != d->channels.end(); ++it) {
	ChannelType type = (*it).first;
	const ChannelData &channel = (*it).second;

	data.append(char(type));
	data.append(ByteVector::fromShort(channel.volumeAdjustment));
	data.append(char(channel.peakVolume.bitsRepresentingPeak));
	data.append(channel.peakVolume.peakVolume);
  }

  return data;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

RelativeVolumeFrame::RelativeVolumeFrame(const ByteVector &data, Header *h) : Frame(h)
{
  d = new RelativeVolumeFramePrivate;
  parseFields(fieldData(data));
}

/*** End of inlined file: relativevolumeframe.cpp ***/


/*** Start of inlined file: textidentificationframe.cpp ***/
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

using namespace TagLib;
using namespace ID3v2;

class TextIdentificationFrame::TextIdentificationFramePrivate
{
public:
  TextIdentificationFramePrivate() : textEncoding(String::Latin1) {}
  String::Type textEncoding;
  StringList fieldList;
};

////////////////////////////////////////////////////////////////////////////////
// TextIdentificationFrame public members
////////////////////////////////////////////////////////////////////////////////

TextIdentificationFrame::TextIdentificationFrame(const ByteVector &type, String::Type encoding) :
  Frame(type)
{
  d = new TextIdentificationFramePrivate;
  d->textEncoding = encoding;
}

TextIdentificationFrame::TextIdentificationFrame(const ByteVector &data) :
  Frame(data)
{
  d = new TextIdentificationFramePrivate;
  setData(data);
}

TextIdentificationFrame *TextIdentificationFrame::createTIPLFrame(const PropertyMap &properties) // static
{
  TextIdentificationFrame *frame = new TextIdentificationFrame("TIPL");
  StringList l;
  for(PropertyMap::ConstIterator it = properties.begin(); it != properties.end(); ++it){
	l.append(it->first);
	l.append(it->second.toString(",")); // comma-separated list of names
  }
  frame->setText(l);
  return frame;
}

TextIdentificationFrame *TextIdentificationFrame::createTMCLFrame(const PropertyMap &properties) // static
{
  TextIdentificationFrame *frame = new TextIdentificationFrame("TMCL");
  StringList l;
  for(PropertyMap::ConstIterator it = properties.begin(); it != properties.end(); ++it){
	if(!it->first.startsWith(instrumentPrefix)) // should not happen
	  continue;
	l.append(it->first.substr(instrumentPrefix.size()));
	l.append(it->second.toString(","));
  }
  frame->setText(l);
  return frame;
}

TextIdentificationFrame::~TextIdentificationFrame()
{
  delete d;
}

void TextIdentificationFrame::setText(const StringList &l)
{
  d->fieldList = l;
}

void TextIdentificationFrame::setText(const String &s)
{
  d->fieldList = s;
}

String TextIdentificationFrame::toString() const
{
  return d->fieldList.toString();
}

StringList TextIdentificationFrame::fieldList() const
{
  return d->fieldList;
}

String::Type TextIdentificationFrame::textEncoding() const
{
  return d->textEncoding;
}

void TextIdentificationFrame::setTextEncoding(String::Type encoding)
{
  d->textEncoding = encoding;
}

// array of allowed TIPL prefixes and their corresponding key value
static const TagLib::uint involvedPeopleSize = 5;
static const char* involvedPeople[][2] = {
	{"ARRANGER", "ARRANGER"},
	{"ENGINEER", "ENGINEER"},
	{"PRODUCER", "PRODUCER"},
	{"DJ-MIX", "DJMIXER"},
	{"MIX", "MIXER"},
};

const KeyConversionMap &TextIdentificationFrame::involvedPeopleMap() // static
{
  static KeyConversionMap m;
  if(m.isEmpty())
	for(uint i = 0; i < involvedPeopleSize; ++i)
	  m.insert(involvedPeople[i][1], involvedPeople[i][0]);
  return m;
}

PropertyMap TextIdentificationFrame::asProperties() const
{
  if(frameID() == "TIPL")
	return makeTIPLProperties();
  if(frameID() == "TMCL")
	return makeTMCLProperties();
  PropertyMap map;
  String tagName = frameIDToKey(frameID());
  if(tagName.isNull()) {
	map.unsupportedData().append(frameID());
	return map;
  }
  StringList values = fieldList();
  if(tagName == "GENRE") {
	// Special case: Support ID3v1-style genre numbers. They are not officially supported in
	// ID3v2, however it seems that still a lot of programs use them.
	for(StringList::Iterator it = values.begin(); it != values.end(); ++it) {
	  bool ok = false;
	  int test = it->toInt(&ok); // test if the genre value is an integer
	  if(ok)
		*it = ID3v1::genre(test);
	}
  } else if(tagName == "DATE") {
	for(StringList::Iterator it = values.begin(); it != values.end(); ++it) {
	  // ID3v2 specifies ISO8601 timestamps which contain a 'T' as separator between date and time.
	  // Since this is unusual in other formats, the T is removed.
	  int tpos = it->find("T");
	  if(tpos != -1)
		(*it)[tpos] = ' ';
	}
  }
  PropertyMap ret;
  ret.insert(tagName, values);
  return ret;
}

////////////////////////////////////////////////////////////////////////////////
// TextIdentificationFrame protected members
////////////////////////////////////////////////////////////////////////////////

void TextIdentificationFrame::parseFields(const ByteVector &data)
{
  // Don't try to parse invalid frames

  if(data.size() < 2)
	return;

  // read the string data type (the first byte of the field data)

  d->textEncoding = String::Type(data[0]);

  // split the byte array into chunks based on the string type (two byte delimiter
  // for unicode encodings)

  int byteAlign = d->textEncoding == String::Latin1 || d->textEncoding == String::UTF8 ? 1 : 2;

  // build a small counter to strip nulls off the end of the field

  int dataLength = data.size() - 1;

  while(dataLength > 0 && data[dataLength] == 0)
	dataLength--;

  while(dataLength % byteAlign != 0)
	dataLength++;

  ByteVectorList l = ByteVectorList::split(data.mid(1, dataLength), textDelimiter(d->textEncoding), byteAlign);

  d->fieldList.clear();

  // append those split values to the list and make sure that the new string's
  // type is the same specified for this frame

  for(ByteVectorList::Iterator it = l.begin(); it != l.end(); it++) {
	if(!(*it).isEmpty()) {
	  String s(*it, d->textEncoding);
	  d->fieldList.append(s);
	}
  }
}

ByteVector TextIdentificationFrame::renderFields() const
{
  String::Type encoding = checkTextEncoding(d->fieldList, d->textEncoding);

  ByteVector v;

  v.append(char(encoding));

  for(StringList::ConstIterator it = d->fieldList.begin(); it != d->fieldList.end(); it++) {

	// Since the field list is null delimited, if this is not the first
	// element in the list, append the appropriate delimiter for this
	// encoding.

	if(it != d->fieldList.begin())
	  v.append(textDelimiter(encoding));

	v.append((*it).data(encoding));
  }

  return v;
}

////////////////////////////////////////////////////////////////////////////////
// TextIdentificationFrame private members
////////////////////////////////////////////////////////////////////////////////

TextIdentificationFrame::TextIdentificationFrame(const ByteVector &data, Header *h) : Frame(h)
{
  d = new TextIdentificationFramePrivate;
  parseFields(fieldData(data));
}

PropertyMap TextIdentificationFrame::makeTIPLProperties() const
{
  PropertyMap map;
  if(fieldList().size() % 2 != 0){
	// according to the ID3 spec, TIPL must contain an even number of entries
	map.unsupportedData().append(frameID());
	return map;
  }
  StringList l = fieldList();
  for(StringList::ConstIterator it = l.begin(); it != l.end(); ++it) {
	bool found = false;
	for(uint i = 0; i < involvedPeopleSize; ++i)
	  if(*it == involvedPeople[i][0]) {
		map.insert(involvedPeople[i][1], (++it)->split(","));
		found = true;
		break;
	  }
	if(!found){
	  // invalid involved role -> mark whole frame as unsupported in order to be consisten with writing
	  map.clear();
	  map.unsupportedData().append(frameID());
	  return map;
	}
  }
  return map;
}

PropertyMap TextIdentificationFrame::makeTMCLProperties() const
{
  PropertyMap map;
  if(fieldList().size() % 2 != 0){
	// according to the ID3 spec, TMCL must contain an even number of entries
	map.unsupportedData().append(frameID());
	return map;
  }
  StringList l = fieldList();
  for(StringList::ConstIterator it = l.begin(); it != l.end(); ++it) {
	String instrument = PropertyMap::prepareKey(*it);
	if(instrument.isNull()) {
	  // instrument is not a valid key -> frame unsupported
	  map.clear();
	  map.unsupportedData().append(frameID());
	  return map;
	}
	map.insert(L"PERFORMER:" + instrument, (++it)->split(","));
  }
  return map;
}

////////////////////////////////////////////////////////////////////////////////
// UserTextIdentificationFrame public members
////////////////////////////////////////////////////////////////////////////////

UserTextIdentificationFrame::UserTextIdentificationFrame(String::Type encoding) :
  TextIdentificationFrame("TXXX", encoding),
  d(0)
{
  StringList l;
  l.append(String::null);
  l.append(String::null);
  setText(l);
}

UserTextIdentificationFrame::UserTextIdentificationFrame(const ByteVector &data) :
  TextIdentificationFrame(data)
{
  checkFields();
}

UserTextIdentificationFrame::UserTextIdentificationFrame(const String &description, const StringList &values, String::Type encoding) :
	TextIdentificationFrame("TXXX", encoding),
	d(0)
{
  setDescription(description);
  setText(values);
}

String UserTextIdentificationFrame::toString() const
{
  return "[" + description() + "] " + fieldList().toString();
}

String UserTextIdentificationFrame::description() const
{
  return !TextIdentificationFrame::fieldList().isEmpty()
	? TextIdentificationFrame::fieldList().front()
	: String::null;
}

StringList UserTextIdentificationFrame::fieldList() const
{
  // TODO: remove this function

  return TextIdentificationFrame::fieldList();
}

void UserTextIdentificationFrame::setText(const String &text)
{
  if(description().isEmpty())
	setDescription(String::null);

  TextIdentificationFrame::setText(StringList(description()).append(text));
}

void UserTextIdentificationFrame::setText(const StringList &fields)
{
  if(description().isEmpty())
	setDescription(String::null);

  TextIdentificationFrame::setText(StringList(description()).append(fields));
}

void UserTextIdentificationFrame::setDescription(const String &s)
{
  StringList l = fieldList();

  if(l.isEmpty())
	l.append(s);
  else
	l[0] = s;

  TextIdentificationFrame::setText(l);
}

PropertyMap UserTextIdentificationFrame::asProperties() const
{
  String tagName = description();

  PropertyMap map;
  String key = map.prepareKey(tagName);
  if(key.isNull()) // this frame's description is not a valid PropertyMap key -> add to unsupported list
	map.unsupportedData().append(L"TXXX/" + description());
  else {
	StringList v = fieldList();
	for(StringList::ConstIterator it = v.begin(); it != v.end(); ++it)
	  if(*it != description())
		map.insert(key, *it);
  }
  return map;
}

UserTextIdentificationFrame *UserTextIdentificationFrame::find(
  ID3v2::Tag *tag, const String &description) // static
{
  FrameList l = tag->frameList("TXXX");
  for(FrameList::Iterator it = l.begin(); it != l.end(); ++it) {
	UserTextIdentificationFrame *f = dynamic_cast<UserTextIdentificationFrame *>(*it);
	if(f && f->description() == description)
	  return f;
  }
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
// UserTextIdentificationFrame private members
////////////////////////////////////////////////////////////////////////////////

UserTextIdentificationFrame::UserTextIdentificationFrame(const ByteVector &data, Header *h) :
  TextIdentificationFrame(data, h)
{
  checkFields();
}

void UserTextIdentificationFrame::checkFields()
{
  int fields = fieldList().size();

  if(fields == 0)
	setDescription(String::null);
  if(fields <= 1)
	setText(String::null);
}

/*** End of inlined file: textidentificationframe.cpp ***/


/*** Start of inlined file: uniquefileidentifierframe.cpp ***/
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

using namespace TagLib;
using namespace ID3v2;

class UniqueFileIdentifierFrame::UniqueFileIdentifierFramePrivate
{
public:
  String owner;
  ByteVector identifier;
};

////////////////////////////////////////////////////////////////////////////////
// public methods
////////////////////////////////////////////////////////////////////////////////

UniqueFileIdentifierFrame::UniqueFileIdentifierFrame(const ByteVector &data) :
	ID3v2::Frame(data)
{
  d = new UniqueFileIdentifierFramePrivate;
  setData(data);
}

UniqueFileIdentifierFrame::UniqueFileIdentifierFrame(const String &owner, const ByteVector &id) :
	ID3v2::Frame("UFID")
{
  d = new UniqueFileIdentifierFramePrivate;
  d->owner = owner;
  d->identifier = id;
}

UniqueFileIdentifierFrame::~UniqueFileIdentifierFrame()
{
  delete d;
}

String UniqueFileIdentifierFrame::owner() const
{
	return d->owner;
}

ByteVector UniqueFileIdentifierFrame::identifier() const
{
  return d->identifier;
}

void UniqueFileIdentifierFrame::setOwner(const String &s)
{
  d->owner = s;
}

void UniqueFileIdentifierFrame::setIdentifier(const ByteVector &v)
{
  d->identifier = v;
}

String UniqueFileIdentifierFrame::toString() const
{
  return String::null;
}

void UniqueFileIdentifierFrame::parseFields(const ByteVector &data)
{
  if(data.size() < 1) {
	debug("An UFID frame must contain at least 1 byte.");
	return;
  }

  int pos = 0;
  d->owner = readStringField(data, String::Latin1, &pos);
  d->identifier = data.mid(pos);
}

ByteVector UniqueFileIdentifierFrame::renderFields() const
{
  ByteVector data;

  data.append(d->owner.data(String::Latin1));
  data.append(char(0));
  data.append(d->identifier);

  return data;
}

UniqueFileIdentifierFrame::UniqueFileIdentifierFrame(const ByteVector &data, Header *h) :
  Frame(h)
{
  d = new UniqueFileIdentifierFramePrivate;
  parseFields(fieldData(data));
}

/*** End of inlined file: uniquefileidentifierframe.cpp ***/


/*** Start of inlined file: unknownframe.cpp ***/
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

using namespace TagLib;
using namespace ID3v2;

class UnknownFrame::UnknownFramePrivate
{
public:
  ByteVector fieldData;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

UnknownFrame::UnknownFrame(const ByteVector &data) : Frame(data)
{
  d = new UnknownFramePrivate;
  setData(data);
}

UnknownFrame::~UnknownFrame()
{
  delete d;
}

String UnknownFrame::toString() const
{
  return String::null;
}

ByteVector UnknownFrame::data() const
{
  return d->fieldData;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

void UnknownFrame::parseFields(const ByteVector &data)
{
  d->fieldData = data;
}

ByteVector UnknownFrame::renderFields() const
{
  return d->fieldData;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

UnknownFrame::UnknownFrame(const ByteVector &data, Header *h) : Frame(h)
{
  d = new UnknownFramePrivate;
  parseFields(fieldData(data));
}

/*** End of inlined file: unknownframe.cpp ***/


/*** Start of inlined file: unsynchronizedlyricsframe.cpp ***/
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

using namespace TagLib;
using namespace ID3v2;

class UnsynchronizedLyricsFrame::UnsynchronizedLyricsFramePrivate
{
public:
  UnsynchronizedLyricsFramePrivate() : textEncoding(String::Latin1) {}
  String::Type textEncoding;
  ByteVector language;
  String description;
  String text;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

UnsynchronizedLyricsFrame::UnsynchronizedLyricsFrame(String::Type encoding) :
  Frame("USLT")
{
  d = new UnsynchronizedLyricsFramePrivate;
  d->textEncoding = encoding;
}

UnsynchronizedLyricsFrame::UnsynchronizedLyricsFrame(const ByteVector &data) :
  Frame(data)
{
  d = new UnsynchronizedLyricsFramePrivate;
  setData(data);
}

UnsynchronizedLyricsFrame::~UnsynchronizedLyricsFrame()
{
  delete d;
}

String UnsynchronizedLyricsFrame::toString() const
{
  return d->text;
}

ByteVector UnsynchronizedLyricsFrame::language() const
{
  return d->language;
}

String UnsynchronizedLyricsFrame::description() const
{
  return d->description;
}

String UnsynchronizedLyricsFrame::text() const
{
  return d->text;
}

void UnsynchronizedLyricsFrame::setLanguage(const ByteVector &languageEncoding)
{
  d->language = languageEncoding.mid(0, 3);
}

void UnsynchronizedLyricsFrame::setDescription(const String &s)
{
  d->description = s;
}

void UnsynchronizedLyricsFrame::setText(const String &s)
{
  d->text = s;
}

String::Type UnsynchronizedLyricsFrame::textEncoding() const
{
  return d->textEncoding;
}

void UnsynchronizedLyricsFrame::setTextEncoding(String::Type encoding)
{
  d->textEncoding = encoding;
}

PropertyMap UnsynchronizedLyricsFrame::asProperties() const
{
  PropertyMap map;
  String key = PropertyMap::prepareKey(description());
  if(key.isEmpty() || key.upper() == "LYRICS")
	map.insert("LYRICS", text());
  else if(key.isNull())
	map.unsupportedData().append(L"USLT/" + description());
  else
	map.insert("LYRICS:" + key, text());
  return map;
}

UnsynchronizedLyricsFrame *UnsynchronizedLyricsFrame::findByDescription(const ID3v2::Tag *tag, const String &d) // static
{
  ID3v2::FrameList lyrics = tag->frameList("USLT");

  for(ID3v2::FrameList::ConstIterator it = lyrics.begin(); it != lyrics.end(); ++it){
	UnsynchronizedLyricsFrame *frame = dynamic_cast<UnsynchronizedLyricsFrame *>(*it);
	if(frame && frame->description() == d)
	  return frame;
  }
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

void UnsynchronizedLyricsFrame::parseFields(const ByteVector &data)
{
  if(data.size() < 5) {
	debug("An unsynchronized lyrics frame must contain at least 5 bytes.");
	return;
  }

  d->textEncoding = String::Type(data[0]);
  d->language = data.mid(1, 3);

  int byteAlign
	= d->textEncoding == String::Latin1 || d->textEncoding == String::UTF8 ? 1 : 2;

  ByteVectorList l =
	ByteVectorList::split(data.mid(4), textDelimiter(d->textEncoding), byteAlign, 2);

  if(l.size() == 2) {
	d->description = String(l.front(), d->textEncoding);
	d->text = String(l.back(), d->textEncoding);
  }
}

ByteVector UnsynchronizedLyricsFrame::renderFields() const
{
  ByteVector v;

  v.append(char(d->textEncoding));
  v.append(d->language.size() == 3 ? d->language : "XXX");
  v.append(d->description.data(d->textEncoding));
  v.append(textDelimiter(d->textEncoding));
  v.append(d->text.data(d->textEncoding));

  return v;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

UnsynchronizedLyricsFrame::UnsynchronizedLyricsFrame(const ByteVector &data, Header *h)
  : Frame(h)
{
  d = new UnsynchronizedLyricsFramePrivate();
  parseFields(fieldData(data));
}

/*** End of inlined file: unsynchronizedlyricsframe.cpp ***/


/*** Start of inlined file: urllinkframe.cpp ***/
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

using namespace TagLib;
using namespace ID3v2;

class UrlLinkFrame::UrlLinkFramePrivate
{
public:
  String url;
};

class UserUrlLinkFrame::UserUrlLinkFramePrivate
{
public:
  UserUrlLinkFramePrivate() : textEncoding(String::Latin1) {}
  String::Type textEncoding;
  String description;
};

UrlLinkFrame::UrlLinkFrame(const ByteVector &data) :
  Frame(data)
{
  d = new UrlLinkFramePrivate;
  setData(data);
}

UrlLinkFrame::~UrlLinkFrame()
{
  delete d;
}

void UrlLinkFrame::setUrl(const String &s)
{
  d->url = s;
}

String UrlLinkFrame::url() const
{
  return d->url;
}

void UrlLinkFrame::setText(const String &s)
{
  setUrl(s);
}

String UrlLinkFrame::toString() const
{
  return url();
}

PropertyMap UrlLinkFrame::asProperties() const
{
  String key = frameIDToKey(frameID());
  PropertyMap map;
  if(key.isNull())
	// unknown W*** frame - this normally shouldn't happen
	map.unsupportedData().append(frameID());
  else
	map.insert(key, url());
  return map;
}

void UrlLinkFrame::parseFields(const ByteVector &data)
{
  d->url = String(data);
}

ByteVector UrlLinkFrame::renderFields() const
{
  return d->url.data(String::Latin1);
}

UrlLinkFrame::UrlLinkFrame(const ByteVector &data, Header *h) : Frame(h)
{
  d = new UrlLinkFramePrivate;
  parseFields(fieldData(data));
}

UserUrlLinkFrame::UserUrlLinkFrame(String::Type encoding) :
  UrlLinkFrame("WXXX")
{
  d = new UserUrlLinkFramePrivate;
  d->textEncoding = encoding;
}

UserUrlLinkFrame::UserUrlLinkFrame(const ByteVector &data) :
  UrlLinkFrame(data)
{
  d = new UserUrlLinkFramePrivate;
  setData(data);
}

UserUrlLinkFrame::~UserUrlLinkFrame()
{
  delete d;
}

String UserUrlLinkFrame::toString() const
{
  return "[" + description() + "] " + url();
}

String::Type UserUrlLinkFrame::textEncoding() const
{
  return d->textEncoding;
}

void UserUrlLinkFrame::setTextEncoding(String::Type encoding)
{
  d->textEncoding = encoding;
}

String UserUrlLinkFrame::description() const
{
  return d->description;
}

void UserUrlLinkFrame::setDescription(const String &s)
{
  d->description = s;
}

PropertyMap UserUrlLinkFrame::asProperties() const
{
  PropertyMap map;
  String key = PropertyMap::prepareKey(description());
  if(key.isEmpty() || key.upper() == "URL")
	map.insert("URL", url());
  else if(key.isNull())
	map.unsupportedData().append(L"WXXX/" + description());
  else
	map.insert("URL:" + key, url());
  return map;
}

UserUrlLinkFrame *UserUrlLinkFrame::find(ID3v2::Tag *tag, const String &description) // static
{
  FrameList l = tag->frameList("WXXX");
  for(FrameList::Iterator it = l.begin(); it != l.end(); ++it) {
	UserUrlLinkFrame *f = dynamic_cast<UserUrlLinkFrame *>(*it);
	if(f && f->description() == description)
	  return f;
  }
  return 0;
}

void UserUrlLinkFrame::parseFields(const ByteVector &data)
{
  if(data.size() < 2) {
	debug("A user URL link frame must contain at least 2 bytes.");
	return;
  }

  int pos = 0;

  d->textEncoding = String::Type(data[0]);
  pos += 1;

  if(d->textEncoding == String::Latin1 || d->textEncoding == String::UTF8) {
	int offset = data.find(textDelimiter(d->textEncoding), pos);
	if(offset < pos)
	  return;

	d->description = String(data.mid(pos, offset - pos), d->textEncoding);
	pos = offset + 1;
  }
  else {
	int len = data.mid(pos).find(textDelimiter(d->textEncoding), 0, 2);
	if(len < 0)
	  return;

	d->description = String(data.mid(pos, len), d->textEncoding);
	pos += len + 2;
  }

  setUrl(String(data.mid(pos)));
}

ByteVector UserUrlLinkFrame::renderFields() const
{
  ByteVector v;

  String::Type encoding = checkTextEncoding(d->description, d->textEncoding);

  v.append(char(encoding));
  v.append(d->description.data(encoding));
  v.append(textDelimiter(encoding));
  v.append(url().data(String::Latin1));

  return v;
}

UserUrlLinkFrame::UserUrlLinkFrame(const ByteVector &data, Header *h) : UrlLinkFrame(data, h)
{
  d = new UserUrlLinkFramePrivate;
  parseFields(fieldData(data));
}

/*** End of inlined file: urllinkframe.cpp ***/


/*** Start of inlined file: oggfile.cpp ***/
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

using namespace TagLib;

class Ogg::File::FilePrivate
{
public:
  FilePrivate() :
	streamSerialNumber(0),
	firstPageHeader(0),
	lastPageHeader(0),
	currentPage(0),
	currentPacketPage(0)
  {
	pages.setAutoDelete(true);
  }

  ~FilePrivate()
  {
	delete firstPageHeader;
	delete lastPageHeader;
  }

  uint streamSerialNumber;
  List<Page *> pages;
  PageHeader *firstPageHeader;
  PageHeader *lastPageHeader;
  std::vector< List<int> > packetToPageMap;
  Map<int, ByteVector> dirtyPackets;
  List<int> dirtyPages;

  //! The current page for the reader -- used by nextPage()
  Page *currentPage;
  //! The current page for the packet parser -- used by packet()
  Page *currentPacketPage;
  //! The packets for the currentPacketPage -- used by packet()
  ByteVectorList currentPackets;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

Ogg::File::~File()
{
  delete d;
}

ByteVector Ogg::File::packet(uint i)
{
  // Check to see if we're called setPacket() for this packet since the last
  // save:

  if(d->dirtyPackets.contains(i))
	return d->dirtyPackets[i];

  // If we haven't indexed the page where the packet we're interested in starts,
  // begin reading pages until we have.

  while(d->packetToPageMap.size() <= i) {
	if(!nextPage()) {
	  debug("Ogg::File::packet() -- Could not find the requested packet.");
	  return ByteVector::null;
	}
  }

  // Start reading at the first page that contains part (or all) of this packet.
  // If the last read stopped at the packet that we're interested in, don't
  // reread its packet list.  (This should make sequential packet reads fast.)

  uint pageIndex = d->packetToPageMap[i].front();
  if(d->currentPacketPage != d->pages[pageIndex]) {
	d->currentPacketPage = d->pages[pageIndex];
	d->currentPackets = d->currentPacketPage->packets();
  }

  // If the packet is completely contained in the first page that it's in, then
  // just return it now.

  if(d->currentPacketPage->containsPacket(i) & Page::CompletePacket)
	return d->currentPackets[i - d->currentPacketPage->firstPacketIndex()];

  // If the packet is *not* completely contained in the first page that it's a
  // part of then that packet trails off the end of the page.  Continue appending
  // the pages' packet data until we hit a page that either does not end with the
  // packet that we're fetching or where the last packet is complete.

  ByteVector packet = d->currentPackets.back();
  while(d->currentPacketPage->containsPacket(i) & Page::EndsWithPacket &&
		!d->currentPacketPage->header()->lastPacketCompleted())
  {
	pageIndex++;
	if(pageIndex == d->pages.size()) {
	  if(!nextPage()) {
		debug("Ogg::File::packet() -- Could not find the requested packet.");
		return ByteVector::null;
	  }
	}
	d->currentPacketPage = d->pages[pageIndex];
	d->currentPackets = d->currentPacketPage->packets();
	packet.append(d->currentPackets.front());
  }

  return packet;
}

void Ogg::File::setPacket(uint i, const ByteVector &p)
{
  while(d->packetToPageMap.size() <= i) {
	if(!nextPage()) {
	  debug("Ogg::File::setPacket() -- Could not set the requested packet.");
	  return;
	}
  }

  List<int>::ConstIterator it = d->packetToPageMap[i].begin();
  for(; it != d->packetToPageMap[i].end(); ++it)
	d->dirtyPages.sortedInsert(*it, true);

  d->dirtyPackets.insert(i, p);
}

const Ogg::PageHeader *Ogg::File::firstPageHeader()
{
  if(d->firstPageHeader)
	return d->firstPageHeader->isValid() ? d->firstPageHeader : 0;

  long firstPageHeaderOffset = find("OggS");

  if(firstPageHeaderOffset < 0)
	return 0;

  d->firstPageHeader = new PageHeader(this, firstPageHeaderOffset);
  return d->firstPageHeader->isValid() ? d->firstPageHeader : 0;
}

const Ogg::PageHeader *Ogg::File::lastPageHeader()
{
  if(d->lastPageHeader)
	return d->lastPageHeader->isValid() ? d->lastPageHeader : 0;

  long lastPageHeaderOffset = rfind("OggS");

  if(lastPageHeaderOffset < 0)
	return 0;

  d->lastPageHeader = new PageHeader(this, lastPageHeaderOffset);
  return d->lastPageHeader->isValid() ? d->lastPageHeader : 0;
}

bool Ogg::File::save()
{
  if(readOnly()) {
	debug("Ogg::File::save() - Cannot save to a read only file.");
	return false;
  }

  List<int> pageGroup;

  for(List<int>::ConstIterator it = d->dirtyPages.begin(); it != d->dirtyPages.end(); ++it) {
	if(!pageGroup.isEmpty() && pageGroup.back() + 1 != *it) {
	  writePageGroup(pageGroup);
	  pageGroup.clear();
	}
	else
	  pageGroup.append(*it);
  }
  writePageGroup(pageGroup);
  d->dirtyPages.clear();
  d->dirtyPackets.clear();

  return true;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

Ogg::File::File(FileName file) : TagLib::File(file)
{
  d = new FilePrivate;
}

Ogg::File::File(IOStream *stream) : TagLib::File(stream)
{
  d = new FilePrivate;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

bool Ogg::File::nextPage()
{
  long nextPageOffset;
  int currentPacket;

  if(d->pages.isEmpty()) {
	currentPacket = 0;
	nextPageOffset = find("OggS");
	if(nextPageOffset < 0)
	  return false;
  }
  else {
	if(d->currentPage->header()->lastPageOfStream())
	  return false;

	if(d->currentPage->header()->lastPacketCompleted())
	  currentPacket = d->currentPage->firstPacketIndex() + d->currentPage->packetCount();
	else
	  currentPacket = d->currentPage->firstPacketIndex() + d->currentPage->packetCount() - 1;

	nextPageOffset = d->currentPage->fileOffset() + d->currentPage->size();
  }

  // Read the next page and add it to the page list.

  d->currentPage = new Page(this, nextPageOffset);

  if(!d->currentPage->header()->isValid()) {
	delete d->currentPage;
	d->currentPage = 0;
	return false;
  }

  d->currentPage->setFirstPacketIndex(currentPacket);

  if(d->pages.isEmpty())
	d->streamSerialNumber = d->currentPage->header()->streamSerialNumber();

  d->pages.append(d->currentPage);

  // Loop through the packets in the page that we just read appending the
  // current page number to the packet to page map for each packet.

  for(uint i = 0; i < d->currentPage->packetCount(); i++) {
	uint currentPacket = d->currentPage->firstPacketIndex() + i;
	if(d->packetToPageMap.size() <= currentPacket)
	  d->packetToPageMap.push_back(List<int>());
	d->packetToPageMap[currentPacket].append(d->pages.size() - 1);
  }

  return true;
}

void Ogg::File::writePageGroup(const List<int> &thePageGroup)
{
  if(thePageGroup.isEmpty())
	return;

  // pages in the pageGroup and packets must be equivalent
  // (originalSize and size of packets would not work together),
  // therefore we sometimes have to add pages to the group
  List<int> pageGroup(thePageGroup);
  while (!d->pages[pageGroup.back()]->header()->lastPacketCompleted()) {
	if (d->currentPage->header()->pageSequenceNumber() == pageGroup.back()) {
	  if (nextPage() == false) {
		debug("broken ogg file");
		return;
	  }
	  pageGroup.append(d->currentPage->header()->pageSequenceNumber());
	} else {
	  pageGroup.append(pageGroup.back() + 1);
	}
  }

  ByteVectorList packets;

  // If the first page of the group isn't dirty, append its partial content here.

  if(!d->dirtyPages.contains(d->pages[pageGroup.front()]->firstPacketIndex()))
	packets.append(d->pages[pageGroup.front()]->packets().front());

  int previousPacket = -1;
  int originalSize = 0;

  for(List<int>::ConstIterator it = pageGroup.begin(); it != pageGroup.end(); ++it) {
	uint firstPacket = d->pages[*it]->firstPacketIndex();
	uint lastPacket = firstPacket + d->pages[*it]->packetCount() - 1;

	List<int>::ConstIterator last = --pageGroup.end();

	for(uint i = firstPacket; i <= lastPacket; i++) {

	  if(it == last && i == lastPacket && !d->dirtyPages.contains(i))
		packets.append(d->pages[*it]->packets().back());
	  else if(int(i) != previousPacket) {
		previousPacket = i;
		packets.append(packet(i));
	  }
	}
	originalSize += d->pages[*it]->size();
  }

  const bool continued = d->pages[pageGroup.front()]->header()->firstPacketContinued();
  const bool completed = d->pages[pageGroup.back()]->header()->lastPacketCompleted();

  // TODO: This pagination method isn't accurate for what's being done here.
  // This should account for real possibilities like non-aligned packets and such.

  List<Page *> pages = Page::paginate(packets, Page::SinglePagePerGroup,
									  d->streamSerialNumber, pageGroup.front(),
									  continued, completed);

  List<Page *> renumberedPages;

  // Correct the page numbering of following pages

  if (pages.back()->header()->pageSequenceNumber() != pageGroup.back()) {

	// TODO: change the internal data structure so that we don't need to hold the
	// complete file in memory (is unavoidable at the moment)

	// read the complete stream
	while(!d->currentPage->header()->lastPageOfStream()) {
	  if(nextPage() == false) {
		debug("broken ogg file");
		break;
	  }
	}

	// create a gap for the new pages
	int numberOfNewPages = pages.back()->header()->pageSequenceNumber() - pageGroup.back();
	List<Page *>::Iterator pageIter = d->pages.begin();
	for(int i = 0; i < pageGroup.back(); i++) {
	  if(pageIter != d->pages.end()) {
		++pageIter;
	  }
	  else {
		debug("Ogg::File::writePageGroup() -- Page sequence is broken in original file.");
		break;
	  }
	}

	++pageIter;
	for(; pageIter != d->pages.end(); ++pageIter) {
	  Ogg::Page *newPage =
		(*pageIter)->getCopyWithNewPageSequenceNumber(
			(*pageIter)->header()->pageSequenceNumber() + numberOfNewPages);

	  ByteVector data;
	  data.append(newPage->render());
	  insert(data, newPage->fileOffset(), data.size());

	  renumberedPages.append(newPage);
	}
  }

  // insert the new data

  ByteVector data;
  for(List<Page *>::ConstIterator it = pages.begin(); it != pages.end(); ++it)
	data.append((*it)->render());

  // The insertion algorithms could also be improve to queue and prioritize data
  // on the way out.  Currently it requires rewriting the file for every page
  // group rather than just once; however, for tagging applications there will
  // generally only be one page group, so it's not worth the time for the
  // optimization at the moment.

  insert(data, d->pages[pageGroup.front()]->fileOffset(), originalSize);

  // Update the page index to include the pages we just created and to delete the
  // old pages.

  // First step: Pages that contain the comment data

  for(List<Page *>::ConstIterator it = pages.begin(); it != pages.end(); ++it) {
	const unsigned int index = (*it)->header()->pageSequenceNumber();
	if(index < d->pages.size()) {
	  delete d->pages[index];
	  d->pages[index] = *it;
	}
	else if(index == d->pages.size()) {
	  d->pages.append(*it);
	}
	else {
	  // oops - there's a hole in the sequence
	  debug("Ogg::File::writePageGroup() -- Page sequence is broken.");
	}
  }

  // Second step: the renumbered pages

  for(List<Page *>::ConstIterator it = renumberedPages.begin(); it != renumberedPages.end(); ++it) {
	const unsigned int index = (*it)->header()->pageSequenceNumber();
	if(index < d->pages.size()) {
	  delete d->pages[index];
	  d->pages[index] = *it;
	}
	else if(index == d->pages.size()) {
	  d->pages.append(*it);
	}
	else {
	  // oops - there's a hole in the sequence
	  debug("Ogg::File::writePageGroup() -- Page sequence is broken.");
	}
  }
}

/*** End of inlined file: oggfile.cpp ***/


/*** Start of inlined file: oggpage.cpp ***/
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

using namespace TagLib;

class Ogg::Page::PagePrivate
{
public:
  PagePrivate(File *f = 0, long pageOffset = -1) :
	file(f),
	fileOffset(pageOffset),
	packetOffset(0),
	header(f, pageOffset),
	firstPacketIndex(-1)
  {
	if(file) {
	  packetOffset = fileOffset + header.size();
	  packetSizes = header.packetSizes();
	  dataSize = header.dataSize();
	}
  }

  File *file;
  long fileOffset;
  long packetOffset;
  int dataSize;
  List<int> packetSizes;
  PageHeader header;
  int firstPacketIndex;
  ByteVectorList packets;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

Ogg::Page::Page(Ogg::File *file, long pageOffset)
{
  d = new PagePrivate(file, pageOffset);
}

Ogg::Page::~Page()
{
  delete d;
}

long Ogg::Page::fileOffset() const
{
  return d->fileOffset;
}

const Ogg::PageHeader *Ogg::Page::header() const
{
  return &d->header;
}

int Ogg::Page::firstPacketIndex() const
{
  return d->firstPacketIndex;
}

void Ogg::Page::setFirstPacketIndex(int index)
{
  d->firstPacketIndex = index;
}

Ogg::Page::ContainsPacketFlags Ogg::Page::containsPacket(int index) const
{
  int lastPacketIndex = d->firstPacketIndex + packetCount() - 1;
  if(index < d->firstPacketIndex || index > lastPacketIndex)
	return DoesNotContainPacket;

  ContainsPacketFlags flags = DoesNotContainPacket;

  if(index == d->firstPacketIndex)
	flags = ContainsPacketFlags(flags | BeginsWithPacket);

  if(index == lastPacketIndex)
	flags = ContainsPacketFlags(flags | EndsWithPacket);

  // If there's only one page and it's complete:

  if(packetCount() == 1 &&
	 !d->header.firstPacketContinued() &&
	 d->header.lastPacketCompleted())
  {
	flags = ContainsPacketFlags(flags | CompletePacket);
  }

  // Or if there is more than one page and the page is
  // (a) the first page and it's complete or
  // (b) the last page and it's complete or
  // (c) a page in the middle.
  else if(packetCount() > 1 &&
		  ((flags & BeginsWithPacket && !d->header.firstPacketContinued()) ||
		   (flags & EndsWithPacket && d->header.lastPacketCompleted()) ||
		   (!(flags & BeginsWithPacket) && !(flags & EndsWithPacket))))
  {
	flags = ContainsPacketFlags(flags | CompletePacket);
  }

  return flags;
}

TagLib::uint Ogg::Page::packetCount() const
{
  return d->header.packetSizes().size();
}

ByteVectorList Ogg::Page::packets() const
{
  if(!d->packets.isEmpty())
	return d->packets;

  ByteVectorList l;

  if(d->file && d->header.isValid()) {

	d->file->seek(d->packetOffset);

	List<int> packetSizes = d->header.packetSizes();

	List<int>::ConstIterator it = packetSizes.begin();
	for(; it != packetSizes.end(); ++it)
	  l.append(d->file->readBlock(*it));
  }
  else
	debug("Ogg::Page::packets() -- attempting to read packets from an invalid page.");

  return l;
}

int Ogg::Page::size() const
{
  return d->header.size() + d->header.dataSize();
}

ByteVector Ogg::Page::render() const
{
  ByteVector data;

  data.append(d->header.render());

  if(d->packets.isEmpty()) {
	if(d->file) {
	  d->file->seek(d->packetOffset);
	  data.append(d->file->readBlock(d->dataSize));
	}
	else
	  debug("Ogg::Page::render() -- this page is empty!");
  }
  else {
	ByteVectorList::ConstIterator it = d->packets.begin();
	for(; it != d->packets.end(); ++it)
	  data.append(*it);
  }

  // Compute and set the checksum for the Ogg page.  The checksum is taken over
  // the entire page with the 4 bytes reserved for the checksum zeroed and then
  // inserted in bytes 22-25 of the page header.

  ByteVector checksum = ByteVector::fromUInt(data.checksum(), false);
  for(int i = 0; i < 4; i++)
	data[i + 22] = checksum[i];

  return data;
}

List<Ogg::Page *> Ogg::Page::paginate(const ByteVectorList &packets,
									  PaginationStrategy strategy,
									  uint streamSerialNumber,
									  int firstPage,
									  bool firstPacketContinued,
									  bool lastPacketCompleted,
									  bool containsLastPacket)
{
  List<Page *> l;

  int totalSize = 0;

  for(ByteVectorList::ConstIterator it = packets.begin(); it != packets.end(); ++it)
	totalSize += (*it).size();

  // Handle creation of multiple pages with appropriate pagination.
  if(strategy == Repaginate || totalSize + packets.size() > 255 * 255) {

	// SPLITSIZE must be a multiple of 255 in order to get the lacing values right
	// create pages of about 8KB each
#define SPLITSIZE (32*255)

	int pageIndex = 0;

	for(ByteVectorList::ConstIterator it = packets.begin(); it != packets.end(); ++it) {
	  bool continued = false;

	  // mark very first packet?
	  if(firstPacketContinued && it==packets.begin()) {
		continued = true;
	  }

	  // append to buf
	  ByteVector packetBuf;
	  packetBuf.append(*it);

	  while(packetBuf.size() > SPLITSIZE) {
		// output a Page
		ByteVector packetForOnePage;
		packetForOnePage.resize(SPLITSIZE);
		std::copy(packetBuf.begin(), packetBuf.begin() + SPLITSIZE, packetForOnePage.begin());

		ByteVectorList packetList;
		packetList.append(packetForOnePage);
		Page *p = new Page(packetList, streamSerialNumber, firstPage+pageIndex, continued, false, false);
		l.append(p);

		pageIndex++;
		continued = true;
		packetBuf = packetBuf.mid(SPLITSIZE);
	  }

	  ByteVectorList::ConstIterator jt = it;
	  ++jt;
	  bool lastPacketInList = (jt == packets.end());

	  // output a page for the rest (we output one packet per page, so this one should be completed)
	  ByteVectorList packetList;
	  packetList.append(packetBuf);

	  bool isVeryLastPacket = false;
	  if(containsLastPacket) {
		// mark the very last output page as last of stream
		ByteVectorList::ConstIterator jt = it;
		++jt;
		if(jt == packets.end()) {
		  isVeryLastPacket = true;
		}
	  }

	  Page *p = new Page(packetList, streamSerialNumber, firstPage+pageIndex, continued,
						 lastPacketInList ? lastPacketCompleted : true,
						 isVeryLastPacket);
	  pageIndex++;

	  l.append(p);
	}
  }
  else {
	Page *p = new Page(packets, streamSerialNumber, firstPage, firstPacketContinued,
					   lastPacketCompleted, containsLastPacket);
	l.append(p);
  }

  return l;
}

Ogg::Page* Ogg::Page::getCopyWithNewPageSequenceNumber(int sequenceNumber)
{
  Page *pResultPage = NULL;

  // TODO: a copy constructor would be helpful

  if(d->file == 0) {
	pResultPage = new Page(
		d->packets,
		d->header.streamSerialNumber(),
		sequenceNumber,
		d->header.firstPacketContinued(),
		d->header.lastPacketCompleted(),
		d->header.lastPageOfStream());
  }
  else
  {
	pResultPage = new Page(d->file, d->fileOffset);
	pResultPage->d->header.setPageSequenceNumber(sequenceNumber);
  }
  return pResultPage;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

Ogg::Page::Page(const ByteVectorList &packets,
				uint streamSerialNumber,
				int pageNumber,
				bool firstPacketContinued,
				bool lastPacketCompleted,
				bool containsLastPacket)
{
  d = new PagePrivate;

  ByteVector data;
  List<int> packetSizes;

  d->header.setFirstPageOfStream(pageNumber == 0 && !firstPacketContinued);
  d->header.setLastPageOfStream(containsLastPacket);
  d->header.setFirstPacketContinued(firstPacketContinued);
  d->header.setLastPacketCompleted(lastPacketCompleted);
  d->header.setStreamSerialNumber(streamSerialNumber);
  d->header.setPageSequenceNumber(pageNumber);

  // Build a page from the list of packets.

  for(ByteVectorList::ConstIterator it = packets.begin(); it != packets.end(); ++it) {
	packetSizes.append((*it).size());
	data.append(*it);
  }
  d->packets = packets;
  d->header.setPacketSizes(packetSizes);
}

/*** End of inlined file: oggpage.cpp ***/


/*** Start of inlined file: oggpageheader.cpp ***/
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

#include <stdlib.h>

#include <bitset>

using namespace TagLib;

class Ogg::PageHeader::PageHeaderPrivate
{
public:
  PageHeaderPrivate(File *f, long pageOffset) :
	file(f),
	fileOffset(pageOffset),
	isValid(false),
	firstPacketContinued(false),
	lastPacketCompleted(false),
	firstPageOfStream(false),
	lastPageOfStream(false),
	absoluteGranularPosition(0),
	streamSerialNumber(0),
	pageSequenceNumber(-1),
	size(0),
	dataSize(0)
	{}

  File *file;
  long fileOffset;
  bool isValid;
  List<int> packetSizes;
  bool firstPacketContinued;
  bool lastPacketCompleted;
  bool firstPageOfStream;
  bool lastPageOfStream;
  long long absoluteGranularPosition;
  uint streamSerialNumber;
  int pageSequenceNumber;
  int size;
  int dataSize;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

Ogg::PageHeader::PageHeader(Ogg::File *file, long pageOffset)
{
  d = new PageHeaderPrivate(file, pageOffset);
  if(file && pageOffset >= 0)
	  read();
}

Ogg::PageHeader::~PageHeader()
{
  delete d;
}

bool Ogg::PageHeader::isValid() const
{
  return d->isValid;
}

List<int> Ogg::PageHeader::packetSizes() const
{
  return d->packetSizes;
}

void Ogg::PageHeader::setPacketSizes(const List<int> &sizes)
{
  d->packetSizes = sizes;
}

bool Ogg::PageHeader::firstPacketContinued() const
{
  return d->firstPacketContinued;
}

void Ogg::PageHeader::setFirstPacketContinued(bool continued)
{
  d->firstPacketContinued = continued;
}

bool Ogg::PageHeader::lastPacketCompleted() const
{
  return d->lastPacketCompleted;
}

void Ogg::PageHeader::setLastPacketCompleted(bool completed)
{
  d->lastPacketCompleted = completed;
}

bool Ogg::PageHeader::firstPageOfStream() const
{
  return d->firstPageOfStream;
}

void Ogg::PageHeader::setFirstPageOfStream(bool first)
{
  d->firstPageOfStream = first;
}

bool Ogg::PageHeader::lastPageOfStream() const
{
  return d->lastPageOfStream;
}

void Ogg::PageHeader::setLastPageOfStream(bool last)
{
  d->lastPageOfStream = last;
}

long long Ogg::PageHeader::absoluteGranularPosition() const
{
  return d->absoluteGranularPosition;
}

void Ogg::PageHeader::setAbsoluteGranularPosition(long long agp)
{
  d->absoluteGranularPosition = agp;
}

int Ogg::PageHeader::pageSequenceNumber() const
{
  return d->pageSequenceNumber;
}

void Ogg::PageHeader::setPageSequenceNumber(int sequenceNumber)
{
  d->pageSequenceNumber = sequenceNumber;
}

TagLib::uint Ogg::PageHeader::streamSerialNumber() const
{
  return d->streamSerialNumber;
}

void Ogg::PageHeader::setStreamSerialNumber(uint n)
{
  d->streamSerialNumber = n;
}

int Ogg::PageHeader::size() const
{
  return d->size;
}

int Ogg::PageHeader::dataSize() const
{
  return d->dataSize;
}

ByteVector Ogg::PageHeader::render() const
{
  ByteVector data;

  // capture patern

  data.append("OggS");

  // stream structure version

  data.append(char(0));

  // header type flag

  std::bitset<8> flags;
  flags[0] = d->firstPacketContinued;
  flags[1] = d->pageSequenceNumber == 0;
  flags[2] = d->lastPageOfStream;

  data.append(char(flags.to_ulong()));

  // absolute granular position

  data.append(ByteVector::fromLongLong(d->absoluteGranularPosition, false));

  // stream serial number

  data.append(ByteVector::fromUInt(d->streamSerialNumber, false));

  // page sequence number

  data.append(ByteVector::fromUInt(d->pageSequenceNumber, false));

  // checksum -- this is left empty and should be filled in by the Ogg::Page
  // class

  data.append(ByteVector(4, 0));

  // page segment count and page segment table

  ByteVector pageSegments = lacingValues();

  data.append(char(uchar(pageSegments.size())));
  data.append(pageSegments);

  return data;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void Ogg::PageHeader::read()
{
  d->file->seek(d->fileOffset);

  // An Ogg page header is at least 27 bytes, so we'll go ahead and read that
  // much and then get the rest when we're ready for it.

  ByteVector data = d->file->readBlock(27);

  // Sanity check -- make sure that we were in fact able to read as much data as
  // we asked for and that the page begins with "OggS".

  if(data.size() != 27 || !data.startsWith("OggS")) {
	debug("Ogg::PageHeader::read() -- error reading page header");
	return;
  }

  std::bitset<8> flags(data[5]);

  d->firstPacketContinued = flags.test(0);
  d->firstPageOfStream = flags.test(1);
  d->lastPageOfStream = flags.test(2);

  d->absoluteGranularPosition = data.mid(6, 8).toLongLong(false);
  d->streamSerialNumber = data.mid(14, 4).toUInt(false);
  d->pageSequenceNumber = data.mid(18, 4).toUInt(false);

  // Byte number 27 is the number of page segments, which is the only variable
  // length portion of the page header.  After reading the number of page
  // segments we'll then read in the corresponding data for this count.

  int pageSegmentCount = uchar(data[26]);

  ByteVector pageSegments = d->file->readBlock(pageSegmentCount);

  // Another sanity check.

  if(pageSegmentCount < 1 || int(pageSegments.size()) != pageSegmentCount)
	return;

  // The base size of an Ogg page 27 bytes plus the number of lacing values.

  d->size = 27 + pageSegmentCount;

  int packetSize = 0;

  for(int i = 0; i < pageSegmentCount; i++) {
	d->dataSize += uchar(pageSegments[i]);
	packetSize += uchar(pageSegments[i]);

	if(uchar(pageSegments[i]) < 255) {
	  d->packetSizes.append(packetSize);
	  packetSize = 0;
	}
  }

  if(packetSize > 0) {
	d->packetSizes.append(packetSize);
	d->lastPacketCompleted = false;
  }
  else
	d->lastPacketCompleted = true;

  d->isValid = true;
}

ByteVector Ogg::PageHeader::lacingValues() const
{
  ByteVector data;

  List<int> sizes = d->packetSizes;
  for(List<int>::ConstIterator it = sizes.begin(); it != sizes.end(); ++it) {

	// The size of a packet in an Ogg page is indicated by a series of "lacing
	// values" where the sum of the values is the packet size in bytes.  Each of
	// these values is a byte.  A value of less than 255 (0xff) indicates the end
	// of the packet.

	div_t n = div(*it, 255);

	for(int i = 0; i < n.quot; i++)
	  data.append(char(uchar(255)));

	if(it != --sizes.end() || d->lastPacketCompleted)
	  data.append(char(uchar(n.rem)));
  }

  return data;
}

/*** End of inlined file: oggpageheader.cpp ***/


/*** Start of inlined file: xiphcomment.cpp ***/
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

using namespace TagLib;

class Ogg::XiphComment::XiphCommentPrivate
{
public:
  FieldListMap fieldListMap;
  String vendorID;
  String commentField;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

Ogg::XiphComment::XiphComment() : TagLib::Tag()
{
  d = new XiphCommentPrivate;
}

Ogg::XiphComment::XiphComment(const ByteVector &data) : TagLib::Tag()
{
  d = new XiphCommentPrivate;
  parse(data);
}

Ogg::XiphComment::~XiphComment()
{
  delete d;
}

String Ogg::XiphComment::title() const
{
  if(d->fieldListMap["TITLE"].isEmpty())
	return String::null;
  return d->fieldListMap["TITLE"].front();
}

String Ogg::XiphComment::artist() const
{
  if(d->fieldListMap["ARTIST"].isEmpty())
	return String::null;
  return d->fieldListMap["ARTIST"].front();
}

String Ogg::XiphComment::album() const
{
  if(d->fieldListMap["ALBUM"].isEmpty())
	return String::null;
  return d->fieldListMap["ALBUM"].front();
}

String Ogg::XiphComment::comment() const
{
  if(!d->fieldListMap["DESCRIPTION"].isEmpty()) {
	d->commentField = "DESCRIPTION";
	return d->fieldListMap["DESCRIPTION"].front();
  }

  if(!d->fieldListMap["COMMENT"].isEmpty()) {
	d->commentField = "COMMENT";
	return d->fieldListMap["COMMENT"].front();
  }

  return String::null;
}

String Ogg::XiphComment::genre() const
{
  if(d->fieldListMap["GENRE"].isEmpty())
	return String::null;
  return d->fieldListMap["GENRE"].front();
}

TagLib::uint Ogg::XiphComment::year() const
{
  if(!d->fieldListMap["DATE"].isEmpty())
	return d->fieldListMap["DATE"].front().toInt();
  if(!d->fieldListMap["YEAR"].isEmpty())
	return d->fieldListMap["YEAR"].front().toInt();
  return 0;
}

TagLib::uint Ogg::XiphComment::track() const
{
  if(!d->fieldListMap["TRACKNUMBER"].isEmpty())
	return d->fieldListMap["TRACKNUMBER"].front().toInt();
  if(!d->fieldListMap["TRACKNUM"].isEmpty())
	return d->fieldListMap["TRACKNUM"].front().toInt();
  return 0;
}

void Ogg::XiphComment::setTitle(const String &s)
{
  addField("TITLE", s);
}

void Ogg::XiphComment::setArtist(const String &s)
{
  addField("ARTIST", s);
}

void Ogg::XiphComment::setAlbum(const String &s)
{
  addField("ALBUM", s);
}

void Ogg::XiphComment::setComment(const String &s)
{
  addField(d->commentField.isEmpty() ? "DESCRIPTION" : d->commentField, s);
}

void Ogg::XiphComment::setGenre(const String &s)
{
  addField("GENRE", s);
}

void Ogg::XiphComment::setYear(uint i)
{
  removeField("YEAR");
  if(i == 0)
	removeField("DATE");
  else
	addField("DATE", String::number(i));
}

void Ogg::XiphComment::setTrack(uint i)
{
  removeField("TRACKNUM");
  if(i == 0)
	removeField("TRACKNUMBER");
  else
	addField("TRACKNUMBER", String::number(i));
}

bool Ogg::XiphComment::isEmpty() const
{
  FieldListMap::ConstIterator it = d->fieldListMap.begin();
  for(; it != d->fieldListMap.end(); ++it)
	if(!(*it).second.isEmpty())
	  return false;

  return true;
}

TagLib::uint Ogg::XiphComment::fieldCount() const
{
  uint count = 0;

  FieldListMap::ConstIterator it = d->fieldListMap.begin();
  for(; it != d->fieldListMap.end(); ++it)
	count += (*it).second.size();

  return count;
}

const Ogg::FieldListMap &Ogg::XiphComment::fieldListMap() const
{
  return d->fieldListMap;
}

PropertyMap Ogg::XiphComment::properties() const
{
  return d->fieldListMap;
}

PropertyMap Ogg::XiphComment::setProperties(const PropertyMap &properties)
{
  // check which keys are to be deleted
  StringList toRemove;
  for(FieldListMap::ConstIterator it = d->fieldListMap.begin(); it != d->fieldListMap.end(); ++it)
	if (!properties.contains(it->first))
	  toRemove.append(it->first);

  for(StringList::ConstIterator it = toRemove.begin(); it != toRemove.end(); ++it)
	  removeField(*it);

  // now go through keys in \a properties and check that the values match those in the xiph comment */
  PropertyMap::ConstIterator it = properties.begin();
  for(; it != properties.end(); ++it)
  {
	if(!d->fieldListMap.contains(it->first) || !(it->second == d->fieldListMap[it->first])) {
	  const StringList &sl = it->second;
	  if(sl.size() == 0)
		// zero size string list -> remove the tag with all values
		removeField(it->first);
	  else {
		// replace all strings in the list for the tag
		StringList::ConstIterator valueIterator = sl.begin();
		addField(it->first, *valueIterator, true);
		++valueIterator;
		for(; valueIterator != sl.end(); ++valueIterator)
		  addField(it->first, *valueIterator, false);
	  }
	}
  }
  return PropertyMap();
}

String Ogg::XiphComment::vendorID() const
{
  return d->vendorID;
}

void Ogg::XiphComment::addField(const String &key, const String &value, bool replace)
{
  if(replace)
	removeField(key.upper());

  if(!key.isEmpty() && !value.isEmpty())
	d->fieldListMap[key.upper()].append(value);
}

void Ogg::XiphComment::removeField(const String &key, const String &value)
{
  if(!value.isNull()) {
	StringList::Iterator it = d->fieldListMap[key].begin();
	while(it != d->fieldListMap[key].end()) {
	  if(value == *it)
		it = d->fieldListMap[key].erase(it);
	  else
		it++;
	}
  }
  else
	d->fieldListMap.erase(key);
}

bool Ogg::XiphComment::contains(const String &key) const
{
  return d->fieldListMap.contains(key) && !d->fieldListMap[key].isEmpty();
}

ByteVector Ogg::XiphComment::render() const
{
  return render(true);
}

ByteVector Ogg::XiphComment::render(bool addFramingBit) const
{
  ByteVector data;

  // Add the vendor ID length and the vendor ID.  It's important to use the
  // length of the data(String::UTF8) rather than the length of the the string
  // since this is UTF8 text and there may be more characters in the data than
  // in the UTF16 string.

  ByteVector vendorData = d->vendorID.data(String::UTF8);

  data.append(ByteVector::fromUInt(vendorData.size(), false));
  data.append(vendorData);

  // Add the number of fields.

  data.append(ByteVector::fromUInt(fieldCount(), false));

  // Iterate over the the field lists.  Our iterator returns a
  // std::pair<String, StringList> where the first String is the field name and
  // the StringList is the values associated with that field.

  FieldListMap::ConstIterator it = d->fieldListMap.begin();
  for(; it != d->fieldListMap.end(); ++it) {

	// And now iterate over the values of the current list.

	String fieldName = (*it).first;
	StringList values = (*it).second;

	StringList::ConstIterator valuesIt = values.begin();
	for(; valuesIt != values.end(); ++valuesIt) {
	  ByteVector fieldData = fieldName.data(String::UTF8);
	  fieldData.append('=');
	  fieldData.append((*valuesIt).data(String::UTF8));

	  data.append(ByteVector::fromUInt(fieldData.size(), false));
	  data.append(fieldData);
	}
  }

  // Append the "framing bit".

  if(addFramingBit)
	data.append(char(1));

  return data;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

void Ogg::XiphComment::parse(const ByteVector &data)
{
  // The first thing in the comment data is the vendor ID length, followed by a
  // UTF8 string with the vendor ID.

  uint pos = 0;

  uint vendorLength = data.mid(0, 4).toUInt(false);
  pos += 4;

  d->vendorID = String(data.mid(pos, vendorLength), String::UTF8);
  pos += vendorLength;

  // Next the number of fields in the comment vector.

  uint commentFields = data.mid(pos, 4).toUInt(false);
  pos += 4;

  if(commentFields > (data.size() - 8) / 4) {
	return;
  }

  for(uint i = 0; i < commentFields; i++) {

	// Each comment field is in the format "KEY=value" in a UTF8 string and has
	// 4 bytes before the text starts that gives the length.

	uint commentLength = data.mid(pos, 4).toUInt(false);
	pos += 4;

	String comment = String(data.mid(pos, commentLength), String::UTF8);
	pos += commentLength;
	if(pos > data.size()) {
	  break;
	}

	int commentSeparatorPosition = comment.find("=");
	if(commentSeparatorPosition == -1) {
	  break;
	}

	String key = comment.substr(0, commentSeparatorPosition);
	String value = comment.substr(commentSeparatorPosition + 1);

	addField(key, value, false);
  }
}

/*** End of inlined file: xiphcomment.cpp ***/


/*** Start of inlined file: vorbisfile.cpp ***/
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

#include <bitset>

using namespace TagLib;

class Vorbis::File::FilePrivate
{
public:
  FilePrivate() :
	comment(0),
	properties(0) {}

  ~FilePrivate()
  {
	delete comment;
	delete properties;
  }

  Ogg::XiphComment *comment;
  Properties *properties;
};

namespace TagLib {
  /*!
   * Vorbis headers can be found with one type ID byte and the string "vorbis" in
   * an Ogg stream.  0x03 indicates the comment header.
   */
  static const char vorbisCommentHeaderID[] = { 0x03, 'v', 'o', 'r', 'b', 'i', 's', 0 };
}

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

Vorbis::File::File(FileName file, bool readProperties,
				   Properties::ReadStyle propertiesStyle) : Ogg::File(file)
{
  d = new FilePrivate;
  read(readProperties, propertiesStyle);
}

Vorbis::File::File(IOStream *stream, bool readProperties,
				   Properties::ReadStyle propertiesStyle) : Ogg::File(stream)
{
  d = new FilePrivate;
  read(readProperties, propertiesStyle);
}

Vorbis::File::~File()
{
  delete d;
}

Ogg::XiphComment *Vorbis::File::tag() const
{
  return d->comment;
}

PropertyMap Vorbis::File::properties() const
{
  return d->comment->properties();
}

PropertyMap Vorbis::File::setProperties(const PropertyMap &properties)
{
  return d->comment->setProperties(properties);
}

Vorbis::Properties *Vorbis::File::audioProperties() const
{
  return d->properties;
}

bool Vorbis::File::save()
{
  ByteVector v(vorbisCommentHeaderID);

  if(!d->comment)
	d->comment = new Ogg::XiphComment;
  v.append(d->comment->render());

  setPacket(1, v);

  return Ogg::File::save();
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void Vorbis::File::read(bool readProperties, Properties::ReadStyle propertiesStyle)
{
  ByteVector commentHeaderData = packet(1);

  if(commentHeaderData.mid(0, 7) != vorbisCommentHeaderID) {
	debug("Vorbis::File::read() - Could not find the Vorbis comment header.");
	setValid(false);
	return;
  }

  d->comment = new Ogg::XiphComment(commentHeaderData.mid(7));

  if(readProperties)
	d->properties = new Properties(this, propertiesStyle);
}

/*** End of inlined file: vorbisfile.cpp ***/


/*** Start of inlined file: vorbisproperties.cpp ***/
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

using namespace TagLib;

class Vorbis::Properties::PropertiesPrivate
{
public:
  PropertiesPrivate(File *f, ReadStyle s) :
	file(f),
	style(s),
	length(0),
	bitrate(0),
	sampleRate(0),
	channels(0),
	vorbisVersion(0),
	bitrateMaximum(0),
	bitrateNominal(0),
	bitrateMinimum(0) {}

  File *file;
  ReadStyle style;
  int length;
  int bitrate;
  int sampleRate;
  int channels;
  int vorbisVersion;
  int bitrateMaximum;
  int bitrateNominal;
  int bitrateMinimum;
};

namespace TagLib {
  /*!
   * Vorbis headers can be found with one type ID byte and the string "vorbis" in
   * an Ogg stream.  0x01 indicates the setup header.
   */
  static const char vorbisSetupHeaderID[] = { 0x01, 'v', 'o', 'r', 'b', 'i', 's', 0 };
}

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

Vorbis::Properties::Properties(File *file, ReadStyle style) : AudioProperties(style)
{
  d = new PropertiesPrivate(file, style);
  read();
}

Vorbis::Properties::~Properties()
{
  delete d;
}

int Vorbis::Properties::length() const
{
  return d->length;
}

int Vorbis::Properties::bitrate() const
{
  return int(float(d->bitrate) / float(1000) + 0.5);
}

int Vorbis::Properties::sampleRate() const
{
  return d->sampleRate;
}

int Vorbis::Properties::channels() const
{
  return d->channels;
}

int Vorbis::Properties::vorbisVersion() const
{
  return d->vorbisVersion;
}

int Vorbis::Properties::bitrateMaximum() const
{
  return d->bitrateMaximum;
}

int Vorbis::Properties::bitrateNominal() const
{
  return d->bitrateNominal;
}

int Vorbis::Properties::bitrateMinimum() const
{
  return d->bitrateMinimum;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void Vorbis::Properties::read()
{
  // Get the identification header from the Ogg implementation.

  ByteVector data = d->file->packet(0);

  int pos = 0;

  if(data.mid(pos, 7) != vorbisSetupHeaderID) {
	debug("Vorbis::Properties::read() -- invalid Vorbis identification header");
	return;
  }

  pos += 7;

  d->vorbisVersion = data.mid(pos, 4).toUInt(false);
  pos += 4;

  d->channels = uchar(data[pos]);
  pos += 1;

  d->sampleRate = data.mid(pos, 4).toUInt(false);
  pos += 4;

  d->bitrateMaximum = data.mid(pos, 4).toUInt(false);
  pos += 4;

  d->bitrateNominal = data.mid(pos, 4).toUInt(false);
  pos += 4;

  d->bitrateMinimum = data.mid(pos, 4).toUInt(false);

  // TODO: Later this should be only the "fast" mode.
  d->bitrate = d->bitrateNominal;

  // Find the length of the file.  See http://wiki.xiph.org/VorbisStreamLength/
  // for my notes on the topic.

  const Ogg::PageHeader *first = d->file->firstPageHeader();
  const Ogg::PageHeader *last = d->file->lastPageHeader();

  if(first && last) {
	long long start = first->absoluteGranularPosition();
	long long end = last->absoluteGranularPosition();

	if(start >= 0 && end >= 0 && d->sampleRate > 0)
	  d->length = (end - start) / (long long) d->sampleRate;
	else
	  debug("Vorbis::Properties::read() -- Either the PCM values for the start or "
			"end of this file was incorrect or the sample rate is zero.");
  }
  else
	debug("Vorbis::Properties::read() -- Could not find valid first and last Ogg pages.");
}

/*** End of inlined file: vorbisproperties.cpp ***/


/*** Start of inlined file: flacfile.cpp ***/
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


/*** Start of inlined file: flacunknownmetadatablock.h ***/
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

#ifndef TAGLIB_FLACUNKNOWNMETADATABLOCK_H
#define TAGLIB_FLACUNKNOWNMETADATABLOCK_H

namespace TagLib {

  namespace FLAC {

	class TAGLIB_EXPORT UnknownMetadataBlock : public MetadataBlock
	{
	public:
	  UnknownMetadataBlock(int blockType, const ByteVector &data);
	  ~UnknownMetadataBlock();

	  /*!
	   * Returns the FLAC metadata block type.
	   */
	  int code() const;

	  /*!
	   * Sets the FLAC metadata block type.
	   */
	  void setCode(int code);

	  /*!
	   * Returns the FLAC metadata block type.
	   */
	  ByteVector data() const;

	  /*!
	   * Sets the FLAC metadata block type.
	   */
	  void setData(const ByteVector &data);

	  /*!
	   * Render the content of the block.
	   */
	  ByteVector render() const;

	private:
	  UnknownMetadataBlock(const MetadataBlock &item);
	  UnknownMetadataBlock &operator=(const MetadataBlock &item);

	  class UnknownMetadataBlockPrivate;
	  UnknownMetadataBlockPrivate *d;
	};

  }

}

#endif

/*** End of inlined file: flacunknownmetadatablock.h ***/

using namespace TagLib;

namespace
{
  enum { FlacXiphIndex = 0, FlacID3v2Index = 1, FlacID3v1Index = 2 };
  enum { MinPaddingLength = 4096 };
  enum { LastBlockFlag = 0x80 };
}

class FLAC::File::FilePrivate
{
public:
  FilePrivate() :
	ID3v2FrameFactory(ID3v2::FrameFactory::instance()),
	ID3v2Location(-1),
	ID3v2OriginalSize(0),
	ID3v1Location(-1),
	properties(0),
	flacStart(0),
	streamStart(0),
	streamLength(0),
	scanned(false),
	hasXiphComment(false),
	hasID3v2(false),
	hasID3v1(false)
  {
  }

  ~FilePrivate()
  {
	for(uint i = 0; i < blocks.size(); i++) {
	  delete blocks[i];
	}
	delete properties;
  }

  const ID3v2::FrameFactory *ID3v2FrameFactory;
  long ID3v2Location;
  uint ID3v2OriginalSize;

  long ID3v1Location;

  TagUnion tag;

  Properties *properties;
  ByteVector streamInfoData;
  ByteVector xiphCommentData;
  List<MetadataBlock *> blocks;

  long flacStart;
  long streamStart;
  long streamLength;
  bool scanned;

  bool hasXiphComment;
  bool hasID3v2;
  bool hasID3v1;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

FLAC::File::File(FileName file, bool readProperties,
				 Properties::ReadStyle propertiesStyle) :
  TagLib::File(file)
{
  d = new FilePrivate;
  read(readProperties, propertiesStyle);
}

FLAC::File::File(FileName file, ID3v2::FrameFactory *frameFactory,
				 bool readProperties, Properties::ReadStyle propertiesStyle) :
  TagLib::File(file)
{
  d = new FilePrivate;
  d->ID3v2FrameFactory = frameFactory;
  read(readProperties, propertiesStyle);
}

FLAC::File::File(IOStream *stream, ID3v2::FrameFactory *frameFactory,
				 bool readProperties, Properties::ReadStyle propertiesStyle) :
  TagLib::File(stream)
{
  d = new FilePrivate;
  d->ID3v2FrameFactory = frameFactory;
  read(readProperties, propertiesStyle);
}

FLAC::File::~File()
{
  delete d;
}

TagLib::Tag *FLAC::File::tag() const
{
  return &d->tag;
}

PropertyMap FLAC::File::properties() const
{
  // once Tag::properties() is virtual, this case distinction could actually be done
  // within TagUnion.
  if(d->hasXiphComment)
	return d->tag.access<Ogg::XiphComment>(FlacXiphIndex, false)->properties();
  if(d->hasID3v2)
	return d->tag.access<ID3v2::Tag>(FlacID3v2Index, false)->properties();
  if(d->hasID3v1)
	return d->tag.access<ID3v1::Tag>(FlacID3v1Index, false)->properties();
  return PropertyMap();
}

void FLAC::File::removeUnsupportedProperties(const StringList &unsupported)
{
  if(d->hasXiphComment)
	d->tag.access<Ogg::XiphComment>(FlacXiphIndex, false)->removeUnsupportedProperties(unsupported);
  if(d->hasID3v2)
	d->tag.access<ID3v2::Tag>(FlacID3v2Index, false)->removeUnsupportedProperties(unsupported);
  if(d->hasID3v1)
	d->tag.access<ID3v1::Tag>(FlacID3v1Index, false)->removeUnsupportedProperties(unsupported);
}

PropertyMap FLAC::File::setProperties(const PropertyMap &properties)
{
  if(d->hasXiphComment)
	return d->tag.access<Ogg::XiphComment>(FlacXiphIndex, false)->setProperties(properties);
  else if(d->hasID3v2)
	return d->tag.access<ID3v2::Tag>(FlacID3v2Index, false)->setProperties(properties);
  else if(d->hasID3v1)
	return d->tag.access<ID3v1::Tag>(FlacID3v1Index, false)->setProperties(properties);
  else
	return d->tag.access<Ogg::XiphComment>(FlacXiphIndex, true)->setProperties(properties);
}

FLAC::Properties *FLAC::File::audioProperties() const
{
  return d->properties;
}

bool FLAC::File::save()
{
  if(readOnly()) {
	debug("FLAC::File::save() - Cannot save to a read only file.");
	return false;
  }

  if(!isValid()) {
	debug("FLAC::File::save() -- Trying to save invalid file.");
	return false;
  }

  // Create new vorbis comments

  Tag::duplicate(&d->tag, xiphComment(true), false);

  d->xiphCommentData = xiphComment()->render(false);

  // Replace metadata blocks

  bool foundVorbisCommentBlock = false;
  List<MetadataBlock *> newBlocks;
  for(uint i = 0; i < d->blocks.size(); i++) {
	MetadataBlock *block = d->blocks[i];
	if(block->code() == MetadataBlock::VorbisComment) {
	  // Set the new Vorbis Comment block
	  delete block;
	  block = new UnknownMetadataBlock(MetadataBlock::VorbisComment, d->xiphCommentData);
	  foundVorbisCommentBlock = true;
	}
	if(block->code() == MetadataBlock::Padding) {
	  delete block;
	  continue;
	}
	newBlocks.append(block);
  }
  if(!foundVorbisCommentBlock) {
	newBlocks.append(new UnknownMetadataBlock(MetadataBlock::VorbisComment, d->xiphCommentData));
	foundVorbisCommentBlock = true;
  }
  d->blocks = newBlocks;

  // Render data for the metadata blocks

  ByteVector data;
  for(uint i = 0; i < newBlocks.size(); i++) {
	FLAC::MetadataBlock *block = newBlocks[i];
	ByteVector blockData = block->render();
	ByteVector blockHeader = ByteVector::fromUInt(blockData.size());
	blockHeader[0] = static_cast<char>(block->code());
	data.append(blockHeader);
	data.append(blockData);
  }

  // Adjust the padding block(s)

  long originalLength = d->streamStart - d->flacStart;
  int paddingLength = originalLength - data.size() - 4;
  if (paddingLength < 0) {
	paddingLength = MinPaddingLength;
  }
  ByteVector padding = ByteVector::fromUInt(paddingLength);
  padding.resize(paddingLength + 4);
  padding[0] = FLAC::MetadataBlock::Padding | LastBlockFlag;
  data.append(padding);

  // Write the data to the file

  insert(data, d->flacStart, originalLength);
  d->hasXiphComment = true;

  // Update ID3 tags

  if(ID3v2Tag()) {
	if(d->hasID3v2) {
	  if(d->ID3v2Location < d->flacStart)
		debug("FLAC::File::save() -- This can't be right -- an ID3v2 tag after the "
			  "start of the FLAC bytestream?  Not writing the ID3v2 tag.");
	  else
		insert(ID3v2Tag()->render(), d->ID3v2Location, d->ID3v2OriginalSize);
	}
	else
	  insert(ID3v2Tag()->render(), 0, 0);
  }

  if(ID3v1Tag()) {
	seek(-128, End);
	writeBlock(ID3v1Tag()->render());
  }

  return true;
}

ID3v2::Tag *FLAC::File::ID3v2Tag(bool create)
{
  if(!create || d->tag[FlacID3v2Index])
	return static_cast<ID3v2::Tag *>(d->tag[FlacID3v2Index]);

  d->tag.set(FlacID3v2Index, new ID3v2::Tag);
  return static_cast<ID3v2::Tag *>(d->tag[FlacID3v2Index]);
}

ID3v1::Tag *FLAC::File::ID3v1Tag(bool create)
{
  return d->tag.access<ID3v1::Tag>(FlacID3v1Index, create);
}

Ogg::XiphComment *FLAC::File::xiphComment(bool create)
{
  return d->tag.access<Ogg::XiphComment>(FlacXiphIndex, create);
}

void FLAC::File::setID3v2FrameFactory(const ID3v2::FrameFactory *factory)
{
  d->ID3v2FrameFactory = factory;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void FLAC::File::read(bool readProperties, Properties::ReadStyle propertiesStyle)
{
  // Look for an ID3v2 tag

  d->ID3v2Location = findID3v2();

  if(d->ID3v2Location >= 0) {

	d->tag.set(FlacID3v2Index, new ID3v2::Tag(this, d->ID3v2Location, d->ID3v2FrameFactory));

	d->ID3v2OriginalSize = ID3v2Tag()->header()->completeTagSize();

	if(ID3v2Tag()->header()->tagSize() <= 0)
	  d->tag.set(FlacID3v2Index, 0);
	else
	  d->hasID3v2 = true;
  }

  // Look for an ID3v1 tag

  d->ID3v1Location = findID3v1();

  if(d->ID3v1Location >= 0) {
	d->tag.set(FlacID3v1Index, new ID3v1::Tag(this, d->ID3v1Location));
	d->hasID3v1 = true;
  }

  // Look for FLAC metadata, including vorbis comments

  scan();

  if(!isValid())
	return;

  if(d->hasXiphComment)
	d->tag.set(FlacXiphIndex, new Ogg::XiphComment(xiphCommentData()));
  else
	d->tag.set(FlacXiphIndex, new Ogg::XiphComment);

  if(readProperties)
	d->properties = new Properties(streamInfoData(), streamLength(), propertiesStyle);
}

ByteVector FLAC::File::streamInfoData()
{
  return isValid() ? d->streamInfoData : ByteVector();
}

ByteVector FLAC::File::xiphCommentData() const
{
  return (isValid() && d->hasXiphComment) ? d->xiphCommentData : ByteVector();
}

long FLAC::File::streamLength()
{
  return d->streamLength;
}

void FLAC::File::scan()
{
  // Scan the metadata pages

  if(d->scanned)
	return;

  if(!isValid())
	return;

  long nextBlockOffset;

  if(d->hasID3v2)
	nextBlockOffset = find("fLaC", d->ID3v2Location + d->ID3v2OriginalSize);
  else
	nextBlockOffset = find("fLaC");

  if(nextBlockOffset < 0) {
	debug("FLAC::File::scan() -- FLAC stream not found");
	setValid(false);
	return;
  }

  nextBlockOffset += 4;
  d->flacStart = nextBlockOffset;

  seek(nextBlockOffset);

  ByteVector header = readBlock(4);

  // Header format (from spec):
  // <1> Last-metadata-block flag
  // <7> BLOCK_TYPE
  //    0 : STREAMINFO
  //    1 : PADDING
  //    ..
  //    4 : VORBIS_COMMENT
  //    ..
  // <24> Length of metadata to follow

  char blockType = header[0] & 0x7f;
  bool isLastBlock = (header[0] & 0x80) != 0;
  uint length = header.mid(1, 3).toUInt();

  // First block should be the stream_info metadata

  if(blockType != MetadataBlock::StreamInfo) {
	debug("FLAC::File::scan() -- invalid FLAC stream");
	setValid(false);
	return;
  }

  d->streamInfoData = readBlock(length);
  d->blocks.append(new UnknownMetadataBlock(blockType, d->streamInfoData));
  nextBlockOffset += length + 4;

  // Search through the remaining metadata
  while(!isLastBlock) {

	header = readBlock(4);
	blockType = header[0] & 0x7f;
	isLastBlock = (header[0] & 0x80) != 0;
	length = header.mid(1, 3).toUInt();

	ByteVector data = readBlock(length);
	if(data.size() != length) {
	  debug("FLAC::File::scan() -- FLAC stream corrupted");
	  setValid(false);
	  return;
	}

	MetadataBlock *block = 0;

	// Found the vorbis-comment
	if(blockType == MetadataBlock::VorbisComment) {
	  if(!d->hasXiphComment) {
		d->xiphCommentData = data;
		d->hasXiphComment = true;
	  }
	  else {
		debug("FLAC::File::scan() -- multiple Vorbis Comment blocks found, using the first one");
	  }
	}
	else if(blockType == MetadataBlock::Picture) {
	  FLAC::Picture *picture = new FLAC::Picture();
	  if(picture->parse(data)) {
		block = picture;
	  }
	  else {
		debug("FLAC::File::scan() -- invalid picture found, discarting");
		delete picture;
	  }
	}

	if(!block) {
	  block = new UnknownMetadataBlock(blockType, data);
	}
	if(block->code() != MetadataBlock::Padding) {
	  d->blocks.append(block);
	}
	else {
	  delete block;
	}

	nextBlockOffset += length + 4;

	if(nextBlockOffset >= File::length()) {
	  debug("FLAC::File::scan() -- FLAC stream corrupted");
	  setValid(false);
	  return;
	}
	seek(nextBlockOffset);
  }

  // End of metadata, now comes the datastream

  d->streamStart = nextBlockOffset;
  d->streamLength = File::length() - d->streamStart;

  if(d->hasID3v1)
	d->streamLength -= 128;

  d->scanned = true;
}

long FLAC::File::findID3v1()
{
  if(!isValid())
	return -1;

  seek(-128, End);
  long p = tell();

  if(readBlock(3) == ID3v1::Tag::fileIdentifier())
	return p;

  return -1;
}

long FLAC::File::findID3v2()
{
  if(!isValid())
	return -1;

  seek(0);

  if(readBlock(3) == ID3v2::Header::fileIdentifier())
	return 0;

  return -1;
}

List<FLAC::Picture *> FLAC::File::pictureList()
{
  List<Picture *> pictures;
  for(uint i = 0; i < d->blocks.size(); i++) {
	Picture *picture = dynamic_cast<Picture *>(d->blocks[i]);
	if(picture) {
	  pictures.append(picture);
	}
  }
  return pictures;
}

void FLAC::File::addPicture(Picture *picture)
{
  d->blocks.append(picture);
}

void FLAC::File::removePicture(Picture *picture, bool del)
{
  MetadataBlock *block = picture;
  List<MetadataBlock *>::Iterator it = d->blocks.find(block);
  if(it != d->blocks.end())
	d->blocks.erase(it);

  if(del)
	delete picture;
}

void FLAC::File::removePictures()
{
  List<MetadataBlock *> newBlocks;
  for(uint i = 0; i < d->blocks.size(); i++) {
	Picture *picture = dynamic_cast<Picture *>(d->blocks[i]);
	if(picture) {
	  delete picture;
	}
	else {
	  newBlocks.append(d->blocks[i]);
	}
  }
  d->blocks = newBlocks;
}

/*** End of inlined file: flacfile.cpp ***/


/*** Start of inlined file: flacpicture.cpp ***/
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace TagLib;

class FLAC::Picture::PicturePrivate
{
public:
  PicturePrivate() :
	type(FLAC::Picture::Other),
	width(0),
	height(0),
	colorDepth(0),
	numColors(0)
	{}

  Type type;
  String mimeType;
  String description;
  int width;
  int height;
  int colorDepth;
  int numColors;
  ByteVector data;
};

FLAC::Picture::Picture()
{
  d = new PicturePrivate;
}

FLAC::Picture::Picture(const ByteVector &data)
{
  d = new PicturePrivate;
  parse(data);
}

FLAC::Picture::~Picture()
{
  delete d;
}

int FLAC::Picture::code() const
{
  return FLAC::MetadataBlock::Picture;
}

bool FLAC::Picture::parse(const ByteVector &data)
{
  if(data.size() < 32) {
	debug("A picture block must contain at least 5 bytes.");
	return false;
  }

  int pos = 0;
  d->type = FLAC::Picture::Type(data.mid(pos, 4).toUInt());
  pos += 4;
  uint mimeTypeLength = data.mid(pos, 4).toUInt();
  pos += 4;
  if(pos + mimeTypeLength + 24 > data.size()) {
	debug("Invalid picture block.");
	return false;
  }
  d->mimeType = String(data.mid(pos, mimeTypeLength), String::UTF8);
  pos += mimeTypeLength;
  uint descriptionLength = data.mid(pos, 4).toUInt();
  pos += 4;
  if(pos + descriptionLength + 20 > data.size()) {
	debug("Invalid picture block.");
	return false;
  }
  d->description = String(data.mid(pos, descriptionLength), String::UTF8);
  pos += descriptionLength;
  d->width = data.mid(pos, 4).toUInt();
  pos += 4;
  d->height = data.mid(pos, 4).toUInt();
  pos += 4;
  d->colorDepth = data.mid(pos, 4).toUInt();
  pos += 4;
  d->numColors = data.mid(pos, 4).toUInt();
  pos += 4;
  uint dataLength = data.mid(pos, 4).toUInt();
  pos += 4;
  if(pos + dataLength > data.size()) {
	debug("Invalid picture block.");
	return false;
  }
  d->data = data.mid(pos, dataLength);

  return true;
}

ByteVector FLAC::Picture::render() const
{
  ByteVector result;
  result.append(ByteVector::fromUInt(d->type));
  ByteVector mimeTypeData = d->mimeType.data(String::UTF8);
  result.append(ByteVector::fromUInt(mimeTypeData.size()));
  result.append(mimeTypeData);
  ByteVector descriptionData = d->description.data(String::UTF8);
  result.append(ByteVector::fromUInt(descriptionData.size()));
  result.append(descriptionData);
  result.append(ByteVector::fromUInt(d->width));
  result.append(ByteVector::fromUInt(d->height));
  result.append(ByteVector::fromUInt(d->colorDepth));
  result.append(ByteVector::fromUInt(d->numColors));
  result.append(ByteVector::fromUInt(d->data.size()));
  result.append(d->data);
  return result;
}

FLAC::Picture::Type FLAC::Picture::type() const
{
  return d->type;
}

void FLAC::Picture::setType(FLAC::Picture::Type type)
{
  d->type = type;
}

String FLAC::Picture::mimeType() const
{
  return d->mimeType;
}

void FLAC::Picture::setMimeType(const String &mimeType)
{
  d->mimeType = mimeType;
}

String FLAC::Picture::description() const
{
  return d->description;
}

void FLAC::Picture::setDescription(const String &description)
{
  d->description = description;
}

int FLAC::Picture::width() const
{
  return d->width;
}

void FLAC::Picture::setWidth(int width)
{
  d->width = width;
}

int FLAC::Picture::height() const
{
  return d->height;
}

void FLAC::Picture::setHeight(int height)
{
  d->height = height;
}

int FLAC::Picture::colorDepth() const
{
  return d->colorDepth;
}

void FLAC::Picture::setColorDepth(int colorDepth)
{
  d->colorDepth = colorDepth;
}

int FLAC::Picture::numColors() const
{
  return d->numColors;
}

void FLAC::Picture::setNumColors(int numColors)
{
  d->numColors = numColors;
}

ByteVector FLAC::Picture::data() const
{
  return d->data;
}

void FLAC::Picture::setData(const ByteVector &data)
{
  d->data = data;
}

/*** End of inlined file: flacpicture.cpp ***/


/*** Start of inlined file: flacproperties.cpp ***/
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

using namespace TagLib;

class FLAC::Properties::PropertiesPrivate
{
public:
  PropertiesPrivate(ByteVector d, long st, ReadStyle s) :
	data(d),
	streamLength(st),
	style(s),
	length(0),
	bitrate(0),
	sampleRate(0),
	sampleWidth(0),
	channels(0),
	sampleFrames(0) {}

  ByteVector data;
  long streamLength;
  ReadStyle style;
  int length;
  int bitrate;
  int sampleRate;
  int sampleWidth;
  int channels;
  unsigned long long sampleFrames;
  ByteVector signature;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

FLAC::Properties::Properties(ByteVector data, long streamLength, ReadStyle style) : AudioProperties(style)
{
  d = new PropertiesPrivate(data, streamLength, style);
  read();
}

FLAC::Properties::Properties(File *file, ReadStyle style) : AudioProperties(style)
{
  d = new PropertiesPrivate(file->streamInfoData(), file->streamLength(), style);
  read();
}

FLAC::Properties::~Properties()
{
  delete d;
}

int FLAC::Properties::length() const
{
  return d->length;
}

int FLAC::Properties::bitrate() const
{
  return d->bitrate;
}

int FLAC::Properties::sampleRate() const
{
  return d->sampleRate;
}

int FLAC::Properties::sampleWidth() const
{
  return d->sampleWidth;
}

int FLAC::Properties::channels() const
{
  return d->channels;
}

unsigned long long FLAC::Properties::sampleFrames() const
{
  return d->sampleFrames;
}

ByteVector FLAC::Properties::signature() const
{
  return d->signature;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void FLAC::Properties::read()
{
  if(d->data.size() < 18) {
	debug("FLAC::Properties::read() - FLAC properties must contain at least 18 bytes.");
	return;
  }

  int pos = 0;

  // Minimum block size (in samples)
  pos += 2;

  // Maximum block size (in samples)
  pos += 2;

  // Minimum frame size (in bytes)
  pos += 3;

  // Maximum frame size (in bytes)
  pos += 3;

  uint flags = d->data.mid(pos, 4).toUInt(true);
  pos += 4;

  d->sampleRate = flags >> 12;
  d->channels = ((flags >> 9) & 7) + 1;
  d->sampleWidth = ((flags >> 4) & 31) + 1;

  // The last 4 bits are the most significant 4 bits for the 36 bit
  // stream length in samples. (Audio files measured in days)

  unsigned long long hi = flags & 0xf;
  unsigned long long lo = d->data.mid(pos, 4).toUInt(true);
  pos += 4;

  d->sampleFrames = (hi << 32) | lo;

  if(d->sampleRate > 0)
	d->length = int(d->sampleFrames / d->sampleRate);

  // Uncompressed bitrate:

  //d->bitrate = ((d->sampleRate * d->channels) / 1000) * d->sampleWidth;

  // Real bitrate:

  d->bitrate = d->length > 0 ? ((d->streamLength * 8UL) / d->length) / 1000 : 0;

  d->signature = d->data.mid(pos, 32);
}

/*** End of inlined file: flacproperties.cpp ***/


/*** Start of inlined file: flacmetadatablock.cpp ***/
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace TagLib;

class FLAC::MetadataBlock::MetadataBlockPrivate
{
public:
  MetadataBlockPrivate() {}

};

FLAC::MetadataBlock::MetadataBlock()
{
  d = 0;
}

FLAC::MetadataBlock::~MetadataBlock()
{
}

/*** End of inlined file: flacmetadatablock.cpp ***/


/*** Start of inlined file: flacunknownmetadatablock.cpp ***/
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace TagLib;

class FLAC::UnknownMetadataBlock::UnknownMetadataBlockPrivate
{
public:
  UnknownMetadataBlockPrivate() : code(0) {}

  int code;
  ByteVector data;
};

FLAC::UnknownMetadataBlock::UnknownMetadataBlock(int code, const ByteVector &data)
{
  d = new UnknownMetadataBlockPrivate;
  d->code = code;
  //debug(String(data.toHex()));
  d->data = data;
}

FLAC::UnknownMetadataBlock::~UnknownMetadataBlock()
{
  delete d;
}

int FLAC::UnknownMetadataBlock::code() const
{
  return d->code;
}

void FLAC::UnknownMetadataBlock::setCode(int code)
{
  d->code = code;
}

ByteVector FLAC::UnknownMetadataBlock::data() const
{
  return d->data;
}

void FLAC::UnknownMetadataBlock::setData(const ByteVector &data)
{
  d->data = data;
}

ByteVector FLAC::UnknownMetadataBlock::render() const
{
  return d->data;
}

/*** End of inlined file: flacunknownmetadatablock.cpp ***/


/*** Start of inlined file: oggflacfile.cpp ***/
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

using namespace TagLib;
using TagLib::FLAC::Properties;

class Ogg::FLAC::File::FilePrivate
{
public:
  FilePrivate() :
	comment(0),
	properties(0),
	streamStart(0),
	streamLength(0),
	scanned(false),
	hasXiphComment(false),
	commentPacket(0) {}

  ~FilePrivate()
  {
	delete comment;
	delete properties;
  }

  Ogg::XiphComment *comment;

  Properties *properties;
  ByteVector streamInfoData;
  ByteVector xiphCommentData;
  long streamStart;
  long streamLength;
  bool scanned;

  bool hasXiphComment;
  int commentPacket;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

Ogg::FLAC::File::File(FileName file, bool readProperties,
					  Properties::ReadStyle propertiesStyle) : Ogg::File(file)
{
  d = new FilePrivate;
  read(readProperties, propertiesStyle);
}

Ogg::FLAC::File::File(IOStream *stream, bool readProperties,
					  Properties::ReadStyle propertiesStyle) : Ogg::File(stream)
{
  d = new FilePrivate;
  read(readProperties, propertiesStyle);
}

Ogg::FLAC::File::~File()
{
  delete d;
}

Ogg::XiphComment *Ogg::FLAC::File::tag() const
{
  return d->comment;
}

Properties *Ogg::FLAC::File::audioProperties() const
{
  return d->properties;
}

bool Ogg::FLAC::File::save()
{
  d->xiphCommentData = d->comment->render(false);

  // Create FLAC metadata-block:

  // Put the size in the first 32 bit (I assume no more than 24 bit are used)

  ByteVector v = ByteVector::fromUInt(d->xiphCommentData.size());

  // Set the type of the metadata-block to be a Xiph / Vorbis comment

  v[0] = 4;

  // Append the comment-data after the 32 bit header

  v.append(d->xiphCommentData);

  // Save the packet at the old spot
  // FIXME: Use padding if size is increasing

  setPacket(d->commentPacket, v);

  return Ogg::File::save();
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void Ogg::FLAC::File::read(bool readProperties, Properties::ReadStyle propertiesStyle)
{
  // Sanity: Check if we really have an Ogg/FLAC file

/*
  ByteVector oggHeader = packet(0);

  if (oggHeader.mid(28,4) != "fLaC") {
	debug("Ogg::FLAC::File::read() -- Not an Ogg/FLAC file");
	setValid(false);
	return;
  }*/

  // Look for FLAC metadata, including vorbis comments

  scan();

  if (!d->scanned) {
	setValid(false);
	return;
  }

  if(d->hasXiphComment)
	d->comment = new Ogg::XiphComment(xiphCommentData());
  else
	d->comment = new Ogg::XiphComment;

  if(readProperties)
	d->properties = new Properties(streamInfoData(), streamLength(), propertiesStyle);
}

ByteVector Ogg::FLAC::File::streamInfoData()
{
  scan();
  return d->streamInfoData;
}

ByteVector Ogg::FLAC::File::xiphCommentData()
{
  scan();
  return d->xiphCommentData;
}

long Ogg::FLAC::File::streamLength()
{
  scan();
  return d->streamLength;
}

void Ogg::FLAC::File::scan()
{
  // Scan the metadata pages

  if(d->scanned)
	return;

  if(!isValid())
	return;

  int ipacket = 0;
  long overhead = 0;

  ByteVector metadataHeader = packet(ipacket);
  if(metadataHeader.isNull())
	return;

  ByteVector header;

  if (!metadataHeader.startsWith("fLaC"))  {
	// FLAC 1.1.2+
	if (metadataHeader.mid(1,4) != "FLAC") return;

	if (metadataHeader[5] != 1) return; // not version 1

	metadataHeader = metadataHeader.mid(13);
  }
  else {
	// FLAC 1.1.0 & 1.1.1
	metadataHeader = packet(++ipacket);

	if(metadataHeader.isNull())
	  return;

  }

  header = metadataHeader.mid(0,4);
  // Header format (from spec):
  // <1> Last-metadata-block flag
  // <7> BLOCK_TYPE
  //    0 : STREAMINFO
  //    1 : PADDING
  //    ..
  //    4 : VORBIS_COMMENT
  //    ..
  // <24> Length of metadata to follow

  char blockType = header[0] & 0x7f;
  bool lastBlock = (header[0] & 0x80) != 0;
  uint length = header.mid(1, 3).toUInt();
  overhead += length;

  // Sanity: First block should be the stream_info metadata

  if(blockType != 0) {
	debug("Ogg::FLAC::File::scan() -- Invalid Ogg/FLAC stream");
	return;
  }

  d->streamInfoData = metadataHeader.mid(4,length);

  // Search through the remaining metadata

  while(!lastBlock) {
	metadataHeader = packet(++ipacket);

	if(metadataHeader.isNull())
	  return;

	header = metadataHeader.mid(0, 4);
	blockType = header[0] & 0x7f;
	lastBlock = (header[0] & 0x80) != 0;
	length = header.mid(1, 3).toUInt();
	overhead += length;

	if(blockType == 1) {
	  // debug("Ogg::FLAC::File::scan() -- Padding found");
	}
	else if(blockType == 4) {
	  // debug("Ogg::FLAC::File::scan() -- Vorbis-comments found");
	  d->xiphCommentData = metadataHeader.mid(4, length);
	  d->hasXiphComment = true;
	  d->commentPacket = ipacket;
	}
	else if(blockType > 5)
	  debug("Ogg::FLAC::File::scan() -- Unknown metadata block");

  }

  // End of metadata, now comes the datastream
  d->streamStart = overhead;
  d->streamLength = File::length() - d->streamStart;

  d->scanned = true;
}

/*** End of inlined file: oggflacfile.cpp ***/


/*** Start of inlined file: mpcfile.cpp ***/
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

using namespace TagLib;

namespace
{
  enum { MPCAPEIndex, MPCID3v1Index };
}

class MPC::File::FilePrivate
{
public:
  FilePrivate() :
	APELocation(-1),
	APESize(0),
	ID3v1Location(-1),
	ID3v2Header(0),
	ID3v2Location(-1),
	ID3v2Size(0),
	properties(0),
	scanned(false),
	hasAPE(false),
	hasID3v1(false),
	hasID3v2(false) {}

  ~FilePrivate()
  {
	delete ID3v2Header;
	delete properties;
  }

  long APELocation;
  uint APESize;

  long ID3v1Location;

  ID3v2::Header *ID3v2Header;
  long ID3v2Location;
  uint ID3v2Size;

  TagUnion tag;

  Properties *properties;
  bool scanned;

  // These indicate whether the file *on disk* has these tags, not if
  // this data structure does.  This is used in computing offsets.

  bool hasAPE;
  bool hasID3v1;
  bool hasID3v2;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

MPC::File::File(FileName file, bool readProperties,
				Properties::ReadStyle propertiesStyle) : TagLib::File(file)
{
  d = new FilePrivate;
  read(readProperties, propertiesStyle);
}

MPC::File::File(IOStream *stream, bool readProperties,
				Properties::ReadStyle propertiesStyle) : TagLib::File(stream)
{
  d = new FilePrivate;
  read(readProperties, propertiesStyle);
}

MPC::File::~File()
{
  delete d;
}

TagLib::Tag *MPC::File::tag() const
{
  return &d->tag;
}

PropertyMap MPC::File::properties() const
{
  if(d->hasAPE)
	return d->tag.access<APE::Tag>(MPCAPEIndex, false)->properties();
  if(d->hasID3v1)
	return d->tag.access<ID3v1::Tag>(MPCID3v1Index, false)->properties();
  return PropertyMap();
}

void MPC::File::removeUnsupportedProperties(const StringList &properties)
{
  if(d->hasAPE)
	d->tag.access<APE::Tag>(MPCAPEIndex, false)->removeUnsupportedProperties(properties);
  if(d->hasID3v1)
	d->tag.access<ID3v1::Tag>(MPCID3v1Index, false)->removeUnsupportedProperties(properties);
}

PropertyMap MPC::File::setProperties(const PropertyMap &properties)
{
  if(d->hasAPE)
	return d->tag.access<APE::Tag>(MPCAPEIndex, false)->setProperties(properties);
  else if(d->hasID3v1)
	return d->tag.access<ID3v1::Tag>(MPCID3v1Index, false)->setProperties(properties);
  else
	return d->tag.access<APE::Tag>(APE, true)->setProperties(properties);
}

MPC::Properties *MPC::File::audioProperties() const
{
  return d->properties;
}

bool MPC::File::save()
{
  if(readOnly()) {
	debug("MPC::File::save() -- File is read only.");
	return false;
  }

  // Possibly strip ID3v2 tag

  if(d->hasID3v2 && !d->ID3v2Header) {
	removeBlock(d->ID3v2Location, d->ID3v2Size);
	d->hasID3v2 = false;
	if(d->hasID3v1)
	  d->ID3v1Location -= d->ID3v2Size;
	if(d->hasAPE)
	  d->APELocation -= d->ID3v2Size;
  }

  // Update ID3v1 tag

  if(ID3v1Tag()) {
	if(d->hasID3v1) {
	  seek(d->ID3v1Location);
	  writeBlock(ID3v1Tag()->render());
	}
	else {
	  seek(0, End);
	  d->ID3v1Location = tell();
	  writeBlock(ID3v1Tag()->render());
	  d->hasID3v1 = true;
	}
  } else
	if(d->hasID3v1) {
	  removeBlock(d->ID3v1Location, 128);
	  d->hasID3v1 = false;
	  if(d->hasAPE) {
		if(d->APELocation > d->ID3v1Location)
		  d->APELocation -= 128;
	  }
	}

  // Update APE tag

  if(APETag()) {
	if(d->hasAPE)
	  insert(APETag()->render(), d->APELocation, d->APESize);
	else {
	  if(d->hasID3v1)  {
		insert(APETag()->render(), d->ID3v1Location, 0);
		d->APESize = APETag()->footer()->completeTagSize();
		d->hasAPE = true;
		d->APELocation = d->ID3v1Location;
		d->ID3v1Location += d->APESize;
	  }
	  else {
		seek(0, End);
		d->APELocation = tell();
		writeBlock(APETag()->render());
		d->APESize = APETag()->footer()->completeTagSize();
		d->hasAPE = true;
	  }
	}
  }
  else
	if(d->hasAPE) {
	  removeBlock(d->APELocation, d->APESize);
	  d->hasAPE = false;
	  if(d->hasID3v1) {
		if(d->ID3v1Location > d->APELocation)
		  d->ID3v1Location -= d->APESize;
	  }
	}

  return true;
}

ID3v1::Tag *MPC::File::ID3v1Tag(bool create)
{
  return d->tag.access<ID3v1::Tag>(MPCID3v1Index, create);
}

APE::Tag *MPC::File::APETag(bool create)
{
  return d->tag.access<APE::Tag>(MPCAPEIndex, create);
}

void MPC::File::strip(int tags)
{
  if(tags & ID3v1) {
	d->tag.set(MPCID3v1Index, 0);
	APETag(true);
  }

  if(tags & ID3v2) {
	delete d->ID3v2Header;
	d->ID3v2Header = 0;
  }

  if(tags & APE) {
	d->tag.set(MPCAPEIndex, 0);

	if(!ID3v1Tag())
	  APETag(true);
  }
}

void MPC::File::remove(int tags)
{
  strip(tags);
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void MPC::File::read(bool readProperties, Properties::ReadStyle /* propertiesStyle */)
{
  // Look for an ID3v1 tag

  d->ID3v1Location = findID3v1();

  if(d->ID3v1Location >= 0) {
	d->tag.set(MPCID3v1Index, new ID3v1::Tag(this, d->ID3v1Location));
	d->hasID3v1 = true;
  }

  // Look for an APE tag

  findAPE();

  d->APELocation = findAPE();

  if(d->APELocation >= 0) {
	d->tag.set(MPCAPEIndex, new APE::Tag(this, d->APELocation));

	d->APESize = APETag()->footer()->completeTagSize();
	d->APELocation = d->APELocation + APETag()->footer()->size() - d->APESize;
	d->hasAPE = true;
  }

  if(!d->hasID3v1)
	APETag(true);

  // Look for and skip an ID3v2 tag

  d->ID3v2Location = findID3v2();

  if(d->ID3v2Location >= 0) {
	seek(d->ID3v2Location);
	d->ID3v2Header = new ID3v2::Header(readBlock(ID3v2::Header::size()));
	d->ID3v2Size = d->ID3v2Header->completeTagSize();
	d->hasID3v2 = true;
  }

  if(d->hasID3v2)
	seek(d->ID3v2Location + d->ID3v2Size);
  else
	seek(0);

  // Look for MPC metadata

  if(readProperties) {
	d->properties = new Properties(readBlock(MPC::HeaderSize),
								   length() - d->ID3v2Size - d->APESize);
  }
}

long MPC::File::findAPE()
{
  if(!isValid())
	return -1;

  if(d->hasID3v1)
	seek(-160, End);
  else
	seek(-32, End);

  long p = tell();

  if(readBlock(8) == APE::Tag::fileIdentifier())
	return p;

  return -1;
}

long MPC::File::findID3v1()
{
  if(!isValid())
	return -1;

  seek(-128, End);
  long p = tell();

  if(readBlock(3) == ID3v1::Tag::fileIdentifier())
	return p;

  return -1;
}

long MPC::File::findID3v2()
{
  if(!isValid())
	return -1;

  seek(0);

  if(readBlock(3) == ID3v2::Header::fileIdentifier())
	return 0;

  return -1;
}

/*** End of inlined file: mpcfile.cpp ***/


/*** Start of inlined file: mpcproperties.cpp ***/
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

#include <bitset>

using namespace TagLib;

class MPC::Properties::PropertiesPrivate
{
public:
  PropertiesPrivate(const ByteVector &d, long length, ReadStyle s) :
	data(d),
	streamLength(length),
	style(s),
	version(0),
	length(0),
	bitrate(0),
	sampleRate(0),
	channels(0),
	totalFrames(0),
	sampleFrames(0) {}

  ByteVector data;
  long streamLength;
  ReadStyle style;
  int version;
  int length;
  int bitrate;
  int sampleRate;
  int channels;
  uint totalFrames;
  uint sampleFrames;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

MPC::Properties::Properties(const ByteVector &data, long streamLength, ReadStyle style) : AudioProperties(style)
{
  d = new PropertiesPrivate(data, streamLength, style);
  read();
}

MPC::Properties::~Properties()
{
  delete d;
}

int MPC::Properties::length() const
{
  return d->length;
}

int MPC::Properties::bitrate() const
{
  return d->bitrate;
}

int MPC::Properties::sampleRate() const
{
  return d->sampleRate;
}

int MPC::Properties::channels() const
{
  return d->channels;
}

int MPC::Properties::mpcVersion() const
{
  return d->version;
}

uint MPC::Properties::totalFrames() const
{
  return d->totalFrames;
}

uint MPC::Properties::sampleFrames() const
{
  return d->sampleFrames;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

static const unsigned short sftable [4] = { 44100, 48000, 37800, 32000 };

void MPC::Properties::read()
{
  if(!d->data.startsWith("MP+"))
	return;

  d->version = d->data[3] & 15;

  if(d->version >= 7) {
	d->totalFrames = d->data.mid(4, 4).toUInt(false);

	std::bitset<32> flags(TAGLIB_CONSTRUCT_BITSET(d->data.mid(8, 4).toUInt(false)));
	d->sampleRate = sftable[flags[17] * 2 + flags[16]];
	d->channels = 2;

	uint gapless = d->data.mid(5, 4).toUInt(false);
	bool trueGapless = (gapless >> 31) & 0x0001;
	if(trueGapless) {
	  uint lastFrameSamples = (gapless >> 20) & 0x07FF;
	  d->sampleFrames = d->totalFrames * 1152 - lastFrameSamples;
	}
	else
	  d->sampleFrames = d->totalFrames * 1152 - 576;
  }
  else {
	uint headerData = d->data.mid(0, 4).toUInt(false);

	d->bitrate = (headerData >> 23) & 0x01ff;
	d->version = (headerData >> 11) & 0x03ff;
	d->sampleRate = 44100;
	d->channels = 2;

	if(d->version >= 5)
	  d->totalFrames = d->data.mid(4, 4).toUInt(false);
	else
	  d->totalFrames = d->data.mid(6, 2).toUInt(false);

	d->sampleFrames = d->totalFrames * 1152 - 576;
  }

  d->length = d->sampleRate > 0 ? (d->sampleFrames + (d->sampleRate / 2)) / d->sampleRate : 0;

  if(!d->bitrate)
	d->bitrate = d->length > 0 ? ((d->streamLength * 8L) / d->length) / 1000 : 0;
}

/*** End of inlined file: mpcproperties.cpp ***/


/*** Start of inlined file: mp4file.cpp ***/
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace TagLib;

class MP4::File::FilePrivate
{
public:
  FilePrivate() : tag(0), atoms(0), properties(0)
  {
  }

  ~FilePrivate()
  {
	if(atoms) {
		delete atoms;
		atoms = 0;
	}
	if(tag) {
		delete tag;
		tag = 0;
	}
	if(properties) {
		delete properties;
		properties = 0;
	}
  }

  MP4::Tag *tag;
  MP4::Atoms *atoms;
  MP4::Properties *properties;
};

MP4::File::File(FileName file, bool readProperties, AudioProperties::ReadStyle audioPropertiesStyle)
	: TagLib::File(file)
{
  d = new FilePrivate;
  read(readProperties, audioPropertiesStyle);
}

MP4::File::File(IOStream *stream, bool readProperties, AudioProperties::ReadStyle audioPropertiesStyle)
	: TagLib::File(stream)
{
  d = new FilePrivate;
  read(readProperties, audioPropertiesStyle);
}

MP4::File::~File()
{
  delete d;
}

MP4::Tag *
MP4::File::tag() const
{
  return d->tag;
}

MP4::Properties *
MP4::File::audioProperties() const
{
  return d->properties;
}

bool
MP4::File::checkValid(const MP4::AtomList &list)
{
  for(uint i = 0; i < list.size(); i++) {
	if(list[i]->length == 0)
	  return false;
	if(!checkValid(list[i]->children))
	  return false;
  }
  return true;
}

void
MP4::File::read(bool readProperties, Properties::ReadStyle audioPropertiesStyle)
{
  if(!isValid())
	return;

  d->atoms = new Atoms(this);
  if (!checkValid(d->atoms->atoms)) {
	setValid(false);
	return;
  }

  // must have a moov atom, otherwise consider it invalid
  MP4::Atom *moov = d->atoms->find("moov");
  if(!moov) {
	setValid(false);
	return;
  }

  d->tag = new Tag(this, d->atoms);
  if(readProperties) {
	d->properties = new Properties(this, d->atoms, audioPropertiesStyle);
  }
}

bool
MP4::File::save()
{
  if(readOnly()) {
	debug("MP4::File::save() -- File is read only.");
	return false;
  }

  if(!isValid()) {
	debug("MP4::File::save() -- Trying to save invalid file.");
	return false;
  }

  return d->tag->save();
}

/*** End of inlined file: mp4file.cpp ***/


/*** Start of inlined file: mp4atom.cpp ***/
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace TagLib;

const char *MP4::Atom::containers[11] = {
	"moov", "udta", "mdia", "meta", "ilst",
	"stbl", "minf", "moof", "traf", "trak",
	"stsd"
};

MP4::Atom::Atom(File *file)
{
  offset = file->tell();
  ByteVector header = file->readBlock(8);
  if (header.size() != 8) {
	// The atom header must be 8 bytes long, otherwise there is either
	// trailing garbage or the file is truncated
	debug("MP4: Couldn't read 8 bytes of data for atom header");
	length = 0;
	file->seek(0, File::End);
	return;
  }

  length = header.mid(0, 4).toUInt();

  if (length == 1) {
	long long longLength = file->readBlock(8).toLongLong();
	if (longLength >= 8 && longLength <= 0xFFFFFFFF) {
		// The atom has a 64-bit length, but it's actually a 32-bit value
		length = (long)longLength;
	}
	else {
		debug("MP4: 64-bit atoms are not supported");
		length = 0;
		file->seek(0, File::End);
		return;
	}
  }
  if (length < 8) {
	debug("MP4: Invalid atom size");
	length = 0;
	file->seek(0, File::End);
	return;
  }

  name = header.mid(4, 4);

  for(int i = 0; i < numContainers; i++) {
	if(name == containers[i]) {
	  if(name == "meta") {
		file->seek(4, File::Current);
	  }
	  else if(name == "stsd") {
		file->seek(8, File::Current);
	  }
	  while(file->tell() < offset + length) {
		MP4::Atom *child = new MP4::Atom(file);
		children.append(child);
		if (child->length == 0)
		  return;
	  }
	  return;
	}
  }

  file->seek(offset + length);
}

MP4::Atom::~Atom()
{
  for(unsigned int i = 0; i < children.size(); i++) {
	delete children[i];
  }
  children.clear();
}

MP4::Atom *
MP4::Atom::find(const char *name1, const char *name2, const char *name3, const char *name4)
{
  if(name1 == 0) {
	return this;
  }
  for(unsigned int i = 0; i < children.size(); i++) {
	if(children[i]->name == name1) {
	  return children[i]->find(name2, name3, name4);
	}
  }
  return 0;
}

MP4::AtomList
MP4::Atom::findall(const char *name, bool recursive)
{
  MP4::AtomList result;
  for(unsigned int i = 0; i < children.size(); i++) {
	if(children[i]->name == name) {
	  result.append(children[i]);
	}
	if(recursive) {
	  result.append(children[i]->findall(name, recursive));
	}
  }
  return result;
}

bool
MP4::Atom::path(MP4::AtomList &path, const char *name1, const char *name2, const char *name3)
{
  path.append(this);
  if(name1 == 0) {
	return true;
  }
  for(unsigned int i = 0; i < children.size(); i++) {
	if(children[i]->name == name1) {
	  return children[i]->path(path, name2, name3);
	}
  }
  return false;
}

MP4::Atoms::Atoms(File *file)
{
  file->seek(0, File::End);
  long end = file->tell();
  file->seek(0);
  while(file->tell() + 8 <= end) {
	MP4::Atom *atom = new MP4::Atom(file);
	atoms.append(atom);
	if (atom->length == 0)
	  break;
  }
}

MP4::Atoms::~Atoms()
{
  for(unsigned int i = 0; i < atoms.size(); i++) {
	delete atoms[i];
  }
  atoms.clear();
}

MP4::Atom *
MP4::Atoms::find(const char *name1, const char *name2, const char *name3, const char *name4)
{
  for(unsigned int i = 0; i < atoms.size(); i++) {
	if(atoms[i]->name == name1) {
	  return atoms[i]->find(name2, name3, name4);
	}
  }
  return 0;
}

MP4::AtomList
MP4::Atoms::path(const char *name1, const char *name2, const char *name3, const char *name4)
{
  MP4::AtomList path;
  for(unsigned int i = 0; i < atoms.size(); i++) {
	if(atoms[i]->name == name1) {
	  if(!atoms[i]->path(path, name2, name3, name4)) {
		path.clear();
	  }
	  return path;
	}
  }
  return path;
}

/*** End of inlined file: mp4atom.cpp ***/


/*** Start of inlined file: mp4tag.cpp ***/
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace TagLib;

class MP4::Tag::TagPrivate
{
public:
  TagPrivate() : file(0), atoms(0) {}
  ~TagPrivate() {}
  TagLib::File *file;
  Atoms *atoms;
  ItemListMap items;
};

MP4::Tag::Tag()
{
  d = new TagPrivate;
}

MP4::Tag::Tag(TagLib::File *file, MP4::Atoms *atoms)
{
  d = new TagPrivate;
  d->file = file;
  d->atoms = atoms;

  MP4::Atom *ilst = atoms->find("moov", "udta", "meta", "ilst");
  if(!ilst) {
	//debug("Atom moov.udta.meta.ilst not found.");
	return;
  }

  for(unsigned int i = 0; i < ilst->children.size(); i++) {
	MP4::Atom *atom = ilst->children[i];
	file->seek(atom->offset + 8);
	if(atom->name == "----") {
	  parseFreeForm(atom, file);
	}
	else if(atom->name == "trkn" || atom->name == "disk") {
	  parseIntPair(atom, file);
	}
	else if(atom->name == "cpil" || atom->name == "pgap" || atom->name == "pcst" ||
			atom->name == "hdvd") {
	  parseBool(atom, file);
	}
	else if(atom->name == "tmpo") {
	  parseInt(atom, file);
	}
	else if(atom->name == "tvsn" || atom->name == "tves" || atom->name == "cnID" ||
			atom->name == "sfID" || atom->name == "atID" || atom->name == "geID") {
	  parseUInt(atom, file);
	}
	else if(atom->name == "plID") {
	  parseLongLong(atom, file);
	}
	else if(atom->name == "stik" || atom->name == "rtng" || atom->name == "akID") {
	  parseByte(atom, file);
	}
	else if(atom->name == "gnre") {
	  parseGnre(atom, file);
	}
	else if(atom->name == "covr") {
	  parseCovr(atom, file);
	}
	else {
	  parseText(atom, file);
	}
  }
}

MP4::Tag::~Tag()
{
  delete d;
}

MP4::AtomDataList
MP4::Tag::parseData2(MP4::Atom *atom, TagLib::File *file, int expectedFlags, bool freeForm)
{
  AtomDataList result;
  ByteVector data = file->readBlock(atom->length - 8);
  int i = 0;
  unsigned int pos = 0;
  while(pos < data.size()) {
	int length = data.mid(pos, 4).toUInt();
	ByteVector name = data.mid(pos + 4, 4);
	int flags = data.mid(pos + 8, 4).toUInt();
	if(freeForm && i < 2) {
	  if(i == 0 && name != "mean") {
		debug("MP4: Unexpected atom \"" + name + "\", expecting \"mean\"");
		return result;
	  }
	  else if(i == 1 && name != "name") {
		debug("MP4: Unexpected atom \"" + name + "\", expecting \"name\"");
		return result;
	  }
	  result.append(AtomData(AtomDataType(flags), data.mid(pos + 12, length - 12)));
	}
	else {
	  if(name != "data") {
		debug("MP4: Unexpected atom \"" + name + "\", expecting \"data\"");
		return result;
	  }
	  if(expectedFlags == -1 || flags == expectedFlags) {
		result.append(AtomData(AtomDataType(flags), data.mid(pos + 16, length - 16)));
	  }
	}
	pos += length;
	i++;
  }
  return result;
}

ByteVectorList
MP4::Tag::parseData(MP4::Atom *atom, TagLib::File *file, int expectedFlags, bool freeForm)
{
  AtomDataList data = parseData2(atom, file, expectedFlags, freeForm);
  ByteVectorList result;
  for(uint i = 0; i < data.size(); i++) {
	result.append(data[i].data);
  }
  return result;
}

void
MP4::Tag::parseInt(MP4::Atom *atom, TagLib::File *file)
{
  ByteVectorList data = parseData(atom, file);
  if(data.size()) {
	d->items.insert(atom->name, (int)data[0].toShort());
  }
}

void
MP4::Tag::parseUInt(MP4::Atom *atom, TagLib::File *file)
{
  ByteVectorList data = parseData(atom, file);
  if(data.size()) {
	d->items.insert(atom->name, data[0].toUInt());
  }
}

void
MP4::Tag::parseLongLong(MP4::Atom *atom, TagLib::File *file)
{
  ByteVectorList data = parseData(atom, file);
  if(data.size()) {
	d->items.insert(atom->name, data[0].toLongLong());
  }
}

void
MP4::Tag::parseByte(MP4::Atom *atom, TagLib::File *file)
{
  ByteVectorList data = parseData(atom, file);
  if(data.size()) {
	d->items.insert(atom->name, (uchar)data[0].at(0));
  }
}

void
MP4::Tag::parseGnre(MP4::Atom *atom, TagLib::File *file)
{
  ByteVectorList data = parseData(atom, file);
  if(data.size()) {
	int idx = (int)data[0].toShort();
	if(!d->items.contains("\251gen") && idx > 0) {
	  d->items.insert("\251gen", StringList(ID3v1::genre(idx - 1)));
	}
  }
}

void
MP4::Tag::parseIntPair(MP4::Atom *atom, TagLib::File *file)
{
  ByteVectorList data = parseData(atom, file);
  if(data.size()) {
	int a = data[0].mid(2, 2).toShort();
	int b = data[0].mid(4, 2).toShort();
	d->items.insert(atom->name, MP4::Item(a, b));
  }
}

void
MP4::Tag::parseBool(MP4::Atom *atom, TagLib::File *file)
{
  ByteVectorList data = parseData(atom, file);
  if(data.size()) {
	bool value = data[0].size() ? data[0][0] != '\0' : false;
	d->items.insert(atom->name, value);
  }
}

void
MP4::Tag::parseText(MP4::Atom *atom, TagLib::File *file, int expectedFlags)
{
  ByteVectorList data = parseData(atom, file, expectedFlags);
  if(data.size()) {
	StringList value;
	for(unsigned int i = 0; i < data.size(); i++) {
	  value.append(String(data[i], String::UTF8));
	}
	d->items.insert(atom->name, value);
  }
}

void
MP4::Tag::parseFreeForm(MP4::Atom *atom, TagLib::File *file)
{
  AtomDataList data = parseData2(atom, file, -1, true);
  if(data.size() > 2) {
	String name = "----:" + String(data[0].data, String::UTF8) + ':' + String(data[1].data, String::UTF8);
	AtomDataType type = data[2].type;
	for(uint i = 2; i < data.size(); i++) {
	  if(data[i].type != type) {
		debug("MP4: We currently don't support values with multiple types");
		break;
	  }
	}
	if(type == TypeUTF8) {
	  StringList value;
	  for(uint i = 2; i < data.size(); i++) {
		value.append(String(data[i].data, String::UTF8));
	  }
	  Item item(value);
	  item.setAtomDataType(type);
	  d->items.insert(name, item);
	}
	else {
	  ByteVectorList value;
	  for(uint i = 2; i < data.size(); i++) {
		value.append(data[i].data);
	  }
	  Item item(value);
	  item.setAtomDataType(type);
	  d->items.insert(name, item);
	}
  }
}

void
MP4::Tag::parseCovr(MP4::Atom *atom, TagLib::File *file)
{
  MP4::CoverArtList value;
  ByteVector data = file->readBlock(atom->length - 8);
  unsigned int pos = 0;
  while(pos < data.size()) {
	int length = data.mid(pos, 4).toUInt();
	ByteVector name = data.mid(pos + 4, 4);
	int flags = data.mid(pos + 8, 4).toUInt();
	if(name != "data") {
	  debug("MP4: Unexpected atom \"" + name + "\", expecting \"data\"");
	  break;
	}
	if(flags == TypeJPEG || flags == TypePNG || flags == TypeBMP || flags == TypeGIF) {
	  value.append(MP4::CoverArt(MP4::CoverArt::Format(flags),
								 data.mid(pos + 16, length - 16)));
	}
	pos += length;
  }
  if(value.size() > 0)
	d->items.insert(atom->name, value);
}

ByteVector
MP4::Tag::padIlst(const ByteVector &data, int length)
{
  if (length == -1) {
	length = ((data.size() + 1023) & ~1023) - data.size();
  }
  return renderAtom("free", ByteVector(length, '\1'));
}

ByteVector
MP4::Tag::renderAtom(const ByteVector &name, const ByteVector &data)
{
  return ByteVector::fromUInt(data.size() + 8) + name + data;
}

ByteVector
MP4::Tag::renderData(const ByteVector &name, int flags, const ByteVectorList &data)
{
  ByteVector result;
  for(unsigned int i = 0; i < data.size(); i++) {
	result.append(renderAtom("data", ByteVector::fromUInt(flags) + ByteVector(4, '\0') + data[i]));
  }
  return renderAtom(name, result);
}

ByteVector
MP4::Tag::renderBool(const ByteVector &name, MP4::Item &item)
{
  ByteVectorList data;
  data.append(ByteVector(1, item.toBool() ? '\1' : '\0'));
  return renderData(name, TypeInteger, data);
}

ByteVector
MP4::Tag::renderInt(const ByteVector &name, MP4::Item &item)
{
  ByteVectorList data;
  data.append(ByteVector::fromShort(static_cast<short>(item.toInt())));
  return renderData(name, TypeInteger, data);
}

ByteVector
MP4::Tag::renderUInt(const ByteVector &name, MP4::Item &item)
{
  ByteVectorList data;
  data.append(ByteVector::fromUInt(item.toUInt()));
  return renderData(name, TypeInteger, data);
}

ByteVector
MP4::Tag::renderLongLong(const ByteVector &name, MP4::Item &item)
{
  ByteVectorList data;
  data.append(ByteVector::fromLongLong(item.toLongLong()));
  return renderData(name, TypeInteger, data);
}

ByteVector
MP4::Tag::renderByte(const ByteVector &name, MP4::Item &item)
{
  ByteVectorList data;
  data.append(ByteVector(1, item.toByte()));
  return renderData(name, TypeInteger, data);
}

ByteVector
MP4::Tag::renderIntPair(const ByteVector &name, MP4::Item &item)
{
  ByteVectorList data;
  data.append(ByteVector(2, '\0') +
			  ByteVector::fromShort(static_cast<short>(item.toIntPair().first)) +
			  ByteVector::fromShort(static_cast<short>(item.toIntPair().second)) +
			  ByteVector(2, '\0'));
  return renderData(name, TypeImplicit, data);
}

ByteVector
MP4::Tag::renderIntPairNoTrailing(const ByteVector &name, MP4::Item &item)
{
  ByteVectorList data;
  data.append(ByteVector(2, '\0') +
			  ByteVector::fromShort(static_cast<short>(item.toIntPair().first)) +
			  ByteVector::fromShort(static_cast<short>(item.toIntPair().second)));
  return renderData(name, TypeImplicit, data);
}

ByteVector
MP4::Tag::renderText(const ByteVector &name, MP4::Item &item, int flags)
{
  ByteVectorList data;
  StringList value = item.toStringList();
  for(unsigned int i = 0; i < value.size(); i++) {
	data.append(value[i].data(String::UTF8));
  }
  return renderData(name, flags, data);
}

ByteVector
MP4::Tag::renderCovr(const ByteVector &name, MP4::Item &item)
{
  ByteVector data;
  MP4::CoverArtList value = item.toCoverArtList();
  for(unsigned int i = 0; i < value.size(); i++) {
	data.append(renderAtom("data", ByteVector::fromUInt(value[i].format()) +
								   ByteVector(4, '\0') + value[i].data()));
  }
  return renderAtom(name, data);
}

ByteVector
MP4::Tag::renderFreeForm(const String &name, MP4::Item &item)
{
  StringList header = StringList::split(name, ":");
  if (header.size() != 3) {
	debug("MP4: Invalid free-form item name \"" + name + "\"");
	return ByteVector::null;
  }
  ByteVector data;
  data.append(renderAtom("mean", ByteVector::fromUInt(0) + header[1].data(String::UTF8)));
  data.append(renderAtom("name", ByteVector::fromUInt(0) + header[2].data(String::UTF8)));
  AtomDataType type = item.atomDataType();
  if(type == TypeUndefined) {
	if(!item.toStringList().isEmpty()) {
	  type = TypeUTF8;
	}
	else {
	  type = TypeImplicit;
	}
  }
  if(type == TypeUTF8) {
	StringList value = item.toStringList();
	for(unsigned int i = 0; i < value.size(); i++) {
	  data.append(renderAtom("data", ByteVector::fromUInt(type) + ByteVector(4, '\0') + value[i].data(String::UTF8)));
	}
  }
  else {
	ByteVectorList value = item.toByteVectorList();
	for(unsigned int i = 0; i < value.size(); i++) {
	  data.append(renderAtom("data", ByteVector::fromUInt(type) + ByteVector(4, '\0') + value[i]));
	}
  }
  return renderAtom("----", data);
}

bool
MP4::Tag::save()
{
  ByteVector data;
  for(MP4::ItemListMap::Iterator i = d->items.begin(); i != d->items.end(); i++) {
	const String name = i->first;
	if(name.startsWith("----")) {
	  data.append(renderFreeForm(name, i->second));
	}
	else if(name == "trkn") {
	  data.append(renderIntPair(name.data(String::Latin1), i->second));
	}
	else if(name == "disk") {
	  data.append(renderIntPairNoTrailing(name.data(String::Latin1), i->second));
	}
	else if(name == "cpil" || name == "pgap" || name == "pcst" || name == "hdvd") {
	  data.append(renderBool(name.data(String::Latin1), i->second));
	}
	else if(name == "tmpo") {
	  data.append(renderInt(name.data(String::Latin1), i->second));
	}
	else if(name == "tvsn" || name == "tves" || name == "cnID" ||
			name == "sfID" || name == "atID" || name == "geID") {
	  data.append(renderUInt(name.data(String::Latin1), i->second));
	}
	else if(name == "plID") {
	  data.append(renderLongLong(name.data(String::Latin1), i->second));
	}
	else if(name == "stik" || name == "rtng" || name == "akID") {
	  data.append(renderByte(name.data(String::Latin1), i->second));
	}
	else if(name == "covr") {
	  data.append(renderCovr(name.data(String::Latin1), i->second));
	}
	else if(name.size() == 4){
	  data.append(renderText(name.data(String::Latin1), i->second));
	}
	else {
	  debug("MP4: Unknown item name \"" + name + "\"");
	}
  }
  data = renderAtom("ilst", data);

  AtomList path = d->atoms->path("moov", "udta", "meta", "ilst");
  if(path.size() == 4) {
	saveExisting(data, path);
  }
  else {
	saveNew(data);
  }

  return true;
}

void
MP4::Tag::updateParents(AtomList &path, long delta, int ignore)
{
  for(unsigned int i = 0; i < path.size() - ignore; i++) {
	d->file->seek(path[i]->offset);
	long size = d->file->readBlock(4).toUInt();
	// 64-bit
	if (size == 1) {
	  d->file->seek(4, File::Current); // Skip name
	  long long longSize = d->file->readBlock(8).toLongLong();
	  // Seek the offset of the 64-bit size
	  d->file->seek(path[i]->offset + 8);
	  d->file->writeBlock(ByteVector::fromLongLong(longSize + delta));
	}
	// 32-bit
	else {
	  d->file->seek(path[i]->offset);
	  d->file->writeBlock(ByteVector::fromUInt(size + delta));
	}
  }
}

void
MP4::Tag::updateOffsets(long delta, long offset)
{
  MP4::Atom *moov = d->atoms->find("moov");
  if(moov) {
	MP4::AtomList stco = moov->findall("stco", true);
	for(unsigned int i = 0; i < stco.size(); i++) {
	  MP4::Atom *atom = stco[i];
	  if(atom->offset > offset) {
		atom->offset += delta;
	  }
	  d->file->seek(atom->offset + 12);
	  ByteVector data = d->file->readBlock(atom->length - 12);
	  unsigned int count = data.mid(0, 4).toUInt();
	  d->file->seek(atom->offset + 16);
	  int pos = 4;
	  while(count--) {
		long o = data.mid(pos, 4).toUInt();
		if(o > offset) {
		  o += delta;
		}
		d->file->writeBlock(ByteVector::fromUInt(o));
		pos += 4;
	  }
	}

	MP4::AtomList co64 = moov->findall("co64", true);
	for(unsigned int i = 0; i < co64.size(); i++) {
	  MP4::Atom *atom = co64[i];
	  if(atom->offset > offset) {
		atom->offset += delta;
	  }
	  d->file->seek(atom->offset + 12);
	  ByteVector data = d->file->readBlock(atom->length - 12);
	  unsigned int count = data.mid(0, 4).toUInt();
	  d->file->seek(atom->offset + 16);
	  int pos = 4;
	  while(count--) {
		long long o = data.mid(pos, 8).toLongLong();
		if(o > offset) {
		  o += delta;
		}
		d->file->writeBlock(ByteVector::fromLongLong(o));
		pos += 8;
	  }
	}
  }

  MP4::Atom *moof = d->atoms->find("moof");
  if(moof) {
	MP4::AtomList tfhd = moof->findall("tfhd", true);
	for(unsigned int i = 0; i < tfhd.size(); i++) {
	  MP4::Atom *atom = tfhd[i];
	  if(atom->offset > offset) {
		atom->offset += delta;
	  }
	  d->file->seek(atom->offset + 9);
	  ByteVector data = d->file->readBlock(atom->offset - 9);
	  unsigned int flags = (ByteVector(1, '\0') + data.mid(0, 3)).toUInt();
	  if(flags & 1) {
		long long o = data.mid(7, 8).toLongLong();
		if(o > offset) {
		  o += delta;
		}
		d->file->seek(atom->offset + 16);
		d->file->writeBlock(ByteVector::fromLongLong(o));
	  }
	}
  }
}

void
MP4::Tag::saveNew(ByteVector &data)
{
  data = renderAtom("meta", TagLib::ByteVector(4, '\0') +
					renderAtom("hdlr", TagLib::ByteVector(8, '\0') + TagLib::ByteVector("mdirappl") + TagLib::ByteVector(9, '\0')) +
					data + padIlst(data));

  AtomList path = d->atoms->path("moov", "udta");
  if(path.size() != 2) {
	path = d->atoms->path("moov");
	data = renderAtom("udta", data);
  }

  long offset = path[path.size() - 1]->offset + 8;
  d->file->insert(data, offset, 0);

  updateParents(path, data.size());
  updateOffsets(data.size(), offset);
}

void
MP4::Tag::saveExisting(ByteVector &data, AtomList &path)
{
  MP4::Atom *ilst = path[path.size() - 1];
  long offset = ilst->offset;
  long length = ilst->length;

  MP4::Atom *meta = path[path.size() - 2];
  AtomList::Iterator index = meta->children.find(ilst);

  // check if there is an atom before 'ilst', and possibly use it as padding
  if(index != meta->children.begin()) {
	AtomList::Iterator prevIndex = index;
	prevIndex--;
	MP4::Atom *prev = *prevIndex;
	if(prev->name == "free") {
	  offset = prev->offset;
	  length += prev->length;
	}
  }
  // check if there is an atom after 'ilst', and possibly use it as padding
  AtomList::Iterator nextIndex = index;
  nextIndex++;
  if(nextIndex != meta->children.end()) {
	MP4::Atom *next = *nextIndex;
	if(next->name == "free") {
	  length += next->length;
	}
  }

  long delta = data.size() - length;
  if(delta > 0 || (delta < 0 && delta > -8)) {
	data.append(padIlst(data));
	delta = data.size() - length;
  }
  else if(delta < 0) {
	data.append(padIlst(data, -delta - 8));
	delta = 0;
  }

  d->file->insert(data, offset, length);

  if(delta) {
	updateParents(path, delta, 1);
	updateOffsets(delta, offset);
  }
}

String
MP4::Tag::title() const
{
  if(d->items.contains("\251nam"))
	return d->items["\251nam"].toStringList().toString(", ");
  return String::null;
}

String
MP4::Tag::artist() const
{
  if(d->items.contains("\251ART"))
	return d->items["\251ART"].toStringList().toString(", ");
  return String::null;
}

String
MP4::Tag::album() const
{
  if(d->items.contains("\251alb"))
	return d->items["\251alb"].toStringList().toString(", ");
  return String::null;
}

String
MP4::Tag::comment() const
{
  if(d->items.contains("\251cmt"))
	return d->items["\251cmt"].toStringList().toString(", ");
  return String::null;
}

String
MP4::Tag::genre() const
{
  if(d->items.contains("\251gen"))
	return d->items["\251gen"].toStringList().toString(", ");
  return String::null;
}

unsigned int
MP4::Tag::year() const
{
  if(d->items.contains("\251day"))
	return d->items["\251day"].toStringList().toString().toInt();
  return 0;
}

unsigned int
MP4::Tag::track() const
{
  if(d->items.contains("trkn"))
	return d->items["trkn"].toIntPair().first;
  return 0;
}

void
MP4::Tag::setTitle(const String &value)
{
  d->items["\251nam"] = StringList(value);
}

void
MP4::Tag::setArtist(const String &value)
{
  d->items["\251ART"] = StringList(value);
}

void
MP4::Tag::setAlbum(const String &value)
{
  d->items["\251alb"] = StringList(value);
}

void
MP4::Tag::setComment(const String &value)
{
  d->items["\251cmt"] = StringList(value);
}

void
MP4::Tag::setGenre(const String &value)
{
  d->items["\251gen"] = StringList(value);
}

void
MP4::Tag::setYear(uint value)
{
  d->items["\251day"] = StringList(String::number(value));
}

void
MP4::Tag::setTrack(uint value)
{
  d->items["trkn"] = MP4::Item(value, 0);
}

MP4::ItemListMap &
MP4::Tag::itemListMap()
{
  return d->items;
}

/*** End of inlined file: mp4tag.cpp ***/


/*** Start of inlined file: mp4item.cpp ***/
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace TagLib;

class MP4::Item::ItemPrivate : public RefCounter
{
public:
  ItemPrivate() : RefCounter(), valid(true), atomDataType(TypeUndefined) {}

  bool valid;
  AtomDataType atomDataType;
  union {
	bool m_bool;
	int m_int;
	IntPair m_intPair;
	uchar m_byte;
	uint m_uint;
	long long m_longlong;
  };
  StringList m_stringList;
  ByteVectorList m_byteVectorList;
  MP4::CoverArtList m_coverArtList;
};

MP4::Item::Item()
{
  d = new ItemPrivate;
  d->valid = false;
}

MP4::Item::Item(const Item &item) : d(item.d)
{
  d->ref();
}

MP4::Item &
MP4::Item::operator=(const Item &item)
{
  if(d->deref()) {
	delete d;
  }
  d = item.d;
  d->ref();
  return *this;
}

MP4::Item::~Item()
{
  if(d->deref()) {
	delete d;
  }
}

MP4::Item::Item(bool value)
{
  d = new ItemPrivate;
  d->m_bool = value;
}

MP4::Item::Item(int value)
{
  d = new ItemPrivate;
  d->m_int = value;
}

MP4::Item::Item(uchar value)
{
  d = new ItemPrivate;
  d->m_byte = value;
}

MP4::Item::Item(uint value)
{
  d = new ItemPrivate;
  d->m_uint = value;
}

MP4::Item::Item(long long value)
{
  d = new ItemPrivate;
  d->m_longlong = value;
}

MP4::Item::Item(int value1, int value2)
{
  d = new ItemPrivate;
  d->m_intPair.first = value1;
  d->m_intPair.second = value2;
}

MP4::Item::Item(const ByteVectorList &value)
{
  d = new ItemPrivate;
  d->m_byteVectorList = value;
}

MP4::Item::Item(const StringList &value)
{
  d = new ItemPrivate;
  d->m_stringList = value;
}

MP4::Item::Item(const MP4::CoverArtList &value)
{
  d = new ItemPrivate;
  d->m_coverArtList = value;
}

void MP4::Item::setAtomDataType(MP4::AtomDataType type)
{
  d->atomDataType = type;
}

MP4::AtomDataType MP4::Item::atomDataType() const
{
  return d->atomDataType;
}

bool
MP4::Item::toBool() const
{
  return d->m_bool;
}

int
MP4::Item::toInt() const
{
  return d->m_int;
}

uchar
MP4::Item::toByte() const
{
  return d->m_byte;
}

TagLib::uint
MP4::Item::toUInt() const
{
  return d->m_uint;
}

long long
MP4::Item::toLongLong() const
{
  return d->m_longlong;
}

MP4::Item::IntPair
MP4::Item::toIntPair() const
{
  return d->m_intPair;
}

StringList
MP4::Item::toStringList() const
{
  return d->m_stringList;
}

ByteVectorList
MP4::Item::toByteVectorList() const
{
  return d->m_byteVectorList;
}

MP4::CoverArtList
MP4::Item::toCoverArtList() const
{
  return d->m_coverArtList;
}

bool
MP4::Item::isValid() const
{
  return d->valid;
}

/*** End of inlined file: mp4item.cpp ***/


/*** Start of inlined file: mp4properties.cpp ***/
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace TagLib;

class MP4::Properties::PropertiesPrivate
{
public:
  PropertiesPrivate() : length(0), bitrate(0), sampleRate(0), channels(0), bitsPerSample(0), encrypted(false) {}

  int length;
  int bitrate;
  int sampleRate;
  int channels;
  int bitsPerSample;
  bool encrypted;
};

MP4::Properties::Properties(File *file, MP4::Atoms *atoms, ReadStyle style)
  : AudioProperties(style)
{
  d = new PropertiesPrivate;

  MP4::Atom *moov = atoms->find("moov");
  if(!moov) {
	debug("MP4: Atom 'moov' not found");
	return;
  }

  MP4::Atom *trak = 0;
  ByteVector data;

  MP4::AtomList trakList = moov->findall("trak");
  for (unsigned int i = 0; i < trakList.size(); i++) {
	trak = trakList[i];
	MP4::Atom *hdlr = trak->find("mdia", "hdlr");
	if(!hdlr) {
	  debug("MP4: Atom 'trak.mdia.hdlr' not found");
	  return;
	}
	file->seek(hdlr->offset);
	data = file->readBlock(hdlr->length);
	if(data.mid(16, 4) == "soun") {
	  break;
	}
	trak = 0;
  }
  if (!trak) {
	debug("MP4: No audio tracks");
	return;
  }

  MP4::Atom *mdhd = trak->find("mdia", "mdhd");
  if(!mdhd) {
	debug("MP4: Atom 'trak.mdia.mdhd' not found");
	return;
  }

  file->seek(mdhd->offset);
  data = file->readBlock(mdhd->length);
  uint version = data[8];
  if(version == 1) {
	if (data.size() < 36 + 8) {
	  debug("MP4: Atom 'trak.mdia.mdhd' is smaller than expected");
	  return;
	}
	long long unit = data.mid(28, 8).toLongLong();
	long long length = data.mid(36, 8).toLongLong();
	d->length = unit ? int(length / unit) : 0;
  }
  else {
	if (data.size() < 24 + 4) {
	  debug("MP4: Atom 'trak.mdia.mdhd' is smaller than expected");
	  return;
	}
	unsigned int unit = data.mid(20, 4).toUInt();
	unsigned int length = data.mid(24, 4).toUInt();
	d->length = unit ? length / unit : 0;
  }

  MP4::Atom *atom = trak->find("mdia", "minf", "stbl", "stsd");
  if(!atom) {
	return;
  }

  file->seek(atom->offset);
  data = file->readBlock(atom->length);
  if(data.mid(20, 4) == "mp4a") {
	d->channels = data.mid(40, 2).toShort();
	d->bitsPerSample = data.mid(42, 2).toShort();
	d->sampleRate = data.mid(46, 4).toUInt();
	if(data.mid(56, 4) == "esds" && data[64] == 0x03) {
	  long pos = 65;
	  if(data.mid(pos, 3) == "\x80\x80\x80") {
		pos += 3;
	  }
	  pos += 4;
	  if(data[pos] == 0x04) {
		pos += 1;
		if(data.mid(pos, 3) == "\x80\x80\x80") {
		  pos += 3;
		}
		pos += 10;
		d->bitrate = (data.mid(pos, 4).toUInt() + 500) / 1000;
	  }
	}
  }
  else if (data.mid(20, 4) == "alac") {
	if (atom->length == 88 && data.mid(56, 4) == "alac") {
	  d->bitsPerSample = data.at(69);
	  d->channels = data.at(73);
	  d->bitrate = data.mid(80, 4).toUInt() / 1000;
	  d->sampleRate = data.mid(84, 4).toUInt();
	}
  }

  MP4::Atom *drms = atom->find("drms");
  if(drms) {
	d->encrypted = true;
  }
}

MP4::Properties::~Properties()
{
  delete d;
}

int
MP4::Properties::channels() const
{
  return d->channels;
}

int
MP4::Properties::sampleRate() const
{
  return d->sampleRate;
}

int
MP4::Properties::length() const
{
  return d->length;
}

int
MP4::Properties::bitrate() const
{
  return d->bitrate;
}

int
MP4::Properties::bitsPerSample() const
{
  return d->bitsPerSample;
}

bool
MP4::Properties::isEncrypted() const
{
  return d->encrypted;
}

/*** End of inlined file: mp4properties.cpp ***/


/*** Start of inlined file: mp4coverart.cpp ***/
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace TagLib;

class MP4::CoverArt::CoverArtPrivate : public RefCounter
{
public:
  CoverArtPrivate() : RefCounter(), format(MP4::CoverArt::JPEG) {}

  Format format;
  ByteVector data;
};

MP4::CoverArt::CoverArt(Format format, const ByteVector &data)
{
  d = new CoverArtPrivate;
  d->format = format;
  d->data = data;
}

MP4::CoverArt::CoverArt(const CoverArt &item) : d(item.d)
{
  d->ref();
}

MP4::CoverArt &
MP4::CoverArt::operator=(const CoverArt &item)
{
  if(d->deref()) {
	delete d;
  }
  d = item.d;
  d->ref();
  return *this;
}

MP4::CoverArt::~CoverArt()
{
  if(d->deref()) {
	delete d;
  }
}

MP4::CoverArt::Format
MP4::CoverArt::format() const
{
  return d->format;
}

ByteVector
MP4::CoverArt::data() const
{
  return d->data;
}

/*** End of inlined file: mp4coverart.cpp ***/


/*** Start of inlined file: apetag.cpp ***/
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

#ifdef __SUNPRO_CC
// Sun Studio finds multiple specializations of Map because
// it considers specializations with and without class types
// to be different; this define forces Map to use only the
// specialization with the class keyword.
#define WANT_CLASS_INSTANTIATION_OF_MAP (1)
#endif

using namespace TagLib;
using namespace APE;

class APE::Tag::TagPrivate
{
public:
  TagPrivate() : file(0), footerLocation(-1), tagLength(0) {}

  TagLib::File *file;
  long footerLocation;
  long tagLength;

  Footer footer;

  ItemListMap itemListMap;
};

////////////////////////////////////////////////////////////////////////////////
// public methods
////////////////////////////////////////////////////////////////////////////////

APE::Tag::Tag() : TagLib::Tag()
{
  d = new TagPrivate;
}

APE::Tag::Tag(TagLib::File *file, long footerLocation) : TagLib::Tag()
{
  d = new TagPrivate;
  d->file = file;
  d->footerLocation = footerLocation;

  read();
}

APE::Tag::~Tag()
{
  delete d;
}

ByteVector APE::Tag::fileIdentifier()
{
  return ByteVector::fromCString("APETAGEX");
}

String APE::Tag::title() const
{
  if(d->itemListMap["TITLE"].isEmpty())
	return String::null;
  return d->itemListMap["TITLE"].toString();
}

String APE::Tag::artist() const
{
  if(d->itemListMap["ARTIST"].isEmpty())
	return String::null;
  return d->itemListMap["ARTIST"].toString();
}

String APE::Tag::album() const
{
  if(d->itemListMap["ALBUM"].isEmpty())
	return String::null;
  return d->itemListMap["ALBUM"].toString();
}

String APE::Tag::comment() const
{
  if(d->itemListMap["COMMENT"].isEmpty())
	return String::null;
  return d->itemListMap["COMMENT"].toString();
}

String APE::Tag::genre() const
{
  if(d->itemListMap["GENRE"].isEmpty())
	return String::null;
  return d->itemListMap["GENRE"].toString();
}

TagLib::uint APE::Tag::year() const
{
  if(d->itemListMap["YEAR"].isEmpty())
	return 0;
  return d->itemListMap["YEAR"].toString().toInt();
}

TagLib::uint APE::Tag::track() const
{
  if(d->itemListMap["TRACK"].isEmpty())
	return 0;
  return d->itemListMap["TRACK"].toString().toInt();
}

void APE::Tag::setTitle(const String &s)
{
  addValue("TITLE", s, true);
}

void APE::Tag::setArtist(const String &s)
{
  addValue("ARTIST", s, true);
}

void APE::Tag::setAlbum(const String &s)
{
  addValue("ALBUM", s, true);
}

void APE::Tag::setComment(const String &s)
{
  addValue("COMMENT", s, true);
}

void APE::Tag::setGenre(const String &s)
{
  addValue("GENRE", s, true);
}

void APE::Tag::setYear(uint i)
{
  if(i <= 0)
	removeItem("YEAR");
  else
	addValue("YEAR", String::number(i), true);
}

void APE::Tag::setTrack(uint i)
{
  if(i <= 0)
	removeItem("TRACK");
  else
	addValue("TRACK", String::number(i), true);
}

// conversions of tag keys between what we use in PropertyMap and what's usual
// for APE tags
static const TagLib::uint keyConversionsSize = 5; //usual,         APE
static const char *keyConversions[][2] =  {{"TRACKNUMBER", "TRACK"       },
										   {"DATE",        "YEAR"        },
										   {"ALBUMARTIST", "ALBUM ARTIST"},
										   {"DISCNUMBER",  "DISC"        },
										   {"REMIXER",     "MIXARTIST"   }};

PropertyMap APE::Tag::properties() const
{
  PropertyMap properties;
  ItemListMap::ConstIterator it = itemListMap().begin();
  for(; it != itemListMap().end(); ++it) {
	String tagName = PropertyMap::prepareKey(it->first);
	// if the item is Binary or Locator, or if the key is an invalid string,
	// add to unsupportedData
	if(it->second.type() != Item::Text || tagName.isNull())
	  properties.unsupportedData().append(it->first);
	else {
	  // Some tags need to be handled specially
	  for(uint i = 0; i < keyConversionsSize; ++i)
		if(tagName == keyConversions[i][1])
		  tagName = keyConversions[i][0];
		properties[tagName].append(it->second.toStringList());
	}
  }
  return properties;
}

void APE::Tag::removeUnsupportedProperties(const StringList &properties)
{
  StringList::ConstIterator it = properties.begin();
  for(; it != properties.end(); ++it)
	removeItem(*it);
}

PropertyMap APE::Tag::setProperties(const PropertyMap &origProps)
{
  PropertyMap properties(origProps); // make a local copy that can be modified

  // see comment in properties()
  for(uint i = 0; i < keyConversionsSize; ++i)
	if(properties.contains(keyConversions[i][0])) {
	  properties.insert(keyConversions[i][1], properties[keyConversions[i][0]]);
	  properties.erase(keyConversions[i][0]);
	}

  // first check if tags need to be removed completely
  StringList toRemove;
  ItemListMap::ConstIterator remIt = itemListMap().begin();
  for(; remIt != itemListMap().end(); ++remIt) {
	String key = PropertyMap::prepareKey(remIt->first);
	// only remove if a) key is valid, b) type is text, c) key not contained in new properties
	if(!key.isNull() && remIt->second.type() == APE::Item::Text && !properties.contains(key))
	  toRemove.append(remIt->first);
  }

  for (StringList::Iterator removeIt = toRemove.begin(); removeIt != toRemove.end(); removeIt++)
	removeItem(*removeIt);

  // now sync in the "forward direction"
  PropertyMap::ConstIterator it = properties.begin();
  for(; it != properties.end(); ++it) {
	const String &tagName = it->first;
	if(!(itemListMap().contains(tagName)) || !(itemListMap()[tagName].values() == it->second)) {
	  if(it->second.size() == 0)
		removeItem(tagName);
	  else {
		StringList::ConstIterator valueIt = it->second.begin();
		addValue(tagName, *valueIt, true);
		++valueIt;
		for(; valueIt != it->second.end(); ++valueIt)
		  addValue(tagName, *valueIt, false);
	  }
	}
  }
  return PropertyMap();
}

APE::Footer *APE::Tag::footer() const
{
  return &d->footer;
}

const APE::ItemListMap& APE::Tag::itemListMap() const
{
  return d->itemListMap;
}

void APE::Tag::removeItem(const String &key)
{
  Map<const String, Item>::Iterator it = d->itemListMap.find(key.upper());
  if(it != d->itemListMap.end())
	d->itemListMap.erase(it);
}

void APE::Tag::addValue(const String &key, const String &value, bool replace)
{
  if(replace)
	removeItem(key);
  if(!key.isEmpty() && !value.isEmpty()) {
	if(!replace && d->itemListMap.contains(key)) {
	  // Text items may contain more than one value
	  if(APE::Item::Text == d->itemListMap.begin()->second.type())
		d->itemListMap[key.upper()].appendValue(value);
	  // Binary or locator items may have only one value
	  else
		setItem(key, Item(key, value));
	}
	else
	  setItem(key, Item(key, value));
  }
}

void APE::Tag::setData(const String &key, const ByteVector &value)
{
  removeItem(key);
  if(!key.isEmpty() && !value.isEmpty())
	setItem(key, Item(key, value, true));
}

void APE::Tag::setItem(const String &key, const Item &item)
{
  if(!key.isEmpty())
	d->itemListMap.insert(key.upper(), item);
}

bool APE::Tag::isEmpty() const
{
  return d->itemListMap.isEmpty();
}

////////////////////////////////////////////////////////////////////////////////
// protected methods
////////////////////////////////////////////////////////////////////////////////

void APE::Tag::read()
{
  if(d->file && d->file->isValid()) {

	d->file->seek(d->footerLocation);
	d->footer.setData(d->file->readBlock(Footer::size()));

	if(d->footer.tagSize() <= Footer::size() ||
	   d->footer.tagSize() > uint(d->file->length()))
	  return;

	d->file->seek(d->footerLocation + Footer::size() - d->footer.tagSize());
	parse(d->file->readBlock(d->footer.tagSize() - Footer::size()));
  }
}

ByteVector APE::Tag::render() const
{
  ByteVector data;
  uint itemCount = 0;

  {
	for(Map<const String, Item>::ConstIterator it = d->itemListMap.begin();
		it != d->itemListMap.end(); ++it)
	{
	  data.append(it->second.render());
	  itemCount++;
	}
  }

  d->footer.setItemCount(itemCount);
  d->footer.setTagSize(data.size() + Footer::size());
  d->footer.setHeaderPresent(true);

  return d->footer.renderHeader() + data + d->footer.renderFooter();
}

void APE::Tag::parse(const ByteVector &data)
{
  uint pos = 0;

  // 11 bytes is the minimum size for an APE item

  for(uint i = 0; i < d->footer.itemCount() && pos <= data.size() - 11; i++) {
	APE::Item item;
	item.parse(data.mid(pos));

	d->itemListMap.insert(item.key().upper(), item);

	pos += item.size();
  }
}

/*** End of inlined file: apetag.cpp ***/


/*** Start of inlined file: apefooter.cpp ***/
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

#include <iostream>
#include <bitset>

using namespace TagLib;
using namespace APE;

class APE::Footer::FooterPrivate
{
public:
  FooterPrivate() : version(0),
					footerPresent(true),
					headerPresent(false),
					isHeader(false),
					itemCount(0),
					tagSize(0) {}

  ~FooterPrivate() {}

  uint version;

  bool footerPresent;
  bool headerPresent;

  bool isHeader;

  uint itemCount;
  uint tagSize;

  static const uint size = 32;
};

////////////////////////////////////////////////////////////////////////////////
// static members
////////////////////////////////////////////////////////////////////////////////

TagLib::uint APE::Footer::size()
{
  return FooterPrivate::size;
}

ByteVector APE::Footer::fileIdentifier()
{
  return ByteVector::fromCString("APETAGEX");
}

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

APE::Footer::Footer()
{
  d = new FooterPrivate;
}

APE::Footer::Footer(const ByteVector &data)
{
  d = new FooterPrivate;
  parse(data);
}

APE::Footer::~Footer()
{
  delete d;
}

TagLib::uint APE::Footer::version() const
{
  return d->version;
}

bool APE::Footer::headerPresent() const
{
  return d->headerPresent;
}

bool APE::Footer::footerPresent() const
{
  return d->footerPresent;
}

bool APE::Footer::isHeader() const
{
  return d->isHeader;
}

void APE::Footer::setHeaderPresent(bool b) const
{
  d->headerPresent = b;
}

TagLib::uint APE::Footer::itemCount() const
{
  return d->itemCount;
}

void APE::Footer::setItemCount(uint s)
{
  d->itemCount = s;
}

TagLib::uint APE::Footer::tagSize() const
{
  return d->tagSize;
}

TagLib::uint APE::Footer::completeTagSize() const
{
  if(d->headerPresent)
	return d->tagSize + d->size;
  else
	return d->tagSize;
}

void APE::Footer::setTagSize(uint s)
{
  d->tagSize = s;
}

void APE::Footer::setData(const ByteVector &data)
{
  parse(data);
}

ByteVector APE::Footer::renderFooter() const
{
	return render(false);
}

ByteVector APE::Footer::renderHeader() const
{
	if (!d->headerPresent) return ByteVector();

	return render(true);
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

void APE::Footer::parse(const ByteVector &data)
{
  if(data.size() < size())
	return;

  // The first eight bytes, data[0..7], are the File Identifier, "APETAGEX".

  // Read the version number

  d->version = data.mid(8, 4).toUInt(false);

  // Read the tag size

  d->tagSize = data.mid(12, 4).toUInt(false);

  // Read the item count

  d->itemCount = data.mid(16, 4).toUInt(false);

  // Read the flags

  std::bitset<32> flags(TAGLIB_CONSTRUCT_BITSET(data.mid(20, 4).toUInt(false)));

  d->headerPresent = flags[31];
  d->footerPresent = !flags[30];
  d->isHeader = flags[29];

}

ByteVector APE::Footer::render(bool isHeader) const
{
  ByteVector v;

  // add the file identifier -- "APETAGEX"

  v.append(fileIdentifier());

  // add the version number -- we always render a 2.000 tag regardless of what
  // the tag originally was.

  v.append(ByteVector::fromUInt(2000, false));

  // add the tag size

  v.append(ByteVector::fromUInt(d->tagSize, false));

  // add the item count

  v.append(ByteVector::fromUInt(d->itemCount, false));

  // render and add the flags

  std::bitset<32> flags;

  flags[31] = d->headerPresent;
  flags[30] = false; // footer is always present
  flags[29] = isHeader;

  v.append(ByteVector::fromUInt(flags.to_ulong(), false));

  // add the reserved 64bit

  v.append(ByteVector::fromLongLong(0));

  return v;
}

/*** End of inlined file: apefooter.cpp ***/


/*** Start of inlined file: apeitem.cpp ***/
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

using namespace TagLib;
using namespace APE;

class APE::Item::ItemPrivate
{
public:
  ItemPrivate() : type(Text), readOnly(false) {}

  Item::ItemTypes type;
  String key;
  ByteVector value;
  StringList text;
  bool readOnly;
};

APE::Item::Item()
{
  d = new ItemPrivate;
}

APE::Item::Item(const String &key, const String &value)
{
  d = new ItemPrivate;
  d->key = key;
  d->text.append(value);
}

APE::Item::Item(const String &key, const StringList &values)
{
  d = new ItemPrivate;
  d->key = key;
  d->text = values;
}

APE::Item::Item(const String &key, const ByteVector &value, bool binary)
{
  d = new ItemPrivate;
  d->key = key;
  if(binary) {
	d->type = Binary;
	d->value = value;
  }
  else
	  d->text.append(value);
}

APE::Item::Item(const Item &item)
{
  d = new ItemPrivate(*item.d);
}

APE::Item::~Item()
{
  delete d;
}

Item &APE::Item::operator=(const Item &item)
{
  delete d;
  d = new ItemPrivate(*item.d);
  return *this;
}

void APE::Item::setReadOnly(bool readOnly)
{
  d->readOnly = readOnly;
}

bool APE::Item::isReadOnly() const
{
  return d->readOnly;
}

void APE::Item::setType(APE::Item::ItemTypes val)
{
  d->type = val;
}

APE::Item::ItemTypes APE::Item::type() const
{
  return d->type;
}

String APE::Item::key() const
{
  return d->key;
}

ByteVector APE::Item::binaryData() const
{
  return d->value;
}

void APE::Item::setBinaryData(const ByteVector &value)
{
  d->type = Binary;
  d->value = value;
}

ByteVector APE::Item::value() const
{
  // This seems incorrect as it won't be actually rendering the value to keep it
  // up to date.

  return d->value;
}

void APE::Item::setKey(const String &key)
{
	d->key = key;
}

void APE::Item::setValue(const String &value)
{
	d->type = Text;
	d->text = value;
}

void APE::Item::setValues(const StringList &value)
{
	d->type = Text;
	d->text = value;
}

void APE::Item::appendValue(const String &value)
{
	d->type = Text;
	d->text.append(value);
}

void APE::Item::appendValues(const StringList &values)
{
	d->type = Text;
	d->text.append(values);
}

int APE::Item::size() const
{
  // SFB: Why is d->key.size() used when size() returns the length in UniChars and not UTF-8?
  int result = 8 + d->key.size() /* d->key.data(String::UTF8).size() */ + 1;
  switch (d->type) {
	case Text:
	  if(d->text.size()) {
		StringList::ConstIterator it = d->text.begin();

		result += it->data(String::UTF8).size();
		it++;
		for(; it != d->text.end(); ++it)
		  result += 1 + it->data(String::UTF8).size();
	  }
	  break;

	case Binary:
	case Locator:
	  result += d->value.size();
	  break;
  }
  return result;
}

StringList APE::Item::toStringList() const
{
  return d->text;
}

StringList APE::Item::values() const
{
  return d->text;
}

String APE::Item::toString() const
{
  return isEmpty() ? String::null : d->text.front();
}

bool APE::Item::isEmpty() const
{
  switch(d->type) {
	case Text:
	  if(d->text.isEmpty())
		return true;
	  if(d->text.size() == 1 && d->text.front().isEmpty())
		return true;
	  return false;
	case Binary:
	case Locator:
	  return d->value.isEmpty();
	default:
	  return false;
  }
}

void APE::Item::parse(const ByteVector &data)
{
  // 11 bytes is the minimum size for an APE item

  if(data.size() < 11) {
	debug("APE::Item::parse() -- no data in item");
	return;
  }

  uint valueLength  = data.mid(0, 4).toUInt(false);
  uint flags        = data.mid(4, 4).toUInt(false);

  d->key = String(data.mid(8), String::UTF8);

  d->value = data.mid(8 + d->key.size() + 1, valueLength);

  setReadOnly(flags & 1);
  setType(ItemTypes((flags >> 1) & 3));

  if(Text == d->type)
	d->text = StringList(ByteVectorList::split(d->value, '\0'), String::UTF8);
}

ByteVector APE::Item::render() const
{
  ByteVector data;
  TagLib::uint flags = ((d->readOnly) ? 1 : 0) | (d->type << 1);
  ByteVector value;

  if(isEmpty())
	return data;

  if(d->type == Text) {
	StringList::ConstIterator it = d->text.begin();

	value.append(it->data(String::UTF8));
	it++;
	for(; it != d->text.end(); ++it) {
	  value.append('\0');
	  value.append(it->data(String::UTF8));
	}
	d->value = value;
  }
  else
	value.append(d->value);

  data.append(ByteVector::fromUInt(value.size(), false));
  data.append(ByteVector::fromUInt(flags, false));
  data.append(d->key.data(String::UTF8));
  data.append(ByteVector('\0'));
  data.append(value);

  return data;
}

/*** End of inlined file: apeitem.cpp ***/


/*** Start of inlined file: apefile.cpp ***/
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

using namespace TagLib;

namespace
{
  enum { ApeAPEIndex, ApeID3v1Index };
}

class APE::File::FilePrivate
{
public:
  FilePrivate() :
	APELocation(-1),
	APESize(0),
	ID3v1Location(-1),
	properties(0),
	hasAPE(false),
	hasID3v1(false) {}

  ~FilePrivate()
  {
	delete properties;
  }

  long APELocation;
  uint APESize;

  long ID3v1Location;

  TagUnion tag;

  Properties *properties;

  // These indicate whether the file *on disk* has these tags, not if
  // this data structure does.  This is used in computing offsets.

  bool hasAPE;
  bool hasID3v1;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

APE::File::File(FileName file, bool readProperties,
				Properties::ReadStyle propertiesStyle) : TagLib::File(file)
{
  d = new FilePrivate;
  read(readProperties, propertiesStyle);
}

APE::File::File(IOStream *stream, bool readProperties,
				Properties::ReadStyle propertiesStyle) : TagLib::File(stream)
{
  d = new FilePrivate;
  read(readProperties, propertiesStyle);
}

APE::File::~File()
{
  delete d;
}

TagLib::Tag *APE::File::tag() const
{
  return &d->tag;
}

PropertyMap APE::File::properties() const
{
  if(d->hasAPE)
	return d->tag.access<APE::Tag>(ApeAPEIndex, false)->properties();
  if(d->hasID3v1)
	return d->tag.access<ID3v1::Tag>(ApeID3v1Index, false)->properties();
  return PropertyMap();
}

void APE::File::removeUnsupportedProperties(const StringList &properties)
{
  if(d->hasAPE)
	d->tag.access<APE::Tag>(ApeAPEIndex, false)->removeUnsupportedProperties(properties);
  if(d->hasID3v1)
	d->tag.access<ID3v1::Tag>(ApeID3v1Index, false)->removeUnsupportedProperties(properties);
}

PropertyMap APE::File::setProperties(const PropertyMap &properties)
{
  if(d->hasAPE)
	return d->tag.access<APE::Tag>(ApeAPEIndex, false)->setProperties(properties);
  else if(d->hasID3v1)
	return d->tag.access<ID3v1::Tag>(ApeID3v1Index, false)->setProperties(properties);
  else
	return d->tag.access<APE::Tag>(ApeAPEIndex, true)->setProperties(properties);
}

APE::Properties *APE::File::audioProperties() const
{
  return d->properties;
}

bool APE::File::save()
{
  if(readOnly()) {
	debug("APE::File::save() -- File is read only.");
	return false;
  }

  // Update ID3v1 tag

  if(ID3v1Tag()) {
	if(d->hasID3v1) {
	  seek(d->ID3v1Location);
	  writeBlock(ID3v1Tag()->render());
	}
	else {
	  seek(0, End);
	  d->ID3v1Location = tell();
	  writeBlock(ID3v1Tag()->render());
	  d->hasID3v1 = true;
	}
  }
  else {
	if(d->hasID3v1) {
	  removeBlock(d->ID3v1Location, 128);
	  d->hasID3v1 = false;
	  if(d->hasAPE) {
		if(d->APELocation > d->ID3v1Location)
		  d->APELocation -= 128;
	  }
	}
  }

  // Update APE tag

  if(APETag()) {
	if(d->hasAPE)
	  insert(APETag()->render(), d->APELocation, d->APESize);
	else {
	  if(d->hasID3v1)  {
		insert(APETag()->render(), d->ID3v1Location, 0);
		d->APESize = APETag()->footer()->completeTagSize();
		d->hasAPE = true;
		d->APELocation = d->ID3v1Location;
		d->ID3v1Location += d->APESize;
	  }
	  else {
		seek(0, End);
		d->APELocation = tell();
		writeBlock(APETag()->render());
		d->APESize = APETag()->footer()->completeTagSize();
		d->hasAPE = true;
	  }
	}
  }
  else {
	if(d->hasAPE) {
	  removeBlock(d->APELocation, d->APESize);
	  d->hasAPE = false;
	  if(d->hasID3v1) {
		if(d->ID3v1Location > d->APELocation) {
		  d->ID3v1Location -= d->APESize;
		}
	  }
	}
  }

   return true;
}

ID3v1::Tag *APE::File::ID3v1Tag(bool create)
{
  return d->tag.access<ID3v1::Tag>(ApeID3v1Index, create);
}

APE::Tag *APE::File::APETag(bool create)
{
  return d->tag.access<APE::Tag>(ApeAPEIndex, create);
}

void APE::File::strip(int tags)
{
  if(tags & ID3v1) {
	d->tag.set(ApeID3v1Index, 0);
	APETag(true);
  }

  if(tags & APE) {
	d->tag.set(ApeAPEIndex, 0);

	if(!ID3v1Tag())
	  APETag(true);
  }
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void APE::File::read(bool readProperties, Properties::ReadStyle /* propertiesStyle */)
{
  // Look for an ID3v1 tag

  d->ID3v1Location = findID3v1();

  if(d->ID3v1Location >= 0) {
	d->tag.set(ApeID3v1Index, new ID3v1::Tag(this, d->ID3v1Location));
	d->hasID3v1 = true;
  }

  // Look for an APE tag

  d->APELocation = findAPE();

  if(d->APELocation >= 0) {
	d->tag.set(ApeAPEIndex, new APE::Tag(this, d->APELocation));
	d->APESize = APETag()->footer()->completeTagSize();
	d->APELocation = d->APELocation + APETag()->footer()->size() - d->APESize;
	d->hasAPE = true;
  }

  if(!d->hasID3v1)
	APETag(true);

  // Look for APE audio properties

  if(readProperties) {
	d->properties = new Properties(this);
  }
}

long APE::File::findAPE()
{
  if(!isValid())
	return -1;

  if(d->hasID3v1)
	seek(-160, End);
  else
	seek(-32, End);

  long p = tell();

  if(readBlock(8) == APE::Tag::fileIdentifier())
	return p;

  return -1;
}

long APE::File::findID3v1()
{
  if(!isValid())
	return -1;

  seek(-128, End);
  long p = tell();

  if(readBlock(3) == ID3v1::Tag::fileIdentifier())
	return p;

  return -1;
}

/*** End of inlined file: apefile.cpp ***/


/*** Start of inlined file: apeproperties.cpp ***/
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

#include <bitset>

using namespace TagLib;

class APE::Properties::PropertiesPrivate
{
public:
  PropertiesPrivate(File *file, long streamLength) :
	length(0),
	bitrate(0),
	sampleRate(0),
	channels(0),
	version(0),
	bitsPerSample(0),
	sampleFrames(0),
	file(file),
	streamLength(streamLength) {}

  int length;
  int bitrate;
  int sampleRate;
  int channels;
  int version;
  int bitsPerSample;
  uint sampleFrames;
  File *file;
  long streamLength;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

APE::Properties::Properties(File *file, ReadStyle style) : AudioProperties(style)
{
  d = new PropertiesPrivate(file, file->length());
  read();
}

APE::Properties::~Properties()
{
  delete d;
}

int APE::Properties::length() const
{
  return d->length;
}

int APE::Properties::bitrate() const
{
  return d->bitrate;
}

int APE::Properties::sampleRate() const
{
  return d->sampleRate;
}

int APE::Properties::channels() const
{
  return d->channels;
}

int APE::Properties::version() const
{
  return d->version;
}

int APE::Properties::bitsPerSample() const
{
  return d->bitsPerSample;
}

TagLib::uint APE::Properties::sampleFrames() const
{
  return d->sampleFrames;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void APE::Properties::read()
{
  // First we are searching the descriptor
  long offset = findDescriptor();
  if(offset < 0)
	return;

  // Then we read the header common for all versions of APE
  d->file->seek(offset);
  ByteVector commonHeader=d->file->readBlock(6);
  if(!commonHeader.startsWith("MAC "))
	return;
  d->version = commonHeader.mid(4).toUInt(false);

  if(d->version >= 3980) {
	analyzeCurrent();
  }
  else {
	analyzeOld();
  }
}

long APE::Properties::findDescriptor()
{
  long ID3v2Location = findID3v2();
  long ID3v2OriginalSize = 0;
  bool hasID3v2 = false;
  if(ID3v2Location >= 0) {
	ID3v2::Tag tag(d->file, ID3v2Location);
	ID3v2OriginalSize = tag.header()->completeTagSize();
	if(tag.header()->tagSize() > 0)
	  hasID3v2 = true;
  }

  long offset = 0;
  if(hasID3v2)
	offset = d->file->find("MAC ", ID3v2Location + ID3v2OriginalSize);
  else
	offset = d->file->find("MAC ");

  if(offset < 0) {
	debug("APE::Properties::findDescriptor() -- APE descriptor not found");
	return -1;
  }

  return offset;
}

long APE::Properties::findID3v2()
{
  if(!d->file->isValid())
	return -1;

  d->file->seek(0);

  if(d->file->readBlock(3) == ID3v2::Header::fileIdentifier())
	return 0;

  return -1;
}

void APE::Properties::analyzeCurrent()
{
  // Read the descriptor
  d->file->seek(2, File::Current);
  ByteVector descriptor = d->file->readBlock(44);
  uint descriptorBytes = descriptor.mid(0,4).toUInt(false);

  if ((descriptorBytes - 52) > 0)
	d->file->seek(descriptorBytes - 52, File::Current);

  // Read the header
  ByteVector header = d->file->readBlock(24);

  // Get the APE info
  d->channels = header.mid(18, 2).toShort(false);
  d->sampleRate = header.mid(20, 4).toUInt(false);
  d->bitsPerSample = header.mid(16, 2).toShort(false);
  //d->compressionLevel =

  uint totalFrames = header.mid(12, 4).toUInt(false);
  uint blocksPerFrame = header.mid(4, 4).toUInt(false);
  uint finalFrameBlocks = header.mid(8, 4).toUInt(false);
  d->sampleFrames = totalFrames > 0 ? (totalFrames -  1) * blocksPerFrame + finalFrameBlocks : 0;
  d->length = d->sampleRate > 0 ? d->sampleFrames / d->sampleRate : 0;
  d->bitrate = d->length > 0 ? ((d->streamLength * 8L) / d->length) / 1000 : 0;
}

void APE::Properties::analyzeOld()
{
  ByteVector header = d->file->readBlock(26);
  uint totalFrames = header.mid(18, 4).toUInt(false);

  // Fail on 0 length APE files (catches non-finalized APE files)
  if(totalFrames == 0)
	return;

  short compressionLevel = header.mid(0, 2).toShort(false);
  uint blocksPerFrame;
  if(d->version >= 3950)
	blocksPerFrame = 73728 * 4;
  else if(d->version >= 3900 || (d->version >= 3800 && compressionLevel == 4000))
	blocksPerFrame = 73728;
  else
	blocksPerFrame = 9216;
  d->channels = header.mid(4, 2).toShort(false);
  d->sampleRate = header.mid(6, 4).toUInt(false);
  uint finalFrameBlocks = header.mid(22, 4).toUInt(false);
  uint totalBlocks = totalFrames > 0 ? (totalFrames - 1) * blocksPerFrame + finalFrameBlocks : 0;
  d->length = totalBlocks / d->sampleRate;
  d->bitrate = d->length > 0 ? ((d->streamLength * 8L) / d->length) / 1000 : 0;
}

/*** End of inlined file: apeproperties.cpp ***/


/*** Start of inlined file: wavpackfile.cpp ***/
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

using namespace TagLib;

namespace
{
  enum { WavAPEIndex, WavID3v1Index };
}

class WavPack::File::FilePrivate
{
public:
  FilePrivate() :
	APELocation(-1),
	APESize(0),
	ID3v1Location(-1),
	properties(0),
	hasAPE(false),
	hasID3v1(false) {}

  ~FilePrivate()
  {
	delete properties;
  }

  long APELocation;
  uint APESize;

  long ID3v1Location;

  TagUnion tag;

  Properties *properties;

  // These indicate whether the file *on disk* has these tags, not if
  // this data structure does.  This is used in computing offsets.

  bool hasAPE;
  bool hasID3v1;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

WavPack::File::File(FileName file, bool readProperties,
				Properties::ReadStyle propertiesStyle) : TagLib::File(file)
{
  d = new FilePrivate;
  read(readProperties, propertiesStyle);
}

WavPack::File::File(IOStream *stream, bool readProperties,
				Properties::ReadStyle propertiesStyle) : TagLib::File(stream)
{
  d = new FilePrivate;
  read(readProperties, propertiesStyle);
}

WavPack::File::~File()
{
  delete d;
}

TagLib::Tag *WavPack::File::tag() const
{
  return &d->tag;
}

PropertyMap WavPack::File::properties() const
{
  if(d->hasAPE)
	return d->tag.access<APE::Tag>(WavAPEIndex, false)->properties();
  if(d->hasID3v1)
	return d->tag.access<ID3v1::Tag>(WavID3v1Index, false)->properties();
  return PropertyMap();
}

PropertyMap WavPack::File::setProperties(const PropertyMap &properties)
{
  if(d->hasAPE)
	return d->tag.access<APE::Tag>(WavAPEIndex, false)->setProperties(properties);
  else if(d->hasID3v1)
	return d->tag.access<ID3v1::Tag>(WavID3v1Index, false)->setProperties(properties);
  else
	return d->tag.access<APE::Tag>(APE, true)->setProperties(properties);
}

WavPack::Properties *WavPack::File::audioProperties() const
{
  return d->properties;
}

bool WavPack::File::save()
{
  if(readOnly()) {
	debug("WavPack::File::save() -- File is read only.");
	return false;
  }

  // Update ID3v1 tag

  if(ID3v1Tag()) {
	if(d->hasID3v1) {
	  seek(d->ID3v1Location);
	  writeBlock(ID3v1Tag()->render());
	}
	else {
	  seek(0, End);
	  d->ID3v1Location = tell();
	  writeBlock(ID3v1Tag()->render());
	  d->hasID3v1 = true;
	}
  }
  else {
	if(d->hasID3v1) {
	  removeBlock(d->ID3v1Location, 128);
	  d->hasID3v1 = false;
	  if(d->hasAPE) {
		if(d->APELocation > d->ID3v1Location)
		  d->APELocation -= 128;
	  }
	}
  }

  // Update APE tag

  if(APETag()) {
	if(d->hasAPE)
	  insert(APETag()->render(), d->APELocation, d->APESize);
	else {
	  if(d->hasID3v1)  {
		insert(APETag()->render(), d->ID3v1Location, 0);
		d->APESize = APETag()->footer()->completeTagSize();
		d->hasAPE = true;
		d->APELocation = d->ID3v1Location;
		d->ID3v1Location += d->APESize;
	  }
	  else {
		seek(0, End);
		d->APELocation = tell();
		writeBlock(APETag()->render());
		d->APESize = APETag()->footer()->completeTagSize();
		d->hasAPE = true;
	  }
	}
  }
  else {
	if(d->hasAPE) {
	  removeBlock(d->APELocation, d->APESize);
	  d->hasAPE = false;
	  if(d->hasID3v1) {
		if(d->ID3v1Location > d->APELocation) {
		  d->ID3v1Location -= d->APESize;
		}
	  }
	}
  }

   return true;
}

ID3v1::Tag *WavPack::File::ID3v1Tag(bool create)
{
  return d->tag.access<ID3v1::Tag>(WavID3v1Index, create);
}

APE::Tag *WavPack::File::APETag(bool create)
{
  return d->tag.access<APE::Tag>(WavAPEIndex, create);
}

void WavPack::File::strip(int tags)
{
  if(tags & ID3v1) {
	d->tag.set(WavID3v1Index, 0);
	APETag(true);
  }

  if(tags & APE) {
	d->tag.set(WavAPEIndex, 0);

	if(!ID3v1Tag())
	  APETag(true);
  }
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void WavPack::File::read(bool readProperties, Properties::ReadStyle /* propertiesStyle */)
{
  // Look for an ID3v1 tag

  d->ID3v1Location = findID3v1();

  if(d->ID3v1Location >= 0) {
	d->tag.set(WavID3v1Index, new ID3v1::Tag(this, d->ID3v1Location));
	d->hasID3v1 = true;
  }

  // Look for an APE tag

  d->APELocation = findAPE();

  if(d->APELocation >= 0) {
	d->tag.set(WavAPEIndex, new APE::Tag(this, d->APELocation));
	d->APESize = APETag()->footer()->completeTagSize();
	d->APELocation = d->APELocation + APETag()->footer()->size() - d->APESize;
	d->hasAPE = true;
  }

  if(!d->hasID3v1)
	APETag(true);

  // Look for WavPack audio properties

  if(readProperties) {
	seek(0);
	d->properties = new Properties(this, length() - d->APESize);
  }
}

long WavPack::File::findAPE()
{
  if(!isValid())
	return -1;

  if(d->hasID3v1)
	seek(-160, End);
  else
	seek(-32, End);

  long p = tell();

  if(readBlock(8) == APE::Tag::fileIdentifier())
	return p;

  return -1;
}

long WavPack::File::findID3v1()
{
  if(!isValid())
	return -1;

  seek(-128, End);
  long p = tell();

  if(readBlock(3) == ID3v1::Tag::fileIdentifier())
	return p;

  return -1;
}

/*** End of inlined file: wavpackfile.cpp ***/


/*** Start of inlined file: wavpackproperties.cpp ***/
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

using namespace TagLib;

class WavPack::Properties::PropertiesPrivate
{
public:
  PropertiesPrivate(const ByteVector &d, long length, ReadStyle s) :
	data(d),
	streamLength(length),
	style(s),
	length(0),
	bitrate(0),
	sampleRate(0),
	channels(0),
	version(0),
	bitsPerSample(0),
	sampleFrames(0),
	file(0) {}

  ByteVector data;
  long streamLength;
  ReadStyle style;
  int length;
  int bitrate;
  int sampleRate;
  int channels;
  int version;
  int bitsPerSample;
  uint sampleFrames;
  File *file;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

WavPack::Properties::Properties(const ByteVector &data, long streamLength, ReadStyle style) : AudioProperties(style)
{
  d = new PropertiesPrivate(data, streamLength, style);
  read();
}

WavPack::Properties::Properties(File *file, long streamLength, ReadStyle style) : AudioProperties(style)
{
  ByteVector data = file->readBlock(32);
  d = new PropertiesPrivate(data, streamLength, style);
  d->file = file;
  read();
}

WavPack::Properties::~Properties()
{
  delete d;
}

int WavPack::Properties::length() const
{
  return d->length;
}

int WavPack::Properties::bitrate() const
{
  return d->bitrate;
}

int WavPack::Properties::sampleRate() const
{
  return d->sampleRate;
}

int WavPack::Properties::channels() const
{
  return d->channels;
}

int WavPack::Properties::version() const
{
  return d->version;
}

int WavPack::Properties::bitsPerSample() const
{
  return d->bitsPerSample;
}

uint WavPack::Properties::sampleFrames() const
{
  return d->sampleFrames;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

static const unsigned int sample_rates[] = { 6000, 8000, 9600, 11025, 12000,
	16000, 22050, 24000, 32000, 44100, 48000, 64000, 88200, 96000, 192000 };

#define BYTES_STORED    3
#define MONO_FLAG       4

#define SHIFT_LSB       13
#define SHIFT_MASK      (0x1fL << SHIFT_LSB)

#define SRATE_LSB       23
#define SRATE_MASK      (0xfL << SRATE_LSB)

#define MIN_STREAM_VERS     0x402
#define MAX_STREAM_VERS     0x410

#define FINAL_BLOCK     0x1000

void WavPack::Properties::read()
{
  if(!d->data.startsWith("wvpk"))
	return;

  d->version = d->data.mid(8, 2).toShort(false);
  if(d->version < MIN_STREAM_VERS || d->version > MAX_STREAM_VERS)
	return;

  unsigned int flags = d->data.mid(24, 4).toUInt(false);
  d->bitsPerSample = ((flags & BYTES_STORED) + 1) * 8 -
	((flags & SHIFT_MASK) >> SHIFT_LSB);
  d->sampleRate = sample_rates[(flags & SRATE_MASK) >> SRATE_LSB];
  d->channels = (flags & MONO_FLAG) ? 1 : 2;

  unsigned int samples = d->data.mid(12, 4).toUInt(false);
  if(samples == ~0u) {
	if(d->file && d->style != Fast) {
	  samples = seekFinalIndex();
	}
	else {
	  samples = 0;
	}
  }
  d->length = d->sampleRate > 0 ? (samples + (d->sampleRate / 2)) / d->sampleRate : 0;
  d->sampleFrames = samples;

  d->bitrate = d->length > 0 ? ((d->streamLength * 8L) / d->length) / 1000 : 0;
}

unsigned int WavPack::Properties::seekFinalIndex()
{
  ByteVector blockID("wvpk", 4);

  long offset = d->streamLength;
  while(offset > 0) {
	offset = d->file->rfind(blockID, offset);
	if(offset == -1)
	  return 0;
	d->file->seek(offset);
	ByteVector data = d->file->readBlock(32);
	if(data.size() != 32)
	  return 0;
	int version = data.mid(8, 2).toShort(false);
	if(version < MIN_STREAM_VERS || version > MAX_STREAM_VERS)
	  continue;
	unsigned int flags = data.mid(24, 4).toUInt(false);
	if(!(flags & FINAL_BLOCK))
	  return 0;
	unsigned int blockIndex = data.mid(16, 4).toUInt(false);
	unsigned int blockSamples = data.mid(20, 4).toUInt(false);
	return blockIndex + blockSamples;
  }

  return 0;
}

/*** End of inlined file: wavpackproperties.cpp ***/


/*** Start of inlined file: speexfile.cpp ***/
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

#include <bitset>

using namespace TagLib;
using namespace TagLib::Ogg;

class Speex::File::FilePrivate
{
public:
  FilePrivate() :
	comment(0),
	properties(0) {}

  ~FilePrivate()
  {
	delete comment;
	delete properties;
  }

  Ogg::XiphComment *comment;
  Properties *properties;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

Speex::File::File(FileName file, bool readProperties,
				   Properties::ReadStyle propertiesStyle) : Ogg::File(file)
{
  d = new FilePrivate;
  read(readProperties, propertiesStyle);
}

Speex::File::File(IOStream *stream, bool readProperties,
				   Properties::ReadStyle propertiesStyle) : Ogg::File(stream)
{
  d = new FilePrivate;
  read(readProperties, propertiesStyle);
}

Speex::File::~File()
{
  delete d;
}

Ogg::XiphComment *Speex::File::tag() const
{
  return d->comment;
}

Speex::Properties *Speex::File::audioProperties() const
{
  return d->properties;
}

bool Speex::File::save()
{
  if(!d->comment)
	d->comment = new Ogg::XiphComment;

  setPacket(1, d->comment->render());

  return Ogg::File::save();
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void Speex::File::read(bool readProperties, Properties::ReadStyle propertiesStyle)
{
  ByteVector speexHeaderData = packet(0);

  if(!speexHeaderData.startsWith("Speex   ")) {
	debug("Speex::File::read() -- invalid Speex identification header");
	return;
  }

  ByteVector commentHeaderData = packet(1);

  d->comment = new Ogg::XiphComment(commentHeaderData);

  if(readProperties)
	d->properties = new Properties(this, propertiesStyle);
}

/*** End of inlined file: speexfile.cpp ***/


/*** Start of inlined file: speexproperties.cpp ***/
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

using namespace TagLib;
using namespace TagLib::Ogg;

class Speex::Properties::PropertiesPrivate
{
public:
  PropertiesPrivate(File *f, ReadStyle s) :
	file(f),
	style(s),
	length(0),
	bitrate(0),
	sampleRate(0),
	channels(0),
	speexVersion(0),
	vbr(false),
	mode(0) {}

  File *file;
  ReadStyle style;
  int length;
  int bitrate;
  int sampleRate;
  int channels;
  int speexVersion;
  bool vbr;
  int mode;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

Speex::Properties::Properties(File *file, ReadStyle style) : AudioProperties(style)
{
  d = new PropertiesPrivate(file, style);
  read();
}

Speex::Properties::~Properties()
{
  delete d;
}

int Speex::Properties::length() const
{
  return d->length;
}

int Speex::Properties::bitrate() const
{
  return int(float(d->bitrate) / float(1000) + 0.5);
}

int Speex::Properties::sampleRate() const
{
  return d->sampleRate;
}

int Speex::Properties::channels() const
{
  return d->channels;
}

int Speex::Properties::speexVersion() const
{
  return d->speexVersion;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void Speex::Properties::read()
{
  // Get the identification header from the Ogg implementation.

  ByteVector data = d->file->packet(0);

  int pos = 28;

  // speex_version_id;       /**< Version for Speex (for checking compatibility) */
  d->speexVersion = data.mid(pos, 4).toUInt(false);
  pos += 4;

  // header_size;            /**< Total size of the header ( sizeof(SpeexHeader) ) */
  pos += 4;

  // rate;                   /**< Sampling rate used */
  d->sampleRate = data.mid(pos, 4).toUInt(false);
  pos += 4;

  // mode;                   /**< Mode used (0 for narrowband, 1 for wideband) */
  d->mode = data.mid(pos, 4).toUInt(false);
  pos += 4;

  // mode_bitstream_version; /**< Version ID of the bit-stream */
  pos += 4;

  // nb_channels;            /**< Number of channels encoded */
  d->channels = data.mid(pos, 4).toUInt(false);
  pos += 4;

  // bitrate;                /**< Bit-rate used */
  d->bitrate = data.mid(pos, 4).toUInt(false);
  pos += 4;

  // frame_size;             /**< Size of frames */
  // unsigned int frameSize = data.mid(pos, 4).toUInt(false);
  pos += 4;

  // vbr;                    /**< 1 for a VBR encoding, 0 otherwise */
  d->vbr = data.mid(pos, 4).toUInt(false) == 1;
  pos += 4;

  // frames_per_packet;      /**< Number of frames stored per Ogg packet */
  // unsigned int framesPerPacket = data.mid(pos, 4).toUInt(false);

  const Ogg::PageHeader *first = d->file->firstPageHeader();
  const Ogg::PageHeader *last = d->file->lastPageHeader();

  if(first && last) {
	long long start = first->absoluteGranularPosition();
	long long end = last->absoluteGranularPosition();

	if(start >= 0 && end >= 0 && d->sampleRate > 0)
	  d->length = (int) ((end - start) / (long long) d->sampleRate);
	else
	  debug("Speex::Properties::read() -- Either the PCM values for the start or "
			"end of this file was incorrect or the sample rate is zero.");
  }
  else
	debug("Speex::Properties::read() -- Could not find valid first and last Ogg pages.");
}

/*** End of inlined file: speexproperties.cpp ***/


/*** Start of inlined file: trueaudiofile.cpp ***/
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

using namespace TagLib;

namespace
{
  enum { TrueAudioID3v2Index = 0, TrueAudioID3v1Index = 1 };
}

class TrueAudio::File::FilePrivate
{
public:
  FilePrivate(const ID3v2::FrameFactory *frameFactory = ID3v2::FrameFactory::instance()) :
	ID3v2FrameFactory(frameFactory),
	ID3v2Location(-1),
	ID3v2OriginalSize(0),
	ID3v1Location(-1),
	properties(0),
	hasID3v1(false),
	hasID3v2(false) {}

  ~FilePrivate()
  {
	delete properties;
  }

  const ID3v2::FrameFactory *ID3v2FrameFactory;
  long ID3v2Location;
  uint ID3v2OriginalSize;

  long ID3v1Location;

  TagUnion tag;

  Properties *properties;

  // These indicate whether the file *on disk* has these tags, not if
  // this data structure does.  This is used in computing offsets.

  bool hasID3v1;
  bool hasID3v2;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

TrueAudio::File::File(FileName file, bool readProperties,
				 Properties::ReadStyle propertiesStyle) : TagLib::File(file)
{
  d = new FilePrivate;
  if(isOpen())
	read(readProperties, propertiesStyle);
}

TrueAudio::File::File(FileName file, ID3v2::FrameFactory *frameFactory,
				 bool readProperties, Properties::ReadStyle propertiesStyle) :
  TagLib::File(file)
{
  d = new FilePrivate(frameFactory);
  if(isOpen())
	read(readProperties, propertiesStyle);
}

TrueAudio::File::File(IOStream *stream, bool readProperties,
				 Properties::ReadStyle propertiesStyle) : TagLib::File(stream)
{
  d = new FilePrivate;
  if(isOpen())
	read(readProperties, propertiesStyle);
}

TrueAudio::File::File(IOStream *stream, ID3v2::FrameFactory *frameFactory,
				 bool readProperties, Properties::ReadStyle propertiesStyle) :
  TagLib::File(stream)
{
  d = new FilePrivate(frameFactory);
  if(isOpen())
	read(readProperties, propertiesStyle);
}

TrueAudio::File::~File()
{
  delete d;
}

TagLib::Tag *TrueAudio::File::tag() const
{
  return &d->tag;
}

PropertyMap TrueAudio::File::properties() const
{
  // once Tag::properties() is virtual, this case distinction could actually be done
  // within TagUnion.
  if(d->hasID3v2)
	return d->tag.access<ID3v2::Tag>(TrueAudioID3v2Index, false)->properties();
  if(d->hasID3v1)
	return d->tag.access<ID3v1::Tag>(TrueAudioID3v1Index, false)->properties();
  return PropertyMap();
}

PropertyMap TrueAudio::File::setProperties(const PropertyMap &properties)
{
  if(d->hasID3v2)
	return d->tag.access<ID3v2::Tag>(TrueAudioID3v2Index, false)->setProperties(properties);
  else if(d->hasID3v1)
	return d->tag.access<ID3v1::Tag>(TrueAudioID3v1Index, false)->setProperties(properties);
  else
	return d->tag.access<ID3v2::Tag>(TrueAudioID3v2Index, true)->setProperties(properties);
}

TrueAudio::Properties *TrueAudio::File::audioProperties() const
{
  return d->properties;
}

void TrueAudio::File::setID3v2FrameFactory(const ID3v2::FrameFactory *factory)
{
  d->ID3v2FrameFactory = factory;
}

bool TrueAudio::File::save()
{
  if(readOnly()) {
	debug("TrueAudio::File::save() -- File is read only.");
	return false;
  }

  // Update ID3v2 tag

  if(ID3v2Tag() && !ID3v2Tag()->isEmpty()) {
	if(!d->hasID3v2) {
	  d->ID3v2Location = 0;
	  d->ID3v2OriginalSize = 0;
	}
	ByteVector data = ID3v2Tag()->render();
	insert(data, d->ID3v2Location, d->ID3v2OriginalSize);
	d->ID3v1Location -= d->ID3v2OriginalSize - data.size();
	d->ID3v2OriginalSize = data.size();
	d->hasID3v2 = true;
  }
  else if(d->hasID3v2) {
	removeBlock(d->ID3v2Location, d->ID3v2OriginalSize);
	d->ID3v1Location -= d->ID3v2OriginalSize;
	d->ID3v2Location = -1;
	d->ID3v2OriginalSize = 0;
	d->hasID3v2 = false;
  }

  // Update ID3v1 tag

  if(ID3v1Tag() && !ID3v1Tag()->isEmpty()) {
	if(!d->hasID3v1) {
	  seek(0, End);
	  d->ID3v1Location = tell();
	}
	else
	  seek(d->ID3v1Location);
	writeBlock(ID3v1Tag()->render());
	d->hasID3v1 = true;
  }
  else if(d->hasID3v1) {
	removeBlock(d->ID3v1Location, 128);
	d->ID3v1Location = -1;
	d->hasID3v1 = false;
  }

  return true;
}

ID3v1::Tag *TrueAudio::File::ID3v1Tag(bool create)
{
  return d->tag.access<ID3v1::Tag>(TrueAudioID3v1Index, create);
}

ID3v2::Tag *TrueAudio::File::ID3v2Tag(bool create)
{
  return d->tag.access<ID3v2::Tag>(TrueAudioID3v2Index, create);
}

void TrueAudio::File::strip(int tags)
{
  if(tags & ID3v1) {
	d->tag.set(TrueAudioID3v1Index, 0);
	ID3v2Tag(true);
  }

  if(tags & ID3v2) {
	d->tag.set(TrueAudioID3v2Index, 0);

	if(!ID3v1Tag())
	  ID3v2Tag(true);
  }
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void TrueAudio::File::read(bool readProperties, Properties::ReadStyle /* propertiesStyle */)
{
  // Look for an ID3v2 tag

  d->ID3v2Location = findID3v2();

  if(d->ID3v2Location >= 0) {

	d->tag.set(TrueAudioID3v2Index, new ID3v2::Tag(this, d->ID3v2Location, d->ID3v2FrameFactory));

	d->ID3v2OriginalSize = ID3v2Tag()->header()->completeTagSize();

	if(ID3v2Tag()->header()->tagSize() <= 0)
	  d->tag.set(TrueAudioID3v2Index, 0);
	else
	  d->hasID3v2 = true;
  }

  // Look for an ID3v1 tag

  d->ID3v1Location = findID3v1();

  if(d->ID3v1Location >= 0) {
	d->tag.set(TrueAudioID3v1Index, new ID3v1::Tag(this, d->ID3v1Location));
	d->hasID3v1 = true;
  }

  if(!d->hasID3v1)
	ID3v2Tag(true);

  // Look for TrueAudio metadata

  if(readProperties) {
	if(d->ID3v2Location >= 0) {
	  seek(d->ID3v2Location + d->ID3v2OriginalSize);
	  d->properties = new Properties(readBlock(TrueAudio::HeaderSize),
									 length() - d->ID3v2OriginalSize);
	}
	else {
	  seek(0);
	  d->properties = new Properties(readBlock(TrueAudio::HeaderSize),
									 length());
	}
  }
}

long TrueAudio::File::findID3v1()
{
  if(!isValid())
	return -1;

  seek(-128, End);
  long p = tell();

  if(readBlock(3) == ID3v1::Tag::fileIdentifier())
	return p;

  return -1;
}

long TrueAudio::File::findID3v2()
{
  if(!isValid())
	return -1;

  seek(0);

  if(readBlock(3) == ID3v2::Header::fileIdentifier())
	return 0;

  return -1;
}

/*** End of inlined file: trueaudiofile.cpp ***/


/*** Start of inlined file: trueaudioproperties.cpp ***/
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

#include <bitset>

using namespace TagLib;

class TrueAudio::Properties::PropertiesPrivate
{
public:
  PropertiesPrivate(const ByteVector &d, long length, ReadStyle s) :
	data(d),
	streamLength(length),
	style(s),
	version(0),
	length(0),
	bitrate(0),
	sampleRate(0),
	channels(0),
	bitsPerSample(0),
	sampleFrames(0) {}

  ByteVector data;
  long streamLength;
  ReadStyle style;
  int version;
  int length;
  int bitrate;
  int sampleRate;
  int channels;
  int bitsPerSample;
  uint sampleFrames;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

TrueAudio::Properties::Properties(const ByteVector &data, long streamLength, ReadStyle style) : AudioProperties(style)
{
  d = new PropertiesPrivate(data, streamLength, style);
  read();
}

TrueAudio::Properties::~Properties()
{
  delete d;
}

int TrueAudio::Properties::length() const
{
  return d->length;
}

int TrueAudio::Properties::bitrate() const
{
  return d->bitrate;
}

int TrueAudio::Properties::sampleRate() const
{
  return d->sampleRate;
}

int TrueAudio::Properties::bitsPerSample() const
{
  return d->bitsPerSample;
}

int TrueAudio::Properties::channels() const
{
  return d->channels;
}

uint TrueAudio::Properties::sampleFrames() const
{
  return d->sampleFrames;
}

int TrueAudio::Properties::ttaVersion() const
{
  return d->version;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void TrueAudio::Properties::read()
{
  if(!d->data.startsWith("TTA"))
	return;

  int pos = 3;

  d->version = d->data[pos] - '0';
  pos += 1;

  // According to http://en.true-audio.com/TTA_Lossless_Audio_Codec_-_Format_Description
  // TTA2 headers are in development, and have a different format
  if(1 == d->version) {
	// Skip the audio format
	pos += 2;

	d->channels = d->data.mid(pos, 2).toShort(false);
	pos += 2;

	d->bitsPerSample = d->data.mid(pos, 2).toShort(false);
	pos += 2;

	d->sampleRate = d->data.mid(pos, 4).toUInt(false);
	pos += 4;

	d->sampleFrames = d->data.mid(pos, 4).toUInt(false);
	d->length = d->sampleRate > 0 ? d->sampleFrames / d->sampleRate : 0;

	d->bitrate = d->length > 0 ? ((d->streamLength * 8L) / d->length) / 1000 : 0;
  }
}

/*** End of inlined file: trueaudioproperties.cpp ***/


/*** Start of inlined file: asftag.cpp ***/
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace TagLib;

class ASF::Tag::TagPrivate
{
public:
  String title;
  String artist;
  String copyright;
  String comment;
  String rating;
  AttributeListMap attributeListMap;
};

ASF::Tag::Tag()
: TagLib::Tag()
{
  d = new TagPrivate;
}

ASF::Tag::~Tag()
{
  if(d)
	delete d;
}

String ASF::Tag::title() const
{
  return d->title;
}

String ASF::Tag::artist() const
{
  return d->artist;
}

String ASF::Tag::album() const
{
  if(d->attributeListMap.contains("WM/AlbumTitle"))
	return d->attributeListMap["WM/AlbumTitle"][0].toString();
  return String::null;
}

String ASF::Tag::copyright() const
{
  return d->copyright;
}

String ASF::Tag::comment() const
{
  return d->comment;
}

String ASF::Tag::rating() const
{
  return d->rating;
}

unsigned int ASF::Tag::year() const
{
  if(d->attributeListMap.contains("WM/Year"))
	return d->attributeListMap["WM/Year"][0].toString().toInt();
  return 0;
}

unsigned int ASF::Tag::track() const
{
  if(d->attributeListMap.contains("WM/TrackNumber")) {
	const ASF::Attribute attr = d->attributeListMap["WM/TrackNumber"][0];
	if(attr.type() == ASF::Attribute::DWordType)
	  return attr.toUInt();
	else
	  return attr.toString().toInt();
  }
  if(d->attributeListMap.contains("WM/Track"))
	return d->attributeListMap["WM/Track"][0].toUInt();
  return 0;
}

String ASF::Tag::genre() const
{
  if(d->attributeListMap.contains("WM/Genre"))
	return d->attributeListMap["WM/Genre"][0].toString();
  return String::null;
}

void ASF::Tag::setTitle(const String &value)
{
  d->title = value;
}

void ASF::Tag::setArtist(const String &value)
{
  d->artist = value;
}

void ASF::Tag::setCopyright(const String &value)
{
  d->copyright = value;
}

void ASF::Tag::setComment(const String &value)
{
  d->comment = value;
}

void ASF::Tag::setRating(const String &value)
{
  d->rating = value;
}

void ASF::Tag::setAlbum(const String &value)
{
  setAttribute("WM/AlbumTitle", value);
}

void ASF::Tag::setGenre(const String &value)
{
  setAttribute("WM/Genre", value);
}

void ASF::Tag::setYear(uint value)
{
  setAttribute("WM/Year", String::number(value));
}

void ASF::Tag::setTrack(uint value)
{
  setAttribute("WM/TrackNumber", String::number(value));
}

ASF::AttributeListMap& ASF::Tag::attributeListMap()
{
  return d->attributeListMap;
}

void ASF::Tag::removeItem(const String &key)
{
  AttributeListMap::Iterator it = d->attributeListMap.find(key);
  if(it != d->attributeListMap.end())
	d->attributeListMap.erase(it);
}

void ASF::Tag::setAttribute(const String &name, const Attribute &attribute)
{
  AttributeList value;
  value.append(attribute);
  d->attributeListMap.insert(name, value);
}

void ASF::Tag::addAttribute(const String &name, const Attribute &attribute)
{
  if(d->attributeListMap.contains(name)) {
	d->attributeListMap[name].append(attribute);
  }
  else {
	setAttribute(name, attribute);
  }
}

bool ASF::Tag::isEmpty() const
{
  return TagLib::Tag::isEmpty() &&
		 copyright().isEmpty() &&
		 rating().isEmpty() &&
		 d->attributeListMap.isEmpty();
}

/*** End of inlined file: asftag.cpp ***/


/*** Start of inlined file: asffile.cpp ***/
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace TagLib;

class ASF::File::FilePrivate
{
public:
  FilePrivate():
	size(0),
	tag(0),
	properties(0),
	contentDescriptionObject(0),
	extendedContentDescriptionObject(0),
	headerExtensionObject(0),
	metadataObject(0),
	metadataLibraryObject(0) {}
  unsigned long long size;
  ASF::Tag *tag;
  ASF::Properties *properties;
  List<ASF::File::BaseObject *> objects;
  ASF::File::ContentDescriptionObject *contentDescriptionObject;
  ASF::File::ExtendedContentDescriptionObject *extendedContentDescriptionObject;
  ASF::File::HeaderExtensionObject *headerExtensionObject;
  ASF::File::MetadataObject *metadataObject;
  ASF::File::MetadataLibraryObject *metadataLibraryObject;
};

static ByteVector headerGuid("\x30\x26\xB2\x75\x8E\x66\xCF\x11\xA6\xD9\x00\xAA\x00\x62\xCE\x6C", 16);
static ByteVector filePropertiesGuid("\xA1\xDC\xAB\x8C\x47\xA9\xCF\x11\x8E\xE4\x00\xC0\x0C\x20\x53\x65", 16);
static ByteVector streamPropertiesGuid("\x91\x07\xDC\xB7\xB7\xA9\xCF\x11\x8E\xE6\x00\xC0\x0C\x20\x53\x65", 16);
static ByteVector contentDescriptionGuid("\x33\x26\xB2\x75\x8E\x66\xCF\x11\xA6\xD9\x00\xAA\x00\x62\xCE\x6C", 16);
static ByteVector extendedContentDescriptionGuid("\x40\xA4\xD0\xD2\x07\xE3\xD2\x11\x97\xF0\x00\xA0\xC9\x5E\xA8\x50", 16);
static ByteVector headerExtensionGuid("\xb5\x03\xbf_.\xa9\xcf\x11\x8e\xe3\x00\xc0\x0c Se", 16);
static ByteVector metadataGuid("\xEA\xCB\xF8\xC5\xAF[wH\204g\xAA\214D\xFAL\xCA", 16);
static ByteVector metadataLibraryGuid("\224\034#D\230\224\321I\241A\x1d\x13NEpT", 16);
static ByteVector contentEncryptionGuid("\xFB\xB3\x11\x22\x23\xBD\xD2\x11\xB4\xB7\x00\xA0\xC9\x55\xFC\x6E", 16);
static ByteVector extendedContentEncryptionGuid("\x14\xE6\x8A\x29\x22\x26 \x17\x4C\xB9\x35\xDA\xE0\x7E\xE9\x28\x9C", 16);
static ByteVector advancedContentEncryptionGuid("\xB6\x9B\x07\x7A\xA4\xDA\x12\x4E\xA5\xCA\x91\xD3\x8D\xC1\x1A\x8D", 16);

class ASF::File::BaseObject
{
public:
  ByteVector data;
  virtual ~BaseObject() {}
  virtual ByteVector guid() = 0;
  virtual void parse(ASF::File *file, unsigned int size);
  virtual ByteVector render(ASF::File *file);
};

class ASF::File::UnknownObject : public ASF::File::BaseObject
{
  ByteVector myGuid;
public:
  UnknownObject(const ByteVector &guid);
  ByteVector guid();
};

class ASF::File::FilePropertiesObject : public ASF::File::BaseObject
{
public:
  ByteVector guid();
  void parse(ASF::File *file, uint size);
};

class ASF::File::StreamPropertiesObject : public ASF::File::BaseObject
{
public:
  ByteVector guid();
  void parse(ASF::File *file, uint size);
};

class ASF::File::ContentDescriptionObject : public ASF::File::BaseObject
{
public:
  ByteVector guid();
  void parse(ASF::File *file, uint size);
  ByteVector render(ASF::File *file);
};

class ASF::File::ExtendedContentDescriptionObject : public ASF::File::BaseObject
{
public:
  ByteVectorList attributeData;
  ByteVector guid();
  void parse(ASF::File *file, uint size);
  ByteVector render(ASF::File *file);
};

class ASF::File::MetadataObject : public ASF::File::BaseObject
{
public:
  ByteVectorList attributeData;
  ByteVector guid();
  void parse(ASF::File *file, uint size);
  ByteVector render(ASF::File *file);
};

class ASF::File::MetadataLibraryObject : public ASF::File::BaseObject
{
public:
  ByteVectorList attributeData;
  ByteVector guid();
  void parse(ASF::File *file, uint size);
  ByteVector render(ASF::File *file);
};

class ASF::File::HeaderExtensionObject : public ASF::File::BaseObject
{
public:
  List<ASF::File::BaseObject *> objects;
  ~HeaderExtensionObject();
  ByteVector guid();
  void parse(ASF::File *file, uint size);
  ByteVector render(ASF::File *file);
};

ASF::File::HeaderExtensionObject::~HeaderExtensionObject()
{
  for(unsigned int i = 0; i < objects.size(); i++) {
	delete objects[i];
  }
}

void ASF::File::BaseObject::parse(ASF::File *file, unsigned int size)
{
  data.clear();
  if (size > 24 && size <= (unsigned int)(file->length()))
	data = file->readBlock(size - 24);
  else
	data = ByteVector::null;
}

ByteVector ASF::File::BaseObject::render(ASF::File * /*file*/)
{
  return guid() + ByteVector::fromLongLong(data.size() + 24, false) + data;
}

ASF::File::UnknownObject::UnknownObject(const ByteVector &guid) : myGuid(guid)
{
}

ByteVector ASF::File::UnknownObject::guid()
{
  return myGuid;
}

ByteVector ASF::File::FilePropertiesObject::guid()
{
  return filePropertiesGuid;
}

void ASF::File::FilePropertiesObject::parse(ASF::File *file, uint size)
{
  BaseObject::parse(file, size);
  file->d->properties->setLength((int)(data.mid(40, 8).toLongLong(false) / 10000000L - data.mid(56, 8).toLongLong(false) / 1000L));
}

ByteVector ASF::File::StreamPropertiesObject::guid()
{
  return streamPropertiesGuid;
}

void ASF::File::StreamPropertiesObject::parse(ASF::File *file, uint size)
{
  BaseObject::parse(file, size);
  file->d->properties->setChannels(data.mid(56, 2).toShort(false));
  file->d->properties->setSampleRate(data.mid(58, 4).toUInt(false));
  file->d->properties->setBitrate(data.mid(62, 4).toUInt(false) * 8 / 1000);
}

ByteVector ASF::File::ContentDescriptionObject::guid()
{
  return contentDescriptionGuid;
}

void ASF::File::ContentDescriptionObject::parse(ASF::File *file, uint /*size*/)
{
  file->d->contentDescriptionObject = this;
  int titleLength = file->readWORD();
  int artistLength = file->readWORD();
  int copyrightLength = file->readWORD();
  int commentLength = file->readWORD();
  int ratingLength = file->readWORD();
  file->d->tag->setTitle(file->readString(titleLength));
  file->d->tag->setArtist(file->readString(artistLength));
  file->d->tag->setCopyright(file->readString(copyrightLength));
  file->d->tag->setComment(file->readString(commentLength));
  file->d->tag->setRating(file->readString(ratingLength));
}

ByteVector ASF::File::ContentDescriptionObject::render(ASF::File *file)
{
  ByteVector v1 = file->renderString(file->d->tag->title());
  ByteVector v2 = file->renderString(file->d->tag->artist());
  ByteVector v3 = file->renderString(file->d->tag->copyright());
  ByteVector v4 = file->renderString(file->d->tag->comment());
  ByteVector v5 = file->renderString(file->d->tag->rating());
  data.clear();
  data.append(ByteVector::fromShort(static_cast<short>(v1.size()), false));
  data.append(ByteVector::fromShort(static_cast<short>(v2.size()), false));
  data.append(ByteVector::fromShort(static_cast<short>(v3.size()), false));
  data.append(ByteVector::fromShort(static_cast<short>(v4.size()), false));
  data.append(ByteVector::fromShort(static_cast<short>(v5.size()), false));
  data.append(v1);
  data.append(v2);
  data.append(v3);
  data.append(v4);
  data.append(v5);
  return BaseObject::render(file);
}

ByteVector ASF::File::ExtendedContentDescriptionObject::guid()
{
  return extendedContentDescriptionGuid;
}

void ASF::File::ExtendedContentDescriptionObject::parse(ASF::File *file, uint /*size*/)
{
  file->d->extendedContentDescriptionObject = this;
  int count = file->readWORD();
  while(count--) {
	ASF::Attribute attribute;
	String name = attribute.parse(*file);
	file->d->tag->addAttribute(name, attribute);
  }
}

ByteVector ASF::File::ExtendedContentDescriptionObject::render(ASF::File *file)
{
  data.clear();
  data.append(ByteVector::fromShort(static_cast<short>(attributeData.size()), false));
  data.append(attributeData.toByteVector(ByteVector::null));
  return BaseObject::render(file);
}

ByteVector ASF::File::MetadataObject::guid()
{
  return metadataGuid;
}

void ASF::File::MetadataObject::parse(ASF::File *file, uint /*size*/)
{
  file->d->metadataObject = this;
  int count = file->readWORD();
  while(count--) {
	ASF::Attribute attribute;
	String name = attribute.parse(*file, 1);
	file->d->tag->addAttribute(name, attribute);
  }
}

ByteVector ASF::File::MetadataObject::render(ASF::File *file)
{
  data.clear();
  data.append(ByteVector::fromShort(static_cast<short>(attributeData.size()), false));
  data.append(attributeData.toByteVector(ByteVector::null));
  return BaseObject::render(file);
}

ByteVector ASF::File::MetadataLibraryObject::guid()
{
  return metadataLibraryGuid;
}

void ASF::File::MetadataLibraryObject::parse(ASF::File *file, uint /*size*/)
{
  file->d->metadataLibraryObject = this;
  int count = file->readWORD();
  while(count--) {
	ASF::Attribute attribute;
	String name = attribute.parse(*file, 2);
	file->d->tag->addAttribute(name, attribute);
  }
}

ByteVector ASF::File::MetadataLibraryObject::render(ASF::File *file)
{
  data.clear();
  data.append(ByteVector::fromShort(static_cast<short>(attributeData.size()), false));
  data.append(attributeData.toByteVector(ByteVector::null));
  return BaseObject::render(file);
}

ByteVector ASF::File::HeaderExtensionObject::guid()
{
  return headerExtensionGuid;
}

void ASF::File::HeaderExtensionObject::parse(ASF::File *file, uint /*size*/)
{
  file->d->headerExtensionObject = this;
  file->seek(18, File::Current);
  long long dataSize = file->readDWORD();
  long long dataPos = 0;
  while(dataPos < dataSize) {
	ByteVector guid = file->readBlock(16);
	if(guid.size() != 16) {
	  file->setValid(false);
	  break;
	}
	bool ok;
	long long size = file->readQWORD(&ok);
	if(!ok) {
	  file->setValid(false);
	  break;
	}
	BaseObject *obj;
	if(guid == metadataGuid) {
	  obj = new MetadataObject();
	}
	else if(guid == metadataLibraryGuid) {
	  obj = new MetadataLibraryObject();
	}
	else {
	  obj = new UnknownObject(guid);
	}
	obj->parse(file, size);
	objects.append(obj);
	dataPos += size;
  }
}

ByteVector ASF::File::HeaderExtensionObject::render(ASF::File *file)
{
  data.clear();
  for(unsigned int i = 0; i < objects.size(); i++) {
	data.append(objects[i]->render(file));
  }
  data = ByteVector("\x11\xD2\xD3\xAB\xBA\xA9\xcf\x11\x8E\xE6\x00\xC0\x0C\x20\x53\x65\x06\x00", 18) + ByteVector::fromUInt(data.size(), false) + data;
  return BaseObject::render(file);
}

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

ASF::File::File(FileName file, bool readProperties, Properties::ReadStyle propertiesStyle)
  : TagLib::File(file)
{
  d = new FilePrivate;
  read(readProperties, propertiesStyle);
}

ASF::File::File(IOStream *stream, bool readProperties, Properties::ReadStyle propertiesStyle)
  : TagLib::File(stream)
{
  d = new FilePrivate;
  read(readProperties, propertiesStyle);
}

ASF::File::~File()
{
  for(unsigned int i = 0; i < d->objects.size(); i++) {
	delete d->objects[i];
  }
  if(d->tag) {
	delete d->tag;
  }
  if(d->properties) {
	delete d->properties;
  }
  delete d;
}

ASF::Tag *ASF::File::tag() const
{
  return d->tag;
}

ASF::Properties *ASF::File::audioProperties() const
{
  return d->properties;
}

void ASF::File::read(bool /*readProperties*/, Properties::ReadStyle /*propertiesStyle*/)
{
  if(!isValid())
	return;

  ByteVector guid = readBlock(16);
  if(guid != headerGuid) {
	debug("ASF: Not an ASF file.");
	setValid(false);
	return;
  }

  d->tag = new ASF::Tag();
  d->properties = new ASF::Properties();

  bool ok;
  d->size = readQWORD(&ok);
  if(!ok) {
	setValid(false);
	return;
  }
  int numObjects = readDWORD(&ok);
  if(!ok) {
	setValid(false);
	return;
  }
  seek(2, Current);

  for(int i = 0; i < numObjects; i++) {
	ByteVector guid = readBlock(16);
	if(guid.size() != 16) {
	  setValid(false);
	  break;
	}
	long size = (long)readQWORD(&ok);
	if(!ok) {
	  setValid(false);
	  break;
	}
	BaseObject *obj;
	if(guid == filePropertiesGuid) {
	  obj = new FilePropertiesObject();
	}
	else if(guid == streamPropertiesGuid) {
	  obj = new StreamPropertiesObject();
	}
	else if(guid == contentDescriptionGuid) {
	  obj = new ContentDescriptionObject();
	}
	else if(guid == extendedContentDescriptionGuid) {
	  obj = new ExtendedContentDescriptionObject();
	}
	else if(guid == headerExtensionGuid) {
	  obj = new HeaderExtensionObject();
	}
	else {
	  if(guid == contentEncryptionGuid ||
		 guid == extendedContentEncryptionGuid ||
		 guid == advancedContentEncryptionGuid) {
		d->properties->setEncrypted(true);
	  }
	  obj = new UnknownObject(guid);
	}
	obj->parse(this, size);
	d->objects.append(obj);
  }
}

bool ASF::File::save()
{
  if(readOnly()) {
	debug("ASF::File::save() -- File is read only.");
	return false;
  }

  if(!isValid()) {
	debug("ASF::File::save() -- Trying to save invalid file.");
	return false;
  }

  if(!d->contentDescriptionObject) {
	d->contentDescriptionObject = new ContentDescriptionObject();
	d->objects.append(d->contentDescriptionObject);
  }
  if(!d->extendedContentDescriptionObject) {
	d->extendedContentDescriptionObject = new ExtendedContentDescriptionObject();
	d->objects.append(d->extendedContentDescriptionObject);
  }
  if(!d->headerExtensionObject) {
	d->headerExtensionObject = new HeaderExtensionObject();
	d->objects.append(d->headerExtensionObject);
  }
  if(!d->metadataObject) {
	d->metadataObject = new MetadataObject();
	d->headerExtensionObject->objects.append(d->metadataObject);
  }
  if(!d->metadataLibraryObject) {
	d->metadataLibraryObject = new MetadataLibraryObject();
	d->headerExtensionObject->objects.append(d->metadataLibraryObject);
  }

  ASF::AttributeListMap::ConstIterator it = d->tag->attributeListMap().begin();
  for(; it != d->tag->attributeListMap().end(); it++) {
	const String &name = it->first;
	const AttributeList &attributes = it->second;
	bool inExtendedContentDescriptionObject = false;
	bool inMetadataObject = false;
	for(unsigned int j = 0; j < attributes.size(); j++) {
	  const Attribute &attribute = attributes[j];
	  bool largeValue = attribute.dataSize() > 65535;
	  if(!inExtendedContentDescriptionObject && !largeValue && attribute.language() == 0 && attribute.stream() == 0) {
		d->extendedContentDescriptionObject->attributeData.append(attribute.render(name));
		inExtendedContentDescriptionObject = true;
	  }
	  else if(!inMetadataObject && !largeValue && attribute.language() == 0 && attribute.stream() != 0) {
		d->metadataObject->attributeData.append(attribute.render(name, 1));
		inMetadataObject = true;
	  }
	  else {
		d->metadataLibraryObject->attributeData.append(attribute.render(name, 2));
	  }
	}
  }

  ByteVector data;
  for(unsigned int i = 0; i < d->objects.size(); i++) {
	data.append(d->objects[i]->render(this));
  }
  data = headerGuid + ByteVector::fromLongLong(data.size() + 30, false) + ByteVector::fromUInt(d->objects.size(), false) + ByteVector("\x01\x02", 2) + data;
  insert(data, 0, d->size);

  return true;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

int ASF::File::readBYTE(bool *ok)
{
  ByteVector v = readBlock(1);
  if(v.size() != 1) {
	if(ok) *ok = false;
	return 0;
  }
  if(ok) *ok = true;
  return v[0];
}

unsigned short ASF::File::readWORD(bool *ok)
{
  ByteVector v = readBlock(2);
  if(v.size() != 2) {
	if(ok) *ok = false;
	return 0;
  }
  if(ok) *ok = true;
  return v.toUShort(false);
}

unsigned int ASF::File::readDWORD(bool *ok)
{
  ByteVector v = readBlock(4);
  if(v.size() != 4) {
	if(ok) *ok = false;
	return 0;
  }
  if(ok) *ok = true;
  return v.toUInt(false);
}

long long ASF::File::readQWORD(bool *ok)
{
  ByteVector v = readBlock(8);
  if(v.size() != 8) {
	if(ok) *ok = false;
	return 0;
  }
  if(ok) *ok = true;
  return v.toLongLong(false);
}

String ASF::File::readString(int length)
{
  ByteVector data = readBlock(length);
  unsigned int size = data.size();
  while (size >= 2) {
	if(data[size - 1] != '\0' || data[size - 2] != '\0') {
	  break;
	}
	size -= 2;
  }
  if(size != data.size()) {
	data.resize(size);
  }
  return String(data, String::UTF16LE);
}

ByteVector ASF::File::renderString(const String &str, bool includeLength)
{
  ByteVector data = str.data(String::UTF16LE) + ByteVector::fromShort(0, false);
  if(includeLength) {
	data = ByteVector::fromShort(static_cast<short>(data.size()), false) + data;
  }
  return data;
}

/*** End of inlined file: asffile.cpp ***/


/*** Start of inlined file: asfproperties.cpp ***/
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace TagLib;

class ASF::Properties::PropertiesPrivate
{
public:
  PropertiesPrivate(): length(0), bitrate(0), sampleRate(0), channels(0), encrypted(false) {}
  int length;
  int bitrate;
  int sampleRate;
  int channels;
  bool encrypted;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

ASF::Properties::Properties() : AudioProperties(AudioProperties::Average)
{
  d = new PropertiesPrivate;
}

ASF::Properties::~Properties()
{
  if(d)
	delete d;
}

int ASF::Properties::length() const
{
  return d->length;
}

int ASF::Properties::bitrate() const
{
  return d->bitrate;
}

int ASF::Properties::sampleRate() const
{
  return d->sampleRate;
}

int ASF::Properties::channels() const
{
  return d->channels;
}

bool ASF::Properties::isEncrypted() const
{
  return d->encrypted;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void ASF::Properties::setLength(int length)
{
  d->length = length;
}

void ASF::Properties::setBitrate(int length)
{
  d->bitrate = length;
}

void ASF::Properties::setSampleRate(int length)
{
  d->sampleRate = length;
}

void ASF::Properties::setChannels(int length)
{
  d->channels = length;
}

void ASF::Properties::setEncrypted(bool encrypted)
{
  d->encrypted = encrypted;
}

/*** End of inlined file: asfproperties.cpp ***/


/*** Start of inlined file: asfattribute.cpp ***/
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace TagLib;

class ASF::Attribute::AttributePrivate : public RefCounter
{
public:
  AttributePrivate()
	: pictureValue(ASF::Picture::fromInvalid()),
	  stream(0),
	  language(0) {}
  AttributeTypes type;
  String stringValue;
  ByteVector byteVectorValue;
  ASF::Picture pictureValue;
  union {
	unsigned int intValue;
	unsigned short shortValue;
	unsigned long long longLongValue;
	bool boolValue;
  };
  int stream;
  int language;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

ASF::Attribute::Attribute()
{
  d = new AttributePrivate;
  d->type = UnicodeType;
}

ASF::Attribute::Attribute(const ASF::Attribute &other)
  : d(other.d)
{
  d->ref();
}

ASF::Attribute &ASF::Attribute::operator=(const ASF::Attribute &other)
{
  if(d->deref())
	delete d;
  d = other.d;
  d->ref();
  return *this;
}

ASF::Attribute::~Attribute()
{
  if(d->deref())
	delete d;
}

ASF::Attribute::Attribute(const String &value)
{
  d = new AttributePrivate;
  d->type = UnicodeType;
  d->stringValue = value;
}

ASF::Attribute::Attribute(const ByteVector &value)
{
  d = new AttributePrivate;
  d->type = BytesType;
  d->byteVectorValue = value;
}

ASF::Attribute::Attribute(const ASF::Picture &value)
{
  d = new AttributePrivate;
  d->type = BytesType;
  d->pictureValue = value;
}

ASF::Attribute::Attribute(unsigned int value)
{
  d = new AttributePrivate;
  d->type = DWordType;
  d->intValue = value;
}

ASF::Attribute::Attribute(unsigned long long value)
{
  d = new AttributePrivate;
  d->type = QWordType;
  d->longLongValue = value;
}

ASF::Attribute::Attribute(unsigned short value)
{
  d = new AttributePrivate;
  d->type = WordType;
  d->shortValue = value;
}

ASF::Attribute::Attribute(bool value)
{
  d = new AttributePrivate;
  d->type = BoolType;
  d->boolValue = value;
}

ASF::Attribute::AttributeTypes ASF::Attribute::type() const
{
  return d->type;
}

String ASF::Attribute::toString() const
{
  return d->stringValue;
}

ByteVector ASF::Attribute::toByteVector() const
{
  if(d->pictureValue.isValid())
	return d->pictureValue.render();
  return d->byteVectorValue;
}

unsigned short ASF::Attribute::toBool() const
{
  return d->shortValue;
}

unsigned short ASF::Attribute::toUShort() const
{
  return d->shortValue;
}

unsigned int ASF::Attribute::toUInt() const
{
  return d->intValue;
}

unsigned long long ASF::Attribute::toULongLong() const
{
  return d->longLongValue;
}

ASF::Picture ASF::Attribute::toPicture() const
{
  return d->pictureValue;
}

String ASF::Attribute::parse(ASF::File &f, int kind)
{
  uint size, nameLength;
  String name;
  d->pictureValue = Picture::fromInvalid();
  // extended content descriptor
  if(kind == 0) {
	nameLength = f.readWORD();
	name = f.readString(nameLength);
	d->type = ASF::Attribute::AttributeTypes(f.readWORD());
	size = f.readWORD();
  }
  // metadata & metadata library
  else {
	int temp = f.readWORD();
	// metadata library
	if(kind == 2) {
	  d->language = temp;
	}
	d->stream = f.readWORD();
	nameLength = f.readWORD();
	d->type = ASF::Attribute::AttributeTypes(f.readWORD());
	size = f.readDWORD();
	name = f.readString(nameLength);
  }

  if(kind != 2 && size > 65535) {
	debug("ASF::Attribute::parse() -- Value larger than 64kB");
  }

  switch(d->type) {
  case WordType:
	d->shortValue = f.readWORD();
	break;

  case BoolType:
	if(kind == 0) {
	  d->boolValue = f.readDWORD() == 1;
	}
	else {
	  d->boolValue = f.readWORD() == 1;
	}
	break;

  case DWordType:
	d->intValue = f.readDWORD();
	break;

  case QWordType:
	d->longLongValue = f.readQWORD();
	break;

  case UnicodeType:
	d->stringValue = f.readString(size);
	break;

  case BytesType:
  case GuidType:
	d->byteVectorValue = f.readBlock(size);
	break;
  }

  if(d->type == BytesType && name == "WM/Picture") {
	d->pictureValue.parse(d->byteVectorValue);
	if(d->pictureValue.isValid()) {
	  d->byteVectorValue.clear();
	}
  }

  return name;
}

int ASF::Attribute::dataSize() const
{
  switch (d->type) {
  case WordType:
	return 2;
  case BoolType:
	return 4;
  case DWordType:
	return 4;
  case QWordType:
	return 5;
  case UnicodeType:
	return d->stringValue.size() * 2 + 2;
  case BytesType:
	if(d->pictureValue.isValid())
	  return d->pictureValue.dataSize();
  case GuidType:
	return d->byteVectorValue.size();
  }
  return 0;
}

ByteVector ASF::Attribute::render(const String &name, int kind) const
{
  ByteVector data;

  switch (d->type) {
  case WordType:
	data.append(ByteVector::fromShort(d->shortValue, false));
	break;

  case BoolType:
	if(kind == 0) {
	  data.append(ByteVector::fromUInt(d->boolValue ? 1 : 0, false));
	}
	else {
	  data.append(ByteVector::fromShort(d->boolValue ? 1 : 0, false));
	}
	break;

  case DWordType:
	data.append(ByteVector::fromUInt(d->intValue, false));
	break;

  case QWordType:
	data.append(ByteVector::fromLongLong(d->longLongValue, false));
	break;

  case UnicodeType:
	data.append(File::renderString(d->stringValue));
	break;

  case BytesType:
	if(d->pictureValue.isValid()) {
	  data.append(d->pictureValue.render());
	  break;
	}
  case GuidType:
	data.append(d->byteVectorValue);
	break;
  }

  if(kind == 0) {
	data = File::renderString(name, true) +
		   ByteVector::fromShort(static_cast<short>(d->type), false) +
		   ByteVector::fromShort(static_cast<short>(data.size()), false) +
		   data;
  }
  else {
	ByteVector nameData = File::renderString(name);
	data = ByteVector::fromShort(kind == 2 ? static_cast<short>(d->language) : 0, false) +
		   ByteVector::fromShort(static_cast<short>(d->stream), false) +
		   ByteVector::fromShort(static_cast<short>(nameData.size()), false) +
		   ByteVector::fromShort(static_cast<short>(d->type), false) +
		   ByteVector::fromUInt(data.size(), false) +
		   nameData +
		   data;
  }

  return data;
}

int ASF::Attribute::language() const
{
  return d->language;
}

void ASF::Attribute::setLanguage(int value)
{
  d->language = value;
}

int ASF::Attribute::stream() const
{
  return d->stream;
}

void ASF::Attribute::setStream(int value)
{
  d->stream = value;
}

/*** End of inlined file: asfattribute.cpp ***/


/*** Start of inlined file: asfpicture.cpp ***/
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace TagLib;

class ASF::Picture::PicturePrivate : public RefCounter
{
public:
  bool valid;
  Type type;
  String mimeType;
  String description;
  ByteVector picture;
};

////////////////////////////////////////////////////////////////////////////////
// Picture class members
////////////////////////////////////////////////////////////////////////////////

ASF::Picture::Picture()
{
  d = new PicturePrivate();
  d->valid = true;
}

ASF::Picture::Picture(const Picture& other)
  : d(other.d)
{
  d->ref();
}

ASF::Picture::~Picture()
{
  if(d->deref())
	delete d;
}

bool ASF::Picture::isValid() const
{
  return d->valid;
}

String ASF::Picture::mimeType() const
{
  return d->mimeType;
}

void ASF::Picture::setMimeType(const String &value)
{
  d->mimeType = value;
}

ASF::Picture::Type ASF::Picture::type() const
{
  return d->type;
}

void ASF::Picture::setType(const ASF::Picture::Type& t)
{
  d->type = t;
}

String ASF::Picture::description() const
{
  return d->description;
}

void ASF::Picture::setDescription(const String &desc)
{
  d->description = desc;
}

ByteVector ASF::Picture::picture() const
{
  return d->picture;
}

void ASF::Picture::setPicture(const ByteVector &p)
{
  d->picture = p;
}

int ASF::Picture::dataSize() const
{
  return
	9 + (d->mimeType.length() + d->description.length()) * 2 +
	d->picture.size();
}

ASF::Picture& ASF::Picture::operator=(const ASF::Picture& other)
{
  if(other.d != d) {
	if(d->deref())
	  delete d;
	d = other.d;
	d->ref();
  }
  return *this;
}

ByteVector ASF::Picture::render() const
{
  if(!isValid())
	return ByteVector::null;
  return
	ByteVector((char)d->type) +
	ByteVector::fromUInt(d->picture.size(), false) +
	ASF::File::renderString(d->mimeType) +
	ASF::File::renderString(d->description) +
	d->picture;
}

void ASF::Picture::parse(const ByteVector& bytes)
{
  d->valid = false;
  if(bytes.size() < 9)
	return;
  int pos = 0;
  d->type = (Type)bytes[0]; ++pos;
  uint dataLen = bytes.mid(pos, 4).toUInt(false); pos+=4;

  const ByteVector nullStringTerminator(2, 0);

  int endPos = bytes.find(nullStringTerminator, pos, 2);
  if(endPos < 0)
	return;
  d->mimeType = String(bytes.mid(pos, endPos - pos), String::UTF16LE);
  pos = endPos+2;

  endPos = bytes.find(nullStringTerminator, pos, 2);
  if(endPos < 0)
	return;
  d->description = String(bytes.mid(pos, endPos - pos), String::UTF16LE);
  pos = endPos+2;

  if(dataLen + pos != bytes.size())
	return;

  d->picture = bytes.mid(pos, dataLen);
  d->valid = true;
  return;
}

ASF::Picture ASF::Picture::fromInvalid()
{
  Picture ret;
  ret.d->valid = false;
  return ret;
}

/*** End of inlined file: asfpicture.cpp ***/


/*** Start of inlined file: rifffile.cpp ***/
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

#include <vector>

using namespace TagLib;

struct Chunk
{
  ByteVector name;
  TagLib::uint offset;
  TagLib::uint size;
  char padding;
};

class RIFF::File::FilePrivate
{
public:
  FilePrivate() :
	endianness(BigEndian),
	size(0)
  {

  }
  Endianness endianness;
  ByteVector type;
  TagLib::uint size;
  ByteVector format;

  std::vector<Chunk> chunks;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

RIFF::File::~File()
{
  delete d;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

RIFF::File::File(FileName file, Endianness endianness) : TagLib::File(file)
{
  d = new FilePrivate;
  d->endianness = endianness;

  if(isOpen())
	read();
}

RIFF::File::File(IOStream *stream, Endianness endianness) : TagLib::File(stream)
{
  d = new FilePrivate;
  d->endianness = endianness;

  if(isOpen())
	read();
}

TagLib::uint RIFF::File::riffSize() const
{
  return d->size;
}

TagLib::uint RIFF::File::chunkCount() const
{
  return d->chunks.size();
}

TagLib::uint RIFF::File::chunkDataSize(uint i) const
{
  return d->chunks[i].size;
}

TagLib::uint RIFF::File::chunkOffset(uint i) const
{
  return d->chunks[i].offset;
}

TagLib::uint RIFF::File::chunkPadding(uint i) const
{
  return d->chunks[i].padding;
}

ByteVector RIFF::File::chunkName(uint i) const
{
  if(i >= chunkCount())
	return ByteVector::null;

  return d->chunks[i].name;
}

ByteVector RIFF::File::chunkData(uint i)
{
  if(i >= chunkCount())
	return ByteVector::null;

  // Offset for the first subchunk's data

  long begin = 12 + 8;

  for(uint it = 0; it < i; it++)
	begin += 8 + d->chunks[it].size + d->chunks[it].padding;

  seek(begin);

  return readBlock(d->chunks[i].size);
}

void RIFF::File::setChunkData(const ByteVector &name, const ByteVector &data)
{
  if(d->chunks.size() == 0) {
	debug("RIFF::File::setChunkData - No valid chunks found.");
	return;
  }

  for(uint i = 0; i < d->chunks.size(); i++) {
	if(d->chunks[i].name == name) {

	  // First we update the global size

	  d->size += ((data.size() + 1) & ~1) - (d->chunks[i].size + d->chunks[i].padding);
	  insert(ByteVector::fromUInt(d->size, d->endianness == BigEndian), 4, 4);

	  // Now update the specific chunk

	  writeChunk(name, data, d->chunks[i].offset - 8, d->chunks[i].size + d->chunks[i].padding + 8);

	  d->chunks[i].size = data.size();
	  d->chunks[i].padding = (data.size() & 0x01) ? 1 : 0;

	  // Now update the internal offsets

	  for(i++; i < d->chunks.size(); i++)
		d->chunks[i].offset = d->chunks[i-1].offset + 8 + d->chunks[i-1].size + d->chunks[i-1].padding;

	  return;
	}
  }

  // Couldn't find an existing chunk, so let's create a new one.

  uint i =  d->chunks.size() - 1;
  ulong offset = d->chunks[i].offset + d->chunks[i].size;

  // First we update the global size

  d->size += (offset & 1) + data.size() + 8;
  insert(ByteVector::fromUInt(d->size, d->endianness == BigEndian), 4, 4);

  // Now add the chunk to the file

  writeChunk(name, data, offset, std::max(ulong(0), length() - offset), (offset & 1) ? 1 : 0);

  // And update our internal structure

  if (offset & 1) {
	d->chunks[i].padding = 1;
	offset++;
  }

  Chunk chunk;
  chunk.name = name;
  chunk.size = data.size();
  chunk.offset = offset + 8;
  chunk.padding = (data.size() & 0x01) ? 1 : 0;

  d->chunks.push_back(chunk);
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

static bool isValidChunkID(const ByteVector &name)
{
  if(name.size() != 4) {
	return false;
  }
  for(int i = 0; i < 4; i++) {
	if(name[i] < 32 || name[i] > 127) {
	  return false;
	}
  }
  return true;
}

void RIFF::File::read()
{
  bool bigEndian = (d->endianness == BigEndian);

  d->type = readBlock(4);
  d->size = readBlock(4).toUInt(bigEndian);
  d->format = readBlock(4);

  // + 8: chunk header at least, fix for additional junk bytes
  while(tell() + 8 <= length()) {
	ByteVector chunkName = readBlock(4);
	uint chunkSize = readBlock(4).toUInt(bigEndian);

	if(!isValidChunkID(chunkName)) {
	  debug("RIFF::File::read() -- Chunk '" + chunkName + "' has invalid ID");
	  setValid(false);
	  break;
	}

	if(tell() + chunkSize > uint(length())) {
	  debug("RIFF::File::read() -- Chunk '" + chunkName + "' has invalid size (larger than the file size)");
	  setValid(false);
	  break;
	}

	Chunk chunk;
	chunk.name = chunkName;
	chunk.size = chunkSize;
	chunk.offset = tell();

	seek(chunk.size, Current);

	// check padding
	chunk.padding = 0;
	long uPosNotPadded = tell();
	if((uPosNotPadded & 0x01) != 0) {
	  ByteVector iByte = readBlock(1);
	  if((iByte.size() != 1) || (iByte[0] != 0)) {
		// not well formed, re-seek
		seek(uPosNotPadded, Beginning);
	  }
	  else {
		chunk.padding = 1;
	  }
	}
	d->chunks.push_back(chunk);

  }
}

void RIFF::File::writeChunk(const ByteVector &name, const ByteVector &data,
							ulong offset, ulong replace, uint leadingPadding)
{
  ByteVector combined;
  if(leadingPadding) {
	combined.append(ByteVector(leadingPadding, '\x00'));
  }
  combined.append(name);
  combined.append(ByteVector::fromUInt(data.size(), d->endianness == BigEndian));
  combined.append(data);
  if((data.size() & 0x01) != 0) {
	combined.append('\x00');
  }
  insert(combined, offset, replace);
}

/*** End of inlined file: rifffile.cpp ***/


/*** Start of inlined file: aifffile.cpp ***/
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

using namespace TagLib;

class RIFF::AIFF::File::FilePrivate
{
public:
  FilePrivate() :
	properties(0),
	tag(0),
	tagChunkID("ID3 ")
  {

  }

  ~FilePrivate()
  {
	delete properties;
	delete tag;
  }

  Properties *properties;
  ID3v2::Tag *tag;
  ByteVector tagChunkID;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

RIFF::AIFF::File::File(FileName file, bool readProperties,
					   Properties::ReadStyle propertiesStyle) : RIFF::File(file, BigEndian)
{
  d = new FilePrivate;
  if(isOpen())
	read(readProperties, propertiesStyle);
}

RIFF::AIFF::File::File(IOStream *stream, bool readProperties,
					   Properties::ReadStyle propertiesStyle) : RIFF::File(stream, BigEndian)
{
  d = new FilePrivate;
  if(isOpen())
	read(readProperties, propertiesStyle);
}

RIFF::AIFF::File::~File()
{
  delete d;
}

ID3v2::Tag *RIFF::AIFF::File::tag() const
{
  return d->tag;
}

PropertyMap RIFF::AIFF::File::properties() const
{
  return d->tag->properties();
}

PropertyMap RIFF::AIFF::File::setProperties(const PropertyMap &properties)
{
  return d->tag->setProperties(properties);
}

RIFF::AIFF::Properties *RIFF::AIFF::File::audioProperties() const
{
  return d->properties;
}

bool RIFF::AIFF::File::save()
{
  if(readOnly()) {
	debug("RIFF::AIFF::File::save() -- File is read only.");
	return false;
  }

  if(!isValid()) {
	debug("RIFF::AIFF::File::save() -- Trying to save invalid file.");
	return false;
  }

  setChunkData(d->tagChunkID, d->tag->render());

  return true;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void RIFF::AIFF::File::read(bool readProperties, Properties::ReadStyle propertiesStyle)
{
  for(uint i = 0; i < chunkCount(); i++) {
	if(chunkName(i) == "ID3 " || chunkName(i) == "id3 ") {
	  d->tagChunkID = chunkName(i);
	  d->tag = new ID3v2::Tag(this, chunkOffset(i));
	}
	else if(chunkName(i) == "COMM" && readProperties)
	  d->properties = new Properties(chunkData(i), propertiesStyle);
  }

  if(!d->tag)
	d->tag = new ID3v2::Tag;
}

/*** End of inlined file: aifffile.cpp ***/


/*** Start of inlined file: aiffproperties.cpp ***/
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

#include <cmath>
// ldexp is a c99 function, which might not be defined in <cmath>
// so we pull in math.h too and hope it does the right (wrong) thing
// wrt. c99 functions in C++
#include <math.h>

////////////////////////////////////////////////////////////////////////////////
// nasty 80-bit float helpers
////////////////////////////////////////////////////////////////////////////////

#define UnsignedToFloat(u) (((double)((long)(u - 2147483647L - 1))) + 2147483648.0)

static double ConvertFromIeeeExtended(unsigned char *bytes)
{
  double f;
  int expon;
  unsigned long hiMant, loMant;

  expon  = ((bytes[0] & 0x7F) << 8) | (bytes[1] & 0xFF);

  hiMant = ((unsigned long)(bytes[2] & 0xFF) << 24) |
		   ((unsigned long)(bytes[3] & 0xFF) << 16) |
		   ((unsigned long)(bytes[4] & 0xFF) << 8)  |
		   ((unsigned long)(bytes[5] & 0xFF));

  loMant = ((unsigned long)(bytes[6] & 0xFF) << 24) |
		   ((unsigned long)(bytes[7] & 0xFF) << 16) |
		   ((unsigned long)(bytes[8] & 0xFF) << 8)  |
		   ((unsigned long)(bytes[9] & 0xFF));

  if (expon == 0 && hiMant == 0 && loMant == 0)
	f = 0;
  else {
	if(expon == 0x7FFF) /* Infinity or NaN */
	  f = HUGE_VAL;
	else {
	  expon -= 16383;
	  f  = ldexp(UnsignedToFloat(hiMant), expon -= 31);
	  f += ldexp(UnsignedToFloat(loMant), expon -= 32);
	}
  }

  if(bytes[0] & 0x80)
	return -f;
  else
	return f;
}

using namespace TagLib;

class RIFF::AIFF::Properties::PropertiesPrivate
{
public:
  PropertiesPrivate() :
	length(0),
	bitrate(0),
	sampleRate(0),
	channels(0),
	sampleWidth(0),
	sampleFrames(0)
  {

  }

  int length;
  int bitrate;
  int sampleRate;
  int channels;
  int sampleWidth;
  uint sampleFrames;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

RIFF::AIFF::Properties::Properties(const ByteVector &data, ReadStyle style) : AudioProperties(style)
{
  d = new PropertiesPrivate;
  read(data);
}

RIFF::AIFF::Properties::~Properties()
{
  delete d;
}

int RIFF::AIFF::Properties::length() const
{
  return d->length;
}

int RIFF::AIFF::Properties::bitrate() const
{
  return d->bitrate;
}

int RIFF::AIFF::Properties::sampleRate() const
{
  return d->sampleRate;
}

int RIFF::AIFF::Properties::channels() const
{
  return d->channels;
}

int RIFF::AIFF::Properties::sampleWidth() const
{
  return d->sampleWidth;
}

uint RIFF::AIFF::Properties::sampleFrames() const
{
  return d->sampleFrames;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void RIFF::AIFF::Properties::read(const ByteVector &data)
{
  d->channels       = data.mid(0, 2).toShort();
  d->sampleFrames   = data.mid(2, 4).toUInt();
  d->sampleWidth    = data.mid(6, 2).toShort();
  double sampleRate = ConvertFromIeeeExtended(reinterpret_cast<unsigned char *>(data.mid(8, 10).data()));
  d->sampleRate     = sampleRate;
  d->bitrate        = (sampleRate * d->sampleWidth * d->channels) / 1000.0;
  d->length         = d->sampleRate > 0 ? d->sampleFrames / d->sampleRate : 0;
}

/*** End of inlined file: aiffproperties.cpp ***/


/*** Start of inlined file: wavfile.cpp ***/
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

using namespace TagLib;

class RIFF::WAV::File::FilePrivate
{
public:
  FilePrivate() :
	properties(0),
	tag(0),
	tagChunkID("ID3 ")
  {

  }

  ~FilePrivate()
  {
	delete properties;
	delete tag;
  }

  Properties *properties;
  ID3v2::Tag *tag;
  ByteVector tagChunkID;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

RIFF::WAV::File::File(FileName file, bool readProperties,
					   Properties::ReadStyle propertiesStyle) : RIFF::File(file, LittleEndian)
{
  d = new FilePrivate;
  if(isOpen())
	read(readProperties, propertiesStyle);
}

RIFF::WAV::File::File(IOStream *stream, bool readProperties,
					   Properties::ReadStyle propertiesStyle) : RIFF::File(stream, LittleEndian)
{
  d = new FilePrivate;
  if(isOpen())
	read(readProperties, propertiesStyle);
}

RIFF::WAV::File::~File()
{
  delete d;
}

ID3v2::Tag *RIFF::WAV::File::tag() const
{
  return d->tag;
}

PropertyMap RIFF::WAV::File::properties() const
{
  return d->tag->properties();
}

PropertyMap RIFF::WAV::File::setProperties(const PropertyMap &properties)
{
  return d->tag->setProperties(properties);
}

RIFF::WAV::Properties *RIFF::WAV::File::audioProperties() const
{
  return d->properties;
}

bool RIFF::WAV::File::save()
{
  if(readOnly()) {
	debug("RIFF::WAV::File::save() -- File is read only.");
	return false;
  }

  if(!isValid()) {
	debug("RIFF::WAV::File::save() -- Trying to save invalid file.");
	return false;
  }

  setChunkData(d->tagChunkID, d->tag->render());

  return true;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void RIFF::WAV::File::read(bool readProperties, Properties::ReadStyle propertiesStyle)
{
  ByteVector formatData;
  uint streamLength = 0;
  for(uint i = 0; i < chunkCount(); i++) {
	if(chunkName(i) == "ID3 " || chunkName(i) == "id3 ") {
	  d->tagChunkID = chunkName(i);
	  d->tag = new ID3v2::Tag(this, chunkOffset(i));
	}
	else if(chunkName(i) == "fmt " && readProperties)
	  formatData = chunkData(i);
	else if(chunkName(i) == "data" && readProperties)
	  streamLength = chunkDataSize(i);
  }

  if(!formatData.isEmpty())
	d->properties = new Properties(formatData, streamLength, propertiesStyle);

  if(!d->tag)
	d->tag = new ID3v2::Tag;
}

/*** End of inlined file: wavfile.cpp ***/


/*** Start of inlined file: wavproperties.cpp ***/
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

#include <cmath>
#include <math.h>

using namespace TagLib;

class RIFF::WAV::Properties::PropertiesPrivate
{
public:
  PropertiesPrivate(uint streamLength = 0) :
	format(0),
	length(0),
	bitrate(0),
	sampleRate(0),
	channels(0),
	sampleWidth(0),
	sampleFrames(0),
	streamLength(streamLength)
  {

  }

  short format;
  int length;
  int bitrate;
  int sampleRate;
  int channels;
  int sampleWidth;
  uint sampleFrames;
  uint streamLength;
};

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

RIFF::WAV::Properties::Properties(const ByteVector &data, ReadStyle style) : AudioProperties(style)
{
  d = new PropertiesPrivate();
  read(data);
}

RIFF::WAV::Properties::Properties(const ByteVector &data, uint streamLength, ReadStyle style) : AudioProperties(style)
{
  d = new PropertiesPrivate(streamLength);
  read(data);
}

RIFF::WAV::Properties::~Properties()
{
  delete d;
}

int RIFF::WAV::Properties::length() const
{
  return d->length;
}

int RIFF::WAV::Properties::bitrate() const
{
  return d->bitrate;
}

int RIFF::WAV::Properties::sampleRate() const
{
  return d->sampleRate;
}

int RIFF::WAV::Properties::channels() const
{
  return d->channels;
}

int RIFF::WAV::Properties::sampleWidth() const
{
  return d->sampleWidth;
}

uint RIFF::WAV::Properties::sampleFrames() const
{
  return d->sampleFrames;
}

////////////////////////////////////////////////////////////////////////////////
// private members
////////////////////////////////////////////////////////////////////////////////

void RIFF::WAV::Properties::read(const ByteVector &data)
{
  d->format = data.mid(0, 2).toShort(false);
  d->channels = data.mid(2, 2).toShort(false);
  d->sampleRate = data.mid(4, 4).toUInt(false);
  d->sampleWidth = data.mid(14, 2).toShort(false);

  uint byteRate = data.mid(8, 4).toUInt(false);
  d->bitrate = byteRate * 8 / 1000;

  d->length = byteRate > 0 ? d->streamLength / byteRate : 0;
  if(d->channels > 0 && d->sampleWidth > 0)
	d->sampleFrames = d->streamLength / (d->channels * ((d->sampleWidth + 7) / 8));
}

/*** End of inlined file: wavproperties.cpp ***/


/*** Start of inlined file: modfilebase.cpp ***/
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

using namespace TagLib;
using namespace Mod;

Mod::FileBase::FileBase(FileName file) : TagLib::File(file)
{
}

Mod::FileBase::FileBase(IOStream *stream) : TagLib::File(stream)
{
}

void Mod::FileBase::writeString(const String &s, ulong size, char padding)
{
  ByteVector data(s.data(String::Latin1));
  data.resize(size, padding);
  writeBlock(data);
}

bool Mod::FileBase::readString(String &s, ulong size)
{
  ByteVector data(readBlock(size));
  if(data.size() < size) return false;
  int index = data.find((char) 0);
  if(index > -1)
  {
	data.resize(index);
  }
  data.replace((char) 0xff, ' ');

  s = data;
  return true;
}

void Mod::FileBase::writeByte(uchar byte)
{
  ByteVector data(1, byte);
  writeBlock(data);
}

void Mod::FileBase::writeU16L(ushort number)
{
  writeBlock(ByteVector::fromShort(number, false));
}

void Mod::FileBase::writeU32L(ulong number)
{
  writeBlock(ByteVector::fromUInt(number, false));
}

void Mod::FileBase::writeU16B(ushort number)
{
  writeBlock(ByteVector::fromShort(number, true));
}

void Mod::FileBase::writeU32B(ulong number)
{
  writeBlock(ByteVector::fromUInt(number, true));
}

bool Mod::FileBase::readByte(uchar &byte)
{
  ByteVector data(readBlock(1));
  if(data.size() < 1) return false;
  byte = data[0];
  return true;
}

bool Mod::FileBase::readU16L(ushort &number)
{
  ByteVector data(readBlock(2));
  if(data.size() < 2) return false;
  number = data.toUShort(false);
  return true;
}

bool Mod::FileBase::readU32L(ulong &number) {
  ByteVector data(readBlock(4));
  if(data.size() < 4) return false;
  number = data.toUInt(false);
  return true;
}

bool Mod::FileBase::readU16B(ushort &number)
{
  ByteVector data(readBlock(2));
  if(data.size() < 2) return false;
  number = data.toUShort(true);
  return true;
}

bool Mod::FileBase::readU32B(ulong &number) {
  ByteVector data(readBlock(4));
  if(data.size() < 4) return false;
  number = data.toUInt(true);
  return true;
}

/*** End of inlined file: modfilebase.cpp ***/


/*** Start of inlined file: modfile.cpp ***/
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


/*** Start of inlined file: modfileprivate.h ***/
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

#ifndef TAGLIB_MODFILEPRIVATE_H
#define TAGLIB_MODFILEPRIVATE_H

// some helper-macros only used internally by (s3m|it|xm)file.cpp
#define READ_ASSERT(cond) \
  if(!(cond)) \
  { \
	setValid(false); \
	return; \
  }

#define READ(setter,type,read) \
  { \
	type number; \
	READ_ASSERT(read(number)); \
	setter(number); \
  }

#define READ_BYTE(setter) READ(setter,uchar,readByte)
#define READ_U16L(setter) READ(setter,ushort,readU16L)
#define READ_U32L(setter) READ(setter,ulong,readU32L)
#define READ_U16B(setter) READ(setter,ushort,readU16B)
#define READ_U32B(setter) READ(setter,ulong,readU32B)

#define READ_STRING(setter,size) \
  { \
	String s; \
	READ_ASSERT(readString(s, size)); \
	setter(s); \
  }

#define READ_AS(type,name,read) \
  type name = 0; \
  READ_ASSERT(read(name));

#define READ_BYTE_AS(name) READ_AS(uchar,name,readByte)
#define READ_U16L_AS(name) READ_AS(ushort,name,readU16L)
#define READ_U32L_AS(name) READ_AS(ulong,name,readU32L)
#define READ_U16B_AS(name) READ_AS(ushort,name,readU16B)
#define READ_U32B_AS(name) READ_AS(ulong,name,readU32B)

#define READ_STRING_AS(name,size) \
  String name; \
  READ_ASSERT(readString(name, size));

#endif

/*** End of inlined file: modfileprivate.h ***/

using namespace TagLib;
using namespace Mod;

class Mod::File::FilePrivate
{
public:
  FilePrivate(AudioProperties::ReadStyle propertiesStyle)
	: properties(propertiesStyle)
  {
  }

  Mod::Tag        tag;
  Mod::Properties properties;
};

Mod::File::File(FileName file, bool readProperties,
				AudioProperties::ReadStyle propertiesStyle) :
  Mod::FileBase(file),
  d(new FilePrivate(propertiesStyle))
{
  read(readProperties);
}

Mod::File::File(IOStream *stream, bool readProperties,
				AudioProperties::ReadStyle propertiesStyle) :
  Mod::FileBase(stream),
  d(new FilePrivate(propertiesStyle))
{
  read(readProperties);
}

Mod::File::~File()
{
  delete d;
}

Mod::Tag *Mod::File::tag() const
{
  return &d->tag;
}

Mod::Properties *Mod::File::audioProperties() const
{
  return &d->properties;
}

PropertyMap Mod::File::properties() const
{
  return d->tag.properties();
}

PropertyMap Mod::File::setProperties(const PropertyMap &properties)
{
  return d->tag.setProperties(properties);
}

bool Mod::File::save()
{
  if(readOnly()) {
	debug("Mod::File::save() - Cannot save to a read only file.");
	return false;
  }
  seek(0);
  writeString(d->tag.title(), 20);
  StringList lines = d->tag.comment().split("\n");
  uint n = std::min(lines.size(), d->properties.instrumentCount());
  for(uint i = 0; i < n; ++ i) {
	writeString(lines[i], 22);
	seek(8, Current);
  }

  for(uint i = n; i < d->properties.instrumentCount(); ++ i) {
	writeString(String::null, 22);
	seek(8, Current);
  }
  return true;
}

void Mod::File::read(bool)
{
  if(!isOpen())
	return;

  seek(1080);
  ByteVector modId = readBlock(4);
  READ_ASSERT(modId.size() == 4);

  int  channels    =  4;
  uint instruments = 31;
  if(modId == "M.K." || modId == "M!K!" || modId == "M&K!" || modId == "N.T.") {
	d->tag.setTrackerName("ProTracker");
	channels = 4;
  }
  else if(modId.startsWith("FLT") || modId.startsWith("TDZ")) {
	d->tag.setTrackerName("StarTrekker");
	char digit = modId[3];
	READ_ASSERT(digit >= '0' && digit <= '9');
	channels = digit - '0';
  }
  else if(modId.endsWith("CHN")) {
	d->tag.setTrackerName("StarTrekker");
	char digit = modId[0];
	READ_ASSERT(digit >= '0' && digit <= '9');
	channels = digit - '0';
  }
  else if(modId == "CD81" || modId == "OKTA") {
	d->tag.setTrackerName("Atari Oktalyzer");
	channels = 8;
  }
  else if(modId.endsWith("CH") || modId.endsWith("CN")) {
	d->tag.setTrackerName("TakeTracker");
	char digit = modId[0];
	READ_ASSERT(digit >= '0' && digit <= '9');
	channels = (digit - '0') * 10;
	digit = modId[1];
	READ_ASSERT(digit >= '0' && digit <= '9');
	channels += digit - '0';
  }
  else {
	// Not sure if this is correct. I'd need a file
	// created with NoiseTracker to check this.
	d->tag.setTrackerName("NoiseTracker"); // probably
	channels    =  4;
	instruments = 15;
  }
  d->properties.setChannels(channels);
  d->properties.setInstrumentCount(instruments);

  seek(0);
  READ_STRING(d->tag.setTitle, 20);

  StringList comment;
  for(uint i = 0; i < instruments; ++ i) {
	READ_STRING_AS(instrumentName, 22);
	// value in words, * 2 (<< 1) for bytes:
	READ_U16B_AS(sampleLength);

	READ_BYTE_AS(fineTuneByte);
	int fineTune = fineTuneByte & 0xF;
	// > 7 means negative value
	if(fineTune > 7) fineTune -= 16;

	READ_BYTE_AS(volume);
	if(volume > 64) volume = 64;
	// volume in decibels: 20 * log10(volume / 64)

	// value in words, * 2 (<< 1) for bytes:
	READ_U16B_AS(repeatStart);
	// value in words, * 2 (<< 1) for bytes:
	READ_U16B_AS(repatLength);

	comment.append(instrumentName);
  }

  READ_BYTE(d->properties.setLengthInPatterns);

  d->tag.setComment(comment.toString("\n"));
}

/*** End of inlined file: modfile.cpp ***/


/*** Start of inlined file: modtag.cpp ***/
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

using namespace TagLib;
using namespace Mod;

class Mod::Tag::TagPrivate
{
public:
  TagPrivate()
  {
  }

  String title;
  String comment;
  String trackerName;
};

Mod::Tag::Tag() : TagLib::Tag()
{
  d = new TagPrivate;
}

Mod::Tag::~Tag()
{
  delete d;
}

String Mod::Tag::title() const
{
  return d->title;
}

String Mod::Tag::artist() const
{
  return String::null;
}

String Mod::Tag::album() const
{
  return String::null;
}

String Mod::Tag::comment() const
{
  return d->comment;
}

String Mod::Tag::genre() const
{
  return String::null;
}

TagLib::uint Mod::Tag::year() const
{
  return 0;
}

TagLib::uint Mod::Tag::track() const
{
  return 0;
}

String Mod::Tag::trackerName() const
{
  return d->trackerName;
}

void Mod::Tag::setTitle(const String &title)
{
  d->title = title;
}

void Mod::Tag::setArtist(const String &)
{
}

void Mod::Tag::setAlbum(const String &)
{
}

void Mod::Tag::setComment(const String &comment)
{
  d->comment = comment;
}

void Mod::Tag::setGenre(const String &)
{
}

void Mod::Tag::setYear(uint)
{
}

void Mod::Tag::setTrack(uint)
{
}

void Mod::Tag::setTrackerName(const String &trackerName)
{
  d->trackerName = trackerName;
}

PropertyMap Mod::Tag::properties() const
{
  PropertyMap properties;
  properties["TITLE"] = d->title;
  properties["COMMENT"] = d->comment;
  if(!(d->trackerName.isNull()))
	properties["TRACKERNAME"] = d->trackerName;
  return properties;
}

PropertyMap Mod::Tag::setProperties(const PropertyMap &origProps)
{
  PropertyMap properties(origProps);
  properties.removeEmpty();
  StringList oneValueSet;
  if(properties.contains("TITLE")) {
	d->title = properties["TITLE"].front();
	oneValueSet.append("TITLE");
  } else
	d->title = String::null;

  if(properties.contains("COMMENT")) {
	d->comment = properties["COMMENT"].front();
	oneValueSet.append("COMMENT");
  } else
	d->comment = String::null;

  if(properties.contains("TRACKERNAME")) {
	d->trackerName = properties["TRACKERNAME"].front();
	oneValueSet.append("TRACKERNAME");
  } else
	d->trackerName = String::null;

  // for each tag that has been set above, remove the first entry in the corresponding
  // value list. The others will be returned as unsupported by this format.
  for(StringList::Iterator it = oneValueSet.begin(); it != oneValueSet.end(); ++it) {
	if(properties[*it].size() == 1)
	  properties.erase(*it);
	else
	  properties[*it].erase( properties[*it].begin() );
  }
  return properties;
}

/*** End of inlined file: modtag.cpp ***/


/*** Start of inlined file: modproperties.cpp ***/
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

using namespace TagLib;
using namespace Mod;

class Mod::Properties::PropertiesPrivate
{
public:
  PropertiesPrivate() :
	channels(0),
	instrumentCount(0),
	lengthInPatterns(0)
  {
  }

  int   channels;
  uint  instrumentCount;
  uchar lengthInPatterns;
};

Mod::Properties::Properties(AudioProperties::ReadStyle propertiesStyle) :
  AudioProperties(propertiesStyle),
  d(new PropertiesPrivate)
{
}

Mod::Properties::~Properties()
{
  delete d;
}

int Mod::Properties::length() const
{
  return 0;
}

int Mod::Properties::bitrate() const
{
  return 0;
}

int Mod::Properties::sampleRate() const
{
  return 0;
}

int Mod::Properties::channels() const
{
  return d->channels;
}

uint Mod::Properties::instrumentCount() const
{
  return d->instrumentCount;
}

uchar Mod::Properties::lengthInPatterns() const
{
  return d->lengthInPatterns;
}

void Mod::Properties::setChannels(int channels)
{
  d->channels = channels;
}

void Mod::Properties::setInstrumentCount(uint instrumentCount)
{
  d->instrumentCount = instrumentCount;
}

void Mod::Properties::setLengthInPatterns(uchar lengthInPatterns)
{
  d->lengthInPatterns = lengthInPatterns;
}

/*** End of inlined file: modproperties.cpp ***/


/*** Start of inlined file: s3mfile.cpp ***/
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

#include <iostream>

using namespace TagLib;
using namespace S3M;

class S3M::File::FilePrivate
{
public:
  FilePrivate(AudioProperties::ReadStyle propertiesStyle)
	: properties(propertiesStyle)
  {
  }

  Mod::Tag        tag;
  S3M::Properties properties;
};

S3M::File::File(FileName file, bool readProperties,
				AudioProperties::ReadStyle propertiesStyle) :
  Mod::FileBase(file),
  d(new FilePrivate(propertiesStyle))
{
  read(readProperties);
}

S3M::File::File(IOStream *stream, bool readProperties,
				AudioProperties::ReadStyle propertiesStyle) :
  Mod::FileBase(stream),
  d(new FilePrivate(propertiesStyle))
{
  read(readProperties);
}

S3M::File::~File()
{
  delete d;
}

Mod::Tag *S3M::File::tag() const
{
  return &d->tag;
}

PropertyMap S3M::File::properties() const
{
  return d->tag.properties();
}

PropertyMap S3M::File::setProperties(const PropertyMap &properties)
{
  return d->tag.setProperties(properties);
}

S3M::Properties *S3M::File::audioProperties() const
{
  return &d->properties;
}

bool S3M::File::save()
{
  if(readOnly()) {
	debug("S3M::File::save() - Cannot save to a read only file.");
	return false;
  }
  // note: if title starts with "Extended Module: "
  // the file would look like an .xm file
  seek(0);
  writeString(d->tag.title(), 27);
  // string terminating NUL is not optional:
  writeByte(0);

  seek(32);

  ushort length = 0;
  ushort sampleCount = 0;

  if(!readU16L(length) || !readU16L(sampleCount))
	return false;

  seek(28, Current);

  int channels = 0;
  for(int i = 0; i < 32; ++ i) {
	uchar setting = 0;
	if(!readByte(setting))
	  return false;
	// or if(setting >= 128)?
	// or channels = i + 1;?
	// need a better spec!
	if(setting != 0xff) ++ channels;
  }

  seek(channels, Current);

  StringList lines = d->tag.comment().split("\n");
  // write comment as sample names:
  for(ushort i = 0; i < sampleCount; ++ i) {
	seek(96L + length + ((long)i << 1));

	ushort instrumentOffset = 0;
	if(!readU16L(instrumentOffset))
	  return false;
	seek(((long)instrumentOffset << 4) + 48);

	if(i < lines.size())
	  writeString(lines[i], 27);
	else
	  writeString(String::null, 27);
	// string terminating NUL is not optional:
	writeByte(0);
  }
  return true;
}

void S3M::File::read(bool)
{
  if(!isOpen())
	return;

  READ_STRING(d->tag.setTitle, 28);
  READ_BYTE_AS(mark);
  READ_BYTE_AS(type);

  READ_ASSERT(mark == 0x1A && type == 0x10);

  seek(32);

  READ_U16L_AS(length);
  READ_U16L_AS(sampleCount);

  d->properties.setSampleCount(sampleCount);

  READ_U16L(d->properties.setPatternCount);
  READ_U16L(d->properties.setFlags);
  READ_U16L(d->properties.setTrackerVersion);
  READ_U16L(d->properties.setFileFormatVersion);

  READ_ASSERT(readBlock(4) == "SCRM");

  READ_BYTE(d->properties.setGlobalVolume);
  READ_BYTE(d->properties.setBpmSpeed);
  READ_BYTE(d->properties.setTempo);

  READ_BYTE_AS(masterVolume);
  d->properties.setMasterVolume(masterVolume & 0x7f);
  d->properties.setStereo((masterVolume & 0x80) != 0);

  // I've seen players who call the next two bytes
  // "ultra click" and "use panning values" (if == 0xFC).
  // I don't see them in any spec, though.
  // Hm, but there is "UltraClick-removal" and some other
  // variables in ScreamTracker IIIs GUI.

  seek(12, Current);

  int channels = 0;
  for(int i = 0; i < 32; ++ i) {
	READ_BYTE_AS(setting);
	// or if(setting >= 128)?
	// or channels = i + 1;?
	// need a better spec!
	if(setting != 0xff) ++ channels;
  }
  d->properties.setChannels(channels);

  seek(96);
  ushort realLength = 0;
  for(ushort i = 0; i < length; ++ i) {
	  READ_BYTE_AS(order);
	  if(order == 255) break;
	  if(order != 254) ++ realLength;
  }
  d->properties.setLengthInPatterns(realLength);

  seek(channels, Current);

  // Note: The S3M spec mentions samples and instruments, but in
  //       the header there are only pointers to instruments.
  //       However, there I never found instruments (SCRI) but
  //       instead samples (SCRS).
  StringList comment;
  for(ushort i = 0; i < sampleCount; ++ i) {
	seek(96L + length + ((long)i << 1));

	READ_U16L_AS(sampleHeaderOffset);
	seek((long)sampleHeaderOffset << 4);

	READ_BYTE_AS(sampleType);
	READ_STRING_AS(dosFileName, 13);
	READ_U16L_AS(sampleDataOffset);
	READ_U32L_AS(sampleLength);
	READ_U32L_AS(repeatStart);
	READ_U32L_AS(repeatStop);
	READ_BYTE_AS(sampleVolume);

	seek(1, Current);

	READ_BYTE_AS(packing);
	READ_BYTE_AS(sampleFlags);
	READ_U32L_AS(baseFrequency);

	seek(12, Current);

	READ_STRING_AS(sampleName, 28);
	// The next 4 bytes should be "SCRS", but I've found
	// files that are otherwise ok with 4 nils instead.
	// READ_ASSERT(readBlock(4) == "SCRS");

	comment.append(sampleName);
  }

  d->tag.setComment(comment.toString("\n"));
  d->tag.setTrackerName("ScreamTracker III");
}

/*** End of inlined file: s3mfile.cpp ***/


/*** Start of inlined file: s3mproperties.cpp ***/
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

using namespace TagLib;
using namespace S3M;

class S3M::Properties::PropertiesPrivate
{
public:
  PropertiesPrivate() :
	lengthInPatterns(0),
	channels(0),
	stereo(false),
	sampleCount(0),
	patternCount(0),
	flags(0),
	trackerVersion(0),
	fileFormatVersion(0),
	globalVolume(0),
	masterVolume(0),
	tempo(0),
	bpmSpeed(0)
  {
  }

  ushort lengthInPatterns;
  int    channels;
  bool   stereo;
  ushort sampleCount;
  ushort patternCount;
  ushort flags;
  ushort trackerVersion;
  ushort fileFormatVersion;
  uchar  globalVolume;
  uchar  masterVolume;
  uchar  tempo;
  uchar  bpmSpeed;
};

S3M::Properties::Properties(AudioProperties::ReadStyle propertiesStyle) :
  AudioProperties(propertiesStyle),
  d(new PropertiesPrivate)
{
}

S3M::Properties::~Properties()
{
  delete d;
}

int S3M::Properties::length() const
{
  return 0;
}

int S3M::Properties::bitrate() const
{
  return 0;
}

int S3M::Properties::sampleRate() const
{
  return 0;
}

int S3M::Properties::channels() const
{
  return d->channels;
}

ushort S3M::Properties::lengthInPatterns() const
{
  return d->lengthInPatterns;
}

bool S3M::Properties::stereo() const
{
  return d->stereo;
}

ushort S3M::Properties::sampleCount() const
{
  return d->sampleCount;
}

ushort S3M::Properties::patternCount() const
{
  return d->patternCount;
}

ushort S3M::Properties::flags() const
{
  return d->flags;
}

ushort S3M::Properties::trackerVersion() const
{
  return d->trackerVersion;
}

ushort S3M::Properties::fileFormatVersion() const
{
  return d->fileFormatVersion;
}

uchar S3M::Properties::globalVolume() const
{
  return d->globalVolume;
}

uchar S3M::Properties::masterVolume() const
{
  return d->masterVolume;
}

uchar S3M::Properties::tempo() const
{
  return d->tempo;
}

uchar S3M::Properties::bpmSpeed() const
{
  return d->bpmSpeed;
}

void S3M::Properties::setLengthInPatterns(ushort lengthInPatterns)
{
  d->lengthInPatterns = lengthInPatterns;
}

void S3M::Properties::setChannels(int channels)
{
  d->channels = channels;
}

void S3M::Properties::setStereo(bool stereo)
{
  d->stereo = stereo;
}

void S3M::Properties::setSampleCount(ushort sampleCount)
{
  d->sampleCount = sampleCount;
}

void S3M::Properties::setPatternCount(ushort patternCount)
{
  d->patternCount = patternCount;
}

void S3M::Properties::setFlags(ushort flags)
{
  d->flags = flags;
}

void S3M::Properties::setTrackerVersion(ushort trackerVersion)
{
  d->trackerVersion = trackerVersion;
}

void S3M::Properties::setFileFormatVersion(ushort fileFormatVersion)
{
  d->fileFormatVersion = fileFormatVersion;
}

void S3M::Properties::setGlobalVolume(uchar globalVolume)
{
  d->globalVolume = globalVolume;
}

void S3M::Properties::setMasterVolume(uchar masterVolume)
{
  d->masterVolume = masterVolume;
}

void S3M::Properties::setTempo(uchar tempo)
{
  d->tempo = tempo;
}

void S3M::Properties::setBpmSpeed(uchar bpmSpeed)
{
  d->bpmSpeed = bpmSpeed;
}

/*** End of inlined file: s3mproperties.cpp ***/


/*** Start of inlined file: itfile.cpp ***/
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

using namespace TagLib;
using namespace IT;

class IT::File::FilePrivate
{
public:
  FilePrivate(AudioProperties::ReadStyle propertiesStyle)
	: tag(), properties(propertiesStyle)
  {
  }

  Mod::Tag       tag;
  IT::Properties properties;
};

IT::File::File(FileName file, bool readProperties,
			   AudioProperties::ReadStyle propertiesStyle) :
  Mod::FileBase(file),
  d(new FilePrivate(propertiesStyle))
{
  read(readProperties);
}

IT::File::File(IOStream *stream, bool readProperties,
			   AudioProperties::ReadStyle propertiesStyle) :
  Mod::FileBase(stream),
  d(new FilePrivate(propertiesStyle))
{
  read(readProperties);
}

IT::File::~File()
{
  delete d;
}

Mod::Tag *IT::File::tag() const
{
  return &d->tag;
}

PropertyMap IT::File::properties() const
{
  return d->tag.properties();
}

PropertyMap IT::File::setProperties(const PropertyMap &properties)
{
  return d->tag.setProperties(properties);
}

IT::Properties *IT::File::audioProperties() const
{
  return &d->properties;
}

bool IT::File::save()
{
  if(readOnly())
  {
	debug("IT::File::save() - Cannot save to a read only file.");
	return false;
  }
  seek(4);
  writeString(d->tag.title(), 25);
  writeByte(0);

  seek(2, Current);

  ushort length = 0;
  ushort instrumentCount = 0;
  ushort sampleCount = 0;

  if(!readU16L(length) || !readU16L(instrumentCount) || !readU16L(sampleCount))
	return false;

  seek(15, Current);

  // write comment as instrument and sample names:
  StringList lines = d->tag.comment().split("\n");
  for(ushort i = 0; i < instrumentCount; ++ i) {
	seek(192L + length + ((long)i << 2));
	ulong instrumentOffset = 0;
	if(!readU32L(instrumentOffset))
	  return false;

	seek(instrumentOffset + 32);

	if(i < lines.size())
	  writeString(lines[i], 25);
	else
	  writeString(String::null, 25);
	writeByte(0);
  }

  for(ushort i = 0; i < sampleCount; ++ i) {
	seek(192L + length + ((long)instrumentCount << 2) + ((long)i << 2));
	ulong sampleOffset = 0;
	if(!readU32L(sampleOffset))
	  return false;

	seek(sampleOffset + 20);

	if((i + instrumentCount) < lines.size())
	  writeString(lines[i + instrumentCount], 25);
	else
	  writeString(String::null, 25);
	writeByte(0);
  }

  // write rest as message:
  StringList messageLines;
  for(uint i = instrumentCount + sampleCount; i < lines.size(); ++ i)
	messageLines.append(lines[i]);
  ByteVector message = messageLines.toString("\r").data(String::Latin1);

  // it's actually not really stated if the message needs a
  // terminating NUL but it does not hurt to add one:
  if(message.size() > 7999)
	message.resize(7999);
  message.append((char)0);

  ushort special = 0;
  ushort messageLength = 0;
  ulong  messageOffset = 0;

  seek(46);
  if(!readU16L(special))
	return false;

  ulong fileSize = File::length();
  if(special & Properties::MessageAttached) {
	seek(54);
	if(!readU16L(messageLength) || !readU32L(messageOffset))
	  return false;

	if(messageLength == 0)
	  messageOffset = fileSize;
  }
  else
  {
	messageOffset = fileSize;
	seek(46);
	writeU16L(special | 0x1);
  }

  if(messageOffset + messageLength >= fileSize) {
	// append new message
	seek(54);
	writeU16L(static_cast<ushort>(message.size()));
	writeU32L(messageOffset);
	seek(messageOffset);
	writeBlock(message);
	truncate(messageOffset + message.size());
  }
  else {
	// Only overwrite existing message.
	// I'd need to parse (understand!) the whole file for more.
	// Although I could just move the message to the end of file
	// and let the existing one be, but that would waste space.
	message.resize(messageLength, 0);
	seek(messageOffset);
	writeBlock(message);
  }
  return true;
}

void IT::File::read(bool)
{
  if(!isOpen())
	return;

  seek(0);
  READ_ASSERT(readBlock(4) == "IMPM");
  READ_STRING(d->tag.setTitle, 26);

  seek(2, Current);

  READ_U16L_AS(length);
  READ_U16L_AS(instrumentCount);
  READ_U16L_AS(sampleCount);

  d->properties.setInstrumentCount(instrumentCount);
  d->properties.setSampleCount(sampleCount);
  READ_U16L(d->properties.setPatternCount);
  READ_U16L(d->properties.setVersion);
  READ_U16L(d->properties.setCompatibleVersion);
  READ_U16L(d->properties.setFlags);
  READ_U16L_AS(special);
  d->properties.setSpecial(special);
  READ_BYTE(d->properties.setGlobalVolume);
  READ_BYTE(d->properties.setMixVolume);
  READ_BYTE(d->properties.setBpmSpeed);
  READ_BYTE(d->properties.setTempo);
  READ_BYTE(d->properties.setPanningSeparation);
  READ_BYTE(d->properties.setPitchWheelDepth);

  // IT supports some kind of comment tag. Still, the
  // sample/instrument names are abused as comments so
  // I just add all together.
  String message;
  if(special & Properties::MessageAttached) {
	READ_U16L_AS(messageLength);
	READ_U32L_AS(messageOffset);
	seek(messageOffset);
	ByteVector messageBytes = readBlock(messageLength);
	READ_ASSERT(messageBytes.size() == messageLength);
	int index = messageBytes.find((char) 0);
	if(index > -1)
	  messageBytes.resize(index, 0);
	messageBytes.replace('\r', '\n');
	message = messageBytes;
  }

  seek(64);

  ByteVector pannings = readBlock(64);
  ByteVector volumes  = readBlock(64);
  READ_ASSERT(pannings.size() == 64 && volumes.size() == 64);
  int channels = 0;
  for(int i = 0; i < 64; ++ i) {
	// Strictly speaking an IT file has always 64 channels, but
	// I don't count disabled and muted channels.
	// But this always gives 64 channels for all my files anyway.
	// Strangely VLC does report other values. I wonder how VLC
	// gets it's values.
	if((unsigned char) pannings[i] < 128 && volumes[i] > 0)
		++channels;
  }
  d->properties.setChannels(channels);

  // real length might be shorter because of skips and terminator
  ushort realLength = 0;
  for(ushort i = 0; i < length; ++ i) {
	READ_BYTE_AS(order);
	if(order == 255) break;
	if(order != 254) ++ realLength;
  }
  d->properties.setLengthInPatterns(realLength);

  StringList comment;
  // Note: I found files that have nil characters somewhere
  //       in the instrument/sample names and more characters
  //       afterwards. The spec does not mention such a case.
  //       Currently I just discard anything after a nil, but
  //       e.g. VLC seems to interprete a nil as a space. I
  //       don't know what is the proper behaviour.
  for(ushort i = 0; i < instrumentCount; ++ i) {
	seek(192L + length + ((long)i << 2));
	READ_U32L_AS(instrumentOffset);
	seek(instrumentOffset);

	ByteVector instrumentMagic = readBlock(4);
	READ_ASSERT(instrumentMagic == "IMPI");

	READ_STRING_AS(dosFileName, 13);

	seek(15, Current);

	READ_STRING_AS(instrumentName, 26);
	comment.append(instrumentName);
  }

  for(ushort i = 0; i < sampleCount; ++ i) {
	seek(192L + length + ((long)instrumentCount << 2) + ((long)i << 2));
	READ_U32L_AS(sampleOffset);

	seek(sampleOffset);

	ByteVector sampleMagic = readBlock(4);
	READ_ASSERT(sampleMagic == "IMPS");

	READ_STRING_AS(dosFileName, 13);
	READ_BYTE_AS(globalVolume);
	READ_BYTE_AS(sampleFlags);
	READ_BYTE_AS(sampleVolume);
	READ_STRING_AS(sampleName, 26);
	/*
	READ_BYTE_AS(sampleCvt);
	READ_BYTE_AS(samplePanning);
	READ_U32L_AS(sampleLength);
	READ_U32L_AS(loopStart);
	READ_U32L_AS(loopStop);
	READ_U32L_AS(c5speed);
	READ_U32L_AS(sustainLoopStart);
	READ_U32L_AS(sustainLoopEnd);
	READ_U32L_AS(sampleDataOffset);
	READ_BYTE_AS(vibratoSpeed);
	READ_BYTE_AS(vibratoDepth);
	READ_BYTE_AS(vibratoRate);
	READ_BYTE_AS(vibratoType);
	*/

	comment.append(sampleName);
  }

  if(message.size() > 0)
	comment.append(message);
  d->tag.setComment(comment.toString("\n"));
  d->tag.setTrackerName("Impulse Tracker");
}

/*** End of inlined file: itfile.cpp ***/


/*** Start of inlined file: itproperties.cpp ***/
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

using namespace TagLib;
using namespace IT;

class IT::Properties::PropertiesPrivate
{
public:
  PropertiesPrivate() :
	channels(0),
	lengthInPatterns(0),
	instrumentCount(0),
	sampleCount(0),
	patternCount(0),
	version(0),
	compatibleVersion(0),
	flags(0),
	special(0),
	globalVolume(0),
	mixVolume(0),
	tempo(0),
	bpmSpeed(0),
	panningSeparation(0),
	pitchWheelDepth(0)
  {
  }

  int    channels;
  ushort lengthInPatterns;
  ushort instrumentCount;
  ushort sampleCount;
  ushort patternCount;
  ushort version;
  ushort compatibleVersion;
  ushort flags;
  ushort special;
  uchar  globalVolume;
  uchar  mixVolume;
  uchar  tempo;
  uchar  bpmSpeed;
  uchar  panningSeparation;
  uchar  pitchWheelDepth;
};

IT::Properties::Properties(AudioProperties::ReadStyle propertiesStyle) :
  AudioProperties(propertiesStyle),
  d(new PropertiesPrivate)
{
}

IT::Properties::~Properties()
{
  delete d;
}

int IT::Properties::length() const
{
  return 0;
}

int IT::Properties::bitrate() const
{
  return 0;
}

int IT::Properties::sampleRate() const
{
  return 0;
}

int IT::Properties::channels() const
{
  return d->channels;
}

ushort IT::Properties::lengthInPatterns() const
{
  return d->lengthInPatterns;
}

bool IT::Properties::stereo() const
{
  return d->flags & Stereo;
}

ushort IT::Properties::instrumentCount() const
{
  return d->instrumentCount;
}

ushort IT::Properties::sampleCount() const
{
  return d->sampleCount;
}

ushort IT::Properties::patternCount() const
{
  return d->patternCount;
}

ushort IT::Properties::version() const
{
  return d->version;
}

ushort IT::Properties::compatibleVersion() const
{
  return d->compatibleVersion;
}

ushort IT::Properties::flags() const
{
  return d->flags;
}

ushort IT::Properties::special() const
{
  return d->special;
}

uchar IT::Properties::globalVolume() const
{
  return d->globalVolume;
}

uchar IT::Properties::mixVolume() const
{
  return d->mixVolume;
}

uchar IT::Properties::tempo() const
{
  return d->tempo;
}

uchar IT::Properties::bpmSpeed() const
{
  return d->bpmSpeed;
}

uchar IT::Properties::panningSeparation() const
{
  return d->panningSeparation;
}

uchar IT::Properties::pitchWheelDepth() const
{
  return d->pitchWheelDepth;
}

void IT::Properties::setChannels(int channels)
{
  d->channels = channels;
}

void IT::Properties::setLengthInPatterns(ushort lengthInPatterns)
{
  d->lengthInPatterns = lengthInPatterns;
}

void IT::Properties::setInstrumentCount(ushort instrumentCount)
{
  d->instrumentCount = instrumentCount;
}

void IT::Properties::setSampleCount(ushort sampleCount)
{
  d->sampleCount = sampleCount;
}

void IT::Properties::setPatternCount(ushort patternCount)
{
  d->patternCount = patternCount;
}

void IT::Properties::setFlags(ushort flags)
{
  d->flags = flags;
}

void IT::Properties::setSpecial(ushort special)
{
  d->special = special;
}

void IT::Properties::setCompatibleVersion(ushort compatibleVersion)
{
  d->compatibleVersion = compatibleVersion;
}

void IT::Properties::setVersion(ushort version)
{
  d->version = version;
}

void IT::Properties::setGlobalVolume(uchar globalVolume)
{
  d->globalVolume = globalVolume;
}

void IT::Properties::setMixVolume(uchar mixVolume)
{
  d->mixVolume = mixVolume;
}

void IT::Properties::setTempo(uchar tempo)
{
  d->tempo = tempo;
}

void IT::Properties::setBpmSpeed(uchar bpmSpeed)
{
  d->bpmSpeed = bpmSpeed;
}

void IT::Properties::setPanningSeparation(uchar panningSeparation)
{
  d->panningSeparation = panningSeparation;
}

void IT::Properties::setPitchWheelDepth(uchar pitchWheelDepth)
{
  d->pitchWheelDepth = pitchWheelDepth;
}

/*** End of inlined file: itproperties.cpp ***/


/*** Start of inlined file: xmfile.cpp ***/
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

#include <string.h>
#include <algorithm>

using namespace TagLib;
using namespace XM;
using TagLib::uint;
using TagLib::ushort;
using TagLib::ulong;

/*!
 * The Reader classes are helpers to make handling of the stripped XM
 * format more easy. In the stripped XM format certain header sizes might
 * be smaller than one would expect. The fields that are not included
 * are then just some predefined valued (e.g. 0).
 *
 * Using these classes this code:
 *
 *   if(headerSize >= 4) {
 *     if(!readU16L(value1)) ERROR();
 *     if(headerSize >= 8) {
 *       if(!readU16L(value2)) ERROR();
 *       if(headerSize >= 12) {
 *         if(!readString(value3, 22)) ERROR();
 *         ...
 *       }
 *     }
 *   }
 *
 * Becomes:
 *
 *   StructReader header;
 *   header.u16L(value1).u16L(value2).string(value3, 22). ...;
 *   if(header.read(*this, headerSize) < std::min(header.size(), headerSize))
 *     ERROR();
 *
 * Maybe if this is useful to other formats these classes can be moved to
 * their own public files.
 */
class Reader
{
public:
  virtual ~Reader()
  {
  }

  /*!
   * Reads associated values from \a file, but never reads more
   * then \a limit bytes.
   */
  virtual uint read(TagLib::File &file, uint limit) = 0;

  /*!
   * Returns the number of bytes this reader would like to read.
   */
  virtual uint size() const = 0;
};

class SkipReader : public Reader
{
public:
  SkipReader(uint size) : m_size(size)
  {
  }

  uint read(TagLib::File &file, uint limit)
  {
	uint count = std::min(m_size, limit);
	file.seek(count, TagLib::File::Current);
	return count;
  }

  uint size() const
  {
	return m_size;
  }

private:
  uint m_size;
};

template<typename T>
class ValueReader : public Reader
{
public:
  ValueReader(T &value) : value(value)
  {
  }

protected:
  ValueReader &operator=(const ValueReader &);
  T &value;
};

class StringReader : public ValueReader<String>
{
public:
  StringReader(String &string, uint size) :
	ValueReader<String>(string), m_size(size)
  {
  }

  uint read(TagLib::File &file, uint limit)
  {
	ByteVector data = file.readBlock(std::min(m_size, limit));
	uint count = data.size();
	int index = data.find((char) 0);
	if(index > -1) {
	  data.resize(index);
	}
	data.replace((char) 0xff, ' ');
	value = data;
	return count;
  }

  uint size() const
  {
	return m_size;
  }

private:
  uint m_size;
};

class ByteReader : public ValueReader<uchar>
{
public:
  ByteReader(uchar &byte) : ValueReader<uchar>(byte) {}

  uint read(TagLib::File &file, uint limit)
  {
	ByteVector data = file.readBlock(std::min(1U,limit));
	if(data.size() > 0) {
	  value = data[0];
	}
	return data.size();
  }

  uint size() const
  {
	return 1;
  }
};

template<typename T>
class NumberReader : public ValueReader<T>
{
public:
  NumberReader(T &value, bool bigEndian) :
	ValueReader<T>(value), bigEndian(bigEndian)
  {
  }

protected:
  bool bigEndian;
};

class U16Reader : public NumberReader<ushort>
{
public:
  U16Reader(ushort &value, bool bigEndian)
  : NumberReader<ushort>(value, bigEndian) {}

  uint read(TagLib::File &file, uint limit)
  {
	ByteVector data = file.readBlock(std::min(2U,limit));
	value = data.toUShort(bigEndian);
	return data.size();
  }

  uint size() const
  {
	return 2;
  }
};

class U32Reader : public NumberReader<ulong>
{
public:
  U32Reader(ulong &value, bool bigEndian = true) :
	NumberReader<ulong>(value, bigEndian)
  {
  }

  uint read(TagLib::File &file, uint limit)
  {
	ByteVector data = file.readBlock(std::min(4U,limit));
	value = data.toUInt(bigEndian);
	return data.size();
  }

  uint size() const
  {
	return 4;
  }
};

class StructReader : public Reader
{
public:
  StructReader()
  {
	m_readers.setAutoDelete(true);
  }

  /*!
   * Add a nested reader. This reader takes ownership.
   */
  StructReader &reader(Reader *reader)
  {
	m_readers.append(reader);
	return *this;
  }

  /*!
   * Don't read anything but skip \a size bytes.
   */
  StructReader &skip(uint size)
  {
	m_readers.append(new SkipReader(size));
	return *this;
  }

  /*!
   * Read a string of \a size characters (bytes) into \a string.
   */
  StructReader &string(String &string, uint size)
  {
	m_readers.append(new StringReader(string, size));
	return *this;
  }

  /*!
   * Read a byte into \a byte.
   */
  StructReader &byte(uchar &byte)
  {
	m_readers.append(new ByteReader(byte));
	return *this;
  }

  /*!
   * Read a unsigned 16 Bit integer into \a number. The byte order
   * is controlled by \a bigEndian.
   */
  StructReader &u16(ushort &number, bool bigEndian)
  {
	m_readers.append(new U16Reader(number, bigEndian));
	return *this;
  }

  /*!
   * Read a unsigned 16 Bit little endian integer into \a number.
   */
  StructReader &u16L(ushort &number)
  {
	return u16(number, false);
  }

  /*!
   * Read a unsigned 16 Bit big endian integer into \a number.
   */
  StructReader &u16B(ushort &number)
  {
	return u16(number, true);
  }

  /*!
   * Read a unsigned 32 Bit integer into \a number. The byte order
   * is controlled by \a bigEndian.
   */
  StructReader &u32(ulong &number, bool bigEndian)
  {
	m_readers.append(new U32Reader(number, bigEndian));
	return *this;
  }

  /*!
   * Read a unsigned 32 Bit little endian integer into \a number.
   */
  StructReader &u32L(ulong &number)
  {
	return u32(number, false);
  }

  /*!
   * Read a unsigned 32 Bit big endian integer into \a number.
   */
  StructReader &u32B(ulong &number)
  {
	return u32(number, true);
  }

  uint size() const
  {
	uint size = 0;
	for(List<Reader*>::ConstIterator i = m_readers.begin();
		i != m_readers.end(); ++ i) {
	  size += (*i)->size();
	}
	return size;
  }

  uint read(TagLib::File &file, uint limit)
  {
	uint sumcount = 0;
	for(List<Reader*>::Iterator i = m_readers.begin();
		limit > 0 && i != m_readers.end(); ++ i) {
	  uint count = (*i)->read(file, limit);
	  limit    -= count;
	  sumcount += count;
	}
	return sumcount;
  }

private:
  List<Reader*> m_readers;
};

class XM::File::FilePrivate
{
public:
  FilePrivate(AudioProperties::ReadStyle propertiesStyle)
	: tag(), properties(propertiesStyle)
  {
  }

  Mod::Tag       tag;
  XM::Properties properties;
};

XM::File::File(FileName file, bool readProperties,
			   AudioProperties::ReadStyle propertiesStyle) :
  Mod::FileBase(file),
  d(new FilePrivate(propertiesStyle))
{
  read(readProperties);
}

XM::File::File(IOStream *stream, bool readProperties,
			   AudioProperties::ReadStyle propertiesStyle) :
  Mod::FileBase(stream),
  d(new FilePrivate(propertiesStyle))
{
  read(readProperties);
}

XM::File::~File()
{
  delete d;
}

Mod::Tag *XM::File::tag() const
{
  return &d->tag;
}

PropertyMap XM::File::properties() const
{
  return d->tag.properties();
}

PropertyMap XM::File::setProperties(const PropertyMap &properties)
{
  return d->tag.setProperties(properties);
}

XM::Properties *XM::File::audioProperties() const
{
  return &d->properties;
}

bool XM::File::save()
{
  if(readOnly()) {
	debug("XM::File::save() - Cannot save to a read only file.");
	return false;
  }
  seek(17);
  writeString(d->tag.title(), 20);
  seek(1, Current);
  writeString(d->tag.trackerName(), 20);
  seek(2, Current);
  ulong headerSize = 0;
  if(!readU32L(headerSize))
	return false;
  seek(2+2+2, Current);

  ushort patternCount = 0;
  ushort instrumentCount = 0;
  if(!readU16L(patternCount) || !readU16L(instrumentCount))
	return false;

  seek(60 + headerSize);

  // need to read patterns again in order to seek to the instruments:
  for(ushort i = 0; i < patternCount; ++ i) {
	ulong patternHeaderLength = 0;
	if(!readU32L(patternHeaderLength) || patternHeaderLength < 4)
	  return false;

	ushort dataSize = 0;
	StructReader pattern;
	pattern.skip(3).u16L(dataSize);

	uint count = pattern.read(*this, patternHeaderLength - 4U);
	if(count != std::min(patternHeaderLength - 4U, (ulong)pattern.size()))
	  return false;

	seek(patternHeaderLength - (4 + count) + dataSize, Current);
  }

  StringList lines = d->tag.comment().split("\n");
  uint sampleNameIndex = instrumentCount;
  for(ushort i = 0; i < instrumentCount; ++ i) {
	ulong instrumentHeaderSize = 0;
	if(!readU32L(instrumentHeaderSize) || instrumentHeaderSize < 4)
	  return false;

	uint len = std::min(22UL, instrumentHeaderSize - 4U);
	if(i > lines.size())
	  writeString(String::null, len);
	else
	  writeString(lines[i], len);

	long offset = 0;
	if(instrumentHeaderSize >= 29U) {
	  ushort sampleCount = 0;
	  seek(1, Current);
	  if(!readU16L(sampleCount))
		return false;

	  if(sampleCount > 0) {
		ulong sampleHeaderSize = 0;
		if(instrumentHeaderSize < 33U || !readU32L(sampleHeaderSize))
		  return false;
		// skip unhandeled header proportion:
		seek(instrumentHeaderSize - 33, Current);

		for(ushort j = 0; j < sampleCount; ++ j) {
		  if(sampleHeaderSize > 4U) {
			ulong sampleLength = 0;
			if(!readU32L(sampleLength))
			  return false;
			offset += sampleLength;

			seek(std::min(sampleHeaderSize, 14UL), Current);
			if(sampleHeaderSize > 18U) {
			  uint len = std::min(sampleHeaderSize - 18U, 22UL);
			  if(sampleNameIndex >= lines.size())
				writeString(String::null, len);
			  else
				writeString(lines[sampleNameIndex ++], len);
			  seek(sampleHeaderSize - (18U + len), Current);
			}
		  }
		  else {
			seek(sampleHeaderSize, Current);
		  }
		}
	  }
	  else {
		offset = instrumentHeaderSize - 29;
	  }
	}
	else {
	  offset = instrumentHeaderSize - (4 + len);
	}
	seek(offset, Current);
  }

  return true;
}

void XM::File::read(bool)
{
  if(!isOpen())
	return;

  seek(0);
  ByteVector magic = readBlock(17);
  // it's all 0x00 for stripped XM files:
  READ_ASSERT(magic == "Extended Module: " || magic == ByteVector(17, 0));

  READ_STRING(d->tag.setTitle, 20);
  READ_BYTE_AS(escape);
  // in stripped XM files this is 0x00:
  READ_ASSERT(escape == 0x1A || escape == 0x00);

  READ_STRING(d->tag.setTrackerName, 20);
  READ_U16L(d->properties.setVersion);

  READ_U32L_AS(headerSize);
  READ_ASSERT(headerSize >= 4);

  ushort length          = 0;
  ushort restartPosition = 0;
  ushort channels        = 0;
  ushort patternCount    = 0;
  ushort instrumentCount = 0;
  ushort flags    = 0;
  ushort tempo    = 0;
  ushort bpmSpeed = 0;

  StructReader header;
  header.u16L(length)
		.u16L(restartPosition)
		.u16L(channels)
		.u16L(patternCount)
		.u16L(instrumentCount)
		.u16L(flags)
		.u16L(tempo)
		.u16L(bpmSpeed);

  uint count = header.read(*this, headerSize - 4U);
  uint size = std::min(headerSize - 4U, (ulong)header.size());

  READ_ASSERT(count == size);

  d->properties.setLengthInPatterns(length);
  d->properties.setRestartPosition(restartPosition);
  d->properties.setChannels(channels);
  d->properties.setPatternCount(patternCount);
  d->properties.setInstrumentCount(instrumentCount);
  d->properties.setFlags(flags);
  d->properties.setTempo(tempo);
  d->properties.setBpmSpeed(bpmSpeed);

  seek(60 + headerSize);

  // read patterns:
  for(ushort i = 0; i < patternCount; ++ i) {
	READ_U32L_AS(patternHeaderLength);
	READ_ASSERT(patternHeaderLength >= 4);

	uchar  packingType = 0;
	ushort rowCount = 0;
	ushort dataSize = 0;
	StructReader pattern;
	pattern.byte(packingType).u16L(rowCount).u16L(dataSize);

	uint count = pattern.read(*this, patternHeaderLength - 4U);
	READ_ASSERT(count == std::min(patternHeaderLength - 4U, (ulong)pattern.size()));

	seek(patternHeaderLength - (4 + count) + dataSize, Current);
  }

  StringList intrumentNames;
  StringList sampleNames;
  uint sumSampleCount = 0;

  // read instruments:
  for(ushort i = 0; i < instrumentCount; ++ i) {
	READ_U32L_AS(instrumentHeaderSize);
	READ_ASSERT(instrumentHeaderSize >= 4);

	String instrumentName;
	uchar  instrumentType = 0;
	ushort sampleCount = 0;

	StructReader instrument;
	instrument.string(instrumentName, 22).byte(instrumentType).u16L(sampleCount);

	// 4 for instrumentHeaderSize
	uint count = 4 + instrument.read(*this, instrumentHeaderSize - 4U);
	READ_ASSERT(count == std::min(instrumentHeaderSize, (ulong)instrument.size() + 4));

	ulong sampleHeaderSize = 0;
	long offset = 0;
	if(sampleCount > 0) {
	  sumSampleCount += sampleCount;
	  // wouldn't know which header size to assume otherwise:
	  READ_ASSERT(instrumentHeaderSize >= count + 4 && readU32L(sampleHeaderSize));
	  // skip unhandeled header proportion:
	  seek(instrumentHeaderSize - count - 4, Current);

	  for(ushort j = 0; j < sampleCount; ++ j) {
		ulong sampleLength = 0;
		ulong loopStart    = 0;
		ulong loopLength   = 0;
		uchar volume       = 0;
		uchar finetune     = 0;
		uchar sampleType   = 0;
		uchar panning      = 0;
		uchar noteNumber   = 0;
		uchar compression  = 0;
		String sampleName;
		StructReader sample;
		sample.u32L(sampleLength)
			  .u32L(loopStart)
			  .u32L(loopLength)
			  .byte(volume)
			  .byte(finetune)
			  .byte(sampleType)
			  .byte(panning)
			  .byte(noteNumber)
			  .byte(compression)
			  .string(sampleName, 22);

		uint count = sample.read(*this, sampleHeaderSize);
		READ_ASSERT(count == std::min(sampleHeaderSize, (ulong)sample.size()));
		// skip unhandeled header proportion:
		seek(sampleHeaderSize - count, Current);

		offset += sampleLength;
		sampleNames.append(sampleName);
	  }
	}
	else {
	  offset = instrumentHeaderSize - count;
	}
	intrumentNames.append(instrumentName);
	seek(offset, Current);
  }

  d->properties.setSampleCount(sumSampleCount);
  String comment(intrumentNames.toString("\n"));
  if(sampleNames.size() > 0) {
	comment += "\n";
	comment += sampleNames.toString("\n");
  }
  d->tag.setComment(comment);
}

/*** End of inlined file: xmfile.cpp ***/


/*** Start of inlined file: xmproperties.cpp ***/
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

using namespace TagLib;
using namespace XM;

class XM::Properties::PropertiesPrivate
{
public:
  PropertiesPrivate() :
	lengthInPatterns(0),
	channels(0),
	version(0),
	restartPosition(0),
	patternCount(0),
	instrumentCount(0),
	sampleCount(0),
	flags(0),
	tempo(0),
	bpmSpeed(0)
  {
  }

  ushort lengthInPatterns;
  int    channels;
  ushort version;
  ushort restartPosition;
  ushort patternCount;
  ushort instrumentCount;
  uint   sampleCount;
  ushort flags;
  ushort tempo;
  ushort bpmSpeed;
};

XM::Properties::Properties(AudioProperties::ReadStyle propertiesStyle) :
  AudioProperties(propertiesStyle),
  d(new PropertiesPrivate)
{
}

XM::Properties::~Properties()
{
  delete d;
}

int XM::Properties::length() const
{
  return 0;
}

int XM::Properties::bitrate() const
{
  return 0;
}

int XM::Properties::sampleRate() const
{
  return 0;
}

int XM::Properties::channels() const
{
  return d->channels;
}

ushort XM::Properties::lengthInPatterns() const
{
  return d->lengthInPatterns;
}

ushort XM::Properties::version() const
{
  return d->version;
}

ushort XM::Properties::restartPosition() const
{
  return d->restartPosition;
}

ushort XM::Properties::patternCount() const
{
  return d->patternCount;
}

ushort XM::Properties::instrumentCount() const
{
  return d->instrumentCount;
}

uint XM::Properties::sampleCount() const
{
  return d->sampleCount;
}

ushort XM::Properties::flags() const
{
  return d->flags;
}

ushort XM::Properties::tempo() const
{
  return d->tempo;
}

ushort XM::Properties::bpmSpeed() const
{
  return d->bpmSpeed;
}

void XM::Properties::setLengthInPatterns(ushort lengthInPatterns)
{
  d->lengthInPatterns = lengthInPatterns;
}

void XM::Properties::setChannels(int channels)
{
  d->channels = channels;
}

void XM::Properties::setVersion(ushort version)
{
  d->version = version;
}

void XM::Properties::setRestartPosition(ushort restartPosition)
{
  d->restartPosition = restartPosition;
}

void XM::Properties::setPatternCount(ushort patternCount)
{
  d->patternCount = patternCount;
}

void XM::Properties::setInstrumentCount(ushort instrumentCount)
{
  d->instrumentCount = instrumentCount;
}

void XM::Properties::setSampleCount(uint sampleCount)
{
  d->sampleCount = sampleCount;
}

void XM::Properties::setFlags(ushort flags)
{
  d->flags = flags;
}

void XM::Properties::setTempo(ushort tempo)
{
  d->tempo = tempo;
}

void XM::Properties::setBpmSpeed(ushort bpmSpeed)
{
  d->bpmSpeed = bpmSpeed;
}

/*** End of inlined file: xmproperties.cpp ***/


/*** Start of inlined file: tstringlist.cpp ***/
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

using namespace TagLib;

class StringListPrivate
{

};

////////////////////////////////////////////////////////////////////////////////
// static members
////////////////////////////////////////////////////////////////////////////////

StringList StringList::split(const String &s, const String &pattern)
{
  StringList l;

  int previousOffset = 0;
  for(int offset = s.find(pattern); offset != -1; offset = s.find(pattern, offset + 1)) {
	l.append(s.substr(previousOffset, offset - previousOffset));
	previousOffset = offset + 1;
  }

  l.append(s.substr(previousOffset, s.size() - previousOffset));

  return l;
}

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

StringList::StringList() : List<String>()
{

}

StringList::StringList(const StringList &l) : List<String>(l)
{

}

StringList::StringList(const String &s) : List<String>()
{
  append(s);
}

StringList::StringList(const ByteVectorList &bl, String::Type t) : List<String>()
{
  ByteVectorList::ConstIterator i = bl.begin();
  for(;i != bl.end(); i++) {
	append(String(*i, t));
  }
}

StringList::~StringList()
{

}

String StringList::toString(const String &separator) const
{
  String s;

  ConstIterator it = begin();
  ConstIterator itEnd = end();

  while(it != itEnd) {
	s += *it;
	it++;
	if(it != itEnd)
	  s += separator;
  }

  return s;
}

StringList &StringList::append(const String &s)
{
  List<String>::append(s);
  return *this;
}

StringList &StringList::append(const StringList &l)
{
  List<String>::append(l);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// related functions
////////////////////////////////////////////////////////////////////////////////

std::ostream &operator<<(std::ostream &s, const StringList &l)
{
  s << l.toString();
  return s;
}

/*** End of inlined file: tstringlist.cpp ***/


/*** Start of inlined file: tbytevector.cpp ***/
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

#include <iostream>

#include <string.h>

// This is a bit ugly to keep writing over and over again.

// A rather obscure feature of the C++ spec that I hadn't thought of that makes
// working with C libs much more effecient.  There's more here:
//
// http://www.informit.com/isapi/product_id~{9C84DAB4-FE6E-49C5-BB0A-FB50331233EA}/content/index.asp

#define DATA(x) (&(x->data[0]))

namespace TagLib {
  static const char hexTable[17] = "0123456789abcdef";

  static const uint crcTable[256] = {
	0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9, 0x130476dc, 0x17c56b6b,
	0x1a864db2, 0x1e475005, 0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61,
	0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd, 0x4c11db70, 0x48d0c6c7,
	0x4593e01e, 0x4152fda9, 0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,
	0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011, 0x791d4014, 0x7ddc5da3,
	0x709f7b7a, 0x745e66cd, 0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039,
	0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5, 0xbe2b5b58, 0xbaea46ef,
	0xb7a96036, 0xb3687d81, 0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
	0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49, 0xc7361b4c, 0xc3f706fb,
	0xceb42022, 0xca753d95, 0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1,
	0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d, 0x34867077, 0x30476dc0,
	0x3d044b19, 0x39c556ae, 0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,
	0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16, 0x018aeb13, 0x054bf6a4,
	0x0808d07d, 0x0cc9cdca, 0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde,
	0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02, 0x5e9f46bf, 0x5a5e5b08,
	0x571d7dd1, 0x53dc6066, 0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
	0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e, 0xbfa1b04b, 0xbb60adfc,
	0xb6238b25, 0xb2e29692, 0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6,
	0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a, 0xe0b41de7, 0xe4750050,
	0xe9362689, 0xedf73b3e, 0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
	0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686, 0xd5b88683, 0xd1799b34,
	0xdc3abded, 0xd8fba05a, 0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637,
	0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb, 0x4f040d56, 0x4bc510e1,
	0x46863638, 0x42472b8f, 0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
	0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47, 0x36194d42, 0x32d850f5,
	0x3f9b762c, 0x3b5a6b9b, 0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff,
	0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623, 0xf12f560e, 0xf5ee4bb9,
	0xf8ad6d60, 0xfc6c70d7, 0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,
	0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f, 0xc423cd6a, 0xc0e2d0dd,
	0xcda1f604, 0xc960ebb3, 0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7,
	0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b, 0x9b3660c6, 0x9ff77d71,
	0x92b45ba8, 0x9675461f, 0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
	0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640, 0x4e8ee645, 0x4a4ffbf2,
	0x470cdd2b, 0x43cdc09c, 0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8,
	0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24, 0x119b4be9, 0x155a565e,
	0x18197087, 0x1cd86d30, 0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,
	0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088, 0x2497d08d, 0x2056cd3a,
	0x2d15ebe3, 0x29d4f654, 0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0,
	0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c, 0xe3a1cbc1, 0xe760d676,
	0xea23f0af, 0xeee2ed18, 0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
	0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0, 0x9abc8bd5, 0x9e7d9662,
	0x933eb0bb, 0x97ffad0c, 0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668,
	0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4
  };

  /*!
   * A templatized KMP find that works both with a ByteVector and a ByteVectorMirror.
   */

  template <class Vector>
  int vectorFind(const Vector &v, const Vector &pattern, uint offset, int byteAlign)
  {
	if(pattern.size() > v.size() || offset > v.size() - 1)
	  return -1;

	// Let's go ahead and special case a pattern of size one since that's common
	// and easy to make fast.

	if(pattern.size() == 1) {
	  char p = pattern[0];
	  for(uint i = offset; i < v.size(); i++) {
		if(v[i] == p && (i - offset) % byteAlign == 0)
		  return i;
	  }
	  return -1;
	}

	uchar lastOccurrence[256];

	for(uint i = 0; i < 256; ++i)
	  lastOccurrence[i] = uchar(pattern.size());

	for(uint i = 0; i < pattern.size() - 1; ++i)
	  lastOccurrence[uchar(pattern[i])] = uchar(pattern.size() - i - 1);

	for(uint i = pattern.size() - 1 + offset; i < v.size(); i += lastOccurrence[uchar(v.at(i))]) {
	  int iBuffer = i;
	  int iPattern = pattern.size() - 1;

	  while(iPattern >= 0 && v.at(iBuffer) == pattern[iPattern]) {
		--iBuffer;
		--iPattern;
	  }

	  if(-1 == iPattern && (iBuffer + 1 - offset) % byteAlign == 0)
		return iBuffer + 1;
	}

	return -1;
  }

  /*!
   * Wraps the accessors to a ByteVector to make the search algorithm access the
   * elements in reverse.
   *
   * \see vectorFind()
   * \see ByteVector::rfind()
   */

  class ByteVectorMirror
  {
  public:
	ByteVectorMirror(const ByteVector &source) : v(source) {}

	char operator[](int index) const
	{
	  return v[v.size() - index - 1];
	}

	char at(int index) const
	{
	  return v.at(v.size() - index - 1);
	}

	ByteVectorMirror mid(uint index, uint length = 0xffffffff) const
	{
	  return length == 0xffffffff ? v.mid(0, index) : v.mid(index - length, length);
	}

	uint size() const
	{
	  return v.size();
	}

	int find(const ByteVectorMirror &pattern, uint offset = 0, int byteAlign = 1) const
	{
	  ByteVectorMirror v(*this);

	  if(offset > 0) {
		offset = size() - offset - pattern.size();
		if(offset >= size())
		  offset = 0;
	  }

	  const int pos = vectorFind<ByteVectorMirror>(v, pattern, offset, byteAlign);

	  // If the offset is zero then we need to adjust the location in the search
	  // to be appropriately reversed.  If not we need to account for the fact
	  // that the recursive call (called from the above line) has already ajusted
	  // for this but that the normal templatized find above will add the offset
	  // to the returned value.
	  //
	  // This is a little confusing at first if you don't first stop to think
	  // through the logic involved in the forward search.

	  if(pos == -1)
		return -1;

	  return size() - pos - pattern.size();
	}

  private:
	ByteVectorMirror &operator=(const ByteVectorMirror &);
	const ByteVector &v;
  };

  template <class T>
  T toNumber(const std::vector<char> &data, bool mostSignificantByteFirst)
  {
	T sum = 0;

	if(data.size() <= 0) {
	  debug("ByteVectorMirror::toNumber<T>() -- data is empty, returning 0");
	  return sum;
	}

	uint size = sizeof(T);
	uint last = data.size() > size ? size - 1 : data.size() - 1;

	for(uint i = 0; i <= last; i++)
	  sum |= (T) uchar(data[i]) << ((mostSignificantByteFirst ? last - i : i) * 8);

	return sum;
  }

  template <class T>
  ByteVector fromNumber(T value, bool mostSignificantByteFirst)
  {
	int size = sizeof(T);

	ByteVector v(size, 0);

	for(int i = 0; i < size; i++)
	  v[i] = uchar(value >> ((mostSignificantByteFirst ? size - 1 - i : i) * 8) & 0xff);

	return v;
  }
}

using namespace TagLib;

class ByteVector::ByteVectorPrivate : public RefCounter
{
public:
  ByteVectorPrivate() : RefCounter(), size(0) {}
  ByteVectorPrivate(const std::vector<char> &v) : RefCounter(), data(v), size(v.size()) {}
  ByteVectorPrivate(TagLib::uint len, char value) : RefCounter(), data(len, value), size(len) {}

  std::vector<char> data;

  // std::vector<T>::size() is very slow, so we'll cache the value

  uint size;
};

////////////////////////////////////////////////////////////////////////////////
// static members
////////////////////////////////////////////////////////////////////////////////

ByteVector ByteVector::null;

ByteVector ByteVector::fromCString(const char *s, uint length)
{
  ByteVector v;

  if(length == 0xffffffff)
	v.setData(s);
  else
	v.setData(s, length);

  return v;
}

ByteVector ByteVector::fromUInt(uint value, bool mostSignificantByteFirst)
{
  return fromNumber<uint>(value, mostSignificantByteFirst);
}

ByteVector ByteVector::fromShort(short value, bool mostSignificantByteFirst)
{
  return fromNumber<short>(value, mostSignificantByteFirst);
}

ByteVector ByteVector::fromLongLong(long long value, bool mostSignificantByteFirst)
{
  return fromNumber<long long>(value, mostSignificantByteFirst);
}

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

ByteVector::ByteVector()
{
  d = new ByteVectorPrivate;
}

ByteVector::ByteVector(uint size, char value)
{
  d = new ByteVectorPrivate(size, value);
}

ByteVector::ByteVector(const ByteVector &v) : d(v.d)
{
  d->ref();
}

ByteVector::ByteVector(char c)
{
  d = new ByteVectorPrivate;
  d->data.push_back(c);
  d->size = 1;
}

ByteVector::ByteVector(const char *data, uint length)
{
  d = new ByteVectorPrivate;
  setData(data, length);
}

ByteVector::ByteVector(const char *data)
{
  d = new ByteVectorPrivate;
  setData(data);
}

ByteVector::~ByteVector()
{
  if(d->deref())
	delete d;
}

ByteVector &ByteVector::setData(const char *data, uint length)
{
  detach();

  resize(length);

  if(length > 0)
	::memcpy(DATA(d), data, length);

  return *this;
}

ByteVector &ByteVector::setData(const char *data)
{
  return setData(data, ::strlen(data));
}

char *ByteVector::data()
{
  detach();
  return size() > 0 ? DATA(d) : 0;
}

const char *ByteVector::data() const
{
  return size() > 0 ? DATA(d) : 0;
}

ByteVector ByteVector::mid(uint index, uint length) const
{
  ByteVector v;

  if(index > size())
	return v;

  ConstIterator endIt;

  if(length < size() - index)
	endIt = d->data.begin() + index + length;
  else
	endIt = d->data.end();

  v.d->data.insert(v.d->data.begin(), ConstIterator(d->data.begin() + index), endIt);
  v.d->size = v.d->data.size();

  return v;
}

char ByteVector::at(uint index) const
{
  return index < size() ? d->data[index] : 0;
}

int ByteVector::find(const ByteVector &pattern, uint offset, int byteAlign) const
{
  return vectorFind<ByteVector>(*this, pattern, offset, byteAlign);
}

int ByteVector::rfind(const ByteVector &pattern, uint offset, int byteAlign) const
{
  // Ok, this is a little goofy, but pretty cool after it sinks in.  Instead of
  // reversing the find method's Boyer-Moore search algorithm I created a "mirror"
  // for a ByteVector to reverse the behavior of the accessors.

  ByteVectorMirror v(*this);
  ByteVectorMirror p(pattern);

  return v.find(p, offset, byteAlign);
}

bool ByteVector::containsAt(const ByteVector &pattern, uint offset, uint patternOffset, uint patternLength) const
{
  if(pattern.size() < patternLength)
	patternLength = pattern.size();

  // do some sanity checking -- all of these things are needed for the search to be valid

  if(patternLength > size() || offset >= size() || patternOffset >= pattern.size() || patternLength == 0)
	return false;

  // loop through looking for a mismatch

  for(uint i = 0; i < patternLength - patternOffset; i++) {
	if(at(i + offset) != pattern[i + patternOffset])
	  return false;
  }

  return true;
}

bool ByteVector::startsWith(const ByteVector &pattern) const
{
  return containsAt(pattern, 0);
}

bool ByteVector::endsWith(const ByteVector &pattern) const
{
  return containsAt(pattern, size() - pattern.size());
}

ByteVector &ByteVector::replace(const ByteVector &pattern, const ByteVector &with)
{
  if(pattern.size() == 0 || pattern.size() > size())
	return *this;

  const uint withSize = with.size();
  const uint patternSize = pattern.size();
  int offset = 0;

  if(withSize == patternSize) {
	// I think this case might be common enough to optimize it
	detach();
	offset = find(pattern);
	while(offset >= 0) {
	  ::memcpy(data() + offset, with.data(), withSize);
	  offset = find(pattern, offset + withSize);
	}
	return *this;
  }

  // calculate new size:
  uint newSize = 0;
  for(;;) {
	int next = find(pattern, offset);
	if(next < 0) {
	  if(offset == 0)
		// pattern not found, do nothing:
		return *this;
	  newSize += size() - offset;
	  break;
	}
	newSize += (next - offset) + withSize;
	offset = next + patternSize;
  }

  // new private data of appropriate size:
  ByteVectorPrivate *newData = new ByteVectorPrivate(newSize, 0);
  char *target = DATA(newData);
  const char *source = data();

  // copy modified data into new private data:
  offset = 0;
  for(;;) {
	int next = find(pattern, offset);
	if(next < 0) {
	  ::memcpy(target, source + offset, size() - offset);
	  break;
	}
	int chunkSize = next - offset;
	::memcpy(target, source + offset, chunkSize);
	target += chunkSize;
	::memcpy(target, with.data(), withSize);
	target += withSize;
	offset += chunkSize + patternSize;
  }

  // replace private data:
  if(d->deref())
	delete d;

  d = newData;

  return *this;
}

int ByteVector::endsWithPartialMatch(const ByteVector &pattern) const
{
  if(pattern.size() > size())
	return -1;

  const int startIndex = size() - pattern.size();

  // try to match the last n-1 bytes from the vector (where n is the pattern
  // size) -- continue trying to match n-2, n-3...1 bytes

  for(uint i = 1; i < pattern.size(); i++) {
	if(containsAt(pattern, startIndex + i, 0, pattern.size() - i))
	  return startIndex + i;
  }

  return -1;
}

ByteVector &ByteVector::append(const ByteVector &v)
{
  if(v.d->size == 0)
	return *this; // Simply return if appending nothing.

  detach();

  uint originalSize = d->size;
  resize(d->size + v.d->size);
  ::memcpy(DATA(d) + originalSize, DATA(v.d), v.size());

  return *this;
}

ByteVector &ByteVector::clear()
{
  detach();
  d->data.clear();
  d->size = 0;

  return *this;
}

TagLib::uint ByteVector::size() const
{
  return d->size;
}

ByteVector &ByteVector::resize(uint size, char padding)
{
  if(d->size < size) {
	d->data.reserve(size);
	d->data.insert(d->data.end(), size - d->size, padding);
  }
  else
	d->data.erase(d->data.begin() + size, d->data.end());

  d->size = size;

  return *this;
}

ByteVector::Iterator ByteVector::begin()
{
  return d->data.begin();
}

ByteVector::ConstIterator ByteVector::begin() const
{
  return d->data.begin();
}

ByteVector::Iterator ByteVector::end()
{
  return d->data.end();
}

ByteVector::ConstIterator ByteVector::end() const
{
  return d->data.end();
}

bool ByteVector::isNull() const
{
  return d == null.d;
}

bool ByteVector::isEmpty() const
{
  return d->data.size() == 0;
}

TagLib::uint ByteVector::checksum() const
{
  uint sum = 0;
  for(ByteVector::ConstIterator it = begin(); it != end(); ++it)
	sum = (sum << 8) ^ crcTable[((sum >> 24) & 0xff) ^ uchar(*it)];
  return sum;
}

TagLib::uint ByteVector::toUInt(bool mostSignificantByteFirst) const
{
  return toNumber<uint>(d->data, mostSignificantByteFirst);
}

short ByteVector::toShort(bool mostSignificantByteFirst) const
{
  return toNumber<unsigned short>(d->data, mostSignificantByteFirst);
}

unsigned short ByteVector::toUShort(bool mostSignificantByteFirst) const
{
  return toNumber<unsigned short>(d->data, mostSignificantByteFirst);
}

long long ByteVector::toLongLong(bool mostSignificantByteFirst) const
{
  return toNumber<unsigned long long>(d->data, mostSignificantByteFirst);
}

const char &ByteVector::operator[](int index) const
{
  return d->data[index];
}

char &ByteVector::operator[](int index)
{
  detach();

  return d->data[index];
}

bool ByteVector::operator==(const ByteVector &v) const
{
  if(d->size != v.d->size)
	return false;

  return ::memcmp(data(), v.data(), size()) == 0;
}

bool ByteVector::operator!=(const ByteVector &v) const
{
  return !operator==(v);
}

bool ByteVector::operator==(const char *s) const
{
  if(d->size != ::strlen(s))
	return false;

  return ::memcmp(data(), s, d->size) == 0;
}

bool ByteVector::operator!=(const char *s) const
{
  return !operator==(s);
}

bool ByteVector::operator<(const ByteVector &v) const
{
  int result = ::memcmp(data(), v.data(), d->size < v.d->size ? d->size : v.d->size);

  if(result != 0)
	return result < 0;
  else
	return size() < v.size();
}

bool ByteVector::operator>(const ByteVector &v) const
{
  return v < *this;
}

ByteVector ByteVector::operator+(const ByteVector &v) const
{
  ByteVector sum(*this);
  sum.append(v);
  return sum;
}

ByteVector &ByteVector::operator=(const ByteVector &v)
{
  if(&v == this)
	return *this;

  if(d->deref())
	delete d;

  d = v.d;
  d->ref();
  return *this;
}

ByteVector &ByteVector::operator=(char c)
{
  *this = ByteVector(c);
  return *this;
}

ByteVector &ByteVector::operator=(const char *data)
{
  *this = ByteVector(data);
  return *this;
}

ByteVector ByteVector::toHex() const
{
  ByteVector encoded(size() * 2);

  uint j = 0;
  for(uint i = 0; i < size(); i++) {
	unsigned char c = d->data[i];
	encoded[j++] = hexTable[(c >> 4) & 0x0F];
	encoded[j++] = hexTable[(c     ) & 0x0F];
  }

  return encoded;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

void ByteVector::detach()
{
  if(d->count() > 1) {
	d->deref();
	d = new ByteVectorPrivate(d->data);
  }
}

////////////////////////////////////////////////////////////////////////////////
// related functions
////////////////////////////////////////////////////////////////////////////////

std::ostream &operator<<(std::ostream &s, const ByteVector &v)
{
  for(TagLib::uint i = 0; i < v.size(); i++)
	s << v[i];
  return s;
}

/*** End of inlined file: tbytevector.cpp ***/


/*** Start of inlined file: tbytevectorlist.cpp ***/
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

using namespace TagLib;

class ByteVectorListPrivate
{

};

////////////////////////////////////////////////////////////////////////////////
// static members
////////////////////////////////////////////////////////////////////////////////

ByteVectorList ByteVectorList::split(const ByteVector &v, const ByteVector &pattern,
									 int byteAlign)
{
  return split(v, pattern, byteAlign, 0);
}

ByteVectorList ByteVectorList::split(const ByteVector &v, const ByteVector &pattern,
									 int byteAlign, int max)
{
  ByteVectorList l;

  uint previousOffset = 0;
  for(int offset = v.find(pattern, 0, byteAlign);
	  offset != -1 && (max == 0 || max > int(l.size()) + 1);
	  offset = v.find(pattern, offset + pattern.size(), byteAlign))
  {
	if(offset - previousOffset >= 1)
	  l.append(v.mid(previousOffset, offset - previousOffset));
	else
	  l.append(ByteVector::null);

	previousOffset = offset + pattern.size();
  }

  if(previousOffset < v.size())
	l.append(v.mid(previousOffset, v.size() - previousOffset));

  return l;
}

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

ByteVectorList::ByteVectorList() : List<ByteVector>()
{

}

ByteVectorList::ByteVectorList(const ByteVectorList &l) : List<ByteVector>(l)
{

}

ByteVectorList::~ByteVectorList()
{

}

ByteVector ByteVectorList::toByteVector(const ByteVector &separator) const
{
  ByteVector v;

  ConstIterator it = begin();

  while(it != end()) {
	v.append(*it);
	it++;
	if(it != end())
	  v.append(separator);
  }

  return v;
}

/*** End of inlined file: tbytevectorlist.cpp ***/


/*** Start of inlined file: tbytevectorstream.cpp ***/
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

#include <stdio.h>
#include <string.h>

#include <stdlib.h>

using namespace TagLib;

class ByteVectorStream::ByteVectorStreamPrivate
{
public:
  ByteVectorStreamPrivate(const ByteVector &data);

  ByteVector data;
  long position;
};

ByteVectorStream::ByteVectorStreamPrivate::ByteVectorStreamPrivate(const ByteVector &data) :
  data(data),
  position(0)
{
}

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

ByteVectorStream::ByteVectorStream(const ByteVector &data)
{
  d = new ByteVectorStreamPrivate(data);
}

ByteVectorStream::~ByteVectorStream()
{
  delete d;
}

FileName ByteVectorStream::name() const
{
  return FileName(""); // XXX do we need a name?
}

ByteVector ByteVectorStream::readBlock(ulong length)
{
  if(length == 0)
	return ByteVector::null;

  ByteVector v = d->data.mid(d->position, length);
  d->position += v.size();
  return v;
}

void ByteVectorStream::writeBlock(const ByteVector &data)
{
  uint size = data.size();
  if(d->position + size > length()) {
	truncate(d->position + size);
  }
  memcpy(d->data.data() + d->position, data.data(), size);
  d->position += size;
}

void ByteVectorStream::insert(const ByteVector &data, ulong start, ulong replace)
{
  long sizeDiff = data.size() - replace;
  if(sizeDiff < 0) {
	removeBlock(start + data.size(), -sizeDiff);
  }
  else if(sizeDiff > 0) {
	truncate(length() + sizeDiff);
	ulong readPosition = start + replace;
	ulong writePosition = start + data.size();
	memmove(d->data.data() + writePosition, d->data.data() + readPosition, length() - sizeDiff - readPosition);
  }
  seek(start);
  writeBlock(data);
}

void ByteVectorStream::removeBlock(ulong start, ulong length)
{
  ulong readPosition = start + length;
  ulong writePosition = start;
  if(readPosition < ulong(ByteVectorStream::length())) {
	ulong bytesToMove = ByteVectorStream::length() - readPosition;
	memmove(d->data.data() + writePosition, d->data.data() + readPosition, bytesToMove);
	writePosition += bytesToMove;
  }
  d->position = writePosition;
  truncate(writePosition);
}

bool ByteVectorStream::readOnly() const
{
  return false;
}

bool ByteVectorStream::isOpen() const
{
  return true;
}

void ByteVectorStream::seek(long offset, Position p)
{
  switch(p) {
  case Beginning:
	d->position = offset;
	break;
  case Current:
	d->position += offset;
	break;
  case End:
	d->position = length() - offset;
	break;
  }
}

void ByteVectorStream::clear()
{
}

long ByteVectorStream::tell() const
{
  return d->position;
}

long ByteVectorStream::length()
{
  return d->data.size();
}

void ByteVectorStream::truncate(long length)
{
  d->data.resize(length);
}

ByteVector *ByteVectorStream::data()
{
  return &d->data;
}

/*** End of inlined file: tbytevectorstream.cpp ***/


/*** Start of inlined file: tiostream.cpp ***/
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

using namespace TagLib;

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

IOStream::IOStream()
{
}

IOStream::~IOStream()
{
}

void IOStream::clear()
{
}

/*** End of inlined file: tiostream.cpp ***/


/*** Start of inlined file: tfilestream.cpp ***/
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

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4996) // Deprecated POSIX names
#pragma push_macro ("_CRT_SECURE_NO_WARNINGS")
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif
#include <stdio.h>
#ifdef _MSC_VER
#pragma pop_macro ("_CRT_SECURE_NO_WARNINGS")
#pragma warning (pop)
#endif

#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
# include <wchar.h>
# include <windows.h>
# include <io.h>
# define ftruncate _chsize
#else
# include <unistd.h>
#endif

#include <stdlib.h>

#ifndef R_OK
# define R_OK 4
#endif
#ifndef W_OK
# define W_OK 2
#endif

using namespace TagLib;

#ifdef _WIN32

typedef FileName FileNameHandle;

#else

struct FileNameHandle : public std::string
{
  FileNameHandle(FileName name) : std::string(name) {}
  operator FileName () const { return c_str(); }
};

#endif

class FileStream::FileStreamPrivate
{
public:
  FileStreamPrivate(FileName fileName, bool openReadOnly);

  FILE *file;

  FileNameHandle name;

  bool readOnly;
  ulong size;
  static const uint bufferSize = 1024;
};

FileStream::FileStreamPrivate::FileStreamPrivate(FileName fileName, bool openReadOnly) :
  file(0),
  name(fileName),
  readOnly(true),
  size(0)
{
  // First try with read / write mode, if that fails, fall back to read only.

#ifdef _WIN32

  if(wcslen((const wchar_t *) fileName) > 0) {

	if(openReadOnly)
	  file = _wfopen(name, L"rb");
	else {
	  file = _wfopen(name, L"rb+");

	  if(file)
		readOnly = false;
	  else
		file = _wfopen(name, L"rb");
	}

	if(file)
	  return;

  }

#endif

  if(openReadOnly)
	file = fopen(name, "rb");
  else {
	file = fopen(name, "rb+");

	if(file)
	  readOnly = false;
	else
	  file = fopen(name, "rb");
  }

  if(!file)
  {
	debug("Could not open file " + String((const char *) name));
  }
}

////////////////////////////////////////////////////////////////////////////////
// public members
////////////////////////////////////////////////////////////////////////////////

FileStream::FileStream(FileName file, bool openReadOnly)
{
  d = new FileStreamPrivate(file, openReadOnly);
}

FileStream::~FileStream()
{
  if(d->file)
	fclose(d->file);
  delete d;
}

FileName FileStream::name() const
{
  return d->name;
}

ByteVector FileStream::readBlock(ulong length)
{
  if(!d->file) {
	debug("FileStream::readBlock() -- Invalid File");
	return ByteVector::null;
  }

  if(length == 0)
	return ByteVector::null;

  if(length > FileStreamPrivate::bufferSize &&
	 length > ulong(FileStream::length()))
  {
	length = FileStream::length();
  }

  ByteVector v(static_cast<uint>(length));
  const int count = fread(v.data(), sizeof(char), length, d->file);
  v.resize(count);
  return v;
}

void FileStream::writeBlock(const ByteVector &data)
{
  if(!d->file)
	return;

  if(d->readOnly) {
	debug("File::writeBlock() -- attempted to write to a file that is not writable");
	return;
  }

  fwrite(data.data(), sizeof(char), data.size(), d->file);
}

void FileStream::insert(const ByteVector &data, ulong start, ulong replace)
{
  if(!d->file)
	return;

  if(data.size() == replace) {
	seek(start);
	writeBlock(data);
	return;
  }
  else if(data.size() < replace) {
	  seek(start);
	  writeBlock(data);
	  removeBlock(start + data.size(), replace - data.size());
	  return;
  }

  // Woohoo!  Faster (about 20%) than id3lib at last.  I had to get hardcore
  // and avoid TagLib's high level API for rendering just copying parts of
  // the file that don't contain tag data.
  //
  // Now I'll explain the steps in this ugliness:

  // First, make sure that we're working with a buffer that is longer than
  // the *differnce* in the tag sizes.  We want to avoid overwriting parts
  // that aren't yet in memory, so this is necessary.

  ulong bufferLength = bufferSize();

  while(data.size() - replace > bufferLength)
	bufferLength += bufferSize();

  // Set where to start the reading and writing.

  long readPosition = start + replace;
  long writePosition = start;

  ByteVector buffer;
  ByteVector aboutToOverwrite(static_cast<uint>(bufferLength));

  // This is basically a special case of the loop below.  Here we're just
  // doing the same steps as below, but since we aren't using the same buffer
  // size -- instead we're using the tag size -- this has to be handled as a
  // special case.  We're also using File::writeBlock() just for the tag.
  // That's a bit slower than using char *'s so, we're only doing it here.

  seek(readPosition);
  int bytesRead = fread(aboutToOverwrite.data(), sizeof(char), bufferLength, d->file);
  readPosition += bufferLength;

  seek(writePosition);
  writeBlock(data);
  writePosition += data.size();

  buffer = aboutToOverwrite;

  // In case we've already reached the end of file...

  buffer.resize(bytesRead);

  // Ok, here's the main loop.  We want to loop until the read fails, which
  // means that we hit the end of the file.

  while(!buffer.isEmpty()) {

	// Seek to the current read position and read the data that we're about
	// to overwrite.  Appropriately increment the readPosition.

	seek(readPosition);
	bytesRead = fread(aboutToOverwrite.data(), sizeof(char), bufferLength, d->file);
	aboutToOverwrite.resize(bytesRead);
	readPosition += bufferLength;

	// Check to see if we just read the last block.  We need to call clear()
	// if we did so that the last write succeeds.

	if(ulong(bytesRead) < bufferLength)
	  clear();

	// Seek to the write position and write our buffer.  Increment the
	// writePosition.

	seek(writePosition);
	fwrite(buffer.data(), sizeof(char), buffer.size(), d->file);
	writePosition += buffer.size();

	// Make the current buffer the data that we read in the beginning.

	buffer = aboutToOverwrite;

	// Again, we need this for the last write.  We don't want to write garbage
	// at the end of our file, so we need to set the buffer size to the amount
	// that we actually read.

	bufferLength = bytesRead;
  }
}

void FileStream::removeBlock(ulong start, ulong length)
{
  if(!d->file)
	return;

  ulong bufferLength = bufferSize();

  long readPosition = start + length;
  long writePosition = start;

  ByteVector buffer(static_cast<uint>(bufferLength));

  ulong bytesRead = 1;

  while(bytesRead != 0) {
	seek(readPosition);
	bytesRead = fread(buffer.data(), sizeof(char), bufferLength, d->file);
	readPosition += bytesRead;

	// Check to see if we just read the last block.  We need to call clear()
	// if we did so that the last write succeeds.

	if(bytesRead < bufferLength)
	  clear();

	seek(writePosition);
	fwrite(buffer.data(), sizeof(char), bytesRead, d->file);
	writePosition += bytesRead;
  }
  truncate(writePosition);
}

bool FileStream::readOnly() const
{
  return d->readOnly;
}

bool FileStream::isOpen() const
{
  return (d->file != NULL);
}

void FileStream::seek(long offset, Position p)
{
  if(!d->file) {
	debug("File::seek() -- trying to seek in a file that isn't opened.");
	return;
  }

  switch(p) {
  case Beginning:
	fseek(d->file, offset, SEEK_SET);
	break;
  case Current:
	fseek(d->file, offset, SEEK_CUR);
	break;
  case End:
	fseek(d->file, offset, SEEK_END);
	break;
  }
}

void FileStream::clear()
{
  clearerr(d->file);
}

long FileStream::tell() const
{
  return ftell(d->file);
}

long FileStream::length()
{
  // Do some caching in case we do multiple calls.

  if(d->size > 0)
	return d->size;

  if(!d->file)
	return 0;

  long curpos = tell();

  seek(0, End);
  long endpos = tell();

  seek(curpos, Beginning);

  d->size = endpos;
  return endpos;
}

////////////////////////////////////////////////////////////////////////////////
// protected members
////////////////////////////////////////////////////////////////////////////////

void FileStream::truncate(long length)
{
  ftruncate(fileno(d->file), length);
}

TagLib::uint FileStream::bufferSize()
{
  return FileStreamPrivate::bufferSize;
}

/*** End of inlined file: tfilestream.cpp ***/


/*** Start of inlined file: tdebug.cpp ***/
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

#ifndef NDEBUG
#include <iostream>
#include <bitset>

using namespace TagLib;

void TagLib::debug(const String &s)
{
  std::cerr << "TagLib: " << s << std::endl;
}

void TagLib::debugData(const ByteVector &v)
{
  for(uint i = 0; i < v.size(); i++) {

	std::cout << "*** [" << i << "] - '" << char(v[i]) << "' - int " << int(v[i])
			  << std::endl;

	std::bitset<8> b(v[i]);

	for(int j = 0; j < 8; j++)
	  std::cout << i << ":" << j << " " << b.test(j) << std::endl;

	std::cout << std::endl;
  }
}
#endif

/*** End of inlined file: tdebug.cpp ***/


/*** Start of inlined file: unicode.cpp ***/
/*
 * Copyright 2001 Unicode, Inc.
 *
 * Disclaimer
 *
 * This source code is provided as is by Unicode, Inc. No claims are
 * made as to fitness for any particular purpose. No warranties of any
 * kind are expressed or implied. The recipient agrees to determine
 * applicability of information provided. If this file has been
 * purchased on magnetic or optical media from Unicode, Inc., the
 * sole remedy for any claim will be exchange of defective media
 * within 90 days of receipt.
 *
 * Limitations on Rights to Redistribute This Code
 *
 * Unicode, Inc. hereby grants the right to freely use the information
 * supplied in this file in the creation of products supporting the
 * Unicode Standard, and to make copies of this file in any form
 * for internal or external distribution as long as this notice
 * remains attached.
 */

/*
 * This file has been modified by Scott Wheeler <wheeler@kde.org> to remove
 * the UTF32 conversion functions and to place the appropriate functions
 * in their own C++ namespace.
 */

/* ---------------------------------------------------------------------

	Conversions between UTF32, UTF-16, and UTF-8. Source code file.
	Author: Mark E. Davis, 1994.
	Rev History: Rick McGowan, fixes & updates May 2001.
	Sept 2001: fixed const & error conditions per
		mods suggested by S. Parent & A. Lillich.

	See the header file "ConvertUTF.h" for complete documentation.

------------------------------------------------------------------------ */

#include <stdio.h>

#define UNI_SUR_HIGH_START	(UTF32)0xD800
#define UNI_SUR_HIGH_END	(UTF32)0xDBFF
#define UNI_SUR_LOW_START	(UTF32)0xDC00
#define UNI_SUR_LOW_END		(UTF32)0xDFFF
#define false			0
#define true			1

namespace Unicode {

static const int halfShift	= 10; /* used for shifting by 10 bits */

static const UTF32 halfBase	= 0x0010000UL;
static const UTF32 halfMask	= 0x3FFUL;

/*
 * Index into the table below with the first byte of a UTF-8 sequence to
 * get the number of trailing bytes that are supposed to follow it.
 */
static const char trailingBytesForUTF8[256] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};

/*
 * Magic values subtracted from a buffer value during UTF8 conversion.
 * This table contains as many values as there might be trailing bytes
 * in a UTF-8 sequence.
 */
static const UTF32 offsetsFromUTF8[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL,
					 0x03C82080UL, 0xFA082080UL, 0x82082080UL };

/*
 * Once the bits are split out into bytes of UTF-8, this is a mask OR-ed
 * into the first byte, depending on how many bytes follow.  There are
 * as many entries in this table as there are UTF-8 sequence types.
 * (I.e., one byte sequence, two byte... six byte sequence.)
 */
static const UTF8 firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

/* --------------------------------------------------------------------- */

/* The interface converts a whole buffer to avoid function-call overhead.
 * Constants have been gathered. Loops & conditionals have been removed as
 * much as possible for efficiency, in favor of drop-through switches.
 * (See "Note A" at the bottom of the file for equivalent code.)
 * If your compiler supports it, the "isLegalUTF8" call can be turned
 * into an inline function.
 */

/* --------------------------------------------------------------------- */

ConversionResult ConvertUTF16toUTF8 (
		const UTF16** sourceStart, const UTF16* sourceEnd,
		UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags) {
	ConversionResult result = conversionOK;
	const UTF16* source = *sourceStart;
	UTF8* target = *targetStart;
	while (source < sourceEnd) {
		UTF32 ch;
		unsigned short bytesToWrite = 0;
		const UTF32 byteMask = 0xBF;
		const UTF32 byteMark = 0x80;
		const UTF16* oldSource = source; /* In case we have to back up because of target overflow. */
		ch = *source++;
		/* If we have a surrogate pair, convert to UTF32 first. */
		if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_HIGH_END && source < sourceEnd) {
			UTF32 ch2 = *source;
			if (ch2 >= UNI_SUR_LOW_START && ch2 <= UNI_SUR_LOW_END) {
				ch = ((ch - UNI_SUR_HIGH_START) << halfShift)
					+ (ch2 - UNI_SUR_LOW_START) + halfBase;
				++source;
			} else if (flags == strictConversion) { /* it's an unpaired high surrogate */
				--source; /* return to the illegal value itself */
				result = sourceIllegal;
				break;
			}
		} else if ((flags == strictConversion) && (ch >= UNI_SUR_LOW_START && ch <= UNI_SUR_LOW_END)) {
			--source; /* return to the illegal value itself */
			result = sourceIllegal;
			break;
		}
		/* Figure out how many bytes the result will require */
		if (ch < (UTF32)0x80) {			bytesToWrite = 1;
		} else if (ch < (UTF32)0x800) {		bytesToWrite = 2;
		} else if (ch < (UTF32)0x10000) {	bytesToWrite = 3;
		} else if (ch < (UTF32)0x200000) {	bytesToWrite = 4;
		} else {				bytesToWrite = 2;
							ch = UNI_REPLACEMENT_CHAR;
		}
		// printf("bytes to write = %i\n", bytesToWrite);
		target += bytesToWrite;
		if (target > targetEnd) {
			source = oldSource; /* Back up source pointer! */
			target -= bytesToWrite; result = targetExhausted; break;
		}
		switch (bytesToWrite) {	/* note: everything falls through. */
			case 4:	*--target = (ch | byteMark) & byteMask; ch >>= 6;
			case 3:	*--target = (ch | byteMark) & byteMask; ch >>= 6;
			case 2:	*--target = (ch | byteMark) & byteMask; ch >>= 6;
			case 1:	*--target =  ch | firstByteMark[bytesToWrite];
		}
		target += bytesToWrite;
	}
	*sourceStart = source;
	*targetStart = target;
	return result;
}

/* --------------------------------------------------------------------- */

/*
 * Utility routine to tell whether a sequence of bytes is legal UTF-8.
 * This must be called with the length pre-determined by the first byte.
 * If not calling this from ConvertUTF8to*, then the length can be set by:
 *	length = trailingBytesForUTF8[*source]+1;
 * and the sequence is illegal right away if there aren't that many bytes
 * available.
 * If presented with a length > 4, this returns false.  The Unicode
 * definition of UTF-8 goes up to 4-byte sequences.
 */

static Boolean isLegalUTF8(const UTF8 *source, int length) {
	UTF8 a;
	const UTF8 *srcptr = source+length;
	switch (length) {
	default: return false;
		/* Everything else falls through when "true"... */
	case 4: if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return false;
	case 3: if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return false;
	case 2: if ((a = (*--srcptr)) > 0xBF) return false;
		switch (*source) {
		    /* no fall-through in this inner switch */
		    case 0xE0: if (a < 0xA0) return false; break;
		    case 0xF0: if (a < 0x90) return false; break;
		    case 0xF4: if (a > 0x8F) return false; break;
		    default:  if (a < 0x80) return false;
		}
		case 1: if (*source >= 0x80 && *source < 0xC2) return false;
		if (*source > 0xF4) return false;
	}
	return true;
}

/* --------------------------------------------------------------------- */

/*
 * Exported function to return whether a UTF-8 sequence is legal or not.
 * This is not used here; it's just exported.
 */
Boolean isLegalUTF8Sequence(const UTF8 *source, const UTF8 *sourceEnd) {
	int length = trailingBytesForUTF8[*source]+1;
	if (source+length > sourceEnd) {
	    return false;
	}
	return isLegalUTF8(source, length);
}

/* --------------------------------------------------------------------- */

ConversionResult ConvertUTF8toUTF16 (
		const UTF8** sourceStart, const UTF8* sourceEnd,
		UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags) {
	ConversionResult result = conversionOK;
	const UTF8* source = *sourceStart;
	UTF16* target = *targetStart;
	while (source < sourceEnd) {
		UTF32 ch = 0;
		unsigned short extraBytesToRead = trailingBytesForUTF8[*source];
		if (source + extraBytesToRead >= sourceEnd) {
			result = sourceExhausted; break;
		}
		/* Do this check whether lenient or strict */
		if (! isLegalUTF8(source, extraBytesToRead+1)) {
			result = sourceIllegal;
			break;
		}
		/*
		 * The cases all fall through. See "Note A" below.
		 */
		switch (extraBytesToRead) {
			case 3:	ch += *source++; ch <<= 6;
			case 2:	ch += *source++; ch <<= 6;
			case 1:	ch += *source++; ch <<= 6;
			case 0:	ch += *source++;
		}
		ch -= offsetsFromUTF8[extraBytesToRead];

		if (target >= targetEnd) {
			source -= (extraBytesToRead+1);	/* Back up source pointer! */
			result = targetExhausted; break;
		}
		if (ch <= UNI_MAX_BMP) { /* Target is a character <= 0xFFFF */
			if ((flags == strictConversion) && (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END)) {
				source -= (extraBytesToRead+1); /* return to the illegal value itself */
				result = sourceIllegal;
				break;
			} else {
			    *target++ = ch;	/* normal case */
			}
		} else if (ch > UNI_MAX_UTF16) {
			if (flags == strictConversion) {
				result = sourceIllegal;
				source -= (extraBytesToRead+1); /* return to the start */
				break; /* Bail out; shouldn't continue */
			} else {
				*target++ = UNI_REPLACEMENT_CHAR;
			}
		} else {
			/* target is a character in range 0xFFFF - 0x10FFFF. */
			if (target + 1 >= targetEnd) {
				source -= (extraBytesToRead+1);	/* Back up source pointer! */
				result = targetExhausted; break;
			}
			ch -= halfBase;
			*target++ = (ch >> halfShift) + UNI_SUR_HIGH_START;
			*target++ = (ch & halfMask) + UNI_SUR_LOW_START;
		}
	}
	*sourceStart = source;
	*targetStart = target;
	return result;
}

}

/* ---------------------------------------------------------------------

	Note A.
	The fall-through switches in UTF-8 reading code save a
	temp variable, some decrements & conditionals.  The switches
	are equivalent to the following loop:
		{
			int tmpBytesToRead = extraBytesToRead+1;
			do {
				ch += *source++;
				--tmpBytesToRead;
				if (tmpBytesToRead) ch <<= 6;
			} while (tmpBytesToRead > 0);
		}
	In UTF-8 writing code, the switches on "bytesToWrite" are
	similarly unrolled loops.

   --------------------------------------------------------------------- */

/*** End of inlined file: unicode.cpp ***/

#ifdef _MSC_VER
#pragma warning (pop)
#pragma pop_macro ("_CRT_SECURE_NO_WARNINGS")
#endif

