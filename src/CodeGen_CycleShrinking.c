#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
//#include "cuda_y.h"
#include "CodeGen_CycleShrinking.h"
#include "fdisplay_2.h"
/************************************** KERNEL DECLARATION CODE GENERATION ****************************************************/

//Function for kernel declaration if dependency exists
void  SimpleSelective_kernel_declaration_DEPENDENCY(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,int count)
{
    struct Stmt_Var* stmt_var_temp, *stmt_temp;
	//struct StatementNode* left_var_temp, *var_temp;
	//struct StatementNode* read_var_temp;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New* loop_index_temp;
	struct SizeNode* sz;
	int x,i;
        if(count==0)
        {
	fprintf(out,"#ifndef DATASET\n\t#define _NTHREAD 512\n\t#define _NBLOCK 65535\n#endif\n\n");
	fprintf(out, "#include<cuda.h>\n#include<time.h>\n");
        }
	fprintf(out, "\n\n// ----------KERNEL DECLARATION----------\n");
	fprintf(out, "__global__ void _AFFINE_KERNEL_%d(",count);
	stmt_var_temp = stmt_var;
	while(stmt_var_temp!=NULL){
		fdisplay_type(stmt_var_temp->var->type); 
		if(stmt_var_temp->var->identifier->size!=NULL) 
		    fprintf(out, "*");
		fprintf(out, " ");
		fprintf(out, ",");
		if(stmt_var_temp->var->identifier->size!=NULL) {
			sz = stmt_var_temp->var->identifier->size;
			x = 0;
			while(sz!=NULL){
				x++;
				sz = sz->next;
			}
			for(i=x;i>0;i--){
				fprintf(out, "int ,");
			}
		}
		stmt_var_temp = stmt_var_temp->next;
	}
	fprintf(out,"int ,");       //for "Total_Phi"
	//for(i=0;i<Total_Phi;i++)    // for phi_values
	    fprintf(out, "int ,");
    loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		fprintf(out, "int ,"); // for lower limit
		fprintf(out, "int ,");  // for upper limit
		loop_index_temp = loop_index_temp->next;
		}
	fprintf(out, "int );\n\n"); // for CUDA_TILE
}

void TD_kernel_declaration_DEPENDENCY(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,int count)
{
    struct Stmt_Var* stmt_var_temp, *stmt_temp;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New* loop_index_temp;
	struct SizeNode* sz;
	int x,i;
        if(count==0)
       {
	fprintf(out,"#ifndef DATASET\n\t#define _NTHREAD 512\n\t#define _NBLOCK 65535\n#endif\n\n");
       
	fprintf(out, "#include<cuda.h>\n#include<time.h>\n");
        }
	fprintf(out, "\n\n// ----------KERNEL DECLARATION----------\n");
	fprintf(out, "__global__ void _AFFINE_KERNEL_%d(",count);
	stmt_var_temp = stmt_var;
	while(stmt_var_temp!=NULL){
		fdisplay_type(stmt_var_temp->var->type);
		if(stmt_var_temp->var->identifier->size!=NULL) 
		    fprintf(out, "*");
		fprintf(out, " ");
		fprintf(out, ",");
		if(stmt_var_temp->var->identifier->size!=NULL) {
			sz = stmt_var_temp->var->identifier->size;
			x = 0;
			while(sz!=NULL){
				x++;
				sz = sz->next;
			}
			for(i=x;i>0;i--){
				fprintf(out, "int ,");
			}
		}
		stmt_var_temp = stmt_var_temp->next;
	}
	fprintf(out, "int, int, int, int );\n\n"); // for CUDA_TILE
	
	fprintf(out, "__global__ void _AFFINE_KERNEL_%d(",count);
	stmt_var_temp = stmt_var;
	while(stmt_var_temp!=NULL){
		fdisplay_type(stmt_var_temp->var->type);
		if(stmt_var_temp->var->identifier->size!=NULL) 
		    fprintf(out, "*");
		fprintf(out, " ");
		fprintf(out, ",");
		if(stmt_var_temp->var->identifier->size!=NULL) {
			sz = stmt_var_temp->var->identifier->size;
			x = 0;
			while(sz!=NULL){
				x++;
				sz = sz->next;
			}
			for(i=x;i>0;i--){
				fprintf(out, "int ,");
			}
		}
		stmt_var_temp = stmt_var_temp->next;
	}
	
    loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		fprintf(out, "int ,"); // for lower limit
		fprintf(out, "int ,");  // for upper limit
		loop_index_temp = loop_index_temp->next;
		}
	fprintf(out, "int );\n\n"); // for CUDA_TILE
}

//Function for kernel declaration if dependency doesn't exists
void cuda_kernel_declaration_NO_DEPENDENCY(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,int count)
{
    struct Stmt_Var* stmt_var_temp, *stmt_temp;
	//struct StatementNode* left_var_temp, *var_temp;
	//struct StatementNode* read_var_temp;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New* loop_index_temp;
	struct SizeNode* sz;
	int x,i;
        if(count==0)
       {
	fprintf(out,"#ifndef DATASET\n\t#define _NTHREAD 512\n\t#define _NBLOCK 65535\n#endif\n\n");
	fprintf(out, "#include<cuda.h>\n#include<time.h>\n");
       }
	fprintf(out, "\n\n// ----------KERNEL DECLARATION----------\n");
	fprintf(out, "__global__ void _AFFINE_KERNEL_%d(",count);
	stmt_var_temp = stmt_var;
	while(stmt_var_temp!=NULL){
		fdisplay_type(stmt_var_temp->var->type);
		if(stmt_var_temp->var->identifier->size!=NULL) 
		    fprintf(out, "*");
		fprintf(out, " ");
		fprintf(out, ",");
		if(stmt_var_temp->var->identifier->size!=NULL) {
			sz = stmt_var_temp->var->identifier->size;
			x = 0;
			while(sz!=NULL){
				x++;
				sz = sz->next;
			}
			for(i=x;i>0;i--){
				fprintf(out, "int ,");
			}
		}
		stmt_var_temp = stmt_var_temp->next;
	}
	
    loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
		fprintf(out, "int ,"); // for lower limit
		fprintf(out, "int ,");  // for upper limit
		loop_index_temp = loop_index_temp->next;
		}
	fprintf(out, "int );\n\n"); // for CUDA_TILE
}
/****************************************************************************************************************************/

