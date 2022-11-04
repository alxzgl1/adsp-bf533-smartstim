#include "main.h"

#include <fract.h>
#include <math.h>
#include <window.h>

//---------------------------------------------------------------------------
// Function:	InitAudioWavepacket													
//---------------------------------------------------------------------------
void InitAudioWavepacket(void)
{
  int i, j;
  short nArg = 0;
  short nStep = 0x7fff / WAVEFORM_LEN;
	short pAudioWaveform[WAVEFORM_LEN];
	short pWindowForm[WINFORM_LEN * WAVEFORM_LEN];
	short nWindowFormLength = cStimulatingAudioSet;
	short nWavepacketLength = cStimulatingDuration;
	
  // Make audio waveform
  for (i = 0; i < WAVEFORM_LEN; i++)
  {
    nArg += nStep;
    if (nArg < 0x2000) // Quadrant 1
    {
			pAudioWaveform[i] = sin_fr16(nArg * 4); 
    }
		else if (nArg == 0x2000)	
		{
			pAudioWaveform[i] = 0x7fff;
		}
		else if (nArg < 0x6000) // Quadrant 2 and 3
		{
			pAudioWaveform[i] = -sin_fr16((0xc000 + nArg) * 4);
		}
		else // Quadrant 4
		{
			pAudioWaveform[i] = sin_fr16((0x8000 + nArg) * 4);
		}
	}
	
	// Make audio wavepacket 
	for (i = 0; i < (nWavepacketLength * WAVEFORM_LEN); i++)
	{
	  j = i % WAVEFORM_LEN;
	  pAudioWavepacket[i] = pAudioWaveform[j];
	}

	// Modulate audio wavepacket
	gen_hanning_fr16(pWindowForm, 1, nWindowFormLength * WAVEFORM_LEN); 
	for (i = 0; i < ((nWindowFormLength / 2) * WAVEFORM_LEN); i++)
	{
	 	j = nWavepacketLength * WAVEFORM_LEN - i - 1;
	 	pAudioWavepacket[i] = (pAudioWavepacket[i] * pWindowForm[i]) >> 15;
	 	pAudioWavepacket[j] = (pAudioWavepacket[j] * 
	 		pWindowForm[nWindowFormLength * WAVEFORM_LEN - i - 1]) >> 15;
	}
}

//---------------------------------------------------------------------------

