#include "main.h"

//---------------------------------------------------------------------------
// Function: AddSample
//---------------------------------------------------------------------------
void AddSample(short pBuffer[], short sValue, int nSize)
{
  int i;
	for (i = 1; i < nSize; i++)
	{
		pBuffer[nSize - i] = pBuffer[nSize - i - 1];
	}
	pBuffer[0] = sValue;
}

//---------------------------------------------------------------------------
// Function: Transmitting
//---------------------------------------------------------------------------
void Transmitting(short sADCValue, short sFLTValue, short nCMDValue,
	short nThresholdLevelValue, short nShiftValue, short nModeDependentValue)
{
  char cHiByte, cLoByte, cOpByte;
  
  /* Write to port */
	// ADC
  cHiByte = (char)(sADCValue >> 8);
	cLoByte = (char)(sADCValue & 0xFF);
	WriteUART(cHiByte);  
  WriteUART(cLoByte);
	// FLT 
  cHiByte = (char)(sFLTValue >> 8); 
	cLoByte = (char)(sFLTValue & 0xFF);
  WriteUART(cHiByte);
  WriteUART(cLoByte);
  // CMD and Mode dependent hi
  cOpByte = (char)(nModeDependentValue >> 2);
  cHiByte = (char)(nCMDValue >> 8);  
  cHiByte = (cHiByte & 0xF) | (cOpByte << 4); 
	cLoByte = (char)(nCMDValue & 0xFF);
  WriteUART(cHiByte);
  WriteUART(cLoByte);
	// Threshold, Mode dependent lo and Shift
	cOpByte = (char)(nModeDependentValue & 0x3) | (char)(nShiftValue << 2);
	cHiByte = (char)(nThresholdLevelValue >> 8); 
	cHiByte = (cHiByte & 0xF) | (cOpByte << 4);  
	cLoByte = (char)(nThresholdLevelValue & 0xFF);
  WriteUART(cHiByte);
  WriteUART(cLoByte);
	
  /* Confirm bProcessingState */
  bProcessingState = 0;
}

//---------------------------------------------------------------------------
// Function: Stimulating
//---------------------------------------------------------------------------
short Stimulating(short sADCValue, short sFLTValue, short nPeakValue, 
	short nPowerValue, short nThresholdLevelValue)
{
  static short nShiftSampleCount = 0;
  static short nSyncSampleCount = 0;
  static short nSpaceSampleCount = 0;
  static short nVideoOutSampleCount = 0;
  static short nPatternValue = 0;
  static short bMode10Reset = 0;
  short nShiftValue;
	
 	/* Switch training */
 	if (bStarted)
 	{
 		switch (cTrainingModeIndex)
  	{
	    case STIM_MODE_1: // Peak-wave stimulation
    	{
	      nShiftSampleCount = Mode1Routine(nPeakValue, nShiftSampleCount);
      	break;
    	}
    	case STIM_MODE_2: // Peak-wave threshold stimulation
    	{	
    	 	nShiftSampleCount = Mode2Routine(nPeakValue, nThresholdLevelValue, nShiftSampleCount);
      	break;
    	}
    	case STIM_MODE_3: // Peak-wave power control stimulation
    	{
      	nShiftSampleCount = Mode3Routine(nPeakValue, nThresholdLevelValue, nShiftSampleCount);
      	break;
    	}
    	case STIM_MODE_4: // Peak-wave shift control stimulation
    	{
	      nShiftSampleCount = Mode4Routine(nPeakValue, nThresholdLevelValue, nShiftSampleCount);
      	break;
    	}
    	case STIM_MODE_5: // Rhythmic simple stimulation
    	{
	      nShiftSampleCount = Mode5Routine(nPeakValue, nShiftSampleCount);
      	break;
    	}
    	case STIM_MODE_6N: // Rhythmic adaptive stimulation
    	{
	      // nShiftSampleCount = Mode6Routine(nPeakValue, nThresholdLevelValue, nShiftSampleCount);
      	nShiftSampleCount = Mode6NRoutine(nPeakValue, nThresholdLevelValue, nShiftSampleCount);
      	break;
    	}
    	case STIM_MODE_7: // Rhyrhmic frequency control stimulation
    	{
	      nShiftSampleCount = Mode7Routine(nPeakValue, nThresholdLevelValue, nShiftSampleCount);
      	break;
    	}
    	case STIM_MODE_8: // Smooth-wave simple stimulation
    	{
	      nShiftSampleCount = Mode8Routine(nPowerValue, nThresholdLevelValue, nShiftSampleCount);
      	break;
    	}
			case STIM_MODE_9: // Pattern simple paradigm stimulation
			{
				nShiftSampleCount = Mode9Routine(nPatternValue, nShiftSampleCount);
				break;
			}
			case STIM_MODE_10: // Pattern shock paradigm stimulation
			{
				nShiftSampleCount = Mode10Routine(nPatternValue, nShiftSampleCount);
				bMode10Reset = 0;
				if (nShiftSampleCount == 2)
				{
				  bMode10Reset = 1;
			  	nShiftSampleCount = 0;
				}
				break;
			}
			case STIM_MODE_8A: // Smooth-wave power control stimulation
    	{
	      nShiftSampleCount = Mode8ARoutine(nPowerValue, nThresholdLevelValue, nShiftSampleCount);
      	break;
    	}
    	case STIM_MODE_8B: // Smooth-wave frequency control stimulation
    	{
	      nShiftSampleCount = Mode8BRoutine(nPowerValue, nThresholdLevelValue, nShiftSampleCount);
      	break;
    	}
    	case STIM_MODE_8C: // Smooth-wave power and frequency control stimulation
    	{
	      nShiftSampleCount = Mode8CRoutine(nPowerValue, nThresholdLevelValue, nShiftSampleCount);
      	break;
    	}
  	}
 	}
 	
	/* Video out */ // Save previous color if time between peaks less than 140 ms
  if (nVideoOutSampleCount > 0)
  {
    nVideoOutSampleCount -= 1;
    if (nVideoOutSampleCount == 0)
    	bVideoColorState = 0;
  }

  /* Sync */
  if (nSyncSampleCount > 0)
  {
    nSyncSampleCount -= 1;
    if (nSyncSampleCount == 0)
    	*pFIO_FLAG_C = FLAG_SYNC;
  }

  /* Space between peaks */ // Missing single peak or first peak in sequence (it considered as single peak)
  if (nSpaceSampleCount > 0)
  	nSpaceSampleCount -= 1;

	/* Check space between peaks */
	if (cTrainingModeIndex == STIM_MODE_9 || cTrainingModeIndex == STIM_MODE_10)
	{
	  nPatternValue = PatternDetection(nPeakValue, nPowerValue,	nThresholdLevelValue, 
	  	nSpaceSampleCount, bMode10Reset);
		if (nPatternValue == 1) // Detect peak
			nSpaceSampleCount = cPatterningPeakParamSpace * (nSampleRate / 128);	
  }
  else
  {
    if (nShiftSampleCount > 0)
  	{
    	if (nSpaceSampleCount == 0)
				nShiftSampleCount = 0;
    	nSpaceSampleCount = 18 * (nSampleRate / 128);	// 144 ms
		}
  }
  
  /* Init shift */
  nShiftValue = 0;
  if (nShiftSampleCount > 0)
  {
    nShiftSampleCount -= 1;
    if (nShiftSampleCount == 0)
    {
      GenerateStimulus(cStimulatingTypeIndex);
      // Enable Sync
      *pFIO_FLAG_S = FLAG_SYNC;
      nSyncSampleCount = nSampleRate / 128;
      nVideoOutSampleCount = 18 * (nSampleRate / 128); // 144 ms
      nShiftValue = 1;
    }
  }
  
  return nShiftValue; 
}

