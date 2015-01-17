#include "shell.h"
#include "CHShell_usart.h"
 volatile char received_string[MAX_STRLEN+1]; // this will hold the recieved string
int buffer_flag;
void CHTerminalCmdEcho(char* echo);
int main(void) {
	init_USART1(9600);
	CHTerminalPrint("System Initialize..\n");
	CHTerminalPrint("CHShell v0.1  Copyright (C) 2015  Arif Ahmet Balik\nThis program comes with ABSOLUTELY NO WARRANTY; for details type `help -w'.\nThis is free software, and you are welcome to redistribute it\nunder certain conditions; type `help -c' for details.\n");
    while (1) {
			if(buffer_flag){
				buffer_flag = 0;
				CHTerminalCmdEcho((char*)received_string);
				switch(shell_process((char*)received_string))
				{
					 case SHELL_PROCESS_ERR_CMD_UNKN:
							CHTerminalPrint("Unknown command\n");
							break;
					 case SHELL_PROCESS_ERR_ARGS_LEN:
							CHTerminalPrint("Argument to long\n");
							break;
					 case SHELL_PROCESS_ERR_ARGS_MAX:
							CHTerminalPrint("Too many arguments\n");
							break;
					 default:
							// OK
							break;
				}
				clear_buffer();
			}
		}
}
void CHTerminalCmdEcho(char* echo){
	 CHTerminalPrint("root@CHShell>");
	 CHTerminalPrint(echo);
	 CHTerminalPrint("\n");
}
	
