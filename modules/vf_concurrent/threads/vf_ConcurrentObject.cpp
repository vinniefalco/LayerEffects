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

class ConcurrentObject::Deleter
{
private:
  Deleter () : m_thread ("AsyncDeleter")
  {
    m_thread.start ();
  }

  ~Deleter ()
  {
    m_thread.stop (true);
  }

  void performAtExit ()
  {
    //delete this;
  }

  static void doDelete (ConcurrentObject* sharedObject)
  {
    delete sharedObject;
  }

public:
  void destroy (ConcurrentObject* sharedObject)
  {
    if (m_thread.isAssociatedWithCurrentThread ())
      delete sharedObject;
    else
      m_thread.call (&Deleter::doDelete, sharedObject);
  }

  static Deleter& getInstance ()
  {
    static Deleter instance;

    return instance;
  }

private:
  ThreadWithCallQueue m_thread;
};

//------------------------------------------------------------------------------

ConcurrentObject::ConcurrentObject()
{
}

ConcurrentObject::~ConcurrentObject()
{
}

void ConcurrentObject::destroyConcurrentObject ()
{
  Deleter::getInstance().destroy (this);
}
