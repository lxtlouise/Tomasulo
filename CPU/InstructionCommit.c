# include "../Global/TomasuloSimulator.h"

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
  || opcode == DADDI || opcode == DSUB || opcode == DMUL) {
    destination = rob_entry -> instruction -> rd;
    int result = renaming_int_registers[rob_entry -> int_renaming_register] -> data;
    cpu -> integerRegisters[destination] -> data = result;
  } else if (opcode == ADD_D || opcode == SUB_D || opcode == MUL_D || opcode == DIV_D) {
    destination = rob_entry -> instruction -> fd;
    int result = renaming_int_registers[rob_entry -> fp_renaming_register] -> data;
    cpu -> floatingPointRegisters[destination] -> data = result;
  } else if (opcode == LD) {
    destination = rob_entry -> instruction -> rd;
    address = rob_entry -> ls_address;
    DictionaryEntry * dictionary_entry = getValueChainByDictionaryKey(dataCache, &address);
    int result = *((int *) dictionary_entry -> value -> value);
    cpu -> integerRegisters[destination] -> data = result;
  } else if (opcode == L_D) {
    destination = rob_entry -> instruction -> fd;
    address = rob_entry -> ls_address;
    DictionaryEntry * dictionary_entry = getValueChainByDictionaryKey(dataCache, &address);
    double result = *((double *) dictionary_entry -> value -> value);
    cpu -> floatingPointRegisters[destination] -> data = result;
  }
}

void writeMemory(ROB_entry * rob_entry) {
  void * address = malloc(sizeof(int));
  *((int*)address) = rob_entry -> ls_address;
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
  while (1) {
    int bus = checkBUS();
    if (bus != -1) {
	printf("size2: %d\n", ROB -> count);
      if (ROB->count == 0) {
        printf("Rob is empty!");
        break;
      } else if (((ROB_entry*)ROB->items[0])->valid == 1 && ((ROB_entry*)ROB->items[0])->rob_state == WROTE_RESULT) {
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
      } else if (((ROB_entry*)ROB->items[0])->valid == 0) {
        while (((ROB_entry*)ROB->items[0])->valid == 0) {
          dequeueCircular(ROB);
        }
      }
    } else {
        break;
      }
    }
}
