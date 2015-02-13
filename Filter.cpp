/*
  ==============================================================================

    Filter.cpp
    Created: 30 Dec 2014 9:45:31pm
    Author:  Yoda

  ==============================================================================
*/

#include "Filter.h"

Filter::Filter ()
{
	cutOff = 0.99;
	resonance = 0.0;
	mode = LowPass;


} 
Filter::~Filter(){} 

float Filter::process(float inputValue)
{
	buf0 += cutOff * (inputValue - buf0);
    buf1 += cutOff * (buf0 - buf1);
    switch (mode) {
        case : LowPass
            return buf1;
        case : HighPass
            return inputValue - buf0;
        case : BandPass
            return buf0 - buf1;
        default:
            return 0.0;
}