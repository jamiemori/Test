#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TestAudioProcessorEditor::TestAudioProcessorEditor (TestAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    
    setSize (300,300); //set size of the window (x pixels, y pixels)

    sliderVolume.setRange(0, 1.0, 0.1); //set the range for the sliderVolume object (min, max, increment)
    sliderVolume.setSliderStyle (Slider::LinearVertical); //set the slider style (enumerated type)
    sliderVolume.setTextBoxStyle (Slider::TextBoxBelow, false, 90, 10); //set textboxstyle 
    sliderVolume.addListener (this); //Registers a listener to receive events when this button's state changes. 
    
    sliderFilter.setRange(0.0, 0.49, 0.05); //set the range for the sliderVolume object (min, max, increment)
    sliderFilter.setSliderStyle (Slider::RotaryVerticalDrag); //set the slider style (enumerated type)
    sliderFilter.setTextBoxStyle(Slider::TextBoxBelow, false, 90, 10); //set textboxstyle 
    sliderFilter.addListener (this);  //Registers a listener to receive events when this button's state changes.

    sliderOscfreq.setRange (200.0, 6000.0, 50.0);
    sliderOscfreq.setSliderStyle (Slider::LinearVertical);
    sliderOscfreq.setTextBoxStyle (Slider::TextBoxBelow, false, 90, 10);
    sliderOscfreq.addListener (this);

    buttonStart.setButtonText ("Start");
    buttonStart.addListener (this);
    
    //make the objects visible in the window
    addAndMakeVisible (&sliderVolume);
    addAndMakeVisible (&sliderFilter);
    addAndMakeVisible (&sliderOscfreq);
    addAndMakeVisible (&buttonStart);

    startTimer(50);

}

TestAudioProcessorEditor::~TestAudioProcessorEditor()
{
}

//==============================================================================
void TestAudioProcessorEditor::paint (Graphics& g)
{
    // fill the whole window white
    g.fillAll (Colours::white);
 
    // set the current drawing colour to black
    g.setColour (Colours::black);
 
    // set the font size and draw text to the screen
    g.setFont (15.0f);
 
    g.drawFittedText ("Blah", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void TestAudioProcessorEditor::resized()
{
    sliderVolume.setBounds(10,50,200,200);
    sliderFilter.setBounds(100,50,200,200);
    sliderOscfreq.setBounds (200,50,200,200);   
    buttonStart.setBounds (200,150,200,200);
     
    sliderVolume.setSize(100,100);
    sliderFilter.setSize(100,100);
    sliderOscfreq.setSize (100,100);
    buttonStart.setSize(100,100);
}

void TestAudioProcessorEditor::timerCallback()
{
    TestAudioProcessor* processor = getProcessor();

    sliderVolume.setValue(processor->Volume, dontSendNotification);
    sliderFilter.setValue(processor->frequency, dontSendNotification);
    sliderOscfreq.setValue(processor->oscfrequency, dontSendNotification);
    buttonStart.setToggleState(processor->togglestate, dontSendNotification);
}

void TestAudioProcessorEditor::sliderValueChanged (Slider* sliderMoved)
{
    if (&sliderVolume == sliderMoved)
    {
        getProcessor()->setParameterNotifyingHost (TestAudioProcessor::volumeParameter, (float)sliderVolume.getValue());
	}   
    else if (&sliderFilter == sliderMoved)
    {
        getProcessor()->setParameterNotifyingHost (TestAudioProcessor::frequencyParameter, (float)sliderFilter.getValue());
    }
    else if (&sliderOscfreq == sliderMoved)
    {
        getProcessor()->setParameterNotifyingHost (TestAudioProcessor::oscfrequencyParameter, (float)sliderOscfreq.getValue());
    }
}

void TestAudioProcessorEditor::buttonClicked (Button* button)
{
    if (&buttonStart == button)
    {
        getProcessor()->setParameterNotifyingHost (TestAudioProcessor::togglestateParameter, buttonStart.getToggleState());
    }
}
