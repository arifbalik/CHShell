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
    #include "CHShell_gpio.h" 
    #include "CHShell_usart.h"
    #include <string.h>
    #include <stdio.h>
    #include <stm32f4xx_gpio.h>
   
    #define error 0

    //GPIO Pin Name
    #define GPIO_NAME_COUNT 15
    #define cmdGPIOA 'a'
    #define cmdGPIOB 'b'
    #define cmdGPIOG 'c'
    #define cmdGPIOD 'd'

    //GPIO Mode
    #define MODE_INIT   "i"
    #define MODE_WRITE  "w"
    #define MODE_READ   "r"
    #define MODE_RESET  "reset"

    //Messages
    #define GPIO_INIT_OK  "GPIO Initialize Succes!\n"
    #define GPIO_WRITE_OK "GPIO Write Succes!\n"
    #define GPIO_READ_OK  "GPIO Read Succes!\n"
    #define GPIO_RESET_OK "GPIO Reset Succes!\n"


   //Gpio Pin Field
   uint16_t gpioPinDefineList[] = {
    GPIO_Pin_0,
    GPIO_Pin_1,
    GPIO_Pin_2,
    GPIO_Pin_3,
    GPIO_Pin_4,
    GPIO_Pin_5,
    GPIO_Pin_6,
    GPIO_Pin_7,
    GPIO_Pin_8,
    GPIO_Pin_9,
    GPIO_Pin_10,
    GPIO_Pin_11,
    GPIO_Pin_12,
    GPIO_Pin_13,
    GPIO_Pin_14,
    GPIO_Pin_15,
    GPIO_Pin_All
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
   GPIOMode_TypeDef gpioDirDefineList[] = {
    GPIO_Mode_IN,
    GPIO_Mode_OUT,
    GPIO_Mode_AF,
    GPIO_Mode_AN
   };
   char* gpioDirList[] = {
    "i",
    "o",
    "f",
    "a"
   };
   int gpioDirCount = 4;

   //Gpio OType Field
   GPIOOType_TypeDef gpioOTypeDefineList[] = {
    GPIO_OType_PP,
    GPIO_OType_OD
   };
   char* gpioOTypeList[] = {
    "p",
    "o"
   };
   int gpioOTypeCount = 2;

   //Gpio PuPd Field
   GPIOPuPd_TypeDef gpioPuPdDefineList[] = {
    GPIO_PuPd_UP,
    GPIO_PuPd_DOWN,
    GPIO_PuPd_NOPULL
   };
   char* gpioPuPdList[] = {
    "u",
    "d",
    "n"
   };
   int gpioPuPdCount = 3;

   //Gpio speed fields
   GPIOSpeed_TypeDef gpioSpeedDefineList[] = {
    GPIO_Speed_2MHz,
    GPIO_Speed_25MHz,
    GPIO_Speed_50MHz,
    GPIO_Speed_100MHz
   };
   char* gpioSpeedList[] = {
    "2",
    "25",
    "50",
    "100"
   };
   int gpioSpeedCount = 4;

   int i = 0;

   uint16_t getPin(char* pin){
    for (i = 0; i < gpioPinCount; i++){
     if(!strcmp(pin,gpioPinList[i])){ 
      return gpioPinDefineList[i];
     }
    }
    return gpioPinDefineList[0];
   }
   GPIOMode_TypeDef getMode(char* mode){
      for (i = 0; i < gpioDirCount; i++){
     if(!strcmp(mode,gpioDirList[i])){ 
      return gpioDirDefineList[i];
     }
    }
    return gpioDirDefineList[i];
   }
   GPIOOType_TypeDef getOtype(char* OType){
    for (i = 0; i < gpioOTypeCount; i++){
     if(!strcmp(OType,gpioOTypeList[i])){ 
      return gpioOTypeDefineList[i];
     }
    }
    return gpioOTypeDefineList[0];
   }
   GPIOPuPd_TypeDef getPuPd(char* PuPd){
     for (i = 0; i < gpioPuPdCount; i++){
     if(!strcmp(PuPd,gpioPuPdList[i])){ 
      return gpioPuPdDefineList[i];
     }
    }
    return gpioPuPdDefineList[0];
   }
   GPIOSpeed_TypeDef getSpeed(char* Speed){
    for (i = 0; i < gpioSpeedCount; i++){
     if(!strcmp(Speed,gpioSpeedList[i])){ 
      return gpioSpeedDefineList[i];
     }
   }
    return gpioSpeedDefineList[0];
 }
   int gpioCmdProcess(gpioCmd* Gpio){
    
    GPIO_InitTypeDef GPIO_InitDef;
    GPIO_TypeDef* gpioName;
    
    char readValue[20];
    
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_All;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
    
    for (i = 0; i < 15; i++){
     switch(Gpio->gpioName){ 
      case cmdGPIOA:
       RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
       gpioName = GPIOA;
       break;
      case cmdGPIOD:
       RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
       gpioName = GPIOD;
       break;
      default:
       return error;
     }
    }
    GPIO_InitDef.GPIO_Pin = getPin(Gpio->gpioPin);
    
    
    if(!strcmp(Gpio->gpioMode,MODE_INIT)){
      GPIO_InitDef.GPIO_Mode = getMode(Gpio->gpioMode);
      GPIO_InitDef.GPIO_OType = getOtype(Gpio->gpioOType);
      GPIO_InitDef.GPIO_PuPd = getPuPd(Gpio->gpioPuPd);
      GPIO_InitDef.GPIO_Speed = getSpeed(Gpio->gpioSpeed);
      GPIO_Init(gpioName, &GPIO_InitDef);
      CHTerminalPrint(GPIO_INIT_OK);
    }
    
    else if(!strcmp(Gpio->gpioMode,MODE_WRITE)){
      GPIO_SetBits(gpioName, GPIO_InitDef.GPIO_Pin);
      CHTerminalPrint(GPIO_WRITE_OK);
    }
    else if(!strcmp(Gpio->gpioMode,MODE_READ)){
     if(!strcmp(Gpio->gpioPin,"a")){
        i= 0;
        while(16 != i){
           GPIO_InitDef.GPIO_Pin = gpioPinDefineList[i];
          sprintf(readValue,"Pin %d Value = %d\n",i,GPIO_ReadInputDataBit(gpioName, GPIO_InitDef.GPIO_Pin));
          CHTerminalPrint(readValue);
          i++;
        }
      }
      else{
        sprintf(readValue,"Value = %d\n",GPIO_ReadInputDataBit(gpioName, GPIO_InitDef.GPIO_Pin));
             CHTerminalPrint(readValue);
      }
      CHTerminalPrint(GPIO_READ_OK);
    }
    else if(!strcmp(Gpio->gpioMode,MODE_RESET)){
     GPIO_ResetBits(gpioName, GPIO_InitDef.GPIO_Pin);
     CHTerminalPrint(GPIO_RESET_OK);
    }
    return 1;
  }

  
