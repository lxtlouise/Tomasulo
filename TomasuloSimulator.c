/*
 * TomasuloSimulator.c
 *
 *  Created on: Oct 1, 2015
 *      Author: DebashisGanguly
 */

#include "./Global/TomasuloSimulator.h"

int numberOfIntRegisters = 32; //NIR
int numberOfFPRegisters = 32; //NFPR

int instructionCacheBaseAddress = 1000; //ICBA

int cacheLineSize = 4; //CLS


int main(int argc, char** argv) {

	//Validate command line argument
	if (argc != 3) {
		printf ("USAGE: TomasuloSimulator <benchmark_file> <config_file>\n");
		exit (EXIT_FAILURE);
	}

	config = (Config*)malloc(sizeof(Config));
	read_configfile(argv[2]);

	fillInstructionAndDataCache (argv[1]); //call loader to fill caches

	printInstructionCache (); //print instruction cache

	printDataCache ();

	printCodeLabels (); //print data cache

	initializeCPU (); //initialize CPU data structure

	initializeIF_Unit(); // initialize IF unit

	while (runClockCycle()); //loop emulating simulator clock cycles

	printDataCache (); //print data cache


	printIntegerRegisters (); //print integer registers
	printFPRegisters (); //print floating point registers

	return 0;
}
