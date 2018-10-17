# include "../Global/TomasuloSimulator.h"


void initializeIssue() {
	int i;

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
		rs_int[i] -> qfj = -1;
		rs_int[i] -> qfk = -1;
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
		rs_mutl[i] -> qfj = -1;
		rs_mutl[i] -> qfk = -1;
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
		rs_load[i] -> qfj = -1;
		rs_load[i] -> qfk = -1;
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
		rs_save[i] -> qfj = -1;
		rs_save[i] -> qfk = -1;
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
		rs_fpadd[i] -> qfj = -1;
		rs_fpadd[i] -> qfk = -1;
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
		rs_fpmutl[i] -> qfj = -1;
		rs_fpmutl[i] -> qfk = -1;
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
		rs_fpdiv[i] -> qfj = -1;
		rs_fpdiv[i] -> qfk = -1;
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
		rs_bu[i] -> qfj = -1;
		rs_bu[i] -> qfk = -1;
		rs_bu[i] -> destination = -1;
		rs_bu[i] -> a_immediate = -2147483648;
		rs_bu[i] -> a_register = -1;
		rs_bu[i] -> target = -1;
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
			if(!rs_fpmutl[i] -> busy) {
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
int checkRegStates(Thread *thread, int if_fp, int register_index) {
	if(if_fp) {
		return thread->register_status -> fp_reg[register_index];
	} else {
		return thread->register_status -> int_reg[register_index];
	}
}

int checkROB(Thread *thread) {
	if (thread->ROB -> count == config -> NR) {
		return -1;
	} else {
		return thread->ROB -> tail;
	}
}

//check whether renaming registers are available or not
//check if rd is -1 or if fd is -1
int checkRenameRegister(Instruction *instruction) {
	OpCode opcode = instruction -> op;
	int i;
	if (opcode == AND || opcode == ANDI || opcode == OR || opcode == ORI
		|| opcode == SLT || opcode == SLTI || opcode == DADD || opcode == DADDI
		|| opcode == DSUB || opcode == DMUL || opcode == LD ) {
		for(i = 0; i < RENAMING_INT_REGISTER_NUM; i++) {
			if(instruction->thread->renaming_status -> int_rreg[i] == 0) {
				return i;
			}
		}
	} else if (opcode == L_D || opcode == ADD_D || opcode == SUB_D
		|| opcode == MUL_D || opcode == DIV_D){
		for(i = 0; i < RENAMING_FP_REGISTER_NUM; i++) {
			if(instruction->thread->renaming_status -> fp_rreg[i] == 0) {
				return i + RENAMING_INT_REGISTER_NUM;
			}
		}
	} else {
		return -2;
	}
	return -1;
}

int setRenameRegister(Instruction *instruction) {
	OpCode opcode = instruction -> op;
	int i;
	if (opcode == AND || opcode == ANDI || opcode == OR || opcode == ORI
		|| opcode == SLT || opcode == SLTI || opcode == DADD || opcode == DADDI
		|| opcode == DSUB || opcode == DMUL || opcode == LD ) {
		for(i = 0; i < RENAMING_INT_REGISTER_NUM; i++) {
			if(instruction->thread->renaming_status -> int_rreg[i] == 0) {
				instruction->thread->renaming_status -> int_rreg[i] = 1;
				return i;
			}
		}
	} else if (opcode == L_D || opcode == ADD_D || opcode == SUB_D
		|| opcode == MUL_D || opcode == DIV_D){
		for(i = 0; i < RENAMING_FP_REGISTER_NUM; i++) {
			if(instruction->thread->renaming_status -> fp_rreg[i] == 0) {
				instruction->thread->renaming_status -> fp_rreg[i] = 1;
				return i + RENAMING_INT_REGISTER_NUM;
			}
		}
	} else {
		return -2;
	}
	return -1;
}

void updateRegisterStates(Thread *thread, int if_fp, int register_index, int rob_index) {
	if(if_fp) {
		thread->register_status -> fp_reg[register_index] = ((ROB_entry*)(thread->ROB->items[rob_index]))->fp_renaming_register;
	} else {
		thread->register_status -> int_reg[register_index] = ((ROB_entry*)(thread->ROB->items[rob_index]))->int_renaming_register;
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
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, 0, instruction -> rs);
			int rename_rt = checkRegStates(instruction->thread, 0, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vk = instruction->thread->integerRegisters[instruction -> rt]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(instruction->thread, 0, instruction -> reg_target_int, rob_index); //update register states using the rob index of the result register
		} else if(opcode == ANDI) {
			rs_station = rs_int[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, 0, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			rs_station -> vk = instruction -> immediate;

			rs_station -> destination = rob_index;
			updateRegisterStates(instruction->thread, 0, instruction -> reg_target_int, rob_index);
		} else if(opcode == OR) {
			rs_station = rs_int[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, 0, instruction -> rs);
			int rename_rt = checkRegStates(instruction->thread, 0, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vk = instruction->thread->integerRegisters[instruction -> rt]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(instruction->thread, 0, instruction -> reg_target_int, rob_index);
		} else if(opcode == ORI) {
			rs_station = rs_int[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, 0, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			rs_station -> vk = instruction -> immediate;

			rs_station -> destination = rob_index;
			updateRegisterStates(instruction->thread, 0, instruction -> reg_target_int, rob_index);
		} else if(opcode == SLT) {
			rs_station = rs_int[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, 0, instruction -> rs);
			int rename_rt = checkRegStates(instruction->thread, 0, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vk = instruction->thread->integerRegisters[instruction -> rt]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(instruction->thread, 0, instruction -> reg_target_int, rob_index);
		} else if(opcode == SLTI) {
			rs_station = rs_int[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, 0, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			rs_station -> vk = instruction -> immediate;

			rs_station -> destination = rob_index;
			updateRegisterStates(instruction->thread, 0, instruction -> reg_target_int, rob_index);
		} else if(opcode == DADD) {
			rs_station = rs_int[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, 0, instruction -> rs);
			int rename_rt = checkRegStates(instruction->thread, 0, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vk = instruction->thread->integerRegisters[instruction -> rt]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(instruction->thread, 0, instruction -> reg_target_int, rob_index);
		} else if(opcode == DADDI) {
			rs_station = rs_int[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, 0, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			rs_station -> vk = instruction -> immediate;

			rs_station -> destination = rob_index;
			updateRegisterStates(instruction->thread, 0, instruction -> reg_target_int, rob_index);
		} else if(opcode == DSUB) {
			rs_station = rs_int[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, 0, instruction -> rs);
			int rename_rt = checkRegStates(instruction->thread, 0, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vk = instruction->thread->integerRegisters[instruction -> rt]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(instruction->thread, 0, instruction -> reg_target_int, rob_index);
		} else if(opcode == DMUL) {
			rs_station = rs_mutl[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, 0, instruction -> rs);
			int rename_rt = checkRegStates(instruction->thread, 0, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vk = instruction->thread->integerRegisters[instruction -> rt]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(instruction->thread, 0, instruction -> reg_target_int, rob_index);
		} else if(opcode == LD) {
			rs_station = rs_load[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			rs_station -> a_immediate = instruction -> immediate;
			int rename_rs = checkRegStates(instruction->thread, 0, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			rs_station -> vk = instruction -> immediate;
			/*if(rename_rs != -1) {
				rs_station -> a_register = rename_rs + numberOfIntRegisters; // if a_register >= numberOfIntRegisters, means this register is renamed to an ROB entry
			} else {
				rs_station -> a_register = instruction -> rs;
			}*/
			rs_station -> destination = rob_index;
			updateRegisterStates(instruction->thread, 0, instruction -> reg_target_int, rob_index);
		} else if(opcode == SD) {
			rs_station = rs_save[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			rs_station -> a_immediate = instruction -> immediate;
			int rename_rs = checkRegStates(instruction->thread, 0, instruction -> rs);
			int rename_rt = checkRegStates(instruction->thread, 0, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			/*if(rename_rs != -1) {
				rs_station -> a_register = rename_rs + numberOfIntRegisters; // if a_register >= numberOfIntRegisters, means this register is renamed to an ROB entry
			} else {
				rs_station -> a_register = instruction -> rs;
			}*/
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vk = instruction->thread->integerRegisters[instruction -> rt]->data;
			}
			rs_station -> destination = rob_index;
			//updateRegisterStates(0, instruction -> reg_target_int, rob_index);
		} else if(opcode == L_D) {
			rs_station = rs_load[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			rs_station -> a_immediate = instruction -> immediate;
			int rename_rs = checkRegStates(instruction->thread, 0, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			rs_station -> vk = instruction -> immediate;
			/*if(rename_rs != -1) {
				rs_station -> a_register = rename_rs + numberOfIntRegisters; // if a_register >= numberOfIntRegisters, means this register is renamed to an ROB entry
			} else {
				rs_station -> a_register = instruction -> rs;
			}*/
			rs_station -> destination = rob_index;
			updateRegisterStates(instruction->thread, 1, instruction -> reg_target_fp, rob_index);
		} else if(opcode == S_D) {
			rs_station = rs_save[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			rs_station -> a_immediate = instruction -> immediate;
			int rename_rs = checkRegStates(instruction->thread, 0, instruction -> rs);
			int rename_rt = checkRegStates(instruction->thread, 1, instruction -> ft);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			/*if(rename_rs != -1) {
				rs_station -> a_register = rename_rs + numberOfIntRegisters; // if a_register >= numberOfIntRegisters, means this register is renamed to an ROB entry
			} else {
				rs_station -> a_register = instruction -> rs;
			}*/
			if(rename_rt != -1) {
				rs_station -> qfk = rename_rt;
			} else {
				rs_station -> vfk = instruction->thread->floatingPointRegisters[instruction -> ft]->data;
			}
			rs_station -> destination = rob_index;
			//updateRegisterStates(1, instruction -> ft, rob_index);
		} else if(opcode == ADD_D) {
			rs_station = rs_fpadd[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, 1, instruction -> fs);
			int rename_rt = checkRegStates(instruction->thread, 1, instruction -> ft);
			if(rename_rs != -1) {
				rs_station -> qfj = rename_rs;
			} else {
				rs_station -> vfj = instruction->thread->floatingPointRegisters[instruction -> fs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qfk = rename_rt;
			} else {
				rs_station -> vfk = instruction->thread->floatingPointRegisters[instruction -> ft]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(instruction->thread, 1, instruction -> reg_target_fp, rob_index);
		} else if(opcode == SUB_D) {
			rs_station = rs_fpadd[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, 1, instruction -> fs);
			int rename_rt = checkRegStates(instruction->thread, 1, instruction -> ft);
			if(rename_rs != -1) {
				rs_station -> qfj = rename_rs;
			} else {
				rs_station -> vfj = instruction->thread->floatingPointRegisters[instruction -> fs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qfk = rename_rt;
			} else {
				rs_station -> vfk = instruction->thread->floatingPointRegisters[instruction -> ft]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(instruction->thread, 1, instruction -> reg_target_fp, rob_index);
		} else if(opcode == MUL_D) {
			rs_station = rs_fpmutl[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, 1, instruction -> fs);
			int rename_rt = checkRegStates(instruction->thread, 1, instruction -> ft);
			if(rename_rs != -1) {
				rs_station -> qfj = rename_rs;
			} else {
				rs_station -> vfj = instruction->thread->floatingPointRegisters[instruction -> fs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qfk = rename_rt;
			} else {
				rs_station -> vfk = instruction->thread->floatingPointRegisters[instruction -> ft]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(instruction->thread, 1, instruction -> reg_target_fp, rob_index);
		} else if(opcode == DIV_D) {
			rs_station = rs_fpdiv[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, 1, instruction -> fs);
			int rename_rt = checkRegStates(instruction->thread, 1, instruction -> ft);
			if(rename_rs != -1) {
				rs_station -> qfj = rename_rs;
			} else {
				rs_station -> vfj = instruction->thread->floatingPointRegisters[instruction -> fs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qfk = rename_rt;
			} else {
				rs_station -> vfk = instruction->thread->floatingPointRegisters[instruction -> ft]->data;
			}

			rs_station -> destination = rob_index;
			updateRegisterStates(instruction->thread, 1, instruction -> reg_target_fp, rob_index);
		} else if(opcode == BEQZ) {
			rs_station = rs_bu[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, 0, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			rs_station -> target = instruction -> target;

			rs_station -> destination = rob_index;
		} else if(opcode == BNEZ) {
			rs_station = rs_bu[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, 0, instruction -> rs);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			rs_station -> target = instruction -> target;

			rs_station -> destination = rob_index;
		} else if(opcode == BEQ) {
			rs_station = rs_bu[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, if_fp, instruction -> rs);
			int rename_rt = checkRegStates(instruction->thread, if_fp, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vk = instruction->thread->integerRegisters[instruction -> rt]->data;
			}
			rs_station -> target = instruction -> target;

			rs_station -> destination = rob_index;
		} else if(opcode == BNE) {
			rs_station = rs_bu[rs_index];
			rs_station -> execution_state = 0;
			rs_station -> busy = 1;
			rs_station -> qj = rs_station -> qk = rs_station -> qfj = rs_station -> qfk = -1;
			rs_station -> op = opcode;
			int rename_rs = checkRegStates(instruction->thread, if_fp, instruction -> rs);
			int rename_rt = checkRegStates(instruction->thread, if_fp, instruction -> rt);
			if(rename_rs != -1) {
				rs_station -> qj = rename_rs;
			} else {
				rs_station -> vj = instruction->thread->integerRegisters[instruction -> rs]->data;
			}
			if(rename_rt != -1) {
				rs_station -> qk = rename_rt;
			} else {
				rs_station -> vk = instruction->thread->integerRegisters[instruction -> rt]->data;
			}
			rs_station -> target = instruction -> target;

			rs_station -> destination = rob_index;
		}
		rs_station->thread = instruction->thread;
}

int issueThread(Thread *thread){
    int result = 0;
	int nw; //issue size
	int nr; //rob size
	nw = config -> NW;
	nr = config -> NR;
	int queue_size;
	int rob_size;
	queue_size = thread->instructionQueue -> size;
	rob_size = thread->ROB -> count;
	if (queue_size < nw){
		nw = queue_size;
	}

	if (nw > (nr - rob_size)) {
		nw = nr - rob_size;
	}
	int i;
	for (i = 0; i < nw; i++) {
		Instruction *instruction = (Instruction *)peekCircular(thread->instructionQueue);
		if(instruction==NULL || instruction->is_valid==0)
            break;
        result++;
		int rename = checkRenameRegister(instruction);
		if (rename == -1) {
			printf("STALL - no available rename registers\n");
			break;
		}
		int rob_index = checkROB(thread);
		if (rob_index == -1) {
			printf("STALL - ROB is full\n");
			break;
		}
		int rs_index = checkRSAvailability(instruction);
		if(rs_index == -1) {
			printf("STALL - no available reservation stations\n");
			break;
		}
        dequeueCircular(thread->instructionQueue);
        setRenameRegister(instruction);
        printf ("Thread %i ISSUED       %i: %s\n", instruction->threadIndex, instruction->PC, instruction->instr);
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
		} else {
            rob_entry -> int_renaming_register = -1;
            rob_entry -> fp_renaming_register = -1;
        }
		rob_entry -> index = instruction->thread->ROB -> tail;
		rob_entry -> rob_state = ISSUED_EXECUTING;

		enqueueCircular(thread->ROB, rob_entry);

		updateRS(instruction, rs_index, rob_index);

	}
	return result;
}

int Issue() {
    int result = 0;
    Thread *thread;
    thread = chooseThread(1);
    result = issueThread(thread);
    thread = chooseThread(0);
    if(thread!=NULL)
        result += issueThread(thread);
    return result;
}

