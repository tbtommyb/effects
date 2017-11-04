/*
  ==============================================================================

    Volume.cpp
    Created: 15 Oct 2017 9:41:31pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "Volume.h"
#include "EffectParameter.h"

Volume::Volume() : AudioEffect()
{
  addParameter(std::make_shared<EffectParameter>("level", 0));
}

Volume::~Volume() = default;

void Volume::processBlock(const AudioSourceChannelInfo& bufferToFill)
{
  auto level = parameters.at("level");

  if (!level->isOn) { return; }

  for (int chan = 0; chan < bufferToFill.buffer->getNumChannels(); chan++)
  {
    auto channelData = bufferToFill.buffer->getWritePointer(chan, bufferToFill.startSample);

    for (int i = 0; i < bufferToFill.numSamples; i++)
    {
      channelData[i] = channelData[i] * level->val;
    }
  }
}
