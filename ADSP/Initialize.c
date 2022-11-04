#include "main.h"

//---------------------------------------------------------------------------
// Function: InitUART
//---------------------------------------------------------------------------
void InitUART()
{
  unsigned short DIVISOR = SCLK / (BAUDRATE * 16);
	
	// Enable UART clock
	*pUART_GCTL = UCEN;
	
	// Read period value and apply formula:  divisor = period / 16 * 8
	*pUART_LCR = DLAB;
	*pUART_DLL = DIVISOR;
	*pUART_DLH = DIVISOR >> 8;

	// Clear DLAB again and set UART frame to 8 bits, no parity, 1 stop bit
	*pUART_LCR = WLS(8);			
}

//---------------------------------------------------------------------------
// Function: EnableUART
//---------------------------------------------------------------------------
void EnableUART()
{
	// Enable interrupt
	*pUART_IER = ERBFI | ETBEI;
}

//---------------------------------------------------------------------------
// Function: WriteUART
//---------------------------------------------------------------------------
void WriteUART(char cData)
{
	while (!(*pUART_LSR & THRE)); 
	*pUART_THR = cData;		
}

//---------------------------------------------------------------------------
// Function: ReadUART
//---------------------------------------------------------------------------
char ReadUART(void)
{
	char cData;
	while (!(*pUART_LSR & DR));
	cData = *pUART_RBR;
	return cData;
}

//---------------------------------------------------------------------------
// Function: InitTIMER0
//---------------------------------------------------------------------------
void InitTIMER0(void)
{
  unsigned short nConvstTime = 5;   // 500 ns
  unsigned long nTimer0Period = (unsigned long)SCLK / nSampleRate;
  unsigned long nTimer0Width = ((unsigned long)nConvstTime * 
  	(SCLK / 1000000)) / 10;
  
  // Timer0: Start shift
  *pTIMER0_CONFIG		= IRQ_ENA | PERIOD_CNT | PWM_OUT; 
  *pTIMER0_PERIOD		= nTimer0Period; 
  *pTIMER0_WIDTH    = nTimer0Width;
  *pTIMER_ENABLE 		= TIMEN0;
}

//---------------------------------------------------------------------------
// Function: InitTIMER1			
//---------------------------------------------------------------------------
void InitTIMER1(void)
{
	unsigned long nTimer1Period = (unsigned long)cStimulatingDuration * 8 *
		(SCLK / 1000);
 	unsigned long nTimer1Width = ((unsigned long)cStimulatingDuration * 8 *
  	(SCLK / 1000) * (1 << (cStimulatingIntensity - 1)) * cStimulatingIntensity) / 80;
  	
  // Timer1: Control duty cycle of PWM		
	*pTIMER1_CONFIG		= IRQ_ENA | PERIOD_CNT | PULSE_HI | PWM_OUT;
	*pTIMER1_PERIOD		= nTimer1Period;
	*pTIMER1_WIDTH		= nTimer1Width;
}

//---------------------------------------------------------------------------
// Function: InitTIMER2			
//---------------------------------------------------------------------------
void InitTIMER2(void)
{
 	unsigned long nTimer2Period = 50 * (SCLK / 1000); // 50 ms
 	unsigned long nTimer2Width = 25 * (SCLK / 1000);
  	
  // Timer2: Control current stimulator	
	*pTIMER2_CONFIG		= IRQ_ENA | PERIOD_CNT | PULSE_HI | PWM_OUT;
	*pTIMER2_PERIOD		= nTimer2Period;
	*pTIMER2_WIDTH		= nTimer2Width;
}

//---------------------------------------------------------------------------
// Function: InitFlags			
//---------------------------------------------------------------------------
void InitFlags(void)
{
	*pFIO_DIR	= FLAG_AMP | FLAG_LIGHT | FLAG_SHOCK | FLAG_SYNC;
}

//---------------------------------------------------------------------------
// Function: SetFlags				
//---------------------------------------------------------------------------
void SetFlags(void)
{
  *pFIO_FLAG_S = FLAG_SHOCK; 
	*pFIO_FLAG_C = FLAG_SYNC; 
}

