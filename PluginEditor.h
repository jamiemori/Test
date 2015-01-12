#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class TestAudioProcessorEditor  : public AudioProcessorEditor,
                                  public Slider::Listener,
                                  public Button::Listener,
                                  public Timer
{
public:

    TestAudioProcessorEditor (TestAudioProcessor&);
    ~TestAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;
    void timerCallback();
    void sliderValueChanged (Slider* sliderMoved) override; //Call sliderValueChanged function (pass SliderObject pointer)
    void buttonClicked (Button* button);

private:
    TestAudioProcessor& processor;
    Slider sliderVolume; //declare sliderVolume object
    Slider sliderFilter; //declare sliderFilter object
    Slider sliderOscfreq;
    ToggleButton buttonStart;

    TestAudioProcessor* getProcessor() const
    {
        return static_cast <TestAudioProcessor*> (getAudioProcessor());
    }
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
