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

#ifndef VF_DRAGANDDROPDATA_VFHEADER
#define VF_DRAGANDDROPDATA_VFHEADER

/*============================================================================*/
/**
    Flexible container for drag and drop data.

    This container is designed to be used with the Juce Component drag and drop
    mechanism. To use it, create a new, dynamic DragAndDropData object. Then
    call add() with one or more objects of class type. Components who are
    interested in the drag and drop information will safely convert the data
    passed from Juce to a DragAndDropData if possible.

    When a Component receives a DragAndDropData during a drag and drop operation,
    it calls find() one or more times to determine if the data contains a
    suitable object.

    DragAndDropData is:

    - Convenient. The helper class DragAndDropTarget works with DragAndDropData
      to manage these objects behind the scenes and hide some of the work.

    - Flexible: A DragAndDropData container can hold any objects which can go
      into a STL container (i.e. support copy construction and assignment).

    - Type-safe: objects placed into the container are disposed of correctly.
      If a ReferenceCountedObjectPtr is put inside, it does the right thing.

    In this example we will create a DragAndDropData for an image represented by
    a hyperlink. The container will hold two typed representations: an Image
    with the actual pixels, and a String for the URL.

    First we declare the data types:

    @code

    struct ImageDragData
    {
      Image image;
    };

    struct URLDragData
    {
      String url;
    };

    @endcode

    Now, create a container and put the data inside. Note that both the Image,
    and the String, are reference counted objects:

    @code

    ImageDragData imageData;
    imageData.image = new Image ();

    URLDragData urlData;
    urlData.url = "logo.jpg";

    DragAndDropData::Ptr dragData (new DragAndDropData);

    dragData.add (imageData);
    dragData.add (urlData);

    // Perform the drag
    DragAndDropContainer* container = findDragAndDropContainer (thisComponent);
    container->startDragging (dragData, ...);

    @endcode

    To modify a Component to receive the container, simply derive it from
    DragAndDropData::Target, then override the desired members:

    @code

    class MyComponent : public DragAndDropData::Target
    {
    public:
      void itemDropped (DragAndDropData const& data,
                        const SourceDetails& dragSourceDetails)
      {
        ImageDragData imageData;
        URLDragData urlData;

        // We prefer the image, see if it's there
        //
        if (data.find (&imageData))
        {
          // Great, work with imageData.image
        }
        // No image, look for a URL
        //
        else if (data.find (&urlData))
        {
          // We can use urlData.url now
        }
        else
        {
          // The container had nothing we are interested in
        }
      }
    }

    @endcode

    @ingroup vf_gui
*/
class DragAndDropData : public ReferenceCountedObject
{
public:
  typedef ReferenceCountedObjectPtr <DragAndDropData> Ptr;

  DragAndDropData ();

  ~DragAndDropData ();

  /** Add an object to the container.

      The container may not already have an object of this type.

      @param object   The object to add. Object must be copy constructible
                      and support assignment.
  */
  template <class Object>
  void add (Object const& object)
  {
    vfassert (! find <Object> ());
    m_items.push_back (*new StoredItem <Object> (object));
  }

  /** Retrieve an object from the container.

      Object must be copyable.

      @param[out] pResult  Receives a copy of the object if it exists in the
                           container.
      
      @return              \c true if the object was found.
  */
  template <class Object>
  bool find (Object* pResult = 0) const
  {
    bool found = false;

    for (Items::const_iterator iter = m_items.begin (); iter != m_items.end ();)
    {
      Item const* item = &(*iter++);
      StoredItem <Object> const* stored =
        dynamic_cast <StoredItem <Object> const*> (item);

      if (stored != 0)
      {
        if (pResult)
          *pResult = stored->getObject ();
        found = true;
        break;
      }
    }
    
    return found;
  }

public:
  /**
      DragAndDropTarget wrapper supporting the DragAndDropData container.

      Derive your Component from this instead of DragAndDropTarget, to receive
      drag notifications with a DragAndDropData.

      @see DragAndDropData

      @ingroup vf_gui
  */
  class Target : public DragAndDropTarget
  {
  public:
/** @param data The DragAndDropData.
        
    @param dragSourceDetails The original DragAndDropTarget::SourceDetails
      
    @return \c true if we want to receive further drag notifications.
*/
    virtual bool isInterestedInDragSource (DragAndDropData const& data,
                                           DragAndDropTarget::SourceDetails const& dragSourceDetails)
      { return false; }

/** @param data The DragAndDropData.
        
    @param dragSourceDetails The original DragAndDropTarget::SourceDetails
*/
    virtual void itemDragEnter (DragAndDropData const& data,
                                DragAndDropTarget::SourceDetails const& dragSourceDetails) { }

/** @param data The DragAndDropData.
        
    @param dragSourceDetails The original DragAndDropTarget::SourceDetails
*/
    virtual void itemDragMove (DragAndDropData const& data,
                               DragAndDropTarget::SourceDetails const& dragSourceDetails) { }

/** @param data The DragAndDropData.
        
    @param dragSourceDetails The original DragAndDropTarget::SourceDetails
*/
    virtual void itemDragExit (DragAndDropData const& data,
                               DragAndDropTarget::SourceDetails const& dragSourceDetails) { }

/** @param data The DragAndDropData.
        
    @param dragSourceDetails The original DragAndDropTarget::SourceDetails
*/
    virtual void itemDropped (DragAndDropData const& data,
                              DragAndDropTarget::SourceDetails const& dragSourceDetails) { }

  private:
    bool isInterestedInDragSource (const SourceDetails& dragSourceDetails);
    void itemDragEnter (const SourceDetails& dragSourceDetails);
    void itemDragMove (const SourceDetails& dragSourceDetails);
    void itemDragExit (const SourceDetails& dragSourceDetails);
    void itemDropped (const SourceDetails& dragSourceDetails);
  };

private:
  class Item;
  typedef List <Item> Items;

  class Item : public Items::Node
  {
  public:
    // Make sure every object has a vtable so we can use dynamic_cast
    virtual ~Item() { }
  };

  template <class Object>
  class StoredItem : public Item
  {
  public:
    explicit StoredItem (Object const& object)
      : m_object (object)
    {
    }

    Object const& getObject () const { return m_object; }
  
  private:
    Object m_object;
  };

  Items m_items;
};

#endif
