#ifndef __MAIN_DEFINED
#define __MAIN_DEFINED

#include <cdefBF533.h>
#include <sys\exception.h>

//---------------------------------------------------------------------------
// Symbolic constants													
//---------------------------------------------------------------------------
/* Filtering */
#define FFT_SIZE    		1024
#define PEAK_SIZE   		4
#define MEAN_SIZE   		4
#define LEVEL_NUM   		5
#define MODE6_BAND_NUM  9
#define MODE6_STIM_NUM  80
#define MODE7_PEAK_NUM	4
#define MODE10_STAT_SIZE 6
/* Stimulation mode */
#define STIM_MODE_1 0
#define STIM_MODE_2 1
#define STIM_MODE_3 2
#define STIM_MODE_4 3
#define STIM_MODE_5 4
#define STIM_MODE_6N 5
#define STIM_MODE_7 6
#define STIM_MODE_8 7
#define STIM_MODE_9 8
#define STIM_MODE_10 9
#define STIM_MODE_8A 10
#define STIM_MODE_8B 11
#define STIM_MODE_8C 12
#define STIM_MODE_6 13
/* Audiocodec */
#define DAC1L_VOLUME	0x2000
#define DAC1R_VOLUME	0x3000
#define DAC2L_VOLUME	0x4000
#define DAC2R_VOLUME	0x5000
// DAC
#define INTERNAL_DAC_L0		0
#define INTERNAL_DAC_L1		1
#define INTERNAL_DAC_R0		2
#define INTERNAL_DAC_R1		3
// SPORT0 word length
#define SLEN_24	0x0017
#define FLOW_1  0x1000
// Video 
#define RST_ADV7171	0x04
#define SDRAM_START_ADDR 0x00000000
// Audio packet
#define WAVEFORM_LEN 48 	// AudioCodecSampleRate / StimFreq = 48000 / 1000 = 48
#define WAVEPACKET_NUM 40
#define WINFORM_LEN 8
/* Addresses for Port A and B in Flash A */
#define pFlashA_PortA_Dir		(volatile unsigned char *)0x20270006
#define pFlashA_PortA_Data	(volatile unsigned char *)0x20270004
#define pFlashA_PortB_Dir		(volatile unsigned char *)0x20270007
#define pFlashA_PortB_Data	(volatile unsigned char *)0x20270005
/* LED */
#define SS_WAIT 0
#define SS_RUN  1
#define SS_HALT 2
// Flags
#define FLAG_ADC    0x0001
#define FLAG_AMP    0x0002
#define FLAG_LIGHT  0x0004
#define FLAG_SHOCK  0x0080
#define FLAG_SYNC   0x0200
// Pattern detection type (TL - threshold level)
#define PDT_TL_ABOVE 0
#define PDT_TL_BELOW 1
// Command parameter
#define CMD_PARAM_PEAK 0
#define CMD_PARAM_POWER 1
// Mode6N
#define MODE6N_ACTIVE_RHY  0
#define MODE6N_ACTIVE_INT  1
#define MODE6N_PASSIVE_RHY 2
// Mode10 paradigm
#define MODE10_ONLY_SHOCK 0  
#define MODE10_RELAX_PAST_TIME_SHOCK 1  
#define MODE10_RELAX_SAME_TIME_SHOCK 2  
// Stimulus type
#define STIM_TYPE_LIGHT 1
#define STIM_TYPE_SOUND 2
#define STIM_TYPE_COLOR 3
#define STIM_TYPE_SHOCK 4

