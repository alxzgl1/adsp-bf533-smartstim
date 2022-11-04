#include "main.h"

#include <fract.h>
#include <filter.h>

// FFT
complex_fract16 pFFTTemp[FFT_SIZE];
complex_fract16 pFFTInput[FFT_SIZE];
complex_fract16 pFFTTwiddle[FFT_SIZE / 2];

//---------------------------------------------------------------------------
// Function: InitFFTFiltering
//---------------------------------------------------------------------------
void InitFFTFiltering()
{
  twidfftrad2_fr16(pFFTTwiddle, FFT_SIZE);
}

//---------------------------------------------------------------------------
// Function: FFTFiltering
//---------------------------------------------------------------------------
short FFTFiltering(void)
{
  int i;
  short nWindowLength = FFT_SIZE / 2;
  short nScaleShift = 4;
	short nFFTHiFreq, nFFTLoFreq;
	short sFLTValue = 0;
	
	/* Compute freqs */
	nFFTHiFreq = (13 * FFT_SIZE) / nSampleRate; 
	nFFTLoFreq = (7 * FFT_SIZE) / nSampleRate;  
	
	/* Init Input */  
	for (i = 0; i < nWindowLength; i++)
	{
	  pFFTInput[i].re = ((pFFTBuffer[i] << nScaleShift));
	}
	for (i = nWindowLength; i < FFT_SIZE; i++)
	{
	  pFFTInput[i].re = 0;
	}
	
	/* Compute Direct FFT */
	cfft_fr16(pFFTInput, pFFTTemp, pFFTInput, pFFTTwiddle, 1, FFT_SIZE, 0, 0);
	
	/* Filtering */
	for (i = 0; i < (FFT_SIZE / 2); i++)
	{
		if (i < nFFTLoFreq || i > nFFTHiFreq) 
		{
			pFFTInput[i].re = 0;
			pFFTInput[FFT_SIZE - i - 1].re = 0;
		}
	}

	/* Compute Inverse FFT */
	for (i = 0; i < FFT_SIZE; i++)
	{
  	sFLTValue += (short)pFFTInput[i].re;
	}

	/* Return value */
	return (sFLTValue >> (nScaleShift - 1));
}

//---------------------------------------------------------------------------
// Function: PeakDetection
//---------------------------------------------------------------------------
short PeakDetection(void)
{
  int i;
  static short nCount = 0;
  short bValid; 
  
  // Increase count
  if (nCount > 0)
  {
  	nCount -= 1;
  	return 0;
  }
    
	if (nCount == 0)
	{
	  if (pPeakBuffer[1] >= nPeakThresholdLevelNoise)
	  {
	  	if (pPeakBuffer[1] >= pPeakBuffer[0] && 
	  		pPeakBuffer[1] > pPeakBuffer[2])
	  	{
	   		bValid = 1;
	   		for (i = 2; i < (PEAK_SIZE - 1); i++)
	   		{
	     		if (pPeakBuffer[i] < pPeakBuffer[i + 1])
	     		{
	       		bValid = 0;
	       		break;
	     		}
	   		}
	   		nCount = nPeakDeadTime * bValid;
	   		return pPeakBuffer[1] * bValid;
	  	}
	  }
	}
 	return 0; 
}

//---------------------------------------------------------------------------



