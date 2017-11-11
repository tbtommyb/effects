
/*
==============================================================================

    EffectParameter.h
    Created: 22 Sep 2017 9:46:03pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Control.h"

class EffectParameter : public ChangeListener
{
public:
  EffectParameter(std::string label, int id);
  ~EffectParameter();
  void changeListenerCallback(ChangeBroadcaster* source) override;
  std::string label;
  int id;
  float getVal();
  bool getIsOn();
  void setup(float sampleRate);
  void update(float val, bool isOn);
private:
  LinearSmoothedValue<float> val;
  bool isOn;
  float rampTimeInSeconds = 0.01;
};
