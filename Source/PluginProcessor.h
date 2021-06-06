/*
  This code is developed from the compressor example JUCE code in the textbook:
  Digital Audio Effects: Theory, Implementation and Application
  Joshua D. Reiss and Andrew P. McPherson
  https://www.crcpress.com/Audio-Effects-Theory-Implementation-and-Application/Reiss-McPherson/p/book/9781466560284
  ------------------------------------------------------------------------------
  The original compression algorithm is reused in combination with custom-written code to
  define and process three filtered signals independently.
  ------------------------------------------------------------------------------
  The plugin can be compiled to VST, VST3 and AU using the four source files and
  standard JUCE library modules.
*/

#ifndef __PLUGINPROCESSOR_H_88534BAA__
#define __PLUGINPROCESSOR_H_88534BAA__

#include "../JuceLibraryCode/JuceHeader.h"
#include <math.h>

// Main Compressor AudioProcessor defined sub-class
class CompressorAudioProcessor  : public AudioProcessor
{
public:
    CompressorAudioProcessor();                                             // constructor method
    ~CompressorAudioProcessor();                                            // destructor method
	
    IIRFilter LowPassL, LowPassR, MidLowPassL, MidLowPassR,                 // declare filter objects
                MidHighPassL, MidHighPassR, HighPassL, HighPassR;
    
	int bufferSize;                                                         // container for buffersize
	
    void prepareToPlay (double sampleRate, int samplesPerBlock);            // setup routine method
    void releaseResources();                                                // stop routine method
	void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);// main audio processing method
	
	void lowCompressor(AudioSampleBuffer &buffer, int m);                   // low compressor function
	void midCompressor(AudioSampleBuffer &buffer, int m);                   // mid compressor function
	void highCompressor(AudioSampleBuffer &buffer, int m);                  // high compressor function
		
	template <class T> const T& max ( const T& a, const T& b );             // specify max function

	//==============================================================================
    // Standard JUCE public methods for AudioProcessor class
    //==============================================================================
    AudioProcessorEditor* createEditor();                                   

    bool hasEditor() const;                                                 

	AudioPlayHead::CurrentPositionInfo lastPosInfo;
 
	int round(float inn);
    const String getName() const;

    int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const;
    bool acceptsMidi() const;
    bool producesMidi() const;

    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

	//==============================================================================
    // Getter and setter methods for Compressor subclass
    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

	int getCutoffFrequencyLow(), getCutoffFrequencyHigh();
    float getThresholdLow(), getRatioLow(), getGainLow(), getAttackTimeLow(), getReleaseTimeLow();
	float getThresholdMid(), getRatioMid(), getGainMid(), getAttackTimeMid(), getReleaseTimeMid();
	float getThresholdHigh(), getRatioHigh(), getGainHigh(), getAttackTimeHigh(), getReleaseTimeHigh();
	
	void setCutoffFrequencyLow(int F), setCutoffFrequencyHigh(int F);
	void setThresholdLow(float T), setGainLow(float G), setRatioLow(float R), 
	    setAttackTimeLow(float A), setReleaseTimeLow(float R);
	void setThresholdMid(float T), setGainMid(float G), setRatioMid(float R), 
	    setAttackTimeMid(float A), setReleaseTimeMid(float R); 
	void setThresholdHigh(float T), setGainHigh(float G), setRatioHigh(float R), 
	    setAttackTimeHigh(float A), setReleaseTimeHigh(float R);	    
	void resetAll();


    //==============================================================================
    // Audio playback global variables
    //==============================================================================
    int channels;                               	
	bool autoTime;

	bool lowBandBypass;
	bool midBandBypass;
	bool highBandBypass;
	bool lowBandSolo;
	bool midBandSolo;
	bool highBandSolo;	
	
private:
    // Declare buffer objects
    AudioSampleBuffer inputBuffer, lowBandBuffer, midBandBuffer, branchBuffer, highBandBuffer;

	// Declare buffers for CV calculation
	HeapBlock <float> x_g_low, x_l_low, y_g_low, y_l_low,c_low, // input, output, control
                        x_g_mid, x_l_mid, y_g_mid, y_l_mid,c_mid,// input, output, control
                            x_g_high, x_l_high, y_g_high, y_l_high,c_high;// input, output, control                        
	
	// Control parameter variables
	float ratioLow,thresholdLow,makeUpGainLow,tauAttackLow,tauReleaseLow,alphaAttackLow,alphaReleaseLow;
	float ratioMid,thresholdMid,makeUpGainMid,tauAttackMid,tauReleaseMid,alphaAttackMid,alphaReleaseMid;
	float ratioHigh,thresholdHigh,makeUpGainHigh,tauAttackHigh,tauReleaseHigh,alphaAttackHigh,alphaReleaseHigh;
	float yL_prev_low, yL_prev_mid, yL_prev_high;
	int cutoffFrequencyLow, cutoffFrequencyHigh;
	
	// Host settings variables
	int nhost;
	int samplerate;

	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorAudioProcessor);
};

#endif  // __PLUGINPROCESSOR_H_88534BAA__
