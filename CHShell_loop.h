#ifndef CHSHELL_LOOP_H
#define CHSHELL_LOOP_H
#include "shell.h"
#include "CHShell_usart.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
	char cmdL[250];

int loopCmdParse(shell_cmd_args *args);
int loopCmdProcess(char* loop,char* def);
int loopGetCmd(char* def);

int loopCmdParse(shell_cmd_args *args){
	int i;
	char* loopDef;
		for(i = 0; i<args->count;i = i+2){
			if(!strcmp(args->args[i].val,"-l")){
					loopDef=args->args[++i].val;
					CHTerminalPrint(" Length Select: ");
					CHTerminalPrint(args->args[i].val);
					CHTerminalPrint("\n");
			}
			else if(!strcmp(args->args[i].val,"-i")){
				loopDef = "i";
				CHTerminalPrint(" Infinity Select\n");
			}
			else{
				if(strstr(args->args[i].val,"-")!=NULL){
					CHTerminalPrint(" Error - Unknown parameter: ");
					CHTerminalPrint(args->args[i].val);
					CHTerminalPrint("\n");
					i++;
					return 0;
				}
			}
			i--;
		}
		clear_buffer();
		CHTerminalPrint("Code:\n");
		loopGetCmd(loopDef);
		return 0;
}
int loopGetCmd(char* def){
	int i = 1;
	while(1){
		if(buffer_flag){
			if(strcmp((char*)received_string,"end") != 0){
				buffer_flag = 0;
				CHTerminalPrint("$");
				strcat(cmdL,(char*)received_string);
				strcat(cmdL,";");
				CHTerminalPrint((char*)received_string);
				CHTerminalPrint("\n");
			  clear_buffer();
				i++;
			}
			else{
				CHTerminalPrint("Code Loop Starting..");
				//while(1){
				loopCmdProcess(cmdL,def);
				//}
				break;
			}
		}
}
	return 0;
}

int loopCmdProcess(char *loop,char* def){
	char* tok;
	int i;
	int lenght;
	char temp[250];
	strcpy(temp,loop);
	if(!strcmp(def,"i")){
		while(1){
			for (tok = strtok(loop, ";"); tok && *tok; tok = strtok(NULL, ";"))  
			{  
				 shell_process(tok);  
			}
			strcpy(loop,temp);
		}
	}
	else{
		lenght = atoi(def);
		for(i=0;i<lenght;i++){
		for (tok = strtok(loop, ";"); tok && *tok; tok = strtok(NULL, ";"))  
			{  
				 shell_process(tok);  
			}
			strcpy(loop,temp);
		}
	}
	return 0;
}
#endif
