/*
  ==============================================================================

    SerialConnection.h
    Created: 10 Sep 2017 12:31:58pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class SerialConnection : public Thread,
                         public ChangeBroadcaster
{
 public:
  SerialConnection();
  ~SerialConnection();
  void run() override;
  unsigned int delayVal;
  bool delayIsOn;
 private:
  void recordUpdate(unsigned int);
  int fd;
};
