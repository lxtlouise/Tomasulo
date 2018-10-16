/*
 * CPU.c
 *
 *  Created on: Oct 3, 2015
 *      Author: DebashisGanguly
 */

# include "../Global/TomasuloSimulator.h"

int getHashCodeFromPCHash (void *PCHash);

/**
 * This method initializes CPU data structures and all its data members
 */
void initializeCPU () {
	int i;

	cpu = (CPU *) malloc (sizeof(CPU));

	cpu -> cycle = 0;
	cpu -> PC = instructionCacheBaseAddress;

	 //initialize integer registers
	cpu -> integerRegisters = (INTReg **) malloc (sizeof(INTReg *) * numberOfIntRegisters);

	for (i = 0; i < numberOfIntRegisters; i++) {
		cpu -> integerRegisters [i] = (INTReg *) malloc (sizeof(INTReg));
		cpu -> integerRegisters [i] -> data = 0;
		cpu -> integerRegisters [i] -> intResult = 0;
 	}

	 //initialize floating point registers
	cpu -> floatingPointRegisters = (FPReg **) malloc (sizeof(FPReg *) * numberOfFPRegisters);

	for (i = 0; i < numberOfFPRegisters; i++) {
		cpu -> floatingPointRegisters [i] = (FPReg *) malloc (sizeof(FPReg));
		cpu -> floatingPointRegisters [i] -> data = 0.0;
		cpu -> floatingPointRegisters [i] -> fpResult = 0;
 	}

	cpu -> intDestReg = 0;
	cpu -> intResult = 0;

	cpu -> fpDestReg = 0;
	cpu -> fpResult = 0;
}

/**
 * Method that simulates the looping cycle-wise
 * @return: When the simulator stops
 */
int runClockCycle () {
	cpu -> cycle++; //increment cycle counter

	printf ("\nCycle %d\n", cpu -> cycle);


	if (cpu -> PC >= (instructionCacheBaseAddress + (cacheLineSize * numberOfInstruction))) { //check whether PC exceeds last instruction in cache
                printf ("All instructions finished...\n");
		return 0;
        }

	commit();
    runClockCycle_EX();
	Issue();
	decode();
	int _continue = runClockCycle_IF();
	//if (!_continue) return 0;
    return 1;
}

/**
 * Helper method for BHT hash table to calculate hash value from PC
 * @param PCHash
 * @return
 */
int getHashCodeFromPCHash (void *PCHash) {
	return *((int*)PCHash);
}
