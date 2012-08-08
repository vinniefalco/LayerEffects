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

COptionsTab::COptionsTab (String componentName)
  : Component (componentName)
  , m_pos (0, 0)
{
}

COptionsTab::~COptionsTab ()
{
  deleteAllChildren ();
}

void COptionsTab::buttonClicked (Button* button)
{
}

void COptionsTab::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
}

void COptionsTab::sliderValueChanged (Slider* slider)
{
}

void COptionsTab::onSolidColourChanged (CSolidColourPicker* picker)
{
}

//------------------------------------------------------------------------------

ComboBox* COptionsTab::createEmptyComboBox (String label)
{
  ComboBox* result;

  {
    Label* c = new Label;
    c->setText (label, false);
    c->setJustificationType (Justification::left);
    c->setBorderSize (0, 0);
    c->setBounds (
      getXStart (),
      m_pos.getY (),
      60, 20);
    addAndMakeVisible (c);
  }
  
  {
    ComboBox* c = new ComboBox ("");

    c->setBounds (64, m_pos.getY (), getWidth () - 60, 20);
    c->addListener (this);
    addAndMakeVisible (c);

    m_pos.setY (m_pos.getY () + c->getHeight () + getYGap ());

    result = c;
  }

  return result;
}

ComboBox* COptionsTab::createModeComboBox (String label, vf::BlendMode::Type mode)
{
  ComboBox* result;

  {
    Label* c = new Label;
    c->setText (label, false);
    c->setJustificationType (Justification::left);
    c->setBorderSize (0, 0);
    c->setBounds (
      getXStart (),
      m_pos.getY (),
      60, 20);
    addAndMakeVisible (c);
  }
  
  {
    ComboBox* c = new ComboBox ("Mode");
    addBlendModesToComboBox (c);

    c->setBounds (64, m_pos.getY (), getWidth () - 60, 20);
    c->addListener (this);
    addAndMakeVisible (c);

    m_pos.setY (m_pos.getY () + c->getHeight () + getYGap ());

    result = c;
  }

  result->setSelectedId (mode);

  return result;
}

Slider* COptionsTab::createPercentSlider (String label, double fraction, int maxPercent)
{
  Slider* result;

  {
    Label* c = new Label;
    c->setText (label, false);
    c->setJustificationType (Justification::top);
    c->setBorderSize (0, 0);
    c->setBounds (
      getXStart (),
      m_pos.getY (),
      getWidth (),
      getLabelHeight ());

    addAndMakeVisible (c);

    m_pos.setY (m_pos.getY () + c->getHeight () + getYGap ());
  }

  {
    Slider* c = new Slider (Slider::LinearHorizontal,  Slider::TextBoxRight);
    c->setTextValueSuffix ("%");
    c->setBounds (
      getXStart (),
      m_pos.getY (),
      getWidth (),
      getSliderHeight ());

    c->addListener (this);
    addAndMakeVisible (c);

    m_pos.setY (m_pos.getY () + c->getHeight () + getYGap ());

    result = c;
  }

  result->setRange (0, maxPercent, 1);
  result->setValue (fraction * 100);

  return result;
}

Slider* COptionsTab::createIntegerSlider (String label, int startValue, int endValue, int initialValue)
{
  Slider* result;

  {
    Label* c = new Label;
    c->setText (label, false);
    c->setJustificationType (Justification::top);
    c->setBorderSize (0, 0);
    c->setBounds (
      getXStart (),
      m_pos.getY (),
      getWidth (),
      getLabelHeight ());

    addAndMakeVisible (c);

    m_pos.setY (m_pos.getY () + c->getHeight () + getYGap ());
  }

  {
    Slider* c = new Slider (Slider::LinearHorizontal,  Slider::TextBoxRight);
    c->setRange (startValue, endValue, 1);
    c->setBounds (
      getXStart (),
      m_pos.getY (),
      getWidth (),
      getSliderHeight ());

    c->addListener (this);
    addAndMakeVisible (c);

    m_pos.setY (m_pos.getY () + c->getHeight () + getYGap ());

    result = c;
  }

  result->setValue (initialValue);

  return result;
}

ToggleButton* COptionsTab::createToggleButton (String label, bool initialValue)
{
  ToggleButton* result;

  {
    ToggleButton* c = new ToggleButton (label);
    c->setBounds (
      getXStart (),
      m_pos.getY (),
      getWidth (),
      getToggleButtonHeight ());

    c->addListener (this);
    addAndMakeVisible (c);

    m_pos.setY (m_pos.getY () + c->getHeight () + getYGap ());

    result = c;
  }

  result->setToggleState (initialValue, false);

  return result;
}

CSolidColourPicker* COptionsTab::createColourPicker (String label, Colour colour)
{
  CSolidColourPicker* result;

  {
    Label* c = new Label;
    c->setText (label, false);
    c->setJustificationType (Justification::left);
    c->setBorderSize (0, 0);
    c->setBounds (
      getXStart (),
      m_pos.getY (),
      60, 20);
    addAndMakeVisible (c);
  }
  
  {
    CSolidColourPicker* c = new CSolidColourPicker;

    c->setBounds (64, m_pos.getY (), getWidth () - 60, 20);
    c->addListener (this);
    addAndMakeVisible (c);

    m_pos.setY (m_pos.getY () + c->getHeight () + getYGap ());

    result = c;
  }

  result->setValue (colour);

  return result;
}

void COptionsTab::addBlendModesToComboBox (ComboBox* c)
{
  for (int i = 0; i < vf::BlendMode::getNumModes (); ++i)
  {
    vf::BlendMode::Type mode = vf::BlendMode::getMode (i);
    c->addItem (vf::BlendMode::getName (mode), mode);
  }
}
