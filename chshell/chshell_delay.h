#include "shell.h"
#include <misc.h>
#include <stdlib.h>
#include "stm32f4xx.h"
void TM_Delay_Init(void);
void TM_DelayMillis(uint32_t millis);
int delayCmdParse(shell_cmd_args *args){
	int delay=atoi(args->args[0].val);
	TM_Delay_Init();
	TM_DelayMillis(delay);
	CHTerminalPrint("Delay Succes!");
	return 1;
}
uint32_t multiplier;
 
void TM_Delay_Init(void) {
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq(&RCC_Clocks);
    multiplier = RCC_Clocks.HCLK_Frequency / 4000000;
}
void TM_DelayMillis(uint32_t millis) {
    millis = 1000 * millis * multiplier - 10;
    while (millis--);
}
