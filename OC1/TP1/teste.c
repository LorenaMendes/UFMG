#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char * getBinary(unsigned int decimal){
	char ch_inst[31];
	unsigned int mask=pow(2,31);   //mask = [1000 0000 0000 0000]
	// printf("Binary Eqivalent : ");
	int i = 0;
	while(mask > 0){
		if((decimal & mask) == 0 ){
			// printf("0");
			ch_inst[i] = '0';
		}
		else{
			// printf("1");
			ch_inst[i] = '1';
		}
		mask = mask >> 1 ;  // Right Shift
		i++;
	}
	ch_inst[i] = '\0';
	printf("\n");
	printf("%s\n", ch_inst);
	return *(ch_inst);
}

int main(){
	// FILE *ptr_myfile;
	// int my_record;

	// ptr_myfile = fopen("calculadora","rb");
	// if (!ptr_myfile){
	// 	printf("Unable to open file!");
	// 	return 1;
	// }
	// fread(&my_record, 4, 1, ptr_myfile);
	// my_record = (int)my_record;
	getBinary(16);
	printf("\n");
	return 0;
}