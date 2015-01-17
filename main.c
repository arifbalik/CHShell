/*
     This program is a part of CHShell.
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
	
