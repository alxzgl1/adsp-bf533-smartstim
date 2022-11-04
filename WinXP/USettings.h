//---------------------------------------------------------------------------
#ifndef USettingsH
#define USettingsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <Registry.hpp>
//---------------------------------------------------------------------------
class TfmSettings : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *gbStimulating;
	TGroupBox *gbDigitizing;
	TGroupBox *gbPlot;
	TStaticText *stStimulatingShift;
  TStaticText *stStimulatingIntensity;
	TStaticText *stDigitizingSampleRate;
	TStaticText *stDigitizingLoFreq;
	TStaticText *stDigitizingHiFreq;
	TStaticText *stPlotWidth;
	TStaticText *stPlotHeight;
	TStaticText *stPlotXScale;
	TStaticText *stPlotYScale;
  TStaticText *stInputFileName;
  TSpeedButton *sbInputFileName;
  TEdit *edInputFileName;
	TComboBox *cbStimulatingShift;
  TComboBox *cbStimulatingIntensity;
	TComboBox *cbDigitizingSampleRate;
	TComboBox *cbDigitizingLoFreq;
	TComboBox *cbDigitizingHiFreq;
	TComboBox *cbPlotWidth;
	TComboBox *cbPlotHeight;
	TComboBox *cbPlotXScale;
	TComboBox *cbPlotYScale;
	TStaticText *stDigitizingAmpGain;
	TComboBox *cbDigitizingAmpGain;
	TStaticText *stStimulatingType;
	TComboBox *cbStimulatingType;
  TStaticText *stOutputFileName;
  TEdit *edOutputFileName;
  TSpeedButton *sbOutputFileName;
  TOpenDialog *dlgOpenOutputFile;
	TBevel *blOK;
	TGroupBox *cbPeaking;
  TStaticText *stPeakingThresholdLevelNoise;
  TComboBox *cbPeakingThresholdLevelNoise;
	TStaticText *stPeakingDeadTime;
	TComboBox *cbPeakingDeadTime;
	TGroupBox *gbTraining;
	TStaticText *stTrainingDuration;
	TStaticText *stTrainingMode;
	TComboBox *cbTrainingDuration;
	TComboBox *cbTrainingMode;
  TStaticText *stPeakingThresholdLevelFloat;
  TComboBox *cbPeakingThresholdLevelFloat;
	TButton *bnApply;
	TButton *bnCancel;
	TPageControl *pcStimulatingMode;
	TTabSheet *tsStimulatingMode1;
	TTabSheet *tsStimulatingMode2;
	TTabSheet *tsStimulatingMode3;
	TTabSheet *tsStimulatingMode4;
	TTabSheet *tsStimulatingMode5;
	TTabSheet *tsStimulatingMode6;
	TTabSheet *tsStimulatingMode7;
	TStaticText *stStimulatingMode7CycleTime;
	TComboBox *cbStimulatingMode7CycleTime;
  TStaticText *stStimulatingMode6NStimulationMask;
  TComboBox *cbStimulatingMode6NStimulationMask;
  TStaticText *stStimulatingMode6NStimulusPeriod;
  TComboBox *cbStimulatingMode6NStimulusPeriod;
  TStaticText *stStimulatingMode6NStimulationTime;
  TComboBox *cbStimulatingMode6NStimulationTime;
  TStaticText *stStimulatingMode5StimulusPeriod;
  TComboBox *cbStimulatingMode5StimulusPeriod;
  TStaticText *stStimulatingMode3AlternativeIntensity;
  TComboBox *cbStimulatingMode3AlternativeIntensity;
	TStaticText *stStimulatingMode4AlternativeShift;
	TComboBox *cbStimulatingMode4AlternativeShift;
	TStaticText *stStimulatingMode1NoSpecialParams;
	TStaticText *stStimulatingMode7Modulation;
	TComboBox *cbStimulatingMode7Modulation;
  TStaticText *stStimulatingDuration;
  TComboBox *cbStimulatingDuration;
  TComboBox *cbPeakingMeanShortWindowLength;
  TStaticText *stPeakingMeanShortWindowLength;
  TStaticText *stStimulatingMode2NoSpecialParams;
  TOpenDialog *dlgOpenInputFile;
  TStaticText *stPeakingThresholdLevelFixed;
  TComboBox *cbPeakingThresholdLevelFixed;
  TTabSheet *tsStimulatingMode8;
  TStaticText *stStimulatingMode8StimulusPeriod;
  TComboBox *cbStimulatingMode8StimulusPeriod;
  TStaticText *stStimulatingMode8ParadigmType;
  TComboBox *cbStimulatingMode8ParadigmType;
  TStaticText *stPeakingThresholdLevelType;
  TComboBox *cbPeakingThresholdLevelType;
  TStaticText *stStimulatingVideoSet;
  TComboBox *cbStimulatingVideoSet;
  TStaticText *stStimulatingAudioSet;
  TComboBox *cbStimulatingAudioSet;
  TTabSheet *tsStimulatingMode9;
  TTabSheet *tsStimulatingMode10;
  TStaticText *stStimulatingMode9ParadigmType;
  TComboBox *cbStimulatingMode9ParadigmType;
  TStaticText *stStimulatingMode9StimulusNumber;
  TStaticText *stStimulatingMode9StimulusPeriod;
  TComboBox *cbStimulatingMode9StimulusNumber;
  TComboBox *cbStimulatingMode9StimulusPeriod;
  TStaticText *stStimulatingMode10ParadigmType;
  TComboBox *cbStimulatingMode10ParadigmType;
  TStaticText *stStimulatingMode10ShockType;
  TComboBox *cbStimulatingMode10ShockType;
  TStaticText *stStimulatingMode10AnalysisTime;
  TComboBox *cbStimulatingMode10AnalysisTime;
  TGroupBox *cbPatterning;
  TStaticText *stPatterningPeakParamMin;
  TComboBox *cbPatterningPeakParamMax;
  TStaticText *stPatterningPeakType;
  TComboBox *cbPatterningPeakType;
  TComboBox *cbPatterningPeakParamMin;
  TStaticText *stPatterningPeakParamSpace;
  TStaticText *stPatterningPeakParamMax;
  TComboBox *cbPatterningPeakParamSpace;
  TGroupBox *gbMiscellaneous;
  TStaticText *stMiscellaneousPort;
  TComboBox *cbMiscellaneousPort;
  TStaticText *stMiscellaneousFilterType;
  TComboBox *cbMiscellaneousFilterType;
  TStaticText *stMiscellaneousFilterFc1;
  TComboBox *cbMiscellaneousFilterFc1;
  TStaticText *stMiscellaneousFilterFc2;
  TComboBox *cbMiscellaneousFilterFc2;
  TStaticText *stPeakingMeanLongWindowLength;
  TComboBox *cbPeakingMeanLongWindowLength;
  TStaticText *stPeakingCommandParameter;
  TComboBox *cbPeakingCommandParameter;
  TStaticText *stPeakingThresholdLevelFloatMax;
  TStaticText *stPeakingThresholdLevelFloatMin;
  TComboBox *cbPeakingThresholdLevelFloatMax;
  TComboBox *cbPeakingThresholdLevelFloatMin;
  TComboBox *cbSoundType;
  TEdit *edSoundFileName;
  TOpenDialog *dlgOpenSoundFile;
  TSpeedButton *sbSoundFileName;
  TSpeedButton *sbSoundTest;
  TStaticText *stSoundFileName;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sbOutputFileNameClick(TObject *Sender);
	void __fastcall sbInputFileNameClick(TObject *Sender);
	void __fastcall cbTrainingModeChange(TObject *Sender);
	void __fastcall bnApplyClick(TObject *Sender);
	void __fastcall bnCancelClick(TObject *Sender);
  void __fastcall cbPortChange(TObject *Sender);
  void __fastcall pcStimulatingModeChange(TObject *Sender);
  void __fastcall cbPeakingThresholdLevelTypeChange(TObject *Sender);
  void __fastcall cbPeakingCommandParameterChange(TObject *Sender);
  void __fastcall sbSoundFileNameClick(TObject *Sender);
  void __fastcall cbSoundTypeChange(TObject *Sender);
  void __fastcall sbSoundTestClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfmSettings(TComponent* Owner);
  void __fastcall InitItemsForOperatingMode();
  void __fastcall EnableItemsForOperatingMode();
  void __fastcall EnableItemsForTrainingMode();
  void __fastcall CheckPort(AnsiString aPort);
  bool __fastcall GetFileParams(AnsiString aFileName, bool bMessage);
  AnsiString __fastcall GetShortFileName(AnsiString aFileName);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmSettings *fmSettings;
//---------------------------------------------------------------------------
#endif
