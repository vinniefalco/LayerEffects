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

#ifndef VF_UI_COLOUREDIMAGEMASKFACADE_H
#define VF_UI_COLOUREDIMAGEMASKFACADE_H

namespace Ui {

namespace Facade {

// Takes a single channel grayscale image and uses it as a
// mask for drawing with a solid color.

class ColouredImageMask : public Facade::Base
{
public:
  ColouredImageMask (Colour colour,
                     const Image& image,
                     Justification justification = Justification::centred,
                     Colour dropShadowColour = Colour::fromRGBA(0, 0, 0, 64));

  void paint (Graphics& g, const Rectangle<int>& bounds);

protected:
  void colourImageAt (Graphics& g, int x, int y, const Rectangle<int>& clip);

private:
  Image m_image;
  Colour m_colour;
  Colour m_dropShadowColour;
  Justification m_justification;

  JUCE_LEAK_DETECTOR(ColouredImageMask)
};

}

}

#endif