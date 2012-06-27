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

Error::Error()
  : m_code (success)
  , m_lineNumber (0)
  , m_needsToBeChecked (true)
  , m_szWhat (0)
{
}

Error::Error (const Error& other)
  : m_code (other.m_code)
  , m_reasonText (other.m_reasonText)
  , m_sourceFileName (other.m_sourceFileName)
  , m_lineNumber (other.m_lineNumber)
  , m_needsToBeChecked (true)
  , m_szWhat (0)
{
  other.m_needsToBeChecked = false;
}

Error::~Error() noexcept
{
  /* If this goes off it means an error object was created but never tested */
  jassert (!m_needsToBeChecked);
}

Error& Error::operator= (const Error& other)
{
  m_code = other.m_code;
  m_reasonText = other.m_reasonText;
  m_sourceFileName = other.m_sourceFileName;
  m_lineNumber = other.m_lineNumber;
  m_needsToBeChecked = true;
  m_what = String::empty;
  m_szWhat = 0;

  other.m_needsToBeChecked = false;

  return *this;
}

Error::Code Error::code () const
{
  m_needsToBeChecked = false;
  return m_code;
}

bool Error::failed () const
{
  return code () != success;
}

bool Error::asBoolean () const
{
  return code () != success;
}

const String Error::getReasonText () const
{
  return m_reasonText;
}

const String Error::getSourceFilename () const
{
  return m_sourceFileName;
}

int Error::getLineNumber () const
{
  return m_lineNumber;
}

Error& Error::fail (const char* sourceFileName,
                    int lineNumber,
                    const String reasonText,
                    Code errorCode)
{
  jassert (m_code == success);
  jassert (errorCode != success);

  m_code = errorCode;
  m_reasonText = reasonText;
  m_sourceFileName = Debug::getFileNameFromPath (sourceFileName);
  m_lineNumber = lineNumber;
  m_needsToBeChecked = true;

  return *this;
}

Error& Error::fail (const char* sourceFileName,
                    int lineNumber,
                    Code errorCode)
{
  return fail (sourceFileName,
               lineNumber,
               getReasonTextForCode (errorCode), 
               errorCode);
}

void Error::reset ()
{
  m_code = success;
  m_reasonText = String::empty;
  m_sourceFileName = String::empty;
  m_lineNumber = 0;
  m_needsToBeChecked = true;
  m_what = String::empty;
  m_szWhat = 0;
}

void Error::willBeReported () const
{
  m_needsToBeChecked = false;
}

const char* Error::what () const noexcept
{
  if (!m_szWhat)
  {
// The application could not be initialized because sqlite was denied access permission
// The application unexpectedly quit because the exception 'sqlite was denied access permission at file ' was thrown
    m_what <<
      m_reasonText << " " <<
      TRANS("at file") << " '" <<
      m_sourceFileName << "' " <<
      TRANS("line") << " " <<
      String (m_lineNumber) << " " <<
      TRANS("with code") << " = " <<
      String (m_code);

    m_szWhat = (const char*)m_what.toUTF8();
  }

  return m_szWhat;
}

const String Error::getReasonTextForCode (Code code)
{
  String s;

  switch (code)
  {
  case success:         s=TRANS("the operation was successful"); break;

  case general:         s=TRANS("a general error occurred"); break;

  case canceled:        s=TRANS("the operation was canceled"); break;
  case exception:       s=TRANS("an exception was thrown"); break;
  case unexpected:      s=TRANS("an unexpected result was encountered"); break;
  case platform:        s=TRANS("a system exception was signaled"); break;

  case noMemory:        s=TRANS("there was not enough memory"); break;
  case noMoreData:      s=TRANS("the end of data was reached"); break;
  case invalidData:     s=TRANS("the data is corrupt or invalid"); break;
  case bufferSpace:     s=TRANS("the buffer is too small"); break;
  case badParameter:    s=TRANS("one or more parameters were invalid"); break;
  case assertFailed:    s=TRANS("an assertion failed"); break;

  case fileInUse:       s=TRANS("the file is in use"); break;
  case fileExists:      s=TRANS("the file exists"); break;
  case fileNoPerm:      s=TRANS("permission was denied"); break;
  case fileIOError:     s=TRANS("an I/O or device error occurred"); break;
  case fileNoSpace:     s=TRANS("there is no space left on the device"); break;
  case fileNotFound:    s=TRANS("the file was not found"); break;
  case fileNameInvalid: s=TRANS("the file name was illegal or malformed"); break;

  default:              s=TRANS("an unknown error code was received"); break;
  }

  return s;
}
