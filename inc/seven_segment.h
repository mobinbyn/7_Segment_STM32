#ifndef SEVEN_SEGMENTS_H_
#define SEVEN_SEGMENTS_H_




/**
 *  Driver Name: 7-Segments Display 
 *	Detailed Description
 *
 * 
 * 
 *  @uthor:           Mobin byn
 *  @file:            seven_segment.h
 *  @version:         V1.0
 *  @date:            January 17, 2022
 *  @attention:
 */
 
 
#include "stm32f0xx_hal.h"

/* Pre Private define --------------------------------------------------------*/

/** @defgroup Do not change these values
  * @{
  */
#define COM_CATHODE           							1
#define COM_ANODE             							0

#define SEV_SGM_NOT_FLOT_SHOW								0
#define SEV_SGM_ONE_FLOT_SHOW								1
#define SEV_SGM_TWO_FLOT_SHOW								2

#define SEV_SGM_UNIT_ONE										0
/**
  * @}
  */


/* Seven segment config define ------------------------------------------------*/

#define SEVEN_SEG_UNITS  	                  1             /*!< The number of 7-Segments display units to be used in the project */
#define DIGITS           	                  3             /*!< Number of 7-Segment digits */


#define SEG_COM_MODE                        COM_CATHODE   /*!< 7-Segment Type */

#define DP_PIN_ENABLE		                                  /*!< If your 7_Segment does not have pin dp, comment this line */

#define SEVEN_SEGMENT_REFRESH_TIME          5             /*!< Refresh displaty time (ms) */


/* Nex Private define ----------------------------------------------------------*/

/** @defgroup Do not change these values
  * @{
  */
#ifdef DP_PIN_ENABLE
	#define	SEG_PINS_NUM		((uint8_t) 8)
#else
	#define SEG_PINS_NUM		((uint8_t) 7)
#endif /* DP_PIN_ENABLE */
/**
  * @}
  */



/**
 * @brief Structure definition of seven segment initialization GPIO & PIN 
 * @note 
 * 
 */
typedef struct
{
	GPIO_TypeDef  *SEG_GPIO[SEG_PINS_NUM];
	
	uint16_t       SEG_PIN[SEG_PINS_NUM];
	
	GPIO_TypeDef  *EN_GPIO[DIGITS];
	
	uint16_t       EN_PIN[DIGITS];
	
} SevenSegment_InitTypeDef;




/* Public function prototype --------------------------------------------------*/

void SevenSegment_Init(uint16_t UnitNo);

void SevenSegment_Start(void);

#ifdef DP_PIN_ENABLE
void SevenSegment_Write(uint16_t UnitNo, float Data, uint16_t DotPosition);
#else
void SevenSegment_Write(uint16_t UnitNo, uint16_t Data);
#endif /* DP_PIN_ENABLE  */

void SevenSegment_sWrite(uint16_t UnitNo, char Data[]);

void SevenSegment_Enable(uint16_t UnitNo);

void SevenSegment_Disable(uint16_t UnitNo);


#endif /* SEVEN_SEGMENTS_H_ */