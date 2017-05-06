#pragma once
#include <stdio.h>
#include <malloc.h>

struct charArray {
	int size;
	char* contents;
};

charArray readFromFile(char* path);
void charArrayToIntArray();
void goldCodeGenerator();


