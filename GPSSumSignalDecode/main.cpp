#include "main.h"

int main(int argc, char *argv[]){
	return 0;
}

void readFromFile(char* path){
	FILE * file;
	file = fopen(path, "r");
	if(file){
		
	} else {
		printf("File doesn't exist.\n");
	}
}