/************************************************
* ANJANA SINGH
* Y8127079
* DEPARTMENT OF COMPUTER SCIENCE AND ENGINNERING
* IIT KANPUR

* CUDA AUTOMATIC CODE GENRATION
* CALCULATES WRITE LEFT READ VAR
* CLACULATES LOOP INDEX VAR START AND END
* WORKING
************************************************/


#include <stdio.h>

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "cuda_y.h"
#include "dependency_abstraction_2.h"


//read1=NULL;
//removing loop index variables from variables
void remove_LoopIndexVar(){
	struct LoopIndexVar* loop_index_temp;
	loop_index_temp = loop_index; 
	variables_temp = variables;
	while(loop_index_temp!=NULL){
		variables_temp = variables;
		while(variables_temp!=NULL){
			if(strcmp(variables_temp->identifier->string, loop_index_temp->loopIndex->string)==0){
				if(variables_temp->next!=NULL){
					variables_temp->type = variables_temp->next->type;
					variables_temp->identifier = variables_temp->next->identifier;
					variables_temp->next = variables_temp->next->next;
				}
				else{
					variables_temp->identifier = NULL;
				}
				//break;
			}
			variables_temp = variables_temp->next;
		}
		loop_index_temp = loop_index_temp->next;
	}
	variables_temp = variables;
	if(variables_temp!=NULL || variables_temp->identifier==NULL) {
		variables==NULL;
		return;
	}
	while(variables_temp->next!=NULL){
		if(variables_temp->next->identifier==NULL){
			variables_temp->next=NULL;
			break;
		}
		variables_temp = variables_temp->next;
	}
}

void remove_LoopIndexVar_New(struct LoopIndexVar_New* loop_index_new){
	struct LoopIndexVar_New* loop_index_temp;
	loop_index_temp = loop_index_new;
	variables_temp = variables;
	while(loop_index_temp!=NULL){
		variables_temp = variables;
		while(variables_temp!=NULL){
			if(strcmp(variables_temp->identifier->string, loop_index_temp->loopIndex->string)==0){
				if(variables_temp->next!=NULL){
					variables_temp->type = variables_temp->next->type;
					variables_temp->identifier = variables_temp->next->identifier;
					variables_temp->next = variables_temp->next->next;
				}
				else{
					variables_temp->identifier = NULL;
				}
				//break;
			}
			variables_temp = variables_temp->next;
		}
		loop_index_temp = loop_index_temp->next;
	}
	variables_temp = variables;
	if(variables_temp==NULL || variables_temp->identifier==NULL) {
		variables==NULL;
		return;
	}
	variables_temp = variables;
	while(variables_temp!=NULL && variables_temp->next!=NULL){
		if(variables_temp->next->identifier==NULL){
			variables_temp->next=NULL;
			printf("caught!!\n");
			break;
		}
		variables_temp = variables_temp->next;
	}
}
void add_read_varibales_loop(struct StatementNode* data)
{  //printf("number\n");
   struct Count_Loops* temp2=head;
   if(temp2->read_var==NULL)
    temp2->read_var=data;
   else
   {
   while(temp2->read_var!=NULL)
       temp2=temp2->next;
      temp2->read_var=data;
   }
}

