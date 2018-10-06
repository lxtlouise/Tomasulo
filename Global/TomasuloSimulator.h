/*
 * TomasuloSimulator.h
 *
 *  Created on: Oct 1, 2015
 *      Author: DebashisGanguly
 */

#ifndef GLOBAL_TOMASULOSIMULATOR_H_
#define GLOBAL_TOMASULOSIMULATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "./DataTypes.h"
#include "./ADT/CircularQueue.h"
#include "./ADT/Dictionary.h"

//macros for parsing and tokenizing
#define DATA_LABEL "DATA"
#define WHITE_SPACE " \t\n"
#define LINE_TERMINATOR "\n"
#define LABEL_TERMINATOR ":"
#define LABEL_TERMINATOR_CHAR ':'
#define MEMORY_LABEL "Mem"
#define MEMORY_SEPARATOR " )(=\n"
#define RESERV_INT_SIZE    4
#define RESERV_MULT_SIZE    2
#define RESERV_LOAD_BUFFER_SIZE    2
#define RESERV_STORE_BUFFER_SIZE    2
#define RESERV_FPADD_SIZE    3
#define RESERV_FPMULT_SIZE 4
#define RESERV_FPDIV_SIZE 2
#define RESERV_BU_SIZE 2
#define REGISTER_NOT_BOUND_WITH_ROB -1
#define RENAMING_INT_REGISTER_NUM 8
#define RENAMING_FP_REGISTER_NUM 8

#define MAX_LINE  4096

//global variables populated from configuration
int numberOfIntRegisters; //NIR
int numberOfFPRegisters; //NFPR

int instructionCacheBaseAddress; //ICBA

int cacheLineSize; //CLS

int numberOfInstruction;

Dictionary *instructionCache;
Dictionary *dataCache;
Dictionary *codeLabels;
Dictionary *BTB;
CircularQueue *instructionQueue;
CircularQueue *ROB;


CPU *cpu;
Config *config;
IF_Unit *if_unit;
ID_Unit *id_unit;
EX_Unit *ex_unit;
WB_Unit *wb_unit;

RS_Station **rs_int;
RS_Station **rs_mutl;
RS_Station **rs_load;
RS_Station **rs_save;
RS_Station **rs_fpadd;
RS_Station **rs_fpmutl;
RS_Station **rs_fpdiv;
RS_Station **rs_bu;

Register_Status *register_status;
INTReg **renaming_int_registers;
FPReg **renaming_fp_registers;
Renaming_Status *renaming_status;


int runClockCycle_IF();


void fillInstructionAndDataCache (char *fileName);

void setBTBEntry(Instruction* instruction, int branch_taken, int branch_target);

void initializeCPU ();
void initializeIF_Unit();

int runClockCycle ();
void initializeInstruction(Instruction *instruction);
void copyInstruction(Instruction *dest, Instruction *src);
void decode();
void Issue();


void printInstructionCache ();
void printCodeLabels ();
void printDataCache ();
void printIntegerRegisters ();
void printFPRegisters ();

void read_configfile(char * fileName);

#endif /* GLOBAL_TOMASULOSIMULATOR_H_ */
