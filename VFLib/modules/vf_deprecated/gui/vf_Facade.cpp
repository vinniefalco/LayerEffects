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

namespace Facade {

const BorderSize <int> Base::fullyOpaque =
  BorderSize <int> (0, 0, 0, 0);

const BorderSize <int> Base::fullyTransparent =
  BorderSize <int> (TransparentBorder::maxBorderSize);

Base::Base()
  : m_control (nullptr)
  , m_model (nullptr)
  , m_isEnabled (true)
{
}

Base::~Base()
{
  if (m_model != nullptr)
  {
    m_model->removeListener (this);
  }
}

Model::Base& Base::getModel ()
{
  vfassert (m_model != nullptr);
  return *m_model;
}

Control::Base& Base::getControl ()
{
  vfassert (m_control != nullptr);
  return *m_control;
}

Component& Base::getComponent ()
{
  return getControl().getComponent();
}

Rectangle <int> Base::getLocalBounds ()
{
  return getComponent().getLocalBounds();
}

void Base::setAlpha (float alpha)
{
  getComponent().setAlpha (alpha);
  m_transparentBorder.setAlpha (alpha);
}

void Base::paintFacade (Graphics& g)
{
  paint (g);
}

void Base::paint (Graphics& g)
{
  paint(g, getControl().getComponent().getLocalBounds());
}

void Base::paintOverChildren (Graphics& g)
{
  paintOverChildren (g, getControl().getComponent().getLocalBounds());
}

bool Base::isEnabled()
{
  return m_isEnabled;
}

void Base::setEnabled (bool isEnabled)
{
  m_isEnabled = isEnabled;
}

BorderSize<int> Base::getTransparency()
{
  return fullyTransparent;
}

void Base::paint (Graphics& g, const Rectangle<int>& bounds)
{
}

void Base::paintOverChildren (Graphics& g, const Rectangle<int>& bounds)
{
}

void Base::attach (Model::Base* model, Control::Base* control)
{
  vfassert (m_control == nullptr && m_model == nullptr);

  m_model = model;
  m_control = control;

  m_model->addListener (this);

  onAttach ();
}

void Base::onAttach ()
{
  m_transparentBorder.setComponent (&getComponent(),
                                    getTransparency());
}

void Base::onModelChanged (Model::Base* model)
{
  getComponent().repaint();
}

//------------------------------------------------------------------------------

Path Base::createFittedRoundRect (const Rectangle<int>& bounds,
                                      float frameThickness,
                                      float cornerRadius)
{
  Path path;
  path.addRoundedRectangle(
    bounds.getX() + frameThickness/2,
    bounds.getY() + frameThickness/2,
    bounds.getWidth() - frameThickness,
    bounds.getHeight() - frameThickness,
    cornerRadius);
  return path;
}

//------------------------------------------------------------------------------

#if 0
Empty::Empty()
{
}

BorderSize<int> Empty::getTransparency()
{
  return fullyTransparent;
}

void Empty::paint (Graphics& g, const Rectangle<int>& bounds)
{
  // nothing
}
#endif

}

}
