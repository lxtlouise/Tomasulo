/*
 * PrintUtility.c
 *
 *  Created on: Oct 2, 2015
 *      Author: DebashisGanguly
 */

#include "../TomasuloSimulator.h"

/**
 * Utility method to print instruction cache
 */
void printInstructionCache () {
	DictionaryEntry *current;

	if (cpu->instructionCache != NULL) {
		printf ("-----------------\n");
		printf ("Instruction Cache\n");
		printf ("-----------------\n");

		for (current = cpu->instructionCache -> head; current != NULL; current = current -> next)
			printf ("%d: %s\n", *((int*)current -> key), ((char*)current -> value -> value));
	}
}

/***
 * Utility method to print code lables
 */
void printCodeLabels (Thread *thread) {
	DictionaryEntry *current;

	if (thread->codeLabels != NULL) {
		printf ("-----------\n");
		printf ("Code Lables\n");
		printf ("-----------\n");

		for (current = thread->codeLabels -> head; current != NULL; current = current -> next)
		 	printf ("%s: %d\n", ((char*)current -> key), *((int*)current -> value -> value));
	}
}

/***
 * Utility method to print data cache
 */
void printDataCache () {
	DictionaryEntry *current;

	if (cpu->dataCache != NULL) {
		printf ("----------\n");
		printf ("Data Cache\n");
		printf ("----------\n");

		for (current = cpu->dataCache -> head; current != NULL; current = current -> next)
			printf ("Mem(%d) = %0.1lf\n", *((int*)current -> key), *((double*)current -> value -> value));
	}
}
/**
 * Utility method to print integer registers
 */
void printIntegerRegisters (Thread *thread) {
	int i;

	printf ("-----------------\n");
	printf ("Integer Registers\n");
	printf ("-----------------\n");

	for (i = 0; i < numberOfIntRegisters; i++) {
		printf ("Int_Reg[%d]=%d\n", i, thread -> integerRegisters [i] -> data);
	}
}

/***
 * Utility method to print floating point registers
 */
void printFPRegisters (Thread *thread) {
	int i;

	printf ("------------------------\n");
	printf ("Floating Point Registers\n");
	printf ("------------------------\n");

	for (i = 0; i < numberOfFPRegisters; i++) {
		printf ("FP_Reg[%d]=%0.1lf\n", i, thread -> floatingPointRegisters [i] -> data);
	}
}

