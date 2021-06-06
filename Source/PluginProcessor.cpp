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

#include "PluginProcessor.h"
#include "PluginEditor.h"
CompressorAudioProcessor::CompressorAudioProcessor()  //Initialise the compressor
	// Initializer List
	:
	inputBuffer(1,1),
	nhost(0)
{
    lastPosInfo.resetToDefault();
}
CompressorAudioProcessor::~CompressorAudioProcessor()
{
}
//==============================================================================
void CompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback initialisation that you need.
    channels = getTotalNumInputChannels();      // get input channel format
	samplerate = (float)getSampleRate();        // get input sample rate
	bufferSize = getBlockSize();                // get required buffer size
	// Allocate a lot of dynamic memory
	x_g_low					.allocate(bufferSize, true);
	x_l_low					.allocate(bufferSize, true);			
	y_g_low					.allocate(bufferSize, true);				
	y_l_low					.allocate(bufferSize, true);	
	c_low					.allocate(bufferSize, true);

	x_g_mid					.allocate(bufferSize, true);
	x_l_mid					.allocate(bufferSize, true);			
	y_g_mid					.allocate(bufferSize, true);				
	y_l_mid					.allocate(bufferSize, true);	
	c_mid					.allocate(bufferSize, true);

    x_g_high				.allocate(bufferSize, true);
	x_l_high				.allocate(bufferSize, true);			
	y_g_high				.allocate(bufferSize, true);				
	y_l_high				.allocate(bufferSize, true);	
	c_high					.allocate(bufferSize, true);
	
	// Initialise compressor variables
	resetAll();
	
    // Create and clear a buffer for each filter band	
	lowBandBuffer.setSize(channels,bufferSize);  
	lowBandBuffer.clear();                       
	midBandBuffer.setSize(channels,bufferSize);  
	midBandBuffer.clear();
	branchBuffer.setSize(channels,bufferSize);  // branches already filtered samples to high band
	branchBuffer.clear();
	highBandBuffer.setSize(channels,bufferSize); 
	highBandBuffer.clear();                      
	
}

void CompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this to free up any spare memory, etc.
}

//==============================================================================
// The main DSP method that processes the input signal into three bands and out again.
//==============================================================================

void CompressorAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{       
    // Populate channel(s) of low and mid filter bank buffers from input
    for (int a=0; a<channels; ++a)      
	    {
		    lowBandBuffer.addFrom(a,0,buffer,a,0,bufferSize);    
		    midBandBuffer.addFrom(a,0,buffer,a,0,bufferSize);       		
	    }
 
	    // Create an input buffer for the CV computation
        inputBuffer.setSize(1,bufferSize);  
		inputBuffer.clear();
        
    
        // Setup a filter (and a second if the input is stereo) for the low band and LPF the buffered samples
        LowPassL.setCoefficients(juce::IIRCoefficients::makeLowPass(samplerate,cutoffFrequencyLow));
        LowPassL.processSamples(lowBandBuffer.getWritePointer(0), bufferSize);
        if(channels==2){
        LowPassR.setCoefficients(juce::IIRCoefficients::makeLowPass(samplerate,cutoffFrequencyLow));
        LowPassR.processSamples(lowBandBuffer.getWritePointer(1), bufferSize);
        }

        // If the low band is not bypassed, process the buffer using the current low band compression parameters
	    if (!lowBandBypass)
		{
			inputBuffer.clear();
			// Mix down left-right to analyse the input		
			for (int m = 0 ; m < channels ; ++m)
            {
			    inputBuffer.addFrom(0,0,lowBandBuffer,m,0,bufferSize,0.5);
            }
			// Low compression : calculates the control voltage
			lowCompressor(inputBuffer,0);
			// Apply control voltage to the audio signal(s)
			for (int i = 0 ; i < bufferSize ; ++i)
			{
			    for (int n = 0 ; n < channels ; ++n)                // check if mono/stereo
                {
			        lowBandBuffer.getWritePointer(n)[i] *= c_low[i];
		        }
			}
			inputBuffer.clear();
			// Mix down left-right to analyse the output
			for (int o = 0 ; o < channels ; ++o)
            {
			    inputBuffer.addFrom(0,0,lowBandBuffer,o,0,bufferSize,0.5);
            }
		}

		// Setup a filter (and a second if the input is stereo) for the mid band and HPF the buffered samples
        MidHighPassL.setCoefficients(juce::IIRCoefficients::makeHighPass(samplerate,cutoffFrequencyLow));
        MidHighPassL.processSamples(midBandBuffer.getWritePointer(0), bufferSize);
        if(channels==2){
        MidHighPassR.setCoefficients(juce::IIRCoefficients::makeHighPass(samplerate,cutoffFrequencyLow));
        MidHighPassR.processSamples(midBandBuffer.getWritePointer(1), bufferSize);
        }

        // Branch the HPF processed samples for later filtering by the high band
        branchBuffer.clear();
        for (int b=0; b<channels; ++b)
        {	        
            branchBuffer.addFrom(b,0,midBandBuffer,b,0,bufferSize);
	        highBandBuffer.addFrom(b,0,branchBuffer,b,0,bufferSize);	            
        }

        // Setup a filter (and a second if the input is stereo) for the mid band and LPF the buffered samplesd        
        MidLowPassL.setCoefficients(juce::IIRCoefficients::makeLowPass(samplerate,cutoffFrequencyHigh));
        MidLowPassL.processSamples(midBandBuffer.getWritePointer(0), bufferSize);
        if(channels==2){
        MidLowPassR.setCoefficients(juce::IIRCoefficients::makeLowPass(samplerate,cutoffFrequencyHigh));
        MidLowPassR.processSamples(midBandBuffer.getWritePointer(1), bufferSize);	        
        }
	    
        
        // If the mid band is not bypassed, process the buffer using the current mid band compression parameters 
	    if (!midBandBypass)
		{
			inputBuffer.clear();
			// Mix down left-right to analyse the input		
			for (int m = 0 ; m < channels ; ++m)
            {
			    inputBuffer.addFrom(0,0,midBandBuffer,m,0,bufferSize,0.5);
            }
			// Compression : calculates the control voltage
			midCompressor(inputBuffer,0);
			// Apply control voltage to the audio signal(s)
			for (int i = 0 ; i < bufferSize ; ++i)
			{
			    for (int n = 0 ; n < channels ; ++n)                // check if mono/stereo
                {
			        midBandBuffer.getWritePointer(n)[i] *= c_mid[i];
			    }
			}
			inputBuffer.clear();
			// Mix down left-right to analyse the output
			for (int o = 0 ; o < channels ; ++o)
            {
			    inputBuffer.addFrom(0,0,midBandBuffer,o,0,bufferSize,0.5);
            }			
		}

		// Setup a filter (and a second if the input is stereo) for the high band and HPF the buffered samples
        HighPassL.setCoefficients(juce::IIRCoefficients::makeHighPass(samplerate,cutoffFrequencyHigh));
        HighPassL.processSamples(highBandBuffer.getWritePointer(0), bufferSize);
        if(channels==2){
        HighPassR.setCoefficients(juce::IIRCoefficients::makeHighPass(samplerate,cutoffFrequencyHigh));
        HighPassR.processSamples(highBandBuffer.getWritePointer(1), bufferSize);
        } 

        // If the high band is not bypassed, process the buffer using the current high band compression parameters
	    if (!highBandBypass)
		{
			inputBuffer.clear();
			// Mix down left-right to analyse the input		
			for (int m = 0 ; m < channels ; ++m)
            {
			    inputBuffer.addFrom(0,0,highBandBuffer,m,0,bufferSize,0.5);
            }
			// High compression : calculates the control voltage
			highCompressor(inputBuffer,0);
			// Apply control voltage to the audio signal(s)
			for (int i = 0 ; i < bufferSize ; ++i)
			{
			    for (int n = 0 ; n < channels ; ++n)                // check if mono/stereo
                {
			        highBandBuffer.getWritePointer(n)[i] *= c_high[i];
		        }
			}
			inputBuffer.clear();
			// Mix down left-right to analyse the output
			for (int o = 0 ; o < channels ; ++o)
            {
			    inputBuffer.addFrom(0,0,highBandBuffer,o,0,bufferSize,0.5);
            }
		}            
		
		//Reset the main buffer
		buffer.clear();
		
		// Check if the low band is active and, if so, add its buffered samples to the main buffer
		if(lowBandSolo | (!midBandSolo && !highBandSolo))
		{
	        for (int x=0; x<channels; ++x)                          // check if mono/stereo
	        {		    
		        buffer.addFrom(x,0,lowBandBuffer,x,0,bufferSize);
	        }
		}
		
		// Check if the mid band is active and, if so, add its buffered samples to the main buffer
		if(midBandSolo | (!lowBandSolo && !highBandSolo))
		{
	        for (int y=0; y<channels; ++y)                          // check if mono/stereo
	        {		    
		        buffer.addFrom(y,0,midBandBuffer,y,0,bufferSize);
	        }
		}
		
		// Check if the high band is active and, if so, add its buffered samples to the main buffer
		if(highBandSolo | (!lowBandSolo && !midBandSolo))
		{
	        for (int z=0; z<channels; ++z)                          // check if mono/stereo
	        {		    
		        buffer.addFrom(z,0,highBandBuffer,z,0,bufferSize);
	        }
		}
		lowBandBuffer.clear();
		midBandBuffer.clear();
		highBandBuffer.clear();		
}