/***************************************** KERNEL CALL CODE GENERATION ******************************************************/
//Function for declaring array size, cudamalloc, cudamemcpy, creating threads and blocks, calling kernel for simple shrinking
void simple_loop_shrinking_AFFINE(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct Stmt_Var* write_stmt_var,int count)
{
       // printf(" 1 time----------------------------------------------------------\n");
    	struct Stmt_Var* stmt_var_temp;
	struct StatementNode* var_temp;
	struct Stmt_Var *stmt_temp,*max_size_stmt=NULL;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New *loop_index_temp, *loop_temp;
	struct SizeNode* sz;
	int i,x,j,temp_size=1;
	int max_array_size=1;   //contains the array with maximum size like 'a' for declaration like int a[20][30],b[2][10][10]
	int max_dimension_size=1; //contains the max dimension size like 20 for declaration like int a[10][20] for considering the maximum possible array size while calculating threads and blocks
	
	fprintf(out,"\n\t#ifdef DATASET\n\t\tchar* outfile = (char*)malloc(sizeof(char)*(strlen(readfile)+50));\n\t\tstrcpy(outfile, readfile);\n\t\tstrcat(outfile, \".data\");\n\t\tFILE* fp;\n\t\tfp = fopen(outfile, \"a\");\n\t#endif\n");
	fprintf(out,"\n\t#ifdef TIME\n\t\tstruct timespec start_%d, end_%d, mid_start_%d, mid_end_%d;\n\t\tdouble runTime_%d, pre_time_%d, post_time_%d, computeTime_%d;\n\t#endif\n",count,count,count,count,count,count,count,count);
	
    	//CUDA ARRAY SIZE DECLARATIONS
    	stmt_temp = stmt_var;
         //printf(" display _stmt=-------------------------------\n");
           //        display_Stmt_Var(8,stmt_temp);
	while(stmt_temp!=NULL){
      // printf("------------------------------------1-------------------------------\n");
		if(stmt_temp->var->identifier->size==NULL) {
  //  printf("------------------------------------2-------------------------------\n");
			stmt_temp = stmt_temp->next;
			continue;
		}
		sz = stmt_temp->var->identifier->size;
		x = 0;
		while(sz!=NULL){
  //   printf("------------------------------------2-------------------------------\n");
			x++;
			sz = sz->next;
		}
		temp_size=1;
		for(i=x;i>0;i--){
			fprintf(out, "\tint ");
			fprintf(out, "_SZ_%s_%d = ",stmt_temp->var->identifier->string,count);
			fdisplay_StringNode(stmt_temp->var->identifier->size->sizeString);
			temp_size=temp_size*(atoi(stmt_temp->var->identifier->size->sizeString->string));
			fprintf(out, ";\n");
		}
		max_array_size=(temp_size>max_array_size)?temp_size:max_array_size;
		if(id_max<x)
		{ //  printf("------------------------------------3-------------------------------\n");
		    id_max=x;
		    max_size_stmt=stmt_temp;
                    // printf(" display max_size_stmt=-------------------------------\n");
                   //display_Stmt_Var(8,max_size_stmt);
		    }
		printMessage(8, "id_max for loop %d: %d\n",count,id_max);
		stmt_temp = stmt_temp->next;
	}
	// Calculating max_dimension_size
         if(max_size_stmt!=NULL);
	sz=max_size_stmt->var->identifier->size;
       // printf(" display size=-------------------------------\n");
      //  display_SizeNode(8,sz);
	while(sz!=NULL)
	{
	    temp_size=atoi(sz->sizeString->string);
	    max_dimension_size=(temp_size>max_dimension_size)?temp_size:max_dimension_size;
	    sz=sz->next;
	}
	//Update the max array size to be the max possible size for calculating thread and blocks
	int tempVar=id_max;
	max_array_size=1;
	while(tempVar)
	{
	    max_array_size*=max_dimension_size;
	    tempVar--;
	}
	
	fprintf(out,"\n\t#ifdef TIME\n\t\tclock_gettime(CLOCK_MONOTONIC, &start_%d);\n\t#endif\n",count);
	fprintf(out, "\n\t// ----------Allocating memory to Kernel Variable and copying them on device----------\n");
	// DEVELOPER VARIABLEs
	stmt_temp = stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out,"\t");
		fdisplay_type(stmt_temp->var->type);
		fprintf(out, " *_DEV_%s_%d;\n",stmt_temp->var->identifier->string,count);
		fprintf(out, "\tcudaMalloc((void**) &_DEV_%s_%d, sizeof(",stmt_temp->var->identifier->string,count);
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
		
		fprintf(out, "\tcudaMemcpy(_DEV_%s_%d, %s, sizeof(",stmt_temp->var->identifier->string,count,stmt_temp->var->identifier->string);
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
	
	fprintf(out, "\n\t// ----------Tiling and declaring threads and blocks required for Kernel Execution----------\n");
	fprintf(out, "\tint _NUM_THREADS_%d = %d;\n",count,max_array_size);
    fprintf(out, "\tfloat _NUM_BLOCKS_%d=1;\n\tint _NUM_TILE_%d=1;\n",count,count);
    fprintf(out, "\tdim3 _THREADS_%d(512);\n\tdim3 _BLOCKS_%d(1);\n",count,count);
	fprintf(out, "\tif(_NUM_THREADS_%d < _NTHREAD)\n",count);
	if(id_max==1) 
	    fprintf(out, "\t{\n\t\t_THREADS_%d.x=_NUM_THREADS_%d;\n\t}\n",count,count);
	else if(id_max==2) 
	    fprintf(out, "\t{\n\t\t_THREADS_%d.x=%d;\n\t\t_THREADS_%d.y=%d;\n\t}\n",count,max_dimension_size,count,max_dimension_size);
	else 
	    fprintf(out, "\t{\n\t\t_THREADS_%d.x=%d;\n\t\t_THREADS_%d.y=%d;\n\t\t_THREADS_%d.z=%d;\n\t}\n",count,max_dimension_size,count,max_dimension_size,count,max_dimension_size);
	
	fprintf(out, "\telse {\n");
	if(id_max==1) 
	    fprintf(out, "\t\t _THREADS_%d.x=_NTHREAD;\n\t\t_NUM_BLOCKS_%d=(_NUM_THREADS_%d %% _NTHREAD == 0)?(_NUM_THREADS_%d/_NTHREAD):((_NUM_THREADS_%d/_NTHREAD)+1);\n\t\tif(_NUM_BLOCKS_%d<_NBLOCK)\n\t\t\t_BLOCKS_%d.x=_NUM_BLOCKS_%d;\n\t\telse {\n\t\t\t_BLOCKS_%d.x=_NBLOCK;\n\t\t\tint temp_%d=_NUM_BLOCKS_%d;\n\t\t\t_NUM_TILE_%d=(temp_%d %% _NBLOCK == 0)?(_NUM_BLOCKS_%d/_NBLOCK):((_NUM_BLOCKS_%d/_NBLOCK)+1);\n\t\t}\n\t}\n",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count);
	else if(id_max==2) 
	    fprintf(out, "\t\t_NUM_BLOCKS_%d=(_NUM_THREADS_%d*1.0)/256;\n\t\t_BLOCKS_%d.x=_BLOCKS_%d.y=ceil(sqrt(_NUM_BLOCKS_%d));\n\t\t_THREADS_%d.x=_THREADS_%d.y=ceil(sqrt(%d.0/(_BLOCKS_%d.x*_BLOCKS_%d.y)));\n\t\tint temp_%d=_NUM_BLOCKS_%d;\n\t\tif(_NUM_BLOCKS_%d>_NBLOCK)\n\t\t\t_NUM_TILE_%d=(temp_%d %% _NBLOCK == 0)?(_NUM_BLOCKS_%d/_NBLOCK):((_NUM_BLOCKS_%d/_NBLOCK)+1);\n\t}\n",count,count,count,count,count,count,count,max_array_size,count,count,count,count,count,count,count,count,count);
    else 
        fprintf(out, "\t\t_NUM_BLOCKS_%d=(_NUM_THREADS_%d*1.0)/512;\n\t\t_BLOCKS_%d.x=_BLOCKS_%d.y=_BLOCKS_%d.z=ceil(cbrtf(_NUM_BLOCKS_%d));\n\t\t_THREADS_%d.x=_THREADS_%d.y=_THREADS_%d.z=ceil(cbrtf(%d.0/(_BLOCKS_%d.x*_BLOCKS_%d.y*_BLOCKS_%d.z)));\n\t\tint temp_%d=_NUM_BLOCKS_%d;\n\t\tif(_NUM_BLOCKS_%d>_NBLOCK)\n\t\t\t_NUM_TILE_%d=(temp_%d %% _NBLOCK == 0)?(_NUM_BLOCKS_%d/_NBLOCK):((_NUM_BLOCKS_%d/_NBLOCK)+1);\n\t}\n",count,count,count,count,count,count,count,count,count,max_array_size,count,count,count,count,count,count,count,count,count,count);
	
	fprintf(out,"\n\t#ifdef TIME\n\t\tclock_gettime(CLOCK_MONOTONIC, &mid_start_%d);\n\t#endif\n\n",count);
	fprintf(out, "\tint _CUDA_TILE_%d;\n",count);
	if(DependencyExists=='y')
	{
	loop_index_temp = loop_index_new;
	struct Phi_Values *lambda_temp=lambda_var;
	while(loop_index_temp!=NULL)
	{
	    fprintf(out, "\tfor(%s=%s;%s",loop_index_temp->loopIndex->string,loop_index_temp->L->string,loop_index_temp->loopIndex->string);
	    int ch=loop_index_temp->relop;
	    switch(ch)
	    {
	        case 1:fprintf(out, "<"); break;
	        case 2:fprintf(out, ">"); break;
	        case 3:fprintf(out, "<="); break;
	        case 4:fprintf(out, ">="); break;
	        default:fprintf(out, "wrong choice"); break;
	    }
	    fprintf(out, "%s;%s+=%d)\n",loop_index_temp->U->string,loop_index_temp->loopIndex->string,lambda_temp->phi_val);
	    lambda_temp=lambda_temp->next;
	    loop_index_temp=loop_index_temp->next;
	}
	}
	fprintf(out, "\tfor(_CUDA_TILE_%d=0;_CUDA_TILE_%d<_NUM_TILE_%d;_CUDA_TILE_%d++)\n\t{",count,count,count,count);
	fprintf(out, "\n\t\t// ----------KERNEL LAUNCH----------\n");
	fprintf(out, "\t\t_AFFINE_KERNEL_%d<<<_BLOCKS_%d,_THREADS_%d>>>(",count,count,count);
	stmt_var_temp = stmt_var;
	while(stmt_var_temp!=NULL){
		if(stmt_var_temp->var->identifier->size!=NULL) fprintf(out, "_DEV_");
		fprintf(out, "%s_%d, ",stmt_var_temp->var->identifier->string,count);
		if(stmt_var_temp->var->identifier->size!=NULL ) {
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
	if(DependencyExists=='y')
	{
	fprintf(out,"%d, ",Total_Phi);
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
	    fprintf(out,"%s, ",loop_index_temp->loopIndex->string);
	    loop_index_temp=loop_index_temp->next;
	}
	}
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
	    fprintf(out,"%s, %s, ",loop_index_temp->L->string,loop_index_temp->U->string);
	    loop_index_temp=loop_index_temp->next;
	}
	fprintf(out,"_CUDA_TILE_%d);\n",count);
	fprintf(out, "\t\tcudaDeviceSynchronize();\n\t}\n");
	stmt_temp = write_stmt_var;
	fprintf(out,"\n\t#ifdef TIME\n\t\tclock_gettime(CLOCK_MONOTONIC, &mid_end_%d);\n\t#endif\n",count);
	fprintf(out, "\n\t// ---------Copying Kernel variable from device to host----------\n");
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out, "\tcudaMemcpy(%s, _DEV_%s_%d, sizeof(",stmt_temp->var->identifier->string,stmt_temp->var->identifier->string,count);
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
	fprintf(out, "\n\t// ---------Releasing the memory allocated to kernel variable----------\n");
	stmt_temp = write_stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out, "\tcudaFree(_DEV_%s_%d);\n",stmt_temp->var->identifier->string,count);
		stmt_temp = stmt_temp->next;
	}
	fprintf(out,"\n\t#ifdef TIME\n\t\tclock_gettime(CLOCK_MONOTONIC, &end_%d);\n",count);
	fprintf(out,"\t\tpre_time_%d = (double) ((((&mid_start_%d)->tv_sec * 1000000000) + (&mid_start_%d)->tv_nsec) - (((&start_%d)->tv_sec * 1000000000) + (&start_%d)->tv_nsec)) / 1000000000;\n\t\tpost_time_%d = (double) ((((&end_%d)->tv_sec * 1000000000) + (&end_%d)->tv_nsec) - (((&mid_end_%d)->tv_sec * 1000000000) + (&mid_end_%d)->tv_nsec)) / 1000000000;\n\t\tcomputeTime_%d = (double) ((((&mid_end_%d)->tv_sec * 1000000000) + (&mid_end_%d)->tv_nsec) - (((&mid_start_%d)->tv_sec * 1000000000) + (&mid_start_%d)->tv_nsec)) / 1000000000;\n\t\trunTime_%d = (double) ((((&end_%d)->tv_sec * 1000000000) + (&end_%d)->tv_nsec) - (((&start_%d)->tv_sec * 1000000000) + (&start_%d)->tv_nsec)) / 1000000000;\n\t#endif\n\n",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count);
