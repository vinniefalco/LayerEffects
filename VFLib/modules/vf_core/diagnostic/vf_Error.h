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

#ifndef VF_ERROR_VFHEADER
#define VF_ERROR_VFHEADER

#include "vf_SafeBool.h"

/**
  A concise error report.

  This lightweight but flexible class records lets you record the file and
  line where a recoverable error occurred, along with some optional human
  readable text.

  A recoverable error can be passed along and turned into a non recoverable
  error by throwing the object: it's derivation from std::exception is
  fully compliant with the C++ exception interface.

  @ingroup vf_core
*/   
class Error
  : public std::exception
  , public SafeBool <Error>
{
public:
  /** Numeric code.

    This enumeration is useful when the caller needs to take different
    actions depending on the failure. For example, trying again later if
    a file is locked.
  */
  enum Code
  {
    success,        //!< "the operation was successful"

    general,        //!< "a general error occurred"

    canceled,       //!< "the operation was canceled"
    exception,      //!< "an exception was thrown"
    unexpected,     //!< "an unexpected result was encountered"
    platform,       //!< "a system exception was signaled"

    noMemory,       //!< "there was not enough memory"
    noMoreData,     //!< "the end of data was reached"
    invalidData,    //!< "the data is corrupt or invalid"
    bufferSpace,    //!< "the buffer is too small"
    badParameter,   //!< "one or more parameters were invalid"
    assertFailed,   //!< "an assertion failed"

    fileInUse,	    //!< "the file is in use"
    fileExists,	    //!< "the file exists"
    fileNoPerm,	    //!< "permission was denied" (file attributes conflict)
    fileIOError,    //!< "an I/O or device error occurred"
    fileNoSpace,    //!< "there is no space left on the device"
    fileNotFound,   //!< "the file was not found"
    fileNameInvalid //!< "the file name was illegal or malformed"
  };

  Error ();
  Error (const Error& other);
  Error& operator= (const Error& other);

  virtual ~Error() noexcept;

  Code code () const;
  bool failed () const;

  bool asBoolean () const;

  const String getReasonText () const;
  const String getSourceFilename () const;
  int getLineNumber () const;

  Error& fail (const char* sourceFileName,
    int lineNumber,
    const String reasonText,
    Code errorCode = general);

  Error& fail (const char* sourceFileName,
    int lineNumber,
    Code errorCode = general);

  // A function that is capable of recovering from an error (for
  // example, by performing a different action) can reset the
  // object so it can be passed up.
  void reset ();

  // Call this when reporting the error to clear the "checked" flag
  void willBeReported () const;

  // for std::exception. This lets you throw an Error that should
  // terminate the application. The what() message will be less
  // descriptive so ideally you should catch the Error object instead.
  const char* what() const noexcept;

  static const String getReasonTextForCode (Code code);

private:
  Code m_code;
  String m_reasonText;
  String m_sourceFileName;
  int m_lineNumber;
  mutable bool m_needsToBeChecked;

  mutable String m_what; // created on demand
  mutable const char* m_szWhat;
};

#endif