// finding left_var, read_var
void add_write_varibales_loop()
{ struct Count_Loops* temp=head;
        if(temp)
        {
	get_dependency_var(temp->parallel_stmt);
        temp->read_var=read_var;
        temp->write_var=write_var;
        temp=temp->next;
        read_var=NULL; write_var=NULL;
        left_var=NULL;
        }
}
void get_dependency_var(struct StatementNode* parallel_stmt){
	struct StatementNode *stmt_node, *left_temp, *temp;
	stmt_node = parallel_stmt;
	temp = left_var;
         
	//Write variables are in left_var
	while(stmt_node!=NULL){
		left_temp = (struct StatementNode*)malloc(sizeof(struct StatementNode));
		left_temp->stringNode = stmt_node->stringNode;
		left_temp->next = NULL;
		/*if(left_var==NULL) left_var=left_temp;
		else{
			temp = left_var;
			while(temp->next!=NULL) temp = temp->next;
			temp->next = left_temp;
			
		}*/
		left_temp->next = left_var;
		left_var = left_temp;
		/********/
		stmt_node = stmt_node->next;
	}
	//Read dependent variables are in read_var
	//Parallel Statement Variables are in stmt_var
	stmt_node = parallel_stmt;
	while(stmt_node!=NULL){
		get_read_var(stmt_node->stringNode);
		stmt_node = stmt_node->next;
	}
        
	get_write_var();
}
// read_var
void get_read_var(struct StringNode* sn){
	struct SizeNode* szn;
	struct Stmt_Var* stmt_var_temp;
	struct StatementNode* left_var_temp;
	//printf("\n");
       
	while(sn!=NULL){
	
		if((sn->string[0]-'a' <26 && sn->string[0]-'a' >= 0) || (sn->string[0]-'A' <26 && sn->string[0]-'A' >= 0)) {// printf("string is %s",sn->string);
                 }
		else{
                  //   printf("char is in else loop %s\n",sn->string);
			sn = sn->next;
			continue;
		}
		//search sn->string in identifiers list: variables
		variables_temp=variables;
		stmt_var_temp = stmt_var;
                // printMessage(8,"\n-------------------- List of Loop Statement Variables(stmt_var)1\n");
	//display_Stmt_Var(8,stmt_var);
		while(variables_temp!=NULL){
                //  printMessage(8,"\n-------------------- inside loop\n");
                  //  printf("variable string is %s",variables_temp->identifier->string);
			if(strcmp(variables_temp->identifier->string, sn->string)==0)
                       {
				while(stmt_var_temp!=NULL)
                                {
                                //    printMessage(8,"\n-------------------- inside inside loop\n");
					if(variables_temp==stmt_var_temp->var) break;
					stmt_var_temp = stmt_var_temp->next;
				}
				if(stmt_var_temp==NULL)
                                 {
                                    //  printMessage(8,"\n-------------------- inside 3 loop\n");
					stmt_var_temp = (struct Stmt_Var*)malloc(sizeof(struct Stmt_Var));
					//printf("%s  ",variables_temp->identifier->string);
					stmt_var_temp->var=variables_temp;
					stmt_var_temp->next = stmt_var;
					stmt_var = stmt_var_temp;
				}
				break;
			}
                     //  printMessage(8,"\n--------------------after break\n");
			variables_temp = variables_temp->next;
		}
               // printMessage(8,"\n--------------------out of break\n");
               //  if(sn->next!=NULL)
                 //printf("after out of  break in loop variable string is %s\n",sn->next->string);
		//search sn->string in left_vars: for read dependency
		if((sn->next==NULL) || (sn->next!=NULL && strcmp(sn->next->string, "=")!=0)) {
                    //    printMessage(8,"\n--------------------after break in loop\n");
                      //  if(sn->next!=NULL)
                      //   printf("after break in loop variable string is %s",sn->next->string);
			left_var_temp = left_var;
                        //  printMessage(8,"\n-------------------- List of left_var_temp(stmt_var)1\n");
	                 //  display_Stmt_Var(8,left_var_temp);
			while(left_var_temp!=NULL){
                          //   printf("left_var_temp->stringNode->string %s\n",left_var_temp->stringNode->string);
                           //  printf("sn->string %s\n",sn->string);
				if(strcmp(left_var_temp->stringNode->string, sn->string)==0){
					left_var_temp = (struct StatementNode*)malloc(sizeof(struct StatementNode));
					left_var_temp->stringNode = sn;
					left_var_temp->next = read_var;
					read_var = left_var_temp;
					break;
				}
				left_var_temp = left_var_temp->next;
			}
		}
		/***************/
		szn = sn->size;
		while(szn!=NULL){
			get_read_var(szn->sizeString);
			szn = szn->next;
		}
		sn = sn->next;
	}
}