fprintf(out,"\t#ifdef DATASET\n\t\tfprintf(fp,\"%%d,%%d,%%d,%%d,%%d,%%.14f,%%.14f,%%.14f,%%.14f,%%d\\n\",N,_NTHREAD*_NBLOCK,_THREADS_%d.x,_BLOCKS_%d.x,data,pre_time_%d,computeTime_%d,post_time_%d,runTime_%d,_CUDA_TILE_%d);\n\t\tfclose(fp);\n\t\tfclose(f);\n\t#else\n\t#ifdef TIME\n\t\tprintf(\"Runtime:%%f\\n\",runTime_%d);\n\t#endif\n\t#endif\n",count,count,count,count,count,count,count,count);
	
}

//Function for declaring array size, cudamalloc, cudamemcpy, creating threads and blocks, calling kernel for selective shrinking
void complex_loop_shrinking_AFFINE(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct Stmt_Var* write_stmt_var,int count)
{
    struct Stmt_Var* stmt_var_temp;
	struct StatementNode* var_temp;
	struct Stmt_Var *stmt_temp ,*max_size_stmt=NULL;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New *loop_index_temp, *loop_temp;
	struct SizeNode* sz;
	int i,x,j,temp_size=1;
	int max_array_size=1;   //contains the array with maximum size like 'a' for declaration like int a[20][30],b[2][10][10]
	int max_dimension_size=1;
	
	fprintf(out,"\n\t#ifdef DATASET\n\t\tchar* outfile = (char*)malloc(sizeof(char)*(strlen(readfile)+50));\n\t\tstrcpy(outfile, readfile);\n\t\tstrcat(outfile, \".data\");\n\t\tFILE* fp;\n\t\tfp = fopen(outfile, \"a\");\n\t#endif\n");
	fprintf(out,"\n\t#ifdef TIME\n\t\tstruct timespec start_%d, end_%d, mid_start_%d, mid_end_%d;\n\t\tdouble runTime_%d, pre_time_%d, post_time_%d, computeTime_%d;\n\t#endif\n",count,count,count,count,count,count,count,count);
	
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
		temp_size=1;
		for(i=x;i>0;i--){
			fprintf(out, "\tint ");
			fprintf(out, "_SZ_%s_%d = ",stmt_temp->var->identifier->string,count);
			fdisplay_StringNode(stmt_temp->var->identifier->size->sizeString);
			temp_size=temp_size*(atoi(stmt_temp->var->identifier->size->sizeString->string));
			fprintf(out, ";\n");
		}
		max_array_size=(temp_size>max_array_size)?temp_size:max_array_size;
		if(id_max<x)
		{
		    id_max=x;
		    max_size_stmt=stmt_temp;
		    }
		printMessage(8, "id_max: %d\n",id_max);
		stmt_temp = stmt_temp->next;
	}
	// Calculating max_dimension_size
	sz=max_size_stmt->var->identifier->size;
	while(sz!=NULL)
	{
	    temp_size=atoi(sz->sizeString->string);
	    max_dimension_size=(temp_size>max_dimension_size)?temp_size:max_dimension_size;
	    sz=sz->next;
	}
	//Update the max array size to be the max possible size for calculating thread and blocks
	int tempVar=id_max;
	max_array_size=1;
	while(tempVar)
	{
	    max_array_size*=max_dimension_size;
	    tempVar--;
	}
	
	fprintf(out,"\n\t#ifdef TIME\n\t\tclock_gettime(CLOCK_MONOTONIC, &start_%d);\n\t#endif\n",count);
	fprintf(out, "\n\t// ----------Allocating memory to Kernel Variable and copying them on device----------\n");
	// DEVELOPER VARIABLEs
	stmt_temp = stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out,"\t");
		fdisplay_type(stmt_temp->var->type);
		fprintf(out, " *_DEV_%s_%d;\n",stmt_temp->var->identifier->string,count);
		fprintf(out, "\tcudaMalloc((void**) &_DEV_%s_%d sizeof(",stmt_temp->var->identifier->string,count);
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
		
		fprintf(out, "\tcudaMemcpy(_DEV_%s_%d, %s, sizeof(",stmt_temp->var->identifier->string,count,stmt_temp->var->identifier->string);
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
	
	fprintf(out, "\n\t// ----------Tiling and declaring threads and blocks required for Kernel Execution----------\n");
	fprintf(out, "\tint _NUM_THREADS_%d = %d;\n",count,max_array_size);
    fprintf(out, "\tfloat _NUM_BLOCKS_%d=1;\n\tint _NUM_TILE_%d=1;\n",count,count);
    fprintf(out, "\tdim3 _THREADS_%d(512);\n\tdim3 _BLOCKS_%d(1);\n",count,count);
	fprintf(out, "\tif(_NUM_THREADS_%d < _NTHREAD)\n",count);
	if(id_max==1) 
	    fprintf(out, "\t{\n\t\t_THREADS_%d.x=_NUM_THREADS_%d;\n\t}\n",count,count);
	else if(id_max==2) 
	    fprintf(out, "\t{\n\t\t_THREADS_%d.x=%d;\n\t\t_THREADS_%d.y=%d;\n\t}\n",count,max_dimension_size,count,max_dimension_size);
	else 
	    fprintf(out, "\t{\n\t\t_THREADS_%d.x=%d;\n\t\t_THREADS_%d.y=%d;\n\t\t_THREADS_%d.z=%d;\n\t}\n",count,max_dimension_size,count,max_dimension_size,count,max_dimension_size);
	
	fprintf(out, "\telse {\n");
	if(id_max==1) 
	    fprintf(out, "\t\t _THREADS_%d.x=_NTHREAD;\n\t\t_NUM_BLOCKS_%d=(_NUM_THREADS_%d %% _NTHREAD == 0)?(_NUM_THREADS_%d/_NTHREAD):((_NUM_THREADS_%d/_NTHREAD)+1);\n\t\tif(_NUM_BLOCKS_%d<_NBLOCK)\n\t\t\t_BLOCKS_%d.x=_NUM_BLOCKS_%d;\n\t\telse {\n\t\t\t_BLOCKS_%d.x=_NBLOCK;\n\t\t\tint temp_%d=_NUM_BLOCKS_%d;\n\t\t\t_NUM_TILE_%d=(temp_%d %% _NBLOCK == 0)?(_NUM_BLOCKS_%d/_NBLOCK):((_NUM_BLOCKS_%d/_NBLOCK)+1);\n\t\t}\n\t}\n",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count);
	else if(id_max==2) 
	    fprintf(out, "\t\t_NUM_BLOCKS_%d=(_NUM_THREADS_%d*1.0)/256;\n\t\t_BLOCKS_%d.x=_BLOCKS_%d.y=ceil(sqrt(_NUM_BLOCKS_%d));\n\t\t_THREADS_%d.x=_THREADS_%d.y=ceil(sqrt(%d.0/(_BLOCKS_%d.x*_BLOCKS_%d.y)));\n\t\tint temp_%d=_NUM_BLOCKS_%d;\n\t\tif(_NUM_BLOCKS_%d>_NBLOCK)\n\t\t\t_NUM_TILE_%d=(temp_%d %% _NBLOCK == 0)?(_NUM_BLOCKS_%d/_NBLOCK):((_NUM_BLOCKS_%d/_NBLOCK)+1);\n\t}\n",count,count,count,count,count,count,count,max_array_size,count,count,count,count,count,count,count,count,count);
    else 
        fprintf(out, "\t\t_NUM_BLOCKS_%d=(_NUM_THREADS_%d*1.0)/512;\n\t\t_BLOCKS_%d.x=_BLOCKS_%d.y=_BLOCKS_%d.z=ceil(cbrtf(_NUM_BLOCKS_%d));\n\t\t_THREADS_%d.x=_THREADS_%d.y=_THREADS_%d.z=ceil(cbrtf(%d.0/(_BLOCKS_%d.x*_BLOCKS_%d.y*_BLOCKS_%d.z)));\n\t\tint temp_%d=_NUM_BLOCKS_%d;\n\t\tif(_NUM_BLOCKS_%d>_NBLOCK)\n\t\t\t_NUM_TILE_%d=(temp_%d %% _NBLOCK == 0)?(_NUM_BLOCKS_%d/_NBLOCK):((_NUM_BLOCKS_%d/_NBLOCK)+1);\n\t}\n",count,count,count,count,count,count,count,count,count,max_array_size,count,count,count,count,count,count,count,count,count,count);
        
        fprintf(out,"\t#ifdef TIME\n\t\tclock_gettime(CLOCK_MONOTONIC, &mid_start_%d);\n\t#endif\n",count);
	fprintf(out, "\tint _CUDA_TILE_%d;\n",count);
	
	if(DependencyExists=='y')
	{
	int lambda_k=1;
	loop_index_temp = loop_index_new;
	struct Phi_Values *lambda_temp=lambda_var;
	while(loop_index_temp!=NULL&&lambda_k)
	{
	    fprintf(out, "\tfor(%s=%s;%s",loop_index_temp->loopIndex->string,loop_index_temp->L->string,loop_index_temp->loopIndex->string);
	    int ch=loop_index_temp->relop;
	    switch(ch)
	    {
	        case 1:fprintf(out, "<"); break;
	        case 2:fprintf(out, ">"); break;
	        case 3:fprintf(out, "<="); break;
	        case 4:fprintf(out, ">="); break;
	        default:fprintf(out, "wrong choice"); break;
	    }
	    fprintf(out, "%s;%s+=%d)\n",loop_index_temp->U->string,loop_index_temp->loopIndex->string,lambda_temp->phi_val);
	    if(lambda_temp->phi_val>=1)
	        lambda_k=0;
	    lambda_temp=lambda_temp->next;
	    loop_index_temp=loop_index_temp->next;
	}
	}
	fprintf(out, "\tfor(_CUDA_TILE_%d=0;_CUDA_TILE_%d<_NUM_TILE_%d;_CUDA_TILE_%d++)\n\t{",count,count,count,count);
	fprintf(out, "\n\t\t// ----------KERNEL LAUNCH----------\n");
	fprintf(out, "\t\t_AFFINE_KERNEL_%d<<<_BLOCKS_%d,_THREADS_%d>>>(",count,count,count);
	stmt_var_temp = stmt_var;
	while(stmt_var_temp!=NULL){
		if(stmt_var_temp->var->identifier->size!=NULL) fprintf(out, "_DEV_");
		fprintf(out, "%s_%d, ",stmt_var_temp->var->identifier->string,count);
		if(stmt_var_temp->var->identifier->size!=NULL ) {
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
	if(DependencyExists=='y')
	{
	fprintf(out,"%d, ",Total_Phi);
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
	    fprintf(out,"%s, ",loop_index_temp->loopIndex->string);
	    loop_index_temp=loop_index_temp->next;
	}
	}
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
	    fprintf(out,"%s, %s, ",loop_index_temp->L->string,loop_index_temp->U->string);
	    loop_index_temp=loop_index_temp->next;
	}
	fprintf(out,"_CUDA_TILE_%d);\n",count);
	fprintf(out, "\t\tcudaDeviceSynchronize();\n\t}\n");
	fprintf(out,"\n\t#ifdef TIME\n\t\tclock_gettime(CLOCK_MONOTONIC, &mid_end_%d);\n\t#endif\n",count);
	
	fprintf(out, "\n\t// ---------Copying Kernel variable from device to host----------\n");
	stmt_temp = write_stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out, "\tcudaMemcpy(%s, _DEV_%s_%d, sizeof(",stmt_temp->var->identifier->string,stmt_temp->var->identifier->string,count);
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
	
	fprintf(out, "\n\t// ---------Releasing the memory allocated to kernel variable----------\n");
	stmt_temp = write_stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out, "\tcudaFree(_DEV_%s);\n",stmt_temp->var->identifier->string);
		stmt_temp = stmt_temp->next;
	}
	fprintf(out,"\n\t#ifdef TIME\n\t\tclock_gettime(CLOCK_MONOTONIC, &end_%d);\n",count);
	fprintf(out,"\t\tpre_time_%d = (double) ((((&mid_start_%d)->tv_sec * 1000000000) + (&mid_start_%d)->tv_nsec) - (((&start_%d)->tv_sec * 1000000000) + (&start_%d)->tv_nsec)) / 1000000000;\n\t\tpost_time_%d = (double) ((((&end_%d)->tv_sec * 1000000000) + (&end_%d)->tv_nsec) - (((&mid_end_%d)->tv_sec * 1000000000) + (&mid_end_%d)->tv_nsec)) / 1000000000;\n\t\tcomputeTime_%d = (double) ((((&mid_end_%d)->tv_sec * 1000000000) + (&mid_end_%d)->tv_nsec) - (((&mid_start_%d)->tv_sec * 1000000000) + (&mid_start_%d)->tv_nsec)) / 1000000000;\n\t\trunTime_%d = (double) ((((&end_%d)->tv_sec * 1000000000) + (&end_%d)->tv_nsec) - (((&start_%d)->tv_sec * 1000000000) + (&start_%d)->tv_nsec)) / 1000000000;\n\t#endif\n\n",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count);
