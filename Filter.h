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

Filter(); //Constructor
~Filter(); //Destructor

void changeFrequency(float frequency); //changes the frequency value in Filter class
void setFrequency(float* in, float Volume); //DSP part which uses frequency variable

private:
//variables for First order feed-forward filter (p.74 Will Pirkle)
//Difference equation is y(n) = a_o* x(n) = a_1* x(n-1)
float frequency; //"frequency" but is just an arbitrary value between 0.0 and 0.49.

//Variables for left channel
float m_f_a0; //a_o coefficient
float m_f_a1; //a_1 coefficient 
float m_f_z1; // Delay element

};

#endif  // FILTER_H_INCLUDED
