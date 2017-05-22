#include "main.h"

int satellites[24][3];

int main(int argc, char *argv[]){

	//Gold Code Generator Data Basis
	satellites[0][0] = 5;
	satellites[0][1] = 2;
	satellites[0][2] = 6;
	satellites[1][0] = 6;
	satellites[1][1] = 3;
	satellites[1][2] = 7;
	satellites[2][0] = 7;
	satellites[2][1] = 4;
	satellites[2][2] = 8;
	satellites[3][0] = 8;
	satellites[3][1] = 5;
	satellites[3][2] = 9;
	satellites[4][0] = 17;
	satellites[4][1] = 1;
	satellites[4][2] = 9;
	satellites[5][0] = 18;
	satellites[5][1] = 2;
	satellites[5][2] = 10;
	satellites[6][0] = 139;
	satellites[6][1] = 1;
	satellites[6][2] = 8;
	satellites[7][0] = 140;
	satellites[7][1] = 2;
	satellites[7][2] = 9;
	satellites[8][0] = 141;
	satellites[8][1] = 3;
	satellites[8][2] = 10;
	satellites[9][0] = 251;
	satellites[9][1] = 2;
	satellites[9][2] = 3;
	satellites[10][0] = 252;
	satellites[10][1] = 3;
	satellites[10][2] = 4;
	satellites[11][0] = 254;
	satellites[11][1] = 5;
	satellites[11][0] = 6;
	satellites[12][1] = 255;
	satellites[12][2] = 6;
	satellites[12][0] = 7;
	satellites[13][1] = 256;
	satellites[13][0] = 7;
	satellites[13][1] = 8;
	satellites[14][0] = 257;
	satellites[14][1] = 8;
	satellites[14][2] = 9;
	satellites[15][0] = 258;
	satellites[15][1] = 9;
	satellites[15][2] = 10;
	satellites[16][0] = 469;
	satellites[16][1] = 1;
	satellites[16][2] = 4;
	satellites[17][0] = 470;
	satellites[17][1] = 2;
	satellites[17][2] = 5;
	satellites[18][0] = 471;
	satellites[18][1] = 3;
	satellites[18][2] = 6;
	satellites[19][0] = 472;
	satellites[19][1] = 4;
	satellites[19][0] = 7;
	satellites[20][1] = 473;
	satellites[20][0] = 5;
	satellites[20][1] = 8;
	satellites[21][2] = 474;
	satellites[21][0] = 6;
	satellites[21][1] = 9;
	satellites[22][2] = 509;
	satellites[22][0] = 1;
	satellites[22][1] = 3;
	satellites[23][2] = 512;
	satellites[23][2] = 4;
	satellites[23][2] = 6;

	charArray cA;
	int* intArray = new int[1023];

	cA = readFromFile("gps_sequence_3.txt");
	charArrayToIntArray(&cA, intArray);

	for(int i=0; i<1023; i++){
		printf("%d ", intArray[i]);
	}

	free(goldCodeGenerator(5, 2, 6));

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