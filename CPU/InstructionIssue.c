# include "../Global/TomasuloSimulator.h"


void initializeIssue() {
	int i;
	ROB = createCircularQueue(config -> NR);


	// initialize reservation stations
	rs_int = (RS_Station **) malloc(sizeof(RS_Station *) * RESERV_INT_SIZE);
	for (i = 0; i < RESERV_INT_SIZE; i++) {
		rs_int[i] = (RS_Station *) malloc(sizeof(RS_Station));
		rs_int[i] -> busy = 0;
		rs_int[i] -> op = NOOP;
		rs_int[i] -> vj = -1;
		rs_int[i] -> vk = -1;
		rs_int[i] -> qj = -1;
		rs_int[i] -> qk = -1;
		rs_int[i] -> destination = -1;
		rs_int[i] -> a_immediate = -2147483648;
		rs_int[i] -> a_register = -1;
		rs_int[i] -> target = -1;
	}
	rs_mutl = (RS_Station **) malloc(sizeof(RS_Station *) * RESERV_MULT_SIZE);
	for (i = 0; i < RESERV_MULT_SIZE; i++) {
		rs_mutl[i] = (RS_Station *) malloc(sizeof(RS_Station));
		rs_mutl[i] -> busy = 0;
		rs_mutl[i] -> op = NOOP;
		rs_mutl[i] -> vj = -1;
		rs_mutl[i] -> vk = -1;
		rs_mutl[i] -> qj = -1;
		rs_mutl[i] -> qk = -1;
		rs_mutl[i] -> destination = -1;
		rs_mutl[i] -> a_immediate = -2147483648;
		rs_mutl[i] -> a_register = -1;
		rs_mutl[i] -> target = -1;
	}
	rs_load = (RS_Station **) malloc(sizeof(RS_Station *) * RESERV_LOAD_BUFFER_SIZE);
	for (i = 0; i < RESERV_LOAD_BUFFER_SIZE; i++) {
		rs_load[i] = (RS_Station *) malloc(sizeof(RS_Station));
		rs_load[i] -> busy = 0;
		rs_load[i] -> op = NOOP;
		rs_load[i] -> vj = -1;
		rs_load[i] -> vk = -1;
		rs_load[i] -> qj = -1;
		rs_load[i] -> qk = -1;
		rs_load[i] -> destination = -1;
		rs_load[i] -> a_immediate = -2147483648;
		rs_load[i] -> a_register = -1;
		rs_load[i] -> target = -1;
	}
	rs_save = (RS_Station **) malloc(sizeof(RS_Station *) * RESERV_STORE_BUFFER_SIZE);
	for (i = 0; i < RESERV_STORE_BUFFER_SIZE; i++) {
		rs_save[i] = (RS_Station *) malloc(sizeof(RS_Station));
		rs_save[i] -> busy = 0;
		rs_save[i] -> op = NOOP;
		rs_save[i] -> vj = -1;
		rs_save[i] -> vk = -1;
		rs_save[i] -> qj = -1;
		rs_save[i] -> qk = -1;
		rs_save[i] -> destination = -1;
		rs_save[i] -> a_immediate = -2147483648;
		rs_save[i] -> a_register = -1;
		rs_save[i] -> target = -1;
	}
	rs_fpadd = (RS_Station **) malloc(sizeof(RS_Station *) * RESERV_FPADD_SIZE);
	for (i = 0; i < RESERV_FPADD_SIZE; i++) {
		rs_fpadd[i] = (RS_Station *) malloc(sizeof(RS_Station));
		rs_fpadd[i] -> busy = 0;
		rs_fpadd[i] -> op = NOOP;
		rs_fpadd[i] -> vj = -1;
		rs_fpadd[i] -> vk = -1;
		rs_fpadd[i] -> qj = -1;
		rs_fpadd[i] -> qk = -1;
		rs_fpadd[i] -> destination = -1;
		rs_fpadd[i] -> a_immediate = -2147483648;
		rs_fpadd[i] -> a_register = -1;
		rs_fpadd[i] -> target = -1;
	}
	rs_fpmutl = (RS_Station **) malloc(sizeof(RS_Station *) * RESERV_FPMULT_SIZE);
	for (i = 0; i < RESERV_FPMULT_SIZE; i++) {
		rs_fpmutl[i] = (RS_Station *) malloc(sizeof(RS_Station));
		rs_fpmutl[i] -> busy = 0;
		rs_fpmutl[i] -> op = NOOP;
		rs_fpmutl[i] -> vj = -1;
		rs_fpmutl[i] -> vk = -1;
		rs_fpmutl[i] -> qj = -1;
		rs_fpmutl[i] -> qk = -1;
		rs_fpmutl[i] -> destination = -1;
		rs_fpmutl[i] -> a_immediate = -2147483648;
		rs_fpmutl[i] -> a_register = -1;
		rs_fpmutl[i] -> target = -1;
	}
	rs_fpdiv = (RS_Station **) malloc(sizeof(RS_Station *) * RESERV_FPDIV_SIZE);
	for (i = 0; i < RESERV_FPDIV_SIZE; i++) {
		rs_fpdiv[i] = (RS_Station *) malloc(sizeof(RS_Station));
		rs_fpdiv[i] -> busy = 0;
		rs_fpdiv[i] -> op = NOOP;
		rs_fpdiv[i] -> vj = -1;
		rs_fpdiv[i] -> vk = -1;
		rs_fpdiv[i] -> qj = -1;
		rs_fpdiv[i] -> qk = -1;
		rs_fpdiv[i] -> destination = -1;
		rs_fpdiv[i] -> a_immediate = -2147483648;
		rs_fpdiv[i] -> a_register = -1;
		rs_fpdiv[i] -> target = -1;
	}
	rs_bu = (RS_Station **) malloc(sizeof(RS_Station *) * RESERV_BU_SIZE);
	for (i = 0; i < RESERV_BU_SIZE; i++) {
		rs_bu[i] = (RS_Station *) malloc(sizeof(RS_Station));
		rs_bu[i] -> busy = 0;
		rs_bu[i] -> op = NOOP;
		rs_bu[i] -> vj = -1;
		rs_bu[i] -> vk = -1;
		rs_bu[i] -> qj = -1;
		rs_bu[i] -> qk = -1;
		rs_bu[i] -> destination = -1;
		rs_bu[i] -> a_immediate = -2147483648;
		rs_bu[i] -> a_register = -1;
		rs_bu[i] -> target = -1;
	}

	// initialize renaming_status
	renaming_status = (Renaming_Status*) malloc(sizeof(Renaming_Status));
	renaming_status -> int_rreg = (int*) malloc(sizeof(int) * RENAMING_INT_REGISTER_NUM);
	for (i = 0; i < RENAMING_INT_REGISTER_NUM; i++) {
		renaming_status -> int_rreg[i] = 0;
	}
	renaming_status -> fp_rreg = (int*) malloc(sizeof(int) * RENAMING_FP_REGISTER_NUM);
	for (i = 0; i < RENAMING_FP_REGISTER_NUM; i++) {
		renaming_status -> fp_rreg[i] = 0;
	}

	// initialize register_status
	register_status = (Register_Status*) malloc(sizeof(Register_Status));
	register_status -> int_reg = (int*) malloc(sizeof(int) * numberOfIntRegisters);
	for (i = 0; i < numberOfIntRegisters; i++) {
		register_status -> int_reg[i] = REGISTER_NOT_BOUND_WITH_ROB;
	}
	register_status -> fp_reg = (int*) malloc(sizeof(int) * numberOfFPRegisters);
	for (i = 0; i < numberOfFPRegisters; i++) {
		register_status -> fp_reg[i] = REGISTER_NOT_BOUND_WITH_ROB;
	}

	// renaming registers
	renaming_int_registers = (INTReg**) malloc(sizeof (INTReg*) * RENAMING_INT_REGISTER_NUM);
	for (i = 0; i < RENAMING_INT_REGISTER_NUM; i++) {
		renaming_int_registers[i] = (INTReg *) malloc (sizeof(INTReg));
		renaming_int_registers[i] -> data = 0;
		renaming_int_registers[i] -> intResult = 0;
 	}
	renaming_fp_registers = (FPReg**) malloc(sizeof (FPReg*) * RENAMING_FP_REGISTER_NUM);
	for (i = 0; i < RENAMING_FP_REGISTER_NUM; i++) {
		renaming_fp_registers[i] = (FPReg *) malloc (sizeof(FPReg));
		renaming_fp_registers[i] -> data = 0;
		renaming_fp_registers[i] -> fpResult = 0;
 	}
}

