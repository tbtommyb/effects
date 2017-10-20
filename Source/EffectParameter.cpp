
/*
  ==============================================================================

    EffectParameter.cpp
    Created: 22 Sep 2017 9:46:03pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "EffectParameter.h"
#include "Control.h"

EffectParameter::EffectParameter(std::string label, int id) : val(0.0),
                                                              isOn(false)
{
  this->id = id;
  this->label = label;
};

EffectParameter::~EffectParameter() = default;

void EffectParameter::changeListenerCallback(ChangeBroadcaster* source)
{
  if (const Control* ctrl = dynamic_cast<const Control*>(source))
  {
    update(ctrl->val, ctrl->isOn);
  }
};

void EffectParameter::update(float val, bool isOn)
{
  this->val = val;
  this->isOn = isOn;
};
