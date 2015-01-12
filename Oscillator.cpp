/*
  ==============================================================================

    Oscillator.cpp
    Created: 5 Jan 2015 12:25:03pm
    Author:  Yoda

  ==============================================================================
*/

#include "Oscillator.h"
#include <math.h>

Oscillator::Oscillator()
{
	currentAngle = 0.0;
	angleDelta = 0.0;	
};
Oscillator::~Oscillator(){};

void Oscillator::gen(AudioSampleBuffer &outputBuffer, float oscfrequency, int numSamples) override
{	
	
	float fs = 44100.0;
	float pi = 3.1415926535897932384626433f;
	int startSample = 0;
	angleDelta = oscfrequency/fs * 2.0 * pi;

	while (--numSamples >= 0)
    {
        const float currentSample = (float) (sin (currentAngle));

        for (int i = outputBuffer.getNumChannels(); --i >= 0;)
            outputBuffer.addSample (i, startSample, currentSample);

        currentAngle += angleDelta;
        ++startSample;
	}
}


