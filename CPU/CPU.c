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

	int _continue = runClockCycle_IF();
	if (!_continue) return 0;
	decode();
	Issue();
    runClockCycle_EX();
	/******* original execute stage
	void *valuePtr = malloc(sizeof(double));

	DictionaryEntry *dataCacheElement;

	switch (instruction -> op) {
			case ANDI:
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data & instruction -> immediate;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
				break;
			case AND:
                                cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data & cpu -> integerRegisters [instruction -> rt] -> data;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
			case ORI:
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data | instruction -> immediate;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
				break;
                        case OR:
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data | cpu -> integerRegisters [instruction -> rt] -> data;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
			case SLTI:
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data < instruction -> immediate ? 1 : 0;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
				break;
                        case SLT:
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data < cpu -> integerRegisters [instruction -> rt] -> data ? 1 : 0;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
			case DADDI:
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data + instruction -> immediate;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
				break;
                        case DADD:
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data + cpu -> integerRegisters [instruction -> rt] -> data;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
                        case DSUB:
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data - cpu -> integerRegisters [instruction -> rt] -> data;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
			case DMUL:
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data * cpu -> integerRegisters [instruction -> rt] -> data;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
                        case ADD_D:
                                cpu -> fpResult = cpu -> floatingPointRegisters [instruction -> fs] -> data + cpu -> floatingPointRegisters [instruction -> ft] -> data;
				cpu -> floatingPointRegisters [instruction -> fd] -> data = cpu -> fpResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
                        case SUB_D:
				cpu -> fpResult = cpu -> floatingPointRegisters [instruction -> fs] -> data - cpu -> floatingPointRegisters [instruction -> ft] -> data;
				cpu -> floatingPointRegisters [instruction -> fd] -> data = cpu -> fpResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
                        case MUL_D:
				cpu -> fpResult = cpu -> floatingPointRegisters [instruction -> fs] -> data * cpu -> floatingPointRegisters [instruction -> ft] -> data;
				cpu -> floatingPointRegisters [instruction -> fd] -> data = cpu -> fpResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
                        case DIV_D:
				cpu -> fpResult = cpu -> floatingPointRegisters [instruction -> fs] -> data / cpu -> floatingPointRegisters [instruction -> ft] -> data;
				cpu -> floatingPointRegisters [instruction -> fd] -> data = cpu -> fpResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
                        case L_D:
				cpu -> memoryAddress = cpu -> integerRegisters [instruction -> rs] -> data + instruction -> immediate;

				*((int*)addrPtr) = cpu -> memoryAddress;
				dataCacheElement = getValueChainByDictionaryKey (dataCache, addrPtr);

				valuePtr = dataCacheElement -> value -> value;
				cpu -> fpResult = *((double*)valuePtr);

				cpu -> floatingPointRegisters [instruction -> ft] -> data = cpu -> fpResult;
				cpu -> PC = cpu -> PC + 4;
				break;
			case LD:
				cpu -> memoryAddress = cpu -> integerRegisters [instruction -> rs] -> data + instruction -> immediate;

				*((int*)addrPtr) = cpu -> memoryAddress;
				dataCacheElement = getValueChainByDictionaryKey (dataCache, addrPtr);

				valuePtr = dataCacheElement -> value -> value;
				cpu -> intResult =  (int) *((double*)valuePtr);

				cpu -> integerRegisters [instruction -> rt] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
                        case SD:
                                cpu -> memoryAddress = cpu -> integerRegisters [instruction -> rs] -> data + instruction -> immediate;
                                cpu -> intResult = cpu -> integerRegisters [instruction -> rt] -> data ;

				*((int*)addrPtr) = cpu -> memoryAddress;
				removeDictionaryEntriesByKey (dataCache, addrPtr);

				*((double*)valuePtr) = cpu -> intResult;
				addDictionaryEntry (dataCache, addrPtr, valuePtr);
				cpu -> PC = cpu -> PC + 4;
                                break;
                        case S_D:
                                cpu -> memoryAddress = cpu -> integerRegisters [instruction -> rs] -> data  + instruction -> immediate;
                                cpu -> fpResult = cpu -> floatingPointRegisters [instruction -> ft] -> data ;

				*((int*)addrPtr) = cpu -> memoryAddress;
                                removeDictionaryEntriesByKey (dataCache, addrPtr);

                                *((double*)valuePtr) = (double) cpu -> fpResult;
                                addDictionaryEntry (dataCache, addrPtr, valuePtr);
				cpu -> PC = cpu -> PC + 4;
                                break;
			case BNE:
                                cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data != cpu -> integerRegisters [instruction -> rt] -> data ? 0 : -1;
				if (cpu -> intResult == 0) {
					cpu -> PC = instruction -> target;
				} else {
					cpu -> PC = cpu -> PC + 4;
				}
                                break;
                        case BNEZ:
                                cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data != 0 ? 0 : -1;
				if (cpu -> intResult == 0) {
                                        cpu -> PC = instruction -> target;
                                } else {
					cpu -> PC = cpu -> PC + 4;
				}
                                break;
                        case BEQ:
                                cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data == cpu -> integerRegisters [instruction -> rt] -> data ? 0 : -1;
				if (cpu -> intResult == 0) {
                                        cpu -> PC = instruction -> target;
                                } else {
					cpu -> PC = cpu -> PC + 4;
				}
                                break;
                        case BEQZ:
                                cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data == 0 ? 0 : -1;
				if (cpu -> intResult == 0) {
                                        cpu -> PC = instruction -> target;
                                } else {
					cpu -> PC = cpu -> PC + 4;
				}
                                break;
                        default:
                                break;
                }

	**********/
	return 0;
}

/**
 * Helper method for BHT hash table to calculate hash value from PC
 * @param PCHash
 * @return
 */
int getHashCodeFromPCHash (void *PCHash) {
	return *((int*)PCHash);
}
