//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "UMain.h"
#include "USpectrum.h"
#include <stdio.h>
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmSpectrum *fmSpectrum;
//---------------------------------------------------------------------------
__fastcall TfmSpectrum::TfmSpectrum(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
// Function: LoadSpectrumData
//---------------------------------------------------------------------------
bool __fastcall TfmSpectrum::LoadSpectrumData()
{
  // Vars
  int i;
  FILE *pFileStream;
  int nFileLineCount = 0;
  int nFileBeginShift;
  int iValue0, iValue1, iValue2, iValue3, iValue4, iValue5, iValue6;

  // Open file
  if ((pFileStream = fopen(fmMain->m_aOutputFileName.c_str(), "rt")) == NULL)
    return false;
  // Count file lines
  while (true)
  {
    if (feof(pFileStream))
      break;
  	if (fgetc(pFileStream) == '\n')
    	nFileLineCount += 1;
  }
  // Allocate
  m_nSpectrumDataLength = nFileLineCount - 1;
  m_pSpectrumData = new short [m_nSpectrumDataLength];
  // Set file position
  fseek(pFileStream, 0, SEEK_SET);
  while (true)
  {
    if (fgetc(pFileStream) == '\n')
    {
      nFileBeginShift = ftell(pFileStream) + 1;
      fseek(pFileStream, nFileBeginShift, SEEK_SET);
      break;
    }
  }
  // Init spectrum data
  for (i = 0; i < m_nSpectrumDataLength; i++)
 	{
   	fscanf(pFileStream, "%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
    	&iValue0, &iValue1, &iValue2, &iValue3, &iValue4, &iValue5, &iValue6);
		m_pSpectrumData[i] = (short)iValue0;
  }
  // Close file
  fclose(pFileStream);

  return true;
}
//---------------------------------------------------------------------------
// Function: CalcSpectrumShape
//---------------------------------------------------------------------------
void __fastcall TfmSpectrum::CalcSpectrumShape()
{
  int i, j, k, nIndex;
  double fCosComponent, fSinComponent;
  double fSpectrumData;
  double fSpectrumMaxValue;
  int nSampleBlockLength = 2 * fmMain->m_nSampleRate;
  int nSampleBlockNumber = m_nSpectrumDataLength / nSampleBlockLength;
  double *pSpectrumBlock = new double [nSampleBlockLength];

  // Allocate
  m_nSpectrumLoFreq = 4;
  m_nSpectrumHiFreq = 24;
  m_nSpectrumShapeLength = 2 * (m_nSpectrumHiFreq - m_nSpectrumLoFreq);
  m_pSpectrumShape = new double [m_nSpectrumShapeLength];
  for (i = 0; i < m_nSpectrumShapeLength; i++)
    m_pSpectrumShape[i] = 0.0;

  // Routine
  for (k = 0; k < nSampleBlockNumber; k++)
  {
    // Init block spectrum data
    for (i = 0; i < nSampleBlockLength; i++)
    {
      nIndex = k * nSampleBlockLength + i;
      pSpectrumBlock[i] = m_pSpectrumData[nIndex];
    }
    // Calc block spectrum shape
    for (i = m_nSpectrumLoFreq; i < (2 * m_nSpectrumHiFreq - m_nSpectrumLoFreq); i++)
    {
      fCosComponent = 0.0;
      fSinComponent = 0.0;
      for (j = 0; j < nSampleBlockLength; j++)
      {
        fSpectrumData = (double)pSpectrumBlock[j];
        fCosComponent = fCosComponent + cos((2 * M_PI / nSampleBlockLength) * i * j) * fSpectrumData;
        fSinComponent = fSinComponent - sin((2 * M_PI / nSampleBlockLength) * i * j) * fSpectrumData;
      }
      m_pSpectrumShape[i - m_nSpectrumLoFreq] = (m_pSpectrumShape[i - m_nSpectrumLoFreq] +
        fabs(fCosComponent) + fabs(fSinComponent));
    }
  }
  // * Normalize *
  fSpectrumMaxValue = 0.0;
  for (i = 0; i < m_nSpectrumShapeLength; i++)
    if (m_pSpectrumShape[i] > fSpectrumMaxValue)
      fSpectrumMaxValue = m_pSpectrumShape[i];
  for (i = 0; i < m_nSpectrumShapeLength; i++)
    m_pSpectrumShape[i] = m_pSpectrumShape[i] / fSpectrumMaxValue;

  // Free
  delete [] pSpectrumBlock;
}
//---------------------------------------------------------------------------
// Function: SpectrumAnalysis
//---------------------------------------------------------------------------
void __fastcall TfmSpectrum::SpectrumAnalysis()
{
  // Load data
  if (!LoadSpectrumData())
  {
    ShowMessage("Load data failed");
    return;
  }
  // Calc spectrum
  CalcSpectrumShape();
}
//---------------------------------------------------------------------------
// Handler: FormShow
//---------------------------------------------------------------------------
void __fastcall TfmSpectrum::FormShow(TObject *Sender)
{
  int i;
  double fDominantFrequency;
  int nDominantPeriod;
  AnsiString aDominantFrequency, aDominantPeriod;

  // Draw spectrum shape
  TPoint *m_ptSpectrumShape = new TPoint [m_nSpectrumShapeLength];
  for (i = 0; i < m_nSpectrumShapeLength; i++)
  {
    m_ptSpectrumShape[i].x = i * (imSpectrum->Width / m_nSpectrumShapeLength);
    m_ptSpectrumShape[i].y = imSpectrum->Height - floor((m_pSpectrumShape[i] * imSpectrum->Height * 7) / 8);
  }
  imSpectrum->Canvas->Polyline(m_ptSpectrumShape, m_nSpectrumShapeLength - 1);
  // Find dominant frequency
  for (i = 0; i < m_nSpectrumShapeLength; i++)
  {
    if (m_pSpectrumShape[i] == 1.0)
    {
      fDominantFrequency = 0.5 * i + m_nSpectrumLoFreq - 2;
      nDominantPeriod = floor(1000 / fDominantFrequency);
      break;
    }
  }
  // Font
  imSpectrum->Canvas->Font->Name = "Tahoma";
  imSpectrum->Canvas->Font->Size = 10;
  // Text
  aDominantFrequency = "F:" + FloatToStr(fDominantFrequency) + " Hz";
  aDominantPeriod = "P:" + IntToStr(nDominantPeriod) + " ms";
  imSpectrum->Canvas->TextOut(4, 4, aDominantFrequency);
  imSpectrum->Canvas->TextOut(4, 20, aDominantPeriod);
}
//---------------------------------------------------------------------------
// Handler: FormClose
//---------------------------------------------------------------------------
void __fastcall TfmSpectrum::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  // Fill
  imSpectrum->Canvas->Brush->Color = clWhite;
  imSpectrum->Canvas->FillRect(imSpectrum->ClientRect);
  // Free
  delete m_ptSpectrumShape;
  delete [] m_pSpectrumData;
  delete [] m_pSpectrumShape;
}
//---------------------------------------------------------------------------

