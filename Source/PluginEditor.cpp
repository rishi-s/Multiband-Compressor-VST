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

//[Headers] You can add your own extra header files here...
#include "PluginProcessor.h"
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...



//[/MiscUserDefs]

//==============================================================================
CompressorAudioProcessorEditor::CompressorAudioProcessorEditor (CompressorAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (lowBypassButton = new TextButton ("on off button"));
    lowBypassButton->setButtonText (TRANS("Bypass"));
    lowBypassButton->addListener (this);
    lowBypassButton->setColour (TextButton::buttonColourId, Colour (0xff615a5a));
    lowBypassButton->setColour (TextButton::buttonOnColourId, Colours::red);

    addAndMakeVisible (sliderThreshold = new Slider ("new slider"));
    sliderThreshold->setRange (-60, 12, -60);
    sliderThreshold->setSliderStyle (Slider::Rotary);
    sliderThreshold->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderThreshold->setColour (Slider::trackColourId, Colour (0x7fffffff));
    sliderThreshold->setColour (Slider::textBoxBackgroundColourId, Colour (0xff887373));
    sliderThreshold->setColour (Slider::textBoxOutlineColourId, Colour (0xff887373));
    sliderThreshold->addListener (this);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Threshold (dB)")));
    label2->setFont (Font (13.00f, Font::plain));
    label2->setJustificationType (Justification::centred);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderRatio = new Slider ("new slider"));
    sliderRatio->setRange (1, 30, 0.1);
    sliderRatio->setSliderStyle (Slider::Rotary);
    sliderRatio->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderRatio->setColour (Slider::textBoxBackgroundColourId, Colour (0xff887373));
    sliderRatio->setColour (Slider::textBoxOutlineColourId, Colour (0xff887373));
    sliderRatio->addListener (this);

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Ratio")));
    label3->setFont (Font (13.00f, Font::plain));
    label3->setJustificationType (Justification::centred);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderGain = new Slider ("new slider"));
    sliderGain->setRange (-20, 20, 0.1);
    sliderGain->setSliderStyle (Slider::Rotary);
    sliderGain->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderGain->setColour (Slider::textBoxBackgroundColourId, Colour (0xff887373));
    sliderGain->setColour (Slider::textBoxOutlineColourId, Colour (0xff887373));
    sliderGain->addListener (this);

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("Gain")));
    label7->setFont (Font (13.00f, Font::plain));
    label7->setJustificationType (Justification::centred);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderAttack = new Slider ("new slider"));
    sliderAttack->setRange (0, 200, 0.1);
    sliderAttack->setSliderStyle (Slider::Rotary);
    sliderAttack->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderAttack->setColour (Slider::textBoxBackgroundColourId, Colour (0xff887373));
    sliderAttack->setColour (Slider::textBoxOutlineColourId, Colour (0xff887373));
    sliderAttack->addListener (this);

    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Attack (ms)")));
    label5->setFont (Font (13.00f, Font::plain));
    label5->setJustificationType (Justification::centred);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderRelease = new Slider ("new slider"));
    sliderRelease->setRange (2, 2000, 0.1);
    sliderRelease->setSliderStyle (Slider::Rotary);
    sliderRelease->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderRelease->setColour (Slider::textBoxBackgroundColourId, Colour (0xff887373));
    sliderRelease->setColour (Slider::textBoxOutlineColourId, Colour (0xff887373));
    sliderRelease->addListener (this);

    addAndMakeVisible (label6 = new Label ("new label",
                                           TRANS("Release (ms)")));
    label6->setFont (Font (13.00f, Font::plain));
    label6->setJustificationType (Justification::centred);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderLPFFrequency = new Slider ("LPFFrequency"));
    sliderLPFFrequency->setRange (20, 650, 5);
    sliderLPFFrequency->setSliderStyle (Slider::Rotary);
    sliderLPFFrequency->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sliderLPFFrequency->setColour (Slider::rotarySliderFillColourId, Colours::cornflowerblue);
    sliderLPFFrequency->setColour (Slider::textBoxBackgroundColourId, Colour (0xff887373));
    sliderLPFFrequency->setColour (Slider::textBoxOutlineColourId, Colour (0xff887373));
    sliderLPFFrequency->addListener (this);

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Cutoff (Hz):")));
    label4->setFont (Font (13.00f, Font::plain));
    label4->setJustificationType (Justification::centred);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (midBypassButton = new TextButton ("on off button"));
    midBypassButton->setButtonText (TRANS("Bypass"));
    midBypassButton->addListener (this);
    midBypassButton->setColour (TextButton::buttonColourId, Colour (0xff615a5a));
    midBypassButton->setColour (TextButton::buttonOnColourId, Colours::red);

    addAndMakeVisible (sliderThreshold2 = new Slider ("new slider"));
    sliderThreshold2->setRange (-60, 12, -60);
    sliderThreshold2->setSliderStyle (Slider::Rotary);
    sliderThreshold2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderThreshold2->setColour (Slider::trackColourId, Colour (0x7fffffff));
    sliderThreshold2->setColour (Slider::textBoxBackgroundColourId, Colour (0xff887373));
    sliderThreshold2->setColour (Slider::textBoxOutlineColourId, Colour (0xff887373));
    sliderThreshold2->addListener (this);

    addAndMakeVisible (label8 = new Label ("new label",
                                           TRANS("Threshold (dB)")));
    label8->setFont (Font (13.00f, Font::plain));
    label8->setJustificationType (Justification::centred);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderRatio2 = new Slider ("new slider"));
    sliderRatio2->setRange (1, 30, 0.1);
    sliderRatio2->setSliderStyle (Slider::Rotary);
    sliderRatio2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderRatio2->setColour (Slider::textBoxBackgroundColourId, Colour (0xff887373));
    sliderRatio2->setColour (Slider::textBoxOutlineColourId, Colour (0xff887373));
    sliderRatio2->addListener (this);

    addAndMakeVisible (label9 = new Label ("new label",
                                           TRANS("Ratio")));
    label9->setFont (Font (13.00f, Font::plain));
    label9->setJustificationType (Justification::centred);
    label9->setEditable (false, false, false);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderGain2 = new Slider ("new slider"));
    sliderGain2->setRange (-20, 20, 0.1);
    sliderGain2->setSliderStyle (Slider::Rotary);
    sliderGain2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderGain2->setColour (Slider::textBoxBackgroundColourId, Colour (0xff887373));
    sliderGain2->setColour (Slider::textBoxOutlineColourId, Colour (0xff887373));
    sliderGain2->addListener (this);

    addAndMakeVisible (label10 = new Label ("new label",
                                            TRANS("Gain")));
    label10->setFont (Font (13.00f, Font::plain));
    label10->setJustificationType (Justification::centred);
    label10->setEditable (false, false, false);
    label10->setColour (TextEditor::textColourId, Colours::black);
    label10->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderAttack2 = new Slider ("new slider"));
    sliderAttack2->setRange (0, 200, 0.1);
    sliderAttack2->setSliderStyle (Slider::Rotary);
    sliderAttack2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderAttack2->setColour (Slider::textBoxBackgroundColourId, Colour (0xff887373));
    sliderAttack2->setColour (Slider::textBoxOutlineColourId, Colour (0xff887373));
    sliderAttack2->addListener (this);

    addAndMakeVisible (label11 = new Label ("new label",
                                            TRANS("Attack (ms)")));
    label11->setFont (Font (13.00f, Font::plain));
    label11->setJustificationType (Justification::centred);
    label11->setEditable (false, false, false);
    label11->setColour (TextEditor::textColourId, Colours::black);
    label11->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderRelease2 = new Slider ("new slider"));
    sliderRelease2->setRange (2, 2000, 0.1);
    sliderRelease2->setSliderStyle (Slider::Rotary);
    sliderRelease2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderRelease2->setColour (Slider::textBoxBackgroundColourId, Colour (0xff887373));
    sliderRelease2->setColour (Slider::textBoxOutlineColourId, Colour (0xff887373));
    sliderRelease2->addListener (this);

    addAndMakeVisible (label12 = new Label ("new label",
                                            TRANS("Release (ms)")));
    label12->setFont (Font (13.00f, Font::plain));
    label12->setJustificationType (Justification::centred);
    label12->setEditable (false, false, false);
    label12->setColour (TextEditor::textColourId, Colours::black);
    label12->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderHPFFrequency = new Slider ("HPFFrequency"));
    sliderHPFFrequency->setRange (650, 20000, 25);
    sliderHPFFrequency->setSliderStyle (Slider::Rotary);
    sliderHPFFrequency->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    sliderHPFFrequency->setColour (Slider::rotarySliderFillColourId, Colours::cornflowerblue);
    sliderHPFFrequency->setColour (Slider::textBoxBackgroundColourId, Colour (0xff887373));
    sliderHPFFrequency->setColour (Slider::textBoxOutlineColourId, Colour (0xff887373));
    sliderHPFFrequency->addListener (this);

    addAndMakeVisible (label13 = new Label ("new label",
                                            TRANS("Cutoff (Hz)")));
    label13->setFont (Font (13.00f, Font::plain));
    label13->setJustificationType (Justification::centred);
    label13->setEditable (false, false, false);
    label13->setColour (TextEditor::textColourId, Colours::black);
    label13->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lowSoloButton = new TextButton ("on off button"));
    lowSoloButton->setButtonText (TRANS("Solo"));
    lowSoloButton->addListener (this);
    lowSoloButton->setColour (TextButton::buttonColourId, Colour (0xff615a5a));
    lowSoloButton->setColour (TextButton::buttonOnColourId, Colours::chartreuse);

    addAndMakeVisible (midSoloButton = new TextButton ("on off button"));
    midSoloButton->setButtonText (TRANS("Solo"));
    midSoloButton->addListener (this);
    midSoloButton->setColour (TextButton::buttonColourId, Colour (0xff615a5a));
    midSoloButton->setColour (TextButton::buttonOnColourId, Colours::chartreuse);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Low")));
    label->setFont (Font ("Avenir", 35.00f, Font::bold));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label14 = new Label ("new label",
                                            TRANS("Mid")));
    label14->setFont (Font ("Avenir", 35.00f, Font::bold));
    label14->setJustificationType (Justification::centred);
    label14->setEditable (false, false, false);
    label14->setColour (TextEditor::textColourId, Colours::black);
    label14->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label15 = new Label ("new label",
                                            TRANS("High")));
    label15->setFont (Font ("Avenir", 35.00f, Font::bold));
    label15->setJustificationType (Justification::centred);
    label15->setEditable (false, false, false);
    label15->setColour (TextEditor::textColourId, Colours::black);
    label15->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (highBypassButton = new TextButton ("on off button"));
    highBypassButton->setButtonText (TRANS("Bypass"));
    highBypassButton->addListener (this);
    highBypassButton->setColour (TextButton::buttonColourId, Colour (0xff615a5a));
    highBypassButton->setColour (TextButton::buttonOnColourId, Colours::red);

    addAndMakeVisible (sliderThreshold3 = new Slider ("new slider"));
    sliderThreshold3->setRange (-60, 12, -60);
    sliderThreshold3->setSliderStyle (Slider::Rotary);
    sliderThreshold3->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderThreshold3->setColour (Slider::trackColourId, Colour (0x7fffffff));
    sliderThreshold3->setColour (Slider::textBoxBackgroundColourId, Colour (0xff887373));
    sliderThreshold3->setColour (Slider::textBoxOutlineColourId, Colour (0xff887373));
    sliderThreshold3->addListener (this);

    addAndMakeVisible (label16 = new Label ("new label",
                                            TRANS("Threshold (dB)")));
    label16->setFont (Font (13.00f, Font::plain));
    label16->setJustificationType (Justification::centred);
    label16->setEditable (false, false, false);
    label16->setColour (TextEditor::textColourId, Colours::black);
    label16->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderRatio3 = new Slider ("new slider"));
    sliderRatio3->setRange (1, 30, 0.1);
    sliderRatio3->setSliderStyle (Slider::Rotary);
    sliderRatio3->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderRatio3->setColour (Slider::textBoxBackgroundColourId, Colour (0xff887373));
    sliderRatio3->setColour (Slider::textBoxOutlineColourId, Colour (0xff887373));
    sliderRatio3->addListener (this);

    addAndMakeVisible (label17 = new Label ("new label",
                                            TRANS("Ratio")));
    label17->setFont (Font (13.00f, Font::plain));
    label17->setJustificationType (Justification::centred);
    label17->setEditable (false, false, false);
    label17->setColour (TextEditor::textColourId, Colours::black);
    label17->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderGain3 = new Slider ("new slider"));
    sliderGain3->setRange (-20, 20, 0.1);
    sliderGain3->setSliderStyle (Slider::Rotary);
    sliderGain3->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderGain3->setColour (Slider::textBoxBackgroundColourId, Colour (0xff887373));
    sliderGain3->setColour (Slider::textBoxOutlineColourId, Colour (0xff887373));
    sliderGain3->addListener (this);

    addAndMakeVisible (label18 = new Label ("new label",
                                            TRANS("Gain")));
    label18->setFont (Font (13.00f, Font::plain));
    label18->setJustificationType (Justification::centred);
    label18->setEditable (false, false, false);
    label18->setColour (TextEditor::textColourId, Colours::black);
    label18->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderAttack3 = new Slider ("new slider"));
    sliderAttack3->setRange (0, 200, 0.1);
    sliderAttack3->setSliderStyle (Slider::Rotary);
    sliderAttack3->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderAttack3->setColour (Slider::textBoxBackgroundColourId, Colour (0xff887373));
    sliderAttack3->setColour (Slider::textBoxOutlineColourId, Colour (0xff887373));
    sliderAttack3->addListener (this);

    addAndMakeVisible (label19 = new Label ("new label",
                                            TRANS("Attack (ms)")));
    label19->setFont (Font (13.00f, Font::plain));
    label19->setJustificationType (Justification::centred);
    label19->setEditable (false, false, false);
    label19->setColour (TextEditor::textColourId, Colours::black);
    label19->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderRelease3 = new Slider ("new slider"));
    sliderRelease3->setRange (2, 2000, 0.1);
    sliderRelease3->setSliderStyle (Slider::Rotary);
    sliderRelease3->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderRelease3->setColour (Slider::textBoxBackgroundColourId, Colour (0xff887373));
    sliderRelease3->setColour (Slider::textBoxOutlineColourId, Colour (0xff887373));
    sliderRelease3->addListener (this);

    addAndMakeVisible (label20 = new Label ("new label",
                                            TRANS("Release (ms)")));
    label20->setFont (Font (13.00f, Font::plain));
    label20->setJustificationType (Justification::centred);
    label20->setEditable (false, false, false);
    label20->setColour (TextEditor::textColourId, Colours::black);
    label20->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (highSoloButton = new TextButton ("on off button"));
    highSoloButton->setButtonText (TRANS("Solo"));
    highSoloButton->addListener (this);
    highSoloButton->setColour (TextButton::buttonColourId, Colour (0xff615a5a));
    highSoloButton->setColour (TextButton::buttonOnColourId, Colours::chartreuse);


    //[UserPreSize]
    addAndMakeVisible (resizer = new ResizableCornerComponent (this, &resizeLimits));
    resizeLimits.setSizeLimits (150, 150, 850, 290);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	lowBypassButton->setClickingTogglesState(true);
	midBypassButton->setClickingTogglesState(true);
	highBypassButton->setClickingTogglesState(true);
	lowSoloButton->setClickingTogglesState(true);
	midSoloButton->setClickingTogglesState(true);
	highSoloButton->setClickingTogglesState(true);
    startTimer (50);

    //[/Constructor]
}