//---------------------------------------------------------------------------
// Function: GenerateStimulus
//---------------------------------------------------------------------------
void GenerateStimulus(char cStumulusType)
{
  if (bStarted)
  {
  	// Generate Light stimulus
  	if (cStumulusType == STIM_TYPE_LIGHT && cStimulatingEnable == 1)
	  	*pTIMER_ENABLE = TIMEN1;

  	// Generate Sound stimulus
		if (cStumulusType == STIM_TYPE_SOUND)
			*pSPORT0_TCR1 |= TSPEN;

		// Generate Color stimulus
		if (cStumulusType == STIM_TYPE_COLOR)
			bVideoColorState = 1;

		// Generete Shock stimulus
		if (cStumulusType == STIM_TYPE_SHOCK && cStimulatingEnable == 1)
		{
		  nShockImpulseCount = nShockImpulseValue;
			*pTIMER_ENABLE = TIMEN2;
		}
  }
}

//---------------------------------------------------------------------------
// Function: InitMeanShortWindowPeakValue
//---------------------------------------------------------------------------
void InitMeanShortWindowPeakValue()
{
  int i;

  for (i = 0; i < MEAN_SIZE; i++)
	{
		pMeanShortWindowPeakBuffer[i] = (3 * nPeakThresholdLevelNoise) / 2;
	}
	nMeanShortWindowPeakValue = (3 * nPeakThresholdLevelNoise) / 2;
}

//---------------------------------------------------------------------------
// Function: InitMeanLongWindowPeakValue
//---------------------------------------------------------------------------
void InitMeanLongWindowPeakValue()
{
  int i;

  for (i = 0; i < MEAN_SIZE; i++)
	{
		pMeanLongWindowPeakBuffer[i] = (3 * nPeakThresholdLevelNoise) / 2;
	}
	nMeanLongWindowPeakValue = (3 * nPeakThresholdLevelNoise) / 2;
}

//---------------------------------------------------------------------------
// Function: GetMeanShortWindowPeakValue
//---------------------------------------------------------------------------
void GetMeanShortWindowPeakValue(short nPeakValue)
{
  int i;
  static short nSampleCount = 0;
  static long lSumBinValue = 0;
  static short nSumBinCount = 0;
  long lSumBufferValue = 0;
  
  // Check peak
  if (nPeakValue >= nPeakThresholdLevelNoise)
  {
		lSumBinValue += nPeakValue;
		nSumBinCount += 1;
  }
  // Check bin
  nSampleCount += 1;
  if (nSampleCount == cPeakingMeanShortWindowLength * (128 / (8 * MEAN_SIZE)))
  {
		lSumBinValue = (lSumBinValue / nSumBinCount);  
    AddSample(pMeanShortWindowPeakBuffer, (short)lSumBinValue, MEAN_SIZE);
    lSumBufferValue = 0;
    for (i = 0; i < MEAN_SIZE; i++)
    {
      lSumBufferValue += pMeanShortWindowPeakBuffer[i]; 
    }
    nMeanShortWindowPeakValue = (short)(lSumBufferValue / MEAN_SIZE);
    lSumBinValue = 0;
		nSumBinCount = 0;
		nSampleCount = 0;
  }
}

//---------------------------------------------------------------------------
// Function: GetMeanLongWindowPeakValue
//---------------------------------------------------------------------------
void GetMeanLongWindowPeakValue(short nPeakValue)
{
  int i;
  static short nSampleCount = 0;
  static long lSumBinValue = 0;
  static short nSumBinCount = 0;
  long lSumBufferValue = 0;
  
  // Check peak
  if (nPeakValue >= nPeakThresholdLevelNoise)
  {
		lSumBinValue += nPeakValue;
		nSumBinCount += 1;
  }
  // Check bin
  nSampleCount += 1;
  if (nSampleCount == cPeakingMeanLongWindowLength * (1024 / (8 * MEAN_SIZE)))
  {
		lSumBinValue = (lSumBinValue / nSumBinCount);  
    AddSample(pMeanLongWindowPeakBuffer, (short)lSumBinValue, MEAN_SIZE);
    lSumBufferValue = 0;
    for (i = 0; i < MEAN_SIZE; i++)
    {
      lSumBufferValue += pMeanLongWindowPeakBuffer[i]; 
    }
    nMeanLongWindowPeakValue = (short)(lSumBufferValue / MEAN_SIZE);
    lSumBinValue = 0;
		nSumBinCount = 0;
		nSampleCount = 0;
  }
}

