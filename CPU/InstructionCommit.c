# include "../Global/TomasuloSimulator.h"

void propagateResultAgain(ROB_entry *rob_entry){
    Instruction *instruction = rob_entry->instruction;

    int renamed_int = rob_entry->int_renaming_register;
    int renamed_float = rob_entry->fp_renaming_register;
    if(instruction->reg_target_int>=0 && instruction->thread->register_status->int_reg[instruction->reg_target_int]==renamed_int)
        instruction->thread->register_status->int_reg[instruction->reg_target_int] = -1;
    if(instruction->reg_target_fp>=0 && instruction->thread->register_status->fp_reg[instruction->reg_target_fp]==renamed_float)
        instruction->thread->register_status->fp_reg[instruction->reg_target_fp] = -1;

    int i;
    for(i=0; i<RESERV_ALL_NUM; i++){
        RS_Station *rs = ex_unit->allReservationStations[i];
        if(rs->thread!=instruction->thread)
            continue;
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
        instruction->thread->renaming_status -> int_rreg[renamed_int] = 0;
    if(renamed_float>=0)
        instruction->thread->renaming_status -> fp_rreg[renamed_float] = 0;
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
  Thread *thread = rob_entry->instruction->thread;
  int destination;
  int address;
  if (opcode == AND || opcode == ANDI || opcode == OR || opcode == ORI || opcode == SLT || opcode == SLTI || opcode == DADD
  || opcode == DADDI || opcode == DSUB || opcode == DMUL || opcode == LD) {
    destination = rob_entry -> instruction -> reg_target_int;
    thread -> integerRegisters[destination] -> data = rob_entry->int_result;
  } else if (opcode == ADD_D || opcode == SUB_D || opcode == MUL_D || opcode == DIV_D || opcode == L_D) {
    destination = rob_entry -> instruction -> reg_target_fp;
    thread -> floatingPointRegisters[destination] -> data = rob_entry->float_result;
  }
}

void writeMemory(ROB_entry * rob_entry) {
  Thread *thread = rob_entry->instruction->thread;
  void * address = malloc(sizeof(int));
  *((int*)address) = rob_entry -> addr_result;
  OpCode opcode = rob_entry -> instruction -> op;
  void * result = malloc(sizeof(double));
  if (opcode == SD) {
    *((double*)result) = rob_entry -> int_result;
    removeDictionaryEntriesByKey (thread->dataCache, address);
    addDictionaryEntry(thread->dataCache, address, result);
  } else if (opcode == S_D) {
    *((double*)result) = rob_entry -> float_result;
    removeDictionaryEntriesByKey (thread->dataCache, address);
    addDictionaryEntry(thread->dataCache, address, result);
  }
}

int commitThread(Thread *thread) {
  int result = 0;
  while (1) {
    int bus = checkBUS();
    if (bus != -1) {
      if (thread->ROB->count == 0) {
        break;
      } else {
        if (((ROB_entry*)thread->ROB->items[thread->ROB->head])->valid == 0) {
          while (thread->ROB->count>0&& ((ROB_entry*)thread->ROB->items[thread->ROB->head])->valid == 0) {
            dequeueCircular(thread->ROB);
          }
        } else {
          if(((ROB_entry*)thread->ROB->items[thread->ROB->head])->rob_state != WROTE_RESULT){
            break;
          } else {
            ROB_entry *entry = (ROB_entry *) dequeueCircular(thread->ROB);
            result++;
            printf("Thread %i COMMITED     %i: %s -> %i - %f\n", entry->instruction->threadIndex, entry->instruction->PC, entry->instruction->instr, entry->int_result, entry->float_result);
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
    return result;
}

int commit(){
    CDB_counter = 0;
    Thread *thread = chooseThread(1);
    int result = commitThread(thread);
    thread = chooseThread(0);
    if(thread==NULL)
        return result;
    return result + commitThread(thread);
}
