# include "../Global/TomasuloSimulator.h"

void initializeExecute() {
    int i;
    ex_unit = (EX_Unit*) malloc(sizeof(EX_Unit));
    ex_unit->pipeline_stages_INT[0] = NULL;
    for(i=0; i<4; i++)
        ex_unit->pipeline_stages_MULT[i] = NULL;
    ex_unit->pipeline_stages_INT[0] = NULL;
    for(i=0; i<3; i++)
        ex_unit->pipeline_stages_FPadd[i] = NULL;
    for(i=0; i<4; i++)
        ex_unit->pipeline_stages_FPmult[i] = NULL;
    ex_unit->pipeline_stages_FPdiv[0] = NULL;

    ex_unit->allReservationStations = malloc(sizeof(RS_Station*) * (RESERV_ALL_NUM));
    int j=0;
    for(i=0; i<RESERV_INT_SIZE; i++)
        ex_unit->allReservationStations[j++] = rs_int[i];
    for(i=0; i<RESERV_MULT_SIZE; i++)
        ex_unit->allReservationStations[j++] = rs_mutl[i];
    for(i=0; i<RESERV_LOAD_BUFFER_SIZE; i++)
        ex_unit->allReservationStations[j++] = rs_load[i];
    for(i=0; i<RESERV_STORE_BUFFER_SIZE; i++)
        ex_unit->allReservationStations[j++] = rs_save[i];
    for(i=0; i<RESERV_FPADD_SIZE; i++)
        ex_unit->allReservationStations[j++] = rs_fpadd[i];
    for(i=0; i<RESERV_FPMULT_SIZE; i++)
        ex_unit->allReservationStations[j++] = rs_fpmutl[i];
    for(i=0; i<RESERV_FPDIV_SIZE; i++)
        ex_unit->allReservationStations[j++] = rs_fpdiv[i];
    for(i=0; i<RESERV_BU_SIZE; i++)
        ex_unit->allReservationStations[j++] = rs_bu[i];
}


void propagateResult(RS_Station *rs_station, int int_result, float float_result, int addr_result){
    ROB_entry *rob_entry = (ROB_entry*)(ROB->items[rs_station->destination]);
    Instruction *instruction = rob_entry->instruction;
    //int renamed_int = checkRegStates(0, instruction->reg_target_int);
    //int renamed_float = checkRegStates(1, instruction->reg_target_fp);
    int renamed_int = rob_entry->int_renaming_register;
    int renamed_float = rob_entry->fp_renaming_register;

    int i;
    for(i=0; i<RESERV_ALL_NUM; i++){
        RS_Station *rs = ex_unit->allReservationStations[i];
        if(rs->qj >= 0 && rs->qj == renamed_int){
            rs->vj = int_result;
            rs->qj = -1;
        }
        if(rs->qk >= 0 && rs->qk == renamed_int){
            rs->vk = int_result;
            rs->qk = -1;
        }
        if(rs->qfj >= 0 && rs->qfj == renamed_float){
            rs->vfj = float_result;
            rs->qfj = -1;
        }
        if(rs->qfk >= 0 && rs->qfk == renamed_float){
            rs->vfk = float_result;
            rs->qfk = -1;
        }
    }
    //if(renamed_int>=0)
    //    renaming_status -> int_rreg[renamed_int] = 0;
    //if(renamed_float>=0)
    //    renaming_status -> fp_rreg[renamed_float] = 0;
    rs_station->busy = 0;
    rob_entry->int_result = int_result;
    rob_entry->float_result = float_result;
    rob_entry->addr_result = addr_result;
    rob_entry->rob_state = WROTE_RESULT;
}

void execute_operation(RS_Station *rs_station, int *iresult, float *fresult, int *aresult);

void executeBranch(RS_Station *rs_station);

