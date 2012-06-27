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

#ifndef VF_UI_STATIC_H
#define VF_UI_STATIC_H

namespace Ui {

//------------------------------------------------------------------------------

// A Static control has appearance but no model and no user input.
// This is useful for things like background panels and what not.

namespace Control {

class Static
  : public Component // must come first
  , public Control::Base
{
public:
  Static (Facade::Base* facade,
          ReferenceCountedObjectPtr <Model::Base> model = nullptr);
  ~Static ();

  void paint (Graphics& g);
  void paintOverChildren (Graphics& g);

protected:
  void mouseDown (const MouseEvent& e);
  void enablementChanged ();
  void updateView ();

private:
};

//------------------------------------------------------------------------------

template<class Facade>
class StaticType : public Static
{
public:
  explicit StaticType (Facade* facade)
    : Static (facade)
    , m_facade (facade)
  {
  }

  Facade& getFacade ()
  {
    return *m_facade;
  }

private:
  Facade* m_facade;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StaticType)
};

}

}

#endif