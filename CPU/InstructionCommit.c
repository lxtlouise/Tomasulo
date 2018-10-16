# include "../Global/TomasuloSimulator.h"

void propagateResultAgain(ROB_entry *rob_entry){
    //ROB_entry *rob_entry = (ROB_entry*)(ROB->items[rs_station->destination]);
    Instruction *instruction = rob_entry->instruction;
    //int renamed_int = checkRegStates(0, instruction->reg_target_int);
    //int renamed_float = checkRegStates(1, instruction->reg_target_fp);
    if(instruction->reg_target_int>=0)
        register_status->int_reg[instruction->reg_target_int] = -1;
    if(instruction->reg_target_fp>=0)
        register_status->fp_reg[instruction->reg_target_fp] = -1;

    int renamed_int = rob_entry->int_renaming_register;
    int renamed_float = rob_entry->fp_renaming_register;

    int i;
    for(i=0; i<RESERV_ALL_NUM; i++){
        RS_Station *rs = ex_unit->allReservationStations[i];
        if(rs->qj >= 0 && rs->qj == renamed_int){
            rs->vj = rob_entry->int_result;
            rs->qj = -1;
        }
        if(rs->qk >= 0 && rs->qk == renamed_int){
            rs->vk = rob_entry->int_result;
            rs->qk = -1;
        }
        if(rs->qfj >= 0 && rs->qfj == renamed_float){
            rs->vfj = rob_entry->float_result;
            rs->qfj = -1;
        }
        if(rs->qfk >= 0 && rs->qfk == renamed_float){
            rs->vfk = rob_entry->float_result;
            rs->qfk = -1;
        }
    }
    if(renamed_int>=0)
        renaming_status -> int_rreg[renamed_int] = 0;
    if(renamed_float>=0)
        renaming_status -> fp_rreg[renamed_float] = 0;
}

int checkBUS() {
  if (CDB_counter < config -> NB) {
    return (config -> NB - CDB_counter);
  } else {
    return -1;
  }
}

void writeRegister(ROB_entry * rob_entry) {
  OpCode opcode = rob_entry -> instruction -> op;
  int destination;
  int address;
  if (opcode == AND || opcode == ANDI || opcode == OR || opcode == ORI || opcode == SLT || opcode == SLTI || opcode == DADD
  || opcode == DADDI || opcode == DSUB || opcode == DMUL || opcode == LD) {
    destination = rob_entry -> instruction -> reg_target_int;
    cpu -> integerRegisters[destination] -> data = rob_entry->int_result;
  } else if (opcode == ADD_D || opcode == SUB_D || opcode == MUL_D || opcode == DIV_D || opcode == L_D) {
    destination = rob_entry -> instruction -> reg_target_fp;
    cpu -> floatingPointRegisters[destination] -> data = rob_entry->float_result;
  }
}

void writeMemory(ROB_entry * rob_entry) {
  void * address = malloc(sizeof(int));
  *((int*)address) = rob_entry -> addr_result;
  OpCode opcode = rob_entry -> instruction -> op;
  void * result = malloc(sizeof(double));
  if (opcode == SD) {
    *((double*)result) = rob_entry -> int_result;
    addDictionaryEntry(dataCache, address, result);
  } else if (opcode == S_D) {
    *((double*)result) = rob_entry -> float_result;
    addDictionaryEntry(dataCache, address, result);
  }
}

void commit() {
  CDB_counter = 0;
  while (1) {
    int bus = checkBUS();
    if (bus != -1) {
	printf("size2: %d\n", ROB -> count);
      if (ROB->count == 0) {
        printf("Rob is empty!");
        break;
      } else {
        if (((ROB_entry*)ROB->items[ROB->head])->valid == 0) {
          while (ROB->count>0&& ((ROB_entry*)ROB->items[ROB->head])->valid == 0) {
            dequeueCircular(ROB);
          }
        } else {
          if(((ROB_entry*)ROB->items[ROB->head])->rob_state != WROTE_RESULT){
            break;
          } else {
            ROB_entry *entry = (ROB_entry *) dequeueCircular(ROB);
            if (entry->instruction->op == SD || entry->instruction->op == S_D) {
              writeMemory(entry);
              CDB_counter++;
            } else if (entry->instruction->op == BEQ || entry->instruction->op == BEQZ ||
                       entry->instruction->op == BNE || entry->instruction->op == BNEZ) {
              continue;
            } else {
              writeRegister(entry);
              CDB_counter++;
            }
            propagateResultAgain(entry);
          }
        }
      }
    } else {
        break;
      }
    }
}
