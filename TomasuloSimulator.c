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

int CDB_counter = 0;


int main(int argc, char** argv) {

	//Validate command line arguments
	if (argc <2) {
		printf ("USAGE: TomasuloSimulator <benchmark_file1> [<benchmark_file2>]\n");
		exit (EXIT_FAILURE);
	}

	config = (Config*)malloc(sizeof(Config));
	read_configfile(ENV_CONFIG_FILE);

    printf("----------------------- THREAD 0 -------------------------\n\n");
	InitializeThread(0, &(threads[0]), argv[1]);

    printf("----------------------- THREAD 1 -------------------------\n\n");
	InitializeThread(1, &(threads[1]), argc>=3?argv[2]:NULL);

	initializeCPU (); //initialize CPU data structure

	initializeFetch(); // initialize IF unit

	initializeDecode();

	initializeIssue();

	initializeExecute();

	while (runClockCycle()>0); //loop emulating simulator clock cycles

    printState(); // print CPU state

	return 0;
}
