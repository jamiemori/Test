/*
=================================================================================================================
PluginProcessor.cpp

=================================================================================================================

*/

#include "PluginEditor.h"

//==============================================================================
RiserAudioProcessor::RiserAudioProcessor()
{

    // Set default values:
    for (int i; i < numParameters; i++)
      parameters[i] = 0;

    for (int i = 1; --i >= 0;)
    {
        synth.addVoice (new SynthVoice(parameters));
    }

    synth.addSound (new SynthSound());
}

RiserAudioProcessor::~RiserAudioProcessor()
{
}
//==============================================================================
const String RiserAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int RiserAudioProcessor::getNumParameters()
{
    return numParameters;
}

float RiserAudioProcessor::getParameter (int index)
{
    switch (index)
    {
      case volumeParameter : return parameters[volumeParameter];  break;   
      case attackParameter : return parameters[attackParameter];  break;   
      case decayParameter  : return parameters[decayParameter];   break;
      case sustainParameter: return parameters[sustainParameter]; break;
      case releaseParameter: return parameters[releaseParameter]; break;
      default:               return 0.0f;                         break;
    }
}

void RiserAudioProcessor::setParameter (int index, float newValue)
{

    switch (index)
    {
      case volumeParameter  : parameters[volumeParameter]  = newValue; break;
      case attackParameter  : parameters[attackParameter]  = newValue; break;
      case decayParameter   : parameters[decayParameter]   = newValue; break;
      case sustainParameter : parameters[sustainParameter] = newValue; break;
      case releaseParameter : parameters[releaseParameter] = newValue; break;
      default:                                                         break;
    }
}

const String RiserAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String RiserAudioProcessor::getParameterText (int index)
{
    return String();
}
const String RiserAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String RiserAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool RiserAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool RiserAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool RiserAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool RiserAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool RiserAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double RiserAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RiserAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int RiserAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RiserAudioProcessor::setCurrentProgram (int index)
{
}

const String RiserAudioProcessor::getProgramName (int index)
{
    return String();
}

void RiserAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void RiserAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
  synth.setCurrentPlaybackSampleRate (sampleRate);
  keyboardstate.reset();
}

void RiserAudioProcessor::releaseResources()
{
  keyboardstate.reset();
}

void RiserAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{ 

  const int numInputChannels  = getNumInputChannels(); 
  const int numSamples        = buffer.getNumSamples(); 
  const int numOutputChannels = getNumOutputChannels(); 

  keyboardstate.processNextMidiBuffer(midiMessages, 0, numSamples, true);

  synth.renderNextBlock(buffer, midiMessages, 0, numSamples);

  for (int channel = 0; channel < numInputChannels; channel++)
    buffer.applyGain(channel, 0, numSamples, getParameter(volumeParameter));

  // clear the buffer
   for (int i = numInputChannels; i < numOutputChannels; ++i)
  {
    buffer.clear (i, 0, buffer.getNumSamples());
  }
  // End of Process Block
}

//==============================================================================
bool RiserAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* RiserAudioProcessor::createEditor()
{
    return new RiserAudioProcessorEditor (*this);
}

//==============================================================================
void RiserAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void RiserAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RiserAudioProcessor();
}