//---------------------------------------------------------------------------
// Function: InitMode6NStimulationMask
//---------------------------------------------------------------------------
void InitMode6NStimulationMask()
{
  int i;
  // Rhythmic stimulation
  if ((cStimulatingMode6NStimulationMaskIndex == MODE6N_ACTIVE_RHY) || 
  		(cStimulatingMode6NStimulationMaskIndex == MODE6N_PASSIVE_RHY)) 
    for (i = 0; i < MODE6_STIM_NUM; i++)
    	pMode6StimulationMaskArray[i] = 1;
}

//---------------------------------------------------------------------------
// Function: Mode1Routine
//---------------------------------------------------------------------------
short Mode1Routine(short nPeakValue, short nShiftSampleCount)
{
  if (nPeakValue >= nPeakThresholdLevelNoise)
  {
  	nShiftSampleCount = (pStimulatingShiftArray[cStimulatingShiftIndex] * 
  		nSampleRate) / 1000 + 1;
  }
  return nShiftSampleCount;
}

//---------------------------------------------------------------------------
// Function: Mode2Routine
//---------------------------------------------------------------------------
short Mode2Routine(short nPeakValue, short nThresholdLevelValue, short nShiftSampleCount)
{
 	if (nPeakValue >= nThresholdLevelValue)
  {
   	nShiftSampleCount = (pStimulatingShiftArray[cStimulatingShiftIndex] *
  		nSampleRate) / 1000 + 1;
	}
  return nShiftSampleCount;
}	
	
//---------------------------------------------------------------------------
// Function: Mode3Routine
//---------------------------------------------------------------------------
short Mode3Routine(short nPeakValue, short nThresholdLevelValue, short nShiftSampleCount)
{
  char cIndexLevel;
  
	// Check mode 3 condition		
	if (nPeakValue >= nPeakThresholdLevelNoise)
  {
		if (nPeakValue > nThresholdLevelValue)
			cIndexLevel = cStimulatingIntensityIndex;	
		else
			cIndexLevel = cStimulatingMode3AlternativeIntensityIndex;
		cStimulatingIntensity = pStimulatingIntensityArray[cIndexLevel];
		// Init shift
		nShiftSampleCount = (pStimulatingShiftArray[cStimulatingShiftIndex] * 
			nSampleRate) / 1000 + 1;
		InitTIMER1();
  }
  return nShiftSampleCount;
}

//---------------------------------------------------------------------------
// Function: Mode4Routine
//---------------------------------------------------------------------------
short Mode4Routine(short nPeakValue, short nThresholdLevelValue, short nShiftSampleCount)
{
  char cIndexLevel;
  	
	// Check mode 4 condition	
	if (nPeakValue >= nPeakThresholdLevelNoise)
  {
		if (nPeakValue > nThresholdLevelValue)
			cIndexLevel = cStimulatingShiftIndex;	
		else
			cIndexLevel = cStimulatingMode4AlternativeShiftIndex;
		// Init shift
		nShiftSampleCount = (pStimulatingShiftArray[cIndexLevel] *
			nSampleRate) / 1000 + 1;
  }
  return nShiftSampleCount;
}

//---------------------------------------------------------------------------
// Function: Mode5Routine
//---------------------------------------------------------------------------
short Mode5Routine(short nPeakValue, short nShiftSampleCount)
{
  static short nSampleCount = 0;
  
  nSampleCount += 1;
  if (nSampleCount > nStimulatingMode5StimulusPeriod)
  {
    // Init shift
  	nShiftSampleCount = (pStimulatingShiftArray[cStimulatingShiftIndex] * 
	   	nSampleRate) / 1000 + 1;
	  nSampleCount = 0;
  }
  return nShiftSampleCount;
}