//---------------------------------------------------------------------------
// Prototypes														
//---------------------------------------------------------------------------
void InitSCLK(void);
// UART 
void InitUART(void);
void EnableUART(void);
void WriteUART(char cData);
char ReadUART(void);
// Init hardware
void InitFlags(void);
void SetFlags(void);
void InitEBIU(void);
void InitFlash(void);
void InitADC(void);
void InitAD1836(void);
void InitSPORT0(void);
void InitSPORT0DMA(void);
void EnableSPORT0DMA(void);
void InitSPI(void);
void InitTIMER0(void);
void InitTIMER1(void);
void InitTIMER2(void);
void InitADV7171(void);
void InitSDRAM(void);
void InitPPIDMA(void);
void InitPPI(void);
void EnablePPIDMA(void);
void EnablePPI(void);
void InitInterrupts(void);
// Handlers
EX_INTERRUPT_HANDLER(TIMER2_ISR);
EX_INTERRUPT_HANDLER(PPI_TX_ISR);
EX_INTERRUPT_HANDLER(SPORT0_TX_ISR);
EX_INTERRUPT_HANDLER(UART_RX_ISR);
EX_INTERRUPT_HANDLER(TIMER0_ISR);
EX_INTERRUPT_HANDLER(FLAG0_ISR);
EX_INTERRUPT_HANDLER(TIMER1_ISR);
// Processing
void Processing(short sADCValue);
// Filtering
void InitFFTFiltering(void);
void AddSample(short pBuffer[], short sValue, int nSize);
short FFTFiltering(void);
// Peaking
short PeakDetection(void);
short PatternDetection(short nPeakValue, short nPowerValue, 
	short nThresholdLevelValue, short nSpaceSampleCount, short bMode10Reset);
// Transmitting
void Transmitting(short sADCValue, short sFLTValue, short nCMDValue, 
	short nThresholdLevelValue, short nShiftValue, short nModeDependentValue);
// Audio
void InitAudioWavepacket(void);
// Video
void InitVideoFrame(void);
unsigned int InitVideoLine(volatile unsigned int *pVideoFrame, 
	unsigned int nVideoLine, unsigned int nVideoColorCode);
// Hardware
void InitOperationMode(void);
void InitStimulationType(void);
void EnableStimulationType(void);
// Stimulating
short Stimulating(short sADCValue, short sFLTValue, short nPeakValue, 
	short nPowerValue, short nThresholdLevelValue);
void GenerateStimulus(char cStumulusType);
// LED Blinking
void LEDBlinking(short nState);
// ModeXRoutine
void InitMeanShortWindowPeakValue(void);
void InitMeanLongWindowPeakValue(void);
void GetMeanShortWindowPeakValue(short nPeakValue);
void GetMeanLongWindowPeakValue(short nPeakValue);
void InitMode6NStimulationMask(void);
short Mode1Routine(short nPeakValue, short nShiftSampleCount);
short Mode2Routine(short nPeakValue, short nThresholdLevelValue, short nShiftSampleCount); 
short Mode3Routine(short nPeakValue, short nThresholdLevelValue, short nShiftSampleCount);
short Mode4Routine(short nPeakValue, short nThresholdLevelValue, short nShiftSampleCount);
short Mode5Routine(short nPeakValue,short nShiftSampleCount);
short Mode6Routine(short nPeakValue, short nThresholdLevelValue, short nShiftSampleCount);
short Mode7Routine(short nPeakValue, short nThresholdLevelValue, short nShiftSampleCount);
short Mode8Routine(short nPowerValue, short nThresholdLevelValue, short nShiftSampleCount);
short Mode9Routine(short nPatternValue, short nShiftSampleCount);
short Mode10Routine(short nPatternValue, short nShiftSampleCount);
short Mode8ARoutine(short nPowerValue, short nThresholdLevelValue, short nShiftSampleCount);
short Mode8BRoutine(short nPowerValue, short nThresholdLevelValue, short nShiftSampleCount);
short Mode8CRoutine(short nPowerValue, short nThresholdLevelValue, short nShiftSampleCount);
//..
short Mode6NRoutine(short nPeakValue, short nThresholdLevelValue, short nShiftSampleCount);

