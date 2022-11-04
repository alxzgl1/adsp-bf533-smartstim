#include "main.h"

#include <sysreg.h>
#include <ccblkfn.h>

// Start 
short bStarted = 0;
// UART
unsigned short CLKIN = 27;
unsigned long BAUDRATE = 256000; 
unsigned long SCLK;
// Audio
int pSport0DMABuffer[4];
short pAudioWavepacket[WAVEPACKET_NUM * WAVEFORM_LEN];
// Video
short bVideoColorState;
// Shock
short nShockImpulseCount;
short nShockImpulseValue;
// Filtering
short pFFTBuffer[FFT_SIZE / 2];
short pPeakBuffer[PEAK_SIZE];
// Mean
short pMeanShortWindowPeakBuffer[MEAN_SIZE]; 
short pMeanLongWindowPeakBuffer[MEAN_SIZE]; 
// Shift and Intensity array
char pStimulatingShiftArray[LEVEL_NUM] = {0, 8, 16, 32, 64};
char pStimulatingIntensityArray[LEVEL_NUM] = {1, 2, 3, 4, 5};
// Settings
char cOperatingModeIndex;
char cSampleRateRatio;
char cAmpGainIndex;
char cLoFreqIndex;
char cHiFreqIndex;
char cFilteringTypeIndex;
char cPeakingDeadTime;
char cPeakingCommandParameterIndex;
char cPeakingMeanShortWindowLength;
char cPeakingMeanLongWindowLength;
char cPeakingThresholdLevelNoise;
char cPeakingThresholdLevelTypeIndex;
char cPeakingThresholdLevelFixed;
char cPeakingThresholdLevelFloat;
char cPeakingThresholdLevelFloatMax;
char cPeakingThresholdLevelFloatMin;
char cPatterningPeakTypeIndex;
char cPatterningPeakParamMin;
char cPatterningPeakParamMax;
char cPatterningPeakParamSpace;
char cStimulatingTypeIndex;
char cStimulatingIntensityIndex;
char cStimulatingShiftIndex;
char cStimulatingVideoSet;
char cStimulatingAudioSet;
char cStimulatingMode2InverseLogic;
char cStimulatingMode3AlternativeIntensityIndex;
char cStimulatingMode4AlternativeShiftIndex;
char cStimulatingMode5StimulusPeriod;
char cStimulatingMode6PeriodVariation;
char cStimulatingMode6ExternalFlashRatio;
char cStimulatingMode6InternalFlashRatio;
// ..
char cStimulatingMode6NStimulusPeriod;
char cStimulatingMode6NStimulationTime;
char cStimulatingMode6NStimulationMaskIndex;
// ..
char cStimulatingMode7CycleTimeRatio;
char cStimulatingMode7ModulationIndex;
char cStimulatingMode8StimulusPeriod;
char cStimulatingMode8ParadigmTypeIndex;
char cStimulatingMode9ParadigmTypeIndex;
char cStimulatingMode9StimulusNumber;
char cStimulatingMode9StimulusPeriod;
char cStimulatingMode10ParadigmTypeIndex;
char cStimulatingMode10IntervalTypeIndex;
char cStimulatingMode10AnalysisTime;
char cStimulatingDuration = 8;
char cStimulatingIntensity;
char cStimulatingEnable;
char cTrainingModeIndex;
char cTrainingDuration;
char cTrainingDurationRatio;
char cCorrectingMode10Shock;
// Modify settings
short nSampleRate;
char cAmpSettings;
short nStimulatingMode5StimulusPeriod;
short nStimulatingMode6ExternalFlash;
short nStimulatingMode6InternalFlash;
// ..
short nStimulatingMode6NStimulusPeriod;
short nStimulatingMode6NExternalStimulationTime;
short nStimulatingMode6NInternalStimulationTime;
// ..
short nStimulatingMode7CycleTime;
short nStimulatingMode8StimulusPeriod;
char bTrainingState = 1;
char bProcessingState = 0; 
short nPeakDeadTime;
short nPeakThresholdLevelNoise;
short nPeakThresholdLevelFixed;
short nPeakThresholdLevelFloat;
short nPeakThresholdLevelFloatMax;
short nPeakThresholdLevelFloatMin;
// Params
short bEnableMeanPeakValue = 1; 
short nMeanShortWindowPeakValue = 0;
short nMeanLongWindowPeakValue = 0;
short nPowerValue = 0; 
short nThresholdLevelValue = 0;
short nModeDependentValue = 0;
short nMode10SoundSampleMax = 13;
short nMode10SoundNumberMax = 5;
// MODE 6					
short pMode6PeriodPeakBuffer[MODE6_BAND_NUM + 1];
// MODE 6N
short pMode6StimulationMaskArray[MODE6_STIM_NUM] = {
  1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 
	1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 
	1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 
	1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 
	1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 
	1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 
	0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 
	1, 0, 1, 1, 0, 1, 1, 0, 1, 1
};
// MODE 7
short pMode7PeriodFlashBuffer[10] = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7};
short pMode7PeakBuffer[MODE7_PEAK_NUM];
// MODE 9
short pMode9PeriodSoundSpaceBuffer[5] = {16, 14, 12, 10, 8};
short pMode9PeriodSoundPowerBuffer[5] = {5, 4, 3, 2, 1};
// MODE 10
short pMode10StatBuffer[MODE10_STAT_SIZE] = {0};
// Shock
char pShockIntervalArray[256] = { // Median equal 10 second
  9, 8, 8, 11, 10, 8, 10, 11, 9, 10, 12, 9, 10, 11, 12, 8, 
  9, 12, 8, 12, 11, 8, 9, 8, 9, 11, 12, 11, 9, 11, 10, 8, 
  11, 8, 11, 8, 10, 12, 9, 9, 11, 12, 9, 12, 8, 8, 12, 8, 
  12, 12, 8, 10, 11, 9, 11, 9, 10, 9, 12, 10, 9, 12, 8, 8, 
  8, 12, 11, 10, 9, 12, 11, 9, 9, 8, 11, 11, 10, 11, 11, 10, 
  8, 9, 11, 12, 11, 12, 11, 9, 12, 12, 12, 11, 9, 11, 10, 9, 
  10, 11, 10, 12, 10, 11, 10, 9, 9, 12, 8, 9, 11, 11, 10, 11, 
  11, 8, 12, 12, 12, 10, 10, 8, 9, 10, 8, 8, 10, 10, 12, 10,
  9, 8, 8, 11, 10, 8, 10, 11, 9, 10, 12, 9, 10, 11, 12, 8, 
  9, 12, 8, 12, 11, 8, 9, 8, 9, 11, 12, 11, 9, 11, 10, 8, 
  11, 8, 11, 8, 10, 12, 9, 9, 11, 12, 9, 12, 8, 8, 12, 8, 
  12, 12, 8, 10, 11, 9, 11, 9, 10, 9, 12, 10, 9, 12, 8, 8, 
  8, 12, 11, 10, 9, 12, 11, 9, 9, 8, 11, 11, 10, 11, 11, 10, 
  8, 9, 11, 12, 11, 12, 11, 9, 12, 12, 12, 11, 9, 11, 10, 9, 
  10, 11, 10, 12, 10, 11, 10, 9, 9, 12, 8, 9, 11, 11, 10, 11, 
  11, 8, 12, 12, 12, 10, 10, 8, 9, 10, 8, 8, 10, 10, 12, 10
};
/*
char pShockIntervalArray[256] = { // Median equal 15 second
	14, 13, 13, 16, 15, 13, 15, 16, 14, 15, 17, 14, 15, 16, 17, 13,
	14, 17, 13, 17, 16, 13, 14, 13, 14, 16, 17, 16, 14, 16, 15, 13,
	16, 13, 16, 13, 15, 17, 14, 14, 16, 17, 14, 17, 13, 13, 17, 13,
	17, 17, 13, 15, 16, 14, 16, 14, 15, 14, 17, 15, 14, 17, 13, 13,
	13, 17, 16, 15, 14, 17, 16, 14, 14, 13, 16, 16, 15, 16, 16, 15,
	13, 14, 16, 17, 16, 17, 16, 14, 17, 17, 17, 16, 14, 16, 15, 14,
	15, 16, 15, 17, 15, 16, 15, 14, 14, 17, 13, 14, 16, 16, 15, 16,
	16, 13, 17, 17, 17, 15, 15, 13, 14, 15, 13, 13, 15, 15, 17, 15,
	14, 13, 13, 16, 15, 13, 15, 16, 14, 15, 17, 14, 15, 16, 17, 13,
	14, 17, 13, 17, 16, 13, 14, 13, 14, 16, 17, 16, 14, 16, 15, 13,
	16, 13, 16, 13, 15, 17, 14, 14, 16, 17, 14, 17, 13, 13, 17, 13,
	17, 17, 13, 15, 16, 14, 16, 14, 15, 14, 17, 15, 14, 17, 13, 13,
	13, 17, 16, 15, 14, 17, 16, 14, 14, 13, 16, 16, 15, 16, 16, 15,
	13, 14, 16, 17, 16, 17, 16, 14, 17, 17, 17, 16, 14, 16, 15, 14,
	15, 16, 15, 17, 15, 16, 15, 14, 14, 17, 13, 14, 16, 16, 15, 16,
	16, 13, 17, 17, 17, 15, 15, 13, 14, 15, 13, 13, 15, 15, 17, 15
};
*/

