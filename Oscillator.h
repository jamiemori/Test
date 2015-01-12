/*
  ==============================================================================

    Oscillator.h
    Created: 5 Jan 2015 12:25:03pm
    Author:  Yoda

  ==============================================================================
*/

#ifndef OSCILLATOR_H_INCLUDED
#define OSCILLATOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class Oscillator
{

public:
Oscillator();
~Oscillator();

void gen(AudioSampleBuffer &outputBuffer, float oscfrequency, int numSamples) override;

private:
double currentAngle, angleDelta;

};

#endif  // OSCILLATOR_H_INCLUDED
