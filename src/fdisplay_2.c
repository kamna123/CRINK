/************************************************
* ANJANA SINGH
* Y8127079
* DEPARTMENT OF COMPUTER SCIENCE AND ENGINNERING
* IIT KANPUR

* CUDA AUTOMATIC CODE GENRATION
* FDISPLAY EVERYTHING
* EXCLUDING TYPE STATIC [NO NEED]
* NOT WORKING YET
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
//#include "cuda_y.h"
#include "fdisplay_2.h"

void fdisplay_find_loopId(struct LoopIndexVar_New* liv){
	if(liv==NULL) return;
	//if(loop_index_new_end!=NULL && liv==loop_index_new_end) return;
	fdisplay_find_loopId(liv->next);
	fprintf(out, "int %s = %s%%_CUDA_U_%s;\n",liv->loopIndex->string,loop_index_new->loopIndex->string,liv->loopIndex->string);
	fprintf(out, "%s = %s/_CUDA_U_%s;\n",loop_index_new->loopIndex->string,loop_index_new->loopIndex->string,liv->loopIndex->string);
}

/*void fdisplay_declare_loopId_end(){
	struct LoopIndexVar_New* liv;
	liv = loop_index_new_end;
}*/ 

void fdisplay_update_loopId(struct LoopIndexVar_New* liv){
	while(liv!=NULL){
		if((strcmp(liv->L->string,"0")!=0 || liv->L->next!=NULL) || (strcmp(liv->D->string,"1")!=0 || liv->D->next!=NULL) || (liv->op=='-')){
		}
		else {
			liv = liv->next;
			continue;
		}
		
		//fdisplay_upperLimitId(liv->loopIndex->string);
		fprintf(out, "%s = ",liv->loopIndex->string);
		if(strcmp(liv->L->string,"0")!=0 || liv->L->next!=NULL) {
			fdisplay_lowerLimitId(liv->loopIndex->string);
			fprintf(out, " %c ", liv->op);
		}
		else if(liv->op=='-'){
			fprintf(out, "-");
		}
		fprintf(out, "%s",liv->loopIndex->string);
		if(strcmp(liv->D->string,"1")!=0 || liv->D->next!=NULL) {
			fprintf(out, "*");
			fdisplay_differenceId(liv->loopIndex->string);
		}
		fprintf(out, ";\n");
		liv = liv->next;
		
	}
}


void fdisplay_updated_loop_index(char* string,struct LoopIndexVar_New* loop_index_new ){
	struct LoopIndexVar_New* liv;
	liv = loop_index_new;
	while(liv!=NULL){
		if(strcmp(string,liv->loopIndex->string)==0){
			if((strcmp(liv->L->string,"0")!=0 || liv->L->next!=NULL) || (strcmp(liv->D->string,"1")!=0 || liv->D->next!=NULL) || (liv->op=='-')){
				fprintf(out, "(");
			}
			/*else {
				fprintf(out, "%s", liv->loopIndex->string);
				break;
			}*/
			if(strcmp(liv->L->string,"0")!=0 || liv->L->next!=NULL) {
				fdisplay_lowerLimitId(liv->loopIndex->string);
				fprintf(out, " %c ", liv->op);
			}
			else if(liv->op=='-'){
				fprintf(out, "-");
			}
			fprintf(out, "%s",liv->loopIndex->string);
			if(strcmp(liv->D->string,"1")!=0 || liv->D->next!=NULL) {
				fprintf(out, "*");
				fdisplay_differenceId(liv->loopIndex->string);
			}
			if((strcmp(liv->L->string,"0")!=0 || liv->L->next!=NULL) || (strcmp(liv->D->string,"1")!=0 || liv->D->next!=NULL) || (liv->op=='-')){
				fprintf(out, ")");
			}
			break;
		}
		liv = liv->next;
	}
	if(liv==NULL) fprintf(out, "%s",string);
}

void fdisplay_SizeNode_updated_loop_index(struct SizeNode* size_node,struct LoopIndexVar_New* loop_index_new){
	while(size_node!=NULL){
		fprintf(out,"[");
		fdisplay_StringNode_updated_loop_index(size_node->sizeString,loop_index_new);
		fprintf(out,"]");
		size_node = size_node->next;
	}
}

