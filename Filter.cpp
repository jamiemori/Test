/*
  ==============================================================================

    Filter.cpp
    Created: 30 Dec 2014 9:45:31pm
    Author:  Yoda

  ==============================================================================
*/

#include "Filter.h"

Filter::Filter (){} //Constructor
Filter::~Filter(){} //Destructor

void Filter::changeFrequency(float frequency) // reads value from frequency slider and updates values accordingly
{
	m_f_a1 = frequency; 

	m_f_a0 = m_f_a1- 1.0;

	m_f_z1 = 0.0;

}

//DSP calculation for First order feed-forward filter
void Filter::setFrequency (float* in, float Volume) 
{
	//set delay elements 
	float xn_1 = m_f_z1;

	// calculate the difference equation
	float yn_1 = m_f_a0 * (*in) + m_f_a1 * xn_1;
	
	//update the delay elements
	m_f_z1 = *in;

	//scales the calculated output values with volume (ouput)
	*in = yn_1 * Volume;     
}
