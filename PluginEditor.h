#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MinimalLook.h"

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
    void sliderValueChanged (Slider* sliderMoved) override; //Call sliderValueChanged function (pass SliderObject pointer)

private:
    RiserAudioProcessor& processor;
    Slider sliderVolume, sliderAttack, sliderSustain, sliderDecay, sliderRelease;
    Label labelVolume, labelAttack, labelSustain, labelDecay, labelRelease;
    MinimalLook mlaf;
    Font font;
   
    RiserAudioProcessor* getProcessor() const
    {
        return static_cast <RiserAudioProcessor*> (getAudioProcessor());
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RiserAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