fprintf(out,"\t#ifdef DATASET\n\t\tfprintf(fp,\"%%d,%%d,%%d,%%d,%%d,%%.14f,%%.14f,%%.14f,%%.14f,%%d\\n\",N,_NTHREAD*_NBLOCK,_THREADS_%d.x,_BLOCKS_%d.x,data,pre_time_%d,computeTime_%d,post_time_%d,runTime_%d,_CUDA_TILE_%d);\n\t\tfclose(fp);\n\t\tfclose(f);\n\t#else\n\t#ifdef TIME\n\t\tprintf(\"Runtime:%%f\\n\",runTime_%d);\n\t#endif\n\t#endif\n",count,count,count,count,count,count,count,count);
	
	
}

void true_dependence_shrinking_AFFINE(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct Stmt_Var* write_stmt_var,int count)
{
    struct Stmt_Var* stmt_var_temp;
	struct StatementNode* var_temp;
	struct Stmt_Var *stmt_temp,*max_size_stmt=NULL;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New *loop_index_temp, *loop_temp;
	struct SizeNode* sz;
	int i,x,j,temp_size=1;
	int max_array_size=1;   //contains the array with maximum size like 'a' for declaration like int a[20][30],b[2][10][10]
	int max_dimension_size=1;

	fprintf(out,"\n\t#ifdef DATASET\n\t\tchar* outfile = (char*)malloc(sizeof(char)*(strlen(readfile)+50));\n\t\tstrcpy(outfile, readfile);\n\t\tstrcat(outfile, \".data\");\n\t\tFILE* fp;\n\t\tfp = fopen(outfile, \"a\");\n\t#endif\n");
	fprintf(out,"\n\t#ifdef TIME\n\t\tstruct timespec start_%d, end_%d, mid_start_%d, mid_end_%d;\n\t\tdouble runTime_%d, pre_time_%d, post_time_%d, computeTime_%d;\n\t#endif\n",count,count,count,count,count,count,count,count);
	
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
		temp_size=1;
		for(i=x;i>0;i--){
			fprintf(out, "\tint ");
			fprintf(out, "_SZ_%s_%d = ",stmt_temp->var->identifier->string,count);
			fdisplay_StringNode(stmt_temp->var->identifier->size->sizeString);
			temp_size=temp_size*(atoi(stmt_temp->var->identifier->size->sizeString->string));
			fprintf(out, ";\n");
		}
		max_array_size=(temp_size>max_array_size)?temp_size:max_array_size;
		if(id_max<x)
		{
		    id_max=x;
		    max_size_stmt=stmt_temp;
		    }
		printMessage(8, "id_max_for loop_%d: %d\n",count,id_max);
		stmt_temp = stmt_temp->next;
	}
	// Calculating max_dimension_size
	sz=max_size_stmt->var->identifier->size;
	while(sz!=NULL)
	{
	    temp_size=atoi(sz->sizeString->string);
	    max_dimension_size=(temp_size>max_dimension_size)?temp_size:max_dimension_size;
	    sz=sz->next;
	}
	//Update the max array size to be the max possible size for calculating thread and blocks
	int tempVar=id_max;
	max_array_size=1;
	while(tempVar)
	{
	    max_array_size*=max_dimension_size;
	    tempVar--;
	}
	fprintf(out,"\n\t#ifdef TIME\n\t\tclock_gettime(CLOCK_MONOTONIC, &start_%d);\n\t#endif\n",count);
	fprintf(out, "\n\t// ----------Allocating memory to Kernel Variable and copying them on device----------\n");
	// DEVELOPER VARIABLEs
	stmt_temp = stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out,"\t");
		fdisplay_type(stmt_temp->var->type);
		fprintf(out, " *_DEV_%s_%d;\n",stmt_temp->var->identifier->string,count);
		fprintf(out, "\tcudaMalloc((void**) &_DEV_%s_%d, sizeof(",stmt_temp->var->identifier->string,count);
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
		
		fprintf(out, "\tcudaMemcpy(_DEV_%s_%d, %s, sizeof(",stmt_temp->var->identifier->string,count,stmt_temp->var->identifier->string);
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
	fprintf(out, "\n\t// ----------Tiling and declaring threads and blocks required for Kernel Execution----------\n");
	fprintf(out, "\tint _NUM_THREADS_%d = %d;\n",count,max_array_size);
    fprintf(out, "\tfloat _NUM_BLOCKS_%d=1;\n\tint _NUM_TILE_%d=1;\n",count,count);
    fprintf(out, "\tdim3 _THREADS_%d(512);\n\tdim3 _BLOCKS_%d(1);\n",count,count);
	fprintf(out, "\tif(_NUM_THREADS_%d < _NTHREAD)\n",count);
	if(id_max==1) 
	    fprintf(out, "\t{\n\t\t_THREADS_%d.x=_NUM_THREADS_%d;\n\t}\n",count,count);
	else if(id_max==2) 
	    fprintf(out, "\t{\n\t\t_THREADS_%d.x=%d;\n\t\t_THREADS_%d.y=%d;\n\t}\n",count,max_dimension_size,count,max_dimension_size);
	else 
	    fprintf(out, "\t{\n\t\t_THREADS_%d.x=%d;\n\t\t_THREADS_%d.y=%d;\n\t\t_THREADS_%d.z=%d;\n\t}\n",count,max_dimension_size,count,max_dimension_size,count,max_dimension_size);
	
	fprintf(out, "\telse {\n");
	if(id_max==1) 
	    fprintf(out, "\t\t _THREADS_%d.x=_NTHREAD;\n\t\t_NUM_BLOCKS_%d=(_NUM_THREADS_%d %% _NTHREAD == 0)?(_NUM_THREADS_%d/_NTHREAD):((_NUM_THREADS_%d/_NTHREAD)+1);\n\t\tif(_NUM_BLOCKS_%d<_NBLOCK)\n\t\t\t_BLOCKS_%d.x=_NUM_BLOCKS_%d;\n\t\telse {\n\t\t\t_BLOCKS_%d.x=_NBLOCK;\n\t\t\tint temp_%d=_NUM_BLOCKS_%d;\n\t\t\t_NUM_TILE_%d=(temp_%d %% _NBLOCK == 0)?(_NUM_BLOCKS_%d/_NBLOCK):((_NUM_BLOCKS_%d/_NBLOCK)+1);\n\t\t}\n\t}\n",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count);
	else if(id_max==2) 
	    fprintf(out, "\t\t_NUM_BLOCKS_%d=(_NUM_THREADS_%d*1.0)/256;\n\t\t_BLOCKS_%d.x=_BLOCKS_%d.y=ceil(sqrt(_NUM_BLOCKS_%d));\n\t\t_THREADS_%d.x=_THREADS_%d.y=ceil(sqrt(%d.0/(_BLOCKS_%d.x*_BLOCKS_%d.y)));\n\t\tint temp_%d=_NUM_BLOCKS_%d;\n\t\tif(_NUM_BLOCKS_%d>_NBLOCK)\n\t\t\t_NUM_TILE_%d=(temp_%d %% _NBLOCK == 0)?(_NUM_BLOCKS_%d/_NBLOCK):((_NUM_BLOCKS_%d/_NBLOCK)+1);\n\t}\n",count,count,count,count,count,count,count,max_array_size,count,count,count,count,count,count,count,count,count);
    else 
        fprintf(out, "\t\t_NUM_BLOCKS_%d=(_NUM_THREADS_%d*1.0)/512;\n\t\t_BLOCKS_%d.x=_BLOCKS_%d.y=_BLOCKS_%d.z=ceil(cbrtf(_NUM_BLOCKS_%d));\n\t\t_THREADS_%d.x=_THREADS_%d.y=_THREADS_%d.z=ceil(cbrtf(%d.0/(_BLOCKS_%d.x*_BLOCKS_%d.y*_BLOCKS_%d.z)));\n\t\tint temp_%d=_NUM_BLOCKS_%d;\n\t\tif(_NUM_BLOCKS_%d>_NBLOCK)\n\t\t\t_NUM_TILE_%d=(temp_%d %% _NBLOCK == 0)?(_NUM_BLOCKS_%d/_NBLOCK):((_NUM_BLOCKS_%d/_NBLOCK)+1);\n\t}\n",count,count,count,count,count,count,count,count,count,max_array_size,count,count,count,count,count,count,count,count,count,count);
    fprintf(out,"\n\t#ifdef TIME\n\t\tclock_gettime(CLOCK_MONOTONIC, &mid_start_%d);\n\t#endif\n\n",count);  
	fprintf(out, "\tint _CUDA_TILE_%d;\n",count);
	
	int lambda=lambda_var->phi_val;
	if(DependencyExists=='y')
	{
	    fprintf(out, "\tint lambda_%d=%d;\n",count,lambda);
	    fprintf(out, "\tint id_1_%d,id_2_%d,id_3_%d,id_4_%d,id_5_%d;\n",count,count,count,count,count);
	    loop_index_temp = loop_index_new;
	    int temp_var=1;
	    while(loop_index_temp!=NULL)
	    {
	        fprintf(out, "\tint UB_%d_%d=%s-%s;\n",temp_var,count,loop_index_temp->U->string,loop_index_temp->L->string);
	        temp_var++;
	        loop_index_temp=loop_index_temp->next;
	    }
	    fprintf(out, "\tfor(id_1_%d=1;id_1_%d<=(",count,count);
	    loop_index_temp = loop_index_new;
	    temp_var=1;
	    while(loop_index_temp!=NULL)
	    {
	        if(loop_index_temp->next)
	            fprintf(out, "UB_%d_%d*",temp_var,count);
	        else
	            fprintf(out, "UB_%d_%d",temp_var,count);
	        temp_var++;
	        loop_index_temp=loop_index_temp->next;
	    }
	    fprintf(out, ");id_1_%d+=lambda_%d) {\n",count,count);
	    fprintf(out, "\t\tid_2_%d=(id_1_%d/UB_2_%d);\n",count,count,count);
	    fprintf(out, "\t\tid_3_%d=((id_1_%d+lambda_%d)/UB_2_%d);\n",count,count,count,count);
	    fprintf(out, "\t\tid_4_%d=(id_1_%d%%UB_2_%d)-1;\n",count,count,count);
	    fprintf(out, "\t\tid_5_%d=UB_2_%d-((id_1_%d+lambda_%d)%%UB_2_%d);\n\n",count,count,count,count,count);
	    fprintf(out, "\t\tfor(_CUDA_TILE_%d=0;_CUDA_TILE_%d<_NUM_TILE_%d;_CUDA_TILE_%d++)\n\t\t{",count,count,count,count);
	     fprintf(out, "\n\t\t// ----------KERNEL LAUNCH----------\n");
	    fprintf(out, "\t\t\t_AFFINE_KERNEL_1_%d<<<_BLOCKS_%d,_THREADS_%d>>>(",count,count,count);
	    stmt_var_temp = stmt_var;
	    while(stmt_var_temp!=NULL){
		    if(stmt_var_temp->var->identifier->size!=NULL) fprintf(out, "_DEV_");
		    fprintf(out, "%s_%d, ",stmt_var_temp->var->identifier->string,count);
		    if(stmt_var_temp->var->identifier->size!=NULL ) {
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
	    fprintf(out, "id_2_%d, id_4_%d, UB_2_%d, _CUDA_TILE_%d);\n",count,count,count,count);
	    fprintf(out, "\t\t\tcudaDeviceSynchronize();\n\t\t}\n");
	    
	    fprintf(out, "\t\tfor(_CUDA_TILE_%d=0;_CUDA_TILE_%d<_NUM_TILE_%d;_CUDA_TILE_%d++)\n\t\t{",count,count,count,count);
	    fprintf(out, "\n\t\t// ----------KERNEL LAUNCH----------\n");
	    fprintf(out, "\t\t\t_AFFINE_KERNEL_%d<<<_BLOCKS_%d,_THREADS_%d>>>(",count,count,count);
	    stmt_var_temp = stmt_var;
	    while(stmt_var_temp!=NULL){
		    if(stmt_var_temp->var->identifier->size!=NULL) fprintf(out, "_DEV_");
		    fprintf(out, "%s_%d, ",stmt_var_temp->var->identifier->string,count);
		    if(stmt_var_temp->var->identifier->size!=NULL ) {
		    	sz = stmt_var_temp->var->identifier->size;
		    	x = 0;
		    	while(sz!=NULL){
		    		x++;
		    		sz = sz->next;
		    	}
		    	for(i=x;i>0;i--){
		    		fprintf(out, "_SZ_%s_%d, ",stmt_var_temp->var->identifier->string,i);
		    	}
		    }
		    stmt_var_temp = stmt_var_temp->next;
	    }
	    fprintf(out, "id_2_%d, id_3_%d, %s, %s, _CUDA_TILE_%d);\n",count,count,loop_index_new->next->L->string,loop_index_new->next->U->string,count);
	    fprintf(out, "\t\t\tcudaDeviceSynchronize();\n\t\t}\n");
	    
	    fprintf(out, "\t\tfor(_CUDA_TILE_%d=0;_CUDA_TILE_%d<_NUM_TILE_%d;_CUDA_TILE_%d++)\n\t\t{",count,count,count,count);
	    fprintf(out, "\n\t\t// ----------KERNEL LAUNCH----------\n");
	    fprintf(out, "\t\t\t_AFFINE_KERNEL_%d<<<_BLOCKS_%d,_THREADS_%d>>>(",count,count,count);
	    stmt_var_temp = stmt_var;
	    while(stmt_var_temp!=NULL){
		    if(stmt_var_temp->var->identifier->size!=NULL) fprintf(out, "_DEV_");
		    fprintf(out, "%s_%d, ",stmt_var_temp->var->identifier->string,count);
		    if(stmt_var_temp->var->identifier->size!=NULL ) {
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
	    fprintf(out, "id_3_%d,  id_5_%d,%s,%s _CUDA_TILE_%d);\n",count,count,loop_index_new->next->L->string,loop_index_new->next->U->string,count);  
	    fprintf(out, "\t\t\tcudaDeviceSynchronize();\n\t\t}\n\t}\n");
	}
	fprintf(out,"\n\t#ifdef TIME\n\t\tclock_gettime(CLOCK_MONOTONIC, &mid_end_%d);\n\t#endif\n",count);
	fprintf(out, "\n\t// ---------Copying Kernel variable from device to host----------\n");
	stmt_temp = write_stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out, "\tcudaMemcpy(%s, _DEV_%s_%d, sizeof(",stmt_temp->var->identifier->string,stmt_temp->var->identifier->string,count);
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
	fprintf(out, "\n\t// ---------Releasing the memory allocated to kernel variable----------\n");
	stmt_temp = write_stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out, "\tcudaFree(_DEV_%s_%d);\n",stmt_temp->var->identifier->string,count);
		stmt_temp = stmt_temp->next;
	}
	fprintf(out,"\n\t#ifdef TIME\n\t\tclock_gettime(CLOCK_MONOTONIC, &end_%d);\n",count);
	fprintf(out,"\t\tpre_time_%d = (double) ((((&mid_start_%d)->tv_sec * 1000000000) + (&mid_start_%d)->tv_nsec) - (((&start_%d)->tv_sec * 1000000000) + (&start_%d)->tv_nsec)) / 1000000000;\n\t\tpost_time_%d = (double) ((((&end_%d)->tv_sec * 1000000000) + (&end_%d)->tv_nsec) - (((&mid_end_%d)->tv_sec * 1000000000) + (&mid_end_%d)->tv_nsec)) / 1000000000;\n\t\tcomputeTime_%d = (double) ((((&mid_end_%d)->tv_sec * 1000000000) + (&mid_end_%d)->tv_nsec) - (((&mid_start_%d)->tv_sec * 1000000000) + (&mid_start_%d)->tv_nsec)) / 1000000000;\n\t\trunTime_%d = (double) ((((&end_%d)->tv_sec * 1000000000) + (&end_%d)->tv_nsec) - (((&start_%d)->tv_sec * 1000000000) + (&start_%d)->tv_nsec)) / 1000000000;\n\t#endif\n\n",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count);
fprintf(out,"\t#ifdef DATASET\n\t\tfprintf(fp,\"%%d,%%d,%%d,%%d,%%d,%%.14f,%%.14f,%%.14f,%%.14f,%%d\\n\",N,_NTHREAD*_NBLOCK,_THREADS_%d.x,_BLOCKS_%d.x,data,pre_time_%d,computeTime_%d,post_time_%d,runTime_%d,_CUDA_TILE_%d);\n\t\tfclose(fp);\n\t\tfclose(f);\n\t#else\n\t#ifdef TIME\n\t\tprintf(\"Runtime:%%f\\n\",runTime_%d);\n\t#endif\n\t#endif\n",count,count,count,count,count,count,count,count);
}

