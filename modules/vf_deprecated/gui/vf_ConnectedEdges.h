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
