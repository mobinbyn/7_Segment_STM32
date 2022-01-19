#include "seven_segment.h"
#include "main.h"

/**
 * @file seven_segment_conf.c
 * @author Mobin Byn (mobin.byn@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-17
 * 
 * @copyright Copyright (c) 2022
 */

const SevenSegment_InitTypeDef seven_segment_init_struct[SEVEN_SEG_UNITS] =
{
  // Seven segment unit 1 configuration
  {
    // Segment pins
    #ifdef DP_PIN_ENABLE
    {SEG_A_GPIO_Port, SEG_B_GPIO_Port, SEG_C_GPIO_Port, SEG_D_GPIO_Port, SEG_E_GPIO_Port, SEG_F_GPIO_Port, SEG_G_GPIO_Port, SEG_DP_GPIO_Port},
    {SEG_A_Pin, SEG_B_Pin, SEG_C_Pin, SEG_D_Pin, SEG_E_Pin, SEG_F_Pin, SEG_G_Pin, SEG_DP_Pin},
    #else
    {GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA},
    {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6},
    #endif
    // Enable signal control's pin
    {Digit_3_GPIO_Port, Digit_2_GPIO_Port, Digit_1_GPIO_Port},
    {Digit_3_Pin, Digit_2_Pin, Digit_1_Pin}
  }
};
