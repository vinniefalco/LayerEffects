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

//------------------------------------------------------------------------------

/** Editor for displaying and manipulating ContourCurve control points.
*/
class CContourEditor
  : public Component
{
private:
  struct ControlPoint
  {
    bool corner; 
    float in;
    float out;
  };

  ContourCurve m_contour;
  int m_npt;
  ControlPoint m_pt [10];
  ControlPoint* m_edit;

public:
  explicit CContourEditor (ContourCurve contour = ContourCurve ())
    : m_contour (contour)
    , m_npt (2)
    , m_edit (nullptr)
  {
    m_pt [0].corner = true;
    m_pt [0].in = 0;
    m_pt [0].out = 0;
    m_pt [1].corner = true;
    m_pt [1].in = 1;
    m_pt [1].out = 1;
  }

  void paint (Graphics& g)
  {
    Rectangle <int> const r = getLocalBounds ();

    g.setColour (Colours::white);
    g.fillRect (r);

    g.setColour (Colours::black);
    g.drawRect (r);

    paintGrid (g);
    paintControlPoints (g);
  }

  void paintGrid (Graphics& g)
  {
    Rectangle <int> const r = getLocalBounds ();
    for (int i = 1; i < 10; ++i)
    {
      int const x = i * (r.getWidth () / 10);
      int const y = i * (r.getHeight () / 10);

      if (i == 5)
        g.setColour (Colours::black.withAlpha (0.5f));
      else
        g.setColour (Colours::black.withAlpha (0.25f));

      g.drawLine (x + r.getX () + 0.5f, float (r.getY ()), x + r.getX () + 0.5f, float (r.getBottom ()));
      g.drawLine (float (r.getX ()), y + r.getY () + 0.5f, float (r.getRight ()), y + r.getY () + 0.5f);
    }
  }

  void paintControlPoint (Graphics& g, ControlPoint const& cp, bool isSelected)
  {
    Rectangle <int> r = getLocalBounds ();

    float radius = 2.f;
    float x = r.getX () + cp.in * r.getWidth ();
    float y = r.getBottom () - cp.out * r.getHeight ();

    Rectangle <float> area (x - radius, y - radius, 2 * radius, 2 * radius);

    g.setColour (Colours::black);
    g.fillEllipse (area);
  }

  void paintControlPoints (Graphics& g)
  {
    for (int i = 0; i < m_npt; ++i)
    {
      ControlPoint const& cp (m_pt [i]);

      paintControlPoint (g, cp, m_edit == &cp);
    }
  }

  void mouseDown (MouseEvent const& e)
  {
    m_edit = &m_pt [0];
  }

  void mouseDrag (MouseEvent const& e)
  {
    if (m_edit != nullptr)
    {
      Rectangle <int> const bounds = getLocalBounds ();

      int x = jlimit (0, bounds.getWidth (), e.getPosition ().getX () - bounds.getX ());
      int y = jlimit (0, bounds.getHeight (), e.getPosition ().getY () - bounds.getY ());

      m_edit->in = float (x) / bounds.getWidth ();
      m_edit->out = 1.f - (float (y) / bounds.getHeight ());

      repaint ();
    }
  }

  void mouseUp (MouseEvent const& e)
  {
    m_edit = nullptr;
  }
};

//------------------------------------------------------------------------------