//---------------------------------------------------------------------------
// Function: Mode6Routine
//---------------------------------------------------------------------------
short Mode6Routine(short nPeakValue, short nThresholdLevelValue, short nShiftSampleCount)
{
  int i;
  static short nBandPeakValue = 0;					
  short nBandPeakRatio = nSampleRate / 128;
  static short nPeriodPeakSampleCount = 0;
  static short nFlashDurationSampleCount = 0;	// Internal and External
  static short nBandPeakSampleCount = 0;
   	
  /* Internal flash */
  if (nPeakValue >= nPeakThresholdLevelNoise)
  {
    
	  	
		if (nFlashDurationSampleCount < nStimulatingMode6InternalFlash)
		{		
			if (nPeakValue > nThresholdLevelValue) 
			{
				// Set pMode6PeriodPeakBuffer
				for (i = 0; i < (MODE6_BAND_NUM + 1); i++)
				{
					if ((nPeriodPeakSampleCount <= (i + MODE6_BAND_NUM) * nBandPeakRatio)
						&& (nPeriodPeakSampleCount > (i + MODE6_BAND_NUM - 1) * nBandPeakRatio))
					{
						pMode6PeriodPeakBuffer[i] += 1;
						break;
     			}
    		}
    		nPeriodPeakSampleCount = 0;
    		// Init shift		
    		nShiftSampleCount = (pStimulatingShiftArray[cStimulatingShiftIndex] * 
	      	nSampleRate) / 1000 + 1;
      }
    }
  }
  
  /* External flash */
  nPeriodPeakSampleCount += 1;	
  nFlashDurationSampleCount += 1;
  	  
  // Internal flash 
  if (nFlashDurationSampleCount == nStimulatingMode6InternalFlash)
  {
		// Find max
   	short nMaxValue = 0;
	 	short nMaxIndex = 0;
   	for (i = 0; i < (MODE6_BAND_NUM + 1); i++)
    {
	 		if (nMaxValue < pMode6PeriodPeakBuffer[i])
      {
		  	nMaxValue = pMode6PeriodPeakBuffer[i];
       	nMaxIndex = i;
      }
    }
    nBandPeakValue = nMaxIndex + (short)cStimulatingMode6PeriodVariation + MODE6_BAND_NUM;
    nModeDependentValue = nBandPeakValue; // PeriodPeakValue = BandPeakValue * 1000 / 128
    // Zeroing 
    for (i = 0; i < (MODE6_BAND_NUM + 1); i++)
    {
			pMode6PeriodPeakBuffer[i] = 0;  
    }
  }
  	
  // External flash 
  if (nFlashDurationSampleCount > nStimulatingMode6InternalFlash)
  {
  	nBandPeakSampleCount += 1;
  	if (nBandPeakSampleCount > (nBandPeakValue * nBandPeakRatio)) 
  	{
    	nShiftSampleCount = (pStimulatingShiftArray[cStimulatingShiftIndex] * 
     		nSampleRate) / 1000 + 1;
  		nBandPeakSampleCount = 0;
  	}
  	// Check total time
    if (nFlashDurationSampleCount == (nStimulatingMode6InternalFlash + nStimulatingMode6ExternalFlash))
    {
      nModeDependentValue = 0;
    	nFlashDurationSampleCount = 0;
    }
  }
  return nShiftSampleCount;
}

//---------------------------------------------------------------------------
// Function: Mode6NRoutine
//---------------------------------------------------------------------------
short Mode6NRoutine(short nPeakValue, short nThresholdLevelValue, short nShiftSampleCount)
{
  static short nSampleCount = 0;
  static short nStimulusCount = 0;
  static short nStimulationTimeCount = 0;
  static short bStimulusDirection = 0; // 0 - external, 1 - internal
  
  // Switch direction of stimulation
  nStimulationTimeCount += 1;
  if ((nStimulationTimeCount > nStimulatingMode6NExternalStimulationTime) && (bStimulusDirection == 0))
  {
    nStimulationTimeCount = 0;
  	bStimulusDirection = 1;
  	nStimulusCount = 0;
  }
  if ((nStimulationTimeCount > nStimulatingMode6NInternalStimulationTime) && (bStimulusDirection == 1))
  {
    nStimulationTimeCount = 0;
  	bStimulusDirection = 0;
  	nStimulusCount = 0;
  }

  // Increase count	
  nSampleCount += 1;
  // * External stimulus *
  if (bStimulusDirection == 0)
  {
  	if (nSampleCount > nStimulatingMode6NStimulusPeriod)
  	{
	    nSampleCount = 0;
	    nStimulusCount += 1;
	    nShiftSampleCount = (pStimulatingShiftArray[cStimulatingShiftIndex] *
  			nSampleRate) / 1000 + 1;
	  	nShiftSampleCount = nShiftSampleCount * pMode6StimulationMaskArray[nStimulusCount]; // 0 or 1
  	}
  	nModeDependentValue = 1;
  }	
  // * Internal stimulus *
  else
  {
  	if (nPeakValue >= nThresholdLevelValue)
  	{
	   	nShiftSampleCount = (pStimulatingShiftArray[cStimulatingShiftIndex] *
  			nSampleRate) / 1000 + 1;
  		// Passive stimulation
  		if (cStimulatingMode6NStimulationMaskIndex == MODE6N_PASSIVE_RHY)
  			nShiftSampleCount = 0;	
		}		 
		nModeDependentValue = 0;
  }
  	
  return nShiftSampleCount;
}

//---------------------------------------------------------------------------
// Function: Mode7Routine
//---------------------------------------------------------------------------
short Mode7Routine(short nPeakValue, short nThresholdLevelValue, short nShiftSampleCount)
{
  int i;
  long lPeakSum = 0;									
  static short sSign = 1;
  static short nSampleCount = 0;
  static short nCycleTimeSampleCount = 0;
  static short nPeriodFlashCount = 0;
   	
  // Sum peak value in window
  if (nPeakValue >= nPeakThresholdLevelNoise)
  {
    AddSample(pMode7PeakBuffer, nPeakValue, MODE7_PEAK_NUM);
		lPeakSum = 0;
		for (i = 0; i < MODE7_PEAK_NUM; i++)
		{
			lPeakSum += pMode7PeakBuffer[i];
		}
  }
	// Periodical flash
	nSampleCount += 1;
  if (nSampleCount >= pMode7PeriodFlashBuffer[nPeriodFlashCount])
  {
  	nShiftSampleCount = (pStimulatingShiftArray[cStimulatingShiftIndex] * 
	   	nSampleRate) / 1000 + 1;
  	nSampleCount = 0;
	}
	// Check unexpected change state
  if (lPeakSum > MODE7_PEAK_NUM * nThresholdLevelValue)
  {
    sSign = sSign * (-1);
   	nSampleCount -= sSign;	
    lPeakSum = 0;
  }
  
  // Check expected and unexpected change state
  nCycleTimeSampleCount += 1;
  if (nCycleTimeSampleCount == nStimulatingMode7CycleTime)
	{
   	if (cStimulatingMode7ModulationIndex == 0) // Symmetric
   	{
 			if (nPeriodFlashCount > 8)
   			sSign = -1;
  		if (nPeriodFlashCount < 1)
   			sSign = 1;
   		nPeriodFlashCount += sSign;
   	}
   	else if (cStimulatingMode7ModulationIndex == 1) // Asymmetric
   	{
   		nPeriodFlashCount += sSign;
 			if (nPeriodFlashCount > 9)
   			nPeriodFlashCount = 0;
  		if (nPeriodFlashCount < 0)
   			nPeriodFlashCount = 9;
   	}
		nCycleTimeSampleCount = 0;
	}
	return nShiftSampleCount;
}