//check whether reservation station is available
int checkRSAvailability(Instruction *instruction) {
	OpCode opcode = instruction -> op;
	int i;

	if(opcode == AND || opcode == ANDI || opcode == OR || opcode == ORI
		|| opcode == SLT || opcode == SLTI || opcode == DADD || opcode == DADDI
		|| opcode == DSUB) {
		for (i = 0; i < RESERV_INT_SIZE; i++) {
			if(!rs_int[i] -> busy) {
				return i;
			}
		}
	} else if(opcode == DMUL) {
		for (i = 0; i < RESERV_MULT_SIZE; i++) {
			if(!rs_mutl[i] -> busy) {
				return i;
			}
		}
	} else if(opcode == LD || opcode == L_D) {
		for (i = 0; i < RESERV_LOAD_BUFFER_SIZE; i++) {
			if(!rs_load[i] -> busy) {
				return i;
			}
		}
	} else if(opcode == SD || opcode == S_D) {
		for (i = 0; i < RESERV_STORE_BUFFER_SIZE; i++) {
			if(!rs_save[i] -> busy) {
				return i;
			}
		}
	} else if(opcode == ADD_D || opcode == SUB_D) {
		for (i = 0; i < RESERV_FPADD_SIZE; i++) {
			if(!rs_fpadd[i] -> busy) {
				return i;
			}
		}
	} else if(opcode == MUL_D) {
		for (i = 0; i < RESERV_FPMULT_SIZE; i++) {
			if(!rs_mutl[i] -> busy) {
				return i;
			}
		}
	} else if(opcode == DIV_D) {
		for (i = 0; i < RESERV_FPDIV_SIZE; i++) {
			if(!rs_fpdiv[i] -> busy) {
				return i;
			}
		}
	} else if(opcode == BEQZ || opcode == BNEZ || opcode == BEQ || opcode == BNE) {
		for (i = 0; i < RESERV_BU_SIZE; i++) {
			if(!rs_bu[i] -> busy) {
				return i;
			}
		}
	}
	return -1;
}

