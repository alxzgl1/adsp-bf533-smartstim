//---------------------------------------------------------------------------

#ifndef USpectrumH
#define USpectrumH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfmSpectrum : public TForm
{
__published:	// IDE-managed Components
  TImage *imSpectrum;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
  __fastcall TfmSpectrum(TComponent* Owner);
  // FUNCTIONS
  bool __fastcall LoadSpectrumData();
  void __fastcall CalcSpectrumShape();
  void __fastcall SpectrumAnalysis();
  // VARIABLES
  TPoint *m_ptSpectrumShape;
  short *m_pSpectrumData;
  double *m_pSpectrumShape;
  int m_nSpectrumDataLength;
  int m_nSpectrumShapeLength;
  int m_nSpectrumHiFreq;
  int m_nSpectrumLoFreq;
};
//---------------------------------------------------------------------------
extern PACKAGE TfmSpectrum *fmSpectrum;
//---------------------------------------------------------------------------
#endif