//---------------------------------------------------------------------------
// Function: InitADC			
//---------------------------------------------------------------------------
void InitADC(void)
{
  int i;
  
  // Init ADC flags
  *pFIO_INEN		= FLAG_ADC;
	*pFIO_EDGE		= FLAG_ADC;
	*pFIO_POLAR 	= FLAG_ADC;
	*pFIO_MASKA_D = FLAG_ADC;
	*pFIO_FLAG_C  = FLAG_AMP; 
  
	// Set light
	if (cStimulatingTypeIndex == 0x1 || cTrainingModeIndex == STIM_MODE_10 || 
			cTrainingModeIndex == STIM_MODE_9)
  	*pFIO_FLAG_C = FLAG_LIGHT;
  else
  	*pFIO_FLAG_S = FLAG_LIGHT;
  
  // Init SPI TX 
  *pSPI_CTL = 0x0000;
  *pSPI_BAUD = 0x0040;
  *pSPI_CTL = MSTR | 0x01;
	*pSPI_CTL |= SPE;   
	
  // Dummy write
  *pSPI_TDBR = 0x00;
  for (i = 0; i < 0xf000; i++) asm("nop;");
	// Actual write 
	*pSPI_TDBR = cAmpSettings;
	for (i = 0; i < 0xf000; i++) asm("nop;");
	// Confirm params
	*pFIO_FLAG_S = FLAG_AMP;
	for (i = 0; i < 0x0010; i++) asm("nop;");
  *pFIO_FLAG_C = FLAG_AMP;
}

//---------------------------------------------------------------------------
// Function:	InitEBIU																												
//---------------------------------------------------------------------------
void InitEBIU(void)
{
	*pEBIU_AMBCTL0	= 0x7bb07bb0;
	*pEBIU_AMBCTL1	= 0x7bb07bb0;
	*pEBIU_AMGCTL	|= 0x000f;
}

//---------------------------------------------------------------------------
// Function:	InitFlash											
//---------------------------------------------------------------------------
void InitFlash(void)
{
  *pFlashA_PortA_Data = 0x00;
  *pFlashA_PortA_Dir = 0xffff;
  *pFlashA_PortB_Dir = 0x3f;
}

//---------------------------------------------------------------------------
// Function:	InitAD1836											
//---------------------------------------------------------------------------
void InitAD1836(void)
{
	int i;
	
	// Reset and enable AD1836
	*pFlashA_PortA_Data = 0x00;
	*pFlashA_PortA_Data = 0x01; 
	for (i = 0; i < 0xf000; i++) 
		asm("nop;");
	
	// Init SPI
	*pSPI_CTL = 0x0000;
	*pSPI_FLG = FLS4;	
	*pSPI_BAUD = 0x0040;
	*pSPI_CTL = 0x01 | SIZE | MSTR | SPE;
	
	// Init audiocodec 
	*pSPI_TDBR = 0x0000;
	for (i = 0; i < 0xf000; i++) 
		asm("nop;");
	*pSPI_TDBR = DAC1L_VOLUME	| 0x03ff; 
	for (i = 0; i < 0xf000; i++) 
		asm("nop;");
	*pSPI_TDBR = DAC1R_VOLUME	| 0x03ff;
	for (i = 0; i < 0xf000; i++) 
		asm("nop;");
	*pSPI_TDBR = DAC2L_VOLUME	| 0x03ff; 
	for (i = 0; i < 0xf000; i++) 
		asm("nop;");
	*pSPI_TDBR = DAC2R_VOLUME	| 0x03ff;
	for (i = 0; i < 0xf000; i++) 
		asm("nop;");
		
	// Disable spi
	*pSPI_CTL = 0x0000;
}

//---------------------------------------------------------------------------
// Function:	InitSPORT0																																		
//---------------------------------------------------------------------------
void InitSPORT0(void)
{
	// Sport0 transmit configuration
	*pSPORT0_TCR1 = TFSR | LTFS | LATFS | TCKFE;
	*pSPORT0_TCR2 = SLEN_24 | TXSE | TSFSE;
}

//---------------------------------------------------------------------------
// Function:	InitSPORT0DMA												
//---------------------------------------------------------------------------
void InitSPORT0DMA(void)
{
	// Map DMA2 to Sport0 TX
	*pDMA2_PERIPHERAL_MAP = 0x2000;
	
	// Config DMA2
	*pDMA2_CONFIG = FLOW_1 | DI_EN | WDSIZE_32;
	*pDMA2_START_ADDR = (void *)pSport0DMABuffer;
	*pDMA2_X_COUNT = 4;
	*pDMA2_X_MODIFY = 4;
}

