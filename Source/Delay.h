/*
  ==============================================================================

    Delay.h
    Created: 11 Sep 2017 7:54:27pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#pragma once

#include "Control.h"
#include "AudioEffect.h"

class Delay : public AudioEffect
{
  public:
    Delay();
    ~Delay();
    void setupBlock(double sampleRate);
    void processBlock(const AudioSourceChannelInfo& bufferToFill) override;
  private:
    AudioBuffer<float> delayBuffer;
    int delayPosition = 0;
    float lineLength = 2.0;
};
