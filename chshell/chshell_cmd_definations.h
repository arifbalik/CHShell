#ifndef CMD_DEF
#define CMD_DEF
#include "shell.h"
#include "CHShell_loop.h"
#include "chshell_define.h"
#include "CHShell_gpio.h"
#include "CHShell_delay.h"


#define GPIO_CMD "gpio"
#define GPIO_DESC "GPIO Initialize, read and write operation\nParameters;\n -mode <i:initialize, w:write r:read reset:reset>\n -port <a-g>\n -type <o:output, i:input, a:analog, f:alternative function>\n -speed <(MHZ) 2, 25, 50 or 100>\n -pin <0-15 and a: All pin>\n -otype <p: push-pull, o: open drain>\n -pupd <u: pull-up, d: pull-down, n: no-pull>\n\nExample : gpio -mode i -port d -type o -speed 25 -pin a -otype p -pupd u\n"

extern int shell_cmd_help(shell_cmd_args *args);
extern shell_cmd cmd[]={
	{"help","list available commands",shell_cmd_help},
	{GPIO_CMD,GPIO_DESC,gpioCmdParse},
	{"loop","loop",loopCmdParse},
	{"delay","delay",delayCmdParse},
	{"define","define",defineCmdParse}
};
extern shell_cmds komutlar = {5,cmd};
#endif
