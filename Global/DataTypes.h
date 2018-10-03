/*
 * DataTypes.h
 *
 *  Created on: Sep 29, 2015
 *      Author: DebashisGanguly
 */

#ifndef GLOBAL_DATATYPES_H_
#define GLOBAL_DATATYPES_H_

#include "./ADT/CircularQueue.h"
#include "./ADT/Dictionary.h"

typedef enum _opCode {
	AND,
	ANDI,
	OR,
	ORI,
	SLT,
	SLTI,
	DADD,
	DADDI,
	DSUB,
	DMUL,
	LD,
	SD,
	L_D,
	S_D,
	ADD_D,
	SUB_D,
	MUL_D,
	DIV_D,
	BEQZ,
	BNEZ,
	BEQ,
	BNE,
	NOOP
} OpCode;

static inline char *getOpcodeString (int opcode) {
	char *opcodeString[23] = {"AND", "ANDI", "OR", "ORI", "SLT", "SLTI", "DADD", "DADDI", "DSUB", "DMUL", "LD", "SD", "L_D", "S_D", "ADD_D", "SUB_D", "MUL_D", "DIV_D", "BEQZ", "BNEZ", "BEQ", "BNE", "NOOP"};

	return opcodeString[opcode];
}

//data structure for decoded instruction
typedef struct _instruction {
	OpCode op;
	int address;

	int rd;
	int rs;
	int rt;

	int rsValue;
	int rtValue;

	int fd;
	int fs;
	int ft;

	double fsValue;
	double ftValue;

	int immediate;

	int target;

	int is_valid;

} Instruction;

//data structure for each item in integer registers and work as well register status
typedef struct _INTReg {
	int data;
	int intResult;
} INTReg;

//data structure for each item in floating point registers and work as well register status
typedef struct _FPReg {
	double data;
        double fpResult;
} FPReg;


//main data structure representing CPU
typedef struct _cpu {
	int cycle; //counter for number of cycles

	int numberOfInstructionExecuted; //counter for total number of instructions committed

	int PC; //program counter

	INTReg **integerRegisters; //integer register
        FPReg **floatingPointRegisters; //FP registers

	int memoryAddress;

	int intDestReg;
        int intResult;

        int fpDestReg;
        double fpResult;

} CPU;

typedef struct _config {
    int NF; // fetched instructions
    int NI; // instruction queue length
    int NW; // issued instructions
    int NR; // reorder buffer size
    int NB; // number of cdb buses
} Config;

typedef struct _BTB_value{
    int target_address;
    int taken;
} BTB_value;

typedef struct _IFUnit {
//	IF_Instr_entry instructions[32];
	int n_instructions;
	//char instructions[32][MAX_LINE];
	//BTB_entry* instr_btb[32];
} IF_Unit;

typedef struct _IDUnit {
	Instruction** instructionQueue;
	Instruction** instructions;
	int n_instructions;
} ID_Unit;

typedef struct _EXUnit {

} EX_Unit;

typedef struct _MEMUnit {

} MEM_Unit;

typedef struct _WBUnit {

} WB_Unit;

typedef struct INT_Unit {

} INT;

typedef struct MULT_Unit {

} MULT;

typedef struct LOAD_STORE {

} LS;

typedef struct FPADD_Unit {

} FPADD;

typedef struct FPMULT_Unit {

} FPMULT;

typedef struct FPDIV_Unit {

} FPDIV;

typedef struct BU_UNIT {

} BU;

#endif /* GLOBAL_DATATYPES_H_ */