CompressorAudioProcessorEditor::~CompressorAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lowBypassButton = nullptr;
    sliderThreshold = nullptr;
    label2 = nullptr;
    sliderRatio = nullptr;
    label3 = nullptr;
    sliderGain = nullptr;
    label7 = nullptr;
    sliderAttack = nullptr;
    label5 = nullptr;
    sliderRelease = nullptr;
    label6 = nullptr;
    sliderLPFFrequency = nullptr;
    label4 = nullptr;
    midBypassButton = nullptr;
    sliderThreshold2 = nullptr;
    label8 = nullptr;
    sliderRatio2 = nullptr;
    label9 = nullptr;
    sliderGain2 = nullptr;
    label10 = nullptr;
    sliderAttack2 = nullptr;
    label11 = nullptr;
    sliderRelease2 = nullptr;
    label12 = nullptr;
    sliderHPFFrequency = nullptr;
    label13 = nullptr;
    lowSoloButton = nullptr;
    midSoloButton = nullptr;
    label = nullptr;
    label14 = nullptr;
    label15 = nullptr;
    highBypassButton = nullptr;
    sliderThreshold3 = nullptr;
    label16 = nullptr;
    sliderRatio3 = nullptr;
    label17 = nullptr;
    sliderGain3 = nullptr;
    label18 = nullptr;
    sliderAttack3 = nullptr;
    label19 = nullptr;
    sliderRelease3 = nullptr;
    label20 = nullptr;
    highSoloButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CompressorAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff887373));

    g.setColour (Colours::black);
    g.fillRoundedRectangle (200.0f, 80.0f, 1.0f, 310.0f, 10.000f);

    g.setColour (Colours::black);
    g.fillRoundedRectangle (400.0f, 80.0f, 1.0f, 310.0f, 10.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CompressorAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    lowBypassButton->setBounds (20, 65, 60, 30);
    sliderThreshold->setBounds (10, 162, 80, 80);
    label2->setBounds (0, 242, 100, 30);
    sliderRatio->setBounds (10, 289, 80, 80);
    label3->setBounds (10, 369, 80, 30);
    sliderGain->setBounds (110, 302, 70, 70);
    label7->setBounds (95, 368, 100, 30);
    sliderAttack->setBounds (110, 82, 70, 70);
    label5->setBounds (95, 148, 100, 30);
    sliderRelease->setBounds (110, 192, 70, 70);
    label6->setBounds (95, 258, 100, 30);
    sliderLPFFrequency->setBounds (90, 10, 140, 60);
    label4->setBounds (85, 7, 90, 30);
    midBypassButton->setBounds (230, 65, 60, 30);
    sliderThreshold2->setBounds (220, 162, 80, 80);
    label8->setBounds (210, 242, 100, 30);
    sliderRatio2->setBounds (220, 289, 80, 80);
    label9->setBounds (220, 369, 80, 30);
    sliderGain2->setBounds (320, 302, 70, 70);
    label10->setBounds (305, 368, 100, 30);
    sliderAttack2->setBounds (320, 82, 70, 70);
    label11->setBounds (305, 148, 100, 30);
    sliderRelease2->setBounds (320, 192, 70, 70);
    label12->setBounds (305, 258, 100, 30);
    sliderHPFFrequency->setBounds (370, 10, 140, 60);
    label13->setBounds (420, 7, 100, 30);
    lowSoloButton->setBounds (20, 115, 60, 30);
    midSoloButton->setBounds (230, 115, 60, 30);
    label->setBounds (5, 10, 90, 30);
    label14->setBounds (255, 10, 90, 30);
    label15->setBounds (510, 10, 90, 30);
    highBypassButton->setBounds (430, 65, 60, 30);
    sliderThreshold3->setBounds (420, 162, 80, 80);
    label16->setBounds (410, 242, 100, 30);
    sliderRatio3->setBounds (420, 289, 80, 80);
    label17->setBounds (420, 369, 80, 30);
    sliderGain3->setBounds (520, 302, 70, 70);
    label18->setBounds (505, 368, 100, 30);
    sliderAttack3->setBounds (520, 82, 70, 70);
    label19->setBounds (505, 148, 100, 30);
    sliderRelease3->setBounds (520, 192, 70, 70);
    label20->setBounds (505, 258, 100, 30);
    highSoloButton->setBounds (430, 115, 60, 30);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CompressorAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == lowBypassButton)
    {
        //[UserButtonCode_lowBypassButton] -- add your button handler code here..
        getProcessor()->lowBandBypass = lowBypassButton->getToggleState();
        //[/UserButtonCode_lowBypassButton]
    }
    else if (buttonThatWasClicked == midBypassButton)
    {
        //[UserButtonCode_midBypassButton] -- add your button handler code here..
        getProcessor()->midBandBypass = midBypassButton->getToggleState();
        //[/UserButtonCode_midBypassButton]
    }
    else if (buttonThatWasClicked == lowSoloButton)
    {
        //[UserButtonCode_lowSoloButton] -- add your button handler code here..
        getProcessor()->lowBandSolo = lowSoloButton->getToggleState();
        //[/UserButtonCode_lowSoloButton]
    }
    else if (buttonThatWasClicked == midSoloButton)
    {
        //[UserButtonCode_midSoloButton] -- add your button handler code here..
        getProcessor()->midBandSolo = midSoloButton->getToggleState();
        //[/UserButtonCode_midSoloButton]
    }
    else if (buttonThatWasClicked == highBypassButton)
    {
        //[UserButtonCode_highBypassButton] -- add your button handler code here..
        getProcessor()->highBandBypass = highBypassButton->getToggleState();
        //[/UserButtonCode_highBypassButton]
    }
    else if (buttonThatWasClicked == highSoloButton)
    {
        //[UserButtonCode_highSoloButton] -- add your button handler code here..
        getProcessor()->highBandSolo = highSoloButton->getToggleState();
        //[/UserButtonCode_highSoloButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void CompressorAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sliderThreshold)
    {
        //[UserSliderCode_sliderThreshold] -- add your slider handling code here..
		getProcessor()->setThresholdLow(sliderThreshold->getValue());
        //[/UserSliderCode_sliderThreshold]
    }
    else if (sliderThatWasMoved == sliderRatio)
    {
        //[UserSliderCode_sliderRatio] -- add your slider handling code here..
		getProcessor()->setRatioLow(sliderRatio->getValue());
        //[/UserSliderCode_sliderRatio]
    }
    else if (sliderThatWasMoved == sliderGain)
    {
        //[UserSliderCode_sliderGain] -- add your slider handling code here..
		getProcessor()->setGainLow(sliderGain->getValue());
        //[/UserSliderCode_sliderGain]
    }
    else if (sliderThatWasMoved == sliderAttack)
    {
        //[UserSliderCode_sliderAttack] -- add your slider handling code here..
		getProcessor()->setAttackTimeLow(sliderAttack->getValue());
        //[/UserSliderCode_sliderAttack]
    }
    else if (sliderThatWasMoved == sliderRelease)
    {
        //[UserSliderCode_sliderRelease] -- add your slider handling code here..
 		getProcessor()->setReleaseTimeLow(sliderRelease->getValue());
        //[/UserSliderCode_sliderRelease]
    }
    else if (sliderThatWasMoved == sliderLPFFrequency)
    {
        //[UserSliderCode_sliderLPFFrequency] -- add your slider handling code here..
		getProcessor()->setCutoffFrequencyLow(sliderLPFFrequency->getValue());
        //[/UserSliderCode_sliderLPFFrequency]
    }
    else if (sliderThatWasMoved == sliderThreshold2)
    {
        //[UserSliderCode_sliderThreshold2] -- add your slider handling code here..
        getProcessor()->setThresholdMid(sliderThreshold2->getValue());
        //[/UserSliderCode_sliderThreshold2]
    }
    else if (sliderThatWasMoved == sliderRatio2)
    {
        //[UserSliderCode_sliderRatio2] -- add your slider handling code here..
        getProcessor()->setRatioMid(sliderRatio2->getValue());
        //[/UserSliderCode_sliderRatio2]
    }
    else if (sliderThatWasMoved == sliderGain2)
    {
        //[UserSliderCode_sliderGain2] -- add your slider handling code here..
        getProcessor()->setGainMid(sliderGain2->getValue());
        //[/UserSliderCode_sliderGain2]
    }
    else if (sliderThatWasMoved == sliderAttack2)
    {
        //[UserSliderCode_sliderAttack2] -- add your slider handling code here..
        getProcessor()->setAttackTimeMid(sliderAttack2->getValue());
        //[/UserSliderCode_sliderAttack2]
    }
    else if (sliderThatWasMoved == sliderRelease2)
    {
        //[UserSliderCode_sliderRelease2] -- add your slider handling code here..
        getProcessor()->setReleaseTimeMid(sliderRelease2->getValue());
        //[/UserSliderCode_sliderRelease2]
    }
    else if (sliderThatWasMoved == sliderHPFFrequency)
    {
        //[UserSliderCode_sliderHPFFrequency] -- add your slider handling code here..
        getProcessor()->setCutoffFrequencyHigh(sliderHPFFrequency->getValue());
        //[/UserSliderCode_sliderHPFFrequency]
    }
    else if (sliderThatWasMoved == sliderThreshold3)
    {
        //[UserSliderCode_sliderThreshold3] -- add your slider handling code here..
        getProcessor()->setThresholdHigh(sliderThreshold3->getValue());
        //[/UserSliderCode_sliderThreshold3]
    }
    else if (sliderThatWasMoved == sliderRatio3)
    {
        //[UserSliderCode_sliderRatio3] -- add your slider handling code here..
        getProcessor()->setRatioHigh(sliderRatio3->getValue());
        //[/UserSliderCode_sliderRatio3]
    }
    else if (sliderThatWasMoved == sliderGain3)
    {
        //[UserSliderCode_sliderGain3] -- add your slider handling code here..
        getProcessor()->setGainHigh(sliderGain3->getValue());
        //[/UserSliderCode_sliderGain3]
    }
    else if (sliderThatWasMoved == sliderAttack3)
    {
        //[UserSliderCode_sliderAttack3] -- add your slider handling code here..
        getProcessor()->setAttackTimeHigh(sliderAttack3->getValue());
        //[/UserSliderCode_sliderAttack3]
    }
    else if (sliderThatWasMoved == sliderRelease3)
    {
        //[UserSliderCode_sliderRelease3] -- add your slider handling code here..
        getProcessor()->setReleaseTimeHigh(sliderRelease3->getValue());
        //[/UserSliderCode_sliderRelease3]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...


// This timer periodically checks whether any of the filter's parameters have changed...

void CompressorAudioProcessorEditor::timerCallback()
{

		// Display the ON/OFF button in its correct state
	if (lowBypassButton->getToggleState()) lowBypassButton->setToggleState(true, dontSendNotification);
	else lowBypassButton->setToggleState(false, dontSendNotification);
	if (lowSoloButton->getToggleState()) lowSoloButton->setToggleState(true, dontSendNotification);
	else lowSoloButton->setToggleState(false, dontSendNotification);
	if (midBypassButton->getToggleState()) midBypassButton->setToggleState(true, dontSendNotification);
	else midBypassButton->setToggleState(false, dontSendNotification);
	if (midSoloButton->getToggleState()) midSoloButton->setToggleState(true, dontSendNotification);
	else midSoloButton->setToggleState(false, dontSendNotification);
	if (highBypassButton->getToggleState()) highBypassButton->setToggleState(true, dontSendNotification);
	else highBypassButton->setToggleState(false, dontSendNotification);
	if (highSoloButton->getToggleState()) highSoloButton->setToggleState(true, dontSendNotification);
	else highSoloButton->setToggleState(false, dontSendNotification);
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CompressorAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="CompressorAudioProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor (ownerFilter)"
                 snapPixels="10" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff887373">
    <ROUNDRECT pos="200 80 1 310" cornerSize="10" fill="solid: ff000000" hasStroke="0"/>
    <ROUNDRECT pos="400 80 1 310" cornerSize="10" fill="solid: ff000000" hasStroke="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="on off button" id="74cbf2a91094eddb" memberName="lowBypassButton"
              virtualName="" explicitFocusOrder="0" pos="20 65 60 30" bgColOff="ff615a5a"
              bgColOn="ffff0000" buttonText="Bypass" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <SLIDER name="new slider" id="eab20a7ec2124789" memberName="sliderThreshold"
          virtualName="" explicitFocusOrder="0" pos="10 162 80 80" trackcol="7fffffff"
          textboxbkgd="ff887373" textboxoutline="ff887373" min="-60" max="12"
          int="-60" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="a68032c64d515cea" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="0 242 100 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Threshold (dB)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="2707ee7701d502c1" memberName="sliderRatio"
          virtualName="" explicitFocusOrder="0" pos="10 289 80 80" textboxbkgd="ff887373"
          textboxoutline="ff887373" min="1" max="30" int="0.10000000000000000555"
          style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="3e752a04cae9a566" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="10 369 80 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Ratio" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="13"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="c28d5a8c02343352" memberName="sliderGain"
          virtualName="" explicitFocusOrder="0" pos="110 302 70 70" textboxbkgd="ff887373"
          textboxoutline="ff887373" min="-20" max="20" int="0.10000000000000000555"
          style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="e3bb48b03347cb15" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="95 368 100 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Gain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="13"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="153b41a7187b4d90" memberName="sliderAttack"
          virtualName="" explicitFocusOrder="0" pos="110 82 70 70" textboxbkgd="ff887373"
          textboxoutline="ff887373" min="0" max="200" int="0.10000000000000000555"
          style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="ada7a829c3c54075" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="95 148 100 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Attack (ms)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="147aff9502a416d7" memberName="sliderRelease"
          virtualName="" explicitFocusOrder="0" pos="110 192 70 70" textboxbkgd="ff887373"
          textboxoutline="ff887373" min="2" max="2000" int="0.10000000000000000555"
          style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="a04b8eaf5c6b5440" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="95 258 100 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Release (ms)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <SLIDER name="LPFFrequency" id="83872e148e4ef4d2" memberName="sliderLPFFrequency"
          virtualName="" explicitFocusOrder="0" pos="90 10 140 60" rotarysliderfill="ff6495ed"
          textboxbkgd="ff887373" textboxoutline="ff887373" min="20" max="650"
          int="5" style="Rotary" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="f6907e1a5a6cefc5" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="85 7 90 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Cutoff (Hz):" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="on off button" id="9d2f98df0211611c" memberName="midBypassButton"
              virtualName="" explicitFocusOrder="0" pos="230 65 60 30" bgColOff="ff615a5a"
              bgColOn="ffff0000" buttonText="Bypass" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <SLIDER name="new slider" id="fb0b743413733c8b" memberName="sliderThreshold2"
          virtualName="" explicitFocusOrder="0" pos="220 162 80 80" trackcol="7fffffff"
          textboxbkgd="ff887373" textboxoutline="ff887373" min="-60" max="12"
          int="-60" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="4907bf757fbb84d2" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="210 242 100 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Threshold (dB)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="c61d0286f5f504ab" memberName="sliderRatio2"
          virtualName="" explicitFocusOrder="0" pos="220 289 80 80" textboxbkgd="ff887373"
          textboxoutline="ff887373" min="1" max="30" int="0.10000000000000000555"
          style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="e5b4cf6a35604a07" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="220 369 80 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Ratio" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="13"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="d6cc9f70051eb68d" memberName="sliderGain2"
          virtualName="" explicitFocusOrder="0" pos="320 302 70 70" textboxbkgd="ff887373"
          textboxoutline="ff887373" min="-20" max="20" int="0.10000000000000000555"
          style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="82022981cfecfc82" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="305 368 100 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Gain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="13"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="af7e0446144da9b9" memberName="sliderAttack2"
          virtualName="" explicitFocusOrder="0" pos="320 82 70 70" textboxbkgd="ff887373"
          textboxoutline="ff887373" min="0" max="200" int="0.10000000000000000555"
          style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="98618b057a155140" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="305 148 100 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Attack (ms)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="cb065a5f9b1485e0" memberName="sliderRelease2"
          virtualName="" explicitFocusOrder="0" pos="320 192 70 70" textboxbkgd="ff887373"
          textboxoutline="ff887373" min="2" max="2000" int="0.10000000000000000555"
          style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="5f83e255de047aab" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="305 258 100 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Release (ms)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <SLIDER name="HPFFrequency" id="25288d4075269430" memberName="sliderHPFFrequency"
          virtualName="" explicitFocusOrder="0" pos="370 10 140 60" rotarysliderfill="ff6495ed"
          textboxbkgd="ff887373" textboxoutline="ff887373" min="650" max="20000"
          int="25" style="Rotary" textBoxPos="TextBoxRight" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="be0c67a39d8ecc0c" memberName="label13" virtualName=""
         explicitFocusOrder="0" pos="420 7 100 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Cutoff (Hz)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="on off button" id="abbe10688048357f" memberName="lowSoloButton"
              virtualName="" explicitFocusOrder="0" pos="20 115 60 30" bgColOff="ff615a5a"
              bgColOn="ff7fff00" buttonText="Solo" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="on off button" id="f277dc15a1438d36" memberName="midSoloButton"
              virtualName="" explicitFocusOrder="0" pos="230 115 60 30" bgColOff="ff615a5a"
              bgColOn="ff7fff00" buttonText="Solo" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="new label" id="f79472c96ac553bc" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="5 10 90 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Low" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Avenir" fontsize="35" bold="1"
         italic="0" justification="36"/>
  <LABEL name="new label" id="22636f3df62d205f" memberName="label14" virtualName=""
         explicitFocusOrder="0" pos="255 10 90 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Mid" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Avenir" fontsize="35" bold="1"
         italic="0" justification="36"/>
  <LABEL name="new label" id="27db558778c6e660" memberName="label15" virtualName=""
         explicitFocusOrder="0" pos="510 10 90 30" edTextCol="ff000000"
         edBkgCol="0" labelText="High" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Avenir" fontsize="35" bold="1"
         italic="0" justification="36"/>
  <TEXTBUTTON name="on off button" id="f70da3f7382e08c7" memberName="highBypassButton"
              virtualName="" explicitFocusOrder="0" pos="430 65 60 30" bgColOff="ff615a5a"
              bgColOn="ffff0000" buttonText="Bypass" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <SLIDER name="new slider" id="a39b030232d0ca41" memberName="sliderThreshold3"
          virtualName="" explicitFocusOrder="0" pos="420 162 80 80" trackcol="7fffffff"
          textboxbkgd="ff887373" textboxoutline="ff887373" min="-60" max="12"
          int="-60" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="da0131f7332330b2" memberName="label16" virtualName=""
         explicitFocusOrder="0" pos="410 242 100 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Threshold (dB)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="98e258ef44cbc9d4" memberName="sliderRatio3"
          virtualName="" explicitFocusOrder="0" pos="420 289 80 80" textboxbkgd="ff887373"
          textboxoutline="ff887373" min="1" max="30" int="0.10000000000000000555"
          style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="d51adf5563d21f3f" memberName="label17" virtualName=""
         explicitFocusOrder="0" pos="420 369 80 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Ratio" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="13"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="a2e5c9c2867f4b8a" memberName="sliderGain3"
          virtualName="" explicitFocusOrder="0" pos="520 302 70 70" textboxbkgd="ff887373"
          textboxoutline="ff887373" min="-20" max="20" int="0.10000000000000000555"
          style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="890de222d5ba467a" memberName="label18" virtualName=""
         explicitFocusOrder="0" pos="505 368 100 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Gain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="13"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="c2a4b1d137291ad5" memberName="sliderAttack3"
          virtualName="" explicitFocusOrder="0" pos="520 82 70 70" textboxbkgd="ff887373"
          textboxoutline="ff887373" min="0" max="200" int="0.10000000000000000555"
          style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="be30018411160f92" memberName="label19" virtualName=""
         explicitFocusOrder="0" pos="505 148 100 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Attack (ms)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="390eb941b115977a" memberName="sliderRelease3"
          virtualName="" explicitFocusOrder="0" pos="520 192 70 70" textboxbkgd="ff887373"
          textboxoutline="ff887373" min="2" max="2000" int="0.10000000000000000555"
          style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="4bb42ab8085de584" memberName="label20" virtualName=""
         explicitFocusOrder="0" pos="505 258 100 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Release (ms)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="on off button" id="595d1aab864a2161" memberName="highSoloButton"
              virtualName="" explicitFocusOrder="0" pos="430 115 60 30" bgColOff="ff615a5a"
              bgColOn="ff7fff00" buttonText="Solo" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