//check register status
int checkRegStates(int if_fp, int register_index) {
	if(if_fp) {
		return register_status -> fp_reg[register_index];
	} else {
		return register_status -> int_reg[register_index];
	}
}

int checkROB() {
	if (ROB -> count == config -> NR) {
		return -1;
	} else {
		return ROB -> tail;
	}
}

//check whether renaming registers are available or not
//check if rd is -1 or if fd is -1
int checkRenameRegister(Instruction *instruction) {
	OpCode opcode = instruction -> op;
	int i;
	if (opcode == AND || opcode == ANDI || opcode == OR || opcode == ORI
		|| opcode == SLT || opcode == SLTI || opcode == DADD || opcode == DADDI
		|| opcode == DSUB || opcode == DMUL || opcode == LD || opcode == SD) {
		for(i = 0; i < RENAMING_INT_REGISTER_NUM; i++) {
			if(renaming_status -> int_rreg[i] == 0) {
				renaming_status -> int_rreg[i] = 1;
				return i;
			}
		}
	} else if (opcode == L_D || opcode == S_D || opcode == ADD_D || opcode == SUB_D
		|| opcode == MUL_D || opcode == DIV_D){
		for(i = 0; i < RENAMING_FP_REGISTER_NUM; i++) {
			if(renaming_status -> fp_rreg[i] == 0) {
				renaming_status -> fp_rreg[i] = 1;
				return i + RENAMING_INT_REGISTER_NUM;
			}
		}
	} else {
		return -2;
	}
	return -1;
}

void updateRegisterStates(int if_fp, int register_index, int rob_index) {
	if(if_fp) {
		register_status -> fp_reg[register_index] = rob_index;
	} else {
		register_status -> int_reg[register_index] = rob_index;
	}
}