void cuda_kernel_call_NO_DEPENDENCY(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct Stmt_Var* write_stmt_var,int count)
{
    
    struct Stmt_Var* stmt_var_temp;
	struct StatementNode* var_temp;
	struct Stmt_Var *stmt_temp,*max_size_stmt=NULL;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New *loop_index_temp, *loop_temp;
	struct SizeNode* sz;
	int i,x,j,temp_size=1;
	int max_array_size=1;   //contains the array with maximum size like 'a' for declaration like int a[20][30],b[2][10][10]
	int max_dimension_size=1; //contains the max dimension size like 20 for declaration like int a[10][20] for considering the maximum possible array size while calculating threads and blocks
	
	fprintf(out,"\n\t#ifdef DATASET\n\t\tchar* outfile = (char*)malloc(sizeof(char)*(strlen(readfile)+50));\n\t\tstrcpy(outfile, readfile);\n\t\tstrcat(outfile, \".data\");\n\t\tFILE* fp;\n\t\tfp = fopen(outfile, \"a\");\n\t#endif\n");
	fprintf(out,"\n\t#ifdef TIME\n\t\tstruct timespec start_%d, end_%d, mid_start_%d, mid_end_%d;\n\t\tdouble runTime_%d, pre_time_%d, post_time_%d, computeTime_%d;\n\t#endif\n",count,count,count,count,count,count,count,count);
	
	
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
		temp_size=1;
		for(i=x;i>0;i--){
			fprintf(out, "\tint ");
			fprintf(out, "_SZ_%s_%d = ",stmt_temp->var->identifier->string,count);
			fdisplay_StringNode(stmt_temp->var->identifier->size->sizeString);
			temp_size=temp_size*(atoi(stmt_temp->var->identifier->size->sizeString->string));
			fprintf(out, ";\n");
		}
		max_array_size=(temp_size>max_array_size)?temp_size:max_array_size;
		if(id_max<x)
		{
		    id_max=x;
		    max_size_stmt=stmt_temp;
		    }
		printMessage(8, "id_max for loop %d: %d\n",id_max,count);
		stmt_temp = stmt_temp->next;
	}
	// Calculating max_dimension_size
	sz=max_size_stmt->var->identifier->size;
	while(sz!=NULL)
	{
	    temp_size=atoi(sz->sizeString->string);
	    max_dimension_size=(temp_size>max_dimension_size)?temp_size:max_dimension_size;
	    sz=sz->next;
	}
	//Update the max array size to be the max possible size for calculating thread and blocks
	int tempVar=id_max;
	max_array_size=1;
	while(tempVar)
	{
	    max_array_size*=max_dimension_size;
	    tempVar--;
	}
	
	fprintf(out,"\n\t#ifdef TIME\n\t\tclock_gettime(CLOCK_MONOTONIC, &start_%d);\n\t#endif\n",count);
	fprintf(out, "\n\t// ----------Allocating memory to Kernel Variable and copying them on device----------\n");
	// DEVELOPER VARIABLEs
	stmt_temp = stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out,"\t");
		fdisplay_type(stmt_temp->var->type);
		fprintf(out, " *_DEV_%s;\n",stmt_temp->var->identifier->string);
		fprintf(out, "\tcudaMalloc((void**) &_DEV_%s_%d, sizeof(",stmt_temp->var->identifier->string,count);
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
		
		fprintf(out, "\tcudaMemcpy(_DEV_%s_%d, %s, sizeof(",stmt_temp->var->identifier->string,count,stmt_temp->var->identifier->string);
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
	fprintf(out, "\n\t// ----------Tiling and declaring threads and blocks required for Kernel Execution----------\n");
	fprintf(out, "\tint _NUM_THREADS_%d = %d;\n",count,max_array_size);
    fprintf(out, "\tfloat _NUM_BLOCKS_%d=1;\n\tint _NUM_TILE_%d=1;\n",count,count);
    fprintf(out, "\tdim3 _THREADS_%d(512);\n\tdim3 _BLOCKS_%d(1);\n",count,count);
	fprintf(out, "\tif(_NUM_THREADS_%d < _NTHREAD)\n",count);
	if(id_max==1) 
	    fprintf(out, "\t{\n\t\t_THREADS_%d.x=_NUM_THREADS_%d;\n\t}\n",count,count);
	else if(id_max==2) 
	    fprintf(out, "\t{\n\t\t_THREADS_%d.x=%d;\n\t\t_THREADS_%d.y=%d;\n\t}\n",count,max_dimension_size,count,max_dimension_size);
	else 
	    fprintf(out, "\t{\n\t\t_THREADS_%d.x=%d;\n\t\t_THREADS_%d.y=%d;\n\t\t_THREADS_%d.z=%d;\n\t}\n",count,max_dimension_size,count,max_dimension_size,count,max_dimension_size);
	
	fprintf(out, "\telse {\n");
	if(id_max==1) 
	    fprintf(out, "\t\t _THREADS_%d.x=_NTHREAD;\n\t\t_NUM_BLOCKS_%d=(_NUM_THREADS_%d %% _NTHREAD == 0)?(_NUM_THREADS_%d/_NTHREAD):((_NUM_THREADS_%d/_NTHREAD)+1);\n\t\tif(_NUM_BLOCKS_%d<_NBLOCK)\n\t\t\t_BLOCKS_%d.x=_NUM_BLOCKS_%d;\n\t\telse {\n\t\t\t_BLOCKS_%d.x=_NBLOCK;\n\t\t\tint temp_%d=_NUM_BLOCKS_%d;\n\t\t\t_NUM_TILE_%d=(temp_%d %% _NBLOCK == 0)?(_NUM_BLOCKS_%d/_NBLOCK):((_NUM_BLOCKS_%d/_NBLOCK)+1);\n\t\t}\n\t}\n",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count);
	else if(id_max==2) 
	    fprintf(out, "\t\t_NUM_BLOCKS_%d=(_NUM_THREADS_%d*1.0)/256;\n\t\t_BLOCKS_%d.x=_BLOCKS_%d.y=ceil(sqrt(_NUM_BLOCKS_%d));\n\t\t_THREADS_%d.x=_THREADS_%d.y=ceil(sqrt(%d.0/(_BLOCKS_%d.x*_BLOCKS_%d.y)));\n\t\tint temp_%d=_NUM_BLOCKS_%d;\n\t\tif(_NUM_BLOCKS_%d>_NBLOCK)\n\t\t\t_NUM_TILE_%d=(temp_%d %% _NBLOCK == 0)?(_NUM_BLOCKS_%d/_NBLOCK):((_NUM_BLOCKS_%d/_NBLOCK)+1);\n\t}\n",count,count,count,count,count,count,count,max_array_size,count,count,count,count,count,count,count,count,count);
    else 
        fprintf(out, "\t\t_NUM_BLOCKS_%d=(_NUM_THREADS_%d*1.0)/512;\n\t\t_BLOCKS_%d.x=_BLOCKS_%d.y=_BLOCKS_%d.z=ceil(cbrtf(_NUM_BLOCKS_%d));\n\t\t_THREADS_%d.x=_THREADS_%d.y=_THREADS_%d.z=ceil(cbrtf(%d.0/(_BLOCKS_%d.x*_BLOCKS_%d.y*_BLOCKS_%d.z)));\n\t\tint temp_%d=_NUM_BLOCKS_%d;\n\t\tif(_NUM_BLOCKS_%d>_NBLOCK)\n\t\t\t_NUM_TILE_%d=(temp_%d %% _NBLOCK == 0)?(_NUM_BLOCKS_%d/_NBLOCK):((_NUM_BLOCKS_%d/_NBLOCK)+1);\n\t}\n",count,count,count,count,count,count,count,count,count,max_array_size,count,count,count,count,count,count,count,count,count,count);
	
	fprintf(out,"\n\t#ifdef TIME\n\t\tclock_gettime(CLOCK_MONOTONIC, &mid_start_%d);\n\t#endif\n\n",count);
	fprintf(out, "\tint _CUDA_TILE_%d;\n",count);
	fprintf(out, "\tfor(_CUDA_TILE_%d=0;_CUDA_TILE_%d<_NUM_TILE_%d;_CUDA_TILE_%d++)\n\t{",count,count,count,count);
	fprintf(out, "\n\t\t// ----------KERNEL LAUNCH----------\n");
	fprintf(out, "\t\t_AFFINE_KERNEL_%d<<<_BLOCKS_%d,_THREADS_%d>>>(",count,count,count);
	stmt_var_temp = stmt_var;
	while(stmt_var_temp!=NULL){
		if(stmt_var_temp->var->identifier->size!=NULL) fprintf(out, "_DEV_");
		fprintf(out, "%s_%d, ",stmt_var_temp->var->identifier->string,count);
		if(stmt_var_temp->var->identifier->size!=NULL ) {
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
	    fprintf(out,"%s, %s, ",loop_index_temp->L->string,loop_index_temp->U->string);
	    loop_index_temp=loop_index_temp->next;
	}
	fprintf(out,"_CUDA_TILE_%d);\n",count);
	fprintf(out, "\t\tcudaDeviceSynchronize();\n\t}\n");
	
	fprintf(out,"\n\t#ifdef TIME\n\t\tclock_gettime(CLOCK_MONOTONIC, &mid_end_%d);\n\t#endif\n",count);
	fprintf(out, "\n\t// ---------Copying Kernel variable from device to host----------\n");
	stmt_temp = write_stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out, "\tcudaMemcpy(%s, _DEV_%s_%d, sizeof(",stmt_temp->var->identifier->string,stmt_temp->var->identifier->string,count);
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
	fprintf(out, "\n\t// ---------Releasing the memory allocated to kernel variable----------\n");
	stmt_temp = write_stmt_var;
	while(stmt_temp!=NULL){
		if(stmt_temp->var->identifier->size==NULL) {
			stmt_temp = stmt_temp->next;
			continue;
		}
		fprintf(out, "\tcudaFree(_DEV_%s_%d);\n",stmt_temp->var->identifier->string,count);
		stmt_temp = stmt_temp->next;
	}
	fprintf(out,"\n\t#ifdef TIME\n\t\tclock_gettime(CLOCK_MONOTONIC, &end_%d);\n",count);
	fprintf(out,"\t\tpre_time_%d = (double) ((((&mid_start_%d)->tv_sec * 1000000000) + (&mid_start_%d)->tv_nsec) - (((&start_%d)->tv_sec * 1000000000) + (&start_%d)->tv_nsec)) / 1000000000;\n\t\tpost_time_%d = (double) ((((&end_%d)->tv_sec * 1000000000) + (&end_%d)->tv_nsec) - (((&mid_end_%d)->tv_sec * 1000000000) + (&mid_end_%d)->tv_nsec)) / 1000000000;\n\t\tcomputeTime_%d = (double) ((((&mid_end_%d)->tv_sec * 1000000000) + (&mid_end_%d)->tv_nsec) - (((&mid_start_%d)->tv_sec * 1000000000) + (&mid_start_%d)->tv_nsec)) / 1000000000;\n\t\trunTime_%d = (double) ((((&end_%d)->tv_sec * 1000000000) + (&end_%d)->tv_nsec) - (((&start_%d)->tv_sec * 1000000000) + (&start_%d)->tv_nsec)) / 1000000000;\n\t#endif\n\n",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count);
