 /*
     This library is a part of CHShell. This library provides management to GPIO.
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
   	#include "stm32f7xx_hal_gpio.h"              // Keil::Device:STM32Cube HAL:Common
    #include <string.h>
		#include <stdio.h>
		#include <stdlib.h>
		#include "getopt.h"
		#include "chshell_gpio.h"
	
	GPIO_TypeDef* gpioPortDefineList[] = {
			GPIOI,
			GPIOB,
			GPIOC,
			GPIOD
		};
	char* gpioPortList[] = {
    "a",
    "b",
    "c",
    "d",
   };
	 int gpioPortCount = 4;
	 
   //Gpio Pin Field
   uint16_t gpioPinDefineList[] = {
		GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_15,
    GPIO_PIN_All
   };
   char* gpioPinList[] = {
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "11",
    "12",
    "13",
    "14",
    "15",
    "a"
   };
   int gpioPinCount = 17;
	 
	 //Gpio Mode Field
   uint32_t gpioDirDefineList[] = {
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT_PP,
		GPIO_MODE_OUTPUT_OD,
    GPIO_MODE_AF_PP,
		GPIO_MODE_AF_OD,
    GPIO_MODE_ANALOG
   };
   char* gpioDirList[] = {
    "i",
    "o",
		"od",
    "f",
		"fd",
    "a"
   };
   int gpioDirCount = 4;
	 //Gpio PuPd Field
   uint32_t gpioPuPdDefineList[] = {
    GPIO_PULLUP,
    GPIO_PULLDOWN,
    GPIO_NOPULL
   };
   char* gpioPuPdList[] = {
    "u",
    "d",
    "n"
   };
   int gpioPuPdCount = 3;
	  //Gpio speed fields
   uint32_t gpioSpeedDefineList[] = {
    GPIO_SPEED_LOW,
    GPIO_SPEED_MEDIUM,
    GPIO_SPEED_FAST,
    GPIO_SPEED_HIGH
   };
   char* gpioSpeedList[] = {
    "2",
    "25",
    "50",
    "100"
   };
   int gpioSpeedCount = 4;
	 
  uint16_t getPin(char* pin){
		int i = 0;
    for (i = 0; i < gpioPinCount; i++){
     if(!strcmp(pin,gpioPinList[i])){ 
      return gpioPinDefineList[i];
     }
    }
    return gpioPinDefineList[0];
   }
	uint32_t getMode(char* mode){
		int i = 0;
      for (i = 0; i < gpioDirCount; i++){
     if(!strcmp(mode,gpioDirList[i])){ 
      return gpioDirDefineList[i];
     }
    }
    return gpioDirDefineList[i];
   }
	uint32_t getPuPd(char* PuPd){
		int i = 0;
     for (i = 0; i < gpioPuPdCount; i++){
     if(!strcmp(PuPd,gpioPuPdList[i])){ 
      return gpioPuPdDefineList[i];
     }
    }
    return gpioPuPdDefineList[0];
   }
	
	uint32_t getSpeed(char* Speed){
		int i =0;
    for (i = 0; i < gpioSpeedCount; i++){
     if(!strcmp(Speed,gpioSpeedList[i])){ 
      return gpioSpeedDefineList[i];
     }
   }
		return gpioSpeedDefineList[0];
 }
	GPIO_TypeDef* getPort(char* port){
		int i = 0;
    for (i = 0; i < gpioPortCount; i++){
     if(!strcmp(port,gpioPortList[i])){ 
      return gpioPortDefineList[i];
     }
    }
    return gpioPortDefineList[0];
   }
	
	 
const char help[] =
   "\n"
   " Syntax\n"
   " [-p] [portNumber] [-l] [pull up/down] [-m] [mode]\n"
   " [-s] [speed]\n"
   " GPIO provide all io function in CLI.\n"
   " -p\n"
   " Pin number of a port. It can take 0-15 and a (all).\n"
	 " It can also use by -pin\n"
   " -r\n"
   " Pull up or down for pin(s). It can take u (up), d (down)\n"
	 " and n (no pull) It can also use by -pull.\n"
	 " -m\n"
   " Mode for pin(s). It can take o (output pushpull),\n"
	 " od (output opendrain), f (alternative pp), fd (alt. od)\n"
   " i (input) and a (analog). It can also use by -mode.\n"
	 " -s\n"
   " Speed for pin(s). It can take low, medium, fast and high.\n"
	 " It can also use by -speed.\n"
	 "Example:\n"
   " gpio -port a -p 1 -mode op -l u -s high\n";
	 
	 
static int verbose_flag;
int ch_getopt_gpio(int argc, char** argv)
{
	char* port;
	char* pin;
	GPIO_InitTypeDef GPIO_InitDef; //Where GPIO_InitDef is variable to work with struct
	int set_reset = 1;
	int c;
  while (1)
    {
      static struct option long_options[] =
        {
          /* These options set a flag. */
         // {"it",  no_argument,        &verbose_flag, 0}, //call the init function
          {"rd",  	no_argument,        &verbose_flag, 1}, //call the read function
					{"wr",  	required_argument,  &verbose_flag, 2}, //call the write function
					{"dn",  	no_argument,        &verbose_flag, 3}, //call the deinit function
					{"lk",  	no_argument,        &verbose_flag, 4}, //lock function
					{"tg",  	no_argument,        &verbose_flag, 5}, //toggle function
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"port",  	required_argument, 0, 'p'},
          {"pull",  	required_argument, 0, 'r'},
          {"mode",    required_argument, 0, 'm'},
					{"speed",   required_argument, 0, 's'},
					{"exti",   	no_argument, 			 0, 'e'},
					{"help",   	no_argument, 			 0, 'h'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

				c = getopt_long_only(argc, argv, "g:p:l:m:s:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;
	
      switch (c)
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          set_reset = atoi(optarg);
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          
          break;
				case 'e':
						//exti();
          break;
        case 'p':
					sprintf(port,"%c",optarg[0]);
					sprintf(pin,"%c%c",optarg[1],optarg[2]);
					GPIO_InitDef.Pin = getPin(pin);
					
					//printf("Port Selected!\n");
          break;
        case 'l':
					GPIO_InitDef.Pull = getPuPd(optarg);
					//printf("Pull Selected!\n");
          break;
        case 'm':
					GPIO_InitDef.Mode = getMode(optarg);
					//printf("Mode Selected!\n");
					verbose_flag = 0; // for init function
          break;
        case 's':
					GPIO_InitDef.Speed = getSpeed(optarg);
					//printf("Speed Selected!\n");
          break;
				case 'h':
					printf(help);
          break;
        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          printf ("Something happend!");
				break;
        }
    }

  /* Instead of reporting ‘--write’
     and ‘--init’ as they are encountered,
     we report the final status resulting from them. */
    switch(verbose_flag){
      case 0:
    		HAL_GPIO_Init(getPort(port),&GPIO_InitDef);
    	  break;
      case 1:
        printf("Pin value :%d\n",HAL_GPIO_ReadPin(getPort(port),GPIO_InitDef.Pin));
        break;
      case 2:
        HAL_GPIO_WritePin(getPort(port),GPIO_InitDef.Pin,set_reset);
        break;
      case 3:
        HAL_GPIO_DeInit(getPort(port),GPIO_InitDef.Pin);
        break;
      case 4:
				HAL_GPIO_LockPin(getPort(port),GPIO_InitDef.Pin);
        break;
      case 5:
        HAL_GPIO_TogglePin(getPort(port),GPIO_InitDef.Pin);
        break;

    }
	
  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    }
		optind = 0;
	return 1;
}
