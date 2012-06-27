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