fprintf(out,"\t#ifdef DATASET\n\t\tfprintf(fp,\"%%d,%%d,%%d,%%d,%%d,%%.14f,%%.14f,%%.14f,%%.14f,%%d\\n\",N,_NTHREAD*_NBLOCK,_THREADS_%d.x,_BLOCKS_%d.x,data,pre_time_%d,computeTime_%d,post_time_%d,runTime_%d,_CUDA_TILE_%d);\n\t\tfclose(fp);\n\t\tfclose(f);\n\t#else\n\t#ifdef TIME\n\t\tprintf(\"Runtime:%%f\\n\",runTime_%d);\n\t#endif\n\t#endif\n",count,count,count,count,count,count,count,count);

}
/*******************************************************************************************************************************/

/***********************************  KERNEL DEFINITION CODE GENERATION ********************************************************/

//Function for kernel definition if dependency exists
void SimpleSelective_kernel_definition_DEPENDENCY(char *shrinking_type,struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct StatementNode* parallel_stmt,int count)
{
    struct Stmt_Var* stmt_var_temp, *stmt_temp;
	struct StatementNode* left_var_temp, *var_temp;
	struct StatementNode* read_var_temp;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New* loop_index_temp;
	struct SizeNode* sz;
	int x,i;
	
	fprintf(out, "\n\n// ----------KERNEL DEFINITION----------\n");
	fprintf(out, "\n\n__global__ void _AFFINE_KERNEL_%d(",count);
	stmt_var_temp = stmt_var;
	while(stmt_var_temp!=NULL){
		fdisplay_type(stmt_var_temp->var->type);
		if(stmt_var_temp->var->identifier->size!=NULL) fprintf(out, "*");
		fprintf(out, " ");
		fprintf(out, "%s,",stmt_var_temp->var->identifier->string);
		if(stmt_var_temp->var->identifier->size!=NULL) {
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
	fprintf(out,"int phi_count, ");
	int temp=Total_Phi;
	/*int count=1;
	while(temp!=0)
	{
	    fprintf(out,"int phi_%d, ",count++);
	    temp--;   
	}*/
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
	    fprintf(out,"int CUDA_%s, ",loop_index_temp->loopIndex->string);
	    loop_index_temp=loop_index_temp->next;
	}
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
	    fprintf(out,"int CUDA_L_%s,int CUDA_U_%s, ",loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string);
	    loop_index_temp=loop_index_temp->next;
	}
	fprintf(out,"int _CUDA_TILE_%d)\n{\n",count);
	fprintf(out, "\tint %s = gridDim.x*blockDim.x*_CUDA_TILE_%d + blockDim.x*blockIdx.x + threadIdx.x;\n",loop_index_new->loopIndex->string,count);
	if(loop_index_new->next!=NULL)
	{
	    fprintf(out, "\tint %s = gridDim.y*blockDim.y*_CUDA_TILE_%d + blockDim.y*blockIdx.y + threadIdx.y;\n",loop_index_new->next->loopIndex->string,count);
	    if(loop_index_new->next->next!=NULL)
	        fprintf(out, "\tint %s = gridDim.z*blockDim.z*_CUDA_TILE_%d + blockDim.z*blockIdx.z + threadIdx.z;\n",loop_index_new->next->next->loopIndex->string,count);
	    }
	int lambda_k=1;
	loop_index_temp = loop_index_new;
	struct Phi_Values *lambda_temp=lambda_var;
	while(loop_index_temp!=NULL)
	{
	    if((!strcmp(shrinking_type,"selective"))&&(lambda_k==0))
	    {
	        fprintf(out,"\tif((CUDA_L_%s<=%s)&&(%s",loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string);
	    }
	    else
	    {
	        fprintf(out,"\tif((CUDA_%s<=%s)&&(%s<(CUDA_%s+%d))&&(%s",loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string,lambda_temp->phi_val,loop_index_temp->loopIndex->string);
	    }
	    int ch=loop_index_temp->relop;
	    switch(ch)
	    {
	        case 1:fprintf(out, "<"); break;
	        case 2:fprintf(out, ">"); break;
	        case 3:fprintf(out, "<="); break;
	        case 4:fprintf(out, ">="); break;
	        default:fprintf(out, "wrong choice"); break;
	    }
	    fprintf(out,"CUDA_U_%s)){\n",loop_index_temp->loopIndex->string);
	    if(lambda_temp->phi_val>=1)
	        lambda_k=0;
	    lambda_temp=lambda_temp->next;
	    loop_index_temp=loop_index_temp->next;
	}
	fdisplay_StatementNode_1D(parallel_stmt);
	temp=2;
	while(temp--)
	{
	    fprintf(out, "}");
	}
	//fprintf(out, "}\n\n");
}

