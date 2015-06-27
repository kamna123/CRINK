#ifndef EXTENDED_CS
#define EXTENDED_CS
#include "cuda_y.h"
int getLoopNo(char *str,struct LoopIndexVar_New* loop_id);
void CalculateLambda(struct StringNode* depString,int *lambda);
void extCS_VariableDistance_Lambda(struct StatementNode *read_var,struct StatementNode *write_var, struct LoopIndexVar_New* loop_id, struct Stmt_Var* stmt_var);
void extCS_ConstantDistance_Lambda(struct StatementNode *read_var,struct StatementNode *write_var, struct LoopIndexVar_New* loop_id, struct Stmt_Var* stmt_var);
#endif
