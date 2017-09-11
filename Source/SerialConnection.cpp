/*
  ==============================================================================

    SerialConnection.cpp
    Created: 10 Sep 2017 12:31:58pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "SerialConnection.h"
#include <wiringPi.h>
#include <wiringSerial.h>

#define DELAY 0x1000

SerialConnection::SerialConnection() : Thread("serial connection"),
                                       ChangeBroadcaster(),
                                       delayVal(0),
                                       delayIsOn(false) {
  fd = serialOpen("/dev/ttyACM0", 115200);
  if (fd == -1) {
    std::cout << "Error opening device\n";
  }
  wiringPiSetup();
};

SerialConnection::~SerialConnection() {
  serialClose(fd);
};

void SerialConnection::run() {
  while (!threadShouldExit()) {
    if (serialDataAvail(fd) >= 2) {
      unsigned int input = serialGetchar(fd); // LSB
      input |= (serialGetchar(fd) << 8);      // MSB

      recordUpdate(input);

      sendChangeMessage();
    }
  }
};

void SerialConnection::recordUpdate(unsigned int input) {
  auto inputType = input & 0xf000; // top 4 bits
  auto inputValue = input & 0x3FF; // bottom 10 bits

  if (inputType == DELAY) {
    delayVal = inputValue;
    delayIsOn = true;
  }
};
