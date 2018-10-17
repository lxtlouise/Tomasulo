/*
 * CPU.c
 *
 *  Created on: Oct 3, 2015
 *      Author: DebashisGanguly
 */

# include "../Global/TomasuloSimulator.h"

int getHashCodeFromPCHash (void *PCHash);
int getHashCodeFromCacheAddress_IF (void *address);
int compareBTBValues (void *btbvalue1, void *btbvalue2);

void InitializeThread(Thread* thread, char *fileName){
    int i;
    if(fileName==NULL){
        thread->is_available = 0;
        return;
    }
    thread->is_available = 1;
    fillInstructionAndDataCache (fileName, &(thread->instructionCache), &(thread->dataCache), &(thread->codeLabels));
    thread->ROB = createCircularQueue(config -> NR);
    thread->BTB = createDictionary(getHashCodeFromCacheAddress_IF, compareBTBValues);
    thread->PC = instructionCacheBaseAddress;
    thread->instructionQueue = createCircularQueue(config -> NI);

    //initialize integer registers
	thread -> integerRegisters = (INTReg **) malloc (sizeof(INTReg *) * numberOfIntRegisters);
	for (i = 0; i < numberOfIntRegisters; i++) {
		thread -> integerRegisters [i] = (INTReg *) malloc (sizeof(INTReg));
		thread -> integerRegisters [i] -> data = 0;
		thread -> integerRegisters [i] -> intResult = 0;
 	}

	 //initialize floating point registers
	thread -> floatingPointRegisters = (FPReg **) malloc (sizeof(FPReg *) * numberOfFPRegisters);

	for (i = 0; i < numberOfFPRegisters; i++) {
		thread -> floatingPointRegisters [i] = (FPReg *) malloc (sizeof(FPReg));
		thread -> floatingPointRegisters [i] -> data = 0.0;
		thread -> floatingPointRegisters [i] -> fpResult = 0;
 	}

	// initialize renaming_status
	thread->renaming_status = (Renaming_Status*) malloc(sizeof(Renaming_Status));
	thread->renaming_status -> int_rreg = (int*) malloc(sizeof(int) * RENAMING_INT_REGISTER_NUM);
	for (i = 0; i < RENAMING_INT_REGISTER_NUM; i++) {
		thread->renaming_status -> int_rreg[i] = 0;
	}
	thread->renaming_status -> fp_rreg = (int*) malloc(sizeof(int) * RENAMING_FP_REGISTER_NUM);
	for (i = 0; i < RENAMING_FP_REGISTER_NUM; i++) {
		thread->renaming_status -> fp_rreg[i] = 0;
	}

	// initialize register_status
	thread->register_status = (Register_Status*) malloc(sizeof(Register_Status));
	thread->register_status -> int_reg = (int*) malloc(sizeof(int) * numberOfIntRegisters);
	for (i = 0; i < numberOfIntRegisters; i++) {
		thread->register_status -> int_reg[i] = REGISTER_NOT_BOUND_WITH_ROB;
	}
	thread->register_status -> fp_reg = (int*) malloc(sizeof(int) * numberOfFPRegisters);
	for (i = 0; i < numberOfFPRegisters; i++) {
		thread->register_status -> fp_reg[i] = REGISTER_NOT_BOUND_WITH_ROB;
	}

	// renaming registers
	thread->renaming_int_registers = (INTReg**) malloc(sizeof (INTReg*) * RENAMING_INT_REGISTER_NUM);
	for (i = 0; i < RENAMING_INT_REGISTER_NUM; i++) {
		thread->renaming_int_registers[i] = (INTReg *) malloc (sizeof(INTReg));
		thread->renaming_int_registers[i] -> data = 0;
		thread->renaming_int_registers[i] -> intResult = 0;
 	}
	thread->renaming_fp_registers = (FPReg**) malloc(sizeof (FPReg*) * RENAMING_FP_REGISTER_NUM);
	for (i = 0; i < RENAMING_FP_REGISTER_NUM; i++) {
		thread->renaming_fp_registers[i] = (FPReg *) malloc (sizeof(FPReg));
		thread->renaming_fp_registers[i] -> data = 0;
		thread->renaming_fp_registers[i] -> fpResult = 0;
 	}
	printInstructionCache (thread); //print instruction cache

	printDataCache (thread);

	printCodeLabels (thread); //print data cache

}

/**
 * This method initializes CPU data structures and all its data members
 */
void initializeCPU () {
	int i;

	cpu = (CPU *) malloc (sizeof(CPU));

	cpu -> cycle = 0;
	cpu -> PC = instructionCacheBaseAddress;

	 //initialize integer registers
	/*cpu -> integerRegisters = (INTReg **) malloc (sizeof(INTReg *) * numberOfIntRegisters);

	for (i = 0; i < numberOfIntRegisters; i++) {
		cpu -> integerRegisters [i] = (INTReg *) malloc (sizeof(INTReg));
		cpu -> integerRegisters [i] -> data = 0;
		cpu -> integerRegisters [i] -> intResult = 0;
 	}*/

	 //initialize floating point registers
	/*cpu -> floatingPointRegisters = (FPReg **) malloc (sizeof(FPReg *) * numberOfFPRegisters);

	for (i = 0; i < numberOfFPRegisters; i++) {
		cpu -> floatingPointRegisters [i] = (FPReg *) malloc (sizeof(FPReg));
		cpu -> floatingPointRegisters [i] -> data = 0.0;
		cpu -> floatingPointRegisters [i] -> fpResult = 0;
 	}*/

	cpu -> intDestReg = 0;
	cpu -> intResult = 0;

	cpu -> fpDestReg = 0;
	cpu -> fpResult = 0;
}

Thread *chooseThread(int is_primary){
    if(threads[1].is_available){
        if(cpu->cycle%2==0){
            if(is_primary)
                return &(threads[0]);
            else
                return &(threads[1]);
        } else {
            if(is_primary)
                return &(threads[1]);
            else
                return &(threads[0]);
        }
    } else {
        if(is_primary)
            return &(threads[0]);
        else
            return NULL;
    }

}

void printState(){
    printf("------------------------- CPU ----------------------------\n\n");
    printRSStation();
    printf("----------------------- THREAD 0 -------------------------\n\n");
    printIntegerRegisters (&(threads[0]));
    printFPRegisters (&(threads[0]));
	printROB(&(threads[0]));
	printRegisterState(&(threads[0]));
	printDataCache(&(threads[0]));
	if(threads[1].is_available){
        printf("----------------------- THREAD 1 -------------------------\n\n");
        printIntegerRegisters (&(threads[1]));
        printFPRegisters (&(threads[1]));
        printROB(&(threads[1]));
        printRegisterState(&(threads[1]));
        printDataCache(&(threads[1]));
	}
}

/**
 * Method that simulates the looping cycle-wise
 * @return: When the simulator stops
 */
int runClockCycle () {
	cpu -> cycle++; //increment cycle counter

	printf ("\nCYCLE %d\n", cpu -> cycle);


    int result = 0;
	result += commit();
    result += runClockCycle_EX();
	result += Issue();
	result += decode();
	result += runClockCycle_IF();

	//printState(); print entire state every clock
    return result;
}

/**
 * Helper method for BHT hash table to calculate hash value from PC
 * @param PCHash
 * @return
 */
int getHashCodeFromPCHash (void *PCHash) {
	return *((int*)PCHash);
}