void runClockCycle_EX(){
    int cdb_usage = 0;
    int cdb_sz = config->NB - CDB_counter;
    int i, j;
    RS_Station *rs_station;

    RS_Station* cdbr[32];
    int cdbi[32];
    float cdbf[32];
    int cdba[32];

    for(i=0; i<RESERV_BU_SIZE; i++){
        rs_station = rs_bu[i];
        if(rs_station->busy){
            if(rs_station->qj==-1 && rs_station->qk==-1){
                if(rs_station->execution_state==0){
                    ROB_entry* robEntry = ROB->items[rs_station->destination];
                    executeBranch(rs_station);
                    rs_station->execution_state++;
                } else
                    rs_station->execution_state++;
            }
        }
    }

    for(i=0; i<RESERV_INT_SIZE; i++){
        if(cdb_usage < cdb_sz){
            rs_station = rs_int[i];
            if(rs_station->busy){
                if(rs_station->qj==-1 && rs_station->qk==-1){
                    if(rs_station->execution_state==0){
                        cdbr[cdb_usage] = rs_station;
                        execute_operation(rs_station, &(cdbi[cdb_usage]), &(cdbf[cdb_usage]), &(cdba[cdb_usage]));
                        rs_station->execution_state++;
                        cdb_usage++;
                    } else
                        rs_station->execution_state++;
                }
            }
        }
    }

    for(i=0; i<RESERV_LOAD_BUFFER_SIZE; i++){
        if(cdb_usage < cdb_sz){
            rs_station = rs_load[i];
            if(rs_station->busy){
                if(rs_station->qj==-1 && rs_station->qk==-1){
                    if(rs_station->execution_state==0){
                        cdbr[cdb_usage] = rs_station;
                        execute_operation(rs_station, &(cdbi[cdb_usage]), &(cdbf[cdb_usage]), &(cdba[cdb_usage]));
                        rs_station->execution_state++;
                        cdb_usage++;
                    } else
                        rs_station->execution_state++;
                }
            }
        }
    }

    for(i=0; i<RESERV_STORE_BUFFER_SIZE; i++){
        if(cdb_usage < cdb_sz){
            rs_station = rs_save[i];
            if(rs_station->busy){
                if(rs_station->qj==-1 && rs_station->qk==-1){
                    if(rs_station->execution_state==0){
                        cdbr[cdb_usage] = rs_station;
                        execute_operation(rs_station, &(cdbi[cdb_usage]), &(cdbf[cdb_usage]), &(cdba[cdb_usage]));
                        rs_station->execution_state++;
                        cdb_usage++;
                    } else
                        rs_station->execution_state++;
                }
            }
        }
    }

    for(j=PIPELINE_STAGES_MULT-1; j>=0; j--){
        rs_station = ex_unit->pipeline_stages_MULT[j];
        if(j==PIPELINE_STAGES_MULT-1){
            if(rs_station!=NULL){
                if(cdb_usage < cdb_sz && rs_station->busy!=0){
                    cdbr[cdb_usage] = rs_station;
                    execute_operation(rs_station, &(cdbi[cdb_usage]), &(cdbf[cdb_usage]), &(cdba[cdb_usage]));
                    ex_unit->pipeline_stages_MULT[j] = NULL;
                    rs_station->execution_state++;
                    cdb_usage++;
                }
            }
        } else if(j>0){
            if(rs_station!=NULL){
                if(ex_unit->pipeline_stages_MULT[j+1]==NULL){
                    ex_unit->pipeline_stages_MULT[j+1] = rs_station;
                    ex_unit->pipeline_stages_MULT[j] = NULL;
                    rs_station->execution_state++;
                }
            }
        } else {
            int to_insert;
            if(rs_station!=NULL){
                if(ex_unit->pipeline_stages_MULT[j+1]==NULL){
                    ex_unit->pipeline_stages_MULT[j+1] = rs_station;
                    to_insert = 1;
                } else {
                    to_insert = 0;
                }
            } else
                to_insert = 1;
            if(to_insert){
                ex_unit->pipeline_stages_MULT[j] = NULL;

                for(i=0; i<RESERV_MULT_SIZE; i++){
                    rs_station = rs_mutl[i];
                    if(rs_station->busy){
                        if(rs_station->qj==-1 && rs_station->qk==-1){
                            if(rs_station->execution_state==0){
                                rs_station->execution_state++;
                                ex_unit->pipeline_stages_MULT[0] = rs_station;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    for(j=PIPELINE_STAGES_FPadd-1; j>=0; j--){
        rs_station = ex_unit->pipeline_stages_FPadd[j];
        if(j==PIPELINE_STAGES_MULT-1){
            if(rs_station!=NULL){
                if(cdb_usage < cdb_sz && rs_station->busy!=0){
                    cdbr[cdb_usage] = rs_station;
                    execute_operation(rs_station, &(cdbi[cdb_usage]), &(cdbf[cdb_usage]), &(cdba[cdb_usage]));
                    ex_unit->pipeline_stages_FPadd[j] = NULL;
                    rs_station->execution_state++;
                    cdb_usage++;
                }
            }
        } else if(j>0){
            if(rs_station!=NULL){
                if(ex_unit->pipeline_stages_FPadd[j+1]==NULL){
                    ex_unit->pipeline_stages_FPadd[j+1] = rs_station;
                    ex_unit->pipeline_stages_FPadd[j] = NULL;
                    rs_station->execution_state++;
                }
            }
        } else {
            int to_insert;
            if(rs_station!=NULL){
                if(ex_unit->pipeline_stages_FPadd[j+1]==NULL){
                    ex_unit->pipeline_stages_FPadd[j+1] = rs_station;
                    to_insert = 1;
                } else {
                    to_insert = 0;
                }
            } else
                to_insert = 1;
            if(to_insert){
                ex_unit->pipeline_stages_FPadd[j] = NULL;

                for(i=0; i<RESERV_FPADD_SIZE; i++){
                    rs_station = rs_fpadd[i];

                    if(rs_station->busy){
                        if(rs_station->qj==-1 && rs_station->qk==-1){
                            if(rs_station->execution_state==0){
                                rs_station->execution_state++;
                                ex_unit->pipeline_stages_FPadd[0] = rs_station;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    for(j=PIPELINE_STAGES_FPmult-1; j>=0; j--){
        rs_station = ex_unit->pipeline_stages_FPmult[j];
        if(j==PIPELINE_STAGES_MULT-1){
            if(rs_station!=NULL){
                if(cdb_usage < cdb_sz && rs_station->busy!=0){
                    cdbr[cdb_usage] = rs_station;
                    execute_operation(rs_station, &(cdbi[cdb_usage]), &(cdbf[cdb_usage]), &(cdba[cdb_usage]));
                    ex_unit->pipeline_stages_FPmult[j] = NULL;
                    rs_station->execution_state++;
                    cdb_usage++;
                }
            }
        } else if(j>0){
            if(rs_station!=NULL){
                if(ex_unit->pipeline_stages_FPmult[j+1]==NULL){
                    ex_unit->pipeline_stages_FPmult[j+1] = rs_station;
                    ex_unit->pipeline_stages_FPmult[j] = NULL;
                    rs_station->execution_state++;
                }
            }
        } else {
            int to_insert;
            if(rs_station!=NULL){
                if(ex_unit->pipeline_stages_FPmult[j+1]==NULL){
                    ex_unit->pipeline_stages_FPmult[j+1] = rs_station;
                    to_insert = 1;
                } else {
                    to_insert = 0;
                }
            } else
                to_insert = 1;
            if(to_insert){
                ex_unit->pipeline_stages_FPmult[j] = NULL;

                for(i=0; i<RESERV_FPMULT_SIZE; i++){
                    rs_station = rs_fpmutl[i];
                    if(rs_station->busy){
                        if(rs_station->qj==-1 && rs_station->qk==-1){
                            if(rs_station->execution_state==0){
                                rs_station->execution_state++;
                                ex_unit->pipeline_stages_FPmult[0] = rs_station;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    for(i=0; i<cdb_usage; i++){
        propagateResult(cdbr[i], cdbi[i], cdbf[i], cdba[i]);
    }
}
void propagateResultAgain(ROB_entry *rob_entry);

void invalidateROBEntry(ROB_entry *rob_entry){
    rob_entry->valid = 0;
    rob_entry->instruction->is_valid = 0;
    propagateResultAgain(rob_entry);
    int i;
    for(i=0; i<RESERV_ALL_NUM; i++){
        RS_Station *rs = ex_unit->allReservationStations[i];
        if((ROB_entry*)(ROB->items[rs->destination]) == rob_entry){
            if(!rob_entry->valid){
                rs->busy = 0;
            }
        }
    }
}

void executeBranch(RS_Station *rs_station){
    ROB_entry* rob_entry;
    int ended = 0, i;
    for(i=rs_station->destination+1; i<ROB->size; i++){
        if(i==ROB->tail){
            ended = 1;
            break;
        }
        rob_entry = ROB->items[i];
        invalidateROBEntry(rob_entry);
    }
    for(i=0; i<ROB->tail&&ended==0; i++){
        rob_entry = ROB->items[i];
        invalidateROBEntry(rob_entry);
    }
    id_unit->instructionQueue -> head = 0;
	id_unit->instructionQueue -> tail = 0;
	id_unit->instructionQueue -> count = 0;
	if_unit->n_instructions = 0;
	id_unit->min_fetched_instructions = 0;
    rob_entry = ROB->items[rs_station->destination];
    if_unit->PC = rob_entry->instruction->target;
    rob_entry->rob_state = WROTE_RESULT;
    rs_station->busy = 0;
}

void execute_operation(RS_Station *rs_station, int *iresult, float *fresult, int *aresult){
    DictionaryEntry *dataCacheElement;
    *iresult = 0;
    *fresult = 0.0f;
    *aresult = 0;
    switch(rs_station->op){
    case AND:
    case ANDI:
        *iresult = rs_station->vj & rs_station->vk;
        break;
    case OR:
    case ORI:
        *iresult = rs_station->vj | rs_station->vk;
        break;
    case SLT:
    case SLTI:
        if(rs_station->vj < rs_station->vk)
            *iresult = 1;
        else
            *iresult = 0;
        break;
    case DADD:
    case DADDI:
        *iresult = rs_station->vj + rs_station->vk;
        break;
    case DSUB:
        *iresult = rs_station->vj - rs_station->vk;
        break;
    case DMUL:
        *iresult = rs_station->vj * rs_station->vk;
        break;
    case LD:
        *aresult = rs_station->vj + rs_station->vk;
        dataCacheElement = getValueChainByDictionaryKey (dataCache, aresult);
        *iresult = (int) *((double*)(dataCacheElement -> value -> value));
        break;
    case SD:
        *aresult = rs_station->vj + rs_station->vk;
        break;
    case L_D:
        *aresult = rs_station->vj + rs_station->vk;
        dataCacheElement = getValueChainByDictionaryKey (dataCache, aresult);
        *fresult = *((double*)(dataCacheElement -> value -> value));
        break;
    case S_D:
        *aresult = rs_station->vj + rs_station->vk;
        break;
    case ADD_D:
        *fresult = rs_station->vfj - rs_station->vfk;
        break;
    case SUB_D:
        *fresult = rs_station->vfj - rs_station->vfk;
        break;
    case MUL_D:
        *fresult = rs_station->vfj - rs_station->vfk;
        break;
    case DIV_D:
        *fresult = rs_station->vfj - rs_station->vfk;
        break;
    case BEQZ:
        *iresult = rs_station->vj == 0 ? 1 : 0;
        break;
    case BNEZ:
        *iresult = rs_station->vj != 0 ? 1 : 0;
        break;
    case BEQ:
        *iresult = rs_station->vj == rs_station->vk ? 1 : 0;
        break;
    case BNE:
        *iresult = rs_station->vj != rs_station->vk ? 1 : 0;
        break;
    default:
        break;
    }
}
