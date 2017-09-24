/*
  ==============================================================================

    Control.cpp
    Created: 22 Sep 2017 9:46:03pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "Control.h"

Control::Control(int id) : val(0),
                           isOn(false),
                           ChangeBroadcaster() {
  this->id = id;
};

Control::Control(const Control& other) {
  id = other.id;
  val = other.val;
  isOn = other.isOn;
};

Control::~Control() { };

void Control::update(int val, bool isOn) {
  this->val = val;
  this->isOn = isOn;

  sendChangeMessage();
};

Control& Control::operator=(Control rhs) {
  id = rhs.id;
  val = rhs.val;
  isOn = rhs.isOn;
  return *this;
};
