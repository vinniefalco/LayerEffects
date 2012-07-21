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
