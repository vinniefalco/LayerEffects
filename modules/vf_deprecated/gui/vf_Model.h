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
    m_array.removeFirstMatchingValue (listener);
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