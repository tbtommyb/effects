/*
  ==============================================================================

    Volume.cpp
    Created: 15 Oct 2017 9:41:31pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "Volume.h"

Volume::Volume(std::shared_ptr<Control> ctrl) : AudioEffect(ctrl) { }

Volume::~Volume() = default;

void Volume::processBlock(AudioSourceChannelInfo& bufferToFill)
{
  for (int chan = 0; chan < bufferToFill.buffer->getNumChannels(); chan++)
  {
    auto channelData = bufferToFill.buffer->getWritePointer(chan, bufferToFill.startSample);

    for (int i = 0; i < bufferToFill.numSamples; i++)
    {
      channelData[i] = channelData[i] * ctrl->val;
    }
  }
}
