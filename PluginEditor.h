/*
=================================================================================================================
Plugin Editor.h 

=================================================================================================================

*/
#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MinimalLook.h"
#include "PluginProcessor.h"

class RiserAudioProcessorEditor  :		public AudioProcessorEditor,
                                        public Slider::Listener,
                                        public Timer
{
public:

    RiserAudioProcessorEditor (RiserAudioProcessor&);
    ~RiserAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;
    void timerCallback();
    void sliderValueChanged (Slider* sliderMoved) override; 

private:

    // Processor object which holds the address of our RiserAudioProcessor class.
    // We need this object to notify our AudioProcessor class of any changes made to our child components.
    RiserAudioProcessor& processor;

    // Slider objects and their associated labels.  
    Slider sliderVolume, sliderAttack, sliderSustain, sliderDecay, sliderRelease;
    Label labelVolume, labelAttack, labelSustain, labelDecay, labelRelease;

    // Object overrides the default look and feel of our plugin.
    MinimalLook mlaf;

    // Font object to modify the font of the Riser logo and our lables.
    Font font;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RiserAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
