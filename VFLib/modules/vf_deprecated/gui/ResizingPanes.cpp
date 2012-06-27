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

namespace Ui {

namespace Control {

ResizingPanes::Divider::Divider (bool isVertical,
                                 Facade::Base* facade,
                                 ResizingPanes* owner)
  : Static (facade)
  , m_isVertical(isVertical)
  , m_owner (*owner)
{
  updateCursor ();
}

void ResizingPanes::Divider::updateCursor ()
{
  if (isEnabled())
  {
    if (m_isVertical)
      setMouseCursor (MouseCursor::LeftRightResizeCursor);
    else
      setMouseCursor (MouseCursor::UpDownResizeCursor);
  }
  else
  {
    setMouseCursor (MouseCursor::NormalCursor);
  }
}

void ResizingPanes::Divider::mouseDown (const MouseEvent& e)
{
  if (isEnabled())
  {
    if (m_isVertical)
      m_startTopLeft = getBounds().getX();
    else
      m_startTopLeft = getBounds().getY();

    // ResizableChild support
    if (m_owner.m_leftChild)
      m_owner.m_leftChild->resizeStart();
    if (m_owner.m_rightChild)
      m_owner.m_rightChild->resizeStart();

    Rectangle<int> parentBounds = getParentComponent()->getLocalBounds();

    if (m_isVertical)
    {
      m_min = parentBounds.getX() +
        ( m_owner.m_leftChild ? m_owner.m_leftChild->getMinimumWidth() : 0);
      m_max = parentBounds.getRight() - getWidth() -
        ( m_owner.m_rightChild ? m_owner.m_rightChild->getMinimumWidth() : 0);
      jassert (m_min <= m_max);
    }
    else
    {
      m_min = parentBounds.getY() +
        ( m_owner.m_leftChild ? m_owner.m_leftChild->getMinimumHeight() : 0);
      m_max = parentBounds.getBottom() - getHeight() -
        ( m_owner.m_rightChild ? m_owner.m_rightChild->getMinimumHeight() : 0);
      jassert (m_min <= m_max);
    }
  }
}

void ResizingPanes::Divider::mouseDrag (const MouseEvent& e)
{
  if (isEnabled())
  {
    if (m_isVertical)
    {
      int x = jlimit (m_min, m_max, m_startTopLeft + e.getDistanceFromDragStartX());
      setTopLeftPosition(x, getBounds().getY());
    }
    else
    {
      int y = jlimit (m_min, m_max, m_startTopLeft + e.getDistanceFromDragStartY());
      setTopLeftPosition(getBounds().getX(), y);
    }

    m_owner.adjustPanes ();
  }
}

void ResizingPanes::Divider::enablementChanged ()
{
  updateCursor ();

  Static::enablementChanged();
}

//------------------------------------------------------------------------------

ResizingPanes::ResizingPanes (bool isVertical,
                              double growthFraction,
                              double initialRatio,
                              Facade::Base* facade,
                              Component* left,
                              Component* right)
  : m_isVertical (isVertical)
  , m_dividerThickness (dividerThickness)
  , m_growthFraction (growthFraction)
  , m_initialRatio (0.5)
  , m_lastKnownSize (-1)
  , m_left (left)
  , m_right (right)
  , m_leftChild (dynamic_cast<ResizableChild*>(left))
  , m_rightChild (dynamic_cast<ResizableChild*>(right))
{
  m_divider = new Divider (isVertical, facade, this);
  addAndMakeVisible (m_divider);

  addAndMakeVisible (m_left);
  addAndMakeVisible (m_right);
}

void ResizingPanes::setLeftSize (int size)
{
  Rectangle <int> const bounds = getLocalBounds ();

  if (m_isVertical)
  {
    m_divider->setTopLeftPosition (bounds.getX () + size,
                                   bounds.getY ());
  }
  else
  {
    m_divider->setTopLeftPosition (bounds.getX (),
                                   bounds.getY () + size);
  }

  adjustPanes ();
}

void ResizingPanes::resized()
{
  Rectangle <int> b = getLocalBounds();
  Rectangle <int> r = b;

  if (m_lastKnownSize == -1)
  {
    // first time
    if (m_isVertical)
    {
      m_divider->setBounds (r.getX() + m_initialRatio * ( r.getWidth() - m_dividerThickness) + 0.5,
        r.getY(), m_dividerThickness, r.getHeight());
      m_lastKnownSize = getWidth();
    }
    else
    {
      m_divider->setBounds (r.getX(), r.getY() + m_initialRatio * ( r.getHeight() - m_dividerThickness) + 0.5,
        r.getWidth(), m_dividerThickness);
      m_lastKnownSize = getHeight();
    }
  }
  else
  {
    if (m_isVertical)
    {
      int oldX = m_divider->getX();
      double ratio = double(oldX - r.getX()) / (m_lastKnownSize - m_dividerThickness);
      int deltaX = r.getX() + ratio * (r.getWidth() - m_dividerThickness) - oldX + 0.5;
      m_divider->setBounds (oldX + m_growthFraction * deltaX,
        r.getY(), m_dividerThickness, r.getHeight());
      m_lastKnownSize = getWidth();
    }
    else
    {
      int oldY = m_divider->getY();
      double ratio = double(oldY - r.getY()) / (m_lastKnownSize - m_dividerThickness);
      int deltaY = r.getY() + ratio * (r.getHeight() - m_dividerThickness) - oldY + 0.5;
      m_divider->setBounds (r.getX(), oldY + m_growthFraction * deltaY,
        r.getWidth(), m_dividerThickness);
      m_lastKnownSize = getHeight();
    }
  }

  adjustPanes();
}

void ResizingPanes::resizeStart()
{
  if (m_isVertical)
  {
    int minW =
      (m_leftChild ? m_leftChild->getMinimumWidth() : 0) +
      (m_rightChild ? m_rightChild->getMinimumWidth() : 0) +
      m_dividerThickness;
    setMinimumWidth (minW);
  }
  else
  {
    int minH =
      (m_leftChild ? m_leftChild->getMinimumHeight() : 0) +
      (m_rightChild ? m_rightChild->getMinimumHeight() : 0) +
      m_dividerThickness;
    setMinimumHeight (minH);
  }
}

void ResizingPanes::adjustPanes()
{
  Rectangle<int> b = getLocalBounds();
  Rectangle<int> r = b;

  if (m_isVertical)
  {
    m_left->setBounds (r.getX(), r.getY(), m_divider->getBounds().getX(), r.getHeight());
    m_right->setBounds (m_divider->getBounds().getRight(), r.getY(),
      r.getRight()-m_divider->getBounds().getRight(), r.getHeight());
  }
  else
  {
    m_left->setBounds (r.getX(), r.getY(), r.getWidth(), m_divider->getBounds().getY());
    m_right->setBounds (r.getX(), m_divider->getBounds().getBottom(), r.getWidth(),
      r.getBottom()-m_divider->getBounds().getBottom());
  }
}

}

}
