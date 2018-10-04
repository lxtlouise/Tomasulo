# include "../Global/TomasuloSimulator.h"

int getHashCodeFromCacheAddress_IF (void *address);
int compareBTBValues (void *btbvalue1, void *btbvalue2);


void initializeIF_Unit() {
    BTB = createDictionary(getHashCodeFromCacheAddress_IF, compareBTBValues);
	if_unit = (struct _IFUnit*) malloc(sizeof(struct _IFUnit));
	if_unit->instructions = (char**) malloc(config->NF * sizeof(char*));
	int i = 0;
	for (; i < config->NF; i++) {
		*(if_unit->instructions + i) = (char*) malloc(sizeof(char) * MAX_LINE);
	}
}

void fetch_instruction() {
	if_unit -> PC = cpu -> PC;
	if_unit -> n_instructions = 0;
	int num_instrction = config->NF;
	if (0) {
		//TODO: cases when we can only fetch less than NF instructions
	}
	int i = 0;
	for (; i <num_instrction; i++) {
		void *addrPtr = malloc(sizeof(int));
		*((int*)addrPtr) = cpu -> PC;
		DictionaryEntry *currentInstruction = getValueChainByDictionaryKey (instructionCache, addrPtr);

    	strcpy (*(if_unit->instructions + i), ((char*)currentInstruction -> value -> value));
		if_unit -> n_instructions++;
    	printf ("Fetched %d:%s\n", if_unit -> PC, *(if_unit->instructions + i));
		DictionaryEntry *BTB_result = getValueChainByDictionaryKey(BTB, addrPtr);
		if (BTB_result != NULL) {	// if current instruction is a branch
			BTB_value *prediction =  (BTB_value*)BTB_result;
			if (prediction -> taken) {
				cpu -> PC = prediction -> target_address;
				continue;
			}
		}
		cpu -> PC += 4;
	}
}

int getHashCodeFromCacheAddress_IF (void *address) {
    int mask = 0x00E0;
    int result = *((int*)address) & mask;
    result = result >> 4;
    return result;
}


int compareBTBValues (void *btbvalue1, void *btbvalue2) {
	if (((BTB_value*)btbvalue1)->target_address == ((BTB_value*)btbvalue2)->target_address && ((BTB_value*)btbvalue1)->taken == ((BTB_value*)btbvalue2)->taken) {
		return 0;
	}
    return 1;
}