// write_var
void get_write_var(){
	struct StatementNode* left_temp;
	struct StatementNode* read_temp;
	
	left_temp = left_var;
	while(left_temp!=NULL){
		read_temp = read_var;
		while(read_temp!=NULL){
			if(strcmp(read_temp->stringNode->string,left_temp->stringNode->string)==0) {
				read_temp = (struct StatementNode*)malloc(sizeof(struct StatementNode));
				read_temp->stringNode = left_temp->stringNode;
				read_temp->next = write_var;
				write_var = read_temp;
				break;
			}
			read_temp = read_temp->next;
		}
		left_temp = left_temp->next;
	}
	
	
}
void get_left_read_write_stmt_var(struct StatementNode* read_var,struct StatementNode* write_var,struct StatementNode* left_var,struct Stmt_Var* stmt_var){
	struct StatementNode* var_temp;
	struct Stmt_Var* stmt_temp;
	struct Stmt_Var* temp;
	var_temp = left_var;
	while(var_temp!=NULL){
		stmt_temp = left_stmt_var;
		while(stmt_temp!=NULL){
			if(strcmp(var_temp->stringNode->string,stmt_temp->var->identifier->string)==0) break;
			stmt_temp = stmt_temp->next;
		}
		if(stmt_temp==NULL){
			
			temp = stmt_var;
			while(temp!=NULL){
				if(strcmp(temp->var->identifier->string,var_temp->stringNode->string)==0) {
					stmt_temp = (struct Stmt_Var*)malloc(sizeof(struct Stmt_Var));
					stmt_temp->var = temp->var;
					stmt_temp->next = left_stmt_var;
					left_stmt_var = stmt_temp;
					break;
				}
				temp = temp->next;
			}
		}		
		var_temp = var_temp->next;
	}
	
	var_temp = read_var;
	while(var_temp!=NULL){
		stmt_temp = read_stmt_var;
		while(stmt_temp!=NULL){
			if(strcmp(var_temp->stringNode->string,stmt_temp->var->identifier->string)==0) break;
			stmt_temp = stmt_temp->next;
		}
		if(stmt_temp==NULL){
			temp = stmt_var;
			while(temp!=NULL){
				if(strcmp(temp->var->identifier->string,var_temp->stringNode->string)==0) {
					stmt_temp = (struct Stmt_Var*)malloc(sizeof(struct Stmt_Var));
					stmt_temp->var = temp->var;
					stmt_temp->next = read_stmt_var;
					read_stmt_var = stmt_temp;
					break;
				}
				temp = temp->next;
			}
			
		}		
		var_temp = var_temp->next;
	}
	
	var_temp = write_var;
	while(var_temp!=NULL){
		stmt_temp = write_stmt_var;
		while(stmt_temp!=NULL){
			if(strcmp(var_temp->stringNode->string,stmt_temp->var->identifier->string)==0) break;
			stmt_temp = stmt_temp->next;
		}
		if(stmt_temp==NULL){
			
			temp = stmt_var;
			while(temp!=NULL){
				if(strcmp(temp->var->identifier->string,var_temp->stringNode->string)==0) {
					stmt_temp = (struct Stmt_Var*)malloc(sizeof(struct Stmt_Var));
					stmt_temp->var = temp->var;
					stmt_temp->next = write_stmt_var;
					write_stmt_var = stmt_temp;
					break;
				}
				temp = temp->next;
			}
		}		
		var_temp = var_temp->next;
	}
	
}

int is_match(char* id, struct StringNode* str){
	int a;
	struct SizeNode* sz;
	while(str!=NULL){
		if(strcmp(id, str->string)==0) return 1;
		sz = str->size;
		while(sz!=NULL){
			a = is_match(id,sz->sizeString);
			if(a==1) return 1;
			sz = sz->next;
		}
		str = str->next;
	}

	return 0;
}

int get_loop_index_dep(char* id){
	struct StatementNode* temp;
	struct StringNode* str;
	struct SizeNode* sz;
	int a;
	temp = left_var;
	while(temp!=NULL){
		sz = temp->stringNode->size;
		while(sz!=NULL){
			a = is_match(id,sz->sizeString);
			if(a==1) return 1;
			sz = sz->next;	
		}
			
		temp = temp -> next;
	}
	return 0;
	
}

void get_loop_index_start_end(){
	struct LoopIndexVar_New* temp;
	temp = loop_index_new;
	while(temp!=NULL){
		if(get_loop_index_dep(temp->loopIndex->string))	{
			loop_index_new_start = temp;
			break;
		}
		temp = temp -> next;
	}
	while(temp!=NULL){
		if(get_loop_index_dep(temp->loopIndex->string))
			loop_index_new_end = temp->next;
		temp = temp -> next;
	}
	
}

