#include "stm32f7xx_hal.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../getopt.h"


long color_def[] = {
	GLCD_COLOR_GREEN,
	GLCD_COLOR_BLACK,
	GLCD_COLOR_YELLOW,
	GLCD_COLOR_NAVY,
	GLCD_COLOR_DARK_GREEN,
	GLCD_COLOR_DARK_CYAN,
	GLCD_COLOR_MAROON,
	GLCD_COLOR_PURPLE,
	GLCD_COLOR_OLIVE,
	GLCD_COLOR_DARK_GREY,
	GLCD_COLOR_BLUE,
	GLCD_COLOR_CYAN,
	GLCD_COLOR_RED,
	GLCD_COLOR_MAGENTA,
	GLCD_COLOR_WHITE
};
char* color[] = {
	"green",
	"black",
	"yellow",
	"navy",
	"dgreen",
	"dcyan",
	"maroon",
	"purple",
	"olive",
	"dgrey",
	"blue",
	"cyan",
	"red",
	"magenta",
	"white"
};

int ch_module_reboot(int argc, char** argv){
		HAL_NVIC_SystemReset();
		return 1;
}
int ch_module_clear(int argc, char** argv){
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	  //GLCD_ClearScreen();  	
	return 1;
}
int ch_module_color(int argc, char** argv){
  int i = 0;
  int index;
  int c;

  opterr = 0;
  while ((c = getopt (argc, argv, "f:b:")) != -1)
    switch (c)
      {
      case 'f':
        while(strcmp(color[i],optarg) && i < 15) i++;
			GLCD_SetForegroundColor (color_def[i]);
			i = 0;
        break;
		case 'b':
			while(strcmp(color[i],optarg) && i < 15) i++;
			GLCD_SetBackgroundColor (color_def[i]);
			i = 0;
        break;
      case '?':
        if (optopt == 'c')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        //abort ();
			break;
      }
  
  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);
	optind = 0;
	return 1;
}



