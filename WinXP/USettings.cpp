//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include <mmsystem.h>
//---------------------------------------------------------------------------
#include "USettings.h"
#include "UMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmSettings *fmSettings;
//---------------------------------------------------------------------------
__fastcall TfmSettings::TfmSettings(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//***************************************************************************
// Functions
//***************************************************************************
void __fastcall TfmSettings::InitItemsForOperatingMode()
{
  /* Set file name */
  // Output file name
  edOutputFileName->Text = GetShortFileName(fmMain->m_aOutputFileName);
  // Input file name
  edInputFileName->Text = GetShortFileName(fmMain->m_aInputFileName);
  // Sound file name
  edSoundFileName->Text = GetShortFileName(fmMain->m_aSoundBeginFileName);

  /* Check operating mode */
  bnApply->Enabled = true;
  if (fmMain->m_nOperatingModeIndex == 1)
  {
    if (GetFileParams(fmMain->m_aInputFileName, false))
    {
      edInputFileName->Text = "";
      bnApply->Enabled = false;
    }
  }
  if (fmMain->m_nOperatingModeIndex == 2)
  {
    if (GetFileParams(fmMain->m_aOutputFileName, false))
    {
      edOutputFileName->Text = "";
      bnApply->Enabled = false;
    }
  }

  /* Set params */
  // Digitizing
	cbDigitizingSampleRate->Text = IntToStr(fmMain->m_nSampleRate);
  cbDigitizingAmpGain->Text = cbDigitizingAmpGain->Items->Strings[fmMain->m_nAmpGainIndex];
  cbDigitizingLoFreq->Text = cbDigitizingLoFreq->Items->Strings[fmMain->m_nLoFreqIndex];
  cbDigitizingHiFreq->Text = cbDigitizingHiFreq->Items->Strings[fmMain->m_nHiFreqIndex];
  // Processing
  cbMiscellaneousFilterType->Text = cbMiscellaneousFilterType->Items->Strings[fmMain->m_nMiscellaneousFilterTypeIndex];
  // Peaking
  cbPeakingDeadTime->Text = IntToStr(fmMain->m_nPeakingDeadTime);
  cbPeakingCommandParameter->Text =
    cbPeakingCommandParameter->Items->Strings[fmMain->m_nPeakingCommandParameterIndex];
  cbPeakingMeanShortWindowLength->Text = IntToStr(fmMain->m_nPeakingMeanShortWindowLength);
  cbPeakingMeanLongWindowLength->Text = IntToStr(fmMain->m_nPeakingMeanLongWindowLength);
  cbPeakingThresholdLevelNoise->Text = IntToStr(fmMain->m_pPeakingThresholdLevelArray[0]);
  cbPeakingThresholdLevelType->Text =
    cbPeakingThresholdLevelType->Items->Strings[fmMain->m_nPeakingThresholdLevelTypeIndex];
  cbPeakingThresholdLevelFixed->Text = IntToStr(fmMain->m_pPeakingThresholdLevelArray[1]);
  cbPeakingThresholdLevelFloat->Text = IntToStr(fmMain->m_pPeakingThresholdLevelArray[2]);
  // Patterning
  cbPatterningPeakType->Text =
    cbPatterningPeakType->Items->Strings[fmMain->m_nPatterningPeakParamIndex];
  cbPatterningPeakParamMin->Text = IntToStr(fmMain->m_pPatterningPeakParamArray[0]);
  cbPatterningPeakParamMax->Text = IntToStr(fmMain->m_pPatterningPeakParamArray[1]);
  cbPatterningPeakParamSpace->Text = IntToStr(fmMain->m_pPatterningPeakParamArray[2]);
  // Training
  cbTrainingMode->Text = cbTrainingMode->Items->Strings[fmMain->m_nTrainingModeIndex];
  cbTrainingDuration->Text = IntToStr(fmMain->m_nTrainingDuration);
  // Stimulating
  cbStimulatingType->Text = cbStimulatingType->Items->Strings[fmMain->m_nStimulatingTypeIndex];
  cbStimulatingDuration->Text = IntToStr(fmMain->m_nStimulatingDuration);
  cbStimulatingIntensity->Items->Clear();
  cbStimulatingIntensity->Items->Add(IntToStr(fmMain->m_pStimulatingIntensityArray[0]));
  cbStimulatingIntensity->Items->Add(IntToStr(fmMain->m_pStimulatingIntensityArray[1]));
  cbStimulatingIntensity->Items->Add(IntToStr(fmMain->m_pStimulatingIntensityArray[2]));
  cbStimulatingIntensity->Items->Add(IntToStr(fmMain->m_pStimulatingIntensityArray[3]));
  cbStimulatingIntensity->Items->Add(IntToStr(fmMain->m_pStimulatingIntensityArray[4]));
  cbStimulatingIntensity->Text = cbStimulatingIntensity->Items->Strings[fmMain->m_nStimulatingIntensityIndex];
  cbStimulatingShift->Items->Clear();
  cbStimulatingShift->Items->Add(IntToStr(fmMain->m_pStimulatingShiftArray[0]));
  cbStimulatingShift->Items->Add(IntToStr(fmMain->m_pStimulatingShiftArray[1]));
  cbStimulatingShift->Items->Add(IntToStr(fmMain->m_pStimulatingShiftArray[2]));
  cbStimulatingShift->Items->Add(IntToStr(fmMain->m_pStimulatingShiftArray[3]));
  cbStimulatingShift->Items->Add(IntToStr(fmMain->m_pStimulatingShiftArray[4]));
  cbStimulatingShift->Text = cbStimulatingShift->Items->Strings[fmMain->m_nStimulatingShiftIndex];
  cbStimulatingVideoSet->Text = IntToStr(fmMain->m_nStimulatingVideoSet);
  cbStimulatingAudioSet->Text = IntToStr(fmMain->m_nStimulatingAudioSet);
  cbStimulatingMode3AlternativeIntensity->Text =
  	cbStimulatingMode3AlternativeIntensity->Items->Strings[fmMain->m_nStimulatingMode3AlternativeIntensityIndex];
  cbStimulatingMode4AlternativeShift->Text =
  	cbStimulatingMode4AlternativeShift->Items->Strings[fmMain->m_nStimulatingMode4AlternativeShiftIndex];
  cbStimulatingMode5StimulusPeriod->Text = IntToStr(fmMain->m_nStimulatingMode5StimulusPeriod);
  cbStimulatingMode6NStimulusPeriod->Text = IntToStr(fmMain->m_nStimulatingMode6NStimulusPeriod);
  cbStimulatingMode6NStimulationTime->Text = IntToStr(fmMain->m_nStimulatingMode6NStimulationTime);
  cbStimulatingMode6NStimulationMask->Text =
    cbStimulatingMode6NStimulationMask->Items->Strings[fmMain->m_nStimulatingMode6NStimulationMaskIndex];
  cbStimulatingMode7CycleTime->Text = IntToStr(fmMain->m_nStimulatingMode7CycleTime);
  cbStimulatingMode7Modulation->Text =
  	cbStimulatingMode7Modulation->Items->Strings[fmMain->m_nStimulatingMode7ModulationIndex];
  cbStimulatingMode8StimulusPeriod->Text = IntToStr(fmMain->m_nStimulatingMode8StimulusPeriod);
  cbStimulatingMode8ParadigmType->Text =
    cbStimulatingMode8ParadigmType->Items->Strings[fmMain->m_nStimulatingMode8ParadigmTypeIndex];
  cbStimulatingMode9ParadigmType->Text =
  	cbStimulatingMode9ParadigmType->Items->Strings[fmMain->m_nStimulatingMode9ParadigmTypeIndex];
  cbStimulatingMode9StimulusNumber->Text = IntToStr(fmMain->m_nStimulatingMode9StimulusNumber);
  cbStimulatingMode9StimulusPeriod->Text = IntToStr(fmMain->m_nStimulatingMode9StimulusPeriod);
  cbStimulatingMode10ParadigmType->Text =
  	cbStimulatingMode10ParadigmType->Items->Strings[fmMain->m_nStimulatingMode10ParadigmTypeIndex];
  cbStimulatingMode10ShockType->Text =
  	cbStimulatingMode10ShockType->Items->Strings[fmMain->m_nStimulatingMode10ShockTypeIndex];
  cbStimulatingMode10AnalysisTime->Text = IntToStr(fmMain->m_nStimulatingMode10AnalysisTime);
  // Plot
  cbPlotWidth->Text = IntToStr(fmMain->m_nPlotWidth);
  cbPlotHeight->Text = IntToStr(fmMain->m_nPlotHeight * 3);
  cbPlotXScale->Text = IntToStr(fmMain->m_nPlotXScale);
  cbPlotYScale->Text = IntToStr(fmMain->m_nPlotYScale);
  // Init and check port
  cbMiscellaneousPort->Text = fmMain->m_aMiscellaneousPort;
  CheckPort(cbMiscellaneousPort->Text);
}

//---------------------------------------------------------------------------
void __fastcall TfmSettings::EnableItemsForOperatingMode()
{
	bool bState;
  /* Enable all items */
  bState = true;
  // Digitizing
  stDigitizingSampleRate->Enabled = bState;
  cbDigitizingSampleRate->Enabled = bState;
  cbDigitizingAmpGain->Enabled = bState;
  stDigitizingAmpGain->Enabled = bState;
  stDigitizingLoFreq->Enabled = bState;
  cbDigitizingLoFreq->Enabled = bState;
  stDigitizingHiFreq->Enabled = bState;
  cbDigitizingHiFreq->Enabled = bState;
  // Processing
  stMiscellaneousFilterType->Enabled = bState;
  cbMiscellaneousFilterType->Enabled = bState;
  // Peaking
  stPeakingDeadTime->Enabled = bState;
  cbPeakingDeadTime->Enabled = bState;
  stPeakingCommandParameter->Enabled = bState;
  cbPeakingCommandParameter->Enabled = bState;
  stPeakingMeanShortWindowLength->Enabled = bState;
  cbPeakingMeanShortWindowLength->Enabled = bState;
  stPeakingMeanLongWindowLength->Enabled = bState;
  cbPeakingMeanLongWindowLength->Enabled = bState;
  stPeakingThresholdLevelNoise->Enabled = bState;
  cbPeakingThresholdLevelNoise->Enabled = bState;
  stPeakingThresholdLevelType->Enabled = bState;
  cbPeakingThresholdLevelType->Enabled = bState;
  stPeakingThresholdLevelFixed->Enabled = bState;
  cbPeakingThresholdLevelFixed->Enabled = bState;
  stPeakingThresholdLevelFloat->Enabled = bState;
  cbPeakingThresholdLevelFloat->Enabled = bState;
  // Patterning
  stPatterningPeakType->Enabled = bState;
  cbPatterningPeakType->Enabled = bState;
  stPatterningPeakParamMin->Enabled = bState;
  cbPatterningPeakParamMin->Enabled = bState;
  stPatterningPeakParamMax->Enabled = bState;
  cbPatterningPeakParamMax->Enabled = bState;
  stPatterningPeakParamSpace->Enabled = bState;
  cbPatterningPeakParamSpace->Enabled = bState;
  // Training
  stTrainingMode->Enabled = bState;
  cbTrainingMode->Enabled = bState;
  stTrainingDuration->Enabled = bState;
  cbTrainingDuration->Enabled = bState;
  // Stimulating
  stStimulatingType->Enabled = bState;
  cbStimulatingType->Enabled = bState;
  stStimulatingDuration->Enabled = bState;
  cbStimulatingDuration->Enabled = bState;
  stStimulatingIntensity->Enabled = bState;
  cbStimulatingIntensity->Enabled = bState;
  stStimulatingShift->Enabled = bState;
  cbStimulatingShift->Enabled = bState;
  stStimulatingMode3AlternativeIntensity->Enabled = bState;
  cbStimulatingMode3AlternativeIntensity->Enabled = bState;
  stStimulatingMode4AlternativeShift->Enabled = bState;
  cbStimulatingMode4AlternativeShift->Enabled = bState;
  stStimulatingMode5StimulusPeriod->Enabled = bState;
  cbStimulatingMode5StimulusPeriod->Enabled = bState;
  stStimulatingMode6NStimulusPeriod->Enabled = bState;
  cbStimulatingMode6NStimulusPeriod->Enabled = bState;
  stStimulatingMode6NStimulationTime->Enabled = bState;
  cbStimulatingMode6NStimulationTime->Enabled = bState;
  stStimulatingMode6NStimulationMask->Enabled = bState;
  cbStimulatingMode6NStimulationMask->Enabled = bState;
  stStimulatingMode7CycleTime->Enabled = bState;
  cbStimulatingMode7CycleTime->Enabled = bState;
  stStimulatingMode7Modulation->Enabled = bState;
  cbStimulatingMode7Modulation->Enabled = bState;
  stStimulatingMode8StimulusPeriod->Enabled = bState;
  cbStimulatingMode8StimulusPeriod->Enabled = bState;
  stStimulatingMode8ParadigmType->Enabled = bState;
  cbStimulatingMode8ParadigmType->Enabled = bState;
  stStimulatingMode9ParadigmType->Enabled = bState;
  cbStimulatingMode9ParadigmType->Enabled = bState;
  stStimulatingMode9StimulusNumber->Enabled = bState;
  cbStimulatingMode9StimulusNumber->Enabled = bState;
  stStimulatingMode9StimulusPeriod->Enabled = bState;
  cbStimulatingMode9StimulusPeriod->Enabled = bState;
  stStimulatingMode10ParadigmType->Enabled = bState;
  cbStimulatingMode10ParadigmType->Enabled = bState;
  stStimulatingMode10ShockType->Enabled = bState;
  cbStimulatingMode10ShockType->Enabled = bState;
  stStimulatingMode10AnalysisTime->Enabled = bState;
  cbStimulatingMode10AnalysisTime->Enabled = bState;
  // Plot
  stPlotWidth->Enabled = bState;
  cbPlotWidth->Enabled = bState;
  stPlotHeight->Enabled = bState;
  cbPlotHeight->Enabled = bState;
  stPlotXScale->Enabled = bState;
  cbPlotXScale->Enabled = bState;
  stPlotYScale->Enabled = bState;
  cbPlotYScale->Enabled = bState;
  // Port
  stMiscellaneousPort->Enabled = bState;
  cbMiscellaneousPort->Enabled = bState;
  // Output file name
  stOutputFileName->Enabled = bState;
  edOutputFileName->Enabled = bState;
  sbOutputFileName->Enabled = bState;
  // Input file name
  stInputFileName->Enabled = bState;
  edInputFileName->Enabled = bState;
  sbInputFileName->Enabled = bState;

	// Check current mode
  switch (fmMain->m_nOperatingModeIndex)
  {
  	case 0: // Online Processing
    {
    	/* Disabled */
      bState = false;
    	// Input file name
  		stInputFileName->Enabled = bState;
  		edInputFileName->Enabled = bState;
  		sbInputFileName->Enabled = bState;
      // For current training mode
      EnableItemsForTrainingMode();
    	break;
    }
    case 1: // Offline Processing
    {
    	/* Disabled */
      bState = false;
      // Digitizing
  		stDigitizingSampleRate->Enabled = bState;
      cbDigitizingSampleRate->Enabled = bState;
		  stDigitizingAmpGain->Enabled = bState;
      cbDigitizingAmpGain->Enabled = bState;
		  stDigitizingLoFreq->Enabled = bState;
      cbDigitizingLoFreq->Enabled = bState;
		  stDigitizingHiFreq->Enabled = bState;
      cbDigitizingHiFreq->Enabled = bState;
      // Training
  		stTrainingDuration->Enabled = bState;
  		cbTrainingDuration->Enabled = bState;
      // For training mode
      EnableItemsForTrainingMode();
    	break;
    }
    case 2: // Offline Veiwing
    {
    	/* Disabled */
      bState = false;
    	// Digitizing
		  stDigitizingSampleRate->Enabled = bState;
		  stDigitizingAmpGain->Enabled = bState;
		  stDigitizingLoFreq->Enabled = bState;
		  stDigitizingHiFreq->Enabled = bState;
		  cbDigitizingSampleRate->Enabled = bState;
		  cbDigitizingAmpGain->Enabled = bState;
		  cbDigitizingLoFreq->Enabled = bState;
	  	cbDigitizingHiFreq->Enabled = bState;
		  // Processing
		  stMiscellaneousFilterType->Enabled = bState;
		  cbMiscellaneousFilterType->Enabled = bState;
		  // Peaking
      stPeakingDeadTime->Enabled = bState;
		  cbPeakingDeadTime->Enabled = bState;
      stPeakingCommandParameter->Enabled = bState;
      cbPeakingCommandParameter->Enabled = bState;
      stPeakingMeanShortWindowLength->Enabled = bState;
      cbPeakingMeanShortWindowLength->Enabled = bState;
      stPeakingMeanLongWindowLength->Enabled = bState;
      cbPeakingMeanLongWindowLength->Enabled = bState;
		  stPeakingThresholdLevelNoise->Enabled = bState;
		  cbPeakingThresholdLevelNoise->Enabled = bState;
      stPeakingThresholdLevelType->Enabled = bState;
      cbPeakingThresholdLevelType->Enabled = bState;
      stPeakingThresholdLevelFixed->Enabled = bState;
		  cbPeakingThresholdLevelFixed->Enabled = bState;
		  stPeakingThresholdLevelFloat->Enabled = bState;
		  cbPeakingThresholdLevelFloat->Enabled = bState;
      // Patterning
      stPatterningPeakType->Enabled = bState;
      cbPatterningPeakType->Enabled = bState;
      stPatterningPeakParamMin->Enabled = bState;
      cbPatterningPeakParamMin->Enabled = bState;
      stPatterningPeakParamMax->Enabled = bState;
      cbPatterningPeakParamMax->Enabled = bState;
      stPatterningPeakParamSpace->Enabled = bState;
      cbPatterningPeakParamSpace->Enabled = bState;
      // Training
		  stTrainingMode->Enabled = bState;
		  cbTrainingMode->Enabled = bState;
		  stTrainingDuration->Enabled = bState;
		  cbTrainingDuration->Enabled = bState;
		  // Stimulating
  		stStimulatingType->Enabled = bState;
  		cbStimulatingType->Enabled = bState;
      stStimulatingDuration->Enabled = bState;
  		cbStimulatingDuration->Enabled = bState;
      stStimulatingIntensity->Enabled = bState;
  		cbStimulatingIntensity->Enabled = bState;
  		stStimulatingShift->Enabled = bState;
  		cbStimulatingShift->Enabled = bState;
  		stStimulatingMode3AlternativeIntensity->Enabled = bState;
  		cbStimulatingMode3AlternativeIntensity->Enabled = bState;
  		stStimulatingMode4AlternativeShift->Enabled = bState;
  		cbStimulatingMode4AlternativeShift->Enabled = bState;
  		stStimulatingMode5StimulusPeriod->Enabled = bState;
  		cbStimulatingMode5StimulusPeriod->Enabled = bState;
  		stStimulatingMode6NStimulusPeriod->Enabled = bState;
  		cbStimulatingMode6NStimulusPeriod->Enabled = bState;
  		stStimulatingMode6NStimulationTime->Enabled = bState;
  		cbStimulatingMode6NStimulationTime->Enabled = bState;
  		stStimulatingMode6NStimulationMask->Enabled = bState;
  		cbStimulatingMode6NStimulationMask->Enabled = bState;
  		stStimulatingMode7CycleTime->Enabled = bState;
  		cbStimulatingMode7CycleTime->Enabled = bState;
      stStimulatingMode7Modulation->Enabled = bState;
  		cbStimulatingMode7Modulation->Enabled = bState;
      stStimulatingMode8StimulusPeriod->Enabled = bState;
  		cbStimulatingMode8StimulusPeriod->Enabled = bState;
      stStimulatingMode8ParadigmType->Enabled = bState;
      cbStimulatingMode8ParadigmType->Enabled = bState;
      stStimulatingMode9ParadigmType->Enabled = bState;
      cbStimulatingMode9ParadigmType->Enabled = bState;
      stStimulatingMode9StimulusNumber->Enabled = bState;
      cbStimulatingMode9StimulusNumber->Enabled = bState;
      stStimulatingMode9StimulusPeriod->Enabled = bState;
      cbStimulatingMode9StimulusPeriod->Enabled = bState;
      stStimulatingMode10ParadigmType->Enabled = bState;
      cbStimulatingMode10ParadigmType->Enabled = bState;
      stStimulatingMode10ShockType->Enabled = bState;
      cbStimulatingMode10ShockType->Enabled = bState;
      stStimulatingMode10AnalysisTime->Enabled = bState;
      cbStimulatingMode10AnalysisTime->Enabled = bState;
		  // Port
		  stMiscellaneousPort->Enabled = bState;
		  cbMiscellaneousPort->Enabled = bState;
		  // Input file name
		  stInputFileName->Enabled = bState;
		  edInputFileName->Enabled = bState;
		  sbInputFileName->Enabled = bState;
    	break;
    }
  }
}

//---------------------------------------------------------------------------
void __fastcall TfmSettings::EnableItemsForTrainingMode()
{
	bool bState;
  bState = false;
  
  /* Disable */
  // Peaking
  stPeakingCommandParameter->Enabled = bState;
  cbPeakingCommandParameter->Enabled = bState;
  stPeakingMeanShortWindowLength->Enabled = bState;
  cbPeakingMeanShortWindowLength->Enabled = bState;
  stPeakingMeanLongWindowLength->Enabled = bState;
  cbPeakingMeanLongWindowLength->Enabled = bState;
  stPeakingThresholdLevelType->Enabled = bState;
  cbPeakingThresholdLevelType->Enabled = bState;
  stPeakingThresholdLevelFixed->Enabled = bState;
  cbPeakingThresholdLevelFixed->Enabled = bState;
  stPeakingThresholdLevelFloat->Enabled = bState;
  cbPeakingThresholdLevelFloat->Enabled = bState;
  // Patterning
  stPatterningPeakType->Enabled = bState;
  cbPatterningPeakType->Enabled = bState;
  stPatterningPeakParamMin->Enabled = bState;
  cbPatterningPeakParamMin->Enabled = bState;
  stPatterningPeakParamMax->Enabled = bState;
  cbPatterningPeakParamMax->Enabled = bState;
  stPatterningPeakParamSpace->Enabled = bState;
  cbPatterningPeakParamSpace->Enabled = bState;
  // Modes
  stStimulatingMode3AlternativeIntensity->Enabled = bState;
  cbStimulatingMode3AlternativeIntensity->Enabled = bState;
  stStimulatingMode4AlternativeShift->Enabled = bState;
  cbStimulatingMode4AlternativeShift->Enabled = bState;
  stStimulatingMode5StimulusPeriod->Enabled = bState;
  cbStimulatingMode5StimulusPeriod->Enabled = bState;
  stStimulatingMode6NStimulusPeriod->Enabled = bState;
  cbStimulatingMode6NStimulusPeriod->Enabled = bState;
  stStimulatingMode6NStimulationTime->Enabled = bState;
  cbStimulatingMode6NStimulationTime->Enabled = bState;
  stStimulatingMode6NStimulationMask->Enabled = bState;
  cbStimulatingMode6NStimulationMask->Enabled = bState;
  stStimulatingMode7CycleTime->Enabled = bState;
  cbStimulatingMode7CycleTime->Enabled = bState;
  stStimulatingMode7Modulation->Enabled = bState;
  cbStimulatingMode7Modulation->Enabled = bState;
  stStimulatingMode8StimulusPeriod->Enabled = bState;
  cbStimulatingMode8StimulusPeriod->Enabled = bState;
  stStimulatingMode8ParadigmType->Enabled = bState;
  cbStimulatingMode8ParadigmType->Enabled = bState;
  stStimulatingMode9ParadigmType->Enabled = bState;
  cbStimulatingMode9ParadigmType->Enabled = bState;
  stStimulatingMode9StimulusNumber->Enabled = bState;
  cbStimulatingMode9StimulusNumber->Enabled = bState;
  stStimulatingMode9StimulusPeriod->Enabled = bState;
  cbStimulatingMode9StimulusPeriod->Enabled = bState;
  stStimulatingMode10ParadigmType->Enabled = bState;
  cbStimulatingMode10ParadigmType->Enabled = bState;
  stStimulatingMode10ShockType->Enabled = bState;
  cbStimulatingMode10ShockType->Enabled = bState;
  stStimulatingMode10AnalysisTime->Enabled = bState;
  cbStimulatingMode10AnalysisTime->Enabled = bState;
  
  // Set training mode name
  cbTrainingMode->Text = cbTrainingMode->Items->Strings[fmMain->m_nTrainingModeIndex];
  
  // Set training mode params
	switch (fmMain->m_nTrainingModeIndex)
  {
  	case STIM_MODE_1: // Peak-wave stimulation
    {
    	/* Enable */
    	pcStimulatingMode->ActivePageIndex = tsStimulatingMode1->TabIndex;
    	break;
    }
    case STIM_MODE_2: // Peak-wave threshold stimulation
    {
    	/* Enable */
      bState = true;
      stPeakingCommandParameter->Enabled = bState;
      cbPeakingCommandParameter->Enabled = bState;
      if (fmMain->m_nPeakingCommandParameterIndex == 1)
      {
        stPeakingMeanShortWindowLength->Enabled = bState;
        cbPeakingMeanShortWindowLength->Enabled = bState;
      }
      stPeakingThresholdLevelType->Enabled = bState;
      cbPeakingThresholdLevelType->Enabled = bState;
      if (fmMain->m_nPeakingThresholdLevelTypeIndex == 0)
      {
  		  stPeakingThresholdLevelFloat->Enabled = bState;
  		  cbPeakingThresholdLevelFloat->Enabled = bState;
        stPeakingMeanLongWindowLength->Enabled = bState;
        cbPeakingMeanLongWindowLength->Enabled = bState;
      }
      else
      {
        stPeakingThresholdLevelFixed->Enabled = bState;
  		  cbPeakingThresholdLevelFixed->Enabled = bState;
      }
      pcStimulatingMode->ActivePageIndex = tsStimulatingMode2->TabIndex;
    	break;
    }
    case STIM_MODE_3: // Peak-wave power control stimulation
    {
    	/* Enable */
      bState = true;
      stPeakingCommandParameter->Enabled = bState;
      cbPeakingCommandParameter->Enabled = bState;
      if (fmMain->m_nPeakingCommandParameterIndex == 1)
      {
        stPeakingMeanShortWindowLength->Enabled = bState;
        cbPeakingMeanShortWindowLength->Enabled = bState;
      }
      stPeakingThresholdLevelType->Enabled = bState;
      cbPeakingThresholdLevelType->Enabled = bState;
      if (fmMain->m_nPeakingThresholdLevelTypeIndex == 0)
      {
  		  stPeakingThresholdLevelFloat->Enabled = bState;
  		  cbPeakingThresholdLevelFloat->Enabled = bState;
        stPeakingMeanLongWindowLength->Enabled = bState;
        cbPeakingMeanLongWindowLength->Enabled = bState;
      }
      else
      {
        stPeakingThresholdLevelFixed->Enabled = bState;
  		  cbPeakingThresholdLevelFixed->Enabled = bState;
      }
		  stStimulatingMode3AlternativeIntensity->Enabled = bState;
		  cbStimulatingMode3AlternativeIntensity->Enabled = bState;
      pcStimulatingMode->ActivePageIndex = tsStimulatingMode3->TabIndex;
    	break;
    }
    case STIM_MODE_4: // Peak-wave delay control stimulation
    {
    	/* Enable */
      bState = true;
      stPeakingCommandParameter->Enabled = bState;
      cbPeakingCommandParameter->Enabled = bState;
      if (fmMain->m_nPeakingCommandParameterIndex == 1)
      {
        stPeakingMeanShortWindowLength->Enabled = bState;
        cbPeakingMeanShortWindowLength->Enabled = bState;
      }
      stPeakingThresholdLevelType->Enabled = bState;
      cbPeakingThresholdLevelType->Enabled = bState;
      if (fmMain->m_nPeakingThresholdLevelTypeIndex == 0)
      {
  		  stPeakingThresholdLevelFloat->Enabled = bState;
  		  cbPeakingThresholdLevelFloat->Enabled = bState;
        stPeakingMeanLongWindowLength->Enabled = bState;
        cbPeakingMeanLongWindowLength->Enabled = bState;
      }
      else
      {
        stPeakingThresholdLevelFixed->Enabled = bState;
  		  cbPeakingThresholdLevelFixed->Enabled = bState;
      }
		  stStimulatingMode4AlternativeShift->Enabled = bState;
		  cbStimulatingMode4AlternativeShift->Enabled = bState;
      pcStimulatingMode->ActivePageIndex = tsStimulatingMode4->TabIndex;
    	break;
    }
    case STIM_MODE_5: // Rhythmic stimulation
    {
    	/* Enable */
      bState = true;
      stStimulatingMode5StimulusPeriod->Enabled = bState;
      cbStimulatingMode5StimulusPeriod->Enabled = bState;
      pcStimulatingMode->ActivePageIndex = tsStimulatingMode5->TabIndex;
      break;
    }
    case STIM_MODE_6N: // Adaptive rhythmic stimulation
    {
    	/* Enable */
      bState = true;
      stPeakingCommandParameter->Enabled = bState;
      cbPeakingCommandParameter->Enabled = bState;
      if (fmMain->m_nPeakingCommandParameterIndex == 1)
      {
        stPeakingMeanShortWindowLength->Enabled = bState;
        cbPeakingMeanShortWindowLength->Enabled = bState;
      }
      stPeakingThresholdLevelType->Enabled = bState;
      cbPeakingThresholdLevelType->Enabled = bState;
      if (fmMain->m_nPeakingThresholdLevelTypeIndex == 0)
      {
  		  stPeakingThresholdLevelFloat->Enabled = bState;
  		  cbPeakingThresholdLevelFloat->Enabled = bState;
        stPeakingMeanLongWindowLength->Enabled = bState;
        cbPeakingMeanLongWindowLength->Enabled = bState;
      }
      else
      {
        stPeakingThresholdLevelFixed->Enabled = bState;
  		  cbPeakingThresholdLevelFixed->Enabled = bState;
      }
		  stStimulatingMode6NStimulusPeriod->Enabled = bState;
		  cbStimulatingMode6NStimulusPeriod->Enabled = bState;
		  stStimulatingMode6NStimulationTime->Enabled = bState;
		  cbStimulatingMode6NStimulationTime->Enabled = bState;
		  stStimulatingMode6NStimulationMask->Enabled = bState;
		  cbStimulatingMode6NStimulationMask->Enabled = bState;
      pcStimulatingMode->ActivePageIndex = tsStimulatingMode6->TabIndex;
    	break;
    }
    case STIM_MODE_7:
    {
    	/* Enable */
      bState = true;
      stPeakingCommandParameter->Enabled = bState;
      cbPeakingCommandParameter->Enabled = bState;
      if (fmMain->m_nPeakingCommandParameterIndex == 1)
      {
        stPeakingMeanShortWindowLength->Enabled = bState;
        cbPeakingMeanShortWindowLength->Enabled = bState;
      }
      stPeakingThresholdLevelType->Enabled = bState;
      cbPeakingThresholdLevelType->Enabled = bState;
      if (fmMain->m_nPeakingThresholdLevelTypeIndex == 0)
      {
  		  stPeakingThresholdLevelFloat->Enabled = bState;
  		  cbPeakingThresholdLevelFloat->Enabled = bState;
        stPeakingMeanLongWindowLength->Enabled = bState;
        cbPeakingMeanLongWindowLength->Enabled = bState;
      }
      else
      {
        stPeakingThresholdLevelFixed->Enabled = bState;
  		  cbPeakingThresholdLevelFixed->Enabled = bState;
      }
      stStimulatingMode7CycleTime->Enabled = bState;
		  cbStimulatingMode7CycleTime->Enabled = bState;
      stStimulatingMode7Modulation->Enabled = bState;
  		cbStimulatingMode7Modulation->Enabled = bState;
  		pcStimulatingMode->ActivePageIndex = tsStimulatingMode7->TabIndex;
      break;
    }
    case STIM_MODE_8: // Rhythmic threshold stimulation
    {
    	/* Enable */
      bState = true;
      stPeakingCommandParameter->Enabled = bState;
      cbPeakingCommandParameter->Enabled = bState;
      if (fmMain->m_nPeakingCommandParameterIndex == 1)
      {
        stPeakingMeanShortWindowLength->Enabled = bState;
        cbPeakingMeanShortWindowLength->Enabled = bState;
      }
      stPeakingThresholdLevelType->Enabled = bState;
      cbPeakingThresholdLevelType->Enabled = bState;
      if (fmMain->m_nPeakingThresholdLevelTypeIndex == 0)
      {
  		  stPeakingThresholdLevelFloat->Enabled = bState;
  		  cbPeakingThresholdLevelFloat->Enabled = bState;
        stPeakingMeanLongWindowLength->Enabled = bState;
        cbPeakingMeanLongWindowLength->Enabled = bState;
      }
      else
      {
        stPeakingThresholdLevelFixed->Enabled = bState;
  		  cbPeakingThresholdLevelFixed->Enabled = bState;
      }
      stStimulatingMode8StimulusPeriod->Enabled = bState;
      cbStimulatingMode8StimulusPeriod->Enabled = bState;
      stStimulatingMode8ParadigmType->Enabled = bState;
      cbStimulatingMode8ParadigmType->Enabled = bState;
      pcStimulatingMode->ActivePageIndex = tsStimulatingMode8->TabIndex;
      break;
    }
    case STIM_MODE_9: // Pattern simple paradigm stimulation
    {
    	/* Enable */
      bState = true;
      stPeakingCommandParameter->Enabled = bState;
      cbPeakingCommandParameter->Enabled = bState;
      if (fmMain->m_nPeakingCommandParameterIndex == 1)
      {
        stPeakingMeanShortWindowLength->Enabled = bState;
        cbPeakingMeanShortWindowLength->Enabled = bState;
      }
      stPeakingThresholdLevelType->Enabled = bState;
      cbPeakingThresholdLevelType->Enabled = bState;
      if (fmMain->m_nPeakingThresholdLevelTypeIndex == 0)
      {
  		  stPeakingThresholdLevelFloat->Enabled = bState;
  		  cbPeakingThresholdLevelFloat->Enabled = bState;
        stPeakingMeanLongWindowLength->Enabled = bState;
        cbPeakingMeanLongWindowLength->Enabled = bState;
      }
      else
      {
        stPeakingThresholdLevelFixed->Enabled = bState;
  		  cbPeakingThresholdLevelFixed->Enabled = bState;
      }
      // Patterning
      stPatterningPeakType->Enabled = bState;
      cbPatterningPeakType->Enabled = bState;
      stPatterningPeakParamMin->Enabled = bState;
      cbPatterningPeakParamMin->Enabled = bState;
      stPatterningPeakParamMax->Enabled = bState;
      cbPatterningPeakParamMax->Enabled = bState;
      stPatterningPeakParamSpace->Enabled = bState;
      cbPatterningPeakParamSpace->Enabled = bState;
      // Mode 9
      stStimulatingMode9ParadigmType->Enabled = bState;
      cbStimulatingMode9ParadigmType->Enabled = bState;
      stStimulatingMode9StimulusNumber->Enabled = bState;
      cbStimulatingMode9StimulusNumber->Enabled = bState;
      stStimulatingMode9StimulusPeriod->Enabled = bState;
      cbStimulatingMode9StimulusPeriod->Enabled = bState;
      pcStimulatingMode->ActivePageIndex = tsStimulatingMode9->TabIndex;
      break;
    }
    case STIM_MODE_10: // Pattern current paradigm stimulation
    {
    	/* Enable */
      bState = true;
      stPeakingCommandParameter->Enabled = bState;
      cbPeakingCommandParameter->Enabled = bState;
      if (fmMain->m_nPeakingCommandParameterIndex == 1)
      {
        stPeakingMeanShortWindowLength->Enabled = bState;
        cbPeakingMeanShortWindowLength->Enabled = bState;
      }
      stPeakingThresholdLevelType->Enabled = bState;
      cbPeakingThresholdLevelType->Enabled = bState;
      if (fmMain->m_nPeakingThresholdLevelTypeIndex == 0)
      {
  		  stPeakingThresholdLevelFloat->Enabled = bState;
  		  cbPeakingThresholdLevelFloat->Enabled = bState;
        stPeakingMeanLongWindowLength->Enabled = bState;
        cbPeakingMeanLongWindowLength->Enabled = bState;
      }
      else
      {
        stPeakingThresholdLevelFixed->Enabled = bState;
  		  cbPeakingThresholdLevelFixed->Enabled = bState;
      }
      // Patterning
      stPatterningPeakType->Enabled = bState;
      cbPatterningPeakType->Enabled = bState;
      stPatterningPeakParamMin->Enabled = bState;
      cbPatterningPeakParamMin->Enabled = bState;
      stPatterningPeakParamMax->Enabled = bState;
      cbPatterningPeakParamMax->Enabled = bState;
      stPatterningPeakParamSpace->Enabled = bState;
      cbPatterningPeakParamSpace->Enabled = bState;
      // Mode 10
      stStimulatingMode10ParadigmType->Enabled = bState;
      cbStimulatingMode10ParadigmType->Enabled = bState;
      stStimulatingMode10ShockType->Enabled = bState;
      cbStimulatingMode10ShockType->Enabled = bState;
      stStimulatingMode10AnalysisTime->Enabled = bState;
      cbStimulatingMode10AnalysisTime->Enabled = bState;
      pcStimulatingMode->ActivePageIndex = tsStimulatingMode10->TabIndex;
      break;
    }
  }
}

//---------------------------------------------------------------------------
void __fastcall TfmSettings::CheckPort(AnsiString aMiscellaneousPort)
{
  TRegistry *Reg = new TRegistry;
  TStringList *List = new TStringList;
  AnsiString aRegPort;

  // Get serial ports from registry
  Reg->RootKey = HKEY_LOCAL_MACHINE;
  Reg->OpenKey("HARDWARE\\DEVICEMAP\\SERIALCOMM", false);
  Reg->GetValueNames(List);
  aRegPort = Reg->ReadString(List->Strings[List->Count - 1]);
  List->Free();
  Reg->CloseKey();
  Reg->Free();

  // Check port
  if (aMiscellaneousPort == aRegPort)
    stMiscellaneousPort->Font->Color = clBlack;
  else
    stMiscellaneousPort->Font->Color = clRed;
}

//---------------------------------------------------------------------------
bool __fastcall TfmSettings::GetFileParams(AnsiString aFileName, bool bMessage)
{
  FILE *pStream;
  int nStimulatingIntensity, nStimulatingShift, nStimulatingMode3AlternativeIntensity,
  	nStimulatingMode4AlternativeShift;
  int nStringCount = 0;

  // Check existing file
  if ((pStream = fopen(aFileName.c_str(), "rt")) == NULL)
  {
    if (bMessage)
      MessageBox(NULL, "Cannot open file", "File error", MB_OK | MB_ICONERROR);
    fclose(pStream);
    return true;
  }
  // Check file format
  if (fmMain->CheckFileFormat(pStream))
  {
    if (bMessage)
      MessageBox(NULL, "Wrong file format", "File error", MB_OK | MB_ICONERROR);
    fclose(pStream);
    return true;
  }
  // Get file header
  fscanf(pStream,
    "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
  	&fmMain->m_nSampleRate, &fmMain->m_nAmpGainIndex, &fmMain->m_nLoFreqIndex, &fmMain->m_nHiFreqIndex,
    &fmMain->m_nMiscellaneousFilterTypeIndex, &fmMain->m_nPeakingDeadTime,
    &fmMain->m_nPeakingCommandParameterIndex,
    &fmMain->m_nPeakingMeanShortWindowLength, &fmMain->m_nPeakingMeanLongWindowLength,
    &fmMain->m_pPeakingThresholdLevelArray[0], &fmMain->m_nPeakingThresholdLevelTypeIndex,
    &fmMain->m_pPeakingThresholdLevelArray[1], &fmMain->m_pPeakingThresholdLevelArray[2],
    &fmMain->m_nPatterningPeakParamIndex, &fmMain->m_pPatterningPeakParamArray[0],
    &fmMain->m_pPatterningPeakParamArray[1], &fmMain->m_pPatterningPeakParamArray[2],
    &fmMain->m_nTrainingModeIndex, &fmMain->m_nTrainingDuration,
    &fmMain->m_nTrainingDurationRatio, &fmMain->m_nStimulatingTypeIndex,
    &fmMain->m_nStimulatingDuration, &nStimulatingIntensity, &nStimulatingShift,
    &fmMain->m_nStimulatingVideoSet, &fmMain->m_nStimulatingAudioSet,
    &nStimulatingMode3AlternativeIntensity, &nStimulatingMode4AlternativeShift,
    &fmMain->m_nStimulatingMode5StimulusPeriod, &fmMain->m_nStimulatingMode6NStimulusPeriod,
    &fmMain->m_nStimulatingMode6NStimulationTime, &fmMain->m_nStimulatingMode6NStimulationMaskIndex,
    &fmMain->m_nStimulatingMode7CycleTime, &fmMain->m_nStimulatingMode7ModulationIndex,
    &fmMain->m_nStimulatingMode8StimulusPeriod, &fmMain->m_nStimulatingMode8ParadigmTypeIndex,
    &fmMain->m_nStimulatingMode9ParadigmTypeIndex, &fmMain->m_nStimulatingMode9StimulusNumber,
    &fmMain->m_nStimulatingMode9StimulusPeriod, &fmMain->m_nStimulatingMode10ParadigmTypeIndex,
    &fmMain->m_nStimulatingMode10ShockTypeIndex, &fmMain->m_nStimulatingMode10AnalysisTime);

  fmMain->m_nStimulatingIntensityIndex =
  	cbStimulatingIntensity->Items->IndexOf(IntToStr(nStimulatingIntensity));
  fmMain->m_nStimulatingShiftIndex =
  	cbStimulatingShift->Items->IndexOf(IntToStr(nStimulatingShift));
  fmMain->m_nStimulatingMode3AlternativeIntensityIndex =
  	cbStimulatingMode3AlternativeIntensity->Items->IndexOf(IntToStr(nStimulatingMode3AlternativeIntensity));
  fmMain->m_nStimulatingMode4AlternativeShiftIndex =
  	cbStimulatingMode4AlternativeShift->Items->IndexOf(IntToStr(nStimulatingMode4AlternativeShift));
  // Get file length
  while (!feof(pStream))
  {
  	if (fgetc(pStream) == '\n')
    	nStringCount += 1;
  }
  fmMain->m_nTrainingTime = nStringCount / fmMain->m_nSampleRate;
  // Close file
  fclose(pStream);

  return false;
}

//---------------------------------------------------------------------------
AnsiString __fastcall TfmSettings::GetShortFileName(AnsiString aFileName)
{
  // Get short file name
  int nCount = 0;
  int nPosition;

  // Routine
  while (nCount < aFileName.Length())
  {
  	nPosition = aFileName.Pos("\\");
    if (!nPosition)
    {
    	break;
    }
    aFileName.Delete(1, nPosition);
    nCount += 1;
  }
  return aFileName;
}

//***************************************************************************
// Events
//***************************************************************************
void __fastcall TfmSettings::FormShow(TObject *Sender)
{
  // Init items for operating mode
	InitItemsForOperatingMode();
  // Enable items for operating mode
	EnableItemsForOperatingMode();
}
//---------------------------------------------------------------------------
void __fastcall TfmSettings::sbOutputFileNameClick(TObject *Sender)
{
	if (!dlgOpenOutputFile->Execute())
  	return;

  // Init output file name
  fmMain->m_aOutputFileName = dlgOpenOutputFile->FileName;
  // Add extension
  if (fmMain->m_nOperatingModeIndex == 0 || fmMain->m_nOperatingModeIndex == 1)
  {
    int nLength = fmMain->m_aOutputFileName.Length();
    if (fmMain->m_aOutputFileName.SubString(nLength - 2, 3) != ".ss")
      fmMain->m_aOutputFileName += ".ss";
  }
  edOutputFileName->Text = GetShortFileName(fmMain->m_aOutputFileName);

  // Get header file
  if (fmMain->m_nOperatingModeIndex == 2)
  {
    bnApply->Enabled = false;
    if (!GetFileParams(fmMain->m_aOutputFileName, true))
    {
      InitItemsForOperatingMode();
      bnApply->Enabled = true;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfmSettings::sbInputFileNameClick(TObject *Sender)
{
	if (!dlgOpenInputFile->Execute())
  	return;

   // Init input file name
  fmMain->m_aInputFileName = dlgOpenInputFile->FileName;
  // Add to edit
  edInputFileName->Text = GetShortFileName(fmMain->m_aInputFileName);
  // Get header file
  if (fmMain->m_nOperatingModeIndex == 1)
  {
    bnApply->Enabled = false;
    if (!GetFileParams(fmMain->m_aInputFileName, true))
    {
      InitItemsForOperatingMode();
      bnApply->Enabled = true;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfmSettings::cbTrainingModeChange(TObject *Sender)
{
  // Enable items for current training mode
  fmMain->m_nTrainingModeIndex = cbTrainingMode->Items->IndexOf(cbTrainingMode->Text);
	EnableItemsForTrainingMode();
}
//---------------------------------------------------------------------------
void __fastcall TfmSettings::bnApplyClick(TObject *Sender)
{
	/* Pass settings to main module (fmMain) */
  // Digitizing
  fmMain->m_nSampleRate = StrToInt(cbDigitizingSampleRate->Text);
  fmMain->m_nAmpGainIndex = cbDigitizingAmpGain->Items->IndexOf(cbDigitizingAmpGain->Text);
  fmMain->m_nAmpGain = StrToInt(cbDigitizingAmpGain->Text);
  fmMain->m_nLoFreqIndex = cbDigitizingLoFreq->Items->IndexOf(cbDigitizingLoFreq->Text);
  fmMain->m_nHiFreqIndex = cbDigitizingHiFreq->Items->IndexOf(cbDigitizingHiFreq->Text);
  // Processing
  fmMain->m_nMiscellaneousFilterTypeIndex = cbMiscellaneousFilterType->Items->IndexOf(cbMiscellaneousFilterType->Text);
  // Peaking
  fmMain->m_nPeakingDeadTime = StrToInt(cbPeakingDeadTime->Text);
  fmMain->m_nPeakingCommandParameterIndex =
    cbPeakingCommandParameter->Items->IndexOf(cbPeakingCommandParameter->Text);
  fmMain->m_nPeakingMeanShortWindowLength = StrToInt(cbPeakingMeanShortWindowLength->Text);
  fmMain->m_nPeakingMeanLongWindowLength = StrToInt(cbPeakingMeanLongWindowLength->Text);
  fmMain->m_pPeakingThresholdLevelArray[0] = StrToInt(cbPeakingThresholdLevelNoise->Text);
  if (fmMain->m_nTrainingModeIndex == STIM_MODE_5)
    fmMain->m_pPeakingThresholdLevelArray[0] = 0;
  fmMain->m_nPeakingThresholdLevelTypeIndex =
    cbPeakingThresholdLevelType->Items->IndexOf(cbPeakingThresholdLevelType->Text);
  if (fmMain->m_nTrainingModeIndex == STIM_MODE_5)
    fmMain->m_nPeakingThresholdLevelTypeIndex = 0;
  fmMain->m_pPeakingThresholdLevelArray[1] = StrToInt(cbPeakingThresholdLevelFixed->Text);
  fmMain->m_pPeakingThresholdLevelArray[2] = StrToInt(cbPeakingThresholdLevelFloat->Text);
  // Patterning
  fmMain->m_nPatterningPeakParamIndex =
    cbPatterningPeakType->Items->IndexOf(cbPatterningPeakType->Text);
  fmMain->m_pPatterningPeakParamArray[0] = StrToInt(cbPatterningPeakParamMin->Text);
  fmMain->m_pPatterningPeakParamArray[1] = StrToInt(cbPatterningPeakParamMax->Text);
  fmMain->m_pPatterningPeakParamArray[2] = StrToInt(cbPatterningPeakParamSpace->Text);
  // Training
  fmMain->m_nTrainingModeIndex = cbTrainingMode->Items->IndexOf(cbTrainingMode->Text);
  fmMain->m_nTrainingDuration = StrToInt(cbTrainingDuration->Text);
  // Stimulating
  fmMain->m_nStimulatingTypeIndex = cbStimulatingType->Items->IndexOf(cbStimulatingType->Text);
  fmMain->m_nStimulatingDuration = StrToInt(cbStimulatingDuration->Text);
  fmMain->m_nStimulatingIntensityIndex = cbStimulatingIntensity->Items->IndexOf(cbStimulatingIntensity->Text);
  fmMain->m_nStimulatingShiftIndex = cbStimulatingShift->Items->IndexOf(cbStimulatingShift->Text);
  fmMain->m_nStimulatingVideoSet = StrToInt(cbStimulatingVideoSet->Text);
  fmMain->m_nStimulatingAudioSet = StrToInt(cbStimulatingAudioSet->Text);
  fmMain->m_nStimulatingMode3AlternativeIntensityIndex =
  	cbStimulatingMode3AlternativeIntensity->Items->IndexOf(cbStimulatingMode3AlternativeIntensity->Text);
  fmMain->m_nStimulatingMode4AlternativeShiftIndex =
  	cbStimulatingMode4AlternativeShift->Items->IndexOf(cbStimulatingMode4AlternativeShift->Text);
  fmMain->m_nStimulatingMode5StimulusPeriod = StrToInt(cbStimulatingMode5StimulusPeriod->Text);
  fmMain->m_nStimulatingMode6NStimulusPeriod = StrToInt(cbStimulatingMode6NStimulusPeriod->Text);
  fmMain->m_nStimulatingMode6NStimulationTime = StrToInt(cbStimulatingMode6NStimulationTime->Text);
  fmMain->m_nStimulatingMode6NStimulationMaskIndex =
    cbStimulatingMode6NStimulationMask->Items->IndexOf(cbStimulatingMode6NStimulationMask->Text);
  fmMain->m_nStimulatingMode7CycleTime = StrToInt(cbStimulatingMode7CycleTime->Text);
  fmMain->m_nStimulatingMode7ModulationIndex =
  	cbStimulatingMode7Modulation->Items->IndexOf(cbStimulatingMode7Modulation->Text);
  fmMain->m_nStimulatingMode8StimulusPeriod = StrToInt(cbStimulatingMode8StimulusPeriod->Text);
  fmMain->m_nStimulatingMode8ParadigmTypeIndex =
    cbStimulatingMode8ParadigmType->Items->IndexOf(cbStimulatingMode8ParadigmType->Text);
  fmMain->m_nStimulatingMode9ParadigmTypeIndex =
    cbStimulatingMode9ParadigmType->Items->IndexOf(cbStimulatingMode9ParadigmType->Text);
  fmMain->m_nStimulatingMode9StimulusNumber = StrToInt(cbStimulatingMode9StimulusNumber->Text);
  fmMain->m_nStimulatingMode9StimulusPeriod = StrToInt(cbStimulatingMode9StimulusPeriod->Text);
  fmMain->m_nStimulatingMode10ParadigmTypeIndex =
    cbStimulatingMode10ParadigmType->Items->IndexOf(cbStimulatingMode10ParadigmType->Text);
  fmMain->m_nStimulatingMode10ShockTypeIndex =
  	cbStimulatingMode10ShockType->Items->IndexOf(cbStimulatingMode10ShockType->Text);
  fmMain->m_nStimulatingMode10AnalysisTime = StrToInt(cbStimulatingMode10AnalysisTime->Text);
  // Plot
  fmMain->m_nPlotWidth = StrToInt(cbPlotWidth->Text);
  fmMain->m_nPlotHeight = StrToInt(cbPlotHeight->Text) / 3;
  fmMain->m_nPlotXScale = StrToInt(cbPlotXScale->Text);
  fmMain->m_nPlotYScale = StrToInt(cbPlotYScale->Text);
  // Port
  fmMain->m_aMiscellaneousPort = cbMiscellaneousPort->Text;

  /* Data settings */
  fmMain->m_nDataSize = 4;
  fmMain->m_nBlockSize = fmMain->m_nPlotWidth / (fmMain->m_nDataSize *
    fmMain->m_nPlotXScale);

  // Confirm apply
  fmMain->m_bSettingsApplied = true;
  // Close settings window
	fmSettings->Close();
  // Clear plot
  fmMain->blPlot->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfmSettings::bnCancelClick(TObject *Sender)
{
	/* Reset params */
	cbDigitizingSampleRate->Text = IntToStr(fmMain->m_nSampleRate);
  cbDigitizingAmpGain->Text = cbDigitizingAmpGain->Items->Strings[fmMain->m_nAmpGainIndex];
  cbDigitizingLoFreq->Text = cbDigitizingLoFreq->Items->Strings[fmMain->m_nLoFreqIndex];
  cbDigitizingHiFreq->Text = cbDigitizingHiFreq->Items->Strings[fmMain->m_nHiFreqIndex];
  // Processing
  cbMiscellaneousFilterType->Text = cbMiscellaneousFilterType->Items->Strings[fmMain->m_nMiscellaneousFilterTypeIndex];
  // Peaking
  cbPeakingDeadTime->Text = IntToStr(fmMain->m_nPeakingDeadTime);
  cbPeakingCommandParameter->Text =
    cbStimulatingType->Items->Strings[fmMain->m_nPeakingCommandParameterIndex];
  cbPeakingMeanShortWindowLength->Text = IntToStr(fmMain->m_nPeakingMeanShortWindowLength);
  cbPeakingMeanLongWindowLength->Text = IntToStr(fmMain->m_nPeakingMeanLongWindowLength);
  cbPeakingThresholdLevelNoise->Text = IntToStr(fmMain->m_pPeakingThresholdLevelArray[0]);
  cbPeakingThresholdLevelType->Text =
    cbStimulatingType->Items->Strings[fmMain->m_nPeakingThresholdLevelTypeIndex];
  cbPeakingThresholdLevelFixed->Text = IntToStr(fmMain->m_pPeakingThresholdLevelArray[1]);
  cbPeakingThresholdLevelFloat->Text = IntToStr(fmMain->m_pPeakingThresholdLevelArray[2]);
  // Patterning
  cbPatterningPeakType->Text =
    cbPatterningPeakType->Items->Strings[fmMain->m_nPatterningPeakParamIndex];
  cbPatterningPeakParamMin->Text = IntToStr(fmMain->m_pPatterningPeakParamArray[0]);
  cbPatterningPeakParamMax->Text = IntToStr(fmMain->m_pPatterningPeakParamArray[1]);
  cbPatterningPeakParamSpace->Text = IntToStr(fmMain->m_pPatterningPeakParamArray[2]);
  // Training
  cbTrainingMode->Text = cbTrainingMode->Items->Strings[fmMain->m_nTrainingModeIndex];
  cbTrainingDuration->Text = IntToStr(fmMain->m_nTrainingDuration);
  // Stimulating
  cbStimulatingType->Text = cbStimulatingType->Items->Strings[fmMain->m_nStimulatingTypeIndex];
  cbStimulatingDuration->Text = IntToStr(fmMain->m_nStimulatingDuration);
  cbStimulatingIntensity->Items->Clear();
  cbStimulatingIntensity->Items->Add(IntToStr(fmMain->m_pStimulatingIntensityArray[0]));
  cbStimulatingIntensity->Items->Add(IntToStr(fmMain->m_pStimulatingIntensityArray[1]));
  cbStimulatingIntensity->Items->Add(IntToStr(fmMain->m_pStimulatingIntensityArray[2]));
  cbStimulatingIntensity->Items->Add(IntToStr(fmMain->m_pStimulatingIntensityArray[3]));
  cbStimulatingIntensity->Items->Add(IntToStr(fmMain->m_pStimulatingIntensityArray[4]));
  cbStimulatingIntensity->Text = cbStimulatingIntensity->Items->Strings[fmMain->m_nStimulatingIntensityIndex];
  cbStimulatingShift->Items->Clear();
  cbStimulatingShift->Items->Add(IntToStr(fmMain->m_pStimulatingShiftArray[0]));
  cbStimulatingShift->Items->Add(IntToStr(fmMain->m_pStimulatingShiftArray[1]));
  cbStimulatingShift->Items->Add(IntToStr(fmMain->m_pStimulatingShiftArray[2]));
  cbStimulatingShift->Items->Add(IntToStr(fmMain->m_pStimulatingShiftArray[3]));
  cbStimulatingShift->Items->Add(IntToStr(fmMain->m_pStimulatingShiftArray[4]));
  cbStimulatingShift->Text = cbStimulatingShift->Items->Strings[fmMain->m_nStimulatingShiftIndex];
  cbStimulatingVideoSet->Text = IntToStr(fmMain->m_nStimulatingVideoSet);
  cbStimulatingAudioSet->Text = IntToStr(fmMain->m_nStimulatingAudioSet);
  cbStimulatingMode3AlternativeIntensity->Text =
  	cbStimulatingMode3AlternativeIntensity->Items->Strings[fmMain->m_nStimulatingMode3AlternativeIntensityIndex];
  cbStimulatingMode4AlternativeShift->Text =
  	cbStimulatingMode4AlternativeShift->Items->Strings[fmMain->m_nStimulatingMode4AlternativeShiftIndex];
  cbStimulatingMode5StimulusPeriod->Text = IntToStr(fmMain->m_nStimulatingMode5StimulusPeriod);
  cbStimulatingMode6NStimulusPeriod->Text = IntToStr(fmMain->m_nStimulatingMode6NStimulusPeriod);
  cbStimulatingMode6NStimulationTime->Text = IntToStr(fmMain->m_nStimulatingMode6NStimulationTime);
  cbStimulatingMode6NStimulationMask->Text =
    cbStimulatingMode6NStimulationMask->Items->Strings[fmMain->m_nStimulatingMode6NStimulationMaskIndex];
  cbStimulatingMode7CycleTime->Text = IntToStr(fmMain->m_nStimulatingMode7CycleTime);
  cbStimulatingMode7Modulation->Text =
  	cbStimulatingMode7Modulation->Items->Strings[fmMain->m_nStimulatingMode7ModulationIndex];
  cbStimulatingMode8StimulusPeriod->Text = IntToStr(fmMain->m_nStimulatingMode8StimulusPeriod);
  cbStimulatingMode8ParadigmType->Text =
  	cbStimulatingMode8ParadigmType->Items->Strings[fmMain->m_nStimulatingMode8ParadigmTypeIndex];
  cbStimulatingMode9ParadigmType->Text =
  	cbStimulatingMode9ParadigmType->Items->Strings[fmMain->m_nStimulatingMode9ParadigmTypeIndex];
  cbStimulatingMode9StimulusNumber->Text = IntToStr(fmMain->m_nStimulatingMode9StimulusNumber);
  cbStimulatingMode9StimulusPeriod->Text = IntToStr(fmMain->m_nStimulatingMode9StimulusPeriod);
  cbStimulatingMode10ParadigmType->Text =
  	cbStimulatingMode10ParadigmType->Items->Strings[fmMain->m_nStimulatingMode10ParadigmTypeIndex];
  cbStimulatingMode10ShockType->Text =
  	cbStimulatingMode10ShockType->Items->Strings[fmMain->m_nStimulatingMode10ShockTypeIndex];
  cbStimulatingMode10AnalysisTime->Text = IntToStr(fmMain->m_nStimulatingMode10AnalysisTime);
  // Plot
  cbPlotWidth->Text = IntToStr(fmMain->m_nPlotWidth);
  cbPlotHeight->Text = IntToStr(fmMain->m_nPlotHeight * 3);
  cbPlotXScale->Text = IntToStr(fmMain->m_nPlotXScale);
  cbPlotYScale->Text = IntToStr(fmMain->m_nPlotYScale);
  // Port
  cbMiscellaneousPort->Text = fmMain->m_aMiscellaneousPort;
  // Output file name
  edOutputFileName->Text = fmMain->m_aOutputFileName;
  // Input file name
  edInputFileName->Text = fmMain->m_aInputFileName;
  
  // Confirm apply
  fmMain->m_bSettingsApplied = false;
	// Close settings window
	fmSettings->Close();
  // Clear plot
  fmMain->blPlot->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfmSettings::cbPortChange(TObject *Sender)
{
  CheckPort(cbMiscellaneousPort->Text);
}
//---------------------------------------------------------------------------
void __fastcall TfmSettings::pcStimulatingModeChange(TObject *Sender)
{
  if (fmMain->m_nOperatingModeIndex == 0 || fmMain->m_nOperatingModeIndex == 1)
  {
    fmMain->m_nTrainingModeIndex = pcStimulatingMode->ActivePageIndex;
    EnableItemsForTrainingMode();
  }
}
//---------------------------------------------------------------------------
void __fastcall TfmSettings::cbPeakingThresholdLevelTypeChange(
      TObject *Sender)
{
  int nThresholdLevelTypeIndex =
    cbPeakingThresholdLevelType->Items->IndexOf(cbPeakingThresholdLevelType->Text);

  stPeakingThresholdLevelFixed->Enabled = false;
  cbPeakingThresholdLevelFixed->Enabled = false;
  stPeakingThresholdLevelFloat->Enabled = false;
  cbPeakingThresholdLevelFloat->Enabled = false;
  stPeakingMeanLongWindowLength->Enabled = false;
  cbPeakingMeanLongWindowLength->Enabled = false;
  if (nThresholdLevelTypeIndex == 0)
  {
    stPeakingThresholdLevelFloat->Enabled = true;
    cbPeakingThresholdLevelFloat->Enabled = true;
    stPeakingMeanLongWindowLength->Enabled = true;
    cbPeakingMeanLongWindowLength->Enabled = true;

  }
  if (nThresholdLevelTypeIndex == 1)
  {
    stPeakingThresholdLevelFixed->Enabled = true;
    cbPeakingThresholdLevelFixed->Enabled = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfmSettings::cbPeakingCommandParameterChange(
      TObject *Sender)
{
  int nPeakingCommandParameterIndex =
    cbPeakingCommandParameter->Items->IndexOf(cbPeakingCommandParameter->Text);

  stPeakingMeanShortWindowLength->Enabled = false;
  cbPeakingMeanShortWindowLength->Enabled = false;
  if (nPeakingCommandParameterIndex == 1)
  {
    stPeakingMeanShortWindowLength->Enabled = true;
    cbPeakingMeanShortWindowLength->Enabled = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfmSettings::sbSoundFileNameClick(TObject *Sender)
{
  if (!dlgOpenSoundFile->Execute())
  	return;

  // Check sound file name
  if (cbSoundType->Text == "Begin")
  {
    fmMain->m_aSoundBeginFileName = dlgOpenSoundFile->FileName;
    edSoundFileName->Text = GetShortFileName(fmMain->m_aSoundBeginFileName);
  }
  else if (cbSoundType->Text == "Relax")
  {
    fmMain->m_aSoundRelaxFileName = dlgOpenSoundFile->FileName;
    edSoundFileName->Text = GetShortFileName(fmMain->m_aSoundRelaxFileName);
  }
  else if (cbSoundType->Text == "Shock")
  {
    fmMain->m_aSoundShockFileName = dlgOpenSoundFile->FileName;
    edSoundFileName->Text = GetShortFileName(fmMain->m_aSoundShockFileName);
  }
}
//---------------------------------------------------------------------------
void __fastcall TfmSettings::cbSoundTypeChange(TObject *Sender)
{
  // Check sound file name
  if (cbSoundType->Text == "Begin")
  {
    edSoundFileName->Text = GetShortFileName(fmMain->m_aSoundBeginFileName);
  }
  else if (cbSoundType->Text == "Relax")
  {
    edSoundFileName->Text = GetShortFileName(fmMain->m_aSoundRelaxFileName);
  }
  else if (cbSoundType->Text == "Shock")
  {
    edSoundFileName->Text = GetShortFileName(fmMain->m_aSoundShockFileName);
  }
}
//---------------------------------------------------------------------------
void __fastcall TfmSettings::sbSoundTestClick(TObject *Sender)
{
  // Check sound file name
  if (cbSoundType->Text == "Begin")
  {
    PlaySound(fmMain->m_aSoundBeginFileName.c_str(), 0, SND_ASYNC);
  }
  else if (cbSoundType->Text == "Relax")
  {
    PlaySound(fmMain->m_aSoundRelaxFileName.c_str(), 0, SND_ASYNC);
  }
  else if (cbSoundType->Text == "Shock")
  {
    PlaySound(fmMain->m_aSoundShockFileName.c_str(), 0, SND_ASYNC);
  }
}
//---------------------------------------------------------------------------