//---------------------------------------------------------------------------
// Function: Mode8Routine
//---------------------------------------------------------------------------
short Mode8Routine(short nPowerValue, short nThresholdLevelValue, short nShiftSampleCount)
{
  static short nSampleCount = 0;
  static short bEnableStimulation = 0;
    
	// Check condition
 	if (nPowerValue < nThresholdLevelValue)
 	{
  	bEnableStimulation = 1;
 	}
	else
 	{
   	nSampleCount = 0;
 		bEnableStimulation = 0;
 	}

  // Enable stimulation
  if (bEnableStimulation)
  {
  	nSampleCount += 1;
  	if (nSampleCount > nStimulatingMode8StimulusPeriod)
  	{
    	// Init shift
  		nShiftSampleCount = (pStimulatingShiftArray[cStimulatingShiftIndex] *
	   		nSampleRate) / 1000 + 1;
	  	nSampleCount = 0;
  	}
  }
  return nShiftSampleCount;
}

//---------------------------------------------------------------------------
// Function: Mode9Routine
//---------------------------------------------------------------------------
short Mode9Routine(short nPatternValue, short nShiftSampleCount)
{
  static short nSampleCount = 0;
  static short nPeriodSoundNumber = 0; 
  static short nPeriodSoundCount = 0;
  short nPeriodSoundValue; 
  static short nEnableMeanSampleCount = 0;
	
	// Enable mean peak value 
	if (nEnableMeanSampleCount > 0)
	{
	  nEnableMeanSampleCount -= 1;
	  if (nEnableMeanSampleCount == 0)
	  	bEnableMeanPeakValue = 1;
	}
	 	
  // Check pattern
  if (nPatternValue == 2)
  	nPeriodSoundCount = 0;

	// Periodical sound
	nSampleCount += 1;
	if (cStimulatingMode9ParadigmTypeIndex == 0) /* Frequency */
	{
		if (nSampleCount >= pMode9PeriodSoundSpaceBuffer[nPeriodSoundCount])
  	{
	    nPeriodSoundNumber += 1;
    	nSampleCount = 0;
  		nShiftSampleCount = 1;
  		GenerateStimulus(STIM_TYPE_SOUND);
		}
  	// Check sound number
  	nPeriodSoundValue = (short)cStimulatingMode9StimulusNumber + 
	  	(pMode9PeriodSoundSpaceBuffer[0] - pMode9PeriodSoundSpaceBuffer[nPeriodSoundCount]);
	}
	else /* Intensity */
	{
  	if (nSampleCount >= pMode9PeriodSoundSpaceBuffer[2])
  	{
    	nPeriodSoundNumber += 1;
    	nSampleCount = 0;
  		nShiftSampleCount = 1;
  		cStimulatingIntensity = pMode9PeriodSoundPowerBuffer[nPeriodSoundCount];
  		GenerateStimulus(STIM_TYPE_SOUND);
		}
  	// Check sound number
  	nPeriodSoundValue = (short)cStimulatingMode9StimulusNumber;
	}
	
	// Descrease frequency or intensity 
  if (nPeriodSoundNumber >= nPeriodSoundValue) 
	{
   	nPeriodSoundNumber = 0;
   	nPeriodSoundCount += 1;
 		if (nPeriodSoundCount > 4)
 		{
   		nPeriodSoundCount = 0;
   		nShiftSampleCount = 1;
   		nEnableMeanSampleCount = 1 * nSampleRate; // 1 second
			bEnableMeanPeakValue = 0;
   		GenerateStimulus(STIM_TYPE_LIGHT);
 		}
	}
	return nShiftSampleCount;
}

