/*
     This library is a part of CHShell.
       Copyright (C) 2015  Arif Ahmet Balik
       This program is free software: you can redistribute it and/or modify
       it under the terms of the GNU General Public License as published by
       the Free Software Foundation, either version 3 of the License, or
       (at your option) any later version.
       This program is distributed in the hope that it will be useful,
       but WITHOUT ANY WARRANTY; without even the implied warranty of
       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
       GNU General Public License for more details.
       You should have received a copy of the GNU General Public License
       along with this program.  If not, see <http://www.gnu.org/licenses/>.
   */
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