//---------------------------------------------------------------------------
// Function:	EnableSPORT0DMA										
//---------------------------------------------------------------------------
void EnableSPORT0DMA(void)
{
	// Enable DMA
	*pDMA2_CONFIG	|= DMAEN;
}

//---------------------------------------------------------------------------
// Function:	InitSPI																															
//---------------------------------------------------------------------------
void InitSPI()
{
	// Init SPI RX 
  *pSPI_CTL = 0x0000;
  *pSPI_BAUD = 0x0040;
  *pSPI_CTL = MSTR | CPHA | SIZE | SZ;
	*pSPI_CTL |= SPE; 
}

//---------------------------------------------------------------------------
// Function: InitSCLK
//---------------------------------------------------------------------------
void InitSCLK(void)
{
	unsigned short nPLLCTL, nPLLDIV; // Temp variables	
	unsigned short MSEL, SSEL, DF, VCO;
	
	nPLLCTL = *pPLL_CTL;
	nPLLDIV = *pPLL_DIV;

	//get MSEL, SSEL, DF
	MSEL = ((nPLLCTL & 0x7E00) >> 9);
	SSEL = nPLLDIV & 0x000f;
	DF = nPLLCTL & 0x0001;
	
	if (DF == 1) CLKIN = CLKIN / 2;
	
	VCO = MSEL * CLKIN;
	SCLK = VCO / SSEL;  
	SCLK = SCLK * 1000000;
}

//---------------------------------------------------------------------------
// Function:	InitADV7171
//---------------------------------------------------------------------------
void InitADV7171(void)
{
	// De-assert reset from ADV7171 device (flashA portA bit 2) 
	*pFlashA_PortA_Data = RST_ADV7171;
}

//---------------------------------------------------------------------------
// Function:	InitSDRAM
//---------------------------------------------------------------------------
void InitSDRAM(void)
{
	// Check whether SDRAM is enabled already.
	if ((*pEBIU_SDSTAT & 0x0008) != 0x0008)
		return;							// Return if already enabled

	// Initalize SDRAM registers.
	*pEBIU_SDRRC  = 0x0817;				// 406, SDRAM Refresh Rate Control Register
	*pEBIU_SDBCTL = 0x0013;				// SDRAM Memory Bank Control Register
	*pEBIU_SDGCTL = 0x0091998d;		// SDRAM Memory Global Control Register
}

//---------------------------------------------------------------------------
// Function:	InitPPIDMA
//---------------------------------------------------------------------------
void InitPPIDMA(void)
{
  *pDMA0_PERIPHERAL_MAP = 0x0000;
	*pDMA0_START_ADDR = SDRAM_START_ADDR;
	*pDMA0_CONFIG = FLOW_1 | DI_EN | DMA2D;
	*pDMA0_X_COUNT	= 0x06b4;
	*pDMA0_Y_COUNT	= 0x020D;
	*pDMA0_X_MODIFY	= 0x0001;
	*pDMA0_Y_MODIFY	= 0x0001;
}

//---------------------------------------------------------------------------
// Function:	EnablePPIDMA
//---------------------------------------------------------------------------
void EnablePPIDMA(void)
{
	*pDMA0_CONFIG |=  DMAEN;
}

//---------------------------------------------------------------------------
// Function:	InitPPI
//---------------------------------------------------------------------------
void InitPPI(void)
{
	// PPI Control Register:  Output direction, 656 mode.	
	*pPPI_CONTROL = PORT_DIR;
}

//---------------------------------------------------------------------------
// Function:	EnablePPI
//---------------------------------------------------------------------------
void EnablePPI(void)
{
	// PPI Control Register:  Output direction, 656 mode.
	*pPPI_CONTROL |= PORT_EN;
}

//---------------------------------------------------------------------------
// Function: InitInterrupts
//---------------------------------------------------------------------------
void InitInterrupts(void)
{
	// Assign core IDs to interrupts
	*pSIC_IAR0 = 0xffffffff;
	*pSIC_IAR1 = 0xf3fff2f1;
	*pSIC_IAR2 = 0xffff5064;
	
	// Assign ISRs to interrupt vectors
	register_handler(ik_ivg7, TIMER2_ISR);
	register_handler(ik_ivg8, PPI_TX_ISR);
	register_handler(ik_ivg9, SPORT0_TX_ISR);
	register_handler(ik_ivg10, UART_RX_ISR);
	register_handler(ik_ivg11, TIMER0_ISR);
	register_handler(ik_ivg12, FLAG0_ISR);		
	register_handler(ik_ivg13, TIMER1_ISR);		

	// Enable
	*pSIC_IMASK = 0x000f4500;
}

