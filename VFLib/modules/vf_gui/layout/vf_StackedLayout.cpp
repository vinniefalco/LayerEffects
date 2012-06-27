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

StackedLayout::StackedLayout (bool vertical,
                              BorderSize<int> borderSize,
                              int gapSize)
  : m_vertical (vertical)
  , m_active (false)
  , m_borderSize (borderSize)
  , m_gapSize (gapSize)
{
}

StackedLayout::~StackedLayout()
{
  for (size_t i = 0; i < m_bands.size(); ++i)
    delete m_bands[i].component;
}

void StackedLayout::addBand (Component* component)
{
  addAndMakeVisible (component);
  component->addComponentListener (this);
  Item item;
  item.component = component;
  item.resizableChild = dynamic_cast<vf::ResizableChild*>(component);
  m_bands.push_back (item);
}

void StackedLayout::setBandVisible (int index, bool visible)
{
  Component* c = m_bands[index].component;
  
  c->setVisible (visible);
}

void StackedLayout::recalculateLayout ()
{
  if (m_active)
  {
    if (m_vertical)
    {
      const Rectangle <int> bounds = getLocalBounds ();

      int totalSize = m_borderSize.getTop();
      int lastSize = 0;

      for (size_t i = 0; i < m_bands.size(); ++i)
      {
        Component* c = m_bands[i].component;
        if (c->isVisible ())
        {
          lastSize = c->getHeight ();
          totalSize += lastSize;
        }
      }

      totalSize += m_borderSize.getBottom ();

      Component* lastComponent = 0;
      Rectangle<int> lastBounds;
      lastBounds.setX (bounds.getX() + m_borderSize.getLeft());
      lastBounds.setRight (bounds.getRight() - m_borderSize.getRight());
      lastBounds.setY (bounds.getY() + m_borderSize.getTop());

      for (size_t i = 0; i < m_bands.size(); ++i)
      {
        Component* c = m_bands[i].component;
        if (c->isVisible ())
        {
          if (lastComponent)
          {
            lastBounds.setHeight (lastComponent->getHeight());
            lastComponent->setBounds (lastBounds);
          
            lastBounds.setY (lastBounds.getBottom() + m_gapSize);
          }

          lastComponent = c;
        }
      }

      if (lastComponent)
      {
        lastBounds.setBottom (bounds.getBottom() - m_borderSize.getBottom());
        lastComponent->setBounds (lastBounds);
      }
    }
    else
    {
      const Rectangle <int> bounds = getLocalBounds ();

      int totalSize = m_borderSize.getLeft ();
      int lastSize = 0;

      for (size_t i = 0; i < m_bands.size (); ++i)
      {
        Component* c = m_bands[i].component;
        if (c->isVisible ())
        {
          lastSize = c->getWidth ();
          totalSize += lastSize;
        }
      }

      totalSize += m_borderSize.getBottom ();

      Component* lastComponent = 0;
      Rectangle <int> lastBounds;
      lastBounds.setY (bounds.getY () + m_borderSize.getTop ());
      lastBounds.setBottom (bounds.getBottom () - m_borderSize.getBottom ());
      lastBounds.setX (bounds.getX() + m_borderSize.getLeft ());

      for (size_t i = 0; i < m_bands.size(); ++i)
      {
        Component* c = m_bands[i].component;
        
        if (c->isVisible ())
        {
          if (lastComponent)
          {
            lastBounds.setWidth (lastComponent->getWidth ());
            lastComponent->setBounds (lastBounds);
          
            lastBounds.setX (lastBounds.getRight() + m_gapSize);
          }

          lastComponent = c;
        }
      }

      if (lastComponent)
      {
        lastBounds.setRight (bounds.getRight() - m_borderSize.getRight ());
        lastComponent->setBounds (lastBounds);
      }
     }
  }
}

void StackedLayout::activateStackedLayout ()
{
#if 1
//  triggerAsyncUpdate ();
#else
  m_active = true;
  recalculateLayout ();
#endif
}

void StackedLayout::resized ()
{
  recalculateLayout ();
}

void StackedLayout::resizeStart ()
{
  int minW = 0;
  int minH = 0;

  if (m_vertical)
  {
    for (size_t i = 0; i < m_bands.size(); ++i)
    {
      ResizableChild* c = m_bands[i].resizableChild;
      if (c)
        c->resizeStart ();
    }

    for (size_t i = 0; i < m_bands.size(); ++i)
    {
      ResizableChild* c = m_bands[i].resizableChild;
      if (c)
        c->resizeStart ();
    }

    minH = m_borderSize.getTop();
    int lastH = -1;

    for (size_t i = 0; i < m_bands.size(); ++i)
    {
      Component* c = m_bands[i].component;
      if (c->isVisible ())
      {
        if (lastH != -1)
        {
          minH += m_gapSize + lastH;
        }

        ResizableChild* rc = m_bands[i].resizableChild;
        if (rc)
        {
          lastH = rc->getMinimumHeight ();

          minW = jmax (minW, rc->getMinimumWidth ());
        }
        else
        {
          lastH = m_bands[i].component->getHeight ();
        }
      }
    }

    if (lastH != -1)
    {
      minH += lastH + m_borderSize.getBottom ();
    }
  }
  else
  {
    for (size_t i = 0; i < m_bands.size(); ++i)
    {
      ResizableChild* c = m_bands[i].resizableChild;
      if (c)
        c->resizeStart ();
    }

    for (size_t i = 0; i < m_bands.size(); ++i)
    {
      ResizableChild* c = m_bands[i].resizableChild;
      if (c)
        c->resizeStart ();
    }

    minW = m_borderSize.getLeft ();
    int lastH = -1;

    for (size_t i = 0; i < m_bands.size(); ++i)
    {
      Component* c = m_bands[i].component;
      if (c->isVisible ())
      {
        if (lastH != -1)
        {
          minH += m_gapSize + lastH;
        }

        ResizableChild* rc = m_bands[i].resizableChild;
        if (rc)
        {
          lastH = rc->getMinimumWidth ();

          minH = jmax (minW, rc->getMinimumHeight ());
        }
        else
        {
          lastH = m_bands[i].component->getWidth ();
        }
      }
    }

    if (lastH != -1)
    {
      minW += lastH + m_borderSize.getRight ();
    }
  }

  setMinimumWidth (minW);
  setMinimumHeight (minH);
}

void StackedLayout::componentMovedOrResized (Component& component,
                                             bool wasMoved,
                                             bool wasResized)
{
  triggerAsyncUpdate ();
}

void StackedLayout::componentVisibilityChanged (Component& component)
{
  triggerAsyncUpdate ();
}

void StackedLayout::componentBeingDeleted (Component& component)
{
  triggerAsyncUpdate ();
}

void StackedLayout::handleAsyncUpdate ()
{
  m_active = true;
  recalculateLayout ();
}
