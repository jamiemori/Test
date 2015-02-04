#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "RiserSynthSound.h"



//==============================================================================
/**
*/

class Envelope;
class RiserAudioProcessor  : public AudioProcessor 
{
public:
    //==============================================================================
    RiserAudioProcessor();
    ~RiserAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;
    //int setWaveForm();

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    int getNumParameters() override;
    float getParameter (int index) override;
    void setParameter (int index, float newValue) override;

    const String getParameterName (int index) override;
    const String getParameterText (int index) override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    //==============================================================================
    
    enum Parameters
    {
        volumeParameter = 0,
        attackParameter,
        decayParameter,
        sustainParameter,
        releaseParameter,
        numParameters
    };
    Parameters parameters;
    
    float Volume; 
    float Attack;
	float Sustain;
	float Decay;
	float Release;

private:
    Synthesiser synth;
    MidiKeyboardState keyboardstate;
    ScopedPointer<Envelope> envelope;
  
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RiserAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
