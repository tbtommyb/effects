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

#define ID(input) ((input & 0xF000) >> 12)
#define VAL(input) (input & 0x3FF)
#define IS_ON(input) ((input & (1 << 10)) > 0)

class SerialConnection : public Thread
{
 public:
  SerialConnection();
  SerialConnection(const SerialConnection&);
  ~SerialConnection();
  void run() override;
  void addControl(std::shared_ptr<Control> ctrl);
 private:
  std::vector<std::shared_ptr<Control>> ctrls;
  int fd;
};
