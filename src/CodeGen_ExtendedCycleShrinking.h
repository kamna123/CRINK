#ifndef CODEGEN_EXTENDED_CS
#define CODEGEN_EXTENDED_CS
#include "cuda_y.h"
void ExtendedShrinking_kernel_declaration_DEPENDENCY(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,int count );
void extCS_ConstantDistance_AFFINE(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct Stmt_Var* write_stmt_var,int count);
void extCS_VariableDistance_AFFINE(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct Stmt_Var* write_stmt_var,int count);
void ExtendedShrinking_kernel_definition_DEPENDENCY(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new, struct StatementNode* parallel_stmt,int count);
#endif