//==============================================================================
// The compressor functions:
//==============================================================================
void CompressorAudioProcessor::lowCompressor(AudioSampleBuffer &buffer, int m) // compute low CV
{
	alphaAttackLow = exp(-1/(0.001 * samplerate * tauAttackLow));
	alphaReleaseLow = exp(-1/(0.001 * samplerate * tauReleaseLow));
	for (int i = 0 ; i < bufferSize ; ++i)
	{
		//Level detection- estimate level using peak detector
		if (fabs(buffer.getWritePointer(m)[i]) < 0.000001) x_g_low[i] =-120;
		else x_g_low[i] =20*log10(fabs(buffer.getWritePointer(m)[i]));
		//Gain computer- static apply input/output curve
		if (x_g_low[i] >= thresholdLow) y_g_low[i] = thresholdLow+ (x_g_low[i] - thresholdLow) / ratioLow;
		else y_g_low[i] = x_g_low[i];
		x_l_low[i] = x_g_low[i] - y_g_low[i];
		//Ballistics- smoothing of the gain 
		if (x_l_low[0]>yL_prev_low)  y_l_low[i]=alphaAttackLow * yL_prev_low+(1 - alphaAttackLow) * x_l_low[i] ; 
		else				 y_l_low[i]=alphaReleaseLow* yL_prev_low+(1 - alphaReleaseLow) * x_l_low[i] ;
		//find control
		c_low[i] = pow(10,(makeUpGainLow - y_l_low[i])/20);
		yL_prev_low=y_l_low[i];
	}
}

void CompressorAudioProcessor::midCompressor(AudioSampleBuffer &buffer, int m) // compute mid CV
{
	alphaAttackMid = exp(-1/(0.001 * samplerate * tauAttackMid));
	alphaReleaseMid = exp(-1/(0.001 * samplerate * tauReleaseMid));
	for (int i = 0 ; i < bufferSize ; ++i)
	{
		//Level detection- estimate level using peak detector
		if (fabs(buffer.getWritePointer(m)[i]) < 0.000001) x_g_mid[i] =-120;
		else x_g_mid[i] =20*log10(fabs(buffer.getWritePointer(m)[i]));
		//Gain computer- static apply input/output curve
		if (x_g_mid[i] >= thresholdMid) y_g_mid[i] = thresholdMid+ (x_g_mid[i] - thresholdMid) / ratioMid;
		else y_g_mid[i] = x_g_mid[i];
		x_l_mid[i] = x_g_mid[i] - y_g_mid[i];
		//Ballistics- smoothing of the gain 
		if (x_l_mid[0]>yL_prev_mid)  y_l_mid[i]=alphaAttackMid * yL_prev_mid+(1 - alphaAttackMid) * x_l_mid[i] ; 
		else				 y_l_mid[i]=alphaReleaseMid * yL_prev_mid+(1 - alphaReleaseMid) * x_l_mid[i] ;
		//find control
		c_mid[i] = pow(10,(makeUpGainMid - y_l_mid[i])/20);
		yL_prev_mid=y_l_mid[i];
	}
}

