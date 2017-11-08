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
  float delayLength = lengthParam->val * (float) numSamples;

  int writePos = 0;

  for (int chan = 0; chan < bufferToFill.buffer->getNumChannels(); chan++)
  {
    auto channelData = bufferToFill.buffer->getWritePointer(chan);
    auto delayData = delayBuffer.getWritePointer(chan);

    writePos = delayPosition;

    for (int i = 0; i < bufferToFill.numSamples; i++)
    {
      float readPos = (float) writePos - delayLength;

      if (readPos < 0.0) { readPos += numSamples; }

      int baseIndex = (int) std::floor(readPos);
      float fraction = readPos - (float) baseIndex;

      auto in = channelData[i];

      // Linearly interpolate between two samples
      auto output = delayData[baseIndex] + ((delayData[baseIndex + 1] - delayData[baseIndex]) * fraction);
      channelData[i] += output;

      // Write output back into delay line
      delayData[writePos] = (in + output) * levelParam->val;

      writePos++;
      if (writePos >= numSamples)
      {
        writePos = 0;
      }
    }
  }
  delayPosition = writePos;
}
