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
                           ChangeBroadcaster()
{
  this->id = id;
};

Control::~Control() = default;

void Control::update(int val, bool isOn)
{
  this->val = val;
  this->isOn = isOn;

  sendChangeMessage();
};
