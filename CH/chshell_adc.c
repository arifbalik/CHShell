#include "tm_stm32_adc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../getopt.h"

ADC_TypeDef* adc = ADC1;
TM_ADC_Channel_t channel = TM_ADC_Channel_0;

TM_ADC_Channel_t adc_channel_list[] = {
	TM_ADC_Channel_0, 			 /*!< Operate with ADC channel 0 */
	TM_ADC_Channel_1,        /*!< Operate with ADC channel 1 */
	TM_ADC_Channel_2,        /*!< Operate with ADC channel 2 */
	TM_ADC_Channel_3,        /*!< Operate with ADC channel 3 */
	TM_ADC_Channel_4,        /*!< Operate with ADC channel 4 */
	TM_ADC_Channel_5,        /*!< Operate with ADC channel 5 */
	TM_ADC_Channel_6,        /*!< Operate with ADC channel 6 */
	TM_ADC_Channel_7,        /*!< Operate with ADC channel 7 */
	TM_ADC_Channel_8,        /*!< Operate with ADC channel 8 */
	TM_ADC_Channel_9,        /*!< Operate with ADC channel 9 */
	TM_ADC_Channel_10,       /*!< Operate with ADC channel 10 */
	TM_ADC_Channel_11,       /*!< Operate with ADC channel 11 */
	TM_ADC_Channel_12,       /*!< Operate with ADC channel 12 */
	TM_ADC_Channel_13,       /*!< Operate with ADC channel 13 */
	TM_ADC_Channel_14,       /*!< Operate with ADC channel 14 */
	TM_ADC_Channel_15,       /*!< Operate with ADC channel 15 */
	TM_ADC_Channel_16,       /*!< Operate with ADC channel 16 */
	TM_ADC_Channel_17,       /*!< Operate with ADC channel 17 */
	TM_ADC_Channel_18       /*!< Operate with ADC channel 18 */
};
char* adc_channel_name[] = {
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"10",
	"11",
	"12",
	"13",
	"14",
	"15",
	"16",
	"17",
	"18",
};
ADC_TypeDef* adc_list[] = {
	ADC1,
	ADC2,
	ADC3
};
char* adc_name_list[] = {
	"1",
	"2",
	"3"
};

ADC_TypeDef* getModule(char* module) {
	int i = 0;
	while(strcmp(adc_name_list[i], module) && i < sizeof(adc_name_list)) i++;
	return adc_list[i]; 
}
TM_ADC_Channel_t getChannel(char* channel) {
	int i = 0;
	while(strcmp(adc_channel_name[i], channel) && i < sizeof(adc_channel_name)) i++;
	return adc_channel_list[i]; 
}
int adc_flag;	
int ch_getopt_adc(int argc, char** argv)
{
	int c;
  while (1)
    {
      static struct option long_options[] =
        {
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"module",  	required_argument, 0, 'm'},
          {"channel",  	required_argument, 0, 'c'},
					{"read",  	no_argument, &adc_flag, 1},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

				c = getopt_long_only(argc, argv, "g:p:l:m:s:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;
	
      switch (c)
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          
          break;
				case 'm':
					adc = getModule(optarg);
          break;
				case 'c':
					channel = getChannel(optarg);
          break;
				
        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          printf ("Something happend!");
				break;
        }
    }
		if(adc_flag) {
			printf("ADC Reading : ");
			while(1){
				printf("%d",TM_ADC_Read(adc,channel));
				putchar(0x08);
				putchar(' ');
				putchar(0x08);
				//while(1){}
				//osDelay(200);
			}
		}
			


  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    }
		optind = 0;
		
		TM_ADC_Init(adc,channel);
	return 1;
}
