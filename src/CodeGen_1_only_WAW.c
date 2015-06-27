/************************************************
* ANJANA SINGH
* Y8127079
* DEPARTMENT OF COMPUTER SCIENCE AND ENGINNERING
* IIT KANPUR

* CUDA AUTOMATIC CODE GENRATION
* OLD METHOD: DEP CALCULATION INSIDE WHILE LOOP [WAW,WAR,RAW]
* WAW : NOT WORKING YET
* WORKING
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> 
#include <string.h>
//#include "cuda_y.h"
#include "CodeGen_1_only_WAW.h"
#include "fdisplay_2.h"
void cuda_function(struct StatementNode* read_var,struct Stmt_Var* left_stmt_var,struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct StatementNode* parallel_stmt,int count){
	if(read_var!=NULL) { 
		cuda_parallel_2(read_var,left_stmt_var,stmt_var,loop_index_new,parallel_stmt,count);	
		return;
	}
	int i = 0;
	struct Stmt_Var *stmt_temp;
	stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL) {
		if(stmt_temp->var->identifier->size!=NULL) {
			i++;
		}
		stmt_temp = stmt_temp->next;
	}
	if(i==1) cuda_parallel_1(read_var,left_stmt_var,stmt_var,loop_index_new,parallel_stmt,count);
	else cuda_parallel_2(read_var,left_stmt_var,stmt_var,loop_index_new,parallel_stmt,count);
}

void cuda_function_DEF(struct StatementNode* read_var,struct Stmt_Var* left_stmt_var,struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,int count){
	if(read_var!=NULL) { 
		cuda_function_DEF_2( stmt_var, loop_index_new,count);	
		return;
	}
	int i = 0;
	struct Stmt_Var *stmt_temp;
	stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL) {
		if(stmt_temp->var->identifier->size!=NULL) {
			i++;
		}
		stmt_temp = stmt_temp->next;
	}
	if(i==1) cuda_function_DEF_1(stmt_var, loop_index_new,count);
	else cuda_function_DEF_2(stmt_var, loop_index_new,count);
}

void cuda_loop(struct StatementNode* read_var,struct Stmt_Var* left_stmt_var,struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct StatementNode* left_var,struct Stmt_Var* read_stmt_var,struct StatementNode* write_var,int count  ){
	  id_max=0;
          if(read_var!=NULL) { 
	cuda_loop_2(read_var,left_stmt_var,stmt_var,loop_index_new,left_var,read_stmt_var,write_var,id_max,count);	
		return;
      
	}
	int i = 0;
	struct Stmt_Var *stmt_temp;
	stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL) {
		if(stmt_temp->var->identifier->size!=NULL) {
			i++;
		}
		stmt_temp = stmt_temp->next;
	}
	if(i==1) cuda_loop_1(read_var,left_stmt_var,stmt_var,loop_index_new,left_var,read_stmt_var,write_var,count);
	else cuda_loop_2(read_var,left_stmt_var,stmt_var,loop_index_new,left_var,read_stmt_var,write_var,id_max,count);
}

void cuda_function_DEF_2(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,int count){
	struct Stmt_Var* stmt_var_temp, *stmt_temp;
	//struct StatementNode* left_var_temp, *var_temp;
	//struct StatementNode* read_var_temp;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New* loop_index_temp;
	struct SizeNode* sz;
	int x,i;
	fprintf(out, "#define _NTHREAD 512\n#define _NBLOCK 65535\n\n");
	fprintf(out, "__global__ void _CUDA_PARALLEL_FUNCTION_%d(",count);
	stmt_var_temp = stmt_var;
	while(stmt_var_temp!=NULL){
		fdisplay_type(stmt_var_temp->var->type);
		if(stmt_var_temp->var->identifier->size!=NULL) fprintf(out, "*");
		fprintf(out, " ");
		fprintf(out, ",");
		if(stmt_var_temp->var->identifier->size!=NULL && stmt_var_temp->var->identifier->size->next!=NULL ) {
			sz = stmt_var_temp->var->identifier->size;
			x = 0;
			while(sz!=NULL){
				x++;
				sz = sz->next;
			}
			for(i=x;i>0;i--){
				fprintf(out, "int ");
				//fprintf(out, "_SZ_%s_%d,",stmt_var_temp->var->identifier->string,i);
			}
		}
		stmt_var_temp = stmt_var_temp->next;
	}
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		if(strcmp(loop_index_temp->L->string,"0")!=0 || loop_index_temp->L->next!=NULL) {
			fprintf(out, "int "); // print lower limit if it not 0
			//fdisplay_lowerLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, ",");
		}
		if(loop_index_new!=NULL){
			fprintf(out, "int "); //print upper limit if loop index variable exists
			//fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, ",");
		}
		if(strcmp(loop_index_temp->D->string,"1")!=0 || loop_index_temp->D->next!=NULL) {
			fprintf(out, "int "); //if index is incremented by num other than 1 than print that num
			//fdisplay_differenceId(loop_index_temp->loopIndex->string);
			fprintf(out, ",");
		}
		loop_index_temp = loop_index_temp->next;
	}
	/***************/
	/*stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL){
		fprintf(out, "int*,");
		stmt_temp = stmt_temp->next;
	}
	stmt_temp = read_stmt_var;
	while(stmt_temp!=NULL){
		fprintf(out, "int*,");
		stmt_temp = stmt_temp->next;
	}*/
	fprintf(out, "int*, int, ");   //for int* _INDEX , int _CUDA_ITER
	
	//Some more variable if needed
	fprintf(out, "int");           //for int _CUDA_TILE
	fprintf(out, ");\n");
	
}

void cuda_function_DEF_1(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,int count){
	struct Stmt_Var* stmt_var_temp, *stmt_temp;
	//struct StatementNode* left_var_temp, *var_temp;
	//struct StatementNode* read_var_temp;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New* loop_index_temp;
	struct SizeNode* sz;
	int x,i;
	fprintf(out, "#define _NTHREAD 512\n#define _NBLOCK 65535\n\n");
	fprintf(out, "__global__ void _CUDA_PARALLEL_FUNCTION_%d(",count);
	stmt_var_temp = stmt_var;
	while(stmt_var_temp!=NULL){
		fdisplay_type(stmt_var_temp->var->type);
		if(stmt_var_temp->var->identifier->size!=NULL) fprintf(out, "*");
		fprintf(out, " ");
		fprintf(out, ",");
		if(stmt_var_temp->var->identifier->size!=NULL && stmt_var_temp->var->identifier->size->next!=NULL ) {
			sz = stmt_var_temp->var->identifier->size;
			x = 0;
			while(sz!=NULL){
				x++;
				sz = sz->next;
			}
			for(i=x;i>0;i--){
				fprintf(out, "int ");
				//fprintf(out, "_SZ_%s_%d,",stmt_var_temp->var->identifier->string,i);
			}
		}
		stmt_var_temp = stmt_var_temp->next;
	}
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		if(strcmp(loop_index_temp->L->string,"0")!=0 || loop_index_temp->L->next!=NULL) {
			fprintf(out, "int ");
			//fdisplay_lowerLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, ",");
		}
		if(loop_index_new!=NULL){
			fprintf(out, "int ");
			//fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, ",");
		}
		if(strcmp(loop_index_temp->D->string,"1")!=0 || loop_index_temp->D->next!=NULL) {
			fprintf(out, "int ");
			//fdisplay_differenceId(loop_index_temp->loopIndex->string);
			fprintf(out, ",");
		}
		loop_index_temp = loop_index_temp->next;
	}
	/***************/
	fprintf(out, "int*,");
	fprintf(out, "int,");
	//Some more variable if needed
	fprintf(out, "int");
	fprintf(out, ");\n");

	
}




