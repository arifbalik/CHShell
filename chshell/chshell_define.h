
#include "shell.h"
#include <string.h>

#define MAX_DEFINE 100
#define error 0;
#define AYRAC ":"
char* getCmdData(char* defDataParse);
void addDefine(char* defineData,char* defineCmdData);
char* getCmd(char* defCmd);
int isDefinationsData(char* defData);
int defineCmdParse(shell_cmd_args *args);

char* define;

int defineCmdParse(shell_cmd_args *args){
    addDefine(args->args[0].val,args->args[2].val);
	return 1;
}
void addDefine(char* defineData,char* defineCmdData){
	strcat(define,defineData);
    strcat(define,AYRAC);
    strcat(define,defineCmdData);
    strcat(define,AYRAC);
}
char* getCmdData(char* defDataParse){
	char* cmd;
	char* tok;
	char* solvedCmd;
	for (tok = strtok(defDataParse, "_ "); tok && *tok; tok = strtok(NULL, "_ ")) {  
		if(strstr(tok,"_") != NULL){
			solvedCmd = getCmd(tok);
			
			strcat(cmd,solvedCmd);
		}
		else{
			strcat(cmd,tok);
		}
	}
	return cmd;
}
char* getCmd(char* defCmd){
	char* tok;
	if(strstr(defCmd,define) == NULL) return error;
	for (tok = strtok(define, AYRAC); tok && *tok; tok = strtok(NULL, AYRAC)) {  
		if(!strcmp(tok,defCmd)){
			tok = strtok(NULL, AYRAC);
			return tok;
		}
	}
	return error;
}
int isDefinationsData(char* defData){
	return strstr(defData,"_") != NULL ? 1 : 0;
}
