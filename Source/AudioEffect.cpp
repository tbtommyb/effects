/*
  ==============================================================================

    AudioEffect.cpp
    Created: 15 Oct 2017 9:40:33pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "AudioEffect.h"
#include "EffectParameter.h"

AudioEffect::AudioEffect() : parameters() { }
AudioEffect::~AudioEffect() = default;

void AudioEffect::addParameter(std::shared_ptr<EffectParameter> parameter)
{
  parameters.insert({parameter->label, parameter});
}

void AudioEffect::processBlock(const AudioSourceChannelInfo& bufferToFill) { }

AudioEffect::parameterMap& AudioEffect::getParameters() {
  return parameters;
};