void CompressorAudioProcessor::highCompressor(AudioSampleBuffer &buffer, int m) // compute high CV
{
	alphaAttackHigh = exp(-1/(0.001 * samplerate * tauAttackHigh));
	alphaReleaseHigh = exp(-1/(0.001 * samplerate * tauReleaseHigh));
	for (int i = 0 ; i < bufferSize ; ++i)
	{
		//Level detection- estimate level using peak detector
		if (fabs(buffer.getWritePointer(m)[i]) < 0.000001) x_g_high[i] =-120;
		else x_g_high[i] =20*log10(fabs(buffer.getWritePointer(m)[i]));
		//Gain computer- static apply input/output curve
		if (x_g_high[i] >= thresholdHigh) y_g_high[i] = thresholdHigh+ (x_g_high[i] - thresholdHigh) / ratioHigh;
		else y_g_high[i] = x_g_high[i];
		x_l_high[i] = x_g_high[i] - y_g_high[i];
		//Ballistics- smoothing of the gain 
		if (x_l_high[0]>yL_prev_high)  y_l_high[i]=alphaAttackHigh * yL_prev_high+(1 - alphaAttackHigh) * x_l_high[i] ; 
		else				 y_l_high[i]=alphaReleaseHigh * yL_prev_high+(1 - alphaReleaseHigh) * x_l_high[i] ;
		//find control
		c_high[i] = pow(10,(makeUpGainHigh - y_l_high[i])/20);
		yL_prev_high=y_l_high[i];
	}
}

template <class T> const T& CompressorAudioProcessor::max( const T& a, const T& b )
{
  return (a < b) ? b : a;
}

void CompressorAudioProcessor::resetAll() // returns controls to default values
{
		tauAttackLow=0;tauReleaseLow = 2;
		alphaAttackLow=0;alphaReleaseLow = 0;
		thresholdLow = 0;
		ratioLow= 1;
		makeUpGainLow= 0;
		cutoffFrequencyLow=20;
	    lowBandBypass = false;
	    lowBandSolo = false;
		yL_prev_low=0;
	    
		tauAttackMid=0;tauReleaseMid = 2;
		alphaAttackMid=0;alphaReleaseMid = 0;
		thresholdMid = 0;
		ratioMid= 1;
		makeUpGainMid= 0;
        midBandBypass = false;	
        midBandSolo = false;
		yL_prev_mid=0;
        
		tauAttackHigh=0;tauReleaseHigh = 2;
		alphaAttackHigh=0;alphaReleaseHigh = 0;
		thresholdHigh = 0;
		ratioHigh= 1;
		makeUpGainHigh= 0;		
		cutoffFrequencyHigh=650;		
        highBandBypass = false;
        highBandSolo = false; 
		yL_prev_high=0;
        
	    autoTime = false;        

		
	for (int i = 0 ; i < bufferSize ; ++i)
	{
		x_g_low[i] = 0;	y_g_low[i] = 0; x_l_low[i] = 0;	y_l_low[i] = 0;	c_low[i] = 0;
		x_g_mid[i] = 0;	y_g_mid[i] = 0; x_l_mid[i] = 0;	y_l_mid[i] = 0;	c_mid[i] = 0;
		x_g_high[i] = 0; y_g_high[i] = 0; x_l_high[i] = 0; y_l_high[i] = 0; c_high[i] = 0;		
	}
}
////////////////////////////////////////////// Getters for low band controls
float CompressorAudioProcessor::getThresholdLow(){return thresholdLow;}
float CompressorAudioProcessor::getRatioLow(){return ratioLow;}
float CompressorAudioProcessor::getGainLow(){return makeUpGainLow;}
float CompressorAudioProcessor::getAttackTimeLow(){return tauAttackLow;}
float CompressorAudioProcessor::getReleaseTimeLow(){return tauReleaseLow;}
int CompressorAudioProcessor::getCutoffFrequencyLow(){return cutoffFrequencyLow;}
////////////////////////////////////////////// Getters for mid band controls
float CompressorAudioProcessor::getThresholdMid(){return thresholdMid;}
float CompressorAudioProcessor::getRatioMid(){return ratioMid;}
float CompressorAudioProcessor::getGainMid(){return makeUpGainMid;}
float CompressorAudioProcessor::getAttackTimeMid(){return tauAttackMid;}
float CompressorAudioProcessor::getReleaseTimeMid(){return tauReleaseMid;}
////////////////////////////////////////////// Getters for high band controls
float CompressorAudioProcessor::getThresholdHigh(){return thresholdHigh;}
float CompressorAudioProcessor::getRatioHigh(){return ratioHigh;}
float CompressorAudioProcessor::getGainHigh(){return makeUpGainHigh;}
float CompressorAudioProcessor::getAttackTimeHigh(){return tauAttackHigh;}
float CompressorAudioProcessor::getReleaseTimeHigh(){return tauReleaseHigh;}
int CompressorAudioProcessor::getCutoffFrequencyHigh(){return cutoffFrequencyHigh;}