////Function for kernel definition if dependency doesn't exists
void cuda_kernel_definition_NO_DEPENDENCY(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct StatementNode* parallel_stmt,int count)
{
    struct Stmt_Var* stmt_var_temp, *stmt_temp;
	struct StatementNode* left_var_temp, *var_temp;
	struct StatementNode* read_var_temp;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New* loop_index_temp;
	struct SizeNode* sz;
	int x,i;
	
	fprintf(out, "\n\n// ----------KERNEL DEFINITION----------\n");
	fprintf(out, "\n\n__global__ void _AFFINE_KERNEL_%d(", count);
	stmt_var_temp = stmt_var;
	while(stmt_var_temp!=NULL){
		fdisplay_type(stmt_var_temp->var->type);
		if(stmt_var_temp->var->identifier->size!=NULL) fprintf(out, "*");
		fprintf(out, " ");
		fprintf(out, "%s,",stmt_var_temp->var->identifier->string);
		if(stmt_var_temp->var->identifier->size!=NULL) {
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
	    fprintf(out,"int CUDA_L_%s,int CUDA_U_%s, ",loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string);
	    loop_index_temp=loop_index_temp->next;
	}
	fprintf(out,"int _CUDA_TILE_%d)\n{\n",count);
	fprintf(out, "\tint %s = gridDim.x*blockDim.x*_CUDA_TILE_%d + blockDim.x*blockIdx.x + threadIdx.x;\n",loop_index_new->loopIndex->string,count);
	if(loop_index_new->next!=NULL)
	{
	    fprintf(out, "\tint %s = gridDim.y*blockDim.y*_CUDA_TILE_%d + blockDim.y*blockIdx.y + threadIdx.y;\n",loop_index_new->next->loopIndex->string,count);
	    if(loop_index_new->next->next!=NULL)
	        fprintf(out, "\tint %s = gridDim.z*blockDim.z*_CUDA_TILE_%d + blockDim.z*blockIdx.z + threadIdx.z;\n",loop_index_new->next->next->loopIndex->string,count);
	    }
	loop_index_temp = loop_index_new;
	struct Phi_Values *lambda_temp=lambda_var;
	while(loop_index_temp!=NULL)
	{
	    fprintf(out,"\tif((CUDA_L_%s<=%s)&&(%s<=CUDA_U_%s)){\n",loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string);
	    
	    loop_index_temp=loop_index_temp->next;
	}
	fdisplay_StatementNode_1D(parallel_stmt);
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL)
	{
	    fprintf(out, "}");
	    loop_index_temp=loop_index_temp->next;
	}
	fprintf(out, "}\n\n");
}

