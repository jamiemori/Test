/*
  ==============================================================================

    Envelope.h
    Created: 22 Jan 2015 8:54:53pm
    Author:  Yoda

  ==============================================================================
*/

#ifndef ENVELOPE_H_INCLUDED
#define ENVELOPE_H_INCLUDE

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


class Envelope : public AudioSampleBuffer
{
public:    
	enum envelopeStage {
        stageOff = 0,
        stageAttack,
        stageDecay,
        stageSustain,
        stageRelease,
        numEnvelopeStages
    };

    float nextSample();
    void calculateMultiplier (float startLevel, float stopLevel, int lengthInSamples);
    void enterStage(envelopeStage newStage);
    void setSampleRate(float newSampleRate);
    inline envelopeStage getCurrentStage () const {return currentStage;};
    void setEnvelopeParameter (envelopeStage stage, float newValue, float SampleRate);  
    float getEnvelope (envelopeStage stage) {return stageValue[stage];};
    
    Envelope():
 
    minimumLevel(  0.0001),
    currentStage( stageOff),
    currentLevel( minimumLevel),
    multiplier( 1.0),
    currentSampleIndex( 0),
    nextStageSampleIndex( 0){
	stageValue[stageOff] = 0.0;
    stageValue[stageAttack] = 0.01;
    stageValue[stageSustain] = 0.1;
    stageValue[stageDecay] = 0.5;
    stageValue[stageRelease] = 1.0;};
  

private:
    envelopeStage currentStage;
	float minimumLevel;
	float currentLevel;
	float multiplier;
    float stageValue[numEnvelopeStages];
	int nextStageSampleIndex;
	int currentSampleIndex;  
};
#endif  // ENVELOPE_H_INCLUDED
