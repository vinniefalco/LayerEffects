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

Base::Base (Component* component,
            Facade::Base* facade,
            ReferenceCountedObjectPtr <Model::Base> model)
  : m_component (*component)
  , m_facade (facade)
  , m_model (model)
{
  m_facade->attach (model, this);
  m_model->addView (this);
  m_model->addListener (this);
}

Base::~Base ()
{
  m_model->removeListener (this);
  m_model->removeView (this);
}

Model::Base& Base::getModel ()
{
  return *m_model;
}

Facade::Base& Base::getFacade ()
{
  return *m_facade;
}
 
Component& Base::getComponent ()
{
  return m_component;
}

void Base::updateView ()
{
  m_component.repaint ();
}

void Base::onModelEnablement (Model::Base* model)
{
  m_component.setEnabled (model->isEnabled ());
}

}

}
