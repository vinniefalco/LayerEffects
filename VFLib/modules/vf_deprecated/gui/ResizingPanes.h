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

#ifndef RESIZINGPANES_H
#define RESIZINGPANES_H

#include "Static.h"

namespace Ui {

namespace Control {

// holds 2 components stacked vertically or horizontally that
// can have their size adjusted by a gripper between them.
class ResizingPanes
  : public Component
  , public ResizableChild
{
public:
  enum
  {
    dividerThickness = 7
  };

  ResizingPanes (bool isVertical,
                 double growthFraction,
                 double initialRatio,
                 Facade::Base* facade,
                 Component* left,
                 Component* right);

  void setLeftSize (int size);

  void resized();

  void resizeStart();

protected:
  void adjustPanes ();

private:
  class Divider : public Control::Static
  {
  public:
    Divider (bool isVertical,
             Facade::Base* facade,
             ResizingPanes* owner);
    void updateCursor ();
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);
    void enablementChanged ();
  private:
    bool m_isVertical;
    int m_startTopLeft;
    ResizingPanes& m_owner;
    int m_min;
    int m_max;
  };

  bool m_isVertical;
  int m_dividerThickness;
  double m_growthFraction;
  double m_initialRatio;
  ScopedPointer <Divider> m_divider;
  ScopedPointer <Component> m_left;
  ScopedPointer <Component> m_right;
  ResizableChild* m_leftChild;
  ResizableChild* m_rightChild;
  int m_lastKnownSize;
};

}

}

#endif
