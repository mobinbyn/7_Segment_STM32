#include "database.h"
#include "seven_segment.h"
#include "seven_segment_pattern.h"
#include <math.h>
#include <string.h>



/**
 *  Driver Name: 7-Segments Display 
 *	Detailed Description
 *
 * 
 * 
 *  @uthor:           Mobin byn
 *  @file:            seven_segment.c
 *  @version:         V1.0
 *  @date:            January 17, 2022
 *  @attention:
 */



#define ENABLED     1
#define DISABLED    0

typedef struct
{
	uint8_t   EN_State;
	uint8_t   Digits[DIGITS];
  uint8_t   DotPosition;
	uint8_t   Digit_Index;
} SevenSegment_InfoTypeDef;


static SevenSegment_InfoTypeDef seven_segment_info_struct[SEVEN_SEG_UNITS] = {0};
static unsigned long segment_refresh_time;


/* Private function prototype --------------------------------------------------*/
static void SevenSegment_Main(void);
/* -----------------------------------------------------------------------------*/



/**
 * @brief 
 * 
 * @param UnitNo 
 */
void SevenSegment_Init(uint16_t UnitNo)
{
//	uint8_t i = 0;
//	GPIO_InitTypeDef GPIO_InitStruct = {0};

//	/* Configure the 7-Segments GPIO pins ---------------------*/
//	for( i = 0; i < SEG_PINS_NUM; i++)
//	{
//		if(seven_segment_init_struct[UnitNo].SEG_GPIO[i] == GPIOA)
//	  {
//      __HAL_RCC_GPIOA_CLK_ENABLE();
//		}
//		else if(seven_segment_init_struct[UnitNo].SEG_GPIO[i] == GPIOB)
//		{
//			__HAL_RCC_GPIOB_CLK_ENABLE();
//		}
//		else if(seven_segment_init_struct[UnitNo].SEG_GPIO[i] == GPIOC)
//		{
//			__HAL_RCC_GPIOC_CLK_ENABLE();
//		}
//		else if(seven_segment_init_struct[UnitNo].SEG_GPIO[i] == GPIOD)
//		{
//			__HAL_RCC_GPIOD_CLK_ENABLE();
//		}
////		else if(seven_segment_init_struct[UnitNo].SEG_GPIO[i] == GPIOE)
////		{
////			__HAL_RCC_GPIOE_CLK_ENABLE();
////		}
//		else if(seven_segment_init_struct[UnitNo].SEG_GPIO[i] == GPIOF)
//		{
//			__HAL_RCC_GPIOF_CLK_ENABLE();
//		}
//		GPIO_InitStruct.Pin = seven_segment_init_struct[UnitNo].SEG_PIN[i];
//		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
//		HAL_GPIO_Init(seven_segment_init_struct[UnitNo].SEG_GPIO[i], &GPIO_InitStruct);
//	}
//	/* Configure the 7-Segments Enable signals GPIO pins -------*/
//	for(i = 0; i < DIGITS; i++)
//	{
//		if(seven_segment_init_struct[UnitNo].EN_GPIO[i] == GPIOA)
//		{
//      __HAL_RCC_GPIOA_CLK_ENABLE();
//		}
//		else if(seven_segment_init_struct[UnitNo].EN_GPIO[i] == GPIOB)
//		{
//			__HAL_RCC_GPIOB_CLK_ENABLE();
//		}
//		else if(seven_segment_init_struct[UnitNo].EN_GPIO[i] == GPIOC)
//		{
//			__HAL_RCC_GPIOC_CLK_ENABLE();
//		}
//		else if(seven_segment_init_struct[UnitNo].EN_GPIO[i] == GPIOD)
//		{
//			__HAL_RCC_GPIOD_CLK_ENABLE();
//		}
////		else if(seven_segment_init_struct[UnitNo].EN_GPIO[i] == GPIOE)
////		{
////			__HAL_RCC_GPIOE_CLK_ENABLE();
////		}
//		else if(seven_segment_init_struct[UnitNo].SEG_GPIO[i] == GPIOF)
//		{
//			__HAL_RCC_GPIOF_CLK_ENABLE();
//		}
//		GPIO_InitStruct.Pin = seven_segment_init_struct[UnitNo].EN_PIN[i];
//		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
//		HAL_GPIO_Init(seven_segment_init_struct[UnitNo].EN_GPIO[i], &GPIO_InitStruct);
//	}

  segment_refresh_time = HAL_GetTick();
}



