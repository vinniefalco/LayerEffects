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

Static::Static (Facade::Base* facade, ReferenceCountedObjectPtr <Model::Base> model)
  : Base (this,
          facade,
          (model == nullptr) ? 
          ReferenceCountedObjectPtr <Model::Base> (new Model::Base) :
          ReferenceCountedObjectPtr <Model::Base> (model) )
{
}

Static::~Static ()
{
  // BAD!
  deleteAllChildren ();
}

void Static::paint (Graphics& g)
{
  //getFacade().paint (g, getLocalBounds());
  getFacade().paint (g);
}

void Static::paintOverChildren (Graphics& g)
{
  //getFacade().paintOverChildren (g, getLocalBounds());
  getFacade().paintOverChildren (g);
}

void Static::mouseDown (const MouseEvent& e)
{
  //setEnabled (!isEnabled ());
}

void Static::enablementChanged ()
{
  updateView ();
}

void Static::updateView ()
{
  bool enabled = isEnabled ();
  if (getFacade().isEnabled () != enabled)
  {
    getFacade().setEnabled (enabled);
  }
  repaint();
}

}

}
