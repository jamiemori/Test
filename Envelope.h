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

class Envelope
{
public:

	Envelope();
	~Envelope();
    
	enum envelopeStage 
	{
        stageOff = 0,
        stageAttack,
        stageDecay,
        stageSustain,
        stageRelease,
        numEnvelopeStages
    };

    inline envelopeStage getCurrentStage () const {return currentStage;};
    void calculateMultiplier (float startLevel, float stopLevel, int lengthInSamples);
    void enterStage(envelopeStage newStage);
    void setStageValue (float newValue, int index) {stageValue[index] = newValue;};
    void setEnvelopeParameter (envelopeStage stage, float newValue);  
    float getEnvelope (envelopeStage stage) {return stageValue[stage];};
    float getStageValue(int index) {return stageValue[index];};
    float nextSample();
	

private:
    envelopeStage currentStage;
    float stageValue[numEnvelopeStages];
	float minimumLevel;
	float currentLevel;
	float multiplier;
   	int nextStageSampleIndex;
	int currentSampleIndex;  

};
#endif  // ENVELOPE_H_INCLUDED
