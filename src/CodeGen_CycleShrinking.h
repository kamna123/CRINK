#ifndef CODEGEN_CYCLE_SHRINKING
#define CODEGEN_CYCLE_SHRINKING
#include "cuda_y.h"
void  SimpleSelective_kernel_declaration_DEPENDENCY( struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,int count);
void TD_kernel_declaration_DEPENDENCY( struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,int count);
void cuda_kernel_declaration_NO_DEPENDENCY( struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,int count);
void simple_loop_shrinking_AFFINE(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct Stmt_Var* write_stmt_var,int count);
void complex_loop_shrinking_AFFINE(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct Stmt_Var* write_stmt_var,int count);
void true_dependence_shrinking_AFFINE(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct Stmt_Var* write_stmt_var,int count);
void cuda_kernel_call_NO_DEPENDENCY(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct Stmt_Var* write_stmt_var,int count);
void SimpleSelective_kernel_definition_DEPENDENCY(char *shrinking_type,struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct StatementNode* parallel_stmt,int count);
void cuda_kernel_definition_NO_DEPENDENCY(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct StatementNode* parallel_stmt,int count);
void TD_kernel_definition_DEPENDENCY(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct StatementNode* parallel_stmt,int count);
#endif
