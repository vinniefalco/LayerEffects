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

#ifndef __VF_MODEL_VFHEADER__
#define __VF_MODEL_VFHEADER__

namespace Ui {

namespace Control {
class View;
}

namespace Model {

// Special Listeners that uses dynamic_cast to allow a derivation hierarchy 
//
template <class ListenerClass>
class Listeners
{
public:
  Listeners ()
  {
    m_array.ensureStorageAllocated (2);
  }

  void add (ListenerClass* const listener)
  {
    m_array.addIfNotAlreadyThere (listener);
  }

  void remove (ListenerClass* const listener)
  {
    m_array.removeValue (listener);
  }

  template <class C>
  void call (void (C::*f)())
  { callf <C> (vf::bind (f, vf::_1)); }

  template <class C, class T1>
  void call (void (C::*f)(T1), T1 t1)
  { callf <C> (vf::bind (f, vf::_1, t1)); }

  template <class C, class T1, class T2>
  void call (void (C::*f)(T1, T2), T1 t1, T2 t2)
  { callf <C> (vf::bind (f, vf::_1, t1, t2)); }

  template <class C, class T1, class T2, class T3>
  void call (void (C::*f)(T1, T2, T3), T1 t1, T2 t2, T3 t3)
  { callf <C> (vf::bind (f, vf::_1, t1, t2, t3)); }

  template <class C, class T1, class T2, class T3, class T4>
  void call (void (C::*f)(T1, T2, T3, T4), T1 t1, T2 t2, T3 t3, T4 t4)
  { callf <C> (vf::bind (f, vf::_1, t1, t2, t3, t4)); }

  template <class C, class T1, class T2, class T3, class T4, class T5>
  void call (void (C::*f)(T1, T2, T3, T4, T5), T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
  { callf <C> (vf::bind (f, vf::_1, t1, t2, t3, t4, t5)); }

  template <class C, class T1, class T2, class T3, class T4, class T5, class T6>
  void call (void (C::*f)(T1, T2, T3, T4, T5, T6),
             T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
  { callf <C> (vf::bind (f, vf::_1, t1, t2, t3, t4, t5, t6)); }

  template <class C, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
  void call (void (C::*f)(T1, T2, T3, T4, T5, T6, T7),
             T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
  { callf <C> (vf::bind (f, vf::_1, t1, t2, t3, t4, t5, t6, t7)); }

  template <class C, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
  void call (void (C::*f)(T1, T2, T3, T4, T5, T6, T7, T8),
             T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
  { callf <C> (vf::bind (f, vf::_1, t1, t2, t3, t4, t5, t6, t7, t8)); }

private:
  template <class ListenerSubClass, class Functor>
  void callf (Functor f)
  {
    for (int i = 0; i < m_array.size(); ++i)
    {
      // See if the listener derives from the
      // interface containing the member.
      ListenerSubClass* const listener =
        dynamic_cast <ListenerSubClass*> (m_array[i]);

      // Call the listener if it exposes the interface.
      if (listener != nullptr)
      {
        f (listener);
      }
    }
  }

private:
  Array <ListenerClass*> m_array;
};

//------------------------------------------------------------------------------

class ListenerBase
{
public:
  virtual ~ListenerBase () { }
};

// Model::Base abstracts a domain-specific object.
//
class Base : public ReferenceCountedObject, Uncopyable
{
public:
  class Listener : public ListenerBase
  {
  public:
    // Sent when any aspect of the model changes.
    //
    virtual void onModelChanged (Model::Base* model) { }

    // Sent when the enablement of the model changes.
    //
    virtual void onModelEnablement (Model::Base* model) { }
  };

public:
  Base();
  virtual ~Base();

  void addListener (ListenerBase* const listener);
  void removeListener (ListenerBase* const listener);

  bool isEnabled ();



  // LEGACY
  virtual const String getName (); // default: empty
  void addView (Control::View* view);
  void removeView (Control::View* view);
  void updateAllViews ();
  Array <Control::View*> m_views;



protected:
  Listeners <Listener> const& getListeners();

  // Call this to tell listeners that the model changed.
  // The default Facade behavior is to invalide the entire Component.
  //
  void modelChanged ();

public: // public because of DeckGridLockedEnabler
  void setEnabled (bool enabled);

protected:
  Listeners <ListenerBase> m_listeners;

private:
  bool m_enabled;
};

}

}

#endif