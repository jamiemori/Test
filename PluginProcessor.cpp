#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestAudioProcessor::TestAudioProcessor()
{

  // Set default values:
  Volume = 0.0;
  frequency = 0.0;
  oscfrequency = 200.0;
  togglestate = false;
  
}

TestAudioProcessor::~TestAudioProcessor()
{
}
//==============================================================================
const String TestAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int TestAudioProcessor::getNumParameters()
{
    return numParameters;
}

float TestAudioProcessor::getParameter (int index)
{
    switch (index)
    {
      case volumeParameter: 
        return Volume; 
        break;

      case frequencyParameter: 
        return frequency;
        break;

      case togglestateParameter: 
        return togglestate; 
        break;

      case oscfrequencyParameter:
        return oscfrequency;
        break;

      default: 
        return 0.0f; 
        break;
    }
}

void TestAudioProcessor::setParameter (int index, float newValue)
{
    switch (index)
    {
      case volumeParameter: 
        Volume = newValue;
        break;

	  case frequencyParameter:
        frequency = newValue;
        break;

    case oscfrequencyParameter:
        oscfrequency = newValue;
        break;

	  case togglestateParameter:
        togglestate = (bool)newValue;
        break;

      default:
        break;
    }
}

const String TestAudioProcessor::getParameterName (int index)
{
    switch (index)
    {
      case volumeParameter: 
        return "Volume";
        break;

      case frequencyParameter: 
        return "frequency";
        break;

      case oscfrequencyParameter:
        return "oscfrequency";
        break;

      case togglestateParameter: 
        return "togglestate";
        break;

      default: 
        break;
    }
    return String::empty;
}

const String TestAudioProcessor::getParameterText (int index)
{
    return String();
}
const String TestAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String TestAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool TestAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool TestAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool TestAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TestAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TestAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double TestAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TestAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TestAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TestAudioProcessor::setCurrentProgram (int index)
{
}

const String TestAudioProcessor::getProgramName (int index)
{
    return String();
}

void TestAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TestAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void TestAudioProcessor::releaseResources()
{
}

void TestAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{ 

  const int numInputChannels = getNumInputChannels(); //read number of input??? channels
  const int numSamples = buffer.getNumSamples(); //read numbers of samples in channel
  const int numOutputChannels = getNumOutputChannels(); //get number of output channels
  const double sampleRate = getSampleRate();

  if (togglestate == false)
  {
    for (int channel = 0; channel < numInputChannels ; channel++)
    {
      float* channelData = buffer.getWritePointer(channel); //return writeable pointer to channel
    
      for(long i=0; i<buffer.getNumSamples(); i++) //loop over number of samples in buffer
      {
        float in = channelData[i];
        float out = 0.0;
        channelData[i] = out;
      }
    }
  }

  else
  { 
    //float in = channelData[i];
  	osc.gen(buffer, oscfrequency, numSamples);
    //for (channel = 0; channel < numInputChannels; ++channel)
    //filter.setFrequency(&in, Volume);
    /*out = in * Volume;
    channelData[i] = out;*/
  }
  
    
  // clear the buffer
   for (int i = numInputChannels; i < numOutputChannels; ++i)
  {
    buffer.clear (i, 0, buffer.getNumSamples());
  }
  // End of Process Block
}

//==============================================================================
bool TestAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TestAudioProcessor::createEditor()
{
    return new TestAudioProcessorEditor (*this);
}

//==============================================================================
void TestAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TestAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TestAudioProcessor();
}