//---------------------------------------------------------------------------
// Function: Mode10Routine
//---------------------------------------------------------------------------
short Mode10Routine(short nPatternValue, short nShiftSampleCount)
{
  int i;
	static short nShockSampleCount = 0;
	static short nShockSecondCount = 0;
	static short nShockIntervalIndex = 0;
	static short nShockAnalysisTime = 0;
	static short nMode10StatCount = 0;
	static short nMode10StatValue = 0;
	static short bEnableShock = 0;
	static short nSoundSampleCount = 0;
	static short nSoundNumberCount = 0;
	static short nEnableMeanSampleCount = 0;
	static short nShockAnalysisDelay = 0;
	
	// Step 1: Wait start of trial 
	nShockSampleCount += 1;
	if (nShockSampleCount == nSampleRate)
	{
		nShockSecondCount += 1;
		nShockSampleCount = 0;
		if (nShockSecondCount == pShockIntervalArray[nShockIntervalIndex])
		{
			nShockIntervalIndex += 1;
			nShockSecondCount = 0;
			nSoundSampleCount = nMode10SoundSampleMax;  // 13 * 7.8 ms
			nSoundNumberCount = nMode10SoundNumberMax;  // 5 stimuli
		}
	}
	
	// Step 2: Generate sound stimulus {Windows begin.wav length 687 ms = 88 * 7.8 = 8 stimulus by 11 samples}
	if (nSoundSampleCount > 0)
	{
		nSoundSampleCount -= 1;
		if (nSoundSampleCount == 0)
		{
			if (nSoundNumberCount == nMode10SoundNumberMax) // 5 stimuli
			{
				nModeDependentValue = 1; 	// Stimulus type is start sound
			  nShiftSampleCount = 1;
			}
			if (nSoundNumberCount > 0)
			{
				nSoundSampleCount = nMode10SoundSampleMax; // 13 * 7.8 ms
			  nSoundNumberCount -= 1;
				if (nSoundNumberCount == 0)
				{
				  nShockAnalysisDelay = 128; 					// 128 * 7.8 ms
				  bEnableShock = 1;        	 					// Enable shock
					nModeDependentValue = (1 << 2) | 1;	// Stimulus type is sound (1 << 2) | 1
				  nSoundSampleCount = 0;
				  nShiftSampleCount = 1;
				}
			}
			// Init shift
  		GenerateStimulus(STIM_TYPE_SOUND);
		}
	}
	
	// Step 3: Make delay after sound stimulus
	if (nShockAnalysisDelay > 0)
	{
	  nShockAnalysisDelay -= 1;
	  if (nShockAnalysisDelay == 0)
	  {
	    nShockAnalysisTime = cStimulatingMode10AnalysisTime * nSampleRate; // Analysis time in seconds
	    nShiftSampleCount = 2;
	  }
	}

	// Step 4: Analysis - find pattern
	if (nShockAnalysisTime > 0)
	{
	  // Pattern detection
		if (nPatternValue == 2)
		{
			bEnableShock = 0;
			if (cStimulatingMode10ParadigmTypeIndex == MODE10_RELAX_PAST_TIME_SHOCK)
		  	nShockAnalysisTime = 1;
		} 
	  // Check analysis time
		nShockAnalysisTime -= 1;
		if (nShockAnalysisTime == 0)  // Shock
		{
			nShiftSampleCount = 1;
			// Manual shock correction
			if (cCorrectingMode10Shock > 0)
			{
			  if (cCorrectingMode10Shock == 3)
			  	bEnableShock = 1;
			  else  
			  	bEnableShock = 0;
			  cCorrectingMode10Shock = 0;
			}
			// Statistics
			if (bEnableShock)
				pMode10StatBuffer[nMode10StatCount] = 1;
			else
				pMode10StatBuffer[nMode10StatCount] = 0;
			nMode10StatValue = 0;
			for (i = 0; i < MODE10_STAT_SIZE; i++)
	  		nMode10StatValue += pMode10StatBuffer[i];
	  	nModeDependentValue = (nMode10StatValue << 2) | (bEnableShock + 2);
	  	nMode10StatCount += 1;
	  	if (nMode10StatCount == MODE10_STAT_SIZE)
	  		nMode10StatCount = 0;		
			// Stimulus
			if (bEnableShock)
			{
			  nEnableMeanSampleCount = 1 * nSampleRate; // 1 second
			  bEnableMeanPeakValue = 0;
				GenerateStimulus(STIM_TYPE_SHOCK);
			}
			else
			{
				if (cStimulatingMode10ParadigmTypeIndex == MODE10_RELAX_SAME_TIME_SHOCK ||
						cStimulatingMode10ParadigmTypeIndex == MODE10_RELAX_PAST_TIME_SHOCK)
					GenerateStimulus(STIM_TYPE_LIGHT);
			}
		}
	}
	
	// Step 5: Disable mean peak value calculation - skip shock artefact
	if (nEnableMeanSampleCount > 0)
	{
	  nEnableMeanSampleCount -= 1;
	  if (nEnableMeanSampleCount == 0)
	  	bEnableMeanPeakValue = 1;
	}
	
	return nShiftSampleCount;
}

//---------------------------------------------------------------------------
// Function: Mode8ARoutine
//---------------------------------------------------------------------------
short Mode8ARoutine(short nPowerValue, short nThresholdLevelValue, short nShiftSampleCount)
{
  static short nSampleCount = 0;
  static short bEnableStimulation = 0;
  short nIncrementLevelValue = 0;
	  
	// Check level
	nIncrementLevelValue = (nThresholdLevelValue - nPeakThresholdLevelNoise) / 2;
	if ((nPowerValue >= nThresholdLevelValue - 2 * nIncrementLevelValue) &&     // Level 1
			(nPowerValue < nThresholdLevelValue - nIncrementLevelValue))
	{
	  cStimulatingIntensity = 1;
	  InitTIMER1();
	  bEnableStimulation = 1;
	}
	else if ((nPowerValue >= nThresholdLevelValue - nIncrementLevelValue) &&	   // Level 2
			(nPowerValue < nThresholdLevelValue))
	{
		cStimulatingIntensity = 2;
		InitTIMER1();
		bEnableStimulation = 1;
	}
	else if ((nPowerValue >= nThresholdLevelValue) &&                           // Level 3
			(nPowerValue < nThresholdLevelValue + nIncrementLevelValue))
	{
		cStimulatingIntensity = 3;
		InitTIMER1();
		bEnableStimulation = 1;
	}
	else if ((nPowerValue >= nThresholdLevelValue + nIncrementLevelValue) &&	   // Level 4
			(nPowerValue < nThresholdLevelValue + 2 * nIncrementLevelValue))
	{
		cStimulatingIntensity = 4;	 
		InitTIMER1(); 
		bEnableStimulation = 1;
	}
	else if (nPowerValue >= nThresholdLevelValue + 2 * nIncrementLevelValue)    // Level 5
	{
		cStimulatingIntensity = 5;	
		InitTIMER1();  
		bEnableStimulation = 1;
	}
	else // Level 0 
	{
	  nSampleCount = 0;
	 	bEnableStimulation = 0;
	}

  // Enable stimulation
  if (bEnableStimulation)
  {
  	nSampleCount += 1;
  	if (nSampleCount > nStimulatingMode8StimulusPeriod)
  	{
    	// Init shift
  		nShiftSampleCount = (pStimulatingShiftArray[cStimulatingShiftIndex] *
	   		nSampleRate) / 1000 + 1;
	  	nSampleCount = 0;
  	}
  }
  return nShiftSampleCount;
}	

