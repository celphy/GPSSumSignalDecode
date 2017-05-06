#include "main.h"

int main(int argc, char *argv[]){
	return 0;
}

charArray readFromFile(char* path){
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