#ifndef CYCLE_SHRINKING
#define CYCLE_SHRINKING
#include "cuda_y.h"
struct Phi_Values *find_phi_values(struct SizeNode *dep_size,struct Phi_Values *lambda,struct LoopIndexVar_New* loop_node);
struct Phi_Values *Simple_Loops_Code_Gen(struct StatementNode* read,struct StatementNode* write,struct LoopIndexVar_New* loop_id,struct Stmt_Var* statement_var);
struct Phi_Values *True_Dependence_Lambda(struct StatementNode* read,struct StatementNode* write,struct LoopIndexVar_New* loopId,struct Stmt_Var* statement_var);
void CycleShrinking(int verbosity_no, char *shrinking,struct StatementNode* read,struct StatementNode* write,struct LoopIndexVar_New* loop_id,struct Stmt_Var* statement_var);
#endif
