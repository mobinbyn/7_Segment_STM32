#include "seven_segment.h"



int main(void)
{
	SevenSegment_Init(SEV_SGM_UNIT_ONE);
	SevenSegment_Enable(SEV_SGM_UNIT_ONE);
    
	SevenSegment_sWrite(SEV_SGM_UNIT_ONE, "Err");
//	SevenSegment_Write(SEV_SGM_UNIT_ONE,12.5,SEV_SGM_ONE_FLOT_SHOW);
    while (1)
    {
		SevenSegment_Start();
    };
    
}