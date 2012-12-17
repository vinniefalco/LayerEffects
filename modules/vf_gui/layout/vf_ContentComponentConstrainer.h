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

#ifndef VF_CONTENTCOMPONENTCONSTRAINER_VFHEADER
#define VF_CONTENTCOMPONENTCONSTRAINER_VFHEADER

/*============================================================================*/
/**
    Component constraint adjuster.

    When using a ComponentBoundsConstrainer, the size limits include variable
    elements such as the title bar, native window, menu bar, or window border.
    By using this shim, which which goes between your constrainer and a
    ResizableWindow or ResizableWindow-derived class, all specified constraints
    will be relative to the size of the content component itself and excluding
    window decorations.

    If you set a minimum size with your constrainer, the content component will
    be constrained to exactly the desired dimensions.

    The class is very easy to use. First put a constrainer on your window or use
    the function ResizableWindow::setResizeLimits(), and then just call
    ContentComponentConstrainer::attachTo (yourResizableWindow). It will take
    care of deleting itself and handle everything for you, like this:

    @ingroup vf_gui
*/
class ContentComponentConstrainer
  : private ComponentBoundsConstrainer
  , private ComponentListener
{
public:
  /** Attach a new ContentComponentConstrainer to a window.

      @param resizableWindow The window to attach to.
  */
  static void attachTo (ResizableWindow* resizableWindow)
  {
    ContentComponentConstrainer* contentConstrainer =
      new ContentComponentConstrainer (resizableWindow);
    resizableWindow->addComponentListener (contentConstrainer);
  }

private:
  ContentComponentConstrainer (ResizableWindow* resizableWindow)
   : m_resizableWindow (resizableWindow)
   , m_originalConstrainer (0)
  {
    // If you aren't using a custom constrainer, then at least put a
    // constraint on your ResizableWindow using ResizableWindow::setResizeLimits
    // so that it gets the defaultConstrainer.
    m_originalConstrainer = m_resizableWindow->getConstrainer();
    jassert (m_originalConstrainer); // must exist

    m_resizableWindow->setConstrainer (this);
    m_resizableWindow->addComponentListener (this);
  }

  void resizeStart()
  {
    m_originalConstrainer->resizeStart();
    copyConstraints (*m_originalConstrainer);
    adjustConstraints();
  }

  void resizeEnd()
  {
    m_originalConstrainer->resizeEnd();
  }

  void applyBoundsToComponent (Component* component,
                               const Rectangle<int>& bounds)
  {
    m_originalConstrainer->applyBoundsToComponent (component, bounds);
  }

  void copyConstraints (ComponentBoundsConstrainer& from)
  {
    setMinimumWidth (from.getMinimumWidth());
    setMaximumWidth (from.getMaximumWidth());
    setMinimumHeight (from.getMinimumHeight());
    setMaximumHeight (from.getMaximumHeight());
    setFixedAspectRatio (from.getFixedAspectRatio());

    int minimumWhenOffTheTop;
    int minimumWhenOffTheLeft;
    int minimumWhenOffTheBottom;
    int minimumWhenOffTheRight;

    minimumWhenOffTheTop = from.getMinimumWhenOffTheTop();
    minimumWhenOffTheLeft = from.getMinimumWhenOffTheLeft();
    minimumWhenOffTheBottom = from.getMinimumWhenOffTheBottom();
    minimumWhenOffTheRight = from.getMinimumWhenOffTheRight();

    setMinimumOnscreenAmounts (minimumWhenOffTheTop,
                               minimumWhenOffTheLeft,
                               minimumWhenOffTheBottom,
                               minimumWhenOffTheRight);
  }

  static int addWithoutOverflow (int a, int b)
  {
    if (a < (0x7ffffff-b))
      return a+b;
    else
      return 0x7fffffff;
  }

  // adjusts the current constraints to take into account decorations
  void adjustConstraints()
  {
    BorderSize<int> peerFrameBorder = m_resizableWindow->getPeer()->getFrameSize();
    BorderSize<int> contentCompBorder = m_resizableWindow->getContentComponentBorder();
    
    int extraWidth = peerFrameBorder.getLeftAndRight() + contentCompBorder.getLeftAndRight();
    int extraHeight = peerFrameBorder.getTopAndBottom() + contentCompBorder.getTopAndBottom();

    setMinimumHeight (m_originalConstrainer->getMinimumHeight() + extraHeight);
    setMaximumHeight (addWithoutOverflow (m_originalConstrainer->getMaximumHeight(), extraHeight));
    setMinimumWidth (m_originalConstrainer->getMinimumWidth() + extraWidth);
    setMaximumWidth (addWithoutOverflow (m_originalConstrainer->getMaximumWidth(), extraWidth));
  }

  void componentBeingDeleted (Component& component)
  {
    delete this;
  }

private:
  ResizableWindow* m_resizableWindow;
  ComponentBoundsConstrainer* m_originalConstrainer;
};

#endif
