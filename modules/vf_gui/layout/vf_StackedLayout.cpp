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
