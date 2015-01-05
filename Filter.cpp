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
	m_f_a1_left = frequency; 
	m_f_a1_right = frequency;

	m_f_a0_left = m_f_a1_left - 1.0;
	m_f_a0_right = m_f_a1_right - 1.0;

	m_f_z1_left = 0.0;
	m_f_z1_right = 0.0;
}

//DSP calculation for First order feed-forward filter
void Filter::setFrequency (float* LeftSample, float* RightSample, float Volume) 
{
	//set delay elements 
	float xn_1L = m_f_z1_left;
	float xn_1R = m_f_z1_right;

	// calculate the difference equation
	float yn_L = m_f_a0_left * (*LeftSample) + m_f_a1_left * xn_1L;
	float yn_R = m_f_a0_right * (*RightSample) + m_f_a1_right * xn_1R;

	//update the delay elements
	m_f_z1_left = *LeftSample;
	m_f_z1_right = *RightSample;

	//scales the calculated output values with volume (ouput)
	*LeftSample = yn_L * Volume;
	*RightSample = yn_R* Volume;
     
}
