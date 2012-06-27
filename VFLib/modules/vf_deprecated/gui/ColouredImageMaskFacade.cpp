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
