#include "main.h"

//---------------------------------------------------------------------------
// Function:	FLAG0_ISR																										
//---------------------------------------------------------------------------
EX_INTERRUPT_HANDLER(FLAG0_ISR)
{
  static short nCount = 0;
 	short sADCValue;
 	
	// Confirm interrupt handling
	*pFIO_FLAG_C = 0x0001;

	/* Get sample from ADC */
	sADCValue = *pSPI_RDBR;
	sADCValue = sADCValue - ((sADCValue & 0x0800) << 1);
	
	/* Blinking */
	nCount += 1;
	if (nCount == (nSampleRate / 2))
	{
	  LEDBlinking(SS_RUN);
	  nCount = 0;
	}
	
	/* Processing */
	if (!bProcessingState && bTrainingState)
	{
	  bProcessingState = 1;
		Processing(sADCValue);
	}	
}

//---------------------------------------------------------------------------
// Function:	UART_RX_ISR																									
//---------------------------------------------------------------------------
EX_INTERRUPT_HANDLER(UART_RX_ISR)
{
  static short nCount = 0;
  short sPCValue;
  unsigned char cHiByte, cLoByte;
  
  // Read
	cHiByte = ReadUART();
  cLoByte = ReadUART();
  
  // Blinking 
	nCount += 1;
	if (nCount == (nSampleRate / 2))
	{
	 	LEDBlinking(SS_RUN);
	 	nCount = 0;
	}
  // Decode command 
  if (cHiByte == 0x60)	// Code: 0x60 (Terminate)
  {
  	LEDBlinking(SS_HALT);
    bTrainingState = 0;  
  }
  else if (cHiByte == 0x41) // Change noise level
  	nPeakThresholdLevelNoise = (short)cLoByte * 4; 
  else if (cHiByte == 0x42) // Change fixed level
  	nPeakThresholdLevelFixed = (short)cLoByte * 4;
  else if (cHiByte == 0x43) // Change float level
  	nPeakThresholdLevelFloat = (short)cLoByte * 4;
  else if (cHiByte == 0x44) // Change float level max limit
  	nPeakThresholdLevelFloatMin = (short)cLoByte * 4;
  else if (cHiByte == 0x45) // Change float level min limit
  	nPeakThresholdLevelFloatMax = (short)cLoByte * 4;	
  else if (cHiByte == 0x46) // Change pattern peak min
  	cPatterningPeakParamMin = cLoByte;
  else if (cHiByte == 0x47) // Change pattern peak max
  	cPatterningPeakParamMax = cLoByte;
  else if (cHiByte == 0x48) // Change pattern peak space
  	cPatterningPeakParamSpace = cLoByte;
  else if (cHiByte == 0x49) // Correct mode 10 shock type
  	cCorrectingMode10Shock = cLoByte;	
  else if (cHiByte == 0x4f) // Started
  	bStarted = 1;
  else	// Offline processing
  {
    sPCValue = (short)(cHiByte << 8) | (short)(cLoByte & 0xFF);
    if (cOperatingModeIndex == 1)
  	{ 
			if (!bProcessingState && bTrainingState)
			{
				bProcessingState = 1;
				Processing(sPCValue);
			}		
  	}
  }
}

//---------------------------------------------------------------------------
// Function:	TIMER0_ISR																										
//---------------------------------------------------------------------------
EX_INTERRUPT_HANDLER(TIMER0_ISR)
{
  // Confirm Timer0 interrupt
	*pTIMER_STATUS |= TIMIL0;  
	
	if (cOperatingModeIndex == 1)
		WriteUART(0x00);
}

//---------------------------------------------------------------------------
// Function:	TIMER1_ISR																										
//---------------------------------------------------------------------------
EX_INTERRUPT_HANDLER(TIMER1_ISR)
{
  // Confirm Timer1 interrupt
  *pTIMER_STATUS |= TIMIL1;
  *pTIMER_DISABLE = TIMDIS1;
}

//---------------------------------------------------------------------------
// Function:	TIMER2_ISR																										
//---------------------------------------------------------------------------
EX_INTERRUPT_HANDLER(TIMER2_ISR)
{
  // Confirm Timer2 interrupt
  *pTIMER_STATUS |= TIMIL2;
  
  if (nShockImpulseCount > 0)
  {
  	nShockImpulseCount -= 1;
  	*pFIO_FLAG_T = FLAG_SHOCK;
  	// Disable shock
  	if (nShockImpulseCount == 0)
  	{
  	  *pFIO_FLAG_S = FLAG_SHOCK;
  	  *pTIMER_DISABLE = TIMDIS2;
  	}
  }
}

//---------------------------------------------------------------------------
// Function:	SPORT0_TX_ISR												
//---------------------------------------------------------------------------
EX_INTERRUPT_HANDLER(SPORT0_TX_ISR)
{
	// Confirm interrupt handling
	*pDMA2_IRQ_STATUS = DMA_DONE;

  static short nWavepacketIndex = 0;
  
  pSport0DMABuffer[INTERNAL_DAC_L1] = pAudioWavepacket[nWavepacketIndex] << (cStimulatingIntensity + 2);
  pSport0DMABuffer[INTERNAL_DAC_L0] = pAudioWavepacket[nWavepacketIndex] << (cStimulatingIntensity + 2);
	
	nWavepacketIndex += 1;
	if (nWavepacketIndex > (cStimulatingDuration * 8 * WAVEFORM_LEN - 1))
	{
	  *pSPORT0_TCR1 = TFSR | LTFS | LATFS | TCKFE;
	  nWavepacketIndex = 0;
	}
}

//------------------------------------------------------------------------------
// Function:	PPI_TX_ISR			
//------------------------------------------------------------------------------
EX_INTERRUPT_HANDLER(PPI_TX_ISR)
{
  // Wait when output buffer be empty
	*pDMA0_IRQ_STATUS = DMA_DONE;
	
  static short nPrevVideoColorState = 0;
	int i;
	
	if (nPrevVideoColorState != bVideoColorState)
	{
	  *pPPI_CONTROL = PORT_DIR;
	  for (i = 0; i < 0x0040; i++) asm("nop;");
	  
		if (bVideoColorState == 1)
		{
	  	*pDMA0_CONFIG = FLOW_1 | DI_EN | DMA2D;
	 		*pDMA0_START_ADDR = 0x00200000;
	 		*pDMA0_CONFIG =  FLOW_1 | DI_EN | DMA2D | DMAEN;
	 		*pPPI_CONTROL = PORT_DIR | PORT_EN;
		}
		if (bVideoColorState == 0)
		{
	 		*pDMA0_CONFIG = FLOW_1 | DI_EN | DMA2D;
	 		*pDMA0_START_ADDR = 0x00000000;
	 		*pDMA0_CONFIG =  FLOW_1 | DI_EN | DMA2D | DMAEN;
	 		*pPPI_CONTROL = PORT_DIR | PORT_EN;
		}
		nPrevVideoColorState = bVideoColorState;
	}	
}

//---------------------------------------------------------------------------

