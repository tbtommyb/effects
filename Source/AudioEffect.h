/*
  ==============================================================================

    AudioEffect.h
    Created: 15 Oct 2017 9:40:33pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#pragma once

#include <map>
#include "../JuceLibraryCode/JuceHeader.h"
#include "Control.h"
#include "EffectParameter.h"

class AudioEffect
{
public:
  AudioEffect();
  ~AudioEffect();
  void addParameter(std::shared_ptr<EffectParameter> parameter);
  virtual void processBlock(const AudioSourceChannelInfo& bufferToFill);
  typedef std::map<std::string, std::shared_ptr<EffectParameter>> parameterMap;
  parameterMap& getParameters();
protected:
  parameterMap parameters;
};