//---------------------------------------------------------------------------
// Function: InitOperationMode
//---------------------------------------------------------------------------
void InitOperationMode(void)
{
  if (cOperatingModeIndex == 0)
	{
  	InitADC();
	}
}

//---------------------------------------------------------------------------
// Function: InitStimulationType
//---------------------------------------------------------------------------
void InitStimulationType(void)
{
  // Common mode
  cStimulatingEnable = 1;
  if (cStimulatingTypeIndex == 0x0)
  	cStimulatingEnable = 0;

  // Other
  if (cTrainingModeIndex == STIM_MODE_10) /* Mode 10 */
  {
    if (cStimulatingMode10ParadigmTypeIndex == MODE10_RELAX_PAST_TIME_SHOCK ||
    		cStimulatingMode10ParadigmTypeIndex == MODE10_RELAX_SAME_TIME_SHOCK)
    {
    	// Light
 	  	cStimulatingIntensity = 2; // Non variable
  		InitTIMER1();			
  		// Sound
 	  	cStimulatingIntensity = 5; // Non variable
 			InitAudioWavepacket();
			InitAD1836();
			InitSPORT0();
			InitSPORT0DMA();
			// Shock
			nShockImpulseValue = 10;
   		InitTIMER2();
    }
    else if (cStimulatingMode10ParadigmTypeIndex == MODE10_ONLY_SHOCK)
    {
      // Sound
 	  	cStimulatingIntensity = 5; // Non variable
 			InitAudioWavepacket();
			InitAD1836();
			InitSPORT0();
			InitSPORT0DMA();
      // Shock
      nShockImpulseValue = 10;
   		InitTIMER2();
    }
   	// Specific
   	cStimulatingTypeIndex = 0x0;
  }
  else if (cTrainingModeIndex == STIM_MODE_9) /* Mode 9 */ 
  {
    // Light
  	InitTIMER1();			
  	// Sound
 		InitAudioWavepacket();
		InitAD1836();
		InitSPORT0();
		InitSPORT0DMA();
		// Shock
		nShockImpulseValue = 10;
   	InitTIMER2();
   	// Specific
   	cStimulatingTypeIndex = 0x0;
  }
  else /* General mode */
  {
 		if (cStimulatingTypeIndex == 0x1) // Light
 		{
	  	InitTIMER1();
	  }
	  if (cStimulatingTypeIndex == 0x2) // Sound
	  {
 			InitAudioWavepacket();
			InitAD1836();
			InitSPORT0();
			InitSPORT0DMA();
 		}
 		if (cStimulatingTypeIndex == 0x3) // Color
 		{
	  	InitADV7171();
			InitSDRAM();   
			InitVideoFrame();
			InitPPIDMA();
			InitPPI();
 		}
 		if (cStimulatingTypeIndex == 0x4) // Shock
 		{
	    nShockImpulseValue = 2;
   		InitTIMER2();
 		}
  }

  /* Mode specific */
  if (cTrainingModeIndex == STIM_MODE_8) // Mode 8
  {
    if (cStimulatingMode8ParadigmTypeIndex == 1)
    	cTrainingModeIndex = STIM_MODE_8A; 		// Smooth-peak power control
    if (cStimulatingMode8ParadigmTypeIndex == 2)
    	cTrainingModeIndex = STIM_MODE_8B; 		// Smooth-peak freq control
    if (cStimulatingMode8ParadigmTypeIndex == 3)
    	cTrainingModeIndex = STIM_MODE_8C;		// Smooth-peak power-freq control
  }
}

//---------------------------------------------------------------------------
// Function: EnableStimulationType
//---------------------------------------------------------------------------
void EnableStimulationType(void)
{
  if (cStimulatingTypeIndex == 0x2) // Sound
  {
  	EnableSPORT0DMA();
		*pSPORT0_TCR1 |= TSPEN;
  }
  if (cStimulatingTypeIndex == 0x3) // Color
  {
  	EnablePPIDMA();
		EnablePPI(); 
  }
  // Mode specific
  if (cTrainingModeIndex == STIM_MODE_10 || cTrainingModeIndex == STIM_MODE_9)
  {
  	EnableSPORT0DMA(); 
  	*pSPORT0_TCR1 |= TSPEN; 
  }
}

//---------------------------------------------------------------------------