void cuda_parallel_2(struct StatementNode* read_var,struct Stmt_Var* left_stmt_var,struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct StatementNode* parallel_stmt,int count){
	struct Stmt_Var* stmt_var_temp, *stmt_temp;
	struct StatementNode* left_var_temp, *var_temp;
	struct StatementNode* read_var_temp;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New* loop_index_temp;
	struct SizeNode* sz;
	int x,i;
	//fprintf(out, "#define _NTHREAD 512\n#define _NBLOCK 65535\n\n");
	fprintf(out, "\n\n__global__ void _CUDA_PARALLEL_FUNCTION_%d(",count);
	stmt_var_temp = stmt_var;
	while(stmt_var_temp!=NULL){
		fdisplay_type(stmt_var_temp->var->type);
		if(stmt_var_temp->var->identifier->size!=NULL) fprintf(out, "*");
		fprintf(out, " ");
		fprintf(out, "%s,",stmt_var_temp->var->identifier->string);
		if(stmt_var_temp->var->identifier->size!=NULL && stmt_var_temp->var->identifier->size->next!=NULL ) {
			sz = stmt_var_temp->var->identifier->size;
			x = 0;
			while(sz!=NULL){
				x++;
				sz = sz->next;
			}
			for(i=x;i>0;i--){
				fprintf(out, "int ");
				fprintf(out, "_SZ_%s_%d,",stmt_var_temp->var->identifier->string,count);
			}
		}
		stmt_var_temp = stmt_var_temp->next;
	}
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		if(strcmp(loop_index_temp->L->string,"0")!=0 || loop_index_temp->L->next!=NULL) {
			fprintf(out, "int ");
			fdisplay_lowerLimitId(loop_index_temp->loopIndex->string);
                         fprintf(out,"_%d",count);
			fprintf(out, ",");
		}
		if(loop_index_new!=NULL){
			fprintf(out, "int ");
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
                         fprintf(out,"_%d",count);
			fprintf(out, ",");
		}
		if(strcmp(loop_index_temp->D->string,"1")!=0 || loop_index_temp->D->next!=NULL) {
			fprintf(out, "int ");
			fdisplay_differenceId(loop_index_temp->loopIndex->string);
                         fprintf(out,"_%d",count);
			fprintf(out, ",");
		}
		loop_index_temp = loop_index_temp->next;
	}
	/***************/
	/*stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL){
		fprintf(out, "int* _INDEX_w_%s,",stmt_temp->var->identifier->string);
		stmt_temp = stmt_temp->next;
	}
	stmt_temp = read_stmt_var;
	while(stmt_temp!=NULL){
		fprintf(out, "int* _INDEX_r_%s,",stmt_temp->var->identifier->string);
		stmt_temp = stmt_temp->next;
	}*/
	fprintf(out, "int* _INDEX_%d, int _CUDA_ITER_%d, ",count,count);
	
	//Some more variable if needed
	fprintf(out, "int _CUDA_TILE_%d",count);
	fprintf(out, "){\n");
	fprintf(out, "_CUDA_TILE_%d = gridDim.x*blockDim.x*_CUDA_TILE_%d + blockDim.x*blockIdx.x + threadIdx.x;\n",count,count);
	if(loop_index_new!=NULL){
		fprintf(out, "int %s = _CUDA_TILE_%d;\n",loop_index_new->loopIndex->string,count);
		fdisplay_find_loopId(loop_index_new->next);
		fdisplay_update_loopId(loop_index_new);
		fprintf(out, "if(%s<_CUDA_U_%s_%d)\n",loop_index_new->loopIndex->string,loop_index_new->loopIndex->string,count);
	}
	
	fprintf(out, "if(_INDEX_%d[_CUDA_TILE_%d] == _CUDA_ITER_%d)\n",count,count,count);	
	
	fprintf(out, "{\n");
	fdisplay_StatementNode_1D(parallel_stmt);

	fprintf(out, "}\n");

	fprintf(out, "}\n");
}



void cuda_parallel_1(struct StatementNode* read_var,struct Stmt_Var* left_stmt_var,struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct StatementNode* parallel_stmt,int count){
	struct Stmt_Var* stmt_var_temp, *stmt_temp;
	struct StatementNode* left_var_temp, *var_temp;
	struct StatementNode* read_var_temp;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New* loop_index_temp;
	struct SizeNode* sz;
	int x,i;
	//fprintf(out, "#define _NTHREAD 512\n#define _NBLOCK 65535\n\n");
	fprintf(out, "\n\n__global__ void _CUDA_PARALLEL_FUNCTION_%d(",count);
	stmt_var_temp = stmt_var;
	while(stmt_var_temp!=NULL){
		fdisplay_type(stmt_var_temp->var->type);
		if(stmt_var_temp->var->identifier->size!=NULL) fprintf(out, "*");
		fprintf(out, " ");
		fprintf(out, "%s,",stmt_var_temp->var->identifier->string);
		if(stmt_var_temp->var->identifier->size!=NULL && stmt_var_temp->var->identifier->size->next!=NULL ) {
			sz = stmt_var_temp->var->identifier->size;
			x = 0;
			while(sz!=NULL){
				x++;
				sz = sz->next;
			}
			for(i=x;i>0;i--){
				fprintf(out, "int ");
				fprintf(out, "_SZ_%s_%d,",stmt_var_temp->var->identifier->string,count);
			}
		}
		stmt_var_temp = stmt_var_temp->next;
	}
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		if(strcmp(loop_index_temp->L->string,"0")!=0 || loop_index_temp->L->next!=NULL) {
			fprintf(out, "int ");
			fdisplay_lowerLimitId(loop_index_temp->loopIndex->string);
                         fprintf(out,"_%d",count);
			fprintf(out, ",");
		}
		if(loop_index_new!=NULL){
			fprintf(out, "int ");
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
                         fprintf(out,"_%d",count);
			fprintf(out, ",");
		}
		if(strcmp(loop_index_temp->D->string,"1")!=0 || loop_index_temp->D->next!=NULL) {
			fprintf(out, "int ");
			fdisplay_differenceId(loop_index_temp->loopIndex->string);
                         fprintf(out,"_%d",count);
			fprintf(out, ",");
		}
		loop_index_temp = loop_index_temp->next;
	}
	/***************/
	
	fprintf(out, "int* _INDEX_%d, int _SZ_INDEX_%d,",count,count);
	//Some more variable if needed
	fprintf(out, "int _CUDA_TILE_%d",count);
	fprintf(out, "){\n");
	fprintf(out, "_CUDA_TILE_%d = gridDim.x*blockDim.x*_CUDA_TILE_%d + blockDim.x*blockIdx.x + threadIdx.x;\n",count,count);
	fprintf(out, "if(_CUDA_TILE_%d >= _SZ_INDEX_%d) return;\n",count,count);
	fprintf(out, "int %s = _INDEX_%d[_CUDA_TILE_%d];\n",loop_index_new->loopIndex->string,count,count);
	if(loop_index_new!=NULL){
		fdisplay_find_loopId(loop_index_new->next);
		fdisplay_update_loopId(loop_index_new);
	}	
	
	fdisplay_StatementNode_1D(parallel_stmt);
	fprintf(out, "}\n\n");
	
}


