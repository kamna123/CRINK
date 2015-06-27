#ifndef OMEGA
#define OMEGA
#include "cuda_y.h"

int count_dep_var(struct StatementNode* read,char *var_name);
void print_loop_limits(struct StringNode* loop_limit,struct LoopIndexVar_New* loop_id);
void print_dependency(struct StatementNode* read,struct StatementNode* write,struct LoopIndexVar_New* loop_id,char *var_name,int total_read_var,int total_write_var);
int Omega_Test(struct StatementNode* read,struct StatementNode* write,struct LoopIndexVar_New* loop_id,struct Stmt_Var* statement_var);
#endif
