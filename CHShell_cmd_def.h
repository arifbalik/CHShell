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
#ifndef CMD_DEF
#define CMD_DEF
#include "shell.h"
#include "CHShell_loop.h"
#include "CHShell_gpio.h"
#include "CHShell_delay.h"

#define GPIO_CMD "gpio"
#define GPIO_DESC "GPIO Initialize, read and write operation\nParameters;\n -mode <i:initialize, w:write r:read reset:reset>\n -port <a-g>\n -type <o:output, i:input, a:analog, f:alternative function>\n -speed <(MHZ) 2, 25, 50 or 100>\n -pin <0-15 and a: All pin>\n -otype <p: push-pull, o: open drain>\n -pupd <u: pull-up, d: pull-down, n: no-pull>\n\nExample : gpio -mode i -port d -type o -speed 25 -pin a -otype p -pupd u\n"

int shell_cmd_help(shell_cmd_args *args);
shell_cmd cmd[]={
	{"help","list available commands",shell_cmd_help},
	{GPIO_CMD,GPIO_DESC,gpioCmdParse},
	{"loop","loop",loopCmdParse},
	{"delay","delay",delayCmdParse}
};
shell_cmds komutlar = {4,cmd};
#endif
