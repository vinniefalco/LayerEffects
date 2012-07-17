//------------------------------------------------------------------------------
/*
  LayerEffects for JUCE

  Official project location:
  https://github.com/vinniefalco/LayerEffects

  ------------------------------------------------------------------------------

  License: MIT License (http://www.opensource.org/licenses/mit-license.php)
  Copyright (c) 2012 by Vinnie Falco

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
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/
//------------------------------------------------------------------------------

CImageSource::CImageSource (int id)
  : m_id (id)
  , m_imageIndex (-1)
{
  m_comboBox = new ComboBox ("Image");
  m_comboBox->addItem ("Vertical Blend", 1);
  m_comboBox->addItem ("Horizontal Blend", 2);
  addAndMakeVisible (m_comboBox);

  m_comboBox->addListener (this);
}

CImageSource::~CImageSource()
{
}

//------------------------------------------------------------------------------

void CImageSource::selectImage (int imageIndex)
{
  if (m_imageIndex != imageIndex)
  {
    m_imageIndex = imageIndex;

    m_comboBox->setSelectedId (m_imageIndex, true);

    buildImage ();
  }
}

void CImageSource::resized ()
{
  Rectangle <int> const bounds = getLocalBounds ();

  m_comboBox->setBounds (bounds.getX (), bounds.getY (), bounds.getWidth () - 24, 24);
}

void CImageSource::paint (Graphics& g)
{
  Rectangle <int> const bounds = getLocalBounds ();

  g.drawImageAt (m_image, 0, 24);
}

void CImageSource::buildImage ()
{
  switch (m_imageIndex)
  {
  case 1:
    {
      m_image = Image (Image::RGB, 256, 256, false);
      Graphics g (m_image);
      g.setGradientFill (ColourGradient (
        Colours::black, 0, 0, Colours::white, 0, 256, false));
      g.fillRect (0, 0, 256, 256);
    }
    break;

  case 2:
    {
      m_image = Image (Image::RGB, 256, 256, false);
      Graphics g (m_image);
      g.setGradientFill (ColourGradient (
        Colours::black, 0, 0, Colours::white, 256, 0, false));
      g.fillRect (0, 0, 256, 256);
    }
    break;

  default:
    m_image = Image ();
    break;
  }

  vf::componentNotifyParent (this, &CImageSource::Listener::onImageSourceSelect,
    m_id, m_image);

  repaint ();
}

void CImageSource::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
  selectImage (m_comboBox->getSelectedId ());
}