/**
 * @brief 
 * 
 */
void SevenSegment_Start()
{
  if(HAL_GetTick() > segment_refresh_time)
  {
    SevenSegment_Main();
    segment_refresh_time = HAL_GetTick() + SEVEN_SEGMENT_REFRESH_TIME;
  }
}


/**
 * @brief 
 * 
 * @param UnitNo 
 * @param Data 
 */
void SevenSegment_sWrite(uint16_t UnitNo, char Data[])
{
  /* Calculate the size of the string to prevent overflow */
  uint8_t length = strlen(Data);
	uint8_t tmp_empty_digit = DIGITS, tmp_length = strlen(Data);

  if(length <= DIGITS)
  {	
    for( uint8_t i = 0; i < DIGITS; i++)
    {
			/* To spell words left out, we have to ignore empty phrases with the help of a wanderer */
			if(tmp_empty_digit > tmp_length)
			{
				/* Index 37 is blank and the digit will be off */
				seven_segment_info_struct[UnitNo].Digits[i] = 37;
				tmp_empty_digit--;
			}
			else
			{
				/* Extract from lookup table */
				seven_segment_info_struct[UnitNo].Digits[i] = SevenSegment_GetCharFromLookupTable(Data[length-1]);
				length--;
			}
    }
  }
  else
  {
    /* Error Handler */
  }
}




#ifdef DP_PIN_ENABLE
/**
 * @brief 
 * 
 * @param UnitNo 
 * @param Data 
 * @param DotPosition 
 * @param DataType 
 */
void SevenSegment_Write(uint16_t UnitNo, float Data, uint16_t DotPosition)
{
	/* If dot position in range of the 7-Segment digit */
  if((0 < DotPosition) && (DotPosition <= DIGITS-1))
  {
    seven_segment_info_struct->DotPosition = DotPosition;
    Data = (float)(Data * pow(10, DotPosition));
  }
	/* Else does not show dot position */ 
  else
  {
    seven_segment_info_struct->DotPosition = 0;
  }


  for(uint8_t i = 0; i < DIGITS; i++)
  {
		/* If the data is zero, keep that digit off */ 
		if(Data != 0)
		{
			/* Calculate data and prepare for display */
      seven_segment_info_struct[UnitNo].Digits[i] = ((uint16_t)Data%10);
      Data = (uint16_t)Data / 10;
		}
    else
    {
			/* Index 37 is blank and the digit will be off */
      seven_segment_info_struct[UnitNo].Digits[i] = 37;
    }
  }

	seven_segment_info_struct[UnitNo].Digit_Index = 0;
}

#else
/**
 * @brief 
 * 
 * @param UnitNo 
 * @param Data 
 * @param DataType 
 */
void SevenSegment_Write(uint16_t UnitNo, uint16_t Data, uint8_t DataType)
{
	 Data = abs(Data);

  for(uint8_t i = 0; i < DIGITS; i++)
  {
    seven_segment_info_struct[UnitNo].Digits[i] = (Data%10);
    Data /= 10;
  }

	seven_segment_info_struct[UnitNo].Digit_Index = 0;

}
#endif /* SP_PIN_ENABLE */



/**
 * @brief 
 * 
 * @param UnitNo 
 */
void SevenSegment_Enable(uint16_t UnitNo)
{
	seven_segment_info_struct[UnitNo].EN_State = ENABLED;
}



/**
 * @brief 
 * 
 * @param UnitNo 
 */
void SeventSegment_Disable(uint16_t UnitNo)
{
	seven_segment_info_struct[UnitNo].EN_State = DISABLED;
}