//---------------------------------------------------------------------------
// Function: Mode8BRoutine
//---------------------------------------------------------------------------
short Mode8BRoutine(short nPowerValue, short nThresholdLevelValue, short nShiftSampleCount)
{
  static short nSampleCount = 0;
  static short bEnableStimulation = 0;
  short nIncrementLevelValue = 0;
	  
	// Check level
	nIncrementLevelValue = (nThresholdLevelValue - nPeakThresholdLevelNoise) / 2;
	if ((nPowerValue >= nThresholdLevelValue - 2 * nIncrementLevelValue) &&     // Level 1
			(nPowerValue < nThresholdLevelValue - nIncrementLevelValue))
	{
	  cStimulatingIntensity = 1;
	  InitTIMER1();
	  cStimulatingMode8StimulusPeriod = 17;
		nStimulatingMode8StimulusPeriod = (((short)cStimulatingMode8StimulusPeriod * 8) * nSampleRate) / 1000;
	  bEnableStimulation = 1;
	}
	else if ((nPowerValue >= nThresholdLevelValue - nIncrementLevelValue) &&	   // Level 2
			(nPowerValue < nThresholdLevelValue))
	{
	  cStimulatingIntensity = 2;
	  InitTIMER1();
	  cStimulatingMode8StimulusPeriod = 15;
		nStimulatingMode8StimulusPeriod = (((short)cStimulatingMode8StimulusPeriod * 8) * nSampleRate) / 1000;
	  bEnableStimulation = 1;
	}
	else if ((nPowerValue >= nThresholdLevelValue) &&                           // Level 3
			(nPowerValue < nThresholdLevelValue + nIncrementLevelValue))
	{
	  cStimulatingIntensity = 3;
	  InitTIMER1();
	  cStimulatingMode8StimulusPeriod = 13;
		nStimulatingMode8StimulusPeriod = (((short)cStimulatingMode8StimulusPeriod * 8) * nSampleRate) / 1000;
	  bEnableStimulation = 1;
	}
	else if ((nPowerValue >= nThresholdLevelValue + nIncrementLevelValue) &&	   // Level 4
			(nPowerValue < nThresholdLevelValue + 2 * nIncrementLevelValue))
	{
	  cStimulatingIntensity = 4;
	  InitTIMER1();
	  cStimulatingMode8StimulusPeriod = 11;
		nStimulatingMode8StimulusPeriod = (((short)cStimulatingMode8StimulusPeriod * 8) * nSampleRate) / 1000;
	  bEnableStimulation = 1;
	}
	else if (nPowerValue >= nThresholdLevelValue + 2 * nIncrementLevelValue)    // Level 5
	{
	  cStimulatingIntensity = 5;
	  InitTIMER1();
	  cStimulatingMode8StimulusPeriod = 9;
		nStimulatingMode8StimulusPeriod = (((short)cStimulatingMode8StimulusPeriod * 8) * nSampleRate) / 1000;
	  bEnableStimulation = 1;
	}
	else // Level 0 
	{
	  nSampleCount = 0;
	 	bEnableStimulation = 0;
	}

  // Enable stimulation
  if (bEnableStimulation)
  {
  	nSampleCount += 1;
  	if (nSampleCount > nStimulatingMode8StimulusPeriod)
  	{
    	// Init shift
  		nShiftSampleCount = (pStimulatingShiftArray[cStimulatingShiftIndex] *
	   		nSampleRate) / 1000 + 1;
	  	nSampleCount = 0;
  	}
  }
  return nShiftSampleCount;
}	

//---------------------------------------------------------------------------
// Function: Mode8CRoutine
//---------------------------------------------------------------------------
short Mode8CRoutine(short nPowerValue, short nThresholdLevelValue, short nShiftSampleCount)
{
  static short nSampleCount = 0;
  static short bEnableStimulation = 0;
  short nIncrementLevelValue = 0;
	  
	// Check level
	nIncrementLevelValue = (nThresholdLevelValue - nPeakThresholdLevelNoise) / 2;
	if ((nPowerValue >= nThresholdLevelValue - 2 * nIncrementLevelValue) &&     // Level 1
			(nPowerValue < nThresholdLevelValue - nIncrementLevelValue))
	{
	  cStimulatingMode8StimulusPeriod = 17;
		nStimulatingMode8StimulusPeriod = (((short)cStimulatingMode8StimulusPeriod * 8) * nSampleRate) / 1000;
	  bEnableStimulation = 1;
	}
	else if ((nPowerValue >= nThresholdLevelValue - nIncrementLevelValue) &&	   // Level 2
			(nPowerValue < nThresholdLevelValue))
	{
	  cStimulatingMode8StimulusPeriod = 15;
		nStimulatingMode8StimulusPeriod = (((short)cStimulatingMode8StimulusPeriod * 8) * nSampleRate) / 1000;
	  bEnableStimulation = 1;
	}
	else if ((nPowerValue >= nThresholdLevelValue) &&                           // Level 3
			(nPowerValue < nThresholdLevelValue + nIncrementLevelValue))
	{
	  cStimulatingMode8StimulusPeriod = 13;
		nStimulatingMode8StimulusPeriod = (((short)cStimulatingMode8StimulusPeriod * 8) * nSampleRate) / 1000;
	  bEnableStimulation = 1;
	}
	else if ((nPowerValue >= nThresholdLevelValue + nIncrementLevelValue) &&	   // Level 4
			(nPowerValue < nThresholdLevelValue + 2 * nIncrementLevelValue))
	{
	  cStimulatingMode8StimulusPeriod = 11;
		nStimulatingMode8StimulusPeriod = (((short)cStimulatingMode8StimulusPeriod * 8) * nSampleRate) / 1000;
	  bEnableStimulation = 1;
	}
	else if (nPowerValue >= nThresholdLevelValue + 2 * nIncrementLevelValue)    // Level 5
	{
	  cStimulatingMode8StimulusPeriod = 9;
		nStimulatingMode8StimulusPeriod = (((short)cStimulatingMode8StimulusPeriod * 8) * nSampleRate) / 1000;
	  bEnableStimulation = 1;
	}
	else // Level 0 
	{
	  nSampleCount = 0;
	 	bEnableStimulation = 0;
	}

  // Enable stimulation
  if (bEnableStimulation)
  {
  	nSampleCount += 1;
  	if (nSampleCount > nStimulatingMode8StimulusPeriod)
  	{
    	// Init shift
  		nShiftSampleCount = (pStimulatingShiftArray[cStimulatingShiftIndex] *
	   		nSampleRate) / 1000 + 1;
	  	nSampleCount = 0;
  	}
  }
  return nShiftSampleCount;
}	