void cuda_loop_1(struct StatementNode* read_var,struct Stmt_Var* left_stmt_var,struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct StatementNode* left_var,struct Stmt_Var* read_stmt_var,struct StatementNode* write_var,int count ){
	struct Stmt_Var* stmt_var_temp;
	struct StatementNode* var_temp;
	struct Stmt_Var* stmt_temp;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New* loop_index_temp, *loop_temp;
	struct SizeNode* sz;
	int i,x,j;
	//loop indices boundaries
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		if(strcmp(loop_index_temp->L->string,"0")!=0 || loop_index_temp->L->next!=NULL) {
			fprintf(out, "int ");
			fdisplay_lowerLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, " = ");
			fdisplay_StringNode(loop_index_temp->L);
			fprintf(out, ";\n");
		}
		if(strcmp(loop_index_temp->D->string,"1")!=0 || loop_index_temp->D->next!=NULL) {
			fprintf(out, "int ");
			fdisplay_differenceId(loop_index_temp->loopIndex->string);
			fprintf(out, " = ");
			fdisplay_StringNode(loop_index_temp->D);
			fprintf(out, ";\n");
		}
		fprintf(out, "int ");
		fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
		fprintf(out, " = ");
		fdisplay_StringNode(loop_index_temp->U);
		fprintf(out, ";\n");
		
		if(loop_index_temp->op=='+' && (strcmp(loop_index_temp->L->string,"0")!=0 || loop_index_temp->L->next!=NULL)) {
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, " = ");
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, "-");
			fdisplay_lowerLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, ";\n");
		}
		if(loop_index_temp->op=='-' && (strcmp(loop_index_temp->L->string,"0")!=0 || loop_index_temp->L->next!=NULL)) {
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, " = ");
			fdisplay_lowerLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, "-");
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, ";\n");
		}
		else if (loop_index_temp->op=='-'){
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, " = 0 - ");
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, ";\n");
		}
		if(loop_index_temp->relop==1 && (strcmp(loop_index_temp->D->string,"1")!=0 || loop_index_temp->D->next!=NULL)) {
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, "--;\n");
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, " /= ");
			fdisplay_differenceId(loop_index_temp->loopIndex->string);
			fprintf(out, ";\n");
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, "++;\n");
		}
		if(loop_index_temp->relop==2 && (strcmp(loop_index_temp->D->string,"1")!=0 || loop_index_temp->D->next!=NULL)) {
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, " /= ");
			fdisplay_differenceId(loop_index_temp->loopIndex->string);
			fprintf(out, ";\n");
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, "++;\n");
		}
		else if(loop_index_temp->relop==2 ){
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, "++;\n");
		}
		loop_index_temp = loop_index_temp->next;
	}
	
	//CUDA ARRAY SIZE DECLARATIONS
	stmt_temp = stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--){
			fprintf(out, "int ");
			fprintf(out, "_SZ_%s_%d = ",stmt_temp->var->identifier->string,count);
			fdisplay_StringNode(stmt_temp->var->identifier->size->sizeString);
			fprintf(out, ";\n");
		}
		if(id_max<x) id_max=x;
		printMessage(8, "id_max: %d\n",id_max);
		stmt_temp = stmt_temp->next;
	}
	//CUDA NEW LOOP INDICES FOR ARRAYS: DECLARATIONS
	for(i=1;i<=id_max;i++){
		fprintf(out, "int _ID_%d_%d;\n",i,count);
	}
	
	//CUDA new variables:
	stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out, "int _INDEX_%d",count);
		fdisplay_StringNode(stmt_temp->var->identifier);
               
		fprintf(out, ";\n");
		stmt_temp = stmt_temp->next;
	}
	//_INDEX_VAR INITIALIZATION
	stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--){
			fprintf(out, "\nfor(_ID_%d_%d=0; _ID_%d_%d<_SZ_%s_%d; _ID_%d_%d++)",i,count,i,count,stmt_temp->var->identifier->string,count,i,count);
		}
		fprintf(out, "{\n_INDEX_%s_%d",stmt_temp->var->identifier->string,count);
		for(i=x;i>0;i--){
			fprintf(out, "[_ID_%d_%d]",i,count);
		}
		fprintf(out, " = 0;\n}\n");
		stmt_temp = stmt_temp->next;
	}
	
	// _INDEX_VAR CALCULATION
	
	
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		fprintf(out, "for(%s=0; %s<_CUDA_U_%s_%d; %s++)\n",loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string,count,loop_index_temp->loopIndex->string);
		loop_index_temp = loop_index_temp->next;
	}
	var_temp = left_var;
	while(var_temp!=NULL){
		if(var_temp->stringNode->size==NULL) {
			var_temp = var_temp->next;
			continue;
		}		
		fprintf(out, "_INDEX_%s_%d",var_temp->stringNode->string,count);
		fdisplay_SizeNode_updated_loop_index(var_temp->stringNode->size,loop_index_new);
		fprintf(out, " = 1;\n");
		var_temp = var_temp->next;
	}	
	
	
	// _INDEX_VAR RE-CALCULATION
	stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL) {
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--){
			fprintf(out, "for(_ID_%d_%d=0; _ID_%d_%d<_SZ_%s_%d; _ID_%d_%d++){\n",i,count,i,count,stmt_temp->var->identifier->string,count,i,count);
				fprintf(out, "if(_ID_%d_%d!=0)\n",i,count);
				fprintf(out, "_INDEX_%s_%d",stmt_temp->var->identifier->string,count);
				for(j=x;j>0;j--){
					if(j>=i) fprintf(out, "[_ID_%d_%d]",j,count);
					else fprintf(out, "[0]");
				}
				fprintf(out, " += _INDEX_%s_%d",stmt_temp->var->identifier->string,count);
				for(j=x;j>0;j--){
					if(j>i) fprintf(out, "[_ID_%d_%d]",j,count);
					else if(j==i) fprintf(out, "[_ID_%d_%d - 1]",j,count);
					else fprintf(out, "[_SZ_%s_%d - 1]",stmt_temp->var->identifier->string,count);
				}
				fprintf(out, ";\n");
		}
		for(i=x;i>0;i--)
			fprintf(out, "}\n");
		stmt_temp = stmt_temp->next;
	}
	//DECLARE _INDEX 
	stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL) {
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out, "int _INDEX_%d",count);
		fprintf(out, "[_INDEX_%s_%d",stmt_temp->var->identifier->string,count);
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--)
			fprintf(out, "[_SZ_%s_%d - 1]",stmt_temp->var->identifier->string,count);
		fprintf(out, "];\n");
		stmt_temp = stmt_temp->next;
	}
	
	
	var_temp = left_var;
	while(var_temp!=NULL){
		if(var_temp->stringNode->size==NULL) {
			var_temp = var_temp->next;
			continue;
		}
		loop_index_temp = loop_index_new;
		while(loop_index_temp!=NULL){
			fprintf(out, "for(%s=0; %s<_CUDA_U_%s_%d; %s++)\n",loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string,count,loop_index_temp->loopIndex->string);
			loop_index_temp = loop_index_temp->next;
		}
		fprintf(out, "_INDEX_%d[_INDEX_%s_%d",count,var_temp->stringNode->string,count);
		fdisplay_SizeNode_updated_loop_index(var_temp->stringNode->size,loop_index_new);
		fprintf(out, " - 1] = ");
		loop_index_temp = loop_index_new;
		while(loop_index_temp!=NULL){
			fprintf(out, "%s",loop_index_temp->loopIndex->string);
			loop_temp = loop_index_temp->next;
			while(loop_temp!=NULL){
				fprintf(out, "*_CUDA_U_%s_%d",loop_temp->loopIndex->string,count);
				loop_temp = loop_temp->next;
			}
			loop_index_temp = loop_index_temp->next;
			if(loop_index_temp!=NULL) fprintf(out, "+");
		}
		fprintf(out, ";\n");
		var_temp = var_temp->next;
	}
	
	// DEVELOPER VARIABLEs
	stmt_temp = stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fdisplay_type(stmt_temp->var->type);
		fprintf(out, " *_DEV_%s_%d;\n",stmt_temp->var->identifier->string,count);
		fprintf(out, "cudaMalloc((void**) &_DEV_%s_%d, sizeof(",stmt_temp->var->identifier->string,count);
		fdisplay_type(stmt_temp->var->type);
		fprintf(out, ")");
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--){
			fprintf(out, "*_SZ_%s_%d",stmt_temp->var->identifier->string,count);
		}
		fprintf(out, ");\n");
		
		fprintf(out, "cudaMemcpy(_DEV_%s_%d, %s, sizeof(",stmt_temp->var->identifier->string,count,stmt_temp->var->identifier->string);
		fdisplay_type(stmt_temp->var->type);
		fprintf(out, ")");
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--){
			fprintf(out, "*_SZ_%s_%d",stmt_temp->var->identifier->string,count);
		}
		fprintf(out, ", cudaMemcpyHostToDevice);\n");
		stmt_temp = stmt_temp->next;
	}
	stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out, "int *_DEV_INDEX_%d;\n",count);
		fprintf(out, "cudaMalloc((void**) &_DEV_INDEX_%d, sizeof(int)",count);
		fprintf(out, "*_INDEX_%s_%d",stmt_temp->var->identifier->string,count);
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--)
			fprintf(out, "[_SZ_%s_%d - 1]",stmt_temp->var->identifier->string,count);
		fprintf(out, ");\n");
		
		fprintf(out, "cudaMemcpy(_DEV_INDEX_%d, _INDEX_%d, sizeof(int)",count,count);
		fprintf(out, "*_INDEX_%s_%d",stmt_temp->var->identifier->string,count);
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--)
			fprintf(out, "[_SZ_%s_%d - 1]",stmt_temp->var->identifier->string,count);
		fprintf(out, ", cudaMemcpyHostToDevice);\n");
		stmt_temp = stmt_temp->next;
	}
	
	
	
	
	
	
	stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL) {
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out, "int _NUM_THREADS_%d = _INDEX_%s_%d",count,stmt_temp->var->identifier->string,count);
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--)
			fprintf(out, "[_SZ_%s_%d - 1]",stmt_temp->var->identifier->string,count);
		stmt_temp = stmt_temp->next;
	}
	fprintf(out, ";\nint _THREADS_%d=1, _BLOCKS_%d=1, _NUM_TILE_%d=1;\n",count,count,count);
	fprintf(out, "_THREADS_%d = (_NUM_THREADS_%d<=_NTHREAD) ? _NUM_THREADS_%d : _NTHREAD;\n",count,count,count);
	fprintf(out, "_NUM_THREADS_%d = ((_NUM_THREADS_%d-1)/_THREADS_%d)+1;\n",count,count,count);
	fprintf(out, "_BLOCKS_%d = (_NUM_THREADS_%d<=_NBLOCK) ? _NUM_THREADS_%d : _NBLOCK;\n",count,count,count);
	fprintf(out, "_NUM_THREADS_%d = ((_NUM_THREADS_%d-1)/_BLOCKS_%d)+1;\n",count,count,count);
	fprintf(out, "_NUM_TILE_%d = _NUM_THREADS_%d;\n",count,count);
	fprintf(out, "int _CUDA_TILE_%d;\n",count);



	fprintf(out, "for(_CUDA_TILE_%d=0;_CUDA_TILE_%d<_NUM_TILE_%d;_CUDA_TILE_%d++)\n",count,count,count,count);
	fprintf(out, "_CUDA_PARALLEL_FUNCTION%d<<<_BLOCKS_%d,_THREADS_%d>>>(",count,count,count);
	/******************************/
	stmt_var_temp = stmt_var;
	while(stmt_var_temp!=NULL){
		if(stmt_var_temp->var->identifier->size!=NULL) fprintf(out, "_DEV_");
		fprintf(out, "%s_%d, ",stmt_var_temp->var->identifier->string,count);
		if(stmt_var_temp->var->identifier->size!=NULL && stmt_var_temp->var->identifier->size->next!=NULL ) {
			sz = stmt_var_temp->var->identifier->size;
			x = 0;
			while(sz!=NULL){
				x++;
				sz = sz->next;
			}
			for(i=x;i>0;i--){
				fprintf(out, "_SZ_%s_%d, ",stmt_var_temp->var->identifier->string,count);
			}
		}
		stmt_var_temp = stmt_var_temp->next;
	}
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		if(strcmp(loop_index_temp->L->string,"0")!=0 || loop_index_temp->L->next!=NULL) {
			fdisplay_lowerLimitId(loop_index_temp->loopIndex->string);
                        fprintf(out,"_%d",count);
			fprintf(out, ", ");
		}
		if(loop_index_new!=NULL){
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
                        fprintf(out,"_%d",count);
			fprintf(out, ", ");
		}
		if(strcmp(loop_index_temp->D->string,"1")!=0 || loop_index_temp->D->next!=NULL) {
			fdisplay_differenceId(loop_index_temp->loopIndex->string);
                        fprintf(out,"_%d",count);
			fprintf(out, ", ");
		}
		loop_index_temp = loop_index_temp->next;
	}
	/***************/
	fprintf(out, "_DEV_INDEX_%d, ",count);
	stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL) {
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out, " _INDEX_%s_%d",stmt_temp->var->identifier->string,count);
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--)
			fprintf(out, "[_SZ_%s_%d - 1]",stmt_temp->var->identifier->string,count);
		fprintf(out, ",");
		stmt_temp = stmt_temp->next;
	}
	//Some more variable if needed
	fprintf(out, "_CUDA_TILE_%d",count);
	fprintf(out, ");\n");
	fprintf(out, "cudaDeviceSynchronize();\n");
	stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out, "cudaMemcpy(%s, _DEV_%s_%d, sizeof(",stmt_temp->var->identifier->string,stmt_temp->var->identifier->string,count);
		fdisplay_type(stmt_temp->var->type);
		fprintf(out, ")");
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--){
			fprintf(out, "*_SZ_%s_%d",stmt_temp->var->identifier->string,count);
		}
		fprintf(out, ", cudaMemcpyDeviceToHost);\n");
		stmt_temp = stmt_temp->next;
	}
	
	
	
	
	
		


}
void cuda_loop_2(struct StatementNode* read_var,struct Stmt_Var* left_stmt_var,struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct StatementNode* left_var,struct Stmt_Var* read_stmt_var,struct StatementNode* write_var,int id_max,int count ){	
	struct Stmt_Var* stmt_var_temp;
	struct StatementNode* var_temp;
	struct Stmt_Var* stmt_temp;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New* loop_index_temp, *loop_temp;
	struct SizeNode* sz;
	int i,x=0;
	//loop indices boundaries: normalization
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		if(strcmp(loop_index_temp->L->string,"0")!=0 || loop_index_temp->L->next!=NULL) {
			fprintf(out, "int ");
			fdisplay_lowerLimitId(loop_index_temp->loopIndex->string);
                         fprintf(out,"_%d",count);
			fprintf(out, " = ");
			fdisplay_StringNode(loop_index_temp->L);
                       
			fprintf(out, ";\n");
		}
		if(strcmp(loop_index_temp->D->string,"1")!=0 || loop_index_temp->D->next!=NULL) {
			fprintf(out, "int ");
			fdisplay_differenceId(loop_index_temp->loopIndex->string);
			fprintf(out, " = ");
                        fprintf(out,"_%d",count);
			fdisplay_StringNode(loop_index_temp->D);
                        
			fprintf(out, ";\n");
		}
		fprintf(out, "int ");
		fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
                fprintf(out,"_%d",count);
		fprintf(out, " = ");
                 
		fdisplay_StringNode(loop_index_temp->U);
                
		fprintf(out, ";\n");
		
		if(loop_index_temp->op=='+' && (strcmp(loop_index_temp->L->string,"0")!=0 || loop_index_temp->L->next!=NULL)) {
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, " = ");
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, "-");
			fdisplay_lowerLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, ";\n");
		}
		if(loop_index_temp->op=='-' && (strcmp(loop_index_temp->L->string,"0")!=0 || loop_index_temp->L->next!=NULL)) {
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, " = ");
			fdisplay_lowerLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, "-");
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, ";\n");
		}
		else if (loop_index_temp->op=='-'){
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, " = 0 - ");
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, ";\n");
		}
		if(loop_index_temp->relop==1 && (strcmp(loop_index_temp->D->string,"1")!=0 || loop_index_temp->D->next!=NULL)) {
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, "--;\n");
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, " /= ");
			fdisplay_differenceId(loop_index_temp->loopIndex->string);
			fprintf(out, ";\n");
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, "++;\n");
		}
		if(loop_index_temp->relop==2 && (strcmp(loop_index_temp->D->string,"1")!=0 || loop_index_temp->D->next!=NULL)) {
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, " /= ");
			fdisplay_differenceId(loop_index_temp->loopIndex->string);
			fprintf(out, ";\n");
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, "++;\n");
		}
		else if(loop_index_temp->relop==2 ){
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
			fprintf(out, "++;\n");
		}
		loop_index_temp = loop_index_temp->next;
	}
	
	//CUDA ARRAY SIZE DECLARATIONS
	stmt_temp = stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--){
			fprintf(out, "int ");
			fprintf(out, "_SZ_%s_%d = ",stmt_temp->var->identifier->string,count);
			fdisplay_StringNode(stmt_temp->var->identifier->size->sizeString);
			fprintf(out, ";\n");
		}
               
		if(id_max<x) 
                  id_max=x;
                 
		printMessage(8, "id_max: %d\n",id_max);
		stmt_temp = stmt_temp->next;
	}
	
	//CUDA NEW LOOP INDICES FOR ARRAYS: DECLARATIONS
	for(i=1;i<=id_max;i++){
		fprintf(out, "int _ID_%d_%d;\n",i,count);
	}
	
	//FLAG DECLARATION
	/*fprintf(out, "int _FLAG;\n");
	*/
	
	//CUDA new variables:
	fprintf(out, "int _ITERATIONS_%d=0;\n",count);
         
	stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out, "int _INDEX_w_");
                 fprintf(out,"%d_",count);
		fdisplay_StringNode(stmt_temp->var->identifier);
               
		fprintf(out, ";\n");
		stmt_temp = stmt_temp->next;
	}
	stmt_temp = read_stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out, "int _INDEX_r_%d_",count);
		fdisplay_StringNode(stmt_temp->var->identifier);
		fprintf(out, ";\n");
		stmt_temp = stmt_temp->next;
	}
	
	//INDEX DECLARATION
	fprintf(out, "int _INDEX_%d",count);
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		fprintf(out, "[");
		fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
                fprintf(out,"_%d",count);
		fprintf(out, "]");
		loop_index_temp = loop_index_temp->next;
	}
	fprintf(out, ";\n");
	
	//INDEX_w and INDEX_r INITIALIZATION
	
	//INDICES INITIALIZATION
	stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--){
			fprintf(out, "\nfor(_ID_%d_%d=0; _ID_%d_%d<_SZ_%s_%d; _ID_%d_%d++)",i,count,i,count,stmt_temp->var->identifier->string,count,i,count);
		}
		fprintf(out, "{\n_INDEX_w_%d_%s",count,stmt_temp->var->identifier->string);
		for(i=x;i>0;i--){
			fprintf(out, "[_ID_%d_%d]",i,count);
		}
		loop_index_temp = loop_index_new;
		/*fprintf(out, " = _CUDA_U_%s",loop_index_temp->loopIndex->string);
		loop_index_temp = loop_index_temp->next;
		while(loop_index_temp!=NULL){
			fprintf(out, " * _CUDA_U_%s",loop_index_temp->loopIndex->string);
			loop_index_temp = loop_index_temp->next;
		}
		fprintf(out, ";\n_INDEX_r_%s",stmt_temp->var->identifier->string);
		for(i=x;i>0;i--){
			fprintf(out, "[_ID_%d]",i);
		}
		loop_index_temp = loop_index_new;
		fprintf(out, " = _CUDA_U_%s",loop_index_temp->loopIndex->string);
		loop_index_temp = loop_index_temp->next;
		while(loop_index_temp!=NULL){
			fprintf(out, " * _CUDA_U_%s",loop_index_temp->loopIndex->string);
			loop_index_temp = loop_index_temp->next;
		}*/
		fprintf(out, "= -1;\n}\n");
		stmt_temp = stmt_temp->next;
	}
	stmt_temp = read_stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--){
			fprintf(out, "\nfor(_ID_%d_%d=0; _ID_%d_%d<_SZ_%s_%d; _ID_%d_%d++)",i,count,i,count,stmt_temp->var->identifier->string,count,i,count);
		}
		fprintf(out, "{\n_INDEX_r_%d_%s",count,stmt_temp->var->identifier->string);
		for(i=x;i>0;i--){
			fprintf(out, "[_ID_%d_%d]",i,count);
		}
		loop_index_temp = loop_index_new;
		/*fprintf(out, " = _CUDA_U_%s",loop_index_temp->loopIndex->string);
		loop_index_temp = loop_index_temp->next;
		while(loop_index_temp!=NULL){
			fprintf(out, " * _CUDA_U_%s",loop_index_temp->loopIndex->string);
			loop_index_temp = loop_index_temp->next;
		}
		fprintf(out, ";\n_INDEX_r_%s",stmt_temp->var->identifier->string);
		for(i=x;i>0;i--){
			fprintf(out, "[_ID_%d]",i);
		}
		loop_index_temp = loop_index_new;
		fprintf(out, " = _CUDA_U_%s",loop_index_temp->loopIndex->string);
		loop_index_temp = loop_index_temp->next;
		while(loop_index_temp!=NULL){
			fprintf(out, " * _CUDA_U_%s",loop_index_temp->loopIndex->string);
			loop_index_temp = loop_index_temp->next;
		}*/
		fprintf(out, "= -1;\n}\n");
		stmt_temp = stmt_temp->next;
	}
	
	//INDEX CALCULATION
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		fprintf(out, "for(%s=0; %s<_CUDA_U_%s_%d; %s++)\n",loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string,count,loop_index_temp->loopIndex->string);
		loop_index_temp = loop_index_temp->next;
	}
	fprintf(out, "{\n_INDEX_%d",count);
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		fprintf(out, "[%s]",loop_index_temp->loopIndex->string);
		loop_index_temp = loop_index_temp->next;
	}
	fprintf(out, "=0;\n");
	
	var_temp = left_var;
	while(var_temp!=NULL){
		if(var_temp->stringNode->size==NULL) {
			var_temp = var_temp->next;
			continue;
		}
		fprintf(out, "if(_INDEX_w_%d_%s",count,var_temp->stringNode->string);
		fdisplay_SizeNode_updated_loop_index(var_temp->stringNode->size, loop_index_new);
		fprintf(out, "+1>");
		fprintf(out, "_INDEX_%d",count);
		loop_index_temp = loop_index_new;
		while(loop_index_temp!=NULL){
			fprintf(out, "[%s]",loop_index_temp->loopIndex->string);
			loop_index_temp = loop_index_temp->next;
		}
		fprintf(out, ") ");
		fprintf(out, "_INDEX_%d",count);
		loop_index_temp = loop_index_new;
		while(loop_index_temp!=NULL){
			fprintf(out, "[%s]",loop_index_temp->loopIndex->string);
			loop_index_temp = loop_index_temp->next;
		}
		fprintf(out, " = ");
		fprintf(out, "_INDEX_w_%d_%s",count,var_temp->stringNode->string);
		fdisplay_SizeNode_updated_loop_index(var_temp->stringNode->size,loop_index_new);
		fprintf(out, "+1;\n");
		var_temp = var_temp->next;
	}
	var_temp = read_var;
	while(var_temp!=NULL){
		if(var_temp->stringNode->size==NULL) {
			var_temp = var_temp->next;
			continue;
		}
		fprintf(out, "if(_INDEX_w_%d_%s",count,var_temp->stringNode->string);
		fdisplay_SizeNode_updated_loop_index(var_temp->stringNode->size,loop_index_new);
		fprintf(out, "+1>");
		fprintf(out, "_INDEX_%d",count);
		loop_index_temp = loop_index_new;
		while(loop_index_temp!=NULL){
			fprintf(out, "[%s]",loop_index_temp->loopIndex->string);
			loop_index_temp = loop_index_temp->next;
		}
		fprintf(out, ") ");
		fprintf(out, "_INDEX_%d",count);
		loop_index_temp = loop_index_new;
		while(loop_index_temp!=NULL){
			fprintf(out, "[%s]",loop_index_temp->loopIndex->string);
			loop_index_temp = loop_index_temp->next;
		}
		fprintf(out, " = ");
		fprintf(out, "_INDEX_w_%d_%s",count,var_temp->stringNode->string);
		fdisplay_SizeNode_updated_loop_index(var_temp->stringNode->size,loop_index_new);
		fprintf(out, "+1;\n");
		var_temp = var_temp->next;
	}
	var_temp = write_var;
	while(var_temp!=NULL){
		if(var_temp->stringNode->size==NULL) {
			var_temp = var_temp->next;
			continue;
		}
		fprintf(out, "if(_INDEX_r_%d_%s",count,var_temp->stringNode->string);
		fdisplay_SizeNode_updated_loop_index(var_temp->stringNode->size,loop_index_new);
		fprintf(out, "+1>");
		fprintf(out, "_INDEX_%d",count);
		loop_index_temp = loop_index_new;
		while(loop_index_temp!=NULL){
			fprintf(out, "[%s]",loop_index_temp->loopIndex->string);
			loop_index_temp = loop_index_temp->next;
		}
		fprintf(out, ") ");
		fprintf(out, "_INDEX_%d",count);
		loop_index_temp = loop_index_new;
		while(loop_index_temp!=NULL){
			fprintf(out, "[%s]",loop_index_temp->loopIndex->string);
			loop_index_temp = loop_index_temp->next;
		}
		fprintf(out, " = ");
		fprintf(out, "_INDEX_r_%d_%s",count,var_temp->stringNode->string);
		fdisplay_SizeNode_updated_loop_index(var_temp->stringNode->size,loop_index_new);
		fprintf(out, "+1;\n");
		var_temp = var_temp->next;
	}
	
	fprintf(out, "if(_ITERATIONS_%d<",count);
	fprintf(out, "_INDEX_%d",count);
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		fprintf(out, "[%s]",loop_index_temp->loopIndex->string);
		loop_index_temp = loop_index_temp->next;
	}
	fprintf(out, ") ");
	fprintf(out, "_ITERATIONS_%d = ",count);
	fprintf(out, "_INDEX_%d",count);
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		fprintf(out, "[%s]",loop_index_temp->loopIndex->string);
		loop_index_temp = loop_index_temp->next;
	}
	fprintf(out, ";\n");

	var_temp = left_var;
	while(var_temp!=NULL){
		if(var_temp->stringNode->size==NULL) {
			var_temp = var_temp->next;
			continue;
		}
		fprintf(out, "_INDEX_w_%d_%s",count,var_temp->stringNode->string);
		fdisplay_SizeNode_updated_loop_index(var_temp->stringNode->size,loop_index_new);
		fprintf(out, " = ");
		fprintf(out, "_INDEX_%d",count);
		loop_index_temp = loop_index_new;
		while(loop_index_temp!=NULL){
			fprintf(out, "[%s]",loop_index_temp->loopIndex->string);
			loop_index_temp = loop_index_temp->next;
		}
		fprintf(out, ";\n");
		var_temp = var_temp->next;
	}
	
	var_temp = read_var;
	while(var_temp!=NULL){
		if(var_temp->stringNode->size==NULL) {
			var_temp = var_temp->next;
			continue;
		}
		fprintf(out, "if(_INDEX_r_%d_%s",count,var_temp->stringNode->string);
		fdisplay_SizeNode_updated_loop_index(var_temp->stringNode->size,loop_index_new);
		fprintf(out, "<");
		fprintf(out, "_INDEX_%d",count);
		loop_index_temp = loop_index_new;
		while(loop_index_temp!=NULL){
			fprintf(out, "[%s]",loop_index_temp->loopIndex->string);
			loop_index_temp = loop_index_temp->next;
		}
		fprintf(out, ") ");
		fprintf(out, "_INDEX_r_%d_%s",count,var_temp->stringNode->string);
		fdisplay_SizeNode_updated_loop_index(var_temp->stringNode->size,loop_index_new);
		fprintf(out, " = ");
		fprintf(out, "_INDEX_%d",count);
		loop_index_temp = loop_index_new;
		while(loop_index_temp!=NULL){
			fprintf(out, "[%s]",loop_index_temp->loopIndex->string);
			loop_index_temp = loop_index_temp->next;
		}
		fprintf(out, ";\n");
		var_temp = var_temp->next;
	}
	fprintf(out, "}\n");
	fprintf(out, "_ITERATIONS_%d++;\n",count);
	
	//DEVELOPER VARABLES DECLARATIONS
	stmt_temp = stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fdisplay_type(stmt_temp->var->type);
		fprintf(out, " *_DEV_%s_%d;\n",stmt_temp->var->identifier->string,count);
		fprintf(out, "cudaMalloc((void**) &_DEV_%s_%d, sizeof(",stmt_temp->var->identifier->string,count);
		fdisplay_type(stmt_temp->var->type);
		fprintf(out, ")");
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--){
			fprintf(out, "*_SZ_%s_%d",stmt_temp->var->identifier->string,count);
		}
		fprintf(out, ");\n");
		
		fprintf(out, "cudaMemcpy(_DEV_%s_%d, %s, sizeof(",stmt_temp->var->identifier->string,count,stmt_temp->var->identifier->string);
		fdisplay_type(stmt_temp->var->type);
		fprintf(out, ")");
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--){
			fprintf(out, "*_SZ_%s_%d",stmt_temp->var->identifier->string,count);
		}
		fprintf(out, ", cudaMemcpyHostToDevice);\n");
		stmt_temp = stmt_temp->next;
	}
	/*stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL){
		fprintf(out, "int *_DEV_INDEX_w_%s;\n",stmt_temp->var->identifier->string);
		fprintf(out, "cudaMalloc((void**) &_DEV_INDEX_w_%s, sizeof(int)",stmt_temp->var->identifier->string);
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--){
			fprintf(out, "*_SZ_%s_%d",stmt_temp->var->identifier->string,i);
		}
		fprintf(out, ");\n");
		stmt_temp = stmt_temp->next;
	}
	stmt_temp = read_stmt_var;
	while(stmt_temp!=NULL){
		fprintf(out, "int *_DEV_INDEX_r_%s;\n",stmt_temp->var->identifier->string);
		fprintf(out, "cudaMalloc((void**) &_DEV_INDEX_r_%s, sizeof(int)",stmt_temp->var->identifier->string);
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--){
			fprintf(out, "*_SZ_%s_%d",stmt_temp->var->identifier->string,i);
		}
		fprintf(out, ");\n");
		stmt_temp = stmt_temp->next;
	}
	*/
	fprintf(out, "int *_DEV_INDEX_%d;\n",count);
	fprintf(out, "cudaMalloc((void**) &_DEV_INDEX_%d, sizeof(int)",count);
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		fprintf(out, "*_CUDA_U_%s_%d",loop_index_temp->loopIndex->string,count);
		loop_index_temp = loop_index_temp->next;
	}
	fprintf(out, ");\n");
	
	fprintf(out, "cudaMemcpy(_DEV_INDEX_%d, _INDEX_%d, sizeof(int)",count,count);
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		fprintf(out, "*_CUDA_U_%s_%d",loop_index_temp->loopIndex->string,count);
		loop_index_temp = loop_index_temp->next;
	}
	fprintf(out, ", cudaMemcpyHostToDevice);\n");
	fprintf(out, "int _NUM_THREADS_%d = ",count);
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		fprintf(out, "_CUDA_U_%s_%d",loop_index_temp->loopIndex->string,count);
		loop_index_temp = loop_index_temp->next;
		if(loop_index_temp!=NULL) fprintf(out, "*");
	}
	
	fprintf(out, ";\nint _THREADS_%d=1, _BLOCKS_%d=1, _NUM_TILE_%d=1;\n",count,count,count);
	fprintf(out, "_NUM_TILE_%d = (_NUM_THREADS_%d%%(_NTHREAD*_NBLOCK)==0) ? _NUM_THREADS_%d/(_NTHREAD*_NBLOCK) : (_NUM_THREADS_%d/(_NTHREAD*_NBLOCK))+1;\n",count,count,count,count);
	fprintf(out, "_NUM_THREADS_%d = (_NUM_THREADS_%d%%_NUM_TILE_%d==0) ? _NUM_THREADS_%d/_NUM_TILE_%d : (_NUM_THREADS_%d/_NUM_TILE_%d)+1;\n",count,count,count,count,count,count,count);
	fprintf(out, "_THREADS_%d = (_NUM_THREADS_%d<=_NTHREAD) ? _NUM_THREADS_%d : _NTHREAD;\n",count,count,count);
	fprintf(out, "_NUM_THREADS_%d = ((_NUM_THREADS_%d-1)/_THREADS_%d)+1;\n",count,count,count);
	fprintf(out, "_BLOCKS_%d = (_NUM_THREADS_%d<=_NBLOCK) ? _NUM_THREADS_%d : _NBLOCK;\n",count,count,count);
	fprintf(out, "_NUM_THREADS_%d = ((_NUM_THREADS_%d-1)/_BLOCKS_%d)+1;\n",count,count,count);
	
	fprintf(out, "int _CUDA_TILE_%d;\n",count);
	fprintf(out, "int _CUDA_ITER_%d;\n",count);

	fprintf(out, "for(_CUDA_ITER_%d=0;_CUDA_ITER_%d<_ITERATIONS_%d;_CUDA_ITER_%d++)\n",count,count,count,count);
	fprintf(out, "for(_CUDA_TILE_%d=0;_CUDA_TILE_%d<_NUM_TILE_%d;_CUDA_TILE_%d++)\n",count,count,count,count);
	fprintf(out, "_CUDA_PARALLEL_FUNCTION_%d<<<_BLOCKS_%d,_THREADS_%d>>>(",count,count,count);
	/******************************/
	stmt_var_temp = stmt_var;
	while(stmt_var_temp!=NULL){
		if(stmt_var_temp->var->identifier->size!=NULL) fprintf(out, "_DEV_");
		fprintf(out, "%s_%d, ",stmt_var_temp->var->identifier->string,count);
		if(stmt_var_temp->var->identifier->size!=NULL && stmt_var_temp->var->identifier->size->next!=NULL ) {
			sz = stmt_var_temp->var->identifier->size;
			x = 0;
			while(sz!=NULL){
				x++;
				sz = sz->next;
			}
			for(i=x;i>0;i--){
				fprintf(out, "_SZ_%s_%d, ",stmt_var_temp->var->identifier->string,count);
			}
		}
		stmt_var_temp = stmt_var_temp->next;
	}
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		if(strcmp(loop_index_temp->L->string,"0")!=0 || loop_index_temp->L->next!=NULL) {
			fdisplay_lowerLimitId(loop_index_temp->loopIndex->string);
                        fprintf(out,"_%d",count);
			fprintf(out, ", ");
		}
		if(loop_index_new!=NULL){
			fdisplay_upperLimitId(loop_index_temp->loopIndex->string);
                         fprintf(out,"_%d",count);
			fprintf(out, ", ");
		}
		if(strcmp(loop_index_temp->D->string,"1")!=0 || loop_index_temp->D->next!=NULL) {
			fdisplay_differenceId(loop_index_temp->loopIndex->string);
                         fprintf(out,"_%d",count);
			fprintf(out, ", ");
		}
		loop_index_temp = loop_index_temp->next;
	}
	/***************/
	/*stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL){
		fprintf(out, "_DEV_INDEX_w_%s, ",stmt_temp->var->identifier->string);
		stmt_temp = stmt_temp->next;
	}
	stmt_temp = read_stmt_var;
	while(stmt_temp!=NULL){
		fprintf(out, "_DEV_INDEX_r_%s, ",stmt_temp->var->identifier->string);
		stmt_temp = stmt_temp->next;
	}*/
	fprintf(out, "_DEV_INDEX_%d, _CUDA_ITER_%d, ",count,count);
	//Some more variable if needed
	fprintf(out, "_CUDA_TILE_%d",count);
	fprintf(out, ");\n");
	/********************************/
	fprintf(out, "cudaDeviceSynchronize();\n");
	/*fprintf(out, "cudaMemcpy(_DONE, _DEV_DONE, sizeof(int)");
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		fprintf(out, "*_CUDA_U_%s",loop_index_temp->loopIndex->string);
		loop_index_temp = loop_index_temp->next;
	}
	fprintf(out, ", cudaMemcpyDeviceToHost);\n");
	*/




	//fprintf(out, "}\n"); //WHILE CLOSE
	
	stmt_temp = left_stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out, "cudaMemcpy(%s, _DEV_%s_%d, sizeof(",stmt_temp->var->identifier->string,stmt_temp->var->identifier->string,count);
		fdisplay_type(stmt_temp->var->type);
		fprintf(out, ")");
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--){
			fprintf(out, "*_SZ_%s_%d",stmt_temp->var->identifier->string,count);
		}
		fprintf(out, ", cudaMemcpyDeviceToHost);\n");
		stmt_temp = stmt_temp->next;
	}
	

}


void cuda_postloop(struct LoopIndexVar_New* loop_index_new,int count){
	struct LoopIndexVar_New* liv;
	liv = loop_index_new;
	while(liv!=NULL){
		fdisplay_StringNode(liv->loopIndex);
		fprintf(out, " = ");
		if(strcmp(liv->L->string,"0")!=0 || liv->L->next!=NULL) {
			fdisplay_lowerLimitId(liv->loopIndex->string);
                      //   fprintf(out,"_%d",count);
			fprintf(out, " + ");
		}
               
		fdisplay_upperLimitId(liv->loopIndex->string);
		if(strcmp(liv->D->string,"1")!=0 || liv->D->next!=NULL) {
			fprintf(out, "*");
			fdisplay_differenceId(liv->loopIndex->string);
                        
		}
                 fprintf(out,"_%d",count);
		fprintf(out, ";\n");
		liv = liv->next;
	}

}



