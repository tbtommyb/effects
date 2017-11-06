/*
  ==============================================================================

    Delay.cpp
    Created: 11 Sep 2017 7:54:27pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "Delay.h"
#include "EffectParameter.h"

Delay::Delay() : AudioEffect()
{
  addParameter(std::make_shared<EffectParameter>("level", 0));
  addParameter(std::make_shared<EffectParameter>("length", 1));
}

Delay::~Delay() = default;

void Delay::setupBlock(double sampleRate)
{
  delayBuffer.setSize(2, lineLength * sampleRate);
};

void Delay::processBlock(const AudioSourceChannelInfo& bufferToFill)
{
  auto levelParam = parameters.at("level");
  auto lengthParam = parameters.at("length");

  if (!levelParam->isOn) { return; }

  int numSamples = delayBuffer.getNumSamples();
  float delayLength = lengthParam->val * numSamples;
  int base = (int) std::floor(delayLength);
  float fraction = delayLength - base;

  int currentWritePos = 0;

  for (int chan = 0; chan < bufferToFill.buffer->getNumChannels(); chan++)
  {
    auto channelData = bufferToFill.buffer->getWritePointer(chan);
    auto delayData = delayBuffer.getWritePointer(chan);
    /* auto delayData = delayBuffer.getWritePointer(chan, delayPosition); */

    currentWritePos = delayPosition;
    int currentReadPos = base;

    for (int i = 0; i < bufferToFill.numSamples; i++)
    {
      auto in = channelData[i];
      channelData[i] = fraction * delayData[currentReadPos] + (1 - fraction) * delayData[currentReadPos + 1];
      delayData[currentWritePos] = (delayData[currentWritePos] + in) * levelParam->val;

      currentWritePos++;
      currentReadPos++;
      if (currentWritePos >= numSamples)
      {
        currentWritePos = 0;
      }
    }
  }
  delayPosition = currentWritePos;
}
