//---------------------------------------------------------------------------
#ifndef UMainH
#define UMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include <stdio.h>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#define STIM_MODE_1  0
#define STIM_MODE_2  1
#define STIM_MODE_3  2
#define STIM_MODE_4  3
#define STIM_MODE_5  4
#define STIM_MODE_6N 5
#define STIM_MODE_7  6
#define STIM_MODE_8  7
#define STIM_MODE_9  8
#define STIM_MODE_10 9
#define STIM_MODE_6 13
//---------------------------------------------------------------------------
class TfmMain : public TForm
{
__published:	// IDE-managed Components
	TBevel *blPlot;
	TScrollBar *sbPlotXScroll;
	TButton *bnSettings;
	TButton *bnStart;
	TButton *bnStop;
	TComboBox *cbOperatingMode;
  TCheckBox *cbAVStimulation;
  TStaticText *stTrainingTimeCaption;
  TStaticText *stModeDependentInfo;
  TStaticText *stTrainingModeCaption;
  TStaticText *stMarkerR4x4;
  TStaticText *stMarkerR0x4;
  TStaticText *stMarkerR3x4;
  TStaticText *stMarkerR2x4;
  TStaticText *stMarkerR1x4;
  TStaticText *stMarkerF4x4;
  TStaticText *stMarkerF0x4;
  TStaticText *stMarkerF3x4;
  TStaticText *stMarkerF2x4;
  TStaticText *stMarkerF1x4;
  TStaticText *stMarkerP4x4;
  TStaticText *stMarkerP0x4;
  TStaticText *stMarkerP3x4;
  TStaticText *stMarkerP2x4;
  TStaticText *stMarkerP1x4;
  TUpDown *udOnlineThresholdLevelValue;
  TStaticText *stTrainingModeValue;
  TStaticText *stModeDependentValue;
  TStaticText *stTrainingTimeValue;
  TStaticText *stOnlineThresholdLevelValue;
  TStaticText *stOnlinePatternPeakParamValue;
  TUpDown *udOnlinePatternPeakParamValue;
  TUpDown *udOnlinePatternPeakParamIndex;
  TStaticText *stOnlinePatternPeakParamIndex;
  TStaticText *stModeDependentFlag;
  TUpDown *udOnlineThresholdLevelIndex;
  TStaticText *stOnlineThresholdLevelIndex;
  TStaticText *stOnlineCorrectionMode10;
  TSpeedButton *sbOnlineCorrectionMode10Release;
  TSpeedButton *sbOnlineCorrectionMode10Cancel;
  TPopupMenu *pmSmartStimAnalysis;
  TMenuItem *NAnalysisFFT;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall bnStopClick(TObject *Sender);
	void __fastcall sbPlotXScrollChange(TObject *Sender);
	void __fastcall bnSettingsClick(TObject *Sender);
	void __fastcall cbOperatingModeChange(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
  void __fastcall udOnlineThresholdLevelValueClick(TObject *Sender,
          TUDBtnType Button);
  void __fastcall udOnlinePatternPeakParamValueClick(TObject *Sender,
          TUDBtnType Button);
  void __fastcall udOnlinePatternPeakParamIndexClick(TObject *Sender,
          TUDBtnType Button);
  void __fastcall bnStartClick(TObject *Sender);
  void __fastcall udOnlineThresholdLevelIndexClick(TObject *Sender,
          TUDBtnType Button);
  void __fastcall sbOnlineCorrectionMode10CancelClick(TObject *Sender);
  void __fastcall sbOnlineCorrectionMode10ReleaseClick(TObject *Sender);
  void __fastcall NAnalysisFFTClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfmMain(TComponent* Owner);
  // Visualize data
  void __fastcall DrawPlot();
  void __fastcall DrawData();
  void __fastcall ShowOnlineData();
  void __fastcall ShowOfflineData();
  bool __fastcall OpenOfflineData();
  void __fastcall ReadOfflineData();
  bool __fastcall CheckFileFormat(FILE *pStream);
  // Service routine
  void __fastcall EnableControlItems(bool bSettings, bool bStart, bool bStop);
  void __fastcall ShowStimulationType();
  // Training time
  void __fastcall ShowTrainingTime();
  // Graphic objects
  void __fastcall CreateGraphicObjects();
  void __fastcall DeleteGraphicObjects();
  // Delete EEG Objects
  void __fastcall DeleteEEGObjects();
  // Apply plot settings
  void __fastcall ApplyPlotSettings();
  // Class variables
  short *m_pREEG; // Raw EEG
  short *m_pFEEG; // Filtering EEG
  short *m_pCEEG; // Command EEG
  short *m_pMDEEG; // Mode dependent value
  short *m_pTNEEG; // Threshold level value fixed/float for EEG
  short *m_pTVEEG; // Threshold level value fixed/float for EEG
  short *m_pSEEG;  // Shift for EEG
  // FILE for offline mode
  FILE *m_pOfflineViewingStream;
  // File position
  int m_nFileMarkerPosition;
  int *m_pListFileMarkerPositions;
  // Graphic objects
  HDC m_dcPlot;
  HPEN m_pnMarker;
  HPEN m_pnAxis;
  HPEN m_pnEEG;
  HPEN m_pnLevelA;
  HPEN m_pnLevelB;
  HPEN m_pnShift;
  HPEN m_pnClear;
  HBRUSH m_brPlot;
  HBRUSH m_brCursor;
  HBRUSH m_brClear;
  // Paint objects
  POINT *m_ptREEG;
  POINT *m_ptFEEG;
  POINT *m_ptCEEG;
  POINT *m_ptTNEEG;
  POINT *m_ptTVEEG;
  POINT *m_ptSEEG;
  // Visualization params
	int m_nDataSize;
	int m_nBlockSize;
  int m_nADCSize;     // ADC max value
	int m_nCursorWidth;
	int m_nPlotTop;
	int m_nPlotLeft;
  // Use instead of static variables
  int m_nCountVis;
  int m_nStateVis;
  int m_nCountAcq;
  int m_nPrevRX;     // Previous value of Raw EEG axis X
  int m_nPrevFX;
  int m_nPrevCX;
  int m_nPrevTNX;
  int m_nPrevTVX;
  int m_nPrevRY;    // Previous value of Raw EEG axis Y
  int m_nPrevFY;
  int m_nPrevCY;
  int m_nPrevTNY;
  int m_nPrevTVY;
  int m_nPrevRY0;   // Previous value of Raw EEG axis Y (at 0)
  int m_nPrevFY0;
  int m_nPrevCY0;
  int m_nPrevTNY0;
  int m_nPrevTVY0;

  // Training time
  int m_nTrainingTime;
  // Mode dependent
  int m_nModeDependentValue;
  // Disable some event from scroll bar
  bool m_bStopXScroll;
  // Operating mode
  int m_nOperatingModeIndex; // index
  // Apply plot settings
  bool m_bSettingsApplied;
  // Online control
  int m_nOnlineControl;
  int m_nOnlineCorrectionMode10;
  // Started
  bool m_bStarted;
  // Plot update enable
  bool m_bPlotUpdateEnabled;
  // Background color
  int m_nBackgroundColor;
  // File format
  int m_nFileFormatHeaderLength;
  int m_nFileFormatDataLength;

  /* Settings */
  // Digitizing
  int m_nSampleRate; 		// value
  int m_nAmpGainIndex;	// index
  int m_nAmpGain;       // value
  int m_nLoFreqIndex; 	// index
  int m_nHiFreqIndex; 	// index
  // Processing
  int m_nMiscellaneousFilterTypeIndex;  // index
  // Peaking
  int m_nPeakingDeadTime;
  int m_nPeakingCommandParameterIndex;
  int m_nPeakingMeanShortWindowLength;
  int m_nPeakingMeanLongWindowLength;
  int m_nPeakingThresholdLevelTypeIndex; // Fixed or Float
  int m_nPeakingThresholdLevelIndex;
  int m_pPeakingThresholdLevelArray[5];
  // Patterning
  int m_nPatterningPeakParamIndex;
  int m_pPatterningPeakParamArray[3];
  // Stmulating
  int m_nStimulatingTypeIndex; 				  // index
  int m_nStimulatingDuration;           // value
  int m_nStimulatingIntensityIndex; 		// index
  int m_pStimulatingIntensityArray[5];  // array
  int m_nStimulatingShiftIndex;  			  // index
  int m_pStimulatingShiftArray[5];   	  // array
  int m_nStimulatingMode3AlternativeIntensityIndex; // index
  int m_nStimulatingMode4AlternativeShiftIndex;     // index
  int m_nStimulatingMode5StimulusPeriod;  	// value
  int m_nStimulatingMode6NStimulusPeriod; 	// value
  int m_nStimulatingMode6NStimulationTime; // value
  int m_nStimulatingMode6NStimulationMaskIndex;	// index
  int m_nStimulatingMode7CycleTime;					// value
  int m_nStimulatingMode7ModulationIndex;		// index
  int m_nStimulatingMode8StimulusPeriod;  	// value
  int m_nStimulatingMode8ParadigmTypeIndex; // index
  int m_nStimulatingMode9ParadigmTypeIndex; // index
  int m_nStimulatingMode9StimulusNumber;		// value
	int m_nStimulatingMode9StimulusPeriod;    // value
	int m_nStimulatingMode10ParadigmTypeIndex;// index
	int m_nStimulatingMode10ShockTypeIndex;   // index
	int m_nStimulatingMode10AnalysisTime;			// value
  int m_nStimulatingVideoSet;               // value
  int m_nStimulatingAudioSet;               // value
  // Training
  int m_nTrainingModeIndex;			// index
  int m_nTrainingDuration;			// value
  int m_nTrainingDurationRatio;	// value
  // Plot
  int m_nPlotWidth;   	// value
  int m_nPlotHeight;   	// value
  int m_nPlotXScale;   	// value
  int m_nPlotYScale;   	// value
  // Port
  AnsiString m_aMiscellaneousPort;  // string
  // Output file name
  AnsiString m_aOutputFileName; // string
  // Input file name
  AnsiString m_aInputFileName;  // string
  // Sound
  AnsiString m_aSoundBeginFileName;
  AnsiString m_aSoundRelaxFileName;
  AnsiString m_aSoundShockFileName;
  // Version
  AnsiString m_aVersion;  // string
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
