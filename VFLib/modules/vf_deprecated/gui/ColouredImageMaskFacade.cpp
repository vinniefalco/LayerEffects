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

namespace Ui {

namespace Facade {

ColouredImageMask::ColouredImageMask (Colour colour,
                                      const Image& image,
                                      Justification justification,
                                      Colour dropShadowColour)
  : m_image (image)
  , m_colour (colour)
  , m_dropShadowColour (dropShadowColour)
  , m_justification (justification)
{
}

static Rectangle<int> justified (Justification justification,
                                 const Rectangle<int>& space,
                                 const Rectangle<int>& item)
{
  int itemX = item.getX();
  int itemY = item.getY();
  int itemW = item.getWidth();
  int itemH = item.getHeight();

  justification.applyToRectangle (itemX, itemY, itemW, itemH,
    space.getX(), space.getY(), space.getWidth(), space.getHeight());

  return Rectangle<int> (itemX, itemY, itemW, itemH);
}

void ColouredImageMask::paint (Graphics& g, const Rectangle<int>& bounds)
{
  if (!m_dropShadowColour.isTransparent())
  {
    Rectangle<int> r (0, 0, m_image.getWidth(), m_image.getHeight());
    r = justified (m_justification, bounds, r).translated (1, 1);
    g.setColour (m_dropShadowColour);
    colourImageAt (g, r.getX(), r.getY(), bounds);
  }  

  {
    Rectangle<int> r (0, 0, m_image.getWidth(), m_image.getHeight());
    r = justified (m_justification, bounds, r);
    g.setColour (m_colour);
    colourImageAt (g, r.getX(), r.getY(), bounds);
  }
}

void ColouredImageMask::colourImageAt (Graphics& g,
                                       int x, int y,
                                       const Rectangle<int>& clip)
{
  // calc visible portion of image
  Rectangle<int> r;
  r.setX (jmax (clip.getX() - x, 0));
  r.setY (jmax (clip.getY() - y, 0));
  r.setRight (jmin ( clip.getRight()-x , m_image.getWidth()));
  r.setBottom (jmin ( clip.getBottom()-y , m_image.getHeight()));

  if (!r.isEmpty())
  {
    g.drawImage (m_image, x, y, r.getWidth(), r.getHeight(),
      r.getX(), r.getY(), r.getWidth(), r.getHeight(), true);
  }
}

}

}