void TD_kernel_definition_DEPENDENCY(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct StatementNode* parallel_stmt,int count)
{
    struct Stmt_Var* stmt_var_temp, *stmt_temp;
	struct StatementNode* left_var_temp, *var_temp;
	struct StatementNode* read_var_temp;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New* loop_index_temp;
	struct SizeNode* sz;
	int x,i;
	
	fprintf(out, "\n\n// ----------KERNEL DEFINITION----------\n");
	fprintf(out, "\n\n__global__ void _AFFINE_KERNEL_%d(", count);
	stmt_var_temp = stmt_var;
	while(stmt_var_temp!=NULL){
		fdisplay_type(stmt_var_temp->var->type);
		if(stmt_var_temp->var->identifier->size!=NULL) fprintf(out, "*");
		fprintf(out, " ");
		fprintf(out, "%s,",stmt_var_temp->var->identifier->string);
		if(stmt_var_temp->var->identifier->size!=NULL) {
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
	fprintf(out, "int %s, int id_1, int UB_1, int _CUDA_TILE_%d)\n{\n",loop_index_new->loopIndex->string,count);
	if(loop_index_new->next!=NULL)
	{
	    fprintf(out, "\tint %s = gridDim.y*blockDim.y*_CUDA_TILE_%d + blockDim.y*blockIdx.y + threadIdx.y;\n",loop_index_new->next->loopIndex->string,count);
	    if(loop_index_new->next->next!=NULL)
	        fprintf(out, "\tint %s = gridDim.z*blockDim.z*_CUDA_TILE_%d + blockDim.z*blockIdx.z + threadIdx.z;\n",loop_index_new->next->next->loopIndex->string,count);
	    }
	fprintf(out,"\tif((id_1<=%s)&&(%s<=UB_1)){\n",loop_index_new->next->loopIndex->string,loop_index_new->next->loopIndex->string);
	fdisplay_StatementNode_1D(parallel_stmt);
	loop_index_temp = loop_index_new->next;
	while(loop_index_temp!=NULL)
	{
	    fprintf(out, "\t}\n");
	    loop_index_temp=loop_index_temp->next;
	}
	fprintf(out, "}\n\n");
    cuda_kernel_definition_NO_DEPENDENCY(stmt_var,loop_index_new,parallel_stmt,count);
}

/*******************************************************************************************************************************/
