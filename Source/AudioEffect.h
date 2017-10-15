/*
  ==============================================================================

    AudioEffect.h
    Created: 15 Oct 2017 9:40:33pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#pragma once

#include "Control.h"

class AudioEffect
{
public:
  AudioEffect(std::shared_ptr<Control> ctrl);
  AudioEffect();
  ~AudioEffect();
  AudioEffect(const AudioEffect& other) = delete;
  AudioEffect(AudioEffect&& other) = delete;
  AudioEffect& operator=(const AudioEffect& other) = delete;
  AudioEffect& operator=(AudioEffect&& other) = delete;
  virtual void processBlock(AudioSourceChannelInfo& bufferToFill);
protected:
  std::shared_ptr<Control> ctrl;
};