//---------------------------------------------------------------------------
// Global variables													
// All global variables are declared in main.c						
//---------------------------------------------------------------------------
// Start 
extern short bStarted;
// UART 
extern unsigned short CLKIN;
extern unsigned long BAUDRATE;
extern unsigned long SCLK;
// Audio
extern int pSport0DMABuffer[];
extern short pAudioWavepacket[];
// Video
extern short bVideoColorState;
// Shock
extern short nShockImpulseCount;
extern short nShockImpulseValue;
// Filering
extern short pFFTBuffer[];
extern short pPeakBuffer[];					
// Statistics
extern short pMeanShortWindowPeakBuffer[];
extern short pMeanLongWindowPeakBuffer[];
// Shift and Intensity array
extern char pStimulatingIntensityArray[];
extern char pStimulatingShiftArray[];
// Settings
extern char cOperatingModeIndex;
extern char cSampleRateRatio;
extern char cAmpGainIndex;
extern char cLoFreqIndex;
extern char cHiFreqIndex;
extern char cFilteringTypeIndex;
extern char cPeakingDeadTime;
extern char cPeakingCommandParameterIndex;
extern char cPeakingMeanShortWindowLength;
extern char cPeakingMeanLongWindowLength;
extern char cPeakingThresholdLevelNoise;
extern char cPeakingThresholdLevelTypeIndex;
extern char cPeakingThresholdLevelFixed;
extern char cPeakingThresholdLevelFloat;
extern char cPeakingThresholdLevelFloatMax;
extern char cPeakingThresholdLevelFloatMin;
extern char cPatterningPeakTypeIndex;
extern char cPatterningPeakParamMin;
extern char cPatterningPeakParamMax;
extern char cPatterningPeakParamSpace;
extern char cStimulatingTypeIndex;
extern char cStimulatingIntensityIndex;
extern char cStimulatingShiftIndex;
extern char cStimulatingVideoSet;
extern char cStimulatingAudioSet;
extern char cStimulatingMode3AlternativeIntensityIndex;
extern char cStimulatingMode4AlternativeShiftIndex;
extern char cStimulatingMode5StimulusPeriod;
extern char cStimulatingMode6PeriodVariation;
extern char cStimulatingMode6ExternalFlashRatio;
extern char cStimulatingMode6InternalFlashRatio;
// ..
extern char cStimulatingMode6NStimulusPeriod;
extern char cStimulatingMode6NStimulationTime;
extern char cStimulatingMode6NStimulationMaskIndex;
// ..
extern char cStimulatingMode7CycleTimeRatio;
extern char cStimulatingMode7ModulationIndex;
extern char cStimulatingMode8StimulusPeriod;
extern char cStimulatingMode8ParadigmTypeIndex;
extern char cStimulatingMode9ParadigmTypeIndex;
extern char cStimulatingMode9StimulusNumber;
extern char cStimulatingMode9StimulusPeriod;
extern char cStimulatingMode10ParadigmTypeIndex;
extern char cStimulatingMode10IntervalTypeIndex;
extern char cStimulatingMode10AnalysisTime;
extern char cStimulatingDuration;
extern char cStimulatingIntensity;
extern char cStimulatingEnable;
extern char cTrainingModeIndex;
extern char cTrainingDuration;
extern char cTrainingDurationRatio;
extern char cCorrectingMode10Shock;
// Modify settings
extern short nSampleRate;
extern char cAmpSettings;
extern short nStimulatingMode5StimulusPeriod;
extern short nStimulatingMode6ExternalFlash;
extern short nStimulatingMode6InternalFlash;
// ..
extern short nStimulatingMode6NStimulusPeriod;
extern short nStimulatingMode6NExternalStimulationTime;
extern short nStimulatingMode6NInternalStimulationTime;
// ..
extern short nStimulatingMode7CycleTime;
extern short nStimulatingMode8StimulusPeriod;
extern char bTrainingState; 
extern char bProcessingState;
extern short nPeakThresholdLevelNoise;
extern short nPeakThresholdLevelFixed;
extern short nPeakThresholdLevelFloat;
extern short nPeakThresholdLevelFloatMax;
extern short nPeakThresholdLevelFloatMin;
extern short nPeakDeadTime;
// Params
extern short bEnableMeanPeakValue; 
extern short nMeanShortWindowPeakValue;
extern short nMeanLongWindowPeakValue;
extern short nModeDependentValue;
extern short nMode10SoundSampleMax;
extern short nMode10SoundNumberMax;
// MODE 6			
extern short pMode6PeriodPeakBuffer[];
// MODE 6N
extern short pMode6StimulationMaskArray[];
// MODE 7
extern short pMode7PeriodFlashBuffer[];
extern short pMode7PeakBuffer[];
// MODE 9
extern short pMode9PeriodSoundSpaceBuffer[];
extern short pMode9PeriodSoundPowerBuffer[];
// MODE 10
extern short pMode10StatBuffer[];
// Shock
extern char pShockIntervalArray[];

//---------------------------------------------------------------------------
#endif

