/*
  ==============================================================================

    SerialConnection.h
    Created: 10 Sep 2017 12:31:58pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Control.h"
#include "AudioEffect.h"

#define ID(input) ((input & 0xF000) >> 12)
#define VAL(input) (input & 0x3FF)
#define IS_ON(input) ((input & (1 << 10)) > 0)
#define MAX_VAL 1023.0;

class SerialConnection : public Thread
{
 public:
  SerialConnection();
  SerialConnection(const SerialConnection& other) = delete;
  SerialConnection(SerialConnection&& other) = delete;
  SerialConnection& operator=(const SerialConnection& other) = delete;
  SerialConnection& operator=(SerialConnection&& other) = delete;
  ~SerialConnection();
  void run() override;
  void registerEffect(std::shared_ptr<AudioEffect> effect);
 private:
  void initialiseControls();
  const int numCtrls = 6;
  std::vector<std::shared_ptr<Control>> ctrls;
  int fd;
};
