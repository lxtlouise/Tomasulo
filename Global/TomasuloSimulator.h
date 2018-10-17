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
#define ENV_CONFIG_FILE "../Config/TomasuloSimulator.conf"

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
#define CONFIG_EQUAL "="

#define RESERV_ALL_NUM (RESERV_INT_SIZE + RESERV_MULT_SIZE + RESERV_LOAD_BUFFER_SIZE + RESERV_STORE_BUFFER_SIZE + RESERV_FPADD_SIZE + RESERV_FPMULT_SIZE + RESERV_FPDIV_SIZE + RESERV_BU_SIZE)
#define PIPELINE_STAGES_INT 1
#define PIPELINE_STAGES_MULT 4
#define PIPELINE_STAGES_MEM 1
#define PIPELINE_STAGES_FPadd 3
#define PIPELINE_STAGES_FPmult 4
#define PIPELINE_STAGES_FPdiv 1
#define PIPELINE_STAGES_BU 1

#define MAX_LINE  4096

//global variables populated from configuration
int numberOfIntRegisters; //NIR
int numberOfFPRegisters; //NFPR

int instructionCacheBaseAddress; //ICBA

int cacheLineSize; //CLS

//int numberOfInstruction;

int CDB_counter;

//Dictionary *instructionCache;
//Dictionary *dataCache;
//Dictionary *codeLabels;
//Dictionary *BTB;
//CircularQueue *ROB;

Thread threads[2];

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

//Register_Status *register_status;
//INTReg **renaming_int_registers;
//FPReg **renaming_fp_registers;
//Renaming_Status *renaming_status;
void InitializeThread(int index, Thread* thread, char *fileName);

int fillInstructionAndDataCache (char *fileName, Dictionary **instructionCache, Dictionary **dataCache, Dictionary **codeLabels);

void setBTBEntry(Instruction* instruction, int branch_taken, int branch_target);

void initializeCPU ();
void initializeFetch();
void initializeDecode();
void initializeIssue();
void initializeExecute();

int runClockCycle ();
int runClockCycle_IF();
void initializeInstruction(Instruction *instruction);
void copyInstruction(Instruction *dest, Instruction *src);
int decode();
int Issue();
int runClockCycle_EX();
int commit();

void printState();
void printInstructionCache (Thread *thread);
//void printCodeLabels ();
//void printDataCache ();
//void printIntegerRegisters ();
//void printFPRegisters ();
//void printRSStation();
//void printROB();
//void printRegisterState();

void read_configfile(char * fileName);
Thread *chooseThread(int is_primary);

#endif /* GLOBAL_TOMASULOSIMULATOR_H_ */
