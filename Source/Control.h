/*
==============================================================================

    Control.h
    Created: 22 Sep 2017 9:46:03pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Control : public ChangeBroadcaster
{
public:
  Control(int id);
  ~Control();
  void update(float val, bool isOn);
  int id;
  float val;
  bool isOn;
};