//////////////////////////////////////////////////////// Setters for low band controls
void CompressorAudioProcessor::setThresholdLow(float T){thresholdLow= T;}
void CompressorAudioProcessor::setGainLow(float G){makeUpGainLow= G;}
void CompressorAudioProcessor::setRatioLow(float R){ratioLow= R;}
void CompressorAudioProcessor::setAttackTimeLow(float A){tauAttackLow = A;}
void CompressorAudioProcessor::setReleaseTimeLow(float R){tauReleaseLow = R;}
void CompressorAudioProcessor::setCutoffFrequencyLow(int F){cutoffFrequencyLow = F;}
//////////////////////////////////////////////////////// Setters for mid band controls
void CompressorAudioProcessor::setThresholdMid(float T){thresholdMid= T;}
void CompressorAudioProcessor::setGainMid(float G){makeUpGainMid= G;}
void CompressorAudioProcessor::setRatioMid(float R){ratioMid= R;}
void CompressorAudioProcessor::setAttackTimeMid(float A){tauAttackMid = A;}
void CompressorAudioProcessor::setReleaseTimeMid(float R){tauReleaseMid = R;}
//////////////////////////////////////////////////////// Setters for high band controls
void CompressorAudioProcessor::setThresholdHigh(float T){thresholdHigh= T;}
void CompressorAudioProcessor::setGainHigh(float G){makeUpGainHigh= G;}
void CompressorAudioProcessor::setRatioHigh(float R){ratioHigh= R;}
void CompressorAudioProcessor::setAttackTimeHigh(float A){tauAttackHigh = A;}
void CompressorAudioProcessor::setReleaseTimeHigh(float R){tauReleaseHigh = R;}
void CompressorAudioProcessor::setCutoffFrequencyHigh(int F){cutoffFrequencyHigh = F;}


//==============================================================================
//==============================================================================
// Standard JUCE methods
//==============================================================================
//==============================================================================
bool CompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}
AudioProcessorEditor* CompressorAudioProcessor::createEditor()
{
    return new CompressorAudioProcessorEditor (this);
}
//==============================================================================
void CompressorAudioProcessor::getStateInformation (MemoryBlock& destData)
{
//Use this to store your parameters in memory block, either as raw data, or use XML or ValueTree classes as intermediaries to make it easy to save and load complex data.
}
void CompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
// Use this to restore your parameters from this memory block, whose contents will have been created by the getStateInformation() call.
}
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CompressorAudioProcessor();
}
int CompressorAudioProcessor::round(float inn)
{
	if (inn > 0) return (int) (inn + 0.5);
	else return (int) (inn - 0.5);
}
const String CompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}
int CompressorAudioProcessor::getNumParameters()
{
    return 0;
}
float CompressorAudioProcessor::getParameter (int index)
{
    return 0.0f;
}
void CompressorAudioProcessor::setParameter (int index, float newValue)
{
}
const String CompressorAudioProcessor::getParameterName (int index)
{
    return String::empty;
}
const String CompressorAudioProcessor::getParameterText (int index)
{
    return String::empty;
}
const String CompressorAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}
const String CompressorAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}
bool CompressorAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}
bool CompressorAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}
bool CompressorAudioProcessor::silenceInProducesSilenceOut() const
{
#if JucePlugin_SilenceInProducesSilenceOut
    return true;
#else
    return false;
#endif
}

double CompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}
bool CompressorAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}
bool CompressorAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}
int CompressorAudioProcessor::getNumPrograms()
{
    return 0;
}
int CompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}
void CompressorAudioProcessor::setCurrentProgram (int index)
{
}
const String CompressorAudioProcessor::getProgramName (int index)
{
    return String::empty;
}
void CompressorAudioProcessor::changeProgramName (int index, const String& newName)
{
}