#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
//#include "cuda_y.h"
#include "CodeGen_ExtendedCycleShrinking.h"
#include "fdisplay_2.h"

/************************************** KERNEL DECLARATION CODE GENERATION ****************************************************/
void ExtendedShrinking_kernel_declaration_DEPENDENCY(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,int count)
{
   struct Stmt_Var* stmt_var_temp, *stmt_temp;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New* loop_index_temp;
	struct SizeNode* sz;
	int x,i;
	fprintf(out,"#ifndef DATASET\n\t#define _NTHREAD 512\n\t#define _NBLOCK 65535\n#endif\n\n");
	fprintf(out, "#include<cuda.h>\n#include<time.h>\n");
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
	fprintf(out, "int );\n\n#define MIN(a,b) (((a)<(b))?(a):(b))\n#include<cuda.h>\n"); // for CUDA_TILE 
}

/****************************************************************************************************************************/

/***************************************** KERNEL CALL CODE GENERATION ******************************************************/
void extCS_ConstantDistance_AFFINE(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct Stmt_Var* write_stmt_var,int count)
{
    struct Stmt_Var* stmt_var_temp;
	struct StatementNode* var_temp;
	struct Stmt_Var *stmt_temp,*max_size_stmt=NULL;
	struct StatementNode* parallel_stmt_temp;
	struct LoopIndexVar_New *loop_index_temp, *loop_temp,*loop_id;
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
	// DEVELOPER VARIABLEs
	
	fprintf(out, "\n\t// ----------Allocating memory to Kernel Variable and copying them on device----------\n");
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
    struct Phi_Values *lambda,*lambda_temp;
    fprintf(out,"\tint ID_1_%d, ID_2_%d, START_%d[%d];\n",count,count,count,id_max);
    fprintf(out, "\tint _CUDA_TILE_%d;\n",count);
    fprintf(out,"\tint Phi_%d[%d]={",count,noOfNestedLoops);
    lambda=lambda_var;
    while(lambda)
    {
        fprintf(out,"%d",lambda->phi_val);
        lambda=lambda->next;
        if(lambda)  fprintf(out,", ");
        else    fprintf(out,"};\n");
    }
    fprintf(out,"\tint loopUpperLimits_%d[%d]={",count,noOfNestedLoops);
    loop_temp=loop_index_new;
    while(loop_temp)
    {
        fprintf(out,"%s",loop_temp->U->string);
        loop_temp=loop_temp->next;
        if(loop_temp)  fprintf(out,", ");
        else    fprintf(out,"};\n");
    }
    fprintf(out,"\tfor(ID_1_%d=1;ID_1_%d<=",count,count);
    lambda=lambda_var;
    int minCount=0;
    loop_temp=loop_index_new;
    while(loop_temp)
    {
        if(loop_temp->next)
        {
            fprintf(out,"MIN(%s/%d, ",count,loop_temp->U->string,lambda->phi_val);
            minCount++;
        }
        else
        {
            fprintf(out,"%s/%d",loop_temp->U->string,lambda->phi_val);
            while(minCount--)
                fprintf(out,")");
        }
        lambda=lambda->next;
        loop_temp=loop_temp->next;
    }
    fprintf(out,"+1;ID_1_%d++)\n\t{\n",count);
    fprintf(out,"\t\tfor(ID_2_%d=0;ID_2_%d<%d;ID_2_%d++)\n\t\t{\n",count,count,noOfNestedLoops,count);
    fprintf(out,"\t\t\tif(Phi_%d[ID_2_%d]>=0)\n\t\t\t\tSTART_%d[ID_2_%d]=(ID_1_%d-1)*Phi_%d[ID_2_%d];\n\t\t\telse\n\t\t\t\tSTART_%d[ID_2_%d]=loopUpperLimits_%d[ID_2_%d]+(ID_1_%d-1)*Phi_%d[ID_2_%d];\n",count,count,count,count,count,count,count,count,count,count,count,count,count,count);
    fprintf(out,"\t\t}\n");
    int r=0;
    lambda=lambda_var;
    loop_temp=loop_index_new;
    while(r<noOfNestedLoops)
    {
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
	    
	    loop_id=loop_index_new;
	    lambda_temp=lambda_var;
	    i=0;
	    while(i<noOfNestedLoops)
	    {   
	        if(i<r)
	            fprintf(out,"START_%d[%d]+%d, %s, ",count,i,lambda_temp->phi_val,loop_id->U->string);
	        else if(i>r)
	            fprintf(out,"START_%d[%d], %s, ",count,i,loop_id->U->string);
	        else
	            fprintf(out,"START_%d[%d], MIN(START_%d[%d]+%d, %s), ",count,r,count,r,lambda->phi_val,loop_temp->U->string);
	        lambda_temp=lambda_temp->next;
	        loop_id=loop_id->next;
	        i++;
	    }
	    fprintf(out,"_CUDA_TILE_%d);\n",count);
	    fprintf(out,"\t\t\tcudaDeviceSynchronize();\n\t\t}\n");
	    lambda=lambda->next;
	    loop_temp=loop_temp->next;
	    r++;
    }
    fprintf(out,"\t}\n");
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
 
void extCS_VariableDistance_AFFINE(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new,struct Stmt_Var* write_stmt_var,int count)
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
    fprintf(out,"\tint _CUDA_TILE_%d;\n\tint ",count);
	int temp=1;
	while(temp<=noOfNestedLoops)
	{
	    fprintf(out,"ID_%d_%d=0, next_ID_%d_%d", temp,count,temp,count);
	    if(temp<noOfNestedLoops)    fprintf(out,", ");
	    else    fprintf(out,";\n");
	    temp++;
	}
	fprintf(out,"\twhile(");
	temp=1;
	loop_temp=loop_index_new;
	while(loop_temp)
	{
	    fprintf(out,"(ID_%d_%d<%s)",temp,count,loop_temp->U->string);
	    if(temp<noOfNestedLoops)    fprintf(out,"&&");
	    else    fprintf(out,")\n\t{\n");
	    temp++;
	    loop_temp=loop_temp->next;
	}
	temp=1;
	int count1,minCount=0;
	loop_temp=loop_index_new;
	struct ReferencePair *refPairTemp;
	struct DDV *DDVtemp;
	struct DDV_Values *DDVtempValues;
	while(loop_temp)
	{
	    fprintf(out,"\t\tnext_ID_%d_%d = ",temp,count);
	    minCount=0;
	    refPairTemp=RefPair;
	    while(refPairTemp)
	    {
	        if(refPairTemp->next)
	        {
	            fprintf(out,"MIN(");
	            minCount++;
	        }
	        count1=1;
	        DDVtemp=refPairTemp->ddv;
	        while(count1!=temp)
	        {
	            count1++;
	            DDVtemp=DDVtemp->next;
	            }
	        fprintf(out,"(((%d)",DDVtemp->ddv_values->value);
	        DDVtempValues=DDVtemp->ddv_values->next;
	        count1=1;
	        while(DDVtempValues)
	        {
	            if(DDVtempValues->next==NULL)   fprintf(out,")/(%d))",DDVtempValues->value);
	            else
	            {
	                fprintf(out,"+(%d)*ID_%d_%d",DDVtempValues->value,count1,count);
	                count1++;
	                }
	            DDVtempValues=DDVtempValues->next;
	        }
	        refPairTemp=refPairTemp->next;
	        if(refPairTemp) fprintf(out,", ");
	        else
	            while(minCount--)
	                fprintf(out,")");
	    }
	    fprintf(out,";\n");
	    temp++;
	    loop_temp=loop_temp->next;
	}
	if(noOfNestedLoops==1)
	{
	   fprintf(out, "\tfor(_CUDA_TILE_%d=0;_CUDA_TILE_%d<_NUM_TILE_%d;_CUDA_TILE_%d++)\n\t{",count,count,count,count);
	fprintf(out, "\n\t\t// ----------KERNEL LAUNCH----------\n");
	fprintf(out, "\t\t_AFFINE_KERNEL_%d<<<_BLOCKS_%d,_THREADS_%d>>>(",count,count,count);
	    stmt_var_temp = stmt_var;
	    while(stmt_var_temp!=NULL){
		    if(stmt_var_temp->var->identifier->size!=NULL) fprintf(out, "_DEV_");
		    fprintf(out, "%s%d, ",stmt_var_temp->var->identifier->string,count);
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
	    fprintf(out,"ID_1_%d, MIN(next_ID_1_%d,%s), _CUDA_TILE_%d);\n",count,count,loop_index_new->U->string,count);
	    fprintf(out,"\t\t\tcudaDeviceSynchronize();\n\t\t}\n");
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
	    fprintf(out,"next_ID_1_%d, %s, _CUDA_TILE_%d);\n",count,loop_index_new->U->string,count);
        fprintf(out,"\t\t\tcudaDeviceSynchronize();\n\t\t}\n");
	}
	else if(noOfNestedLoops==2)
	{
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
	    fprintf(out,"ID_1_%d, MIN(next_ID_1_%d, %s), ID_1_%d, %s, _CUDA_TILE_%d);\n",count,count,loop_index_new->U->string,count,loop_index_new->next->U->string,count);
	     fprintf(out,"\t\t\tcudaDeviceSynchronize();\n\t\t}\n");
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
	    fprintf(out,"next_ID_1_%d, %s, ID_2_%d, MIN(next_ID_2_%d, %s), _CUDA_TILE_%d);\n",count,loop_index_new->U->string,count,count,loop_index_new->next->U->string,count);
	     fprintf(out,"\t\t\tcudaDeviceSynchronize();\n\t\t}\n");
	}
	temp=1;
	while(temp<=noOfNestedLoops)
	{
	    fprintf(out,"\t\tID_%d_%d=next_ID_%d_%d;\n", temp,count,temp,count);
	    temp++;
	}
	fprintf(out,"\t}\n");
	
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
void ExtendedShrinking_kernel_definition_DEPENDENCY(struct Stmt_Var* stmt_var,struct LoopIndexVar_New* loop_index_new, struct StatementNode* parallel_stmt,int count)
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
	loop_index_temp = loop_index_new;
	while(loop_index_temp!=NULL){
	    fprintf(out,"int CUDA_L_%s_%d,int CUDA_U_%s_%d, ",loop_index_temp->loopIndex->string,count,loop_index_temp->loopIndex->string,count);
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
	    fprintf(out,"\tif((CUDA_L_%s_%d<=%s)&&(%s<=CUDA_U_%s_%d)){\n",loop_index_temp->loopIndex->string,count,loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string,loop_index_temp->loopIndex->string,count);
	    
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
