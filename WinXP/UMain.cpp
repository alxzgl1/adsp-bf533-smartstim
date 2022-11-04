//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "UMain.h"
#include "UConnection.h"
#include "USettings.h"
#include "USpectrum.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmMain *fmMain;
TConnection *tdConnection;
//---------------------------------------------------------------------------
__fastcall TfmMain::TfmMain(TComponent* Owner)
	: TForm(Owner)
{
}
//***************************************************************************
// Events handlers
//***************************************************************************
void __fastcall TfmMain::FormCreate(TObject *Sender)
{
	// Version
  m_aVersion = "2.22 (20090803)";
	// Init const visualization params
  m_nCursorWidth 	= 3;
	m_nPlotTop  = blPlot->Top + 1;
	m_nPlotLeft = blPlot->Left + 1;
  m_nADCSize = 4096; // 12 bit

  /* Init default params */
  m_nOperatingModeIndex = 0; // Online Processing
	// Digitizing
  m_nSampleRate = 128;
  m_nAmpGain = 6;
  m_nAmpGainIndex = 60000;
  m_nLoFreqIndex = 0;
  m_nHiFreqIndex = 1;
  // Processing
  m_nMiscellaneousFilterTypeIndex = 0;
  // Peaking
  m_nPeakingDeadTime = 40;
  m_nPeakingCommandParameterIndex = 0;
  m_nPeakingMeanShortWindowLength = 512;
  m_nPeakingMeanLongWindowLength = 4096;
  m_nPeakingThresholdLevelTypeIndex = 0;
  m_nPeakingThresholdLevelIndex = 0;
  m_pPeakingThresholdLevelArray[0] = 64;   // Noise level
  m_pPeakingThresholdLevelArray[1] = 128;  // Fixed level
  m_pPeakingThresholdLevelArray[2] = 144;  // Float level
  m_pPeakingThresholdLevelArray[3] = 104;  // Float level min
  m_pPeakingThresholdLevelArray[4] = 204;  // Float level max
  // Patterning
  m_nPatterningPeakParamIndex = 0;
  m_pPatterningPeakParamArray[0] = 5;   // Min number of peak
  m_pPatterningPeakParamArray[1] = 10;  // Max number of peak
  m_pPatterningPeakParamArray[2] = 144; // Space between peaks
  // Training
  m_nTrainingDuration = 1;
  m_nTrainingDurationRatio = 64;
  m_nTrainingModeIndex = 0;
  // Stimulating
  m_nStimulatingTypeIndex = 0;
  m_nStimulatingDuration = 5;
  m_nStimulatingIntensityIndex = 3;
  m_pStimulatingIntensityArray[0] = 1;
  m_pStimulatingIntensityArray[1] = 2;
  m_pStimulatingIntensityArray[2] = 3;
  m_pStimulatingIntensityArray[3] = 4;
  m_pStimulatingIntensityArray[4] = 5;
  m_nStimulatingShiftIndex = 1;
  m_pStimulatingShiftArray[0] = 0;
  m_pStimulatingShiftArray[1] = 8;
  m_pStimulatingShiftArray[2] = 16;
  m_pStimulatingShiftArray[3] = 32;
  m_pStimulatingShiftArray[4] = 64;
  m_nStimulatingMode3AlternativeIntensityIndex = 2;
  m_nStimulatingMode4AlternativeShiftIndex = 2;
  m_nStimulatingMode5StimulusPeriod = 104;
  m_nStimulatingMode6NStimulusPeriod = 104;
  m_nStimulatingMode6NStimulationTime = 4;
  m_nStimulatingMode6NStimulationMaskIndex = 0;
  m_nStimulatingMode7CycleTime = 2;
  m_nStimulatingMode7ModulationIndex = 0;
  m_nStimulatingMode8StimulusPeriod = 104;
  m_nStimulatingMode8ParadigmTypeIndex = 0;
  m_nStimulatingMode9ParadigmTypeIndex = 0;
  m_nStimulatingMode9StimulusNumber = 5;
	m_nStimulatingMode9StimulusPeriod = 104;
	m_nStimulatingMode10ParadigmTypeIndex = 0;
	m_nStimulatingMode10ShockTypeIndex = 0;
	m_nStimulatingMode10AnalysisTime = 5;
  // Plot
  m_nPlotWidth = 640;
  m_nPlotHeight = 128;
  m_nPlotXScale = 2;
  m_nPlotYScale = 2;
  // Port
  m_aMiscellaneousPort = "COM3";
  // Output file name
  m_aOutputFileName = "output.txt";
  // Input file name
  m_aInputFileName = "input.txt";
  // Background color
  m_nBackgroundColor = 0xFFFFFF;

  /* Set configuration from ss.ini */
  TStringList *List = new TStringList();
  try
  {
    List->LoadFromFile("SmartStim.ini");
    // [OPERATING_MODE_INDEX]
    m_nOperatingModeIndex = StrToInt(List->Strings[1]);
  	// [SAMPLE_RATE]
		m_nSampleRate = StrToInt(List->Strings[3]);
  	// [AMP_GAIN_INDEX]
		m_nAmpGainIndex = StrToInt(List->Strings[5]);
		// [LOW_FREQ_INDEX]
    m_nLoFreqIndex = StrToInt(List->Strings[7]);
		// [HIGH_FREQ_INDEX]
    m_nHiFreqIndex = StrToInt(List->Strings[9]);
		// [FILTERING_TYPE_INDEX]
		m_nMiscellaneousFilterTypeIndex = StrToInt(List->Strings[11]);
    // [PEAKING_DEAD_TIME]
    m_nPeakingDeadTime = StrToInt(List->Strings[13]);
    // [PEAKING_COMMAND_PARAMETER_INDEX]
    m_nPeakingCommandParameterIndex = StrToInt(List->Strings[15]);
    // [PEAKING_MEAN_SHORT_WINDOW_LENGTH]
    m_nPeakingMeanShortWindowLength = StrToInt(List->Strings[17]);
    // [PEAKING_MEAN_LONG_WINDOW_LENGTH]
    m_nPeakingMeanLongWindowLength = StrToInt(List->Strings[19]);
    // [PEAKING_THRESHOLD_LEVEL_INDEX]
    m_nPeakingThresholdLevelIndex = StrToInt(List->Strings[21]);
    // [PEAKING_THRESHOLD_LEVEL_NOISE]
    m_pPeakingThresholdLevelArray[0] = StrToInt(List->Strings[23]);
    // [PEAKING_THRESHOLD_LEVEL_TYPE_INDEX]
    m_nPeakingThresholdLevelTypeIndex = StrToInt(List->Strings[25]);
    // [PEAKING_THRESHOLD_LEVEL_FIXED]
    m_pPeakingThresholdLevelArray[1] = StrToInt(List->Strings[27]);
    // [PEAKING_THRESHOLD_LEVEL_FLOAT]
    m_pPeakingThresholdLevelArray[2] = StrToInt(List->Strings[29]);
    // [PEAKING_THRESHOLD_LEVEL_FLOAT_MIN]
    m_pPeakingThresholdLevelArray[3] = StrToInt(List->Strings[31]);
    // [PEAKING_THRESHOLD_LEVEL_FLOAT_MAX]
    m_pPeakingThresholdLevelArray[4] = StrToInt(List->Strings[33]);
    // [PATTERNING_PARAM_INDEX]
    m_nPatterningPeakParamIndex = StrToInt(List->Strings[35]);
    // [PATTERNING_PEAK_MIN]
    m_pPatterningPeakParamArray[0] = StrToInt(List->Strings[37]);
    // [PATTERNING_PEAK_MAX]
    m_pPatterningPeakParamArray[1] = StrToInt(List->Strings[39]);
    // [PATTERNING_PEAK_SPACE]
    m_pPatterningPeakParamArray[2] = StrToInt(List->Strings[41]);
    // [TRAINING_MODE_INDEX]
    m_nTrainingModeIndex = StrToInt(List->Strings[43]) - 1;
    // [TRAINING_DURATION]
    m_nTrainingDuration = StrToInt(List->Strings[45]);
    // [TRAINING_DURATION_RATIO]
    m_nTrainingDurationRatio = StrToInt(List->Strings[47]);
		// [STIMULATING_TYPE_INDEX]
    m_nStimulatingTypeIndex = StrToInt(List->Strings[49]);
    // [STIMULATING_DURATION]
    m_nStimulatingDuration = StrToInt(List->Strings[51]);
		// [STIMULATING_INTENSITY_INDEX]
    m_nStimulatingIntensityIndex = StrToInt(List->Strings[53]);
    // [STIMULATING_INTENSITY_ARRAY]
    m_pStimulatingIntensityArray[0] = StrToInt(List->Strings[55]);
    m_pStimulatingIntensityArray[1] = StrToInt(List->Strings[56]);
    m_pStimulatingIntensityArray[2] = StrToInt(List->Strings[57]);
    m_pStimulatingIntensityArray[3] = StrToInt(List->Strings[58]);
    m_pStimulatingIntensityArray[4] = StrToInt(List->Strings[59]);
    // [STIMULATING_SHIFT_INDEX]
    m_nStimulatingShiftIndex = StrToInt(List->Strings[61]);
    // [STIMULATING_SHIFT_ARRAY]
    m_pStimulatingShiftArray[0] = StrToInt(List->Strings[63]);
    m_pStimulatingShiftArray[1] = StrToInt(List->Strings[64]);
    m_pStimulatingShiftArray[2] = StrToInt(List->Strings[65]);
    m_pStimulatingShiftArray[3] = StrToInt(List->Strings[66]);
    m_pStimulatingShiftArray[4] = StrToInt(List->Strings[67]);
    // [STIMULATING_VIDEO_SET]
    m_nStimulatingVideoSet = StrToInt(List->Strings[69]);
    // [STIMULATING_AUDIO_SET]
    m_nStimulatingAudioSet = StrToInt(List->Strings[71]);
    // [STIMULATING_MODE3_ALTERNATIVE_INTENSITY_INDEX]
    m_nStimulatingMode3AlternativeIntensityIndex = StrToInt(List->Strings[73]);
    // [STIMULATING_MODE4_ALTERNATIVE_SHIFT_INDEX]
    m_nStimulatingMode4AlternativeShiftIndex = StrToInt(List->Strings[75]);
    // [STIMULATING_MODE5_STIMULUS_PERIOD]
    m_nStimulatingMode5StimulusPeriod = StrToInt(List->Strings[77]);
   	// [STIMULATING_MODE6N_STIMULUS_PERIOD]
    m_nStimulatingMode6NStimulusPeriod = StrToInt(List->Strings[79]);
    // [STIMULATING_MODE6N_STIMULATION_TIME]
    m_nStimulatingMode6NStimulationTime = StrToInt(List->Strings[81]);
    // [STIMULATING_MODE6N_STIMULATION_MASK]
    m_nStimulatingMode6NStimulationMaskIndex = StrToInt(List->Strings[83]);
    // [STIMULATING_MODE7_CYCLE_TIME]
    m_nStimulatingMode7CycleTime = StrToInt(List->Strings[85]);
    // [STIMULATING_MODE7_MODULATION_INDEX]
    m_nStimulatingMode7ModulationIndex = StrToInt(List->Strings[87]);
    // [STIMULATING_MODE8_STIMULUS_PERIOD]
    m_nStimulatingMode8StimulusPeriod = StrToInt(List->Strings[89]);
    // [STIMULATING_MODE8_PARADIGM_TYPE_INDEX]
    m_nStimulatingMode8ParadigmTypeIndex = StrToInt(List->Strings[91]);
    // [STIMULATING_MODE9_PARADIGM_TYPE_INDEX]
    m_nStimulatingMode9ParadigmTypeIndex = StrToInt(List->Strings[93]);
    // [STIMULATING_MODE9_STIMULUS_NUMBER]
    m_nStimulatingMode9StimulusNumber = StrToInt(List->Strings[95]);
    // [STIMULATING_MODE9_STIMULUS_PERIOD]
    m_nStimulatingMode9StimulusPeriod = StrToInt(List->Strings[97]);
    // [STIMULATING_MODE10_PARADIGM_TYPE_INDEX]
    m_nStimulatingMode10ParadigmTypeIndex = StrToInt(List->Strings[99]);
    // [STIMULATING_MODE10_SHOCK_TYPE_INDEX]
    m_nStimulatingMode10ShockTypeIndex = StrToInt(List->Strings[101]);
    // [STIMULATING_MODE10_ANALYSIS_TIME]
    m_nStimulatingMode10AnalysisTime = StrToInt(List->Strings[103]);
		// [PLOT_WIDTH]
    m_nPlotWidth = StrToInt(List->Strings[105]);
		// [PLOT_HEIGHT]
    m_nPlotHeight = StrToInt(List->Strings[107]) / 3;
		// [PLOT_XSCALE]
    m_nPlotXScale = StrToInt(List->Strings[109]);
		// [PLOT_YSCALE]
    m_nPlotYScale = StrToInt(List->Strings[111]);
    // [PORT]
    m_aMiscellaneousPort = List->Strings[113];
		// [OUTPUT_FILE_NAME]
    m_aOutputFileName = List->Strings[115];
		// [INPUT_FILE_NAME]
		m_aInputFileName = List->Strings[117];
    // [SOUND_BEGIN_FILE_NAME]
    m_aSoundBeginFileName = List->Strings[119];
    // [SOUND_RELAX_FILE_NAME]
    m_aSoundRelaxFileName = List->Strings[121];
    // [SOUND_SHOCK_FILE_NAME]
    m_aSoundShockFileName = List->Strings[123];
    // [BACKGROUND_COLOR]
    m_nBackgroundColor = StrToInt(List->Strings[125]);
  }
  catch (Exception &exception)
  {
    MessageBox(NULL, exception.Message.c_str(), "SmartStim.ini",
    	MB_OK | MB_ICONWARNING);
  }

  /* Init data params */
  m_nDataSize = 4;
  m_nBlockSize = m_nPlotWidth / (m_nDataSize * m_nPlotXScale);

  // Init training time
  m_nTrainingTime = m_nTrainingDuration * m_nTrainingDurationRatio;

  // Mode dependent value
  m_nModeDependentValue = 0;

  // File format
  m_nFileFormatHeaderLength = 42;
  m_nFileFormatDataLength = 7;

  // Init plot apply settings
  m_bSettingsApplied = false;

  // Init online control
  m_nOnlineControl = 0;
  m_nOnlineCorrectionMode10 = 2;

  // Init started
  m_bStarted = false;

  // Init can update plot
  m_bPlotUpdateEnabled = false;

  // Show version
  fmMain->Caption = "SmartStim v" + m_aVersion;

  // Show stimulation type
  ShowStimulationType();

  /* Init control items */
  EnableControlItems(true, false, false);
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::bnStopClick(TObject *Sender)
{
  // Stop
  m_bStarted = false;

  // Check mode
  switch (m_nOperatingModeIndex)
  {
  	case 0: // Online Processing
    {
  		tdConnection->Terminate();
      Sleep(100);
    	break;
    }
    case 1: // Offline Processing
    {
    	tdConnection->Terminate();
      Sleep(100);
    	break;
    }
    case 2: // Offline Viewing
    {
    	// Disable scroll bar
    	m_bStopXScroll = true;
    	sbPlotXScroll->Position = 0;
    	sbPlotXScroll->Enabled = false;
      // Disable plot update
      m_bPlotUpdateEnabled = false;
  		// Delete m_pListFileMarkerPositions
  		if (m_pListFileMarkerPositions)
  			delete [] m_pListFileMarkerPositions;
    	// Close m_pOfflineViewingStream
  		fclose(m_pOfflineViewingStream);
      // Delete EEG objects
  		DeleteEEGObjects();
  		// Delete graphic objects
  		DeleteGraphicObjects();
  		// Enable control items
  		EnableControlItems(true, false, false);
    	break;
    }
  }
}
//---------------------------------------------------------------------------
//***************************************************************************
// Functions
//***************************************************************************
void __fastcall TfmMain::CreateGraphicObjects()
{
	// Init graphic objects
  m_pnMarker = CreatePen(PS_SOLID, 1, clLtGray);
  m_pnAxis = CreatePen(PS_SOLID, 1, clLtGray);
  m_pnEEG = CreatePen(PS_SOLID, 1, clBlack);
  m_pnLevelA = CreatePen(PS_SOLID, 1, clMaroon);
  m_pnLevelB = CreatePen(PS_SOLID, 1, clPurple);
  m_pnShift = CreatePen(PS_SOLID, 1, clFuchsia);
  m_pnClear = CreatePen(PS_SOLID, 1, TColor(m_nBackgroundColor));
  m_brPlot = CreateSolidBrush(TColor(m_nBackgroundColor));
  m_brCursor = CreateSolidBrush(TColor(m_nBackgroundColor));
  m_brClear = CreateSolidBrush(TColor(m_nBackgroundColor));
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::DeleteGraphicObjects()
{
  DeleteObject(m_pnMarker);
  DeleteObject(m_pnAxis);
  DeleteObject(m_pnEEG);
  DeleteObject(m_pnLevelA);
  DeleteObject(m_pnLevelB);
  DeleteObject(m_pnShift);
  DeleteObject(m_pnClear);
  DeleteObject(m_brPlot);
  DeleteObject(m_brCursor);
  DeleteObject(m_brClear);
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::DeleteEEGObjects()
{
	// Delete data arrays
  delete [] m_pREEG;
  delete [] m_pFEEG;
  delete [] m_pCEEG;
  delete [] m_pTNEEG;
  delete [] m_pTVEEG;
  delete [] m_pSEEG;
  delete [] m_pMDEEG;
  // Delete POINTS arrays
  delete [] m_ptREEG;
  delete [] m_ptFEEG;
  delete [] m_ptCEEG;
  delete [] m_ptTNEEG;
  delete [] m_ptTVEEG;
  delete [] m_ptSEEG;
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::DrawPlot()
{
	// Objects for drawing plot
	RECT rcPlot;
  POINT ptMarkerR4x4[2];
  POINT ptMarkerR3x4[2];
  POINT ptMarkerR2x4[2];
  POINT ptMarkerR1x4[2];
  POINT ptMarkerF4x4[2];
  POINT ptMarkerF3x4[2];
  POINT ptMarkerF2x4[2];
  POINT ptMarkerF1x4[2];
  POINT ptMarkerP4x4[2];
  POINT ptMarkerP3x4[2];
  POINT ptMarkerP2x4[2];
  POINT ptMarkerP1x4[2];
  POINT ptAxisXEEG1[2];
  POINT ptAxisXEEG2[2];
  POINT ptAxisXEEG3[2];

  // Set HDC
  m_dcPlot = fmMain->Canvas->Handle;

  /*** Init shapes ***/
  /* Init plot */
  rcPlot.left = blPlot->Left + 1;
  rcPlot.top = blPlot->Top + 1;
  rcPlot.right = m_nPlotWidth + m_nPlotLeft;
  rcPlot.bottom = 3 * m_nPlotHeight + m_nPlotTop + (5 + 1) + 1;

  /* Init X axis */
  // Marker line R
  ptMarkerR4x4[0].x = rcPlot.left;
  ptMarkerR4x4[1].x = rcPlot.right;
  ptMarkerR3x4[0].x = rcPlot.left;
  ptMarkerR3x4[1].x = rcPlot.right;
  ptMarkerR2x4[0].x = rcPlot.left;
  ptMarkerR2x4[1].x = rcPlot.right;
  ptMarkerR1x4[0].x = rcPlot.left;
  ptMarkerR1x4[1].x = rcPlot.right;
  // Marker line F
  ptMarkerF4x4[0].x = rcPlot.left;
  ptMarkerF4x4[1].x = rcPlot.right;
  ptMarkerF3x4[0].x = rcPlot.left;
  ptMarkerF3x4[1].x = rcPlot.right;
  ptMarkerF2x4[0].x = rcPlot.left;
  ptMarkerF2x4[1].x = rcPlot.right;
  ptMarkerF1x4[0].x = rcPlot.left;
  ptMarkerF1x4[1].x = rcPlot.right;
  // Marker line P
  ptMarkerP4x4[0].x = rcPlot.left;
  ptMarkerP4x4[1].x = rcPlot.right;
  ptMarkerP3x4[0].x = rcPlot.left;
  ptMarkerP3x4[1].x = rcPlot.right;
  ptMarkerP2x4[0].x = rcPlot.left;
  ptMarkerP2x4[1].x = rcPlot.right;
  ptMarkerP1x4[0].x = rcPlot.left;
  ptMarkerP1x4[1].x = rcPlot.right;
  // Axis
  ptAxisXEEG1[0].x = rcPlot.left;
  ptAxisXEEG1[1].x = rcPlot.right;
  ptAxisXEEG2[0].x = rcPlot.left;
  ptAxisXEEG2[1].x = rcPlot.right;
  ptAxisXEEG3[0].x = rcPlot.left;
  ptAxisXEEG3[1].x = rcPlot.right;

  /* Check Y axis */
  // Marker R lines
  ptMarkerR4x4[0].y = 0 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 1;
  ptMarkerR4x4[1].y = 0 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 1;
  ptMarkerR3x4[0].y = 1 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 1;
  ptMarkerR3x4[1].y = 1 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 1;
  ptMarkerR2x4[0].y = 2 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 1;
  ptMarkerR2x4[1].y = 2 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 1;
  ptMarkerR1x4[0].y = 3 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 1;
  ptMarkerR1x4[1].y = 3 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 1;
  // Marker F lines
  ptMarkerF4x4[0].y = 8 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 3;
  ptMarkerF4x4[1].y = 8 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 3;
  ptMarkerF3x4[0].y = 9 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 3;
  ptMarkerF3x4[1].y = 9 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 3;
  ptMarkerF2x4[0].y = 10 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 3;
  ptMarkerF2x4[1].y = 10 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 3;
  ptMarkerF1x4[0].y = 11 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 3;
  ptMarkerF1x4[1].y = 11 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 3;
  // Marker P lines
  ptMarkerP4x4[0].y = 16 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 5;
  ptMarkerP4x4[1].y = 16 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 5;
  ptMarkerP3x4[0].y = 17 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 5;
  ptMarkerP3x4[1].y = 17 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 5;
  ptMarkerP2x4[0].y = 18 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 5;
  ptMarkerP2x4[1].y = 18 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 5;
  ptMarkerP1x4[0].y = 19 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 5;
  ptMarkerP1x4[1].y = 19 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 5;

  // Top axis
  ptAxisXEEG1[0].y = 1 * (m_nPlotHeight / 2) + m_nPlotTop + 1;
  ptAxisXEEG1[1].y = 1 * (m_nPlotHeight / 2) + m_nPlotTop + 1;
  // Middle axis
  ptAxisXEEG2[0].y = 3 * (m_nPlotHeight / 2) + m_nPlotTop + 3;
  ptAxisXEEG2[1].y = 3 * (m_nPlotHeight / 2) + m_nPlotTop + 3;
  // Bottom axis
  ptAxisXEEG3[0].y = 5 * (m_nPlotHeight / 2) + m_nPlotTop + 5;
  ptAxisXEEG3[1].y = 5 * (m_nPlotHeight / 2) + m_nPlotTop + 5;

  /*** Draw shapes ***/
  // Try canvas lock
  if (!fmMain->Canvas->TryLock())
  {
    // Lock canvas
    fmMain->Canvas->Lock();

    /* Draw plot */
    SelectObject(m_dcPlot, m_brPlot);
    FillRect(m_dcPlot, &rcPlot, m_brPlot);

    /* Draw axis */
    SelectObject(m_dcPlot, m_pnMarker);
    Polyline(m_dcPlot, ptMarkerR4x4, 2); // Marker R line 4/4
    Polyline(m_dcPlot, ptMarkerR3x4, 2); // Marker R line 3/4
    Polyline(m_dcPlot, ptMarkerR2x4, 2); // Marker R line 2/4
    Polyline(m_dcPlot, ptMarkerR1x4, 2); // Marker R line 1/4
    Polyline(m_dcPlot, ptMarkerF4x4, 2); // Marker F line 4/4
    Polyline(m_dcPlot, ptMarkerF3x4, 2); // Marker F line 3/4
    Polyline(m_dcPlot, ptMarkerF2x4, 2); // Marker F line 2/4
    Polyline(m_dcPlot, ptMarkerF1x4, 2); // Marker F line 1/4
    Polyline(m_dcPlot, ptMarkerP4x4, 2); // Marker P line 4/4
    Polyline(m_dcPlot, ptMarkerP3x4, 2); // Marker P line 3/4
    Polyline(m_dcPlot, ptMarkerP2x4, 2); // Marker P line 2/4
    Polyline(m_dcPlot, ptMarkerP1x4, 2); // Marker P line 1/4
    SelectObject(m_dcPlot, m_pnAxis);
    Polyline(m_dcPlot, ptAxisXEEG1, 2); // Top axis
    Polyline(m_dcPlot, ptAxisXEEG2, 2); // Middle axis
    Polyline(m_dcPlot, ptAxisXEEG3, 2); // Bottom axis

    // Unlock canvas
    fmMain->Canvas->Unlock();
  }
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::DrawData()
{
	/* Objects for drawing plot */
  // Marker R
  POINT ptMarkerR4x4[2];
  POINT ptMarkerR3x4[2];
  POINT ptMarkerR2x4[2];
  POINT ptMarkerR1x4[2];
  // Marker F
  POINT ptMarkerF4x4[2];
  POINT ptMarkerF3x4[2];
  POINT ptMarkerF2x4[2];
  POINT ptMarkerF1x4[2];
  // Marker P
  POINT ptMarkerP4x4[2];
  POINT ptMarkerP3x4[2];
  POINT ptMarkerP2x4[2];
  POINT ptMarkerP1x4[2];
  // Axis
  POINT ptAxisXEEG1[2];
  POINT ptAxisXEEG2[2];
  POINT ptAxisXEEG3[2];
  // Clear
  POINT ptClearLineTop[2];
  POINT ptClearLineBottom[2];
  /* Objects for drawing data */
  RECT rcCursor;
  RECT rcClear;
  // Temp variable
  int i;
  // Amp limitation
  double fREEG, fFEEG, fCEEG, fTNEEG, fTVEEG;

  // Set HDC
  m_dcPlot = fmMain->Canvas->Handle;

  /*** Init shapes ***/
  /* Clear data and cursor */
  rcClear.top = m_nPlotTop + 1;
	rcClear.bottom = 3 * m_nPlotHeight + m_nPlotTop + (5 + 1) + 1;
  rcClear.left = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft;
  rcClear.right = m_nPlotXScale * m_nDataSize * (m_nCountVis + 1) + m_nPlotLeft;

  /* Init markers */
  // Marker R AX
  ptMarkerR4x4[0].x = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft;
  ptMarkerR4x4[1].x = m_nPlotXScale * m_nDataSize * (1 + m_nCountVis)
  	+ m_nPlotLeft;
  ptMarkerR3x4[0].x = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft;
  ptMarkerR3x4[1].x = m_nPlotXScale * m_nDataSize * (1 + m_nCountVis)
  	+ m_nPlotLeft;
  ptMarkerR2x4[0].x = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft;
  ptMarkerR2x4[1].x = m_nPlotXScale * m_nDataSize * (1 + m_nCountVis)
  	+ m_nPlotLeft;
  ptMarkerR1x4[0].x = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft;
  ptMarkerR1x4[1].x = m_nPlotXScale * m_nDataSize * (1 + m_nCountVis)
  	+ m_nPlotLeft;
  // Marker F AX
  ptMarkerF4x4[0].x = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft;
  ptMarkerF4x4[1].x = m_nPlotXScale * m_nDataSize * (1 + m_nCountVis)
  	+ m_nPlotLeft;
  ptMarkerF3x4[0].x = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft;
  ptMarkerF3x4[1].x = m_nPlotXScale * m_nDataSize * (1 + m_nCountVis)
  	+ m_nPlotLeft;
  ptMarkerF2x4[0].x = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft;
  ptMarkerF2x4[1].x = m_nPlotXScale * m_nDataSize * (1 + m_nCountVis)
  	+ m_nPlotLeft;
  ptMarkerF1x4[0].x = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft;
  ptMarkerF1x4[1].x = m_nPlotXScale * m_nDataSize * (1 + m_nCountVis)
  	+ m_nPlotLeft;
  // Marker P AX
  ptMarkerP4x4[0].x = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft;
  ptMarkerP4x4[1].x = m_nPlotXScale * m_nDataSize * (1 + m_nCountVis)
  	+ m_nPlotLeft;
  ptMarkerP3x4[0].x = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft;
  ptMarkerP3x4[1].x = m_nPlotXScale * m_nDataSize * (1 + m_nCountVis)
  	+ m_nPlotLeft;
  ptMarkerP2x4[0].x = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft;
  ptMarkerP2x4[1].x = m_nPlotXScale * m_nDataSize * (1 + m_nCountVis)
  	+ m_nPlotLeft;
  ptMarkerP1x4[0].x = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft;
  ptMarkerP1x4[1].x = m_nPlotXScale * m_nDataSize * (1 + m_nCountVis)
  	+ m_nPlotLeft;
  // Marker R AY
  ptMarkerR4x4[0].y = 0 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 1;
  ptMarkerR4x4[1].y = 0 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 1;
  ptMarkerR3x4[0].y = 1 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 1;
  ptMarkerR3x4[1].y = 1 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 1;
  ptMarkerR2x4[0].y = 2 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 1;
  ptMarkerR2x4[1].y = 2 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 1;
  ptMarkerR1x4[0].y = 3 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 1;
  ptMarkerR1x4[1].y = 3 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 1;
  // Marker F AY
  ptMarkerF4x4[0].y = 8 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 3;
  ptMarkerF4x4[1].y = 8 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 3;
  ptMarkerF3x4[0].y = 9 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 3;
  ptMarkerF3x4[1].y = 9 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 3;
  ptMarkerF2x4[0].y = 10 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 3;
  ptMarkerF2x4[1].y = 10 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 3;
  ptMarkerF1x4[0].y = 11 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 3;
  ptMarkerF1x4[1].y = 11 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 3;
  // Marker P AY
  ptMarkerP4x4[0].y = 16 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 5;
  ptMarkerP4x4[1].y = 16 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 5;
  ptMarkerP3x4[0].y = 17 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 5;
  ptMarkerP3x4[1].y = 17 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 5;
  ptMarkerP2x4[0].y = 18 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 5;
  ptMarkerP2x4[1].y = 18 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 5;
  ptMarkerP1x4[0].y = 19 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 5;
  ptMarkerP1x4[1].y = 19 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop + 5;

  /* Init axis */
  ptAxisXEEG1[0].x = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft;
  ptAxisXEEG1[1].x = m_nPlotXScale * m_nDataSize * (1 + m_nCountVis)
  	+ m_nPlotLeft;
  ptAxisXEEG2[0].x = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft;
  ptAxisXEEG2[1].x = m_nPlotXScale * m_nDataSize * (1 + m_nCountVis)
  	+ m_nPlotLeft;
  ptAxisXEEG3[0].x = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft;
  ptAxisXEEG3[1].x = m_nPlotXScale * m_nDataSize * (1 + m_nCountVis)
  	+ m_nPlotLeft;
 	// Top axis
  ptAxisXEEG1[0].y = 1 * (m_nPlotHeight / 2) + m_nPlotTop + 1;
  ptAxisXEEG1[1].y = 1 * (m_nPlotHeight / 2) + m_nPlotTop + 1;
  // Middle axis
  ptAxisXEEG2[0].y = 3 * (m_nPlotHeight / 2) + m_nPlotTop + 3;
  ptAxisXEEG2[1].y = 3 * (m_nPlotHeight / 2) + m_nPlotTop + 3;
  // Bottom axis
  ptAxisXEEG3[0].y = 5 * (m_nPlotHeight / 2) + m_nPlotTop + 5;
  ptAxisXEEG3[1].y = 5 * (m_nPlotHeight / 2) + m_nPlotTop + 5;

  /* Init cursor */
  rcCursor.top = m_nPlotTop + 1;
  rcCursor.bottom = 3 * m_nPlotHeight + m_nPlotTop + (5 + 1) + 1;
  rcCursor.left = m_nPlotXScale * m_nDataSize * (m_nCountVis + 1)
  	+ m_nPlotLeft;
  if (m_nPlotXScale * m_nDataSize * (m_nCountVis + 1) < m_nPlotWidth)
  {
    rcCursor.right = m_nPlotXScale * m_nDataSize * (m_nCountVis + 1)
    	+ m_nCursorWidth + m_nPlotLeft;
  }
  else
  {
    rcCursor.right = m_nPlotXScale * m_nDataSize * (m_nCountVis + 1)
    	+ m_nPlotLeft;
  }

  /* Init data and delay */
  for (i = 1; i < (m_nDataSize + 1); i++)
  {
  	/* Set X of EEG */
  	// Raw EEG
    m_ptREEG[i].x = m_nPlotXScale * (i + m_nDataSize * m_nCountVis)
    	+ m_nPlotLeft - 1;
    fREEG = ((double)(m_nADCSize - m_nPlotYScale * m_pREEG[i - 1])
    	/ m_nADCSize);
    if (fREEG > 2.0)
    {
    	fREEG = 2.0;
    }
    if (fREEG < 0.0)
    {
    	fREEG = 0.0;
    }
    // Filtering EEG
    m_ptFEEG[i].x = m_nPlotXScale * (i + m_nDataSize * m_nCountVis)
    	+ m_nPlotLeft - 1;
    fFEEG = ((double)(m_nADCSize - m_nPlotYScale * m_pFEEG[i - 1])
    	/ m_nADCSize);
    if (fFEEG > 2.0)
    {
    	fFEEG = 2.0;
    }
    if (fFEEG < 0.0)
    {
    	fFEEG = 0.0;
    }
    // Command EEG
    m_ptCEEG[i].x = m_nPlotXScale * (i + m_nDataSize * m_nCountVis)
    	+ m_nPlotLeft - 1;
    fCEEG = ((double)(m_nADCSize - m_nPlotYScale * m_pCEEG[i - 1])
    	/ m_nADCSize);
    if (fCEEG < 0.0)
    {
    	fCEEG = 0.0;
    }
    // Noise for EEG
    m_ptTNEEG[i].x = m_nPlotXScale * (i + m_nDataSize * m_nCountVis)
    	+ m_nPlotLeft - 1;
    fTNEEG = ((double)(m_nADCSize - m_nPlotYScale * m_pTNEEG[i - 1])
    	/ m_nADCSize);
    if (fTNEEG < 0.0)
    {
    	fTNEEG = 0.0;
    }
    // Threshold level for EEG
    m_ptTVEEG[i].x = m_nPlotXScale * (i + m_nDataSize * m_nCountVis)
    	+ m_nPlotLeft - 1;
    fTVEEG = ((double)(m_nADCSize - m_nPlotYScale * m_pTVEEG[i - 1])
    	/ m_nADCSize);
    if (fTVEEG < 0.0)
    {
    	fTVEEG = 0.0;
    }

    /* Set Y of EEG */
    // Raw EEG
    m_ptREEG[i].y = fREEG * (m_nPlotHeight / 2) + m_nPlotTop + 1;
    // Filtering EEG
    m_ptFEEG[i].y = fFEEG * (m_nPlotHeight / 2) + 2 * (m_nPlotHeight / 2)
      + m_nPlotTop + 3;
    //  Command EEG
    m_ptCEEG[i].y = fCEEG * (m_nPlotHeight / 2) + 4 * (m_nPlotHeight / 2)
      + m_nPlotTop + 5;
    // Noise for EEG
    m_ptTNEEG[i].y = fTNEEG * (m_nPlotHeight / 2) + 2 * (m_nPlotHeight / 2)
      + m_nPlotTop + 3;
    // Threshold level for EEG
    m_ptTVEEG[i].y = fTVEEG * (m_nPlotHeight / 2) + 4 * (m_nPlotHeight / 2)
      + m_nPlotTop + 5;
    // Set delaying EEG
    m_ptSEEG[2 * (i - 1)].x = m_nPlotXScale * (i + m_nDataSize * m_nCountVis)
    	+ m_nPlotLeft - 1;
    m_ptSEEG[2 * (i - 1) + 1].x = m_nPlotXScale * (i + m_nDataSize * m_nCountVis)
    	+ m_nPlotLeft - 1;
    m_ptSEEG[2 * (i - 1)].y = (3 * m_nPlotHeight + 5 + 1)
    	* m_nStateVis + m_nPlotTop;
    m_nStateVis = m_nStateVis ^ m_pSEEG[i - 1];
    m_ptSEEG[2 * (i - 1) + 1].y = (3 * m_nPlotHeight + 5 + 1)
    	* m_nStateVis + m_nPlotTop;
  }

  // Check m_nCountVis for draw begin point
  if (m_nCountVis == 0)
  {
  	m_ptREEG[0].x = m_ptREEG[1].x - m_nPlotXScale + 1;
  	m_ptREEG[0].y = m_nPrevRY0;
  	m_ptFEEG[0].x = m_ptFEEG[1].x - m_nPlotXScale + 1;
  	m_ptFEEG[0].y = m_nPrevFY0;
  	m_ptCEEG[0].x = m_ptCEEG[1].x - m_nPlotXScale + 1;
  	m_ptCEEG[0].y = m_nPrevCY0;
    m_ptTNEEG[0].x = m_ptTNEEG[1].x - m_nPlotXScale + 1;
  	m_ptTNEEG[0].y = m_nPrevTNY0;
  	m_ptTVEEG[0].x = m_ptTVEEG[1].x - m_nPlotXScale + 1;
  	m_ptTVEEG[0].y = m_nPrevTVY0;
  	m_nPrevRY0 = m_ptREEG[m_nDataSize].y;
    m_nPrevFY0 = m_ptFEEG[m_nDataSize].y;
    m_nPrevCY0 = m_ptCEEG[m_nDataSize].y;
    m_nPrevTNY0 = m_ptTNEEG[m_nDataSize].y;
    m_nPrevTVY0 = m_ptTVEEG[m_nDataSize].y;
  }
  else
  {
  	m_ptREEG[0].x = m_nPrevRX;
  	m_ptREEG[0].y = m_nPrevRY;
  	m_ptFEEG[0].x = m_nPrevFX;
  	m_ptFEEG[0].y = m_nPrevFY;
  	m_ptCEEG[0].x = m_nPrevCX;
  	m_ptCEEG[0].y = m_nPrevCY;
    m_ptTNEEG[0].x = m_nPrevTNX;
  	m_ptTNEEG[0].y = m_nPrevTNY;
  	m_ptTVEEG[0].x = m_nPrevTVX;
  	m_ptTVEEG[0].y = m_nPrevTVY;
  }

  /* Init prev */
  m_nPrevRX = m_ptREEG[m_nDataSize].x;
  m_nPrevRY = m_ptREEG[m_nDataSize].y;
  m_nPrevFX = m_ptFEEG[m_nDataSize].x;
  m_nPrevFY = m_ptFEEG[m_nDataSize].y;
  m_nPrevCX = m_ptCEEG[m_nDataSize].x;
  m_nPrevCY = m_ptCEEG[m_nDataSize].y;
  m_nPrevTNX = m_ptTNEEG[m_nDataSize].x;
  m_nPrevTNY = m_ptTNEEG[m_nDataSize].y;
  m_nPrevTVX = m_ptTVEEG[m_nDataSize].x;
  m_nPrevTVY = m_ptTVEEG[m_nDataSize].y;

  /* Init clear line */
  ptClearLineTop[0].x = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft
  	+ m_nCountVis * -1;
  ptClearLineTop[1].x = m_nPlotXScale * m_nDataSize * (m_nCountVis + 1)
  	+ m_nPlotLeft;
  ptClearLineBottom[0].x = m_nPlotXScale * m_nDataSize * m_nCountVis + m_nPlotLeft
  	+ m_nCountVis * -1;
  ptClearLineBottom[1].x = m_nPlotXScale * m_nDataSize * (m_nCountVis + 1)
  	+ m_nPlotLeft;
  // Top clear line
  ptClearLineTop[0].y = m_nPlotTop;
  ptClearLineTop[1].y = m_nPlotTop;
  // Bottom clear line
  ptClearLineBottom[0].y = 3 * m_nPlotHeight + m_nPlotTop + 5 + 1;
  ptClearLineBottom[1].y = 3 * m_nPlotHeight + m_nPlotTop + 5 + 1;

  /*** Draw shapes ***/
  // Try canvas lock
  if (!fmMain->Canvas->TryLock())
  {
    /* Lock canvas */
    fmMain->Canvas->Lock();

    /* Clear data and cursor */
	  SelectObject(m_dcPlot, m_brClear);
	  FillRect(m_dcPlot, &rcClear, m_brClear);

    /* Draw markers */
    SelectObject(m_dcPlot, m_pnMarker);
    Polyline(m_dcPlot, ptMarkerR4x4, 2);
    Polyline(m_dcPlot, ptMarkerR3x4, 2);
    Polyline(m_dcPlot, ptMarkerR2x4, 2);
    Polyline(m_dcPlot, ptMarkerR1x4, 2);
    Polyline(m_dcPlot, ptMarkerF4x4, 2);
    Polyline(m_dcPlot, ptMarkerF3x4, 2);
    Polyline(m_dcPlot, ptMarkerF2x4, 2);
    Polyline(m_dcPlot, ptMarkerF1x4, 2);
    Polyline(m_dcPlot, ptMarkerP4x4, 2);
    Polyline(m_dcPlot, ptMarkerP3x4, 2);
    Polyline(m_dcPlot, ptMarkerP2x4, 2);
    Polyline(m_dcPlot, ptMarkerP1x4, 2);

    /* Draw axis */
    SelectObject(m_dcPlot, m_pnAxis);
    Polyline(m_dcPlot, ptAxisXEEG1, 2);
    Polyline(m_dcPlot, ptAxisXEEG2, 2);
    Polyline(m_dcPlot, ptAxisXEEG3, 2);

    /* Draw cursor */
    if (m_nOperatingModeIndex == 0)
    {
  	  SelectObject(m_dcPlot, m_brCursor);
  	  FillRect(m_dcPlot, &rcCursor, m_brCursor);
    }

    /* Draw data and delay */
    SelectObject(m_dcPlot, m_pnEEG);
    Polyline(m_dcPlot, m_ptREEG, m_nDataSize + 1);
    Polyline(m_dcPlot, m_ptFEEG, m_nDataSize + 1);
    Polyline(m_dcPlot, m_ptCEEG, m_nDataSize + 1);
    SelectObject(m_dcPlot, m_pnLevelA);
    Polyline(m_dcPlot, m_ptTNEEG, m_nDataSize + 1);
    SelectObject(m_dcPlot, m_pnLevelB);
    Polyline(m_dcPlot, m_ptTVEEG, m_nDataSize + 1);
    SelectObject(m_dcPlot, m_pnShift);
    Polyline(m_dcPlot, m_ptSEEG, 2 * m_nDataSize);

    /* Draw clear line */
    SelectObject(m_dcPlot, m_pnClear);
    Polyline(m_dcPlot, ptClearLineTop, 2);
    Polyline(m_dcPlot, ptClearLineBottom, 2);

    /* Unlock canvas */
    fmMain->Canvas->Unlock();
  }

  /* Check count */
  m_nCountVis += 1;
  if (m_nPlotXScale * m_nDataSize * m_nCountVis >= m_nPlotWidth)
  {
  	m_nCountVis = 0;
    m_nPrevRX = m_nPlotLeft;
    m_nPrevFX = m_nPlotLeft;
    m_nPrevCX = m_nPlotLeft;
    m_nPrevTNX = m_nPlotLeft;
    m_nPrevTVX = m_nPlotLeft;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::ShowOnlineData()
{
	DrawData();
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::ShowOfflineData()
{
	int i;

  for (i = 0; i < m_nBlockSize; i++)
  {
  	ReadOfflineData();
    DrawData();
    // Inscrease current position
    m_nFileMarkerPosition += 1;
  }
}
//---------------------------------------------------------------------------
bool __fastcall TfmMain::OpenOfflineData()
{
	int i;
	int nCountA = 0;
  int nCountB = 0;
  int nEndPosition = 0;
  int nSize = 0;
  int nHeaderPosition;
  int nStimulatingIntensity, nStimulatingShift, nStimulatingMode3AlternativeIntensity,
  	nStimulatingMode4AlternativeShift;

	// Open file for read
  if ((m_pOfflineViewingStream = fopen(m_aOutputFileName.c_str(), "rt")) == NULL)
  {
    MessageBox(NULL, "Cannot open file", "File error", MB_OK | MB_ICONERROR);
    return true;
  }
  // Check file format
  if (CheckFileFormat(m_pOfflineViewingStream))
  {
    MessageBox(NULL, "Wrong file format", "File error", MB_OK | MB_ICONERROR);
  	return true;
  }

  /* Params */
  // Get params
  fscanf(m_pOfflineViewingStream,
    "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
  	&m_nSampleRate, &m_nAmpGainIndex, &m_nLoFreqIndex, &m_nHiFreqIndex,
    &m_nMiscellaneousFilterTypeIndex, &m_nPeakingDeadTime,
    &m_nPeakingCommandParameterIndex,
    &m_nPeakingMeanShortWindowLength, &m_nPeakingMeanLongWindowLength,
    &m_pPeakingThresholdLevelArray[0], &m_nPeakingThresholdLevelTypeIndex,
    &m_pPeakingThresholdLevelArray[1], &m_pPeakingThresholdLevelArray[2],
    &m_nPatterningPeakParamIndex, &m_pPatterningPeakParamArray[0],
    &m_pPatterningPeakParamArray[1], &m_pPatterningPeakParamArray[2],
    &m_nTrainingModeIndex, &m_nTrainingDuration,
    &m_nTrainingDurationRatio, &m_nStimulatingTypeIndex,
    &m_nStimulatingDuration, &nStimulatingIntensity, &nStimulatingShift,
    &m_nStimulatingVideoSet, &m_nStimulatingAudioSet,
    &nStimulatingMode3AlternativeIntensity, &nStimulatingMode4AlternativeShift,
    &m_nStimulatingMode5StimulusPeriod, &m_nStimulatingMode6NStimulusPeriod,
    &m_nStimulatingMode6NStimulationTime, &m_nStimulatingMode6NStimulationMaskIndex,
    &m_nStimulatingMode7CycleTime, &m_nStimulatingMode7ModulationIndex,
    &m_nStimulatingMode8StimulusPeriod, &m_nStimulatingMode8ParadigmTypeIndex,
    &m_nStimulatingMode9ParadigmTypeIndex, &m_nStimulatingMode9StimulusNumber,
    &m_nStimulatingMode9StimulusPeriod, &m_nStimulatingMode10ParadigmTypeIndex,
    &m_nStimulatingMode10ShockTypeIndex, &m_nStimulatingMode10AnalysisTime);

  m_nStimulatingIntensityIndex =
  	fmSettings->cbStimulatingIntensity->Items->IndexOf(IntToStr(nStimulatingIntensity));
  m_nStimulatingShiftIndex =
  	fmSettings->cbStimulatingShift->Items->IndexOf(IntToStr(nStimulatingShift));
  m_nStimulatingMode3AlternativeIntensityIndex =
  	fmSettings->cbStimulatingMode3AlternativeIntensity->Items->IndexOf(IntToStr(nStimulatingMode3AlternativeIntensity));
  m_nStimulatingMode4AlternativeShiftIndex =
  	fmSettings->cbStimulatingMode4AlternativeShift->Items->IndexOf(IntToStr(nStimulatingMode4AlternativeShift));

  // Get header position and set file marker after header of file
  nHeaderPosition = ftell(m_pOfflineViewingStream);
  // Set file marker after header of file
  fseek(m_pOfflineViewingStream, nHeaderPosition, SEEK_SET);
  // Get end position of file
  while (!feof(m_pOfflineViewingStream))
  {
  	if (fgetc(m_pOfflineViewingStream) == '\n')
    	nEndPosition += 1;
  }
  // Set size aliquot to m_nDataSize
  nSize = nEndPosition / m_nDataSize;
  /* Init m_pListFileMarkerPositions */
  if (m_pListFileMarkerPositions)
  	delete [] m_pListFileMarkerPositions;
  m_pListFileMarkerPositions = new int [nSize + 1];
  m_pListFileMarkerPositions[0] = nHeaderPosition;
  // Set file marker after header of file
  fseek(m_pOfflineViewingStream, nHeaderPosition, SEEK_SET);
  // Get line positions in file
  while (!feof(m_pOfflineViewingStream))
  {
  	if (fgetc(m_pOfflineViewingStream) == '\n')
    {
    	nCountA += 1;
      if (nCountA == m_nDataSize)
      {
      	nCountA = 0;
        nCountB += 1;
    		m_pListFileMarkerPositions[nCountB] = ftell(m_pOfflineViewingStream);
      }
    }
  }
  // Init Max value of scroll bar
  sbPlotXScroll->Max = nSize - m_nBlockSize;

  return false;
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::ReadOfflineData()
{
  int i;
  int iADCValue, iFLTValue, iCMDValue, iThresholdLevelNoise,
    iThresholdLevelValue, iShiftValue, iModeDependentValue;

  /* Read data from file */
  // Set current position
  fseek(m_pOfflineViewingStream, m_pListFileMarkerPositions[m_nFileMarkerPosition],
  	SEEK_SET);
  // Read data
  for (i = 0; i < m_nDataSize; i++)
 	{
   	fscanf(m_pOfflineViewingStream, "%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
    	&iADCValue, &iFLTValue, &iCMDValue, &iThresholdLevelNoise,
      &iThresholdLevelValue, &iShiftValue, &iModeDependentValue);
		m_pREEG[i]  = (short)iADCValue;
    m_pFEEG[i]  = (short)iFLTValue;
    m_pCEEG[i]  = (short)iCMDValue;
    m_pTNEEG[i] = (short)iThresholdLevelNoise;
    m_pTVEEG[i] = (short)iThresholdLevelValue;
    m_pSEEG[i]  = (short)iShiftValue;
    m_pMDEEG[i] = (short)iModeDependentValue;
  }
}
//---------------------------------------------------------------------------
bool __fastcall TfmMain::CheckFileFormat(FILE *pStream)
{
	int i;
	int nCount;
  char cSymbol;

	// Check header length
  nCount = 0;
  for (i = 0; i < m_nFileFormatHeaderLength * 4; i++)
  {
  	cSymbol = fgetc(pStream);
    if (cSymbol == '\n')
    	break;
    if (cSymbol == '\t')
      nCount += 1;
  }
  // Error
  if (nCount != (m_nFileFormatHeaderLength - 1))
    return true;

  // Check data length
  nCount = 0;
  for (i = 0; i < m_nFileFormatDataLength * 4; i++)
  {
  	cSymbol = fgetc(pStream);
    if (cSymbol == '\n')
    	break;
    if (cSymbol == '\t')
      nCount += 1;
  }
  // Error
  if (nCount != (m_nFileFormatDataLength - 1))
    return true;

  // Set at begin
  fseek(pStream, 0, SEEK_SET);

  return false;
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::EnableControlItems(bool bSettings, bool bStart, bool bStop)
{
  // Mode
  cbOperatingMode->Enabled = bSettings;
  // Settings
  bnSettings->Enabled = bSettings;
	// Start
  bnStart->Enabled = bStart;
  // Stop
  bnStop->Enabled = bStop;
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::ShowStimulationType()
{
	// Uncheked
	cbAVStimulation->Checked = false;
  // Check condition
	if (m_nStimulatingTypeIndex)
    cbAVStimulation->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::ShowTrainingTime()
{
	int nQuotient = m_nTrainingTime / 60;
	int nReminder = m_nTrainingTime % 60;
  AnsiString aTrainingTime;

  aTrainingTime = IntToStr(nQuotient) + ":";
  // Check quotient
  if (nQuotient < 10)
  	aTrainingTime.Insert("0", 1);
  aTrainingTime += IntToStr(nReminder);
  // Check reminder
  if (nReminder < 10)
  	aTrainingTime.Insert("0", 4);

  stTrainingTimeValue->Caption = aTrainingTime;
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::ApplyPlotSettings()
{
  /* Set plot width and height */
  fmMain->Width  = m_nPlotWidth + 37 + 30;
  fmMain->Height = m_nPlotHeight * 3 + 94;
  blPlot->Width  = m_nPlotWidth + 3;
  blPlot->Height = m_nPlotHeight * 3 + 10;
  sbPlotXScroll->Width = m_nPlotWidth + 1;
  sbPlotXScroll->Top 	= m_nPlotHeight * 3 + 40;
  stTrainingTimeCaption->Left = m_nPlotWidth - 56;
  stTrainingTimeValue->Left = m_nPlotWidth - 26;
  // Markers
  stMarkerR4x4->Left = m_nPlotWidth + 8;
  stMarkerR3x4->Left = m_nPlotWidth + 8;
  stMarkerR2x4->Left = m_nPlotWidth + 8;
  stMarkerR1x4->Left = m_nPlotWidth + 8;
  stMarkerR0x4->Left = m_nPlotWidth + 8;
  stMarkerF4x4->Left = m_nPlotWidth + 8;
  stMarkerF3x4->Left = m_nPlotWidth + 8;
  stMarkerF2x4->Left = m_nPlotWidth + 8;
  stMarkerF1x4->Left = m_nPlotWidth + 8;
  stMarkerF0x4->Left = m_nPlotWidth + 8;
  stMarkerP4x4->Left = m_nPlotWidth + 8;
  stMarkerP3x4->Left = m_nPlotWidth + 8;
  stMarkerP2x4->Left = m_nPlotWidth + 8;
  stMarkerP1x4->Left = m_nPlotWidth + 8;
  stMarkerP0x4->Left = m_nPlotWidth + 8;
  // Online control threshold levels
  stOnlineThresholdLevelValue->Left = m_nPlotWidth + 8;
  udOnlineThresholdLevelValue->Left = m_nPlotWidth + 8 +
    stOnlineThresholdLevelValue->Width + 1;
  stOnlineThresholdLevelIndex->Left = m_nPlotWidth + 8;
  udOnlineThresholdLevelIndex->Left = m_nPlotWidth + 8+
    stOnlineThresholdLevelIndex->Width + 1;
  // Online control pattern params
  stOnlinePatternPeakParamValue->Left = m_nPlotWidth + 8;
  udOnlinePatternPeakParamValue->Left = m_nPlotWidth + 8 +
    stOnlinePatternPeakParamValue->Width + 1;
  stOnlinePatternPeakParamIndex->Left = m_nPlotWidth + 8;
  udOnlinePatternPeakParamIndex->Left = m_nPlotWidth + 8 +
    stOnlinePatternPeakParamValue->Width + 1;
  // Online control mode10 correction
  stOnlineCorrectionMode10->Left = m_nPlotWidth + 8;
  sbOnlineCorrectionMode10Cancel->Left = m_nPlotWidth + 8 +
    stOnlineCorrectionMode10->Width + 1;
  sbOnlineCorrectionMode10Release->Left = m_nPlotWidth + 8 +
    stOnlineCorrectionMode10->Width + sbOnlineCorrectionMode10Cancel->Width;
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::sbPlotXScrollChange(TObject *Sender)
{
	// Disable event of init set position
  if (m_bStopXScroll)
  	return;
	// Check limit position
  if (sbPlotXScroll->Position > sbPlotXScroll->Max)
  	return;
  m_nFileMarkerPosition = sbPlotXScroll->Position;
  ShowOfflineData();
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::bnSettingsClick(TObject *Sender)
{
	// Show settings
	fmSettings->ShowModal();

  // Check applied settings
  if (!m_bSettingsApplied)
  	return;

  // ** Main form caption **
  fmMain->Caption = "SmartStim v" + m_aVersion +
    " - [File: " + fmSettings->GetShortFileName(m_aOutputFileName) + "]";

  // ** Settings **
  // Apply plot settings
  ApplyPlotSettings();
  // Set training mode
  stTrainingModeCaption->Visible = true;
  stTrainingModeValue->Visible = true;
  stTrainingModeValue->Caption = IntToStr(m_nTrainingModeIndex + 1);
  // For mode 6N only
  if (m_nTrainingModeIndex == STIM_MODE_6N)
    stTrainingModeValue->Caption = "6:" + IntToStr(m_nStimulatingMode6NStimulationMaskIndex);

  // Show stimulation type
  ShowStimulationType();
  // Set training time
  if (m_nOperatingModeIndex == 0)
  {
	  m_nTrainingTime = m_nTrainingDuration * m_nTrainingDurationRatio;
  }
	// Show training time
  stTrainingTimeCaption->Visible = true;
  stTrainingTimeValue->Visible = true;
	ShowTrainingTime();

  // Set dependent info
  stModeDependentInfo->Visible = false;
  stModeDependentFlag->Visible = false;
  stModeDependentValue->Visible = false;
  if (m_nTrainingModeIndex == STIM_MODE_10 ||  // Type of stimulus
    m_nTrainingModeIndex == STIM_MODE_6)       // Most frequently period
  {
    stModeDependentInfo->Visible = true;
    stModeDependentFlag->Visible = true;
    stModeDependentValue->Caption = "";
    stModeDependentValue->Visible = true;
  }

  /* Markers */
  // Set marker value
  int nMarkerValue;
  nMarkerValue = ((m_nADCSize / 2) / m_nPlotYScale) / 2;
  // Marker R
  stMarkerR4x4->Caption = IntToStr(4 * nMarkerValue).SetLength(4);
  stMarkerR3x4->Caption = IntToStr(3 * nMarkerValue).SetLength(4);
  stMarkerR2x4->Caption = IntToStr(2 * nMarkerValue).SetLength(4);
  stMarkerR1x4->Caption = IntToStr(1 * nMarkerValue).SetLength(4);
  // Marker F
  stMarkerF4x4->Caption = IntToStr(4 * nMarkerValue).SetLength(4);
  stMarkerF3x4->Caption = IntToStr(3 * nMarkerValue).SetLength(4);
  stMarkerF2x4->Caption = IntToStr(2 * nMarkerValue).SetLength(4);
  stMarkerF1x4->Caption = IntToStr(1 * nMarkerValue).SetLength(4);
  // Marker P
  stMarkerP4x4->Caption = IntToStr(4 * nMarkerValue).SetLength(4);
  stMarkerP3x4->Caption = IntToStr(3 * nMarkerValue).SetLength(4);
  stMarkerP2x4->Caption = IntToStr(2 * nMarkerValue).SetLength(4);
  stMarkerP1x4->Caption = IntToStr(1 * nMarkerValue).SetLength(4);
  // Set marker position
  // Marker R
  stMarkerR4x4->Top = 0 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 5;
  stMarkerR3x4->Top = 1 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 5;
  stMarkerR2x4->Top = 2 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 5;
  stMarkerR1x4->Top = 3 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 5;
  stMarkerR0x4->Top = 4 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 5;
  // Marker F
  stMarkerF4x4->Top = 8 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 3;
  stMarkerF3x4->Top = 9 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 3;
  stMarkerF2x4->Top = 10 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 3;
  stMarkerF1x4->Top = 11 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 3;
  stMarkerF0x4->Top = 12 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 3;
  // Marker P
  stMarkerP4x4->Top = 16 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 1;
  stMarkerP3x4->Top = 17 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 1;
  stMarkerP2x4->Top = 18 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 1;
  stMarkerP1x4->Top = 19 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 1;
  stMarkerP0x4->Top = 20 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 1;
  // Set visible marker
  // Marker R
  stMarkerR4x4->Visible = true;
  stMarkerR3x4->Visible = true;
  stMarkerR2x4->Visible = true;
  stMarkerR1x4->Visible = true;
  stMarkerR0x4->Visible = true;
  // Marker F
  stMarkerF4x4->Visible = true;
  stMarkerF3x4->Visible = true;
  stMarkerF2x4->Visible = true;
  stMarkerF1x4->Visible = true;
  stMarkerF0x4->Visible = true;
  // Marker P
  stMarkerP4x4->Visible = true;
  stMarkerP3x4->Visible = true;
  stMarkerP2x4->Visible = true;
  stMarkerP1x4->Visible = true;
  stMarkerP0x4->Visible = true;

  /* Threshold level counters */
  // Set location
  stOnlineThresholdLevelValue->Top = 13 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 7;
  udOnlineThresholdLevelValue->Top = stOnlineThresholdLevelValue->Top;
  stOnlineThresholdLevelIndex->Top = stOnlineThresholdLevelValue->Top +
    stOnlineThresholdLevelValue->Height + 1;
  udOnlineThresholdLevelIndex->Top = stOnlineThresholdLevelIndex->Top;
  // Set counter value
  stOnlineThresholdLevelValue->Caption =
    IntToStr(m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position]);
  // Set counter position
  udOnlineThresholdLevelValue->Position =
    m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position];
  // Set visible counter
  stOnlineThresholdLevelValue->Visible = false;
  udOnlineThresholdLevelValue->Visible = false;
  stOnlineThresholdLevelIndex->Visible = false;
  udOnlineThresholdLevelIndex->Visible = false;
  if (m_nTrainingModeIndex != STIM_MODE_5)
  {
    stOnlineThresholdLevelValue->Visible = true;
    udOnlineThresholdLevelValue->Visible = true;
    stOnlineThresholdLevelIndex->Visible = true;
    udOnlineThresholdLevelIndex->Visible = true;
  }

  /* Pattern params and switch */
  // Set lacation
  stOnlinePatternPeakParamValue->Top = 21 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 5;
  udOnlinePatternPeakParamValue->Top = stOnlinePatternPeakParamValue->Top;
  stOnlinePatternPeakParamIndex->Top = stOnlinePatternPeakParamValue->Top +
    stOnlinePatternPeakParamValue->Height + 1;
  udOnlinePatternPeakParamIndex->Top = stOnlinePatternPeakParamIndex->Top;
  // Set counter value
  stOnlinePatternPeakParamValue->Caption =
    IntToStr(m_pPatterningPeakParamArray[udOnlinePatternPeakParamIndex->Position]);
  // Set counter position
  if (udOnlinePatternPeakParamIndex->Position == 0)
    udOnlinePatternPeakParamValue->Position =
      m_pPatterningPeakParamArray[udOnlinePatternPeakParamIndex->Position];
  else if (udOnlinePatternPeakParamIndex->Position == 1)
    udOnlinePatternPeakParamValue->Position =
      m_pPatterningPeakParamArray[udOnlinePatternPeakParamIndex->Position];
  else if (udOnlinePatternPeakParamIndex->Position == 2)
    udOnlinePatternPeakParamValue->Position =
      m_pPatterningPeakParamArray[udOnlinePatternPeakParamIndex->Position] / 8;
  // Set visible counter
  stOnlinePatternPeakParamValue->Visible = false;
  udOnlinePatternPeakParamValue->Visible = false;
  stOnlinePatternPeakParamIndex->Visible = false;
  udOnlinePatternPeakParamIndex->Visible = false;
  if (m_nTrainingModeIndex == STIM_MODE_9 || m_nTrainingModeIndex == STIM_MODE_10)
  {
    stOnlinePatternPeakParamValue->Visible = true;
    udOnlinePatternPeakParamValue->Visible = true;
    stOnlinePatternPeakParamIndex->Visible = true;
    udOnlinePatternPeakParamIndex->Visible = true;
  }

  /* Mode 10 correction */
  // Set lacation
  stOnlineCorrectionMode10->Top = 5 * (m_nPlotHeight / (2 * 4)) + m_nPlotTop - 9;
  sbOnlineCorrectionMode10Cancel->Top = stOnlineCorrectionMode10->Top;
  sbOnlineCorrectionMode10Release->Top = stOnlineCorrectionMode10->Top;
  // Set visible counter
  stOnlineCorrectionMode10->Visible = false;
  sbOnlineCorrectionMode10Cancel->Visible = false;
  sbOnlineCorrectionMode10Release->Visible = false;
  if (m_nTrainingModeIndex == STIM_MODE_10)
  {
    stOnlineCorrectionMode10->Visible = true;
    sbOnlineCorrectionMode10Cancel->Visible = true;
    sbOnlineCorrectionMode10Release->Visible = true;
  }

  /*** Start ***/
  int i;
	// Init class variables
  m_nFileMarkerPosition = 0;
  m_pListFileMarkerPositions = NULL;

  // Init variables for draw
  m_nCountVis = 0;
  m_nStateVis = 0;
  m_nCountAcq = 0;
  m_nPrevRX = m_nPlotLeft;
  m_nPrevFX = m_nPlotLeft;
  m_nPrevCX = m_nPlotLeft;
  m_nPrevTNX = m_nPlotLeft;
  m_nPrevTVX = m_nPlotLeft;
  m_nPrevRY = 1 * (m_nPlotHeight / 2) + m_nPlotTop + 1;
  m_nPrevFY = 3 * (m_nPlotHeight / 2) + m_nPlotTop + 3;
  m_nPrevCY = 3 * (m_nPlotHeight / 2) + m_nPlotTop + 3;
  m_nPrevTNY = 5 * (m_nPlotHeight / 2) + m_nPlotTop + 5;
  m_nPrevTVY = 5 * (m_nPlotHeight / 2) + m_nPlotTop + 5;
  m_nPrevRY0 = 1 * (m_nPlotHeight / 2) + m_nPlotTop + 1;
  m_nPrevFY0 = 3 * (m_nPlotHeight / 2) + m_nPlotTop + 3;
  m_nPrevCY0 = 3 * (m_nPlotHeight / 2) + m_nPlotTop + 3;
  m_nPrevTNY0 = 5 * (m_nPlotHeight / 2) + m_nPlotTop + 5;
  m_nPrevTVY0 = 5 * (m_nPlotHeight / 2) + m_nPlotTop + 5;

  // Init buffers
  m_pREEG  = new short [m_nDataSize];
  m_pFEEG  = new short [m_nDataSize];
  m_pCEEG  = new short [m_nDataSize];
  m_pTNEEG = new short [m_nDataSize];
  m_pTVEEG = new short [m_nDataSize];
  m_pSEEG  = new short [m_nDataSize];
  m_pMDEEG = new short [m_nDataSize];
  for (i = 0; i < m_nDataSize; i++)
  {
		m_pREEG[i]  = 0;
  	m_pFEEG[i]  = 0;
  	m_pCEEG[i]  = 0;
    m_pTNEEG[i] = 0;
  	m_pTVEEG[i] = 0;
  	m_pSEEG[i]  = 0;
  	m_pMDEEG[i] = 0;
  }

  // Create graphic objects
  CreateGraphicObjects();

  // Init POINTS arrays
  m_ptREEG = new POINT [m_nDataSize + 1];
  m_ptFEEG = new POINT [m_nDataSize + 1];
  m_ptCEEG = new POINT [m_nDataSize + 1];
  m_ptTNEEG = new POINT [m_nDataSize + 1];
  m_ptTVEEG = new POINT [m_nDataSize + 1];
  m_ptSEEG = new POINT [2 * m_nDataSize];

  // Check mode
  switch (m_nOperatingModeIndex)
  {
  	case 0: // Online Processing
    {
    	// Disable control items
  		EnableControlItems(false, true, true);
      // Show stimulation type
	  	ShowStimulationType();
      // Init training time
      m_nTrainingTime = m_nTrainingDuration * m_nTrainingDurationRatio;
      // Show elapsed time
      ShowTrainingTime();
  		// Create thread for data exchange
  		tdConnection = new TConnection(true);
    	// Resume thread
  		tdConnection->Resume();
    	break;
    }
    case 1: // Offline Processing
    {
    	// Disable control items
  		EnableControlItems(false, true, true);
  		// Create thread for data exchange
  		tdConnection = new TConnection(true);
    	// Resume thread
  		tdConnection->Resume();
    	break;
    }
    case 2: // Offline Viewing
    {
    	// Open file for read in offline mode
  		if (OpenOfflineData())
    		return;
      // Disable control items
  		EnableControlItems(false, false, true);
    	// Enable scrooll bar
    	m_bStopXScroll = false;
    	sbPlotXScroll->Enabled = true;
      // Enable plot update
      m_bPlotUpdateEnabled = true;
    	// Show data
    	DrawPlot();
    	ShowOfflineData();
    	break;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::cbOperatingModeChange(TObject *Sender)
{
	m_nOperatingModeIndex = cbOperatingMode->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormPaint(TObject *Sender)
{
	if (m_bPlotUpdateEnabled)
  {
  	m_nFileMarkerPosition = sbPlotXScroll->Position;
  	ShowOfflineData();
  }
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
  //if (MessageBox(NULL, "Save settings?", "SmartStim.ini",
  //  	MB_YESNO | MB_ICONQUESTION) == IDNO)
  //	return;

	/* Save last settings in ss.ini */
  TStringList *List = new TStringList();
  List->Add("[OPERATING_MODE_INDEX]");
	List->Add(IntToStr(m_nOperatingModeIndex));
  List->Add("[SAMPLE_RATE]");
	List->Add(IntToStr(m_nSampleRate));
  List->Add("[AMP_GAIN_INDEX]");
	List->Add(IntToStr(m_nAmpGainIndex));
	List->Add("[LOW_FREQ_INDEX]");
	List->Add(IntToStr(m_nLoFreqIndex));
	List->Add("[HIGH_FREQ_INDEX]");
	List->Add(IntToStr(m_nHiFreqIndex));
	List->Add("[FILTERING_TYPE_INDEX]");
	List->Add(IntToStr(m_nMiscellaneousFilterTypeIndex));
  List->Add("[PEAKING_DEAD_TIME]");
	List->Add(IntToStr(m_nPeakingDeadTime));
  List->Add("[PEAKING_COMMAND_PARAMETER_INDEX]");
	List->Add(IntToStr(m_nPeakingCommandParameterIndex));
  List->Add("[PEAKING_MEAN_SHORT_WINDOW_LENGTH]");
	List->Add(IntToStr(m_nPeakingMeanShortWindowLength));
  List->Add("[PEAKING_MEAN_LONG_WINDOW_LENGTH]");
	List->Add(IntToStr(m_nPeakingMeanLongWindowLength));
  List->Add("[PEAKING_THRESHOLD_LEVEL_INDEX]");
  List->Add(IntToStr(m_nPeakingThresholdLevelIndex));
  List->Add("[PEAKING_THRESHOLD_LEVEL_NOISE]");
	List->Add(IntToStr(m_pPeakingThresholdLevelArray[0]));
  List->Add("[PEAKING_THRESHOLD_LEVEL_TYPE_INDEX]");
	List->Add(IntToStr(m_nPeakingThresholdLevelTypeIndex));
  List->Add("[PEAKING_THRESHOLD_LEVEL_FIXED]");
	List->Add(IntToStr(m_pPeakingThresholdLevelArray[1]));
  List->Add("[PEAKING_THRESHOLD_LEVEL_FLOAT]");
	List->Add(IntToStr(m_pPeakingThresholdLevelArray[2]));
  List->Add("[PEAKING_THRESHOLD_LEVEL_FLOAT_MIN]");
	List->Add(IntToStr(m_pPeakingThresholdLevelArray[3]));
  List->Add("[PEAKING_THRESHOLD_LEVEL_FLOAT_MAX]");
	List->Add(IntToStr(m_pPeakingThresholdLevelArray[4]));
  List->Add("[PATTERNING_PEAK_PARAM_INDEX]");
  List->Add(IntToStr(m_nPatterningPeakParamIndex));
  List->Add("[PATTERNING_PEAK_PARAM_MIN]");
  List->Add(IntToStr(m_pPatterningPeakParamArray[0]));
  List->Add("[PATTERNING_PEAK_PARAM_MAX]");
  List->Add(IntToStr(m_pPatterningPeakParamArray[1]));
  List->Add("[PATTERNING_PEAK_PARAM_SPACE]");
  List->Add(IntToStr(m_pPatterningPeakParamArray[2]));
  List->Add("[TRAINING_MODE]");
	List->Add(IntToStr(m_nTrainingModeIndex + 1));
  List->Add("[TRAINING_DURATION]");
	List->Add(IntToStr(m_nTrainingDuration));
  List->Add("[TRAINING_DURATION_RATIO]");
	List->Add(IntToStr(m_nTrainingDurationRatio));
	List->Add("[STIMULATING_TYPE_INDEX]");
	List->Add(IntToStr(m_nStimulatingTypeIndex));
  List->Add("[STIMULATING_DURATION]");
	List->Add(IntToStr(m_nStimulatingDuration));
	List->Add("[STIMULATING_INTENSITY_INDEX]");
	List->Add(IntToStr(m_nStimulatingIntensityIndex));
  List->Add("[STIMULATING_INTENSITY_ARRAY]");
  List->Add(IntToStr(m_pStimulatingIntensityArray[0]));
  List->Add(IntToStr(m_pStimulatingIntensityArray[1]));
  List->Add(IntToStr(m_pStimulatingIntensityArray[2]));
  List->Add(IntToStr(m_pStimulatingIntensityArray[3]));
  List->Add(IntToStr(m_pStimulatingIntensityArray[4]));
  List->Add("[STIMULATING_SHIFT_INDEX]");
	List->Add(IntToStr(m_nStimulatingShiftIndex));
  List->Add("[STIMULATING_SHIFT_ARRAY]");
  List->Add(IntToStr(m_pStimulatingShiftArray[0]));
  List->Add(IntToStr(m_pStimulatingShiftArray[1]));
  List->Add(IntToStr(m_pStimulatingShiftArray[2]));
  List->Add(IntToStr(m_pStimulatingShiftArray[3]));
  List->Add(IntToStr(m_pStimulatingShiftArray[4]));
  List->Add("[STIMULATING_VIDEO_SET]");
  List->Add(IntToStr(m_nStimulatingVideoSet));
  List->Add("[STIMULATING_AUDIO_SET]");
  List->Add(IntToStr(m_nStimulatingAudioSet));
  List->Add("[STIMULATING_MODE3_ALTERNATIVE_INTENSITY_INDEX]");
	List->Add(IntToStr(m_nStimulatingMode3AlternativeIntensityIndex));
 	List->Add("[STIMULATING_MODE4_ALTERNATIVE_INTENSITY_INDEX]");
	List->Add(IntToStr(m_nStimulatingMode4AlternativeShiftIndex));
  List->Add("[STIMULATING_MODE5_STIMULUS_PERIOD]");
	List->Add(IntToStr(m_nStimulatingMode5StimulusPeriod));
  List->Add("[STIMULATING_MODE6N_STIMULUS_PERIOD]");
	List->Add(IntToStr(m_nStimulatingMode6NStimulusPeriod));
  List->Add("[STIMULATING_MODE6N_STIMULATION_TIME]");
	List->Add(IntToStr(m_nStimulatingMode6NStimulationTime));
  List->Add("[STIMULATING_MODE6N_STIMULATION_MASK]");
	List->Add(IntToStr(m_nStimulatingMode6NStimulationMaskIndex));
  List->Add("[STIMULATING_MODE7_CYCLE_TIME]");
	List->Add(IntToStr(m_nStimulatingMode7CycleTime));
  List->Add("[STIMULATING_MODE7_MODULATION_INDEX]");
	List->Add(IntToStr(m_nStimulatingMode7ModulationIndex));
  List->Add("[STIMULATING_MODE8_STIMULUS_PERIOD]");
	List->Add(IntToStr(m_nStimulatingMode8StimulusPeriod));
  List->Add("[STIMULATING_MODE8_PARADIGM_TYPE_INDEX]");
	List->Add(IntToStr(m_nStimulatingMode8ParadigmTypeIndex));
  List->Add("[STIMULATING_MODE9_PARADIGM_TYPE_INDEX]");
  List->Add(IntToStr(m_nStimulatingMode9ParadigmTypeIndex));
  List->Add("[STIMULATING_MODE9_STIMULUS_NUMBER]");
  List->Add(IntToStr(m_nStimulatingMode9StimulusNumber));
  List->Add("[STIMULATING_MODE9_STIMULUS_PERIOD]");
  List->Add(IntToStr(m_nStimulatingMode9StimulusPeriod));
  List->Add("[STIMULATING_MODE10_PARADIGM_TYPE_INDEX]");
  List->Add(IntToStr(m_nStimulatingMode10ParadigmTypeIndex));
  List->Add("[STIMULATING_MODE10_SHOCK_TYPE_INDEX]");
  List->Add(IntToStr(m_nStimulatingMode10ShockTypeIndex));
  List->Add("[STIMULATING_MODE10_ANALYSIS_TIME]");
  List->Add(IntToStr(m_nStimulatingMode10AnalysisTime));
	List->Add("[PLOT_WIDTH]");
	List->Add(IntToStr(m_nPlotWidth));
	List->Add("[PLOT_HEIGHT]");
	List->Add(IntToStr(m_nPlotHeight * 3));
	List->Add("[PLOT_XSCALE]");
	List->Add(IntToStr(m_nPlotXScale));
	List->Add("[PLOT_YSCALE]");
	List->Add(IntToStr(m_nPlotYScale));
	List->Add("[PORT]");
	List->Add(m_aMiscellaneousPort);
	List->Add("[OUTPUT_FILE_NAME]");
	List->Add(m_aOutputFileName);
	List->Add("[INPUT_FILE_NAME]");
	List->Add(m_aInputFileName);
  List->Add("[SOUND_BEGIN_FILE_NAME]");
  List->Add(m_aSoundBeginFileName);
  List->Add("[SOUND_RELAX_FILE_NAME]");
  List->Add(m_aSoundRelaxFileName);
  List->Add("[SOUND_SHOCK_FILE_NAME]");
  List->Add(m_aSoundShockFileName);
  List->Add("[BACKGOUND_COLOR]");
	List->Add("0x" + IntToHex(m_nBackgroundColor, 6));
  List->Add("[VERSION]");
	List->Add(m_aVersion);

  try
  {
    List->SaveToFile("SmartStim.ini");
  }
  catch (Exception &exception)
  {
    MessageBox(NULL, exception.Message.c_str(), "SmartStim.ini",
    	MB_OK | MB_ICONWARNING);
  }
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormShow(TObject *Sender)
{
	cbOperatingMode->Text =
  	cbOperatingMode->Items->Strings[m_nOperatingModeIndex];
	// Apply plot settings
  ApplyPlotSettings();
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::udOnlineThresholdLevelValueClick(TObject *Sender,
      TUDBtnType Button)
{
  if (udOnlineThresholdLevelIndex->Position == 0)      // TL noise
  {
    // Init array
    m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position] =
      udOnlineThresholdLevelValue->Position;
    // Set caption
    stOnlineThresholdLevelValue->Caption =
      IntToStr(m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position]);
  }
  else if (udOnlineThresholdLevelIndex->Position == 1) // TL fixed
  {
    // Init array
    m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position] =
      udOnlineThresholdLevelValue->Position;
    // Set caption
    stOnlineThresholdLevelValue->Caption =
      IntToStr(m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position]);
  }
  else if (udOnlineThresholdLevelIndex->Position == 2) // TL float
  {
    // Init array
    m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position] =
      udOnlineThresholdLevelValue->Position;
    // Set caption
    stOnlineThresholdLevelValue->Caption =
      IntToStr(m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position]);
  }
  else if (udOnlineThresholdLevelIndex->Position == 3) // TL float min limit
  {
    // Init array
    m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position] =
      udOnlineThresholdLevelValue->Position;
    // Set caption
    stOnlineThresholdLevelValue->Caption =
      IntToStr(m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position]);
  }
  else if (udOnlineThresholdLevelIndex->Position == 4) // TL float max limit
  {
    // Init array
    m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position] =
      udOnlineThresholdLevelValue->Position;
    // Set caption
    stOnlineThresholdLevelValue->Caption =
      IntToStr(m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position]);
  }

  // Init online control code
  fmMain->m_nOnlineControl = udOnlineThresholdLevelIndex->Position + 1;
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::udOnlinePatternPeakParamValueClick(TObject *Sender,
      TUDBtnType Button)
{
  if (udOnlinePatternPeakParamIndex->Position == 0)      // Peak min
  {
    // Init array
    m_pPatterningPeakParamArray[udOnlinePatternPeakParamIndex->Position] =
      udOnlinePatternPeakParamValue->Position;
    // Set caption
    stOnlinePatternPeakParamValue->Caption =
      IntToStr(m_pPatterningPeakParamArray[udOnlinePatternPeakParamIndex->Position]);
  }
  else if (udOnlinePatternPeakParamIndex->Position == 1) // Peak max
  {
    // Init array
    m_pPatterningPeakParamArray[udOnlinePatternPeakParamIndex->Position] =
      udOnlinePatternPeakParamValue->Position;
    // Set caption
    stOnlinePatternPeakParamValue->Caption =
      IntToStr(m_pPatterningPeakParamArray[udOnlinePatternPeakParamIndex->Position]);
  }
  else if (udOnlinePatternPeakParamIndex->Position == 2) // Peak space
  {
    // Init array
    m_pPatterningPeakParamArray[udOnlinePatternPeakParamIndex->Position] =
      udOnlinePatternPeakParamValue->Position * 8;
    // Set caption
    stOnlinePatternPeakParamValue->Caption =
      IntToStr(m_pPatterningPeakParamArray[udOnlinePatternPeakParamIndex->Position]);
  }

  // Init online control code
  fmMain->m_nOnlineControl = udOnlinePatternPeakParamIndex->Position + 6;
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::udOnlinePatternPeakParamIndexClick(
      TObject *Sender, TUDBtnType Button)
{
  // Set current param index
  if (udOnlinePatternPeakParamIndex->Position == 0)
  {
    stOnlinePatternPeakParamIndex->Caption = "min";
    // Set current param value
    stOnlinePatternPeakParamValue->Caption =
      IntToStr(m_pPatterningPeakParamArray[udOnlinePatternPeakParamIndex->Position]);
    // Set current updown position
    udOnlinePatternPeakParamValue->Position =
      m_pPatterningPeakParamArray[udOnlinePatternPeakParamIndex->Position];
  }
  else if (udOnlinePatternPeakParamIndex->Position == 1)
  {
    stOnlinePatternPeakParamIndex->Caption = "max";
    // Set current param value
    stOnlinePatternPeakParamValue->Caption =
      IntToStr(m_pPatterningPeakParamArray[udOnlinePatternPeakParamIndex->Position]);
    // Set current updown position
    udOnlinePatternPeakParamValue->Position =
      m_pPatterningPeakParamArray[udOnlinePatternPeakParamIndex->Position];
  }
  else if (udOnlinePatternPeakParamIndex->Position == 2)
  {
    stOnlinePatternPeakParamIndex->Caption = "int";
    // Set current param value
    stOnlinePatternPeakParamValue->Caption =
      IntToStr(m_pPatterningPeakParamArray[udOnlinePatternPeakParamIndex->Position]);
    // Set current updown position
    udOnlinePatternPeakParamValue->Position =
      m_pPatterningPeakParamArray[udOnlinePatternPeakParamIndex->Position] / 8;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::bnStartClick(TObject *Sender)
{
  m_bStarted = true;
  EnableControlItems(false, false, true);
  // Init online control code
  fmMain->m_nOnlineControl = 0xF;
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::udOnlineThresholdLevelIndexClick(TObject *Sender,
      TUDBtnType Button)
{
  // Set current param index
  if (udOnlineThresholdLevelIndex->Position == 0)
  {
    stOnlineThresholdLevelValue->Enabled = true;
    udOnlineThresholdLevelValue->Enabled = true;
    stOnlineThresholdLevelIndex->Caption = "low";
    // Set current param value
    stOnlineThresholdLevelValue->Caption =
      IntToStr(m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position]);
    // Set current updown position
    udOnlineThresholdLevelValue->Position =
      m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position];
  }
  else if (udOnlineThresholdLevelIndex->Position == 1)
  {
    stOnlineThresholdLevelValue->Enabled = false;
    udOnlineThresholdLevelValue->Enabled = false;
    if (fmMain->m_nPeakingThresholdLevelTypeIndex == 1)
    {
      stOnlineThresholdLevelValue->Enabled = true;
      udOnlineThresholdLevelValue->Enabled = true;
    }
    stOnlineThresholdLevelIndex->Caption = "fix";
    // Set current param value
    stOnlineThresholdLevelValue->Caption =
      IntToStr(m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position]);
    // Set current updown position
    udOnlineThresholdLevelValue->Position =
      m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position];
  }
  else if (udOnlineThresholdLevelIndex->Position == 2)
  {
    stOnlineThresholdLevelValue->Enabled = false;
    udOnlineThresholdLevelValue->Enabled = false;
    if (fmMain->m_nPeakingThresholdLevelTypeIndex == 0)
    {
      stOnlineThresholdLevelValue->Enabled = true;
      udOnlineThresholdLevelValue->Enabled = true;
    }
    stOnlineThresholdLevelIndex->Caption = "flt";
    // Set current param value
    stOnlineThresholdLevelValue->Caption =
      IntToStr(m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position]);
    // Set current updown position
    udOnlineThresholdLevelValue->Position =
      m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position];
  }
  else if (udOnlineThresholdLevelIndex->Position == 3)
  {
    stOnlineThresholdLevelValue->Enabled = false;
    udOnlineThresholdLevelValue->Enabled = false;
    if (fmMain->m_nPeakingThresholdLevelTypeIndex == 0)
    {
      stOnlineThresholdLevelValue->Enabled = true;
      udOnlineThresholdLevelValue->Enabled = true;
    }
    stOnlineThresholdLevelIndex->Caption = "min";
    // Set current param value
    stOnlineThresholdLevelValue->Caption =
      IntToStr(m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position]);
    // Set current updown position
    udOnlineThresholdLevelValue->Position =
      m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position];
  }
  else if (udOnlineThresholdLevelIndex->Position == 4)
  {
    stOnlineThresholdLevelValue->Enabled = false;
    udOnlineThresholdLevelValue->Enabled = false;
    if (fmMain->m_nPeakingThresholdLevelTypeIndex == 0)
    {
      stOnlineThresholdLevelValue->Enabled = true;
      udOnlineThresholdLevelValue->Enabled = true;
    }
    stOnlineThresholdLevelIndex->Caption = "max";
    // Set current param value
    stOnlineThresholdLevelValue->Caption =
      IntToStr(m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position]);
    // Set current updown position
    udOnlineThresholdLevelValue->Position =
      m_pPeakingThresholdLevelArray[udOnlineThresholdLevelIndex->Position];
  }
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::sbOnlineCorrectionMode10CancelClick(
      TObject *Sender)
{
  m_nOnlineCorrectionMode10 = 2;
  stOnlineCorrectionMode10->Color = clGreen;
  fmMain->m_nOnlineControl = 0x9;
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::sbOnlineCorrectionMode10ReleaseClick(
      TObject *Sender)
{
  m_nOnlineCorrectionMode10 = 3;
  stOnlineCorrectionMode10->Color = clRed;
  fmMain->m_nOnlineControl = 0x9;
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::NAnalysisFFTClick(TObject *Sender)
{
  // Spectrum
  fmSpectrum->SpectrumAnalysis();
  fmSpectrum->ShowModal();
}
//---------------------------------------------------------------------------

