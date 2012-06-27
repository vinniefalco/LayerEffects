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

#define SHOW_BORDER 0
#define DISABLE_BORDER 0

const BorderSize <int> TransparentBorder::fullyOpaque =
  BorderSize <int> (0, 0, 0, 0);

const BorderSize <int> TransparentBorder::fullyTransparent =
  BorderSize <int> (maxBorderSize);

//------------------------------------------------------------------------------

TransparentBorder::OpaqueComponent::OpaqueComponent ()
{
  setOpaque (true);
  setPaintingIsUnclipped (true);
}

TransparentBorder::OpaqueComponent::~OpaqueComponent ()
{
}

void TransparentBorder::OpaqueComponent::paint (Graphics& g)
{
#if SHOW_BORDER
  g.setColour (Colours::red);
  g.fillRect (getLocalBounds ());
#endif
}

//------------------------------------------------------------------------------

TransparentBorder::TransparentBorder()
  : m_component (nullptr)
  , m_parent (nullptr)
  , m_visible (true)
{
}

TransparentBorder::~TransparentBorder()
{
  if (m_opaque)
  {
    jassert (m_component);
    m_component->removeComponentListener (this);
  }

  if (m_parent)
    m_parent->removeComponentListener (this);
}

void TransparentBorder::setComponent (Component *component,
                                      BorderSize <int> borderSize)
{
#if DISABLE_BORDER
  borderSize = fullyTransparent;
#endif

  // can only call this once
  jassert (m_component == 0 && component != 0);

  if (borderSize.isEmpty())
  {
    // no transparent border means component is opaque
    m_component = component;
    m_component->setOpaque (true);
  }
  else if (borderSize == fullyTransparent)
  {
    m_component = component;
  }
  else
  {
    m_opaque = new OpaqueComponent;
    m_opaque->addComponentListener (this);

    m_component = component;
    jassert (!m_component->isOpaque ());

    m_component->addComponentListener (this);
    m_opaque->setVisible (m_component->isVisible ());

    m_parent = m_component->getParentComponent();

    if (m_parent)
    {
      m_parent->addComponentListener (this); // to detect z-order changes
      m_parent->addChildComponent (m_opaque);
      m_opaque->toBehind (m_component);
      updateBounds ();
    }
  }

  m_borderSize = borderSize;
}

void TransparentBorder::setAlpha (float alpha)
{
  if (m_component != nullptr)
  {
    if (m_opaque != nullptr)
    {
      m_visible = alpha == 1.f;
      m_opaque->setVisible (m_visible && m_component->isVisible ());
    }
    else
    {
      m_component->setOpaque (alpha == 1);
    }
  }
}

bool TransparentBorder::isAttached ()
{
  return m_component && m_opaque && !m_borderSize.isEmpty();
}

void TransparentBorder::updateBounds()
{
  jassert (isAttached());

#if SHOW_BORDER
  m_opaque->setBounds (m_component->getBounds());
#else
  m_opaque->setBounds (m_borderSize.subtractedFrom (m_component->getBounds()));
#endif
}

void TransparentBorder::updateZOrder ()
{
  jassert (m_component);
  jassert (m_opaque);
  jassert (m_parent == m_component->getParentComponent());
  jassert (m_component->getParentComponent() == m_opaque->getParentComponent());

  int contentIndex = m_parent->getIndexOfChildComponent (m_component);
  int backgroundIndex = m_parent->getIndexOfChildComponent (m_opaque);
  if (backgroundIndex != contentIndex-1)
    m_opaque->toBehind (m_component);

}

void TransparentBorder::componentMovedOrResized (Component& component,
                                                          bool wasMoved,
                                                          bool wasResized)
{
  if (&component == m_component)
  {
    updateBounds();
  }
}

void TransparentBorder::componentVisibilityChanged (Component& component)
{
  if (&component == m_component)
  {
    jassert (isAttached());

    m_opaque->setVisible (m_visible && m_component->isVisible ());
  }
}
void TransparentBorder::componentChildrenChanged (Component& component)
{
  if (&component == m_parent)
  {
    // our z-order might have changed
    updateZOrder ();
  }
}

void TransparentBorder::componentParentHierarchyChanged (Component& component)
{
  if (&component == m_component)
  {
    jassert (isAttached());

    jassert (m_parent == m_opaque->getParentComponent()); 
    Component* newParent = m_component->getParentComponent();

    if (newParent != m_parent)
    {
      if (m_parent)
      {
        // remove the listener first so we dont get the callback
        m_parent->removeComponentListener (this);
        m_parent->removeChildComponent (m_opaque);
      }

      m_parent = newParent;

      if (m_parent)
      {
        int contentIndex = m_parent->getIndexOfChildComponent (m_component);
        m_parent->addChildComponent (m_opaque, contentIndex);
        // add the listener after so we dont get the callback
        m_parent->addComponentListener (this);
        updateBounds ();
      }
    }
  }
}

void TransparentBorder::componentBeingDeleted (Component& component)
{
  // how could the parent get deleted before the children?
  jassert (&component != m_parent);

  if (&component == m_component ||
      &component == m_opaque)
  {
    if (m_component)
    {
      m_component->removeComponentListener (this);
      m_component = 0;
    }

    if (m_parent)
    {
      m_parent->removeComponentListener (this);
      m_parent = 0;
    }

    // causes a crash
    //m_opaque = 0;
  }
}
