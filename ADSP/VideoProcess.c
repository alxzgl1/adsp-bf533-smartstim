#include "main.h"

//------------------------------------------------------------------------------
// Function:	InitVideoFrame
//------------------------------------------------------------------------------
void InitVideoFrame(void)
{
	int i, j, k;
	int nVideoLineCount = 525;
	volatile unsigned int *pVideoFrame;
	unsigned int nVideoColorCode;
	/*
	unsigned int pVideoColorPalette[8] = {
	  0xAA10AAA6,		// Cyan
  	0x91229136,		// Green
		0xD292D210,		// Yellow
		0x296E29F0,		// Blue
		0x51F0515A,		// Red
		0x6ADE6ACA,		// Magenta
		0xEB80EB80,		// White
		0x10801080};	// Black 
	*/
	unsigned int pVideoColorPalette[8] = {
	  0x7D807D80,		// Gray
  	0x837C839C,		// Gray-Blue 1
  	0x7D807D80,		// Gray
		0x897889B7,		// Gray-Blue 2
		0x7D807D80,		// Gray
		0x882888B7,		// Gray-Blue 3
		0x7D807D80,		// Gray
		0x785B78C1};	// Gray-Blue 4

	// Init color # 1
	pVideoFrame = (volatile unsigned int *)0x00000000;
	nVideoColorCode = pVideoColorPalette[cStimulatingVideoSet * 2 - 2];
	for (k = 0; k < nVideoLineCount; k++)
		pVideoFrame = 
			(volatile unsigned int *)InitVideoLine(pVideoFrame, k + 1, nVideoColorCode);
	// Init color # 2
	pVideoFrame = (volatile unsigned int *)0x00200000;
	nVideoColorCode = pVideoColorPalette[cStimulatingVideoSet * 2 - 1];
	for (k = 0; k < nVideoLineCount; k++)
		pVideoFrame = 
			(volatile unsigned int *)InitVideoLine(pVideoFrame, k + 1, nVideoColorCode);
}

//---------------------------------------------------------------------------
// Function:	InitVideoLine
//---------------------------------------------------------------------------
unsigned int InitVideoLine(volatile unsigned int *pVideoFrame,  
	unsigned int nVideoLine, unsigned int nVideoColorCode)
{
	int i;
	static bool V = 1, F = 1;
	
	// V-digital field blanking (NTSC)
	if (nVideoLine == 1)   // Start  / Field 1  
		V = 1;	
	if (nVideoLine == 20)  // Finish / Field 1 
		V = 0;	
	if (nVideoLine == 264) // Start  / Field 2 
		V = 1;	
	if (nVideoLine == 283) // Finish / Field 2
		V = 0;	
	// F-digital field identification (NTSC)
	if (nVideoLine == 4)   // Field 1
		F = 0;	
	if (nVideoLine == 266) // Field 2
		F = 1;
	
	// End Active Video (EAV)
	if (V & F)
		*pVideoFrame++ = 0xF10000FF;
	if (!V & F)
		*pVideoFrame++ = 0xDA0000FF;
	if (V & !F)
		*pVideoFrame++ = 0xB60000FF;
	if (!V & !F)
		*pVideoFrame++ = 0x9D0000FF;
		
	// Output horizontal blanking 
	for	(i = 0; i < 67; i++)
		*pVideoFrame++ = 0x10801080;

	// Start Active Video (SAV)
	if (V & F)
		*pVideoFrame++ = 0xEC0000FF;
	if (!V & F)
		*pVideoFrame++ = 0xC70000FF;
	if (V & !F)
		*pVideoFrame++ = 0xAB0000FF;
	if (!V & !F)
		*pVideoFrame++ = 0x800000FF;
		
	// Active Video
	if (V) 	// Output empty horizontal data
	{
		for	(i = 0; i < 360; i++)
			*pVideoFrame++ = 0x10801080;
	}
	else		// Output reference color horizontal data 
	{
		for	(i = 0; i < 360; i++)
			*pVideoFrame++ = nVideoColorCode;
	}

	return (unsigned int)pVideoFrame;
}

//---------------------------------------------------------------------------
