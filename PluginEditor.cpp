#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TestAudioProcessorEditor::TestAudioProcessorEditor (TestAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    
    setSize (200,200); //set size of the window (x pixels, y pixels)
    sliderVolume.setRange(0, 1.0, 0.1); //set the range for the sliderVolume object (min, max, increment)
    sliderVolume.setSliderStyle (Slider::LinearVertical); //set the slider style (enumerated type)
    sliderVolume.setTextBoxStyle (Slider::NoTextBox, false, 90, 0); //set textboxstyle 
    sliderVolume.setTextValueSuffix ("sliderVolume");
    sliderVolume.addListener (this); //Registers a listener to receive events when this button's state changes. 
    
    sliderFilter.setRange(0.0, 0.49, 0.05); //set the range for the sliderVolume object (min, max, increment)
    sliderFilter.setSliderStyle (Slider::RotaryVerticalDrag); //set the slider style (enumerated type)
    sliderFilter.setTextBoxStyle(Slider::NoTextBox, false, 90, 0); //set textboxstyle 
    sliderFilter.setTextValueSuffix ("sliderFilter");
    sliderFilter.addListener (this);  //Registers a listener to receive events when this button's state changes.
    
    //make the objects visible in the window
    addAndMakeVisible (&sliderVolume);
    addAndMakeVisible (&sliderFilter);
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
    sliderVolume.setSize(100,100);
    sliderFilter.setBounds(100,50,200,200);
    sliderFilter.setSize(100,100);
}

void TestAudioProcessorEditor::sliderValueChanged (Slider* sliderMoved)
{
    if (&sliderVolume == sliderMoved)
    {
        processor.Volume = sliderVolume.getValue(); //reads current state of slider and pass it to Volume in processor.cpp 
    }
    else if (&sliderFilter == sliderMoved)
    {
        processor.frequency = sliderFilter.getValue(); //reads current state of slider and pass it to frequency in processor.cpp 
    }
}
