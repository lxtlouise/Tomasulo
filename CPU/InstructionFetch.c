# include "../Global/TomasuloSimulator.h"

int getHashCodeFromCacheAddress_IF (void *address);
int compareBTBValues (void *btbvalue1, void *btbvalue2);


void initializeInstruction(Instruction *instruction){
    instruction->is_valid = 0;
    instruction->branch_predicted = 0;
    instruction->prediction_taken = 0;
    instruction->prediction_target = 0;
}

void copyInstruction(Instruction *dest, Instruction *src){
    strncpy(dest->instr, src->instr, MAX_LINE);
    dest->PC = src->PC;
    dest->is_valid = src->is_valid;
	dest->op = src->op;
	dest->address = src->address;

	dest->rd = src->rd;
	dest->rs = src->rs;
	dest->rt = src->rt;

	dest->rsValue = src->rsValue;
	dest->rtValue = src->rtValue;

	dest->fd = src->fd;
	dest->fs = src->fs;
	dest->ft = src->ft;

	dest->fsValue = src->fsValue;
	dest->ftValue = src->ftValue;

	dest->immediate = src->immediate;

	dest->target = src->target;
	dest->branch_predicted = src->branch_predicted;
	dest->prediction_taken = src->prediction_taken;
	dest->prediction_target = src->prediction_target;
}

void initializeFetch() {
    if_unit = (IF_Unit*) malloc(sizeof(IF_Unit));
    BTB = createDictionary(getHashCodeFromCacheAddress_IF, compareBTBValues);
    if_unit->PC = instructionCacheBaseAddress;
}


void setBTBEntry(Instruction* instruction, int branch_taken, int branch_target){
    BTB_value* val;
    DictionaryEntry *dval = getValueChainByDictionaryKey(BTB, &(instruction->PC));
    if(dval==NULL){
        val = malloc(sizeof(BTB_value));
        val->PC = instruction->PC;
        addDictionaryEntry (BTB, &(instruction->PC), val);
    } else{
        val = dval->value->value;
        val->PC = instruction->PC;
    }
    val->taken = branch_taken;
    if(branch_taken)
        val->target_address = branch_target;
    else
        val->target_address = instruction->PC + 4;
}

int predecodeBranchInstruction(Instruction *instruction){
    char *token = (char *) malloc (sizeof(char) * MAX_LINE);

	int is_branch = 0;
	token = (char *) malloc (sizeof(char) * MAX_LINE);

	strcpy (token, instruction->instr);

	token = strtok(token, " ,()\t\n");

	if(strcmp(token, "BEQZ") == 0) {
		token = strtok(NULL, " ,()RF\t\n");
		token = strtok(NULL, " ,()\t\n");
        is_branch = 1;
	} else if(strcmp(token, "BNEZ") == 0) {
		token = strtok(NULL, " ,()RF\t\n");
		token = strtok(NULL, " ,()RF\t\n");
        is_branch = 1;
	} else if(strcmp(token, "BEQ") == 0) {
		token = strtok(NULL, " ,()RF\t\n");
		token = strtok(NULL, " ,()RF\t\n");
		token = strtok(NULL, " ,()RF\t\n");
        is_branch = 1;
	} else if(strcmp(token, "BNE") == 0) {
		token = strtok(NULL, " ,()RF\t\n");
		token = strtok(NULL, " ,()RF\t\n");
		token = strtok(NULL, " ,()RF\t\n");
        is_branch = 1;
	} else {
        instruction->branch_predicted = 0;
        instruction->prediction_taken = 0;
        instruction->prediction_target = 0;
	    return 0;
	}

	if (is_branch) {
		DictionaryEntry *codeLabel = getValueChainByDictionaryKey (codeLabels, (void *) token);

		if (codeLabel == NULL) {
			printf("Invalid code label cannot be resolved...\n");
			exit (EXIT_FAILURE);
		} else {
            DictionaryEntry *dval = getValueChainByDictionaryKey(BTB, &(instruction->PC));
            if(dval){
                BTB_value *val = dval->value->value;
                if(val->PC == instruction->PC){
                    instruction->branch_predicted = 1;
                    instruction->prediction_target = val->target_address;
                    instruction->prediction_taken = val->taken;
                    return 1;
                }
            }
		}
	}
    return 0;
}

int runClockCycle_IF() {
    int i;
    if_unit->n_instructions = 0;
    for(i=0; i<config->NF; i++){
        if (if_unit->PC >= (instructionCacheBaseAddress + (cacheLineSize * numberOfInstruction))) { //check whether PC exceeds last instruction in cache
            printf ("All instructions finished...\n");
            return -1;
        }


        DictionaryEntry *currentInstruction = getValueChainByDictionaryKey (instructionCache, &(if_unit->PC));
        if_unit->instructions[i] = (Instruction*)malloc(sizeof(Instruction));
        initializeInstruction(if_unit->instructions[i]);
        if_unit->instructions[i]->PC = if_unit->PC;
        strncpy(if_unit->instructions[i]->instr, ((char*)currentInstruction -> value -> value), MAX_LINE);
        printf ("Fetched %d:%s\n", if_unit->PC, if_unit->instructions[i]->instr);
        if_unit->instructions[i]->is_valid = 1;
        if(predecodeBranchInstruction(if_unit->instructions[i])){
            if(if_unit->instructions[i]->prediction_taken)
                if_unit->PC = if_unit->instructions[i]->prediction_target;
            else
                if_unit->PC = if_unit->PC + 4;
        } else {
            if_unit->PC = if_unit->PC + 4;
        }
        if_unit->n_instructions = i+1;
    }
    return 1;
}

int getHashCodeFromCacheAddress_IF (void *address) {
    return (*((int*)address) & 0x3c) >> 2;
}


int compareBTBValues (void *PC1, void *PC2) {
    return (*((int*)PC1) & 0x3c)  - (*((int*)PC2) & 0x3c);
}

