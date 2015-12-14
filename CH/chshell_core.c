  /*
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

#include <stdio.h>                      /* standard I/O .h-file               */
#include <string.h>
#include <ctype.h>                      /* character functions                */
#include "terminal.h"                   /* getline function 				  */
#include "chshell_gpio.h"
#include "chshell_system.h"
#include "chshell_adc.h"


#define MAX_CMD_SIZE 70 

static char cmdbuf[MAX_CMD_SIZE]; //stream of keyboard data
char* argv[MAX_CMD_SIZE] = {NULL};
int argc = 0;

typedef struct{
	char* ch_module_name;
	int (*ch_module_addr)(int,char**); 
}chshell_cmd;

//Mudoule command and function
chshell_cmd ch_cmd[] = {
	{
		"gpio",
		&ch_getopt_gpio
	},
	{
		"reboot",
		&ch_system_reboot
	},
	{
		"clear",
		&ch_system_clear
	},
	{
		"color",
		&ch_system_color
	},
	{
		"adc",
		&ch_getopt_adc
	},
};

int chshellStart(){

	char* tok;
	int i = 0;

	while(1){
		printf("root@chshell>");			
		while(!getline (&cmdbuf[0], sizeof (cmdbuf))); //waiting for the enter or limit of command

		if(!ch_fill_argv()) 
			continue;
			
		ch_call_module();	
	}

		return 1;
	}

/**
 *	@brief  	\n and \r is a problem in parsing command. In this function I clear the \n and \r in stream data (cmdbuf)
 *	@parameter  none
 *	@return 	none
*/
void clear_cmdbuf(){
	int i = 0;

	while(cmdbuf[i] != NULL) //find last index of the data
		i++; 
	//and delete \n and \r
	cmdbuf[i-1] = NULL;
	cmdbuf[i-2] = NULL;
}

/**
 *	@brief  	This function chechk the argv's first index and find the module. Than call the module default function (in chshell_cmd struct)
 *	@parameter  none
 *	@return 	if there is no defined module name in first index, function will return 0, otherwise return 1
*/
int ch_call_module(){
	int i = 0;
	while(strcmp(argv[0],ch_cmd[i].ch_module_name) && i < sizeof(ch_cmd)) i++;
	if(i != sizeof(ch_cmd)) //meaningless entry detetcion
		ch_cmd[i].ch_module_addr(argc,argv); //call module
	else return 0;

	return 1;
}

/**
 *	@brief  	Getopt need argv type of data. This line split the cmdbuf and fill the argv  
 *	@parameter  none
 *	@return 	if argv is empty than function return 0, otherwise return 1
*/
int ch_fill_argv(){
	argc = 0;
	
	for (tok = strtok(cmdbuf, " "); tok && *tok; tok = strtok(NULL, " ")) argv[argc++] = tok; //printf("Part %i, value: %s\n",argc, argv[argc]);

	if(!argv[0]) //empty command detection
		return 0;

	return 1;
}

