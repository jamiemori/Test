#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestAudioProcessor::TestAudioProcessor()
{
  Volume = 0.7; //initialize the Volume at 0.7
  frequency = 0.0; 
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
    return 0;
}

float TestAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void TestAudioProcessor::setParameter (int index, float newValue)
{
}

const String TestAudioProcessor::getParameterName (int index)
{
    return String();
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
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void TestAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{ 

  const int numChannels = buffer.getNumChannels(); //read number of input??? channels
  const int numSamples = buffer.getNumSamples(); //read numbers of samples in channel
  const int numOutputChannels = getNumOutputChannels(); //get number of output channels
  
  float* leftData = buffer.getWritePointer(0); //return writeable pointer to channel 0 (left channel)
  float* rightData = buffer.getWritePointer(1); //return writeable pointer to channel 1 (right channel)
  filter.changeFrequency(frequency); // read current frequency value and call Filter class function 
  for(long i=0; i<buffer.getNumSamples();i++) //loop over number of samples in buffer
    {
      filter.setFrequency(&leftData[i], &rightData[i], Volume); //setFrequency function call (DSP part)
    }

  // clear the buffer
   for (int i = numChannels; i < numOutputChannels; ++i)  //clear out output buffers
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