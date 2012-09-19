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

#ifndef LAYEREFFECTS_OPTIONS_HEADER
#define LAYEREFFECTS_OPTIONS_HEADER

/** Holds the options for layer graphics.
*/
struct Options
{
  typedef vf::LayerGraphics::Options::General General;
  typedef vf::FillStyle             Fill;
  typedef vf::DropShadowStyle       DropShadow;
  typedef vf::InnerShadowStyle      InnerShadow;
  typedef vf::OuterGlowStyle        OuterGlow;
  typedef vf::InnerGlowStyle        InnerGlow;
  typedef vf::BevelEmbossStyle      BevelEmboss;
  typedef vf::ColourOverlayStyle    ColourOverlay;
  typedef vf::GradientOverlayStyle  GradientOverlay;
  typedef vf::PatternOverlayStyle   PatternOverlay;
  typedef vf::StrokeStyle           Stroke;

  struct Listener
  {
    virtual ~Listener () { }
    virtual void onOptionsGeneral         (General options) { }
    virtual void onOptionsFill            (Fill options) { }
    virtual void onOptionsDropShadow      (DropShadow options) { }
    virtual void onOptionsInnerShadow     (InnerShadow options) { }
    virtual void onOptionsOuterGlow       (OuterGlow options) { }
    virtual void onOptionsInnerGlow       (InnerGlow options) { }
    virtual void onOptionsBevelEmboss     (BevelEmboss options) { }
    virtual void onOptionsColourOverlay   (ColourOverlay options) { }
    virtual void onOptionsGradientOverlay (GradientOverlay options) { }
    virtual void onOptionsPatternOverlay  (PatternOverlay options) { }
    virtual void onOptionsStroke          (Stroke options) { }
  };

  General         general;
  Fill            fill;
  DropShadow      dropShadow;
  InnerShadow     innerShadow;
  OuterGlow       outerGlow;
  InnerGlow       innerGlow;
  BevelEmboss     bevelEmboss;
  ColourOverlay   colourOverlay;
  GradientOverlay gradientOverlay;
  PatternOverlay  patternOverlay;
  Stroke          stroke;
};

#endif
