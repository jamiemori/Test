/*
  ==============================================================================

    RiserSynthSound.h
    Created: 18 Jan 2015 2:57:14pm
    Author:  Yoda

  ==============================================================================
*/

#ifndef RISERSYNTHSOUND_H_INCLUDED
#define RISERSYNTHSOUND_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"
#include "PluginProcessor.h"

class SynthSound : public SynthesiserSound
{   
public:

  SynthSound();

  bool appliesToNote (int /*midiNoteNumber*/) override {return true;}
  bool appliesToChannel (int /*midiChannel*/) override {return true;}
    
};

class SynthVoice : public SynthesiserVoice 
{
public:

	SynthVoice(float* parameters);
	~SynthVoice();

	bool canPlaySound (SynthesiserSound* sound) override;
	void startNote (int midiNoteNumber, float velocity, SynthesiserSound* /*sound*/, int /*currentPithcWheelPosition*/) override;
	void stopNote (float /* velocity*/, bool allowTailOff) override;
	void pitchWheelMoved (int /*newValue*/) override;
  void controllerMoved (int /*controllerNumber*/, int /*newValue*/) override;
  void renderNextBlock(AudioSampleBuffer &outputBuffer, int startSample, int numSamples) override;
  float getParameter (int index);

private:

  Envelope envelope;
  float* localParameters;
  double currentAngle, angleDelta, level;
};

#endif  // RISERSYNTHSOUND_H_INCLUDED