static void SevenSegment_Main(void)
{
	uint8_t i = 0, j = 0;
	uint8_t Digit_Index = 0;
	uint8_t Digit_Value = 0;

	for(i = 0; i < SEVEN_SEG_UNITS; i++)
	{
		/* If this 7-Seg display unit is Enabled*/
		if(seven_segment_info_struct[i].EN_State == ENABLED)
		{
			/* Check the index of the digit to be displayed now */
			Digit_Index = seven_segment_info_struct[i].Digit_Index;
			/* Disable the EN lines momentarily to reduce ghosting effect */
			for (j = 0; j < DIGITS; j++)
			{
				#if(SEG_COM_MODE == COM_CATHODE)
				HAL_GPIO_WritePin(seven_segment_init_struct[i].EN_GPIO[j], seven_segment_init_struct[i].EN_PIN[j], 1);
				#elif(SEG_COM_MODE == COM_ANODE)
				HAL_GPIO_WritePin(seven_segment_init_struct[i].EN_GPIO[j], seven_segment_init_struct[i].EN_PIN[j], 0);
				#endif /*SEG_COM_MODE == COM_CATHODE*/
			}
			/* Get & Move the digit value's pattern to the 7-Seg pins*/
			Digit_Value = seven_segment_info_struct[i].Digits[Digit_Index];
			for(j = 0; j < SEG_PINS_NUM; j++)
			{
        // Trace bit by bit
        if((SEVEN_SEGMENT_LOOKUP_TABLE[Digit_Value] & (1 << j)) == (1 << j))
				{
					HAL_GPIO_WritePin(seven_segment_init_struct[i].SEG_GPIO[j], seven_segment_init_struct[i].SEG_PIN[j], 1);
				}
				else
				{
					HAL_GPIO_WritePin(seven_segment_init_struct[i].SEG_GPIO[j], seven_segment_init_struct[i].SEG_PIN[j], 0);
				}
			}
      /* If DP pin is enable, 7-Segment DP pin must be Enable */
      #ifdef DP_PIN_ENABLE
      if((seven_segment_info_struct[i].DotPosition == Digit_Index) && (Digit_Index != 0))
      {
        #if (SEG_COM_MODE == COM_CATHODE)
        HAL_GPIO_WritePin(seven_segment_init_struct[i].SEG_GPIO[7], seven_segment_init_struct[i].SEG_PIN[7], 1);
        #elif(SEG_COM_MODE == COM_ANODE)
        HAL_GPIO_WritePin(seven_segment_init_struct[i].SEG_GPIO[7], seven_segment_init_struct[i].SEG_PIN[7], 0);
        #endif /* SEG_COM_MODE == COM_CATHODE */
      }
      #endif /* DP_PIN_ENABLE */
			/* Now, Enable the respective EN line */
			#if(SEG_COM_MODE == COM_CATHODE)
			HAL_GPIO_WritePin(seven_segment_init_struct[i].EN_GPIO[Digit_Index], seven_segment_init_struct[i].EN_PIN[Digit_Index], 0);
			#elif(SEG_COM_MODE == COM_ANODE)
			HAL_GPIO_WritePin(seven_segment_init_struct[i].EN_GPIO[Digit_Index], seven_segment_init_struct[i].EN_PIN[Digit_Index], 1);
			#endif /* SEG_COM_MODE == COM_CATHODE */

			/* Increment the index of the digit to be displayed in the next time.. */
			seven_segment_info_struct[i].Digit_Index++;
			if(seven_segment_info_struct[i].Digit_Index == DIGITS)
			{
				seven_segment_info_struct[i].Digit_Index = 0;
			}
		}
		/* Else if this 7-Seg display unit is Disabled */
		else if(seven_segment_info_struct[i].EN_State == DISABLED)
		{
			/* Drive all the EN pins low/high for this 7-Seg unit */
			for (j = 0; j < DIGITS; j++)
			{
				#if(SEG_COM_MODE == COM_CATHODE)
				HAL_GPIO_WritePin(seven_segment_init_struct[i].EN_GPIO[j], seven_segment_init_struct[i].EN_PIN[j], 0);
				#elif(SEG_COM_MODE == COM_ANODE)
				HAL_GPIO_WritePin(seven_segment_init_struct[i].EN_GPIO[j], seven_segment_init_struct[i].EN_PIN[j], 1);
				#endif /* SEG_COM_MODE == COM_CATHODE */
			}
		}
	}
}