void printRSStation() {
	printf ("------------------------\n");
	printf ("Reservation Stations\n");
	printf ("------------------------\n");

	int i;
	for (i = 0; i < RESERV_INT_SIZE; i++) {
		printf("Int rs station %d,	busy: %d, op: %s, vj: %d, vk: %d, qj: %d, qk: %d, destination: %d, a_immediate: %d, a_register: %d, target: %d\n",
			i, rs_int[i] -> busy, getOpcodeString ((int) rs_int[i] -> op), rs_int[i] -> vj, rs_int[i] -> vk, rs_int[i] -> qj, rs_int[i] -> qk, rs_int[i] -> destination,
			rs_int[i] -> a_immediate, rs_int[i] -> a_register, rs_int[i] -> target);
	}
	for (i = 0; i < RESERV_MULT_SIZE; i++) {
		printf("Mutl rs station %d,	busy: %d, op: %s, vj: %d, vk: %d, qj: %d, qk: %d, destination: %d, a_immediate: %d, a_register: %d, target: %d\n",
			i, rs_mutl[i] -> busy, getOpcodeString ((int) rs_mutl[i] -> op), rs_mutl[i] -> vj, rs_mutl[i] -> vk, rs_mutl[i] -> qj, rs_mutl[i] -> qk, rs_mutl[i] -> destination,
			rs_mutl[i] -> a_immediate, rs_mutl[i] -> a_register, rs_mutl[i] -> target);
	}
	for (i = 0; i < RESERV_LOAD_BUFFER_SIZE; i++) {
		printf("Load buffer %d,		busy: %d, op: %s, vj: %d, vk: %d, qj: %d, qk: %d, destination: %d, a_immediate: %d, a_register: %d, target: %d\n",
			i, rs_load[i] -> busy, getOpcodeString ((int) rs_load[i] -> op), rs_load[i] -> vj, rs_load[i] -> vk, rs_load[i] -> qj, rs_load[i] -> qk, rs_load[i] -> destination,
			rs_load[i] -> a_immediate, rs_load[i] -> a_register, rs_load[i] -> target);
	}
	for (i = 0; i < RESERV_STORE_BUFFER_SIZE; i++) {
		printf("Store buffer %d,		busy: %d, op: %s, vj: %d, vk: %d, qj: %d, qk: %d, destination: %d, a_immediate: %d, a_register: %d, target: %d\n",
			i, rs_save[i] -> busy, getOpcodeString ((int) rs_save[i] -> op), rs_save[i] -> vj, rs_save[i] -> vk, rs_save[i] -> qj, rs_save[i] -> qk, rs_save[i] -> destination,
			rs_save[i] -> a_immediate, rs_save[i] -> a_register, rs_save[i] -> target);
	}
	for (i = 0; i < RESERV_FPADD_SIZE; i++) {
		printf("FpAdd rs station %d,	busy: %d, op: %s, vj: %d, vk: %d, qj: %d, qk: %d, destination: %d, a_immediate: %d, a_register: %d, target: %d\n",
			i, rs_fpadd[i] -> busy, getOpcodeString ((int) rs_fpadd[i] -> op), rs_fpadd[i] -> vj, rs_fpadd[i] -> vk, rs_fpadd[i] -> qj, rs_fpadd[i] -> qk, rs_fpadd[i] -> destination,
			rs_fpadd[i] -> a_immediate, rs_fpadd[i] -> a_register, rs_fpadd[i] -> target);
	}
	for (i = 0; i < RESERV_FPMULT_SIZE; i++) {
		printf("FpMutl rs station %d,	busy: %d, op: %s, vj: %d, vk: %d, qj: %d, qk: %d, destination: %d, a_immediate: %d, a_register: %d, target: %d\n",
			i, rs_fpmutl[i] -> busy, getOpcodeString ((int) rs_fpmutl[i] -> op), rs_fpmutl[i] -> vj, rs_fpmutl[i] -> vk, rs_fpmutl[i] -> qj, rs_fpmutl[i] -> qk, rs_fpmutl[i] -> destination,
			rs_fpmutl[i] -> a_immediate, rs_fpmutl[i] -> a_register, rs_fpmutl[i] -> target);
	}
	for (i = 0; i < RESERV_FPDIV_SIZE; i++) {
		printf("FpDiv rs station %d, 	busy: %d, op: %s, vj: %d, vk: %d, qj: %d, qk: %d, destination: %d, a_immediate: %d, a_register: %d, target: %d\n",
			i, rs_fpdiv[i] -> busy, getOpcodeString ((int) rs_fpdiv[i] -> op), rs_fpdiv[i] -> vj, rs_fpdiv[i] -> vk, rs_fpdiv[i] -> qj, rs_fpdiv[i] -> qk, rs_fpdiv[i] -> destination,
			rs_fpdiv[i] -> a_immediate, rs_fpdiv[i] -> a_register, rs_fpdiv[i] -> target);
	}
	for (i = 0; i < RESERV_BU_SIZE; i++) {
		printf("Bu rs station %d,	busy: %d, op: %s, vj: %d, vk: %d, qj: %d, qk: %d, destination: %d, a_immediate: %d, a_register: %d, target: %d\n",
			i, rs_bu[i] -> busy, getOpcodeString ((int) rs_bu[i] -> op), rs_bu[i] -> vj, rs_bu[i] -> vk, rs_bu[i] -> qj, rs_bu[i] -> qk, rs_bu[i] -> destination,
			rs_bu[i] -> a_immediate, rs_bu[i] -> a_register, rs_bu[i] -> target);
	}
}

void printROB(Thread *thread) {
	int i;
	printf ("------------------------\n");
	printf ("Reorder Buffer\n");
	printf ("------------------------\n");
	for (i = 0; i < thread->ROB -> count; i++) {
		ROB_entry* entry = (ROB_entry*) (thread->ROB -> items[i]);
		printf("ROB index: %d op: %s  valid: %d int_renaming_register: %d fp_renaming_register: %d state: %s\n",
				entry -> index, getOpcodeString ((int) entry -> instruction -> op), entry -> valid, entry -> int_renaming_register, entry -> fp_renaming_register, getROBState((int)entry -> rob_state));
	}
}

void printRegisterState(Thread *thread){
	int i;
	printf ("------------------------\n");
	printf ("Regular Registers State\n");
	printf ("------------------------\n");
	for (i = 0; i < numberOfIntRegisters; i++) {
		printf("Int register index: %d ROB index: %d\n", i, thread->register_status -> int_reg[i]);
	}
	for (i = 0; i < numberOfFPRegisters; i++) {
		printf("Fp register index: %d ROB index: %d\n", i, thread->register_status -> fp_reg[i]);
	}
}
