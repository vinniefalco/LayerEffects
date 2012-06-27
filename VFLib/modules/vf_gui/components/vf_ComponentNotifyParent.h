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

#ifndef VF_COMPONENTNOTIFYPARENT_VFHEADER
#define VF_COMPONENTNOTIFYPARENT_VFHEADER

/*============================================================================*/
/**
    Notify some parent of a Component.

    This class functor will ascend the chain of parent components and
    call a member function on the first parent it finds that exposes a
    defined interface. A Component exposes the interface by deriving from the
    class containing the member function of interest. The implementation uses
    dynamic_cast to determine if the Component is eligible, so the interface
    must have a virtual table.

    This provides robust assistance for enforcing separation of concerns, and
    decentralizing program logic into only the areas that need it.

    In this example we will implement a ToggleButton which switches a window
    between basic and advanced modes:

    @code

    // Interface for a window that has basic and advanced modes:

    struct TwoModeWindow
    {
      virtual void onModeChanged (bool isAdvanced) = 0;
    };

    // A ToggleButton that switches between basic and advanced modes

    class AdvancedModeToggleButton : public ToggleButton
    {
    public:
      AdvancedModeToggleButton (String buttonText) : ToggleButton (buttonText)
      {
        setClickingTogglesState (true);
      }

      void clicked ()
      {
        // Inform a parent that the window mode was changed

        componentNotifyParent (this,
                               &TwoModeWindow::onModeChanged,
                               getToggleState ());
      }
    };

    @endcode

    These are some of the benefits of using this system:

    - A Component sending a notification doesn't need to know about
      the recipient.

    - A Component doesn't need to know where it is in the hierarchy
      of components in the window. You can add, remove, or reparent
      controls without breaking anything.
      
    - Child and parent components support sending and receiving notifications
      for multiple interfaces very easily.

    @ingroup vf_gui
*/
class componentNotifyParent
{
public:
  /** Call a member function on some parent of a Component.

      @param c  The Component whose parent hierarchy we will search.
      
      @param f  Any non-static class member to call. This may be followed by up
                to eight parameters. The parameters must match the signature of
                the specified function.
  */
  template <class C>
  componentNotifyParent (Component* c, void (C::*f)())
  { call <C> (c, vf::bind (f, vf::_1)); }

  template <class C, class T1>
  componentNotifyParent (Component* c, void (C::*f)(T1), T1 t1)
  { call <C> (c, vf::bind (f, vf::_1, t1)); }

  template <class C, class T1, class T2>
  componentNotifyParent (Component* c, void (C::*f)(T1, T2), T1 t1, T2 t2)
  { call <C> (c, vf::bind (f, vf::_1, t1, t2)); }

  template <class C, class T1, class T2, class T3>
  componentNotifyParent (Component* c, void (C::*f)(T1, T2, T3), T1 t1, T2 t2, T3 t3)
  { call <C> (c, vf::bind (f, vf::_1, t1, t2, t3)); }

  template <class C, class T1, class T2, class T3, class T4>
  componentNotifyParent (Component* c, void (C::*f)(T1, T2, T3, T4), T1 t1, T2 t2, T3 t3, T4 t4)
  { call <C> (c, vf::bind (f, vf::_1, t1, t2, t3, t4)); }

  template <class C, class T1, class T2, class T3, class T4, class T5>
  componentNotifyParent (Component* c, void (C::*f)(T1, T2, T3, T4, T5), T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
  { call <C> (c, vf::bind (f, vf::_1, t1, t2, t3, t4, t5)); }

  template <class C, class T1, class T2, class T3, class T4, class T5, class T6>
  componentNotifyParent (Component* c, void (C::*f)(T1, T2, T3, T4, T5, T6),
             T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
  { call <C> (c, vf::bind (f, vf::_1, t1, t2, t3, t4, t5, t6)); }

  template <class C, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
  componentNotifyParent (Component* c, void (C::*f)(T1, T2, T3, T4, T5, T6, T7),
             T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
  { call <C> (c, vf::bind (f, vf::_1, t1, t2, t3, t4, t5, t6, t7)); }

  template <class C, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
  componentNotifyParent (Component* c, void (C::*f)(T1, T2, T3, T4, T5, T6, T7, T8),
             T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
  { call <C> (c, vf::bind (f, vf::_1, t1, t2, t3, t4, t5, t6, t7, t8)); }

private:
  template <class Interface, class Functor>
  void call (Component* component, Functor const& f)
  {
    component = component->getParentComponent();
    
    while (component != nullptr)
    {
      Interface* const object = dynamic_cast <Interface*> (component);

      if (object != nullptr)
      {
        f (object);
        break;
      }

      component = component->getParentComponent();
    }
  }
};

#endif