void fdisplay_StringNode_updated_loop_index(struct StringNode* str_node,struct LoopIndexVar_New* loop_index_new){
	while(str_node!=NULL){
		if(str_node->size==NULL) fdisplay_updated_loop_index(str_node->string,loop_index_new);
		else{
			fprintf(out,"%s", str_node->string);
			fdisplay_SizeNode_updated_loop_index(str_node->size,loop_index_new);
		}
		str_node = str_node->next;
	}
}


void fdisplay_SizeNode(struct SizeNode* size_node){
	while(size_node!=NULL){
		fprintf(out,"[");
		fdisplay_StringNode(size_node->sizeString);
		fprintf(out,"]");
		size_node = size_node->next;
	}
}

void fdisplay_StringNode(struct StringNode* str_node){
	while(str_node!=NULL){
		fprintf(out,"%s", str_node->string);
		fdisplay_SizeNode(str_node->size);
		str_node = str_node->next;
	}
}


void fdisplay_SizeNode_1D(struct StringNode* str_node){
	struct SizeNode* size_node, *sz;
	int x,i;
	size_node = str_node->size;
	if(size_node==NULL) return;
	fprintf(out,"[");
	while(size_node!=NULL){
		if(size_node->next!=NULL && size_node->sizeString->next!=NULL) fprintf(out,"(");
		fdisplay_StringNode_1D(size_node->sizeString);
		if(size_node->next!=NULL && size_node->sizeString->next!=NULL) fprintf(out,")");
		sz = size_node->next;
		x = 0;
		while(sz!=NULL){
			x++;
			sz = sz->next;
		}
		for(i=x;i>0;i--){
			fprintf(out, "*_SZ_%s_%d",str_node->string,i);
		}
		size_node = size_node->next;
		if(size_node!=NULL) fprintf(out,"+");
	}
	fprintf(out,"]");
}

void fdisplay_StringNode_1D(struct StringNode* str_node){
	while(str_node!=NULL){
		fprintf(out,"%s", str_node->string);
		fdisplay_SizeNode_1D(str_node);
		str_node = str_node->next;
	}
}

void fdisplay_StatementNode_1D(struct StatementNode* stmt){
	while(stmt!=NULL){
	    fprintf(out,"\t\t");
		fdisplay_StringNode_1D(stmt->stringNode);
		fprintf(out, "\n");
		stmt = stmt->next;
	}
}



void fdisplay_type(int t){
	int n = (t/1000)%10;
	//t=t%1000;
	switch(n){
		case 1 : fprintf(out, "const "); break;
	}
	n=(t/100)%10;
	switch(n){
		case 1 : //fprintf(out, "static ");
				 break;
	}
	n = (t/10)%10;
	switch(n){
		case 1 : fprintf(out, "unsigned ");break;
	}
	n = t%10;
	switch(n){
		case 0 : fprintf(out, "void");break;
		case 1 : fprintf(out, "int");break;
		case 2 : fprintf(out, "char");break;
		case 3 : fprintf(out, "double");break;
		case 4 : fprintf(out, "long");break;
		case 5 : fprintf(out, "float");break;
		case 6 : fprintf(out, "short");break;
	}
}



void fdisplay_lowerLimitId(char* string){
	fprintf(out, "_CUDA_L_%s",string);
}
void fdisplay_upperLimitId(char* string){
	fprintf(out, "_CUDA_U_%s",string);
}
void fdisplay_differenceId(char* string){
	fprintf(out, "_CUDA_D_%s",string);
}


void fdisplay_part1(){
	int i = 0;
     
	char c;
	while((c = fgetc(in)) != EOF && i<start_num )
 {
        if (c == '\n') {
        	i++;
       
        }
       
 
        fputc(c, out);
    }
}
void fdisplay_part3()
{
int i=start_num;
char c;
            while((c=fgetc(in))!=EOF && i<end_num){
            if(c=='\n')
               {i++;}
               fputc(c,out);
}}
/*void fdisplay_part2(){
	int i = 0;
	char c;
	while(i!=end_num-2 && (c = fgetc(in)) != EOF) {
        if (c == '\n') {
        	i++;
        	if(i==end_num-2) break;
        }
    }
       
}*/
void fdisplay_part2(){
	int i = 0;
	char c;
	while(i!=end_num && (c = fgetc(in)) != EOF) {
        if (c == '\n') {
        	i++;
        	if(i==end_num-2) break;
        }
    }
    while((c = fgetc(in)) != EOF) {
       	fputc(c, out);
    }   
}
void end()
{
fprintf(out,"}");
}

