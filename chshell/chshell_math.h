#include <string.h>
#define error 0

void mathCmdParse(shell_cmd_args *args){
	/*
	Birinci parametreyi al
	Eşittire kadar gel
	İkinci parametre içinde aritmetiksel ve mantıksal operatörleri ara
	Eğer yoksa ikinci parametreyi al ve işleme sok
	Eğer varsa hangisi olduğunu bul ve işleme sok
	*/
	if(args->count < 3) return error;
	else if(args->count == 3){
		
	}
	else{
	int parameter = (args->count-2)/2;
	}
	mathCmdProcess(parameter1,parameter2,opr);
}