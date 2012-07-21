/*============================================================================*/
/*
  VFLib: https://github.com/vinniefalco/VFLib

  Copyright (C) 2008 by Vinnie Falco <vinnie.falco@gmail.com>

  This library contains portions of other open source products covered by
  separate licenses. Please see the corresponding source files for specific
  terms.
  
  VFLib is provided under the terms of The MIT License (MIT):

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
*/
/*============================================================================*/

#ifndef __VF_CONNECTEDEDGES_VFHEADER__
#define __VF_CONNECTEDEDGES_VFHEADER__

#ifndef DOXYGEN

class ConnectedEdges
{
public:
  typedef Button::ConnectedEdgeFlags ConnectedEdgeFlags;

  void setConnectedEdges (int connectedEdgeFlags_)
  {
    connectedEdgeFlags.flags = connectedEdgeFlags_;
  }

  void setConnectedEdgeFlag (int flag, bool connected)
  {
    if (connected)
      connectedEdgeFlags.flags |= flag;
    else
      connectedEdgeFlags.flags &= ~flag;
  }

  void setConnectedOnLeft (bool connected)
    { setConnectedEdgeFlag (Button::ConnectedOnLeft, connected); }

  void setConnectedOnRight (bool connected)
    { setConnectedEdgeFlag (Button::ConnectedOnRight, connected); }

  void setConnectedOnTop (bool connected)
    { setConnectedEdgeFlag (Button::ConnectedOnTop, connected); }

  void setConnectedOnBottom (bool connected)
    { setConnectedEdgeFlag (Button::ConnectedOnBottom, connected); }

  int getConnectedEdgeFlags() const  { return connectedEdgeFlags.flags; }
  bool isConnectedOnLeft() const     { return (connectedEdgeFlags.flags & Button::ConnectedOnLeft) != 0; }
  bool isConnectedOnRight() const    { return (connectedEdgeFlags.flags & Button::ConnectedOnRight) != 0; }
  bool isConnectedOnTop() const      { return (connectedEdgeFlags.flags & Button::ConnectedOnTop) != 0; }
  bool isConnectedOnBottom() const   { return (connectedEdgeFlags.flags & Button::ConnectedOnBottom) != 0; }

private:
  struct Flags
  {
    Flags() : flags(0) {}
    int flags;
  };
  Flags connectedEdgeFlags;
};

#endif

#endif
