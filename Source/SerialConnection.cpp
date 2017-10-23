/*
  ==============================================================================

    SerialConnection.cpp
    Created: 10 Sep 2017 12:31:58pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "SerialConnection.h"
#include "Control.h"
#include <wiringPi.h>
#include <wiringSerial.h>

SerialConnection::SerialConnection() : Thread("serial connection"),
                                       ctrls{}
{
  // TODO - pass in as command line argument
  fd = serialOpen("/dev/ttyACM0", 115200);
  if (fd == -1) {
    std::cout << "Error opening device\n";
    exit(EXIT_FAILURE);
  }
  wiringPiSetup();
  initialiseControls();
};

SerialConnection::~SerialConnection()
{
  serialClose(fd);
  signalThreadShouldExit();
};

void SerialConnection::initialiseControls()
{
  for (int i = 0; i < numCtrls; i++)
  {
    ctrls.push_back(std::make_shared<Control>(i));
  }
};

void SerialConnection::registerEffect(std::shared_ptr<AudioEffect> effect)
{
  for (auto const kv : effect->getParameters())
  {
    auto parameter = kv.second;
    ctrls.at(parameter->id)->addChangeListener(parameter.get());
  }
};

void SerialConnection::run()
{
  while (!threadShouldExit()) {
    if (serialDataAvail(fd) > 1) {
      const MessageManagerLock mml {Thread::getCurrentThread()};

      if (!mml.lockWasGained()) {
        return;
      }

      unsigned int serialOutput { 0 };

      int lowerByte = serialGetchar(fd);
      if (lowerByte == -1) {
        std::cout << "ERR: lower byte is -1\n";
        continue;
      }
      int upperByte = serialGetchar(fd);
      if (upperByte == -1) {
        std::cout << "ERR: upper byte is -1\n";
        continue;
      }
      serialOutput = (upperByte << 8) | lowerByte;

      int id = ID(serialOutput);
      float val = VAL(serialOutput) / MAX_VAL;
      bool isOn = IS_ON(serialOutput);

      if (id < ctrls.size()) {
        ctrls.at(id)->update(val, isOn);
      } else {
        std::cout << "ERR: invalid ID: " << id << "\n";
      }
    }
  }
};
