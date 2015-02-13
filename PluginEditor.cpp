/*
=================================================================================================================
Plugin Editor.h 


=================================================================================================================

*/
#include "PluginEditor.h"

//==============================================================================
RiserAudioProcessorEditor::RiserAudioProcessorEditor (RiserAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Because we are using a customized look, we set the look and feel of our plugin 
    // by overriding the lookandfeel class with our minimallook class.
    setLookAndFeel (&mlaf);
    
    // We set the range and increment size of each slider object. 
    // Slider styles are an enumerated type. For the current implementation we do
    // not require a textbox for each slider. 
    sliderVolume.setRange(0, 1.0, 0.001);                           
    sliderVolume.setSliderStyle (Slider::RotaryVerticalDrag);       
    sliderVolume.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);    
    sliderVolume.addListener (this);                                

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

    // Make the objects visible in the parent component window.
    addAndMakeVisible (&sliderAttack);
	addAndMakeVisible (&sliderVolume);
    addAndMakeVisible (&sliderSustain);
    addAndMakeVisible (&sliderDecay);
    addAndMakeVisible (&sliderRelease);

    // Set the size of the component window and set timer to periodically check for changes in the GUI.
	setSize (550,200); 
    startTimer(50);

}

RiserAudioProcessorEditor::~RiserAudioProcessorEditor()
{
}

//==============================================================================
void RiserAudioProcessorEditor::paint (Graphics& g)
{
    // Fill our parent component with the black background.
    g.fillAll (Colours::black);

    // We call the setTypefaceName via the font object f and then set the font using the graphics object g.
    font.setTypefaceName("Gulim");
    g.setFont(font);

    // Drawing the Riser logo. First set the Color to a light blueish color, set the font to 61 and 
    // draw our fitted text. We then change the color of the font to white with a slightly 
    // larger font size and draw over the existing logo, which gives it a 3D look.
    g.setColour (Colour (0xff93bfd2));
    g.setFont(61.0f);
    g.drawFittedText ("Riser", 0,0, 200, 200, Justification::topLeft, 1, 1.0f);
    g.setColour (Colours::white);
    g.setFont(65.0f);
    g.drawFittedText ("Riser", 0,0, 200, 200, Justification::topLeft, 1, 1.0f);
}

void RiserAudioProcessorEditor::resized()
{
    // Setting the size and coordinate of our slider objects. 
    // In JUCE, the top left of the parent comoponent, i.e. the window in which our child  
    // components exist is (0,0). The positive coordinates are right and bottom for x and y respectively.  
    // The width and height of the child components span from the 
    // specified coordinates of each object. (x, y, x + width, y + height)
    sliderVolume.setBounds(50,100,75,75);
    sliderAttack.setBounds(150,100,75,75);
    sliderSustain.setBounds(250,100,75,75);
    sliderDecay.setBounds(350,100,75,75);
    sliderRelease.setBounds(450,100,75,75);
}

void RiserAudioProcessorEditor::timerCallback()
{
    // This method periodically checks whether the slider values have changed. (called every 50ms)
    // If the slider value has changed, we set a new value. A notification is not sent out to the host for this case. 
    sliderVolume.setValue(processor.getParameter(0), dontSendNotification);
    sliderAttack.setValue(processor.getParameter(1), dontSendNotification);
    sliderDecay.setValue(processor.getParameter(2), dontSendNotification);
    sliderSustain.setValue(processor.getParameter(3), dontSendNotification);
    sliderRelease.setValue(processor.getParameter(4), dontSendNotification);
}


void RiserAudioProcessorEditor::sliderValueChanged (Slider* sliderMoved)
{
    // Responds to user changes of the slider. When the user changes a parameter, this method will call 
    // the setParameter() method to change the value and will send a message to the host telling it about the change.
    if (&sliderVolume == sliderMoved)
    {
        processor.setParameterNotifyingHost (RiserAudioProcessor::volumeParameter, (float)sliderVolume.getValue());
	}   
    else if (&sliderAttack == sliderMoved)
    {
        processor.setParameterNotifyingHost (RiserAudioProcessor::attackParameter, (float)sliderAttack.getValue());
    }
    else if (&sliderDecay == sliderMoved)
    {
        processor.setParameterNotifyingHost (RiserAudioProcessor::decayParameter, (float)sliderDecay.getValue());
    }
    else if (&sliderSustain == sliderMoved)
    {
        processor.setParameterNotifyingHost (RiserAudioProcessor::sustainParameter, (float)sliderSustain.getValue());
    }
    else if (&sliderRelease == sliderMoved)
    {
        processor.setParameterNotifyingHost (RiserAudioProcessor::releaseParameter, (float)sliderRelease.getValue());
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