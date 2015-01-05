#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class TestAudioProcessorEditor  : public AudioProcessorEditor,
                                  private Slider::Listener
{
public:
    TestAudioProcessorEditor (TestAudioProcessor&);
    ~TestAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderMoved) override; //Call sliderValueChanged function (pass SliderObject pointer)

private:
    TestAudioProcessor& processor;
    Slider sliderVolume; //declare sliderVolume object
    Slider sliderFilter; //declare sliderFilter object

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
