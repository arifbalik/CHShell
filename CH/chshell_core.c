#include <stdio.h>                      /* standard I/O .h-file               */
#include <string.h>
#include <ctype.h>                      /* character functions                */
#include "chshell_gpio.h"
#include "chshell_system.h"
#include "chshell_adc.h"

typedef struct{
	char* ch_module_cmd;
	int (*ch_module_addr)(int,char**); 
}chshell_cmd;

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

int token(char* cmdbuf){
			
		int i = 0;
		char* argv[70] = {NULL};
		int argc = 0;
		char* tok;
	
	
		while(cmdbuf[i] != NULL) i++; //find last index of the data
		//and delete \n and \r
		cmdbuf[i-1] = NULL;
		cmdbuf[i-2] = NULL;
		i = 0;
		
		for (tok = strtok(cmdbuf, " "); tok && *tok; tok = strtok(NULL, " ")) argv[argc++] = tok; //printf("Part %i, value: %s\n",argc, argv[i]);

		if(argv[0] == NULL) //empty entry detection
			return 0;
				
		//compare the module list with argv's first index value and call the function. the module list and ch is same index number
		while(strcmp(argv[0],ch_cmd[i].ch_module_cmd) && i < sizeof(ch_cmd)) i++;
		if(i != sizeof(ch_cmd)) //meaningless entry detetcion
			ch_cmd[i].ch_module_addr(argc,argv);
		

		return 1;
	}