//---------------------------------------------------------------------------
// Main v2.22 (20090803)
//---------------------------------------------------------------------------
void main(void)
{
  int i;
  sysreg_write(reg_SYSCFG, 0x32);		//Initialize System Configuration Register
  
  // PLL
  *pPLL_CTL = 0x2c00;
	ssync();
	idle();
  // SCLK
	InitSCLK();
  // UART 
  InitUART();
	// LED
  LEDBlinking(SS_WAIT);
  // Receive params
  cOperatingModeIndex = ReadUART();
  cSampleRateRatio = ReadUART();
  cAmpGainIndex = ReadUART();
  cLoFreqIndex = ReadUART();
  cHiFreqIndex = ReadUART();
  cFilteringTypeIndex = ReadUART();
  cPeakingDeadTime = ReadUART();
  cPeakingCommandParameterIndex = ReadUART();
  cPeakingMeanShortWindowLength = ReadUART();
  cPeakingMeanLongWindowLength = ReadUART();
  cPeakingThresholdLevelNoise = ReadUART();
  cPeakingThresholdLevelTypeIndex = ReadUART();
  cPeakingThresholdLevelFixed = ReadUART();
  cPeakingThresholdLevelFloat = ReadUART();
  cPeakingThresholdLevelFloatMin = ReadUART();
  cPeakingThresholdLevelFloatMax = ReadUART();
	cPatterningPeakTypeIndex = ReadUART();
	cPatterningPeakParamMin = ReadUART();
	cPatterningPeakParamMax = ReadUART();
	cPatterningPeakParamSpace = ReadUART();
  cTrainingModeIndex = ReadUART();
  cTrainingDuration = ReadUART();
  cTrainingDurationRatio = ReadUART();
  cStimulatingTypeIndex = ReadUART();
  cStimulatingDuration = ReadUART();
  cStimulatingIntensityIndex = ReadUART();
  pStimulatingIntensityArray[0] = ReadUART();
  pStimulatingIntensityArray[1] = ReadUART();
  pStimulatingIntensityArray[2] = ReadUART();
  pStimulatingIntensityArray[3] = ReadUART();
  pStimulatingIntensityArray[4] = ReadUART();
  cStimulatingShiftIndex = ReadUART();
  pStimulatingShiftArray[0] = ReadUART();
  pStimulatingShiftArray[1] = ReadUART();
  pStimulatingShiftArray[2] = ReadUART();
  pStimulatingShiftArray[3] = ReadUART();
  pStimulatingShiftArray[4] = ReadUART();
  cStimulatingVideoSet = ReadUART();
	cStimulatingAudioSet = ReadUART();
  cStimulatingMode3AlternativeIntensityIndex = ReadUART();
  cStimulatingMode4AlternativeShiftIndex = ReadUART();
  cStimulatingMode5StimulusPeriod = ReadUART();
	cStimulatingMode6NStimulusPeriod = ReadUART();
	cStimulatingMode6NStimulationTime = ReadUART();
	cStimulatingMode6NStimulationMaskIndex = ReadUART();
	cStimulatingMode7CycleTimeRatio = ReadUART();
	cStimulatingMode7ModulationIndex = ReadUART();
	cStimulatingMode8StimulusPeriod = ReadUART();
  cStimulatingMode8ParadigmTypeIndex = ReadUART();
	cStimulatingMode9ParadigmTypeIndex = ReadUART();
	cStimulatingMode9StimulusNumber = ReadUART();
	cStimulatingMode9StimulusPeriod = ReadUART();
	cStimulatingMode10ParadigmTypeIndex = ReadUART();
	cStimulatingMode10IntervalTypeIndex = ReadUART();
	cStimulatingMode10AnalysisTime = ReadUART();
	
	/* new */
	nMode10SoundSampleMax = 13;
	nMode10SoundNumberMax = 5;
	if (cStimulatingMode10IntervalTypeIndex == 1)
	{
	  nMode10SoundSampleMax = 11;
		nMode10SoundNumberMax = 8;
	}
	
	
  // Init variables
  nSampleRate = (short)cSampleRateRatio * 128;
  cAmpSettings = (cLoFreqIndex << 6) | (cAmpGainIndex << 3) | cHiFreqIndex;
  cStimulatingIntensity = pStimulatingIntensityArray[cStimulatingIntensityIndex];
  nPeakThresholdLevelNoise = (short)cPeakingThresholdLevelNoise * 4;
  nPeakThresholdLevelFixed = (short)cPeakingThresholdLevelFixed * 4;
  nPeakThresholdLevelFloat = (short)cPeakingThresholdLevelFloat * 4;
  nPeakThresholdLevelFloatMin = (short)cPeakingThresholdLevelFloatMin * 4;
  nPeakThresholdLevelFloatMax = (short)cPeakingThresholdLevelFloatMax * 4;
  nPeakDeadTime = ((unsigned short)cPeakingDeadTime * nSampleRate) / 
  	1000 + 1;
  nStimulatingMode5StimulusPeriod = (((short)cStimulatingMode5StimulusPeriod * 8) * nSampleRate) / 1000;
 	// nStimulatingMode6ExternalFlash = (short)cStimulatingMode6ExternalFlashRatio * 10 * nSampleRate;
	// nStimulatingMode6InternalFlash = (short)cStimulatingMode6InternalFlashRatio * 10 * nSampleRate;
	// ..
	nStimulatingMode6NStimulusPeriod = (((short)cStimulatingMode6NStimulusPeriod * 8) * nSampleRate) / 1000;
	nStimulatingMode6NExternalStimulationTime = cStimulatingMode6NStimulationTime * nSampleRate; // In samples
	nStimulatingMode6NInternalStimulationTime = cStimulatingMode6NStimulationTime * nSampleRate; // In samples 
	// ..
	nStimulatingMode7CycleTime = (short)cStimulatingMode7CycleTimeRatio * 128;
	nStimulatingMode8StimulusPeriod = (((short)cStimulatingMode8StimulusPeriod * 8) * nSampleRate) / 1000;
	
	// Init processes
	InitMeanShortWindowPeakValue();
	InitMeanLongWindowPeakValue();
	InitFFTFiltering();
	
	// Init mode 6N
	InitMode6NStimulationMask();
	
	// Init hardware
	InitEBIU();
	InitFlash();
	InitFlags();
	SetFlags();
	InitTIMER0();
	InitOperationMode();
	InitStimulationType();
	InitSPI();
	// Interrupts
	InitInterrupts();
  EnableUART();
	EnableStimulationType();
	
	// Quit by time 
	while (1)
	{
	  if (!bTrainingState && !bProcessingState)
	  	break;
	}
	// Stop timers 
	*pTIMER_ENABLE = TIMEN1 | TIMEN0;
	*pTIMER_DISABLE = TIMDIS1 | TIMDIS0;
	*pTIMER_STATUS = TRUN1 | TRUN0;
	for (i = 0; i < 0xf000; i++)
  	asm("nop;");
}

//---------------------------------------------------------------------------
