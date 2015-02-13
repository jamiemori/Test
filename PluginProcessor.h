/*
=================================================================================================================
PluginProcessor.h 

=================================================================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "RiserSynthSound.h"

class RiserAudioProcessor  : public AudioProcessor 
{
public:
    
    RiserAudioProcessor();
    ~RiserAudioProcessor();

    AudioProcessorEditor* createEditor() override;

    const String getProgramName (int index) override;
    const String getName() const override;
    const String getParameterName (int index) override;
    const String getParameterText (int index) override;
    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;

    int getNumParameters() override;
    int getNumPrograms() override;
    int getCurrentProgram() override;

    bool hasEditor() const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;

    void setParameter (int index, float newValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;
    void setCurrentProgram (int index) override;
    void changeProgramName (int index, const String& newName) override;
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    float getParameter (int index) override;
    double getTailLengthSeconds() const override;
    
    // Main purpose of this enumerated type is to indicate the "location" of the parameter
    // stored in the parameters array with words instead of numbers, though the the variables
    // implicitly convertible with numbers. 
    enum Parameters
    {
        volumeParameter = 0,
        attackParameter,
        decayParameter,
        sustainParameter,
        releaseParameter,
        numParameters
    };

    // Holds our main plugin parameters in array form. When one of the plugin's parameters is modified,
    // the array is updated by passing an enumerated type (Parameters) to the array to find the correction 
    // location of the parameter in the array. Parameters are set using the get and set Parameter methods.
    float parameters[numParameters];

private:
    
    // In JUCE, Synthesiser and Midikeyboardstate objects need to be declared together for a synthesiser. 
    // Keyboardstate handles the midi aspect of the synth. The midi buffer is passed into the synth object 
    // along with the audio buffer and takes care of the "signal processing."
    Synthesiser synth;
    MidiKeyboardState keyboardstate;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RiserAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
