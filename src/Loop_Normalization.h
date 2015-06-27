#ifndef LOOP_NORMALIZATION
#define LOOP_NORMALIZATION
#include "cuda_y.h"
int isVariable(char *name,int *b_val,struct Var* variable);
void loop_normalization(int verbosity_no, struct StatementNode* stmt,struct Var* variable, struct LoopIndexVar_New* loop_id);
#endif

