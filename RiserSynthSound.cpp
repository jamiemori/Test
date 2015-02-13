/*	
  ==============================================================================

    RiserSynthSound.cpp
    Created: 18 Jan 2015 2:57:14pm
    Author:  Yoda

  ==============================================================================
*/
#include "RiserSynthSound.h"

SynthSound::SynthSound(){}
SynthVoice::SynthVoice (float* parameters)
{
	angleDelta = 0.0;
    localParameters = parameters;

}
SynthVoice::~SynthVoice(){}

float SynthVoice::getParameter(int index)
{
    switch (index)
    {
        case 1: return localParameters[1];   break;
        case 2: return localParameters[2];   break;
        case 3: return localParameters[3];   break;
        case 4: return localParameters[4];   break;
    }
}

bool SynthVoice::canPlaySound (SynthesiserSound* sound) override
{
    return dynamic_cast <SynthSound*> (sound) != nullptr;
}


void SynthVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound* /*sound*/, int /*currentPithcWheelPosition*/) override
{
    
    currentAngle = 0.0;
    level = velocity * 0.15;
 
    double cyclesPerSecond = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    double cyclesPerSample = cyclesPerSecond/getSampleRate();

    angleDelta = cyclesPerSample * 2.0 * float_Pi;
    envelope.setEnvelopeParameter(static_cast<Envelope::envelopeStage>(Envelope::stageAttack), getParameter(1));
    envelope.setEnvelopeParameter(static_cast<Envelope::envelopeStage>(Envelope::stageDecay), getParameter(2));
    envelope.setEnvelopeParameter(static_cast<Envelope::envelopeStage>(Envelope::stageSustain), getParameter(3));
    envelope.setEnvelopeParameter(static_cast<Envelope::envelopeStage>(Envelope::stageRelease), getParameter(4));
    envelope.enterStage(Envelope::stageAttack);
    
}

void SynthVoice::stopNote (float /* velocity*/, bool allowTailOff) override
{
    clearCurrentNote();
    angleDelta = 0.0;
}

void SynthVoice::pitchWheelMoved (int /*newValue*/) override
{
}

void SynthVoice::controllerMoved (int /*controllerNumber*/, int /*newValue*/) override
{
}

void SynthVoice::renderNextBlock(AudioSampleBuffer &outputBuffer, int startSample, int numSamples) override
{ 
    if (angleDelta != 0.0)
    {   
        while (--numSamples >= 0)
        {
            const float currentSample = (float) (sin(currentAngle) * envelope.nextSample() * level );

            for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                outputBuffer.addSample (i, startSample, currentSample);
              

            currentAngle += angleDelta;
            ++startSample;
        }

        if (isKeyDown() == false)
        {
            envelope.enterStage(Envelope::stageRelease);
        }
    }
}


/*if (angleDelta != 0.0)
    {
            if (tailOff > 0)
            {
                while (--numSamples >= 0)
                {
                    const float currentSample = (float) (sin(currentAngle) * level * tailOff);

                    for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                        outputBuffer.addSample (i, startSample, currentSample);

                    currentAngle += angleDelta;
                    ++startSample;

                    tailOff *= 0.99;

                    if (tailOff <= 0.005)
                    {
                        clearCurrentNote();
                        angleDelta = 0.0;
                        
                        break;
                    }
                }   
            }
            else 
            {
                while (--numSamples >= 0)
                {
                    const float currentSample = (float) sin(currentAngle);

                    for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                        outputBuffer.addSample (i, startSample, currentSample);

                    currentAngle += angleDelta;
                    ++startSample;
                }   

            }
    }
}*/

    /*    case 1:
            if (tailOff > 0)
            {

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
                    tailOff *= 0.99;

                    if (tailOff <= 0.005)
                    {
                        clearCurrentNote();
                        angleDelta = 0.0;
                    }
                }
            }
            else
            {
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

            }

                break;

        case 2:
            if (tailOff > 0)
            {
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
                        tailOff *= 0.99;

                        if (tailOff <= 0.005)
                        {
                            clearCurrentNote();
                            angleDelta = 0.0;
                        }
                }    
            }   
            else
            {
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

            } 
                
                break;*/