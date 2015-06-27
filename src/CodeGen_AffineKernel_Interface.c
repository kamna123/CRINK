#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
//#include "cuda_y.h"
#include "CodeGen_AffineKernel_Interface.h"
#include "CodeGen_CycleShrinking.h"
#include "CodeGen_ExtendedCycleShrinking.h"

// Function for kernel declaration
void cuda_kernel_declaration_AFFINE(char *shrinking, struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,int count )
{
    if((DependencyExists=='y')&&(!strcmp(shrinking,"true_dependence")))
        TD_kernel_declaration_DEPENDENCY(stmt_var,loop_index_new,count);
    else if((DependencyExists=='y')&&((!strcmp(shrinking,"extShrinking1"))||(!strcmp(shrinking,"extShrinking2"))))
        ExtendedShrinking_kernel_declaration_DEPENDENCY(stmt_var,loop_index_new,count);
    else if((DependencyExists=='y')&&((!strcmp(shrinking,"simple"))||(!strcmp(shrinking,"selective"))))
        SimpleSelective_kernel_declaration_DEPENDENCY(stmt_var,loop_index_new,count);
    else
        cuda_kernel_declaration_NO_DEPENDENCY(stmt_var,loop_index_new,count);
}

void cuda_kernel_call_AFFINE(char *shrinking,struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct Stmt_Var* write_stmt_var,int count)
{
    if(DependencyExists=='n') 
        cuda_kernel_call_NO_DEPENDENCY(stmt_var,loop_index_new,write_stmt_var,count);
    else if(!strcmp(shrinking,"simple"))
	    simple_loop_shrinking_AFFINE(stmt_var,loop_index_new,write_stmt_var,count);
	else if(!strcmp(shrinking,"selective"))
	    complex_loop_shrinking_AFFINE(stmt_var,loop_index_new,write_stmt_var,count);
    else if(!strcmp(shrinking,"true_dependence"))
	    true_dependence_shrinking_AFFINE(stmt_var,loop_index_new,write_stmt_var,count);
	else if(!strcmp(shrinking,"extShrinking1"))
	   extCS_ConstantDistance_AFFINE(stmt_var,loop_index_new,write_stmt_var,count);
	else 
	    extCS_VariableDistance_AFFINE(stmt_var,loop_index_new,write_stmt_var,count);
}	    

//Function for kernel definition
void cuda_kernel_definition_AFFINE(char *shrinking_type,struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new, struct StatementNode* parallel_stmt,int count)
{
    if(DependencyExists=='n')
        cuda_kernel_definition_NO_DEPENDENCY(stmt_var,loop_index_new,parallel_stmt,count);
    else if(!strcmp(shrinking_type,"true_dependence"))
        TD_kernel_definition_DEPENDENCY(stmt_var,loop_index_new,parallel_stmt,count);
    else if((!strcmp(shrinking_type,"simple"))||(!strcmp(shrinking_type,"selective")))
        SimpleSelective_kernel_definition_DEPENDENCY(shrinking_type,stmt_var,loop_index_new,parallel_stmt,count);
    else if((!strcmp(shrinking_type,"extShrinking1"))||(!strcmp(shrinking_type,"extShrinking2")))
        ExtendedShrinking_kernel_definition_DEPENDENCY(stmt_var,loop_index_new,parallel_stmt,count);
}
