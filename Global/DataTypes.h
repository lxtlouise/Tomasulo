/*
 * DataTypes.h
 *
 *  Created on: Sep 29, 2015
 *      Author: DebashisGanguly
 */

#ifndef GLOBAL_DATATYPES_H_
#define GLOBAL_DATATYPES_H_
#define MAX_LINE 4096
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

typedef struct _BTB_value{
    int PC;
    int target_address;
    int taken;
} BTB_value;

//data structure for decoded instruction
typedef struct _instruction {
    char instr[MAX_LINE];
    int PC;
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

    int branch_predicted;
    int prediction_target;
    int prediction_taken;
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



typedef struct _IF_Instr_entry{
    char instr[MAX_LINE];
} IF_Instr_entry;

typedef struct _IFUnit {
    int PC;
	Instruction* instructions[32];
	int n_instructions;
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

typedef struct _RS_Station {
	int busy; //initialize as 0
	OpCode op;
	int vj; //initialize as -1
	int vk; //initialize as -1
	int qj; //initialize as -1
	int qk; //initialize as -1
	int destination; //ROB index
	int a_immediate;
	int a_register;
	int target;
} RS_Station;

typedef enum ROB_state {
	COMMIT,
	WROTE_RESULT,
	ISSUED_EXECUTING
} ROB_state;

typedef struct _ROB_entry {
	int index;
	Instruction *instruction;
	int valid; // 0 on creation
	int int_renaming_register; // if fp instr, then -1
	int fp_renaming_register; // if int instr, then -1
	ROB_state rob_state;
} ROB_entry;

typedef struct _Register_Status {
	int *int_reg;
	int *fp_reg;
} Register_Status;

typedef struct _Renaming_Status {
	int *int_rreg;
	int *fp_rreg;
} Renaming_Status;

#endif /* GLOBAL_DATATYPES_H_ */
