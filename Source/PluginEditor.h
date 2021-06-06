/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_388D2EBDBB646058__
#define __JUCE_HEADER_388D2EBDBB646058__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CompressorAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Timer,
                                        public ButtonListener,
                                        public SliderListener
{
public:
    //==============================================================================
    CompressorAudioProcessorEditor (CompressorAudioProcessor* ownerFilter);
    ~CompressorAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void timerCallback();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    ScopedPointer<ResizableCornerComponent> resizer;
    ComponentBoundsConstrainer resizeLimits;



	AudioPlayHead::CurrentPositionInfo lastDisplayedPosition;

    CompressorAudioProcessor* getProcessor() const
    {
        return static_cast <CompressorAudioProcessor*> (getAudioProcessor());
    }

    void displayPositionInfo (const AudioPlayHead::CurrentPositionInfo& pos);

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> lowBypassButton;
    ScopedPointer<Slider> sliderThreshold;
    ScopedPointer<Label> label2;
    ScopedPointer<Slider> sliderRatio;
    ScopedPointer<Label> label3;
    ScopedPointer<Slider> sliderGain;
    ScopedPointer<Label> label7;
    ScopedPointer<Slider> sliderAttack;
    ScopedPointer<Label> label5;
    ScopedPointer<Slider> sliderRelease;
    ScopedPointer<Label> label6;
    ScopedPointer<Slider> sliderLPFFrequency;
    ScopedPointer<Label> label4;
    ScopedPointer<TextButton> midBypassButton;
    ScopedPointer<Slider> sliderThreshold2;
    ScopedPointer<Label> label8;
    ScopedPointer<Slider> sliderRatio2;
    ScopedPointer<Label> label9;
    ScopedPointer<Slider> sliderGain2;
    ScopedPointer<Label> label10;
    ScopedPointer<Slider> sliderAttack2;
    ScopedPointer<Label> label11;
    ScopedPointer<Slider> sliderRelease2;
    ScopedPointer<Label> label12;
    ScopedPointer<Slider> sliderHPFFrequency;
    ScopedPointer<Label> label13;
    ScopedPointer<TextButton> lowSoloButton;
    ScopedPointer<TextButton> midSoloButton;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label14;
    ScopedPointer<Label> label15;
    ScopedPointer<TextButton> highBypassButton;
    ScopedPointer<Slider> sliderThreshold3;
    ScopedPointer<Label> label16;
    ScopedPointer<Slider> sliderRatio3;
    ScopedPointer<Label> label17;
    ScopedPointer<Slider> sliderGain3;
    ScopedPointer<Label> label18;
    ScopedPointer<Slider> sliderAttack3;
    ScopedPointer<Label> label19;
    ScopedPointer<Slider> sliderRelease3;
    ScopedPointer<Label> label20;
    ScopedPointer<TextButton> highSoloButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_388D2EBDBB646058__
