#pragma once
#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define DEBUG_OUTPUT false
#define MINUS_ONE true

struct charArray {
	int size;
	char* contents;
};

charArray readFromFile(char* path);
void charArrayToIntArray(charArray* cArray, int* intArray);
int* goldCodeGenerator(int t, int a, int b);


/*
1. GPS Sequenz einlesen
Datei -> signed int array mit 1023 Einträgen [1023]
z.B.: int gps_chipsequence[1023]

2. Satellitenchipsequenzen berechnen
Codegenerator -> signed int array mit 1023 Einträgen pro Satellit
z.B. int satellite_chip_sequence[24][1023];
Chipsequenz 0 => -1

static int satellite_cs_generator_register_matrix[][2] = {        {1, 5},        {2, 6},        {3, 7},        {4, 8},        {0, 8},        {1, 9},        {0, 7},        {1, 8},        {2, 9},        {1, 2},        {2, 3},        {4, 5},        {5, 6},        {6, 7},        {7, 8},        {8, 9},        {0, 3},        {1, 4},        {2, 5},        {3, 6},        {4, 7},        {5, 8},        {0, 2},        {3, 5}};

#!!!Rauschschwelle/Orrelationswerte errechnen!!!#
    possible_correlation_values[0] = (int) (-pow(2, ((REGISTER_LENGTH + 2) / 2))) - 1; = -65
    possible_correlation_values[1] = -1;
    possible_correlation_values[2] = (int) (pow(2, ((REGISTER_LENGTH + 2) / 2))) - 1;  = 63
    
    MAX_PEAK_SIZE = 1023
    NUM_SATELLITES_IN_SIGNAL = 4
    
    zero_bit_peak = -MAX_PEAK_SIZE - (NUM_SATELLITES_IN_SIGNAL * possible_correlation_values[0]);    = -763
    one_bit_peak = MAX_PEAK_SIZE + (NUM_SATELLITES_IN_SIGNAL * possible_correlation_values[0])       =  763

3. Jede Chipsequenz mit Summensignal (aus Datei) kreuzkorrelieren
für jeden Satellit
	für jede mögliche Verschiebung x der Chipsequenz des Satelliten (0..1022) //modulo 1023 um am ende umzubrechen an array-grenze
		berechne Skalarprodukt von Satellitenchipsequenz mit Summensignal verschoben um x
		 ==> Vergleiche
		  -> < Zero Bit Peak == Satellit hat Bit 0 gesendet
		  -> > One Bit Peak == Satellit hat Bit 1 gesendet
		  -> kein Match für Satellit bei jeder Verschiebung => s nicht in Summensignal
*/