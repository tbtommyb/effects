/*
  ==============================================================================

    AudioEffect.cpp
    Created: 15 Oct 2017 9:40:33pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "AudioEffect.h"

AudioEffect::AudioEffect(std::shared_ptr<Control> ctrl) : ctrl(ctrl) { }
AudioEffect::~AudioEffect() = default;
void AudioEffect::processBlock(const AudioSourceChannelInfo& bufferToFill) { }