//---------------------------------------------------------------------------
// Function: Processing
//---------------------------------------------------------------------------
void Processing(short sADCValue)
{
  int i;
  short sFLTValue, nPeakValue, nPowerValue, nThresholdLevelValue, nShiftValue;
  short nCMDValue;
  static float fMeanFLTValue = 0;
  static long nMeanFLTValueCount = 0;
  
  // Filtering 
	if (cFilteringTypeIndex == 0)
	{
	  AddSample(pFFTBuffer, sADCValue, FFT_SIZE / 2);
		sFLTValue = FFTFiltering();
	}
	
	// Remove mean value 
	fMeanFLTValue = (fMeanFLTValue * nMeanFLTValueCount + sFLTValue) /
		(nMeanFLTValueCount + 1);
	sFLTValue = sFLTValue - (short)fMeanFLTValue;
	nMeanFLTValueCount += 1;
	
	// Peaking 
	AddSample(pPeakBuffer, sFLTValue, PEAK_SIZE);
	nPeakValue = PeakDetection();
	
	// Check enable mean peak value
	if (bEnableMeanPeakValue)
	{
 		GetMeanShortWindowPeakValue(nPeakValue);
 		GetMeanLongWindowPeakValue(nPeakValue);
	}
 	nPowerValue = nMeanShortWindowPeakValue;
 	nThresholdLevelValue = (short)((nMeanLongWindowPeakValue * nPeakThresholdLevelFloat) / 100);
 	// Float threshold level limit 
 	nThresholdLevelValue = nThresholdLevelValue < nPeakThresholdLevelFloatMin ? 
 		nPeakThresholdLevelFloatMin : nThresholdLevelValue;
 	nThresholdLevelValue = nThresholdLevelValue > nPeakThresholdLevelFloatMax ? 
 		nPeakThresholdLevelFloatMax : nThresholdLevelValue;
 	// Check level type
	if (cPeakingThresholdLevelTypeIndex == 1)
	 	nThresholdLevelValue = nPeakThresholdLevelFixed;
 	
  // Stimulating
  nShiftValue = Stimulating(sADCValue, sFLTValue, nPeakValue, nPowerValue, 
  	nThresholdLevelValue);
  	
	// Transmitting
	nCMDValue = nPeakValue;
 	if (cPeakingCommandParameterIndex == CMD_PARAM_POWER)
		nCMDValue = nPowerValue; 
  Transmitting(sADCValue, sFLTValue, nCMDValue,
  	nThresholdLevelValue, nShiftValue, nModeDependentValue);
}

//---------------------------------------------------------------------------
// Function: LEDBlinking
//---------------------------------------------------------------------------
void LEDBlinking(short nState)
{
	static unsigned char ucActiveLED;
	
	if (nState == 0) // Wait params
		ucActiveLED = 0x03;  
	else if (nState == 1) // Start processing
	{
	  if (ucActiveLED == 0x03) 
	  	ucActiveLED = 0x01;  
	  ucActiveLED ^= 0x03;
	}
	else if (nState == 2) // Stop processing
	  ucActiveLED = 0x00;
	
	*pFlashA_PortB_Data = ucActiveLED;	
}

//---------------------------------------------------------------------------
// Function: PatternDetection
//---------------------------------------------------------------------------
short PatternDetection(short nPeakValue, short nPowerValue, 
	short nThresholdLevelValue, short nSpaceSampleCount, short bMode10Reset)
{
	static short nPatternPeakCount = 0;
	short nPatternValue = 0;
	  
	// Reset - Start new analysis in mode 10
	if (bMode10Reset)
	{
	  nSpaceSampleCount = 0;
		nPatternPeakCount = 0;
	}
		
	// Check command parameter 
	if (cPeakingCommandParameterIndex == CMD_PARAM_PEAK) // Peak
	{
 		if ((nPeakValue > nPeakThresholdLevelNoise && nPeakValue > nThresholdLevelValue && cPatterningPeakTypeIndex == PDT_TL_ABOVE) ||
 				(nPeakValue > nPeakThresholdLevelNoise && nPeakValue < nThresholdLevelValue && cPatterningPeakTypeIndex == PDT_TL_BELOW))
 		{
			if (nSpaceSampleCount > 0)
				nPatternPeakCount += 1;
			nPatternValue = 1; 		// Peak detected
			// Consider case when number of peaks more than cPatterningPeakParamMax
			if (nPatternPeakCount >= cPatterningPeakParamMax)
			{
				nPatternValue = 2; 	// Pattern detected
				nPatternPeakCount = 0;
			}
		}
		else
		{
			if (nSpaceSampleCount == 0)
  		{
				if (nPatternPeakCount >= (cPatterningPeakParamMin - 1) && 
						nPatternPeakCount <= (cPatterningPeakParamMax - 1))
					nPatternValue = 2; // Pattern detected
				nPatternPeakCount = 0;
			}
		}
	}
	else if (cPeakingCommandParameterIndex == CMD_PARAM_POWER) // Power
	{
	  if (nPowerValue >= nThresholdLevelValue)
	  	nPatternValue = 2;
	} 

	return nPatternValue;
}

//---------------------------------------------------------------------------
