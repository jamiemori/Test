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

void Oscillator::gen(AudioSampleBuffer &outputBuffer, 
                    float oscfrequency, 
                    int numSamples,
                    int waveform) override
{	
	float fs = 44100.0;
	float pi = 3.1415926535897932384626433f;
	int startSample = 0;
	angleDelta = oscfrequency * 2.0 * pi / fs;

    switch (waveform)
    {
        case 0:
            while (--numSamples >= 0)
            {
                const float currentSample = (float) sin(currentAngle);

                for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);

	            currentAngle += angleDelta;
                ++startSample;

            }
            break;

        case 1:
            while (--numSamples >= 0)
            {
                const float currentSample = (float) 1.0 - (2.0 * currentAngle / (2.0 * pi));

                for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);
                currentAngle += angleDelta;

                while (currentAngle >= 2 * pi)
                {
                    currentAngle -= 2 * pi;
                }
                ++startSample;
            }
            break;

        case 2:
            while (--numSamples >= 0)
            {
                float currentSample = 0.0;

                if (currentAngle <= pi)
                {
                    currentSample = 1.0;
                }
                else
                {
                    currentSample = -1.0;
                }
                for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);
                currentAngle += angleDelta;

                while (currentAngle >= 2 * pi)
                {   
                currentAngle -= 2 * pi;
                }
                ++startSample;
            }
            break;
		default: 
			break;
    }
}

