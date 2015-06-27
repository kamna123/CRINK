#ifndef CODEGEN_AFFINE_KERNEL_INTERFACE
#define CODEGEN_AFFINE_KERNEL_INTERFACE
#include "cuda_y.h"
void cuda_kernel_declaration_AFFINE(char *shrinking, struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,int count);
void cuda_kernel_call_AFFINE(char *shrinking,struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct Stmt_Var* write_stmt_var,int count);
void cuda_kernel_definition_AFFINE(char *shrinking_type,struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct StatementNode* parallel_stmt,int count);
#endif
