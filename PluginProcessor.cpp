#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Envelope.h"

//==============================================================================
RiserAudioProcessor::RiserAudioProcessor()
{

    // Set default values:
    Volume = 0.0;

    for (int i = 1; --i >= 0;)
    {
        synth.addVoice (new SynthVoice());
    }

    synth.addSound (new SynthSound());

    envelope = new Envelope();

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
      case volumeParameter: return Volume;  break;
      case attackParameter: return Attack;  break;
      case decayParameter:  return  Decay;  break;
      case sustainParameter:  return Sustain; break;
      case releaseParameter: return Release; break;
      default: return 0.0f; break;
    }
}

void RiserAudioProcessor::setParameter (int index, float newValue)
{
	int SampleRate = getSampleRate();
    switch (index)
    {
      case volumeParameter:  Volume = newValue; 
      break;

      case attackParameter: 
        Attack = newValue;
        envelope->setEnvelopeParameter(static_cast<Envelope::envelopeStage>(attackParameter) , Attack, SampleRate);
        break;
      case decayParameter: Decay = newValue; break;
      case sustainParameter: Sustain = newValue; break;
      case releaseParameter: Release = newValue; break;
      default: break;
    }
}

const String RiserAudioProcessor::getParameterName (int index)
{
    switch (index)
    {
      case volumeParameter: return "Volume";  break;
      default: break;
    }
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

  const int numInputChannels = getNumInputChannels(); //read number of channels input
  const int numSamples = buffer.getNumSamples(); //read numbers of samples in channel
  const int numOutputChannels = getNumOutputChannels(); //get number of output channels

  keyboardstate.processNextMidiBuffer(midiMessages, 0, numSamples, true);

  synth.renderNextBlock(buffer, midiMessages, 0, numSamples);

  for (int channel = 0; channel < numInputChannels; channel++)
    buffer.applyGain(channel, 0, numSamples, Volume);

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