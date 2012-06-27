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
    m_array.removeValue (listener);
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
