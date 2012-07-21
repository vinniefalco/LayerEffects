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

#ifndef __VF_UIBASE_VFHEADER__
#define __VF_UIBASE_VFHEADER__

namespace Model {

class Base;

//------------------------------------------------------------------------------

// Special Listeners that uses dynamic_cast to allow a derivation hierarchy 
//
// DEPRECATED
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
  void call (void (C::*f)()) const
  { callf <C> (vf::bind (f, vf::_1)); }

  template <class C, class T1>
  void call (void (C::*f)(T1), T1 t1) const
  { callf <C> (vf::bind (f, vf::_1, t1)); }

  template <class C, class T1, class T2>
  void call (void (C::*f)(T1, T2), T1 t1, T2 t2) const
  { callf <C> (vf::bind (f, vf::_1, t1, t2)); }

  template <class C, class T1, class T2, class T3>
  void call (void (C::*f)(T1, T2, T3), T1 t1, T2 t2, T3 t3) const
  { callf <C> (vf::bind (f, vf::_1, t1, t2, t3)); }

  template <class C, class T1, class T2, class T3, class T4>
  void call (void (C::*f)(T1, T2, T3, T4), T1 t1, T2 t2, T3 t3, T4 t4) const
  { callf <C> (vf::bind (f, vf::_1, t1, t2, t3, t4)); }

  template <class C, class T1, class T2, class T3, class T4, class T5>
  void call (void (C::*f)(T1, T2, T3, T4, T5), T1 t1, T2 t2, T3 t3, T4 t4, T5 t5) const
  { callf <C> (vf::bind (f, vf::_1, t1, t2, t3, t4, t5)); }

  template <class C, class T1, class T2, class T3, class T4, class T5, class T6>
  void call (void (C::*f)(T1, T2, T3, T4, T5, T6),
             T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6) const
  { callf <C> (vf::bind (f, vf::_1, t1, t2, t3, t4, t5, t6)); }

  template <class C, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
  void call (void (C::*f)(T1, T2, T3, T4, T5, T6, T7),
             T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7) const
  { callf <C> (vf::bind (f, vf::_1, t1, t2, t3, t4, t5, t6, t7)); }

  template <class C, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
  void call (void (C::*f)(T1, T2, T3, T4, T5, T6, T7, T8),
             T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8) const
  { callf <C> (vf::bind (f, vf::_1, t1, t2, t3, t4, t5, t6, t7, t8)); }

private:
  template <class ListenerSubClass, class Functor>
  void callf (Functor f) const
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

class Listener : public ListenerBase
{
public:
  virtual void onModelChanged (Model::Base* model) = 0;
  virtual void onModelEnablement (Model::Base* model) = 0;
};

//------------------------------------------------------------------------------

class Base : public ReferenceCountedObject, public Uncopyable
{
public:
  typedef ReferenceCountedObjectPtr <Base> Ptr;

  Base ();

  void addListener (Model::Listener* const listener);
  void removeListener (Model::Listener* const listener);

  bool isEnabled ();
  void setEnabled (bool enabled);

  void modelChanged ();

protected:
  Model::Listeners <ListenerBase> const& getListeners ();

private:
  Model::Listeners <ListenerBase> m_listeners;
  bool m_enabled;
};

}

//------------------------------------------------------------------------------

namespace Facade {

class Base
{
public:
  virtual void paint (Graphics& g, Rectangle <int> const& bounds);
  virtual void paintOverChildren (Graphics& g, Rectangle <int> const& bounds);
};

//------------------------------------------------------------------------------

class ConnectedEdges : public Base
{
public:
  ConnectedEdges ();
  bool isConnectedOnTop () const;
  bool isConnectedOnLeft () const;
  bool isConnectedOnBottom () const;
  bool isConnectedOnRight () const;
  void setConnectedEdgeFlags (int connectedEdgeFlags);

  // Returns a rounded rectangle with corners appropriate for the
  // connected edges. The frameThickness is used to inset the bounds.
  //
  // BAD! frameThickness and cornerRadius should not be parameters...
  //
  virtual Path const createConnectedFace (
    Rectangle <int> const& bounds,
    float frameThickness = 1.f,
    float cornerRadius = 2.5f);

private:
  int m_connectedEdgeFlags;
};

}

//------------------------------------------------------------------------------

namespace Control {

class Base
  : public Model::Listener
  , public AsyncUpdater
  , public Uncopyable
{
public:
  Base (Model::Base::Ptr model = nullptr);
  ~Base ();

  Model::Base* getModel ();

  void onModelChanged (Model::Base* model);
  void onModelEnablement (Model::Base* model);

private:
  void handleAsyncUpdate ();

private:
  Model::Base::Ptr const m_model;
};

}

#endif