class CContourCurveEditor
  : public Component
  , public ButtonListener
{
private:
  ComboBox* m_presetCombo;
  CContourEditor* m_curveEditor;
  TextEditor* m_inEdit;
  TextEditor* m_outEdit;
  ToggleButton* m_cornerCheck;
  Button* m_btnOK;
  Button* m_btnReset;
  Button* m_btnLoad;
  Button* m_btnSave;
  Button* m_btnNew;

public:
  CContourCurveEditor ()
  {
    m_presetCombo = new ComboBox;
    m_presetCombo->setBounds (73, 10, 217, 22);
    addAndMakeVisible (m_presetCombo);

    m_curveEditor = new CContourEditor;
    m_curveEditor->setBounds (20, 62, 260, 260);
    addAndMakeVisible (m_curveEditor);

    {
      Label* c = new Label (String::empty, "In:");
      c->setBounds (20, 332, 48, 20);
      c->setJustificationType (Justification::right);
      addAndMakeVisible (c);
    }

    m_inEdit = new TextEditor;
    m_inEdit->setBounds (73, 332, 67, 20);
    addAndMakeVisible (m_inEdit);

    {
      Label* c = new Label (String::empty, "Out:");
      c->setBounds (20, 364, 48, 20);
      c->setJustificationType (Justification::right);
      addAndMakeVisible (c);
    }

    m_outEdit = new TextEditor;
    m_outEdit->setBounds (73, 364, 67, 20);
    addAndMakeVisible (m_outEdit);

    m_cornerCheck = new ToggleButton ("Corner");
    m_cornerCheck->setBounds (166, 347, 120, 24);
    addAndMakeVisible (m_cornerCheck);

    m_btnOK = new TextButton ("OK");
    m_btnOK->setBounds (306, 11, 76, 18);
    m_btnOK->addListener (this);
    addAndMakeVisible (m_btnOK);

    m_btnReset = new TextButton ("Reset");
    m_btnReset->setBounds (306, 39, 76, 18);
    m_btnReset->addListener (this);
    addAndMakeVisible (m_btnReset);

    m_btnLoad = new TextButton ("Load...");
    m_btnLoad->setBounds (306, 67, 76, 18);
    m_btnLoad->addListener (this);
    addAndMakeVisible (m_btnLoad);

    m_btnSave = new TextButton ("Save...");
    m_btnSave->setBounds (306, 105, 76, 18);
    m_btnSave->addListener (this);
    addAndMakeVisible (m_btnSave);

    m_btnNew = new TextButton ("New...");
    m_btnNew->setBounds (306, 133, 76, 18);
    m_btnNew->addListener (this);
    addAndMakeVisible (m_btnNew);

    setSize (393, 406);
  }

  ~CContourCurveEditor ()
  {
    deleteAllChildren ();
  }

  void paint (Graphics& g)
  {
    g.fillAll (Colours::lightgrey);
  }

  void buttonClicked (Button* button)
  {
    if (button == m_btnOK)
    {
      getTopLevelComponent ()->exitModalState (0);
    }
    else if (button == m_btnReset)
    {
    }
    else if (button == m_btnLoad)
    {
    }
    else if (button == m_btnSave)
    {
    }
    else if (button == m_btnNew)
    {
    }
  }
};

//------------------------------------------------------------------------------

class CContourPickerDialog
  : public DocumentWindow
{
private:
public:
  CContourPickerDialog ()
    : DocumentWindow ("Edit Contour", Colours::grey, DocumentWindow::closeButton, true)
  {
    CContourCurveEditor* c = new CContourCurveEditor;
    setContentOwned (c, true);

    centreWithSize (getWidth(), getHeight());
    setVisible (true);
  }

  void closeButtonPressed ()
  {
    exitModalState (0);
  }
};

//------------------------------------------------------------------------------

CContourPicker::CContourPicker ()
{
}

CContourPicker::~CContourPicker ()
{
}

void CContourPicker::addListener (Listener* listener)
{
  m_listeners.add (listener);
}

void CContourPicker::removeListener (Listener* listener)
{
  m_listeners.remove (listener);
}

void CContourPicker::paint (Graphics& g)
{
  Rectangle <int> const r = getLocalBounds ();

  g.setColour (Colours::white);
  g.fillRect (r.reduced (1, 1));
  g.setColour (Colours::black);
  g.drawRect (r);
}

void CContourPicker::mouseDown (MouseEvent const& e)
{
  CContourPickerDialog* w = new CContourPickerDialog;
  w->enterModalState (true, nullptr, true);
}

