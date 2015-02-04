#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RiserAudioProcessorEditor::RiserAudioProcessorEditor (RiserAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setLookAndFeel (&mlaf);
    
    //make the objects visible in the window
    
    sliderVolume.setRange(0, 1.0, 0.001); //set the range for the sliderVolume object (min, max, increment)
    sliderVolume.setSliderStyle (Slider::RotaryVerticalDrag); //set the slider style (enumerated type)
    sliderVolume.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    sliderVolume.addListener (this); //Registers a listener to receive events when this button's state changes. 

    font.setTypefaceName("Gulim");
    labelVolume.setText("Volume", dontSendNotification);
    labelVolume.setFont(font);
    labelVolume.setJustificationType(Justification::centred);
    labelVolume.setColour(Label::textColourId, Colour (0xff93bfd2));
    labelVolume.attachToComponent(&sliderVolume, false);

    sliderAttack.setRange(0, 1.0, 0.001);
    sliderAttack.setSliderStyle (Slider::RotaryVerticalDrag);
    sliderAttack.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    sliderAttack.addListener (this);

    font.setTypefaceName("Gulim");
    labelAttack.setText("Attack", dontSendNotification);
    labelAttack.setFont(font);
    labelAttack.setJustificationType (Justification::centred);
    labelAttack.setColour (Label::textColourId, Colour (0xff93bfd2));
    labelAttack.attachToComponent(&sliderAttack, false);

    sliderSustain.setRange(0, 1.0, 0.001);
    sliderSustain.setSliderStyle (Slider::RotaryVerticalDrag);
    sliderSustain.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    sliderSustain.addListener (this);

    font.setTypefaceName("Gulim");
    labelSustain.setText("Sustain", dontSendNotification);
    labelSustain.setFont(font);
    labelSustain.setJustificationType (Justification::centred);
    labelSustain.setColour (Label::textColourId, Colour (0xff93bfd2));
    labelSustain.attachToComponent(&sliderSustain, false);

    sliderDecay.setRange(0, 1.0, 0.001);
    sliderDecay.setSliderStyle (Slider::RotaryVerticalDrag);
    sliderDecay.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    sliderDecay.addListener (this);

    font.setTypefaceName("Gulim");
    labelDecay.setText("Decay", dontSendNotification);
    labelDecay.setFont(font);
    labelDecay.setJustificationType (Justification::centred);
    labelDecay.setColour (Label::textColourId, Colour (0xff93bfd2));
    labelDecay.attachToComponent(&sliderDecay, false);

    sliderRelease.setRange(0, 1.0, 0.001);
    sliderRelease.setSliderStyle (Slider::RotaryVerticalDrag);
    sliderRelease.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    sliderRelease.addListener (this);

    font.setTypefaceName("Gulim");
    labelRelease.setText("Release", dontSendNotification);
    labelRelease.setFont(font);
    labelRelease.setJustificationType (Justification::centred);
    labelRelease.setColour (Label::textColourId, Colour (0xff93bfd2));
    labelRelease.attachToComponent(&sliderRelease, false);

    addAndMakeVisible (&sliderAttack);
	addAndMakeVisible (&sliderVolume);
    addAndMakeVisible (&sliderSustain);
    addAndMakeVisible (&sliderDecay);
    addAndMakeVisible (&sliderRelease);

	setSize (550,200); 
    startTimer(50);

}

RiserAudioProcessorEditor::~RiserAudioProcessorEditor()
{
}

//==============================================================================
void RiserAudioProcessorEditor::paint (Graphics& g)
{
    // fill the whole window white
    g.fillAll (Colours::black);
    font.setTypefaceName("Gulim");
    g.setFont(font);
    g.setColour (Colour (0xff93bfd2));
    g.setFont(61.0f);
    g.drawFittedText ("Riser", 0,0, 200, 200, Justification::topLeft, 1, 1.0f);
    g.setColour (Colours::white);
    g.setFont(65.0f);
    g.drawFittedText ("Riser", 0,0, 200, 200, Justification::topLeft, 1, 1.0f);
}

void RiserAudioProcessorEditor::resized()
{
    sliderVolume.setBounds(50,100,200,200);
    sliderAttack.setBounds(150,100,200,200);
    sliderSustain.setBounds(250,100,200,200);
    sliderDecay.setBounds(350,100,200,200);
    sliderRelease.setBounds(450,100,200,200);
   
    sliderVolume.setSize(75, 75);
    sliderAttack.setSize(75,75);
    sliderSustain.setSize(75,75);
    sliderDecay.setSize(75,75);
    sliderRelease.setSize(75,75);
}

void RiserAudioProcessorEditor::timerCallback()
{
    RiserAudioProcessor* processor = getProcessor();

    sliderVolume.setValue(processor->Volume, dontSendNotification);
    sliderAttack.setValue(processor->Attack, dontSendNotification);
    sliderDecay.setValue(processor->Decay, dontSendNotification);
    sliderSustain.setValue(processor->Sustain, dontSendNotification);
    sliderRelease.setValue(processor->Release, dontSendNotification);
}

void RiserAudioProcessorEditor::sliderValueChanged (Slider* sliderMoved)
{
    if (&sliderVolume == sliderMoved)
    {
        getProcessor()->setParameterNotifyingHost (RiserAudioProcessor::volumeParameter, (float)sliderVolume.getValue());
	}   
    else if (&sliderAttack == sliderMoved)
    {
        getProcessor()->setParameterNotifyingHost (RiserAudioProcessor::attackParameter, (float)sliderAttack.getValue());
    }
    else if (&sliderDecay == sliderMoved)
    {
        getProcessor()->setParameterNotifyingHost (RiserAudioProcessor::decayParameter, (float)sliderDecay.getValue());
    }
    else if (&sliderSustain == sliderMoved)
    {
        getProcessor()->setParameterNotifyingHost (RiserAudioProcessor::sustainParameter, (float)sliderSustain.getValue());
    }
    else if (&sliderRelease == sliderMoved)
    {
        getProcessor()->setParameterNotifyingHost (RiserAudioProcessor::releaseParameter, (float)sliderRelease.getValue());
    }
}


/*void RiserAudioProcessorEditor::buttonClicked (Button* button)
{
    if (&waveform == button)
    {
        if (waveform.getButtonText() == "Sine")
        {
            waveform.setButtonText("Saw");
            getProcessor().setParameterNotifyingHost (RiserAudioProcessor::waveformParameter, Saw);

        }
           
        else if (waveform.getButtonText() == "Saw")
        {
            waveform.setButtonText("Square");
            getProcessor().setParameterNotifyingHost(RiserAudioProcessor::waveformParameter, Square);
          
        }

        else if (waveform.getButtonText() == "Square")
        {
            waveform.setButtonText("Sine");
            getProcessor().setParameterNotifyingHost (RiserAudioProcessor::waveformParameter, Sine);
  
        }                
    }
}
*/