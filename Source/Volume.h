/*
  ==============================================================================

    Volume.h
    Created: 15 Oct 2017 9:41:31pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#pragma once

#include "Control.h"
#include "AudioEffect.h"

class Volume : public AudioEffect
{
  Volume(std::shared_ptr<Control> ctrl);
  ~Volume();
  void processBlock(AudioSourceChannelInfo& bufferToFill) override;
};
