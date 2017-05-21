#include "main.h"

int main(int argc, char *argv[]){
	charArray cA;
	int* intArray = new int[1023];

	cA = readFromFile("gps_sequence_3.txt");
	charArrayToIntArray(&cA, intArray);

	for(int i=0; i<1023; i++){
		printf("%d ", intArray[i]);
	}
	getchar();
	return 0;
}


//We generate the code sequence here
bool* goldCodeGenerator(int t, int a, int b) {
	//The two registers needed to calculate stuff
	bool register1[10], register2[10];
	//Return ouptut - don't forget to free
	bool* output = (bool*)malloc(sizeof(bool) * 1023);
	//Initialize registers with 1
	for (int i = 0; i < 10; i++) {
		register1[i] = true;
		register2[i] = true;
	}
	//Generate 1023 numbers
	for (int i = 0; i < 1023; i++) {
		//Calculate output bit
		output[i] = register1[9] ^ (register2[a-1] ^ register2[b-1]);
		//Calculate new register bit 0 for 1 and 2
		register1[0] = register1[9] ^ register1[2];
		register2[0] = register2[1] ^ register2[2] ^ register2[5] ^ register2[7] ^ register2[8];

		for (int j = 9; j > 0; j--) {
			register1[j] = register1[j - 1];
			register2[j] = register2[j - 1];
		}
		
	}
	return output;
}


void charArrayToIntArray(charArray* cArray, int* intArray){
	size_t i, parsed;
	short sign = 1;

	for(i=0,parsed=0; i<cArray->size;i++){
		//Skip blanks
		if(cArray->contents[i] != ' '){
			//Do we have a leading '-'?
			if(cArray->contents[i] == '-') {
				sign = -1; //So we have a negative number
			} else { //No leading '-'
				int value = (int)(cArray->contents[i] - '0'); //We convert the char representation to int
				intArray[parsed] = sign * value; //Fill in signed number
				parsed++;
				sign = 1;
			}
		}
	}
}

charArray readFromFile(char* path) {
	//Handle to file
	FILE * file;
	//Size of content
	long size;
	//Content buffer
	char* buffer;
	//Open it and determine size
	file = fopen(path, "r");
	fseek(file,0L,SEEK_END);
	size = ftell(file);
	rewind(file);
	//Allocate memory for the contents and try to fill it
	buffer = (char*)malloc(size+1);
	if( 1 != fread(buffer,size,1,file)){
		fclose(file);
		free(buffer);
		printf("Reading file failed.\n");
	}
	//Assemble return package
	charArray r;
	r.size = size;
	r.contents = buffer;
	//Return the package
	return r;
}