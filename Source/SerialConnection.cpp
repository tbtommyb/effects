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
                                       ctrls{} {
  fd = serialOpen("/dev/ttyACM0", 115200);
  if (fd == -1) {
    std::cout << "Error opening device\n";
    exit(EXIT_FAILURE);
  }
  wiringPiSetup();
};

SerialConnection::~SerialConnection() {
  serialClose(fd);
  signalThreadShouldExit();
};

SerialConnection::SerialConnection(const SerialConnection& other) :
  Thread("serial connection") {
  fd = other.fd;
  for (int i = 0; i < other.ctrls.size(); i++) {
    ctrls.at(i) = other.ctrls.at(i);
  }
};

void SerialConnection::run() {
  while (!threadShouldExit()) {
    if (serialDataAvail(fd) > 0) {
      const MessageManagerLock mml {Thread::getCurrentThread()};

      if (!mml.lockWasGained()) {
        return;
      }

      unsigned int serialOutput { 0 };

      int lowerByte = serialGetchar(fd);
      serialOutput = lowerByte;
      int upperByte = serialGetchar(fd);
      serialOutput |= (upperByte << 8);

      int id = (serialOutput & 0xF000) >> 12;
      int val = serialOutput & 0x3FF;
      bool isOn = (serialOutput & (1 << 10)) > 0;

      if (id < ctrls.size()) {
        ctrls.at(id)->update(val, isOn);
      }
    }
  }
};

void SerialConnection::addControl(std::shared_ptr<Control> ctrl) {
  ctrls.push_back(ctrl);
};
