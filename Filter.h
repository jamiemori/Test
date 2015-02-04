/*
  ==============================================================================

    Filter.h
    Created: 30 Dec 2014 9:45:38pm
    Author:  Yoda

  ==============================================================================
*/

#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

class Filter
{
public:

Filter(); 
~Filter(); 

enum filterMode
{
	LowPass = 0;
	HighPass;
	BandPass;
	numFilterModes;
};

inline void setCutOff (float newCutoff) {cutOff = newCutOff; calculateFeedbackAmount();};
inline void setResonance (float newResonance) {resonance = newResonance; calculateFeedbackAmount();};
inline void setFilterMode (filterMode newMode) {mode = newMode;};

private:

float cutOff;
float resonance;
inline void calculateFeedbackAmount() {feedBackAmount = resonance + resonance/(1.0 - cutOff);};
filterMode mode;

};

#endif  // FILTER_H_INCLUDED
