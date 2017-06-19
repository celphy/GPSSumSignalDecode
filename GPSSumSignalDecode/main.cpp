#include "main.h"

int satellites[24][3];
int T = 0;
int A = 1;
int B = 2;


/*
    Example: 
    x: [3,7,1]
    y: [4,1,9]
    size: 3
    result = (3 * 4) + (7 * 1) + (1 * 9) = 12 + 7 + 9 = 28
*/
int scalarProduct(int* x, int* y, int size){ 
  int result = 0;
  for (int i = 0; i < size; i++) {
      result += x[i] * y[i];
  }
  return result; 
}

int* rotate (int* array, int size, int rotation) {
    int* newArray = (int*)malloc(size*sizeof(int));
    for (int i = 0; i < size; i++) {
        newArray[i] = array[(i + rotation) % size];
    }
    return newArray;
}


int REGISTER_LENGTH = 10;

    
int MAX_PEAK_SIZE = 1023;
int NUM_SATELLITES_IN_SIGNAL = 4;
    



int main(int argc, char *argv[]){

	int possible_correlation_values[3];
	possible_correlation_values[0] = -pow((double)2, (REGISTER_LENGTH+2)/2)-1;//(int) //(-pow(2, ((REGISTER_LENGTH + 2) / 2))) - 1;// -65
	possible_correlation_values[1] = -1;
	possible_correlation_values[2] = pow((double)2, (REGISTER_LENGTH+2)/2)-1;//(int) (pow(2, ((REGISTER_LENGTH + 2) / 2))) - 1;// 63

	int zero_bit_peak = -MAX_PEAK_SIZE - (NUM_SATELLITES_IN_SIGNAL * possible_correlation_values[0]);// -763
	int one_bit_peak = MAX_PEAK_SIZE + (NUM_SATELLITES_IN_SIGNAL * possible_correlation_values[0]);// 763

	if(DEBUG_OUTPUT)
	printf("Zero bit peak %d One bit peak %d\n", zero_bit_peak, one_bit_peak);
	//Gold Code Generator Data Basis

	satellites[0][T] = 5;
	satellites[0][A] = 2;
	satellites[0][B] = 6;
	satellites[1][T] = 6;
	satellites[1][A] = 3;
	satellites[1][B] = 7;
	satellites[2][T] = 7;
	satellites[2][A] = 4;
	satellites[2][B] = 8;
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
	satellites[11][2] = 6;
	satellites[12][0] = 255;
	satellites[12][1] = 6;
	satellites[12][2] = 7;
	satellites[13][0] = 256;
	satellites[13][1] = 7;
	satellites[13][2] = 8;
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
	satellites[19][2] = 7;
	satellites[20][0] = 473;
	satellites[20][1] = 5;
	satellites[20][2] = 8;
	satellites[21][0] = 474;
	satellites[21][1] = 6;
	satellites[21][2] = 9;
	satellites[22][0] = 509;
	satellites[22][1] = 1;
	satellites[22][2] = 3;
	satellites[23][0] = 512;
	satellites[23][1] = 4;
	satellites[23][2] = 6;

	charArray cA;
	int* intArray = new int[1023];
	int* chipSequences[24];

	if(DEBUG_OUTPUT){
	int test1[] = { 3, 7, 1 };
	int test2[] = { 4, 1, 9 };
	printf("Scalartest: %d", scalarProduct(test1, test2, 3));
	rotate(test1, 3, 1);
	printf("test1 : %d %d %d", rotate(test1, 3, 1)[0], rotate(test1, 3, 1)[1], rotate(test1, 3, 1)[2]);
	}

	cA = readFromFile(argv[1]);
	if(cA.size == 0)
		return 0;
	charArrayToIntArray(&cA, intArray);

	if(DEBUG_OUTPUT){
	for(int i=0; i<1023; i++){
		printf("%d ", intArray[i]);
	}
	printf("\n");
	}
	
	for(int i=0; i<24;i++){
		chipSequences[i] = goldCodeGenerator(satellites[i][0], satellites[i][1], satellites[i][2]);
		if(DEBUG_OUTPUT)
		printf("Chip sequence satellite %d: ", i);
		for(int j = 0; j<1023; j++){
			if(DEBUG_OUTPUT)
			printf("%d", *(chipSequences[i]+j));
		}
		if(DEBUG_OUTPUT)
		printf("\n");
	}
	
	for (int sequenzIndex = 0; sequenzIndex < 24; sequenzIndex++) {
		printf("Checking satellite %d\n", sequenzIndex+1);
        int* goldCode = chipSequences[sequenzIndex];
        for (int tDelta = 0; tDelta < 1022; tDelta++) {
            int scalarP = scalarProduct(rotate(goldCode, 1023, tDelta), intArray, 1023); // + um tDelta rotieren?
			//printf("Scalar: %d\n", scalarP);
            //scalarP(int* goldCodeRotiertUmtDelta, int* summenSignal);
            //int code = goldCode[tDelta];
			//printf("Skalarprodukt: %d\n", scalarP);
            if (scalarP > one_bit_peak) {
                printf("Satellite %d has sent bit %d (delta %d)\n", sequenzIndex + 1, 1, tDelta);
				break;
            } else if (scalarP < zero_bit_peak) {
                printf("Satellite %d has sent bit %d (delta %d)\n", sequenzIndex + 1, 0, tDelta);
				break;
            } else {
				//Rauschen
            }
        }
    }

	printf("\nDone\n");
	getchar();
	return 0;
}


//We generate the code sequence here
int* goldCodeGenerator(int t, int a, int b) {
	int newRegister1, newRegister2;
	//The two registers needed to calculate stuff
	int register1[10], register2[10];
	//Return ouptut - don't forget to free
	int* output = (int*)malloc(sizeof(int) * 1023);
	//Initialize registers with 1
	for (int i = 0; i < 10; i++) {
		register1[i] = 1;
		register2[i] = 1;
	}
	if(DEBUG_OUTPUT)
	printf("\n");
	//Generate 1023 numbers
	for (int i = 0; i < 1023; i++) {

		if(DEBUG_OUTPUT){
		//Print Array1 from Generator
		printf("Array1 [");
		for(int j = 0; j < 10; j++){
			printf("%d", register1[j]);
		}
		printf("]   ");

		//Print Array2 from Generator
		printf("Array2 [");
		for(int j = 0; j < 10; j++){
			printf("%d", register2[j]);
		}
		printf("]\n");
		}
		//Calculate output bit
		output[i] = register1[9] ^ (register2[a-1] ^ register2[b-1]);
		if(output[i] == 0 && MINUS_ONE)
			output[i] = -1;

		newRegister1 = register1[9] ^ register1[2];
		newRegister2 = register2[1] ^ register2[2] ^ register2[5] ^ register2[7] ^ register2[8] ^ register2[9];

		//Shift registers
		for (int j = 9; j > 0; j--) {
			register1[j] = register1[j - 1];
			register2[j] = register2[j - 1];
		}

		//Calculate new register bit 0 for 1 and 2
		register1[0] = newRegister1;
		register2[0] = newRegister2;

		
		
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
	if(path == NULL)
	{
		charArray r;
		r.size = 0;
		return r;
	}
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