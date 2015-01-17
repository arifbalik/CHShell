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
#ifndef CHSHELL_USART_H
#define CHSHELL_USART_H

#include <misc.h>	

#define MAX_STRLEN 120 

extern volatile char received_string[MAX_STRLEN+1]; // this will hold the recieved string
extern int buffer_flag;



extern void CHTerminalPrint(char* data);
extern void Delay(__IO uint32_t nCount);
extern void clear_buffer(void);
extern void init_USART1(uint32_t baudrate);


#endif