void updateRS(Instruction *instruction, int rs_index, int rob_index) {
		OpCode opcode = instruction -> op;
		int if_fp = instruction -> fd != -1;
		RS_Station * rs_station;
		if(opcode == AND) {
			rs_station = rs_int[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(if_fp, instruction -> rs);
			int rename_rt = checkRegStates(if_fp, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = cpu->integerRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vk = cpu->integerRegisters[instruction -> rt]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(if_fp, instruction -> rd, rob_index); //update register states using the rob index of the result register
		} else if(opcode == ANDI) {
			rs_station = rs_int[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(if_fp, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = cpu->integerRegisters[instruction -> rs]->data;
			}
			rs_station -> vk = instruction -> immediate;

			rs_station -> destination = rob_index;
			updateRegisterStates(if_fp, instruction -> rd, rob_index);
		} else if(opcode == OR) {
			rs_station = rs_int[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(if_fp, instruction -> rs);
			int rename_rt = checkRegStates(if_fp, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = cpu->integerRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vk = cpu->integerRegisters[instruction -> rt]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(if_fp, instruction -> rd, rob_index);
		} else if(opcode == ORI) {
			rs_station = rs_int[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(if_fp, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = cpu->integerRegisters[instruction -> rs]->data;
			}
			rs_station -> vk = instruction -> immediate;

			rs_station -> destination = rob_index;
			updateRegisterStates(if_fp, instruction -> rd, rob_index);
		} else if(opcode == SLT) {
			rs_station = rs_int[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(if_fp, instruction -> rs);
			int rename_rt = checkRegStates(if_fp, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = cpu->integerRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vk = cpu->integerRegisters[instruction -> rt]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(if_fp, instruction -> rd, rob_index);
		} else if(opcode == SLTI) {
			rs_station = rs_int[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(if_fp, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = cpu->integerRegisters[instruction -> rs]->data;
			}
			rs_station -> vk = instruction -> immediate;

			rs_station -> destination = rob_index;
			updateRegisterStates(if_fp, instruction -> rd, rob_index);
		} else if(opcode == DADD) {
			rs_station = rs_int[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(if_fp, instruction -> rs);
			int rename_rt = checkRegStates(if_fp, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = cpu->integerRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vk = cpu->integerRegisters[instruction -> rt]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(if_fp, instruction -> rd, rob_index);
		} else if(opcode == DADDI) {
			rs_station = rs_int[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(if_fp, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = cpu->integerRegisters[instruction -> rs]->data;
			}
			rs_station -> vk = instruction -> immediate;

			rs_station -> destination = rob_index;
			updateRegisterStates(if_fp, instruction -> rd, rob_index);
		} else if(opcode == DSUB) {
			rs_station = rs_int[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(if_fp, instruction -> rs);
			int rename_rt = checkRegStates(if_fp, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = cpu->integerRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vk = cpu->integerRegisters[instruction -> rt]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(if_fp, instruction -> rd, rob_index);
		} else if(opcode == DMUL) {
			rs_station = rs_mutl[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(if_fp, instruction -> rs);
			int rename_rt = checkRegStates(if_fp, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = cpu->integerRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vk = cpu->integerRegisters[instruction -> rt]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(if_fp, instruction -> rd, rob_index);
		} else if(opcode == LD) {
			rs_station = rs_load[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			rs_station -> a_immediate = instruction -> immediate;
			int rename_rs = checkRegStates(0, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> a_register = rename_rs + numberOfIntRegisters; // if a_register >= numberOfIntRegisters, means this register is renamed to an ROB entry
			} else {
				rs_station -> a_register = instruction -> rs;
			}
			rs_station -> destination = rob_index;
			updateRegisterStates(0, instruction -> rt, rob_index);
		} else if(opcode == SD) {
			rs_station = rs_save[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			rs_station -> a_immediate = instruction -> immediate;
			int rename_rs = checkRegStates(0, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> a_register = rename_rs + numberOfIntRegisters; // if a_register >= numberOfIntRegisters, means this register is renamed to an ROB entry
			} else {
				rs_station -> a_register = instruction -> rs;
			}
			rs_station -> destination = rob_index;
			updateRegisterStates(0, instruction -> rt, rob_index);
		} else if(opcode == L_D) {
			rs_station = rs_load[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			rs_station -> a_immediate = instruction -> immediate;
			int rename_rs = checkRegStates(0, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> a_register = rename_rs + numberOfIntRegisters; // if a_register >= numberOfIntRegisters, means this register is renamed to an ROB entry
			} else {
				rs_station -> a_register = instruction -> rs;
			}
			rs_station -> destination = rob_index;
			updateRegisterStates(1, instruction -> ft, rob_index);
		} else if(opcode == S_D) {
			rs_station = rs_save[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			rs_station -> a_immediate = instruction -> immediate;
			int rename_rs = checkRegStates(0, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> a_register = rename_rs + numberOfIntRegisters; // if a_register >= numberOfIntRegisters, means this register is renamed to an ROB entry
			} else {
				rs_station -> a_register = instruction -> rs;
			}
			rs_station -> destination = rob_index;
			updateRegisterStates(1, instruction -> ft, rob_index);
		} else if(opcode == ADD_D) {
			rs_station = rs_fpadd[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(if_fp, instruction -> rs);
			int rename_rt = checkRegStates(if_fp, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vfj = cpu->floatingPointRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vfk = cpu->floatingPointRegisters[instruction -> rt]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(if_fp, instruction -> fd, rob_index);
		} else if(opcode == SUB_D) {
			rs_station = rs_fpadd[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(if_fp, instruction -> rs);
			int rename_rt = checkRegStates(if_fp, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vfj = cpu->floatingPointRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vfk = cpu->floatingPointRegisters[instruction -> rt]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(if_fp, instruction -> fd, rob_index);
		} else if(opcode == MUL_D) {
			rs_station = rs_fpmutl[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(if_fp, instruction -> rs);
			int rename_rt = checkRegStates(if_fp, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vfj = cpu->floatingPointRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vfk = cpu->floatingPointRegisters[instruction -> rt]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(if_fp, instruction -> fd, rob_index);
		} else if(opcode == DIV_D) {
			rs_station = rs_fpdiv[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(if_fp, instruction -> rs);
			int rename_rt = checkRegStates(if_fp, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vfj = cpu->floatingPointRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vfk = cpu->floatingPointRegisters[instruction -> rt]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(if_fp, instruction -> fd, rob_index);
		} else if(opcode == BEQZ) {
			rs_station = rs_bu[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(0, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = cpu->integerRegisters[instruction -> rs]->data;
			}
			rs_station -> target = instruction -> target;

			rs_station -> destination = rob_index;
		} else if(opcode == BNEZ) {
			rs_station = rs_bu[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(0, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = cpu->integerRegisters[instruction -> rs]->data;
			}
			rs_station -> target = instruction -> target;

			rs_station -> destination = rob_index;
		} else if(opcode == BEQ) {
			rs_station = rs_bu[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(if_fp, instruction -> rs);
			int rename_rt = checkRegStates(if_fp, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = cpu->integerRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vk = cpu->integerRegisters[instruction -> rt]->data;
			}
			rs_station -> target = instruction -> target;

			rs_station -> destination = rob_index;
		} else if(opcode == BNE) {
			rs_station = rs_bu[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = 0;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(if_fp, instruction -> rs);
			int rename_rt = checkRegStates(if_fp, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = cpu->integerRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vk = cpu->integerRegisters[instruction -> rt]->data;
			}
			rs_station -> target = instruction -> target;

			rs_station -> destination = rob_index;
		}
}

void Issue() {
	int nw; //issue size
	int nr; //rob size
	nw = config -> NW;
	nr = config -> NR;
	int queue_size;
	int rob_size;
	queue_size = instructionQueue -> size;
	rob_size = ROB -> count;
	if (queue_size < nw){
		nw = queue_size;
	}

	if (nw > (nr - rob_size)) {
		nw = nr - rob_size;
	}
	int i;
	for (i = 0; i < nw; i++) {
		Instruction *instruction = (Instruction *)dequeueCircular(instructionQueue);
		int rename = checkRenameRegister(instruction);
		if (rename == -1) {
			printf("instruction stall1");
			break;
		}
		int rob_index = checkROB();
		if (rob_index == -1) {
			printf("rob full");
			break;
		}
		int rs_index = checkRSAvailability(instruction);
		if(rs_index == -1) {
			printf("instruction stall2");
			break;
		}

		updateRS(instruction, rs_index, rob_index);

		ROB_entry *rob_entry = (ROB_entry *) malloc(sizeof(ROB_entry));
		rob_entry -> valid = 1;
		rob_entry -> instruction = instruction;
		if(rename != -2) {
			if (rename >= RENAMING_INT_REGISTER_NUM) {
				rob_entry -> fp_renaming_register = rename - RENAMING_INT_REGISTER_NUM;
				rob_entry -> int_renaming_register = -1;
			}
			else {
				rob_entry -> int_renaming_register = rename;
				rob_entry -> fp_renaming_register = -1;
			}
		}
		rob_entry -> index = instructionQueue -> tail;
		rob_entry -> rob_state = ISSUED_EXECUTING;

		enqueueCircular(ROB, rob_entry);


	}
	printRSStation();
	printROB();
	printRegisterState();
}

