/*
  ==============================================================================

    Control.cpp
    Created: 22 Sep 2017 9:46:03pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "Control.h"

Control::Control(int id) : val(0.0),
                           isOn(false)
{
  this->id = id;
};

Control::~Control() = default;

void Control::update(float val, bool isOn)
{
  this->val = val;
  this->isOn = isOn;

};
