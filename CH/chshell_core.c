 /**
  ******************************************************************************
  * @file    chshell_core.c
  * @author  Arif Ahmet Balik <arifbalik@outlook.com>
  * @version V0.1
  * @date    1-Aug-2015
  * @brief   chshell initialize rutine and preparsing
  *
  *   This file provides one functions and one global variable to be called from 
  *   user application:
  *      - chshellStart(): 
  *      - chshell_core variable:   
  *
  ******************************************************************************

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

 * CHSHELL have highly modular architecture. So you can write your own library
 * easily.
 * How You Write Your Own CHSHELL Module Library?
 * 	1. Write your library whatever you want. (for our advise check out our documents)
 * 	2. Add your library here (in @chModule field). 
 * 	3. Add your command and your command function adress here (in @chCmd field) 
 * Thats it. Your library ready to use.
 */

#include <stdio.h>                      /* standard I/O .h-file               */
#include <string.h>
#include <ctype.h>                      /* character functions                */
#include "..\terminal.h"                /* getline function 				  */

/** @addtogroup CHSHELL
  * @{
  */

/** @addtogroup chshell_core
  * @{
  */  

/** @addtogroup CHSHELL_Module_Libraries
  * @{
  */

	/* 
	 * Add your module library here.
	 * Example :
	 * #include "chshell_module_xxx.h"
	 */
	#include "chshell_module_gpio.h"
	#include "chshell_module_system.h"
	#include "chshell_module_adc.h"

/**
  * @}
  */


#define MAX_CMD_SIZE 70 

static char* user = "root"; 

char cmdbuf[MAX_CMD_SIZE]; //stream of keyboard data

char* argv[MAX_CMD_SIZE] = {NULL};
int argc = 0;

/** @addtogroup CHSHELL_Module_Structs
  * @{
  */
	typedef struct{
		char* ch_module_name;
		int (*ch_module_addr)(int,char**); 
	}chshell_cmd;
/**
  * @}
  */

/*
 * @chCmd
 * Module command and function 
 * Add your module library command here.
 * Example : { module_command, &module_main_function_address },
 */
chshell_cmd ch_cmd[] = {
	{ "gpio", 	&ch_module_gpio   },
	{ "adc", 	&ch_module_adc    },
	{ "reboot", &ch_module_reboot },
	{ "clear", 	&ch_module_clear  },
	{ "color", 	&ch_module_color  },
	{ "user", 	&ch_user 		  },
	/* Last index must be this   */
	{ 0,        &unknown_command  }
};
/*
 * @endChCmd
 */


/**
  * @brief  .
  * @note   .
  * @param  .
  * @retval .
  */
int chshellStart(){
	int i = 0;
	char* tok;
	while(1){
		printf("[%s@chshell ~]$ ",user);	

		/* waiting for the enter or limit of command */		
		while(!getline (&cmdbuf[0], sizeof (cmdbuf))); 

		/* \n and \r is a problem in parsing command. This function clear the \n and \r in stream data (cmdbuf) */

		i = 0;
		while(cmdbuf[i]) i++; /* find last index of the data */

		/* and delete \n and \r */

		cmdbuf[i-1] = NULL;
		cmdbuf[i-2] = NULL;

		/* Getopt need argv type of data. This part split the cmdbuf and fill the argv  */

		argc = 0;
		for (tok = strtok(cmdbuf, " "); tok && 
			 *tok; tok = strtok(NULL, " ")) argv[argc++] = tok; 
			//printf("Part %i, value: %s\n",argc, argv[argc]);

		/* empty command detection */
		if(!argv[0])
			 continue;

		/* This part chechk the argv's first index and find the module. Than call the module default function (in chshell_cmd struct) 
		 * If there is no module name in argv[0] than this part call the unknown_command function
		 */
		i = 0;
		while(strcmp(argv[0],ch_cmd[i].ch_module_name) && // find module
			  i < (sizeof(ch_cmd) / sizeof(chshell_cmd) - 1)) i++; 
		ch_cmd[i].ch_module_addr(argc,argv); //call module
	}


	return 1; //Never return
}

int unknown_command(int x, char** y){
	printf("chshell: %s: Unknown Command!\n",argv[0]);
	return 0;
}
int ch_user(int x, char** y){
	// user -n usr_name
	strcpy(user,argv[2]);
	return 0;
}

/**
  * @}
  */

/**
  * @}
  */
