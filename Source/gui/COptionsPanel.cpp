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

COptionsPanel::COptionsPanel ()
  : m_panel (nullptr)
{
  setSize (240, 560);

  m_panels.add (new COptionsGeneralTab);  // 1
  m_panels.add (new COptionsFillTab);     // 2
  m_panels.add (new CDropShadowTab);      // 3
  m_panels.add (new CBackgroundPanel);    // 4
  m_panels.add (new CBackgroundPanel);    // 5
  m_panels.add (new CBackgroundPanel);    // 6
  m_panels.add (new CBevelEmbossTab);     // 7
  m_panels.add (new CBackgroundPanel);    // 8
  m_panels.add (new CBackgroundPanel);    // 9
  m_panels.add (new CGradientOverlayTab); // 10
  m_panels.add (new CBackgroundPanel);    // 11
  m_panels.add (new CBackgroundPanel);    // 12
  m_panels.add (new CBackgroundPanel);    // 13
  m_panels.add (new CBackgroundPanel);    // 14

  for (int i = 0; i < 14; ++i)
  {
    Component* c = m_panels [i];
    c->setBounds (0, 32, 240, 560-32);
    addChildComponent (c);
  }

  {
    ComboBox* c = new ComboBox;
    c->addItem ("General", 1);
    c->addItem ("Fill", 2);
    c->addItem ("Drop Shadow", 3);
    c->addItem ("Inner Shadow", 4);
    c->addItem ("Outer Glow", 5);
    c->addItem ("Inner Glow", 6);
    c->addItem ("Bevel & Emboss", 7);
    c->addItem ("Satin", 8);
    c->addItem ("Colour Overlay", 9);
    c->addItem ("Gradient Overlay", 10);
    c->addItem ("Pattern Overlay", 11);
    c->addItem ("Stroke", 12);
    c->addSeparator ();
    c->addItem ("Background", 13);
    c->addItem ("Foreground", 14);

    c->setBounds (4, 4, 232, 20);
    addAndMakeVisible (c);

    c->setSelectedId (1);
    c->addListener (this);
  }
}

COptionsPanel::~COptionsPanel ()
{
  deleteAllChildren ();
}

void COptionsPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
  if (m_panel != nullptr)
    m_panel->setVisible (false);

  m_panel = m_panels [comboBoxThatHasChanged->getSelectedId () - 1];

  m_panel->setVisible (true);
}
