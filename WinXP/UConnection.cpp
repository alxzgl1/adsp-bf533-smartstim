//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include <mmsystem.h>
//---------------------------------------------------------------------------
#include "UConnection.h"
#include "UMain.h"
#include "USettings.h"
#define MAX_WAIT_READ 100
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TConnection::TConnection(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TConnection::Execute()
{
	int i;
  // For RX
  DWORD bc;
  // Data to PC
  short sADCValue, sFLTValue, nCMDValue, nThresholdLevelNoise,
    nThresholdLevelValue, nShiftValue, nModeDependentValue;
 	char cHiByte, cLoByte, cOpByte;
  // Data to BF
  char cOperatingModeIndex;
  char cSampleRateRatio, cAmpGainIndex, cLoFreqIndex, cHiFreqIndex;
  char cMiscellaneousFilterTypeIndex;
  char cPeakingThresholdLevelNoise, cPeakingThresholdLevelFixed,
    cPeakingThresholdLevelFloat;
  char cPeakingDeadTime, cPeakingMeanShortWindowLength, cPeakingMeanLongWindowLength,
    cPeakingThresholdLevelTypeIndex, cPeakingCommandParameterIndex;
  char cPatterningPeakParamIndex, cPatterningPeakParamMin, cPatterningPeakParamMax,
    cPatterningPeakParamSpace;
  char cTFN0, cTFN1, cTFN2, cTFN3, cTFN4;
  char cTFD0, cTFD1, cTFD2, cTFD3, cTFD4;
  char cTrainingMode, cTrainingDuration, cTrainingDurationRatio;
  char cStimulatingTypeIndex, cStimulatingDuration, cStimulatingIntensityIndex,
    cStimulatingShiftIndex,
    cStimulatingVideoSet, cStimulatingAudioSet, 
    cStimulatingMode2InverseLogic,
  	cStimulatingMode3AlternativeIntensityIndex, cStimulatingMode4AlternativeShiftIndex,
    cStimulatingMode5StimulusPeriod,
    cStimulatingMode6NStimulusPeriod, cStimulatingMode6NStimulationTime,
    cStimulatingMode6NStimulationMaskIndex,
    cStimulatingMode7ModulationIndex,
    cStimulatingMode8StimulusPeriod, cStimulatingMode8ParadigmTypeIndex,
    cStimulatingMode9ParadigmTypeIndex, cStimulatingMode9StimulusNumber,
    cStimulatingMode9StimulusPeriod, cStimulatingMode10ParadigmTypeIndex,
    cStimulatingMode10ShockTypeIndex, cStimulatingMode10AnalysisTime;
  char cStimulatingMode7CycleTimeRatio;
  char cSSHTA0, cSSHTA1, cSSHTA2, cSSHTA3, cSSHTA4,
  	cSPWRA0, cSPWRA1, cSPWRA2, cSPWRA3, cSPWRA4;
  int nStimulatingIntensity, nStimulatingShift, nStimulatingMode3AlternativeIntensity,
  	nStimulatingMode4AlternativeShift;

  // Training time
  int nSampleCount = fmMain->m_nTrainingDuration *
  	fmMain->m_nTrainingDurationRatio * fmMain->m_nSampleRate;
  // Training time sample count
  int nTrainingTimeSampleCount = 0;

  // Check file size
  FILE *pTestStream;

  /* Open COM port */
  if (!OpenSerialPort())
  {
  	// Enable control items
    fmMain->EnableControlItems(true, false, false);
    return;
  }
  /* Check file size */
  if ((pTestStream = fopen(fmMain->m_aOutputFileName.c_str(), "rt")) != NULL)
  {
    if (MessageBox(NULL, "Overwrite file?", "Warning", MB_YESNO |
    	MB_ICONWARNING) == IDNO)
    {
    	// Close opened port
  		CloseHandle(m_hCOM);
      // Close opened file
      fclose(pTestStream);
      // Enable control items
    	fmMain->EnableControlItems(true, false, false);
      return;
    }
  }

  /* Open file for write */
  if ((m_pOnlineProcessingStream = fopen(fmMain->m_aOutputFileName.c_str(), "wt")) ==
  	NULL)
  {
    // Close opened port
  	CloseHandle(m_hCOM);
    // Show message
  	MessageBox(NULL, "Cannot open output file", "Error", MB_OK | MB_ICONERROR);
    // Enable control items
    fmMain->EnableControlItems(true, false, false);
    return;
  }

  // Show plot
  Synchronize(SynchronizeDrawPlot);

  // Write to file
  nStimulatingIntensity =
  	StrToInt(fmSettings->cbStimulatingIntensity->Items->Strings[fmMain->m_nStimulatingIntensityIndex]);
  nStimulatingShift =
  	StrToInt(fmSettings->cbStimulatingShift->Items->Strings[fmMain->m_nStimulatingShiftIndex]);
  nStimulatingMode3AlternativeIntensity =
  	StrToInt(fmSettings->cbStimulatingMode3AlternativeIntensity->Items->Strings[fmMain->m_nStimulatingMode3AlternativeIntensityIndex]);
  nStimulatingMode4AlternativeShift =
  	StrToInt(fmSettings->cbStimulatingMode4AlternativeShift->Items->Strings[fmMain->m_nStimulatingMode4AlternativeShiftIndex]);

  fprintf(m_pOnlineProcessingStream,
    "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
  	fmMain->m_nSampleRate, fmMain->m_nAmpGainIndex, fmMain->m_nLoFreqIndex, fmMain->m_nHiFreqIndex,
    fmMain->m_nMiscellaneousFilterTypeIndex, fmMain->m_nPeakingDeadTime,
    fmMain->m_nPeakingCommandParameterIndex,
    fmMain->m_nPeakingMeanShortWindowLength, fmMain->m_nPeakingMeanLongWindowLength,
    fmMain->m_pPeakingThresholdLevelArray[0], fmMain->m_nPeakingThresholdLevelTypeIndex,
    fmMain->m_pPeakingThresholdLevelArray[1], fmMain->m_pPeakingThresholdLevelArray[2],
    fmMain->m_nPatterningPeakParamIndex, fmMain->m_pPatterningPeakParamArray[0],
    fmMain->m_pPatterningPeakParamArray[1], fmMain->m_pPatterningPeakParamArray[2],
    fmMain->m_nTrainingModeIndex, fmMain->m_nTrainingDuration,
    fmMain->m_nTrainingDurationRatio, fmMain->m_nStimulatingTypeIndex,
    fmMain->m_nStimulatingDuration, nStimulatingIntensity, nStimulatingShift,
    fmMain->m_nStimulatingVideoSet, fmMain->m_nStimulatingAudioSet,
    nStimulatingMode3AlternativeIntensity, nStimulatingMode4AlternativeShift,
    fmMain->m_nStimulatingMode5StimulusPeriod, fmMain->m_nStimulatingMode6NStimulusPeriod,
    fmMain->m_nStimulatingMode6NStimulationTime, fmMain->m_nStimulatingMode6NStimulationMaskIndex,
    fmMain->m_nStimulatingMode7CycleTime, fmMain->m_nStimulatingMode7ModulationIndex,
    fmMain->m_nStimulatingMode8StimulusPeriod, fmMain->m_nStimulatingMode8ParadigmTypeIndex,
    fmMain->m_nStimulatingMode9ParadigmTypeIndex, fmMain->m_nStimulatingMode9StimulusNumber,
    fmMain->m_nStimulatingMode9StimulusPeriod, fmMain->m_nStimulatingMode10ParadigmTypeIndex,
    fmMain->m_nStimulatingMode10ShockTypeIndex, fmMain->m_nStimulatingMode10AnalysisTime);

  /* Write to COM stimulus params */
  // Mode
  cOperatingModeIndex = (char)fmMain->m_nOperatingModeIndex;
  WriteFile(m_hCOM, &cOperatingModeIndex, sizeof(char), &bc, NULL);
  // Sample rate
  cSampleRateRatio = (char)(fmMain->m_nSampleRate / 128);
  WriteFile(m_hCOM, &cSampleRateRatio, sizeof(char), &bc, NULL);
  // Amp gain
  cAmpGainIndex = (char)fmMain->m_nAmpGainIndex;
  WriteFile(m_hCOM, &cAmpGainIndex, sizeof(char), &bc, NULL);
  // Lo freq
  cLoFreqIndex = (char)fmMain->m_nLoFreqIndex;
  WriteFile(m_hCOM, &cLoFreqIndex, sizeof(char), &bc, NULL);
  // Hi freq
  cHiFreqIndex = (char)fmMain->m_nHiFreqIndex;
  WriteFile(m_hCOM, &cHiFreqIndex, sizeof(char), &bc, NULL);
  // Filtering type
  cMiscellaneousFilterTypeIndex = (char)fmMain->m_nMiscellaneousFilterTypeIndex;
  WriteFile(m_hCOM, &cMiscellaneousFilterTypeIndex, sizeof(char), &bc, NULL);
  // Peaking dead time
  cPeakingDeadTime = (char)(fmMain->m_nPeakingDeadTime);
  WriteFile(m_hCOM, &cPeakingDeadTime, sizeof(char), &bc, NULL);
  // Peaking command parameter index
  cPeakingCommandParameterIndex = (char)fmMain->m_nPeakingCommandParameterIndex;
  WriteFile(m_hCOM, &cPeakingCommandParameterIndex, sizeof(char), &bc, NULL);
  // Peaking mean short window length
  cPeakingMeanShortWindowLength = (char)(fmMain->m_nPeakingMeanShortWindowLength / 128);
  WriteFile(m_hCOM, &cPeakingMeanShortWindowLength, sizeof(char), &bc, NULL);
  // Peaking mean long window length
  cPeakingMeanLongWindowLength = (char)(fmMain->m_nPeakingMeanLongWindowLength / 1024);
  WriteFile(m_hCOM, &cPeakingMeanLongWindowLength, sizeof(char), &bc, NULL);
  // Peaking threshold level noise
  cPeakingThresholdLevelNoise = (char)(fmMain->m_pPeakingThresholdLevelArray[0] / 4);
  WriteFile(m_hCOM, &cPeakingThresholdLevelNoise, sizeof(char), &bc, NULL);
  // Peaking threshold level type index
  cPeakingThresholdLevelTypeIndex = (char)fmMain->m_nPeakingThresholdLevelTypeIndex;
  WriteFile(m_hCOM, &cPeakingThresholdLevelTypeIndex, sizeof(char), &bc, NULL);
  // Peaking threshold level fixed
  cPeakingThresholdLevelFixed = (char)(fmMain->m_pPeakingThresholdLevelArray[1] / 4);
  WriteFile(m_hCOM, &cPeakingThresholdLevelFixed, sizeof(char), &bc, NULL);
  // Peaking threshold level float
  cPeakingThresholdLevelFloat = (char)(fmMain->m_pPeakingThresholdLevelArray[2] / 4);
  WriteFile(m_hCOM, &cPeakingThresholdLevelFloat, sizeof(char), &bc, NULL);
  // Peaking threshold level float min limit
  cPeakingThresholdLevelFloat = (char)(fmMain->m_pPeakingThresholdLevelArray[3] / 4);
  WriteFile(m_hCOM, &cPeakingThresholdLevelFloat, sizeof(char), &bc, NULL);
  // Peaking threshold level float max limit
  cPeakingThresholdLevelFloat = (char)(fmMain->m_pPeakingThresholdLevelArray[4] / 4);
  WriteFile(m_hCOM, &cPeakingThresholdLevelFloat, sizeof(char), &bc, NULL);
  // Patterning peak param index
  cPatterningPeakParamIndex = (char)fmMain->m_nPatterningPeakParamIndex;
  WriteFile(m_hCOM, &cPatterningPeakParamIndex, sizeof(char), &bc, NULL);
  // Patterning peak param min
  cPatterningPeakParamMin = (char)fmMain->m_pPatterningPeakParamArray[0];
  WriteFile(m_hCOM, &cPatterningPeakParamMin, sizeof(char), &bc, NULL);
  // Patterning peak param max
  cPatterningPeakParamMax = (char)fmMain->m_pPatterningPeakParamArray[1];
  WriteFile(m_hCOM, &cPatterningPeakParamMax, sizeof(char), &bc, NULL);
  // Patterning peak param space
  cPatterningPeakParamSpace = (char)(fmMain->m_pPatterningPeakParamArray[2] / 8);
  WriteFile(m_hCOM, &cPatterningPeakParamSpace, sizeof(char), &bc, NULL);
  // Training mode
  cTrainingMode = (char)fmMain->m_nTrainingModeIndex;
  WriteFile(m_hCOM, &cTrainingMode, sizeof(char), &bc, NULL);
  // Training duration
  cTrainingDuration = (char)fmMain->m_nTrainingDuration;
  WriteFile(m_hCOM, &cTrainingDuration, sizeof(char), &bc, NULL);
  // Training duration ratio
  cTrainingDurationRatio = (char)fmMain->m_nTrainingDurationRatio;
  WriteFile(m_hCOM, &cTrainingDurationRatio, sizeof(char), &bc, NULL);
  // Stimulating type
  cStimulatingTypeIndex = (char)fmMain->m_nStimulatingTypeIndex;
  WriteFile(m_hCOM, &cStimulatingTypeIndex, sizeof(char), &bc, NULL);
  // Stimulating duration
  cStimulatingDuration = (char)(fmMain->m_nStimulatingDuration / 8);
  WriteFile(m_hCOM, &cStimulatingDuration, sizeof(char), &bc, NULL);
  // Stimulating power index
  cStimulatingIntensityIndex = (char)(fmMain->m_nStimulatingIntensityIndex);
  WriteFile(m_hCOM, &cStimulatingIntensityIndex, sizeof(char), &bc, NULL);
  // Stimulating power array
  cSPWRA0 = (char)(StrToInt(fmSettings->cbStimulatingIntensity->Items->Strings[0]));
  WriteFile(m_hCOM, &cSPWRA0, sizeof(char), &bc, NULL);
  cSPWRA1 = (char)(StrToInt(fmSettings->cbStimulatingIntensity->Items->Strings[1]));
  WriteFile(m_hCOM, &cSPWRA1, sizeof(char), &bc, NULL);
  cSPWRA2 = (char)(StrToInt(fmSettings->cbStimulatingIntensity->Items->Strings[2]));
  WriteFile(m_hCOM, &cSPWRA2, sizeof(char), &bc, NULL);
  cSPWRA3 = (char)(StrToInt(fmSettings->cbStimulatingIntensity->Items->Strings[3]));
  WriteFile(m_hCOM, &cSPWRA3, sizeof(char), &bc, NULL);
  cSPWRA4 = (char)(StrToInt(fmSettings->cbStimulatingIntensity->Items->Strings[4]));
  WriteFile(m_hCOM, &cSPWRA4, sizeof(char), &bc, NULL);
  // Stimulating shift index
  cStimulatingShiftIndex = (char)(fmMain->m_nStimulatingShiftIndex);
  WriteFile(m_hCOM, &cStimulatingShiftIndex, sizeof(char), &bc, NULL);
  // Stimulating shift array
  cSSHTA0 = (char)(StrToInt(fmSettings->cbStimulatingShift->Items->Strings[0]));
  WriteFile(m_hCOM, &cSSHTA0, sizeof(char), &bc, NULL);
  cSSHTA1 = (char)(StrToInt(fmSettings->cbStimulatingShift->Items->Strings[1]));
  WriteFile(m_hCOM, &cSSHTA1, sizeof(char), &bc, NULL);
  cSSHTA2 = (char)(StrToInt(fmSettings->cbStimulatingShift->Items->Strings[2]));
  WriteFile(m_hCOM, &cSSHTA2, sizeof(char), &bc, NULL);
  cSSHTA3 = (char)(StrToInt(fmSettings->cbStimulatingShift->Items->Strings[3]));
  WriteFile(m_hCOM, &cSSHTA3, sizeof(char), &bc, NULL);
  cSSHTA4 = (char)(StrToInt(fmSettings->cbStimulatingShift->Items->Strings[4]));
  WriteFile(m_hCOM, &cSSHTA4, sizeof(char), &bc, NULL);
  // Stimulating video set
  cStimulatingVideoSet = (char)(fmMain->m_nStimulatingVideoSet);
  WriteFile(m_hCOM, &cStimulatingVideoSet, sizeof(char), &bc, NULL);
  // Stimulating audio set
  cStimulatingAudioSet = (char)(fmMain->m_nStimulatingAudioSet);
  WriteFile(m_hCOM, &cStimulatingAudioSet, sizeof(char), &bc, NULL);
  // Stimulating mode 3 alternative power index
  cStimulatingMode3AlternativeIntensityIndex = (char)(fmMain->m_nStimulatingMode3AlternativeIntensityIndex);
  WriteFile(m_hCOM, &cStimulatingMode3AlternativeIntensityIndex, sizeof(char), &bc, NULL);
  // Stimulating mode 4 alternative shift index
  cStimulatingMode4AlternativeShiftIndex = (char)(fmMain->m_nStimulatingMode4AlternativeShiftIndex);
  WriteFile(m_hCOM, &cStimulatingMode4AlternativeShiftIndex, sizeof(char), &bc, NULL);
  // Stimulating mode 5 period
  cStimulatingMode5StimulusPeriod = (char)(fmMain->m_nStimulatingMode5StimulusPeriod / 8);
  WriteFile(m_hCOM, &cStimulatingMode5StimulusPeriod, sizeof(char), &bc, NULL);
  // Stimulating mode 6N stimulus period
  cStimulatingMode6NStimulusPeriod = (char)(fmMain->m_nStimulatingMode6NStimulusPeriod /8);
  WriteFile(m_hCOM, &cStimulatingMode6NStimulusPeriod, sizeof(char), &bc, NULL);
  // Stimulating mode 6N stimulation time
  cStimulatingMode6NStimulationTime = (char)(fmMain->m_nStimulatingMode6NStimulationTime);
  WriteFile(m_hCOM, &cStimulatingMode6NStimulationTime, sizeof(char), &bc, NULL);
  // Stimulating mode 6N mask index
  cStimulatingMode6NStimulationMaskIndex = (char)(fmMain->m_nStimulatingMode6NStimulationMaskIndex);
  WriteFile(m_hCOM, &cStimulatingMode6NStimulationMaskIndex, sizeof(char), &bc, NULL);
  // Stimulating mode 7 cycle time
  cStimulatingMode7CycleTimeRatio = (char)(fmMain->m_nStimulatingMode7CycleTime / 128);
  WriteFile(m_hCOM, &cStimulatingMode7CycleTimeRatio, sizeof(char), &bc, NULL);
  // Stimulating mode 7 modulation index
  cStimulatingMode7ModulationIndex = (char)(fmMain->m_nStimulatingMode7ModulationIndex);
  WriteFile(m_hCOM, &cStimulatingMode7ModulationIndex, sizeof(char), &bc, NULL);
  // Stimulating mode 8 period
  cStimulatingMode8StimulusPeriod = (char)(fmMain->m_nStimulatingMode8StimulusPeriod / 8);
  WriteFile(m_hCOM, &cStimulatingMode8StimulusPeriod, sizeof(char), &bc, NULL);
  // Stimulating mode 8 paradigm type index
  cStimulatingMode8ParadigmTypeIndex = (char)(fmMain->m_nStimulatingMode8ParadigmTypeIndex);
  WriteFile(m_hCOM, &cStimulatingMode8ParadigmTypeIndex, sizeof(char), &bc, NULL);
  // Stimulating mode 9 paradigm type index
  cStimulatingMode9ParadigmTypeIndex = (char)(fmMain->m_nStimulatingMode9ParadigmTypeIndex);
  WriteFile(m_hCOM, &cStimulatingMode9ParadigmTypeIndex, sizeof(char), &bc, NULL);
  // Stimulating mode 9 stimulus number
  cStimulatingMode9StimulusNumber = (char)(fmMain->m_nStimulatingMode9StimulusNumber);
  WriteFile(m_hCOM, &cStimulatingMode9StimulusNumber, sizeof(char), &bc, NULL);
  // Stimulating mode 9 stimulus period
  cStimulatingMode9StimulusPeriod = (char)(fmMain->m_nStimulatingMode9StimulusPeriod / 8);
  WriteFile(m_hCOM, &cStimulatingMode9StimulusPeriod, sizeof(char), &bc, NULL);
  // Stimulating mode 10 paradigm type index
  cStimulatingMode10ParadigmTypeIndex = (char)(fmMain->m_nStimulatingMode10ParadigmTypeIndex);
  WriteFile(m_hCOM, &cStimulatingMode10ParadigmTypeIndex, sizeof(char), &bc, NULL);
  // Stimulating mode 10 interval type index
  cStimulatingMode10ShockTypeIndex = (char)(fmMain->m_nStimulatingMode10ShockTypeIndex);
  WriteFile(m_hCOM, &cStimulatingMode10ShockTypeIndex, sizeof(char), &bc, NULL);
  // Stimulating mode 10 analysis time
  cStimulatingMode10AnalysisTime = (char)(fmMain->m_nStimulatingMode10AnalysisTime);
  WriteFile(m_hCOM, &cStimulatingMode10AnalysisTime, sizeof(char), &bc, NULL);

  // Free on terminate
	FreeOnTerminate = true;

  // Start of offline processing mode
  if (fmMain->m_nOperatingModeIndex == 1)
  {
	  if ((m_pOfflineProcessingStream = fopen(fmMain->m_aInputFileName.c_str(), "rt")) ==
	  	NULL)
	  {
	    // Close opened port
	  	CloseHandle(m_hCOM);
	    // Close opened file
	    fclose(m_pOnlineProcessingStream);
	    // Show message
	  	MessageBox(NULL, "Cannot open input file", "Error", MB_OK | MB_ICONERROR);
	    // Enable control items
	    fmMain->EnableControlItems(true, false, false);
	    return;
	  }
	  // Check file format
	  if (fmMain->CheckFileFormat(m_pOfflineProcessingStream))
    {
      MessageBox(NULL, "Wrong file format", "File error", MB_OK | MB_ICONERROR);
	  	return;
    }
	  // Skip header
	  int nTempSampleRate, nTempAmpGainIndex, nTempLoFreqIndex, nTempHiFreqIndex;
	  int nTempMiscellaneousFilterTypeIndex;
	  int nTempPeakingDeadTime, nTempPeakingCommandParameterIndex,
      nTempPeakingMeanShortWindowLength, nTempPeakingMeanLongWindowLength,
      nTempPeakingThresholdLevelNoise, nTempPeakingThresholdLevelTypeIndex,
      nTempPeakingThresholdLevelFixed, nTempPeakingThresholdLevelFloat;
    int nTempPatterningPeakTypeIndex, nTempPatterningPeakParamMin,
      nTempPatterningPeakParamMax, nTempPatterningPeakParamSpace;
    int nTempTrainingModeIndex, nTempTrainingDuration, nTempTrainingDurationRatio;
	  int nTempStimulatingTypeIndex, nTempStimulatingDuration,
      nTempStimulatingIntensity, nTempStimulatingShift,
      nTempStimulatingVideoSet, nTempStimulatingAudioSet,
	  	nTempStimulatingMode3AlternativeIntensity, nTempStimulatingMode4AlternativeShift,
      nTempStimulatingMode5StimulusPeriod, nTempStimulatingMode6NStimulusPeriod,
	    nTempStimulatingMode6NStimulationTime, nTempStimulatingMode6NStimulationMaskIndex,
      nTempStimulatingMode7CycleTime, nTempStimulatingMode7ModulationIndex,
      nTempStimulatingMode8StimulusPeriod, nTempStimulatingMode8ParadigmTypeIndex,
      nTempStimulatingMode9ParadigmTypeIndex, nTempStimulatingMode9StimulusNumber,
      nTempStimulatingMode9StimulusPeriod, nTempStimulatingMode10ParadigmTypeIndex,
      nTempStimulatingMode10ShockTypeIndex, nTempStimulatingMode10AnalysisTime;
	  fscanf(m_pOfflineProcessingStream,
      "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
	  	&nTempSampleRate, &nTempAmpGainIndex, &nTempLoFreqIndex, &nTempHiFreqIndex,
	    &nTempMiscellaneousFilterTypeIndex, &nTempPeakingDeadTime,
      &nTempPeakingCommandParameterIndex,
      &nTempPeakingMeanShortWindowLength, &nTempPeakingMeanLongWindowLength,
      &nTempPeakingThresholdLevelNoise, &nTempPeakingThresholdLevelTypeIndex,
	    &nTempPeakingThresholdLevelFixed, &nTempPeakingThresholdLevelFloat,
      &nTempPatterningPeakTypeIndex, &nTempPatterningPeakParamMin,
      &nTempPatterningPeakParamMax, &nTempPatterningPeakParamSpace,
      &nTempTrainingModeIndex, &nTempTrainingDuration,
      &nTempTrainingDurationRatio, &nTempStimulatingTypeIndex,
      &nTempStimulatingDuration, &nTempStimulatingIntensity, &nTempStimulatingShift,
      &nTempStimulatingVideoSet, &nTempStimulatingAudioSet,
      &nTempStimulatingMode3AlternativeIntensity, &nTempStimulatingMode4AlternativeShift,
      &nTempStimulatingMode5StimulusPeriod, &nTempStimulatingMode6NStimulusPeriod,
	    &nTempStimulatingMode6NStimulationTime, &nTempStimulatingMode6NStimulationMaskIndex,
      &nTempStimulatingMode7CycleTime, &nTempStimulatingMode7ModulationIndex,
      &nTempStimulatingMode8StimulusPeriod, &nTempStimulatingMode8ParadigmTypeIndex, 
      &nTempStimulatingMode9ParadigmTypeIndex, &nTempStimulatingMode9StimulusNumber,
      &nTempStimulatingMode9StimulusPeriod, &nTempStimulatingMode10ParadigmTypeIndex,
      &nTempStimulatingMode10ShockTypeIndex, &nTempStimulatingMode10AnalysisTime);
  }
	// Variables
	int iADCValue, iFLTValue, iCMDValue, iThresholdLevelNoise,
    iThresholdLevelValue, iShiftValue, iModeDependentValue;
  // Terminate
  int nTerminateCause = 0;

	// Acq loop
  while (true)
  {
    /* Time interrupted */
    if (fmMain->m_bStarted || fmMain->m_nOperatingModeIndex == 1)
    {
      nTrainingTimeSampleCount += 1;
      if (fmMain->m_nOperatingModeIndex == 0) // Online Processing
      {
        nSampleCount -= 1;
        if (nSampleCount == 0)
        {
          nTerminateCause = 1;
          Terminate();
        }
      }
    }

    /* Transmit */
   	if (fmMain->m_nOperatingModeIndex == 1) // Offline Processing
    {
	   	// Check end of file
	   	if (feof(m_pOfflineProcessingStream))
      {
      	nTerminateCause = 2;
     		Terminate();
      }
      // Scan data from file
      fscanf(m_pOfflineProcessingStream, "%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        &iADCValue, &iFLTValue, &iCMDValue, &iThresholdLevelNoise,
        &iThresholdLevelValue, &iShiftValue, &iModeDependentValue);
      // Confirm request
	    ReadFile(m_hCOM, &cLoByte, sizeof(char), &bc, NULL);
      // Write data
      cHiByte = (char)(iADCValue >> 0x8);
	  	cLoByte = (char)(iADCValue & 0xFF);
      WriteFile(m_hCOM, &cHiByte, sizeof(char), &bc, NULL);
      WriteFile(m_hCOM, &cLoByte, sizeof(char), &bc, NULL);
    }
    /* Receive */
    // ADC
    ReadFile(m_hCOM, &cHiByte, sizeof(char), &bc, NULL);
  	ReadFile(m_hCOM, &cLoByte, sizeof(char), &bc, NULL);
    cHiByte = (cHiByte & 0xF);
    cHiByte = (cHiByte & 0x8) ? (cHiByte | 0xF0) : cHiByte;
    sADCValue = (short)(cHiByte << 8) | (short)(cLoByte & 0xFF);
    fmMain->m_pREEG[fmMain->m_nCountAcq] = sADCValue;
  	// FLT
    ReadFile(m_hCOM, &cHiByte, sizeof(char), &bc, NULL);
  	ReadFile(m_hCOM, &cLoByte, sizeof(char), &bc, NULL);
    cHiByte = (cHiByte & 0xF);
    cHiByte = (cHiByte & 0x8) ? (cHiByte | 0xF0) : cHiByte;
  	sFLTValue = (short)(cHiByte << 8) | (short)(cLoByte & 0xFF);
  	fmMain->m_pFEEG[fmMain->m_nCountAcq] = sFLTValue;
    // CMD and Mode dependent hi
    ReadFile(m_hCOM, &cHiByte, sizeof(char), &bc, NULL);
  	ReadFile(m_hCOM, &cLoByte, sizeof(char), &bc, NULL);
    nModeDependentValue = (short)(cHiByte >> 4);
    cHiByte = (cHiByte & 0xF);
    cHiByte = (cHiByte & 0x8) ? (cHiByte | 0xF0) : cHiByte;
  	nCMDValue = (short)(cHiByte << 8) | (short)(cLoByte & 0xFF);
    fmMain->m_pCEEG[fmMain->m_nCountAcq] = nCMDValue;
    // Threshold, Mode dependent lo and Shift
    ReadFile(m_hCOM, &cHiByte, sizeof(char), &bc, NULL);
  	ReadFile(m_hCOM, &cLoByte, sizeof(char), &bc, NULL);
    nShiftValue = (short)(cHiByte >> (4 + 2));
    cHiByte = (cHiByte & 0x3F);
    nModeDependentValue = (nModeDependentValue << 2) | (short)(cHiByte >> 4);
    cHiByte = (cHiByte & 0xF);
    cHiByte = (cHiByte & 0x8) ? (cHiByte | 0xF0) : cHiByte;
  	nThresholdLevelValue = (short)(cHiByte << 8) | (short)(cLoByte & 0xFF);
    fmMain->m_pTVEEG[fmMain->m_nCountAcq] = nThresholdLevelValue;
    // Decode
    fmMain->m_pSEEG[fmMain->m_nCountAcq] = nShiftValue;
    fmMain->m_pMDEEG[fmMain->m_nCountAcq] = nModeDependentValue;
    // Noise
    nThresholdLevelNoise = fmMain->m_pPeakingThresholdLevelArray[0];
    fmMain->m_pTNEEG[fmMain->m_nCountAcq] = nThresholdLevelNoise;

  	/* Write data to file */
    if (fmMain->m_bStarted)
    {
	    fprintf(m_pOnlineProcessingStream, "%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
	  	  sADCValue, sFLTValue, nCMDValue, nThresholdLevelNoise,
        nThresholdLevelValue, nShiftValue, nModeDependentValue);
    }

    // Increase count
    fmMain->m_nCountAcq += 1;
	  if (fmMain->m_nCountAcq == fmMain->m_nDataSize)
	  {
	    fmMain->m_nCountAcq = 0;
	    Synchronize(SynchronizeOnlineData);
	  }

    // Show training time
    if (fmMain->m_bStarted || fmMain->m_nOperatingModeIndex == 1)
    {
      if (nTrainingTimeSampleCount >= fmMain->m_nSampleRate)
      {
        nTrainingTimeSampleCount = 0;
        fmMain->m_nTrainingTime -= 1;
        Synchronize(SynchronizeTrainingTime);
      }
    }

    // Show mode dependent value
    if (fmMain->m_nModeDependentValue != nModeDependentValue)
    {
      fmMain->m_nModeDependentValue = nModeDependentValue;
      Synchronize(SynchronizeModeDependentValue);
    }

    /* Transmit online control code */
    if (fmMain->m_nOnlineControl)
    {
      cHiByte = 0x40 + (char)fmMain->m_nOnlineControl;
      if (fmMain->m_nOnlineControl == 0x1)      // Noise level
    	  cLoByte = (char)(fmMain->m_pPeakingThresholdLevelArray[0] / 4);
      else if (fmMain->m_nOnlineControl == 0x2) // Threshold level fixed
    	  cLoByte = (char)(fmMain->m_pPeakingThresholdLevelArray[1] / 4);
      else if (fmMain->m_nOnlineControl == 0x3) // Threshold level float
    	  cLoByte = (char)(fmMain->m_pPeakingThresholdLevelArray[2] / 4);
      else if (fmMain->m_nOnlineControl == 0x4) // Threshold level float min
    	  cLoByte = (char)(fmMain->m_pPeakingThresholdLevelArray[3] / 4);
      else if (fmMain->m_nOnlineControl == 0x5) // Threshold level float max
    	  cLoByte = (char)(fmMain->m_pPeakingThresholdLevelArray[4] / 4);
      else if (fmMain->m_nOnlineControl == 0x6) // Pattern peak min
    	  cLoByte = (char)(fmMain->m_pPatterningPeakParamArray[0]);
      else if (fmMain->m_nOnlineControl == 0x7) // Pattern peak max
    	  cLoByte = (char)(fmMain->m_pPatterningPeakParamArray[1]);
      else if (fmMain->m_nOnlineControl == 0x8) // Pattern space
    	  cLoByte = (char)(fmMain->m_pPatterningPeakParamArray[2] / 8);
      else if (fmMain->m_nOnlineControl == 0x9) // Correct mode 10 shock type
    	  cLoByte = (char)(fmMain->m_nOnlineCorrectionMode10);
      else if (fmMain->m_nOnlineControl == 0xF) // Started
        cLoByte = 0x1;

      fmMain->m_nOnlineControl = 0;
      WriteFile(m_hCOM, &cHiByte, sizeof(char), &bc, NULL);
      WriteFile(m_hCOM, &cLoByte, sizeof(char), &bc, NULL);
    }

    /* Terminated */
    if (Terminated)
    {
      fmMain->m_bStarted = false;
    	cHiByte = 0x60;
    	cLoByte = 0x00;
      WriteFile(m_hCOM, &cHiByte, sizeof(char), &bc, NULL);
      WriteFile(m_hCOM, &cLoByte, sizeof(char), &bc, NULL);
      // Switch terminate cause
    	switch (nTerminateCause)
      {
      	case 0:
        {
    			// User interrupted message
    			MessageBox(NULL, "Training user interrupted", "Training",
    				MB_OK | MB_ICONINFORMATION);
          break;
        }
        case 1:
        {
         	// Timer interrupted message
      		MessageBox(NULL, "Training time has expired", "Training",
    				MB_OK | MB_ICONINFORMATION);
         	break;
        }
        case 2:
        {
        	// End of file interrupt message
         	MessageBox(NULL, "Training end of file interrupted", "Training",
    				MB_OK | MB_ICONINFORMATION);
        	break;
        }
      }
      // Clear plot
      Synchronize(SynchronizeClearPlot);
    	break;
    }
  }
  // Close files
  fclose(m_pOnlineProcessingStream);
  if (fmMain->m_nOperatingModeIndex == 1)
	  fclose(m_pOfflineProcessingStream);
  // Clear port
  ClearSerialPort();
  // Close port
  CloseHandle(m_hCOM);
  // Delete EEG objects
  fmMain->DeleteEEGObjects();
  // Delete graphic objects
  fmMain->DeleteGraphicObjects();
  // Enable control items
  Synchronize(SynchronizeControlItems);
}
//---------------------------------------------------------------------------
bool __fastcall TConnection::OpenSerialPort()
{
  // Open port
	m_hCOM = CreateFile(fmMain->m_aMiscellaneousPort.c_str(),
  									GENERIC_WRITE|GENERIC_READ,
                 		0,
                  	NULL,
               			OPEN_EXISTING,
                  	0,
                  	NULL);
	if (m_hCOM == INVALID_HANDLE_VALUE)
  {
  	MessageBox(NULL, "Cannot open port", "Error", MB_OK);
   	return false;
  }
  // Init structures
  COMMTIMEOUTS cto =
	{
    MAX_WAIT_READ,  // ReadIntervalTimeOut
    0,              // ReadTotalTimeOutMultiplier
    MAX_WAIT_READ,  // ReadTotalTimeOutConstant
    0,              // WriteTotalTimeOutMultiplier
    0               // WriteTotalTimeOutConstant
	};

	DCB dcb =
	{
    sizeof(DCB),        // DCBlength
    256000,        			// BaudRate
    TRUE,               // fBinary
    FALSE,              // fParity
    FALSE,              // fOutxCtsFlow
    FALSE,              // fOutxDsrFlow
    DTR_CONTROL_ENABLE, // fDtrControl
    FALSE,              // fDsrSensitivity
    FALSE,              // fTXContinueOnXoff
    FALSE,              // fOutX
    FALSE,              // fInX
    FALSE,              // fErrorChar
    FALSE,              // fNull
    RTS_CONTROL_ENABLE, // fRtsControl
    FALSE,              // fAbortOnError
    0,                  // fDummy2
    0,                  // wReserved
    0x100,              // XonLim
    0x100,              // XoffLim
    8,                  // ByteSize
    NOPARITY,           // Parity
    ONESTOPBIT,         // StopBits
    0x11,               // XonChar
    0x13,               // XoffChar
    '?',                // ErrorChar
    0x1A,               // EofChar
    0x10                // EvtChar
	};
  // Configuration COM
  if(!SetCommTimeouts(m_hCOM, &cto) || !SetCommState(m_hCOM, &dcb))
  {
  	MessageBox(NULL, "Cannot configuration COM port", "Error", MB_OK);
    CloseHandle(m_hCOM);
    return false;
  }
  // Clear
  ClearSerialPort();
  return true;
}
//---------------------------------------------------------------------------
void __fastcall TConnection::ClearSerialPort()
{
  PurgeComm(m_hCOM, PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_RXABORT);
}
//---------------------------------------------------------------------------
void __fastcall TConnection::SynchronizeDrawPlot()
{
  fmMain->DrawPlot();
}
//---------------------------------------------------------------------------
void __fastcall TConnection::SynchronizeClearPlot()
{
	fmMain->blPlot->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TConnection::SynchronizeOnlineData()
{
	fmMain->ShowOnlineData();
}
//---------------------------------------------------------------------------
void __fastcall TConnection::SynchronizeControlItems()
{
	fmMain->EnableControlItems(true, false, false);
  fmMain->DeleteEEGObjects();
  fmMain->DeleteGraphicObjects();
}
//---------------------------------------------------------------------------
void __fastcall TConnection::SynchronizeTrainingTime()
{
	fmMain->ShowTrainingTime();
}
//---------------------------------------------------------------------------
void __fastcall TConnection::SynchronizeModeDependentValue()
{
  if (fmMain->m_nTrainingModeIndex == STIM_MODE_6) // Most frequently period
  {
	  fmMain->stModeDependentValue->Caption = IntToStr(fmMain->m_nModeDependentValue);
  }
  if (fmMain->m_nTrainingModeIndex == STIM_MODE_10) // Type of stimulus
  {
    if ((fmMain->m_nModeDependentValue & 0x7) == 1)
    {
      fmMain->stModeDependentFlag->Color = clYellow;
      if (fmMain->m_bStarted && fmMain->m_nStimulatingMode10ShockTypeIndex == 1)
        PlaySound(fmMain->m_aSoundBeginFileName.c_str(), 0, SND_ASYNC);
    }
    else if ((fmMain->m_nModeDependentValue & 0x3) == 2)
    {
      fmMain->stModeDependentFlag->Color = clGreen;
      fmMain->stModeDependentValue->Caption = IntToStr(fmMain->m_nModeDependentValue >> 2) + "/6";
      if (fmMain->m_bStarted && fmMain->m_nStimulatingMode10ShockTypeIndex == 1 && fmMain->m_nStimulatingTypeIndex)
        PlaySound(fmMain->m_aSoundRelaxFileName.c_str(), 0, SND_ASYNC);
    }
    else if ((fmMain->m_nModeDependentValue & 0x3) == 3)
    {
      fmMain->stModeDependentFlag->Color = clRed;
      fmMain->stModeDependentValue->Caption = IntToStr(fmMain->m_nModeDependentValue >> 2) + "/6";
      if (fmMain->m_bStarted && fmMain->m_nStimulatingMode10ShockTypeIndex == 1 && fmMain->m_nStimulatingTypeIndex)
        PlaySound(fmMain->m_aSoundShockFileName.c_str(), 0, SND_ASYNC);
    }
  }
}
//---------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
void __fastcall TConnection::MyTextOut()
{
  ShowMessage(IntToStr(m_nMyVar));
}
//---------------------------------------------------------------------------

