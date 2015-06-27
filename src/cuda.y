/************************************************
* ANJANA SINGH
* Y8127079
* DEPARTMENT OF COMPUTER SCIENCE AND ENGINNERING
* IIT KANPUR

* CUDA AUTOMATIC CODE GENRATION [YACC FILE]
* LOOP INDEX VARIABLES: LoopIndexVar_New
* CALCULATES ALL PARALLELIZABLE LOOP
* GENERATES CODE FOR ONLY ONE LOOP
* CALCULATES LOOP INDEX START AND END
* WORKING
************************************************/


%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "src/cuda_y.h"
/*#include "dependency_abstraction_2.h"
#include "Loop_Normalization.h"
#include "AffineTest.h"
#include "GCD_Banerjee_Test.h"
#include "Dependence_Testing_Interface.h"
#include "Omega_Test.h"
#include "Cycle_Shrinking.h"
#include "ExtendedCS.h"
#include "CodeGen_AffineKernel_Interface.h"
#include "CodeGen_CycleShrinking.h"
#include "CodeGen_ExtendedCycleShrinking.h"
#include "CodeGen_1_only_WAW.h"
#include "fdisplay_2.h"*/
#include <string.h>
#include<getopt.h>
#define LEFT 1;
static int count_loop=0;
#define RIGHT 0;

int yylex(void);
void yyerror(char *);
//Functions:

void insert_variables(int type, struct StringNode* identifier,struct StringNode* value){
	variables_temp = variables;
	if(variables==NULL) {
		variables = (struct Var*)malloc(sizeof(struct Var));
		variables_temp = variables;
	}
	else {
		variables_temp = variables;
		while(variables_temp->next !=NULL) variables_temp = variables_temp->next;
		variables_temp->next = (struct Var*)malloc(sizeof(struct Var));
		variables_temp = variables_temp->next;
	}
	variables_temp->type = type;
	variables_temp->identifier = identifier;
	variables_temp->var_value=(value!=NULL)?atoi(value->string):-1;
	variables_temp->next = NULL;
}

void merge_StringNode(struct StringNode* sn1, struct StringNode* sn2){ 
	if(sn1==NULL){
		sn1 = sn2;
		return;
	}
	if(sn2==NULL) return;
	while(sn1->next!=NULL) sn1 = sn1->next;
	sn1->next = sn2;
}

void merge_StringNode1(struct StringNode** sn1, struct StringNode* sn2){ 
	if(*sn1==NULL){
		*sn1 = sn2;
		return;
	}
	if(sn2==NULL) return;
	struct StringNode* sn;
	sn = *sn1;
	while(sn->next!=NULL) sn = sn->next;
	sn->next = sn2;
}
void add_into_loop_loop_index_new(struct LoopIndexVar_New* loop)
{         struct Count_Loops* temp=head;
         if(head->loop_index_new==NULL)
               {
                 head->loop_index_new=loop;
               }
           else
            { while(temp->loop_index_new!=NULL)
                  temp=temp->next;
                  temp->loop_index_new=loop;
            }
     //remove_LoopIndexVar_New(loop);
}
void remove_loop_index_variables_from_stmt_var(struct Stmt_Var* stmt_var)
{      struct Stmt_Var* temp=stmt_var;
       struct Stmt_Var* prev=temp;
                  while(temp)
                 {
                     
                        if(temp->var->identifier->size==NULL)
                          { prev->next=temp->next;
                           } 
                     prev=temp;
                    temp=temp->next;
                 }
}
void add_into_loop_parallel_stmt(struct StatementNode* data)
{            struct Count_Loops* node=(struct Count_Loops*)malloc(sizeof(struct Count_Loops));
                
                  node->parallel_stmt=data;
                remove_LoopIndexVar_New(node->loop_index_new);
                 
                 get_dependency_var(data);
                  
                 remove_loop_index_variables_from_stmt_var(stmt_var);  
                   node->count=count_loop++;
                    node->left_var=left_var;
                  node->write_var=write_var;
                node->read_var=read_var;
                 
                 
                  node->stmt_var=stmt_var;
                  
      /*printf("----------------inside LOOP-------------------- \n");
         printf("----------------inside LOOP(read)-------------------- \n");
                  display_StatementNode(8,read_var);
     printf("----------------inside LOOP(write)-------------------- \n");
                  display_StatementNode(8,write_var);
    printf("----------------inside LOOP(left_var)-------------------- \n");
                  display_StatementNode(8,left_var);
    printf("----------------inside LOOP(stmt_var)-------------------- \n");
                  display_Stmt_Var(8,stmt_var);*/
          get_left_read_write_stmt_var( read_var, write_var, left_var, stmt_var);
                   node->left_stmt_var=left_stmt_var;
                    node->write_stmt_var=write_stmt_var;
                    node->read_stmt_var=read_stmt_var;
                 node->loop_index=NULL;
                node->lambda_var=NULL;
                write_var=NULL;
                read_var=NULL;
                 left_var=NULL;
                
               parallel_stmt=NULL;
               stmt_var=NULL;
               left_stmt_var=NULL;
               write_stmt_var=NULL;
               read_stmt_var=NULL;
               node->variables=variables;
                node->loop_index_new=NULL;
                   node->next=NULL;
            if(head==NULL)
                  {
                    head=node;
                  }  
             else
               { struct Count_Loops* temp=head;
               while(temp->next!=NULL)
                 temp=temp->next;
                  temp->next=node;
                //node->next=head;
                //head=node;
               }
           
                 
}

struct LoopIndexVar_New* add_loop_index_new(struct StringNode* id, struct StringNode* lb, struct StringNode* ub, struct StringNode* d, char op, int relop){
	struct LoopIndexVar_New* liv = (struct LoopIndexVar_New*)malloc(sizeof(struct LoopIndexVar_New));
       // if(count_loop>0)
        //loop_index_new=NULL;
	liv->loopIndex = id;
	liv->L=lb;
	liv->U=ub;
	liv->D=d;
	liv->op = op;
	liv->relop = relop;
	liv->next = loop_index_new;
         
        
	loop_index_new = liv;
         //remove_LoopIndexVar_New(loop_index_new);
      // add_into_loop_loop_index_new(loop_index_new);
       return loop_index_new;
}

// no use
create_parallel_data(struct ParallelData** pd){
	struct ParallelData* temp;
	temp = (struct ParallelData*)malloc(sizeof(struct ParallelData));
	temp->loop_index = loop_index_new;
	temp->parallel_stmt = parallel_stmt;
	temp->left_var = NULL;
	temp->write_var = NULL;
	temp->read_var = NULL;
	temp->stmt_var = NULL;
	temp->left_stmt_var = NULL;
	temp->write_stmt_var = NULL;
	temp->read_stmt_var = NULL;
	temp->start_num = start_num;
	temp->end_num = end_num;
	temp->next = NULL;
	*pd = temp;
}

reset_parallel(){
	loop_index_new = NULL;
	parallel_stmt = NULL;
}


%}

%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME 

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%token PARALLEL_START PARALLEL_END HASH_INCLUDE HASH_DEFINE  PRINTF TYPE_OP

%union {
	int NUM;
	struct SizeNode* Arr_size;
	struct StringNode* stringNode;
	struct StatementNode* stmtNode;
	struct LoopIndexVar* liv;
	struct ParallelData* pd;
}

%type <NUM> TYPE 
%type <NUM> POINTER 
%type <Arr_size> ARRAY_DATA_LIST
%type <stringNode> IDENTIFIER  CONSTANT ARRAY_IDENTIFIER E OPEN_PAREN CLOSE_PAREN
%type <stringNode> PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%type <stringNode> AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%type <stringNode> SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%type <stringNode> XOR_ASSIGN OR_ASSIGN 
%type <stringNode> UNARY_OP ASSIGN_OP OP SEMI_COLON IDENTIFIER_INC  TYPE_OP 
%type <stmtNode> DEF STATEMENT BODY
%type <pd> PARALLEL_FOR


%start FILE


%%

FILE: STATEMENT FILE
    | DEFINITION FILE
    |
    | PARALLEL_FOR FILE {$1->next = parallel_data; parallel_data = $1;}
;

DEFINITION: TYPE IDENTIFIER ';'                       {insert_variables($1,$2,NULL);}
          | TYPE ARRAY_IDENTIFIER ';'                 {insert_variables($1,$2,NULL);}
          | TYPE IDENTIFIER '=' E ';'                 {insert_variables($1,$2,$4);}
          | TYPE ARRAY_IDENTIFIER '=' E ';'           {insert_variables($1,$2,$4);}
          | TYPE MANY_DEF ';'
          | FUNC_DECL ';'
;

FUNC_DECL: TYPE IDENTIFIER '(' ')'
         | TYPE IDENTIFIER '(' ARGUMENTS
;

ARGUMENTS: ONLY_TYPE
         | TYPE_IDENTIFIER
;

ONLY_TYPE: TYPE ')'
         | TYPE ',' ONLY_TYPE
;

TYPE_IDENTIFIER: TYPE IDENTIFIER ')'
               | TYPE ARRAY_IDENTIFIER ')'
               | TYPE IDENTIFIER ',' TYPE_IDENTIFIER
               | TYPE ARRAY_IDENTIFIER ',' TYPE_IDENTIFIER
;

MANY_DEF: IDENTIFIER                             {insert_variables(type,$1,NULL);}
        | ARRAY_IDENTIFIER                       {insert_variables(type,$1,NULL);}
        | IDENTIFIER '=' E                       {insert_variables(type,$1,$3);}
        | ARRAY_IDENTIFIER '=' E                 {insert_variables(type,$1,$3);}
        | IDENTIFIER ',' MANY_DEF                {insert_variables(type,$1,NULL);}
        | POINTER MANY_DEF
        | ARRAY_IDENTIFIER ',' MANY_DEF          {insert_variables(type,$1,NULL);}
        | IDENTIFIER '=' E ',' MANY_DEF          {insert_variables(type,$1,$3);}
        | ARRAY_IDENTIFIER '=' E ',' MANY_DEF    {insert_variables(type,$1,$3);}
;

TYPE: INT       {$$ = 1; type=$$;}
    | CHAR      {$$ = 2; type=$$;}
    | DOUBLE    {$$ = 3; type=$$;}
    | LONG      {$$ = 4; type=$$;}
    | FLOAT     {$$ = 5; type=$$;}
    | SHORT     {$$ = 6; type=$$;}
    | SIGNED    {$$ = 0; type=$$;}
    | UNSIGNED  {$$ = 10; type=$$;}
    | CONST     {$$ = 1000; type=$$;}
    | VOLATILE  {$$ = 0; type=$$;}
    | VOID      {$$ = 0; type=$$;}
    | STATIC    {$$ = 100; type=$$;}
    | AUTO      {$$ = 0; type=$$;}
    | POINTER   {$$ = $1; type=$$;}
    | TYPE TYPE {$$ = $1+$2; type=$$;}  // ex: int * or int ** or long int
;


POINTER: '*'             {$$ = 10000;}
       | '*' POINTER     {$$ = 10000 + $2;}
;

PARALLEL_FOR: PARALLEL_START FORLOOP_1 PARALLEL_END {$$=NULL; 
// no use
create_parallel_data(&$$); reset_parallel();}
;

       
FORLOOP_1: FOR '(' IDENTIFIER  '=' E ';' IDENTIFIER '<' E ';' IDENTIFIER_INC ')' FORLOOP_1_DEF 
            { struct LoopIndexVar_New* temp=add_loop_index_new($3,$5,$9,$11,'+',1); 
               add_into_loop_loop_index_new(temp) ;}
           
         | FOR '(' IDENTIFIER  '=' E ';' IDENTIFIER '>' E ';' IDENTIFIER_INC ')' FORLOOP_1_DEF 
            {struct LoopIndexVar_New* temp=add_loop_index_new($3,$5,$9,$11,'-',2); add_into_loop_loop_index_new(temp) ;}
         | FOR '(' IDENTIFIER  '=' E ';' IDENTIFIER LE_OP E ';' IDENTIFIER_INC ')' FORLOOP_1_DEF 
            {struct LoopIndexVar_New* temp=add_loop_index_new($3,$5,$9,$11,'+',3); add_into_loop_loop_index_new(temp) ;}
         | FOR '(' IDENTIFIER  '=' E ';' IDENTIFIER GE_OP E ';' IDENTIFIER_INC ')' FORLOOP_1_DEF 
            {struct LoopIndexVar_New* temp=add_loop_index_new($3,$5,$9,$11,'-',4); add_into_loop_loop_index_new(temp) ;}
; 

FORLOOP_1_DEF: DEF
             | FORLOOP_1
             | '{' FORLOOP_1 '}'
;

IDENTIFIER_INC: IDENTIFIER ADD_ASSIGN E {$$ = $3;}  //identifier_inc is "d" in LoopIndexVar_New of StringNode type
              | IDENTIFIER SUB_ASSIGN E {$$ = $3;}
              | IDENTIFIER '=' IDENTIFIER '+' E {$$ = $5;}
              | IDENTIFIER '=' IDENTIFIER '-' E {$$ = $5;}
              | IDENTIFIER INC_OP    // ex: a++ it'll create a StringNode type node and copy 1 in it string part
                {   $$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                    $$->string=(char *)malloc(sizeof(char)*2); 
                    strcpy($$->string,"1"); 
                    $$->next = NULL; 
                    $$->size = NULL;}
              | IDENTIFIER DEC_OP 
              {     $$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                    $$->string=(char *)malloc(sizeof(char)*2); 
                    strcpy($$->string,"1"); 
                    $$->next = NULL; 
                    $$->size = NULL;}
              | INC_OP IDENTIFIER  // ex: for ++a it'll create a StringNode type node and copy 1 in it string part
                {   $$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                    $$->string=(char *)malloc(sizeof(char)*2); 
                    strcpy($$->string,"1"); 
                    $$->next = NULL; 
                    $$->size = NULL;}
              | DEC_OP IDENTIFIER 
                {   $$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                    $$->string=(char *)malloc(sizeof(char)*2); 
                    strcpy($$->string,"1"); 
                    $$->next = NULL; 
                    $$->size = NULL;}
;

DEF: '{' BODY '}' {$$=$2; /*if(parallel_flag)*/ parallel_stmt=$$;add_into_loop_parallel_stmt(parallel_stmt); }   //DEF is of statementnode type
   | STATEMENT        {$$=$1; /*if(parallel_flag)*/ parallel_stmt=$$; add_into_loop_parallel_stmt(parallel_stmt);} 
//   | FORLOOP          
//   | '{' FORLOOP '}'  
   ;

BODY: STATEMENT BODY {$1->next = $2; $$=$1;}   //STATEMENT and BODY is of statementnode type
    |                {$$ = NULL;}
    ;

STATEMENT: E SEMI_COLON  {$$=(struct StatementNode*)malloc(sizeof(struct StatementNode)); 
                          $$->next=NULL; 
                          merge_StringNode($1,$2); 
                          $$->stringNode=$1;}
         ;   // ex: for statement "expression ;" then merge two string i.e. expression and semicolon

SEMI_COLON: ';' {$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*2); 
                 strcpy($$->string,";"); 
                 $$->next = NULL; 
                 $$->size = NULL;}
; // create a stringnode and put semicolon in its string part

E: IDENTIFIER ASSIGN_OP E           {merge_StringNode($1,$2);  //ex: a=E then merge a,=,E
                                     merge_StringNode($1,$3); 
                                     $$=$1; /*if(parallel_flag) {add_parallel_var($1,$2);}*/}
 | ARRAY_IDENTIFIER ASSIGN_OP E     {merge_StringNode($1,$2); 
                                     merge_StringNode($1,$3); 
                                     $$=$1; /*if(parallel_flag) {add_parallel_var($1,$2);}*/}
 | E OP E                           {merge_StringNode1(&$1,$2); 
                                     merge_StringNode1(&$1,$3); 
                                     $$=$1;}
 | E UNARY_OP                       {merge_StringNode($1,$2); 
                                     $$=$1;}
 | UNARY_OP E                       {merge_StringNode($1,$2); 
                                     $$=$1;}
 | OPEN_PAREN E CLOSE_PAREN         {merge_StringNode($1,$2); 
                                     merge_StringNode($1,$3); 
                                     $$=$1;}
 | IDENTIFIER                       {$$=$1;}
 | CONSTANT 	                    {$$=$1;}
 | '0'                              {$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                                     $$->string=(char *)malloc(sizeof(char)*2); 
                                     strcpy($$->string,"0"); 
                                     $$->next = NULL; 
                                     $$->size = NULL;}
 | ARRAY_IDENTIFIER                 {$$=$1;}
 |                                  {$$=NULL;}
 | IDENTIFIER OPEN_PAREN E CLOSE_PAREN {merge_StringNode($1,$2); 
                                        merge_StringNode($1,$3); 
                                        merge_StringNode($1,$4); 
                                        $$=$1;}
 | E ',' E 							{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                                     $$->string=(char *)malloc(sizeof(char)*2); 
                                     strcpy($$->string,","); 
                                     $$->next = NULL; 
                                     $$->size = NULL; 
                                     merge_StringNode($1,$$); 
                                     merge_StringNode($1,$3); 
                                     $$=$1;}
 | E '.' E                          {$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                                     $$->string=(char *)malloc(sizeof(char)*2); 
                                     strcpy($$->string,"."); 
                                     $$->next = NULL; 
                                     $$->size = NULL; 
                                     merge_StringNode($1,$$); 
                                     merge_StringNode($1,$3); 
                                     $$=$1;}
 ;


OPEN_PAREN: '(' {$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*2); 
                 strcpy($$->string,"("); 
                 $$->next = NULL; 
                 $$->size = NULL;}
;

CLOSE_PAREN: ')' {$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                  $$->string=(char *)malloc(sizeof(char)*2); 
                  strcpy($$->string,")"); 
                  $$->next = NULL; 
                  $$->size = NULL;}
;

OP: '+'  		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*2); 
                 strcpy($$->string,"+"); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | '-' 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*2); 
                 strcpy($$->string,"-"); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | '*' 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*2); 
                 strcpy($$->string,"*"); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | '/' 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*2); 
                 strcpy($$->string,"/"); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | '%' 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*2); 
                 strcpy($$->string,"%"); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | '&' 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*2); 
                 strcpy($$->string,"&"); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | '|' 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*2); 
                 strcpy($$->string,"|"); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | '^' 	    {$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*2); 
                 strcpy($$->string,"^"); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | LEFT_OP 	{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*3); 
                 strcpy($$->string,"<<"); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | RIGHT_OP    {$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*3); 
                 strcpy($$->string,">>"); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | OR_OP 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*3); 
                 strcpy($$->string,"||"); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | AND_OP 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*3); 
                 strcpy($$->string,"&&"); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | LE_OP 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*3); 
                 strcpy($$->string,"<="); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | GE_OP 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*3); 
                 strcpy($$->string,">="); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | EQ_OP 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*3); 
                 strcpy($$->string,"=="); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | NE_OP 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*3); 
                 strcpy($$->string,"!="); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | '<' 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*2); 
                 strcpy($$->string,"<"); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | '>'         {$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*2); 
                 strcpy($$->string,">"); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | '?'         {$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*2); 
                 strcpy($$->string,"?"); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  | ':'         {$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 $$->string=(char *)malloc(sizeof(char)*2); 
                 strcpy($$->string,":"); 
                 $$->next = NULL; 
                 $$->size = NULL;}
  ;

UNARY_OP: '~'       {$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                     $$->string=(char *)malloc(sizeof(char)*2); 
                     strcpy($$->string,"~"); 
                     $$->next = NULL; 
                     $$->size = NULL;}
       | INC_OP    {$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                    $$->string=(char *)malloc(sizeof(char)*3); 
                    strcpy($$->string,"++"); 
                    $$->next = NULL; 
                    $$->size = NULL;}
       | DEC_OP    {$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                    $$->string=(char *)malloc(sizeof(char)*3); 
                    strcpy($$->string,"--"); 
                    $$->next = NULL; 
                    $$->size = NULL;}
       | '!'       {$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                    $$->string=(char *)malloc(sizeof(char)*2); 
                    strcpy($$->string,"!");
                    $$->next = NULL; 
                    $$->size = NULL;}
       | TYPE_OP   {$$=$1;}
       ;

ASSIGN_OP: '='              {$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             $$->string=(char *)malloc(sizeof(char)*2); 
                             strcpy($$->string,"="); 
                             $$->next = NULL; 
                             $$->size = NULL;}
        | RIGHT_ASSIGN 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             $$->string=(char *)malloc(sizeof(char)*4); 
                             strcpy($$->string,">>="); 
                             $$->next = NULL; 
                             $$->size = NULL;}
        | LEFT_ASSIGN 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             $$->string=(char *)malloc(sizeof(char)*4); 
                             strcpy($$->string,"<<="); 
                             $$->next = NULL; 
                             $$->size = NULL;}
        | ADD_ASSIGN 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             $$->string=(char *)malloc(sizeof(char)*3); 
                             strcpy($$->string,"+="); 
                             $$->next = NULL; 
                             $$->size = NULL;}
        | SUB_ASSIGN 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             $$->string=(char *)malloc(sizeof(char)*3); strcpy($$->string,"-="); 
                             $$->next = NULL; 
                             $$->size = NULL;}
        | MUL_ASSIGN 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             $$->string=(char *)malloc(sizeof(char)*3); 
                             strcpy($$->string,"*="); 
                             $$->next = NULL; 
                             $$->size = NULL;}
        | DIV_ASSIGN 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             $$->string=(char *)malloc(sizeof(char)*3); 
                             strcpy($$->string,"/="); 
                             $$->next = NULL; 
                             $$->size = NULL;}
        | MOD_ASSIGN 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             $$->string=(char *)malloc(sizeof(char)*3); 
                             strcpy($$->string,"%="); 
                             $$->next = NULL; 
                             $$->size = NULL;}
        | AND_ASSIGN 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             $$->string=(char *)malloc(sizeof(char)*3); 
                             strcpy($$->string,"&="); 
                             $$->next = NULL; 
                             $$->size = NULL;}
        | XOR_ASSIGN 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             $$->string=(char *)malloc(sizeof(char)*3); 
                             strcpy($$->string,"^="); 
                             $$->next = NULL; 
                             $$->size = NULL;}
        | OR_ASSIGN 		{$$=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             $$->string=(char *)malloc(sizeof(char)*3); 
                             strcpy($$->string,"|="); 
                             $$->next = NULL; 
                             $$->size = NULL;}
        ;

ARRAY_IDENTIFIER: IDENTIFIER ARRAY_DATA_LIST {$$=$1; $$->size=$2;}
;

ARRAY_DATA_LIST: '[' E ']' ARRAY_DATA_LIST   
                            {$$=(struct SizeNode*)malloc(sizeof(struct SizeNode)); 
                            $$->sizeString=$2; $$->next=$4;}
               | '[' E ']'                   
                            {$$=(struct SizeNode*)malloc(sizeof(struct SizeNode)); 
                            $$->sizeString=$2; 
                            $$->next=NULL;}
;


%%
#include "lex.yy.c"
char DependencyExists='n';
int id_max=0;
int line_num=0;
int start_num=0;
int end_num=0;
int Total_Phi=0;
int type=0;
int noOfNestedLoops=0;
int verbosity=0;
char VariableDependenceDist='n';
char AffineKernel='n';
int flag=0;
struct Var* variables = NULL;
struct Var* original_variables = NULL;
struct Var* variables_temp = NULL;
struct Stmt_Var* stmt_var = NULL;
struct Stmt_Var* left_stmt_var = NULL;
struct Stmt_Var* write_stmt_var = NULL;
struct Stmt_Var* read_stmt_var = NULL;
struct LoopIndexVar* loop_index=NULL;
struct StatementNode* left_var=NULL;
struct StatementNode* write_var=NULL;
struct StatementNode* read_var=NULL;
struct StatementNode* parallel_stmt=NULL;
struct LoopIndexVar_New* loop_index_new=NULL;
struct LoopIndexVar_New* loopIndex_temp=NULL;
struct LoopIndexVar_New* loop_index_new_start = NULL;
struct LoopIndexVar_New* loop_index_new_end = NULL;
struct Phi_Values* lambda_var=NULL;
struct ReferencePair *RefPair=NULL;
struct DDV *DDVvector=NULL;
struct ParallelData* parallel_data = NULL;// no use
struct Count_Loops* head=NULL;

void display_SizeNode(int verbosity_no, struct SizeNode* size_node){  // display [3][4]
	while(size_node!=NULL){
		printMessage(verbosity_no,"[");
		display_StringNode(verbosity_no, size_node->sizeString);
		printMessage(verbosity_no,"]");
		size_node = size_node->next;
	}

}

void display_StringNode(int verbosity_no, struct StringNode* str_node){ //display A[B[
	while(str_node!=NULL){
		printMessage(verbosity_no,"%s", str_node->string);
		display_SizeNode(verbosity_no, str_node->size);
		str_node = str_node->next;
	}
}


void display_StatementNode(int verbosity_no, struct StatementNode* stmt){
	while(stmt!=NULL){
		display_StringNode(verbosity_no, stmt->stringNode);
		printMessage(verbosity_no, "\n");
		stmt = stmt->next;
	}
}
void display_loop_parallel_stmt(int verbosity_no,struct Count_Loops* l)
{     
    while(l!=NULL)
         {  
         
         display_StatementNode(verbosity_no,l->parallel_stmt);
           printMessage(verbosity_no, "\n");
          l=l->next;
         }
         
}
void display_loop_read_var(int verbosity_no,struct Count_Loops* l)
{
            while(l!=NULL)
         { 
        display_StatementNode(verbosity_no,l->read_var);
           printMessage(verbosity_no, "\n");
            l=l->next;
         }
}
void display_loop_write_var(int verbosity_no,struct Count_Loops* l)
{
            while(l!=NULL)
         { 
          display_StatementNode(verbosity_no,l->write_var);
           printMessage(verbosity_no, "\n");
            l=l->next;
         }
}
void display_loop_left_var(int verbosity_no,struct Count_Loops* l)
{
            while(l!=NULL)
         { 
           display_StatementNode(verbosity_no,l->left_var);
           printMessage(verbosity_no, "\n");
            l=l->next;
         }
}
void display_LoopIndexVar(int verbosity_no, struct LoopIndexVar* loop_id){
	while(loop_id!=NULL){
		display_StringNode(verbosity_no, loop_id->loopIndex);
		printMessage(verbosity_no, ":");
		display_StringNode(verbosity_no, loop_id->size);
		printMessage(verbosity_no, "\n");
		loop_id = loop_id->next;
	}
}

void display_LoopIndexVar_New(int verbosity_no, struct LoopIndexVar_New* loop_id){
	while(loop_id!=NULL){
		display_StringNode(verbosity_no, loop_id->loopIndex);
		printMessage(verbosity_no, ": [");
		display_StringNode(verbosity_no, loop_id->L);
		printMessage(verbosity_no, ",");
		display_StringNode(verbosity_no, loop_id->U);
		printMessage(verbosity_no, (loop_id->relop==1) ? ")" : "]");
		printMessage(verbosity_no, "%c",loop_id->op);
		display_StringNode(verbosity_no, loop_id->D);
		printMessage(verbosity_no, "\n");
		loop_id = loop_id->next;
	}
}
 void display_loop_LoopIndexVar_New(int verbosity_no,struct Count_Loops* l)
{ 
               while(l!=NULL)
         { 
         display_LoopIndexVar_New(verbosity_no,l->loop_index_new);
           printMessage(verbosity_no, "\n");
            l=l->next;
         }

}
        
void display_type(int verbosity_no, int t){
	int n = (t/1000)%10;
	//t=t%1000;
	switch(n){
		case 1 : printMessage(verbosity_no, "const"); break;
	}
	n=(t/100)%10;
	switch(n){
		case 1 : printMessage(verbosity_no, "static");break;
	}
	n = (t/10)%10;
	switch(n){
		case 1 : printMessage(verbosity_no, "unsigned");break;
	}
	n = t%10;
	switch(n){
		case 0 : printMessage(verbosity_no, "void");break;
		case 1 : printMessage(verbosity_no, "int");break;
		case 2 : printMessage(verbosity_no, "char");break;
		case 3 : printMessage(verbosity_no, "double");break;
		case 4 : printMessage(verbosity_no, "long");break;
		case 5 : printMessage(verbosity_no, "float");break;
		case 6 : printMessage(verbosity_no, "short");break;
	}
}

void display_Var(int verbosity_no, struct Var* var){
	while(var!=NULL){
		display_type(verbosity_no, var->type);
		printMessage(verbosity_no, ":");
		display_StringNode(verbosity_no, var->identifier);
		printMessage(verbosity_no, "\n");
		var = var->next;
	}
}

void display_Stmt_Var(int verbosity_no, struct Stmt_Var* var){
	while(var!=NULL){
		display_type(verbosity_no, var->var->type);
		printMessage(verbosity_no, ":");
		display_StringNode(verbosity_no, var->var->identifier);
		printMessage(verbosity_no, "\n");
		var = var->next;
	}
}
void display_loop_stmt_var(int verbosity_no,struct Count_Loops* l)
{
            while(l!=NULL)
         {  printf("------------next time--------------\n");
          // remove_LoopIndexVar_New(l->loop_index_new);
          display_Stmt_Var(verbosity_no,l->stmt_var);
           printMessage(verbosity_no, "\n");
         
            l=l->next;
         }
}
void display_loop_read_stmt_var(int verbosity_no,struct Count_Loops* l)
{
            while(l!=NULL)
         { 
          display_Stmt_Var(verbosity_no,l->read_stmt_var);
           printMessage(verbosity_no, "\n");
            l=l->next;
         }
}
void display_loop_write_stmt_var(int verbosity_no,struct Count_Loops* l)
{
            while(l!=NULL)
         { 
          display_Stmt_Var(verbosity_no,l->write_stmt_var);
           printMessage(verbosity_no, "\n");
            l=l->next;
         }
}
void yyerror(char *s) {
	printMessage(10, "ERROR:  %s \n",s);
    fprintf(stderr, "%s\n", s);
    fprintf(stderr, "line %d: %s\n", yylineno, s);
}

void printMessage(int verbosity_no, char *format, ...)
{
   va_list args;
   if(verbosity_no>=verbosity){
       va_start(args, format);
       vprintf(format, args);
       va_end(args);
   }
}

void main(int argc, char* argv[]){
	char* outfile;
	char* infile, *fileName;
	char* dependence_test,*shrinking,*verbosity_no;
	char* affine_flag;
	extern FILE *yyin, *yyout;
	
	dependence_test = (char*)malloc(sizeof(char)*20);
	verbosity_no = (char*)malloc(sizeof(char)*20);
	shrinking = (char*)malloc(sizeof(char)*20);
	infile = (char*)malloc(sizeof(char)*50);
	fileName = (char*)malloc(sizeof(char)*50);
	strcpy(infile,"input/");
	outfile = (char*)malloc(sizeof(char)*50);
	strcpy(outfile,"output/");
	affine_flag=(char*)malloc(sizeof(char)*50);
	verbosity=10;
	strcpy(dependence_test, "gcd");
	strcpy(shrinking, "simple");
	strcpy(affine_flag,"0");
	static struct option long_options[] = {
        {"verbosityLevel",      required_argument,       0,  'v' },
        {"fileName", required_argument,       0,  'f' },
        {"depTest",    required_argument, 0,  'd' },
        {"cycleShrink",   required_argument, 0,  'c' },
        {"loopType",required_argument,0,'l'},
        {0,           0,                 0,  0   }
        };
        
    int long_index =0, opt;
    while ((opt = getopt_long(argc, argv,"v:f:d:c:l", 
                   long_options, &long_index )) != -1) {
        switch (opt) {
             case 'v' : 
                   verbosity = atoi(optarg);
                   break;
             case 'f' : 
                   strcpy(fileName, optarg);
                   strcat(infile, optarg);
                   strcat(outfile, optarg);
            	   strcat(outfile, "u");
                   break;
             case 'd' : 
                   strcpy(dependence_test, optarg);
                   break;
             case 'c' : 
                   strcpy(shrinking, optarg);
                   break;
              case 'l' : 
                   strcpy(affine_flag, optarg);
                   break;
             default: 
                    fprintf(stderr, "Usage: %s [--verbosityLevel=value] [--fileName=name.c] [--depTest=gcd/banerjee/omega] [--cycleShrink=simple/selective/true_dependence/extShrinking1/extShrinking2] [--loopType=affineOnly/nonAffineOnly]\n", argv[0]);
                   exit(EXIT_FAILURE);
            }
        }
	
	if(strcmp(fileName,"")==0)
	{
	    strcat(infile, "input.c");
	    strcat(outfile, "input.cu");
	}
	if(strcmp(dependence_test,"")==0)
            strcpy(dependence_test,"gcd");
    if(strcmp(shrinking,"")==0)
            strcpy(shrinking,"simple");
	if(strcmp(affine_flag,"")==0)
   strcpy(affine_flag,"0");
	in = fopen(infile, "r");
	out = fopen(outfile, "w");
	yyin = fopen(infile, "r");
	//verbosity=atoi(verbosity_no+1);
	if(yyin==NULL) {
		printMessage(10,"%s : FILE NOT FOUND\n", infile);
		return;
	}
	yyparse();
	printMessage(10,"%s : loop_type", affine_flag);
	// now we have loop index variables and parallel statement
	/*parallel_stmt = parallel_data->parallel_stmt;
	loop_index_new = parallel_data->loop_index;
	*/
	
	 printMessage(10,"\n-------------------- Display LOOP STATEMENTS  IN TOTAL LOOPS: \n");
        display_loop_parallel_stmt(8,head);
        
	printMessage(8,"\n-------------------- Loop statements: \n");
	display_StatementNode(8,parallel_stmt);
        struct Count_Loops* temp=head;
     
       while(temp)
        {
	loop_normalization(5,temp->parallel_stmt,variables,temp->loop_index_new);
       
	printMessage(8,"\n-------------------- Loop statements after Loop Normalization: \n");
	display_StatementNode(8,temp->parallel_stmt);
        temp=temp->next;
        }
	printMessage(8,"\n-------------------- Loop index variables(): \n");
       
	display_LoopIndexVar(8,loop_index); // no use
        temp=head;
        while(temp)
        {
	printMessage(8,"=======================loop_index_new\n");
	display_LoopIndexVar_New(8,temp->loop_index_new);
        temp=temp->next;
        }
       // printMessage(8,"=======================IN LOOPS\n");
        //display_loop_LoopIndexVar_New(8,head);
        
	printMessage(8,"\n-------------------- Original variables: \n");
	display_Var(8,variables);
	
	//remove_LoopIndexVar(head->loop_index_new);// no use
        temp=head;
       while(temp)
        {
	remove_LoopIndexVar_New(temp->loop_index_new);
        temp=temp->next;
        }
	printMessage(8,"\n-------------------- Variables excluding Loop index variables: \n"); // excluding loop index variables
	display_Var(8,variables);
	
	// No need as it reprints the loop statement variables
	//printMessage(8,"---HERE---\n");
	/*display_StatementNode(8,parallel_stmt);*/
	
	// calculate left_var, read_var, write_var
        
	
	/*  NO NEED
	printMessage(8,"left variables\n");
	display_StatementNode(8,left_var);*/
      // add_write_varibales_loop();
        /*temp=head;
        while(temp)
       {
       get_dependency_var(temp);
       temp->read_var=read_var;
       temp->write_var=write_var;
       temp=temp->next;
       }*/
    
      // add_write_varibales_loop();
	printMessage(8,"\n-------------------- Array References involved in RAW dependence\n");
	printMessage(8,"read dep variables\n");
      // display_loop_read_var(8,head);
     //  display_StatementNode(8,read_var);
       
        printMessage(8,"\n-------------------ARRAY REFERENCES INVOLVED IN RAW DEPENDENCE \n");
       display_loop_read_var(8,head);
       
        
	printMessage(8,"\n-------------------- Array References involved in WAW dependence\n");
	printMessage(8,"write dep variables\n");
       // display_StatementNode(8,read_var);
        display_loop_write_var(8,head);
        printMessage(8,"\n-------------------- left var----------\n");
        display_loop_left_var(8,head);
          
       
	//display_StatementNode(8,write_var);
	printMessage(8,"\n-------------------- List of Loop Statement Variables(stmt_var)\n");
      // remove_LoopIndexVar_New(temp->loop_index_new);
       display_loop_stmt_var(8,head);
      
	 /* temp=head;
         while(temp)
         {
          // remove_LoopIndexVar_New(temp->loop_index_new);
           display_Stmt_Var(8,temp->stmt_var);
           printf("----------------------------------------------------------\n");
           temp=temp->next;
          }*/
	// calculate left_stmt_var, read_stmt_var, write_stmt_var 
	//get_left_read_write_stmt_var();
	
	/* NO NEED
	printMessage(8,"left statement variables\n");
	display_Stmt_Var(8,left_stmt_var);*/
	
	printMessage(8,"\n-------------------- List of Loop Statement Variables involved in RAW dependence\n");
	display_loop_read_stmt_var(8,head);
	printMessage(8,"\n-------------------- List of Loop Statement Variables involved in WAW dependence\n");
	display_loop_write_stmt_var(8,head);

	printMessage(5,"\n-------------------- Pragma starts at line number %d and ends at line number %d\n", start_num, end_num);
	// Identifying Affine/Non-Affine kernel
	// Identifying Affine/Non-Affine kernel
	temp=head;
        while(temp!=NULL)
{
	AffineKernel='y';
	Affine_NonAffine_Test(temp-> write_var,temp-> read_var);
  printf("%c\n",AffineKernel);
  printf("%s\n",affine_flag);
  printf("%s\n",dependence_test);

	if(AffineKernel=='n'  &&( !strcmp(affine_flag,"0") || !strcmp(affine_flag,"nonAffineOnly" )))
    { 
        printMessage(8,"\n-------------------- Input program contains a non-affine loop\n");
        flag=1;
       /* if(temp->parallel_stmt!=NULL)
	    cuda_function_DEF(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new);
	    fdisplay_part1();
	    if(temp->parallel_stmt!=NULL)
	    cuda_loop(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new,temp->left_var,temp->read_stmt_var,temp->write_var);
	    if(temp->parallel_stmt!=NULL)
	    cuda_postloop(temp->loop_index_new);
	    in = fopen(infile, "r");
	    fdisplay_part2();
	    if(temp->parallel_stmt!=NULL)
	    cuda_function(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new,temp->parallel_stmt);*/
    }
	 if(AffineKernel=='y'  &&( !strcmp(affine_flag,"0") || !strcmp(affine_flag,"affineOnly" )))
	{
	    printMessage(8,"\n-------------------- Input program contains an affine loop\n");
	    // DEPENDENCE TESTING
	   // Dependence_Testing_Interface(5,dependence_test,temp->read_var,temp->write_var,temp->loop_index_new);
	  /*  CycleShrinking(5,shrinking,temp->read_var,temp->write_var,temp->loop_index_new,temp->stmt_var);
	    //Code Generation
	    cuda_kernel_declaration_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->count);
	    fdisplay_part1();
	    cuda_kernel_call_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->write_stmt_var,temp->count);
           id_max=0;
	    in = fopen(infile, "r");
	    fdisplay_part2();
	    cuda_kernel_definition_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->parallel_stmt,temp->count);*/
	}
temp=temp->next;
}
	temp=head;
        while(temp!=NULL)
{
	AffineKernel='y';
	Affine_NonAffine_Test(temp-> write_var,temp-> read_var);
	if(AffineKernel=='n'  &&( !strcmp(affine_flag,"0") || !strcmp(affine_flag,"nonAffineOnly" )))
    { 
       // printMessage(8,"\n-------------------- Input program contains a non-affine loop\n");
       /* if(temp->parallel_stmt!=NULL)
	    cuda_function_DEF(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new,temp->count);
	    fdisplay_part1();
            
	   if(temp->parallel_stmt!=NULL)
	    cuda_loop(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new,temp->left_var,temp->read_stmt_var,temp->write_var);
	    if(temp->parallel_stmt!=NULL)
	    cuda_postloop(temp->loop_index_new);
	    in = fopen(infile, "r");
	    fdisplay_part2();
	    if(temp->parallel_stmt!=NULL)
	    cuda_function(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new,temp->parallel_stmt);*/
    }
	else if(AffineKernel=='y'   &&( !strcmp(affine_flag,"0") || !strcmp(affine_flag,"affineOnly" )))
	{
	 //   printMessage(8,"\n-------------------- Input program contains an affine loop\n");
	    // DEPENDENCE TESTING
	    Dependence_Testing_Interface(5,dependence_test,temp->read_var,temp->write_var,temp->loop_index_new);
	  /*  CycleShrinking(5,shrinking,temp->read_var,temp->write_var,temp->loop_index_new,temp->stmt_var);
	    //Code Generation
	    cuda_kernel_declaration_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->count);
	    fdisplay_part1();
	    cuda_kernel_call_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->write_stmt_var,temp->count);
           id_max=0;
	    in = fopen(infile, "r");
	    fdisplay_part2();
	    cuda_kernel_definition_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->parallel_stmt,temp->count);*/
	}
temp=temp->next;
}
	temp=head;
        while(temp!=NULL)
{
	AffineKernel='y';
	Affine_NonAffine_Test(temp-> write_var,temp-> read_var);
	if(AffineKernel=='n'  &&( !strcmp(affine_flag,"0") || !strcmp(affine_flag,"nonAffineOnly" )))
    { 
      //  printMessage(8,"\n-------------------- Input program contains a non-affine loop\n");
       /* if(temp->parallel_stmt!=NULL)
	    cuda_function_DEF(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new);
	    fdisplay_part1();
	    if(temp->parallel_stmt!=NULL)
	    cuda_loop(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new,temp->left_var,temp->read_stmt_var,temp->write_var);
	    if(temp->parallel_stmt!=NULL)
	    cuda_postloop(temp->loop_index_new);
	    in = fopen(infile, "r");
	    fdisplay_part2();
	    if(temp->parallel_stmt!=NULL)
	    cuda_function(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new,temp->parallel_stmt);*/
    }
	else if(AffineKernel=='y'   &&( !strcmp(affine_flag,"0") || !strcmp(affine_flag,"affineOnly" )))
	{
	   // printMessage(8,"\n-------------------- Input program contains an affine loop\n");
	    // DEPENDENCE TESTING
	  //  Dependence_Testing_Interface(5,dependence_test,temp->read_var,temp->write_var,temp->loop_index_new);
	    CycleShrinking(5,shrinking,temp->read_var,temp->write_var,temp->loop_index_new,temp->stmt_var);
	    //Code Generation
	  /*  cuda_kernel_declaration_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->count);
	    fdisplay_part1();
	    cuda_kernel_call_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->write_stmt_var,temp->count);
           id_max=0;
	    in = fopen(infile, "r");
	    fdisplay_part2();
	    cuda_kernel_definition_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->parallel_stmt,temp->count);*/
	}
temp=temp->next;
}	temp=head;
          while(temp!=NULL)
{
	AffineKernel='y';
	Affine_NonAffine_Test(temp-> write_var,temp-> read_var);
	if(AffineKernel=='n' &&( !strcmp(affine_flag,"0") || !strcmp(affine_flag,"nonAffineOnly" )))
    { 
       // printMessage(8,"\n-------------------- Input program contains a non-affine loop\n");
        if(temp->parallel_stmt!=NULL)
	    cuda_function_DEF(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new,temp->count);
	   
	  /*  if(temp->parallel_stmt!=NULL)
	    cuda_loop(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new,temp->left_var,temp->read_stmt_var,temp->write_var);
	    if(temp->parallel_stmt!=NULL)
	    cuda_postloop(temp->loop_index_new);
	    in = fopen(infile, "r");
	    fdisplay_part2();
	    if(temp->parallel_stmt!=NULL)
	    cuda_function(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new,temp->parallel_stmt);*/
    }
	else if(AffineKernel=='y' &&( !strcmp(affine_flag,"0") || !strcmp(affine_flag,"affineOnly" )))
	{
	   // printMessage(8,"\n-------------------- Input program contains an affine loop\n");
	    // DEPENDENCE TESTING
	    //Dependence_Testing_Interface(5,dependence_test,temp->read_var,temp->write_var,temp->loop_index_new);
	    //CycleShrinking(5,shrinking,temp->read_var,temp->write_var,temp->loop_index_new,temp->stmt_var);
	    //Code Generation
	    cuda_kernel_declaration_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->count);
         //int i=0;
         // if(temp->next==NULL)
         //i=1;
	 // fdisplay_part1();
        //  fdisplay_part2();
	  /*  cuda_kernel_call_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->write_stmt_var,temp->count);
           id_max=0;
	    in = fopen(infile, "r");
	    fdisplay_part2();
	    cuda_kernel_definition_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->parallel_stmt,temp->count);*/
	}
temp=temp->next;
}
 fdisplay_part1();
  if(flag==0)	
 fdisplay_part1();
temp=head;
        while(temp!=NULL)
{
	AffineKernel='y';
	Affine_NonAffine_Test(temp-> write_var,temp-> read_var);
	if(AffineKernel=='n'   &&( !strcmp(affine_flag,"0") || !strcmp(affine_flag,"nonAffineOnly" )))
    { 
      //  printMessage(8,"\n-------------------- Input program contains a non-affine loop\n");
       // if(temp->parallel_stmt!=NULL)
	   // cuda_function_DEF(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new);
	    //fdisplay_part1();
	    if(temp->parallel_stmt!=NULL)
	    cuda_loop(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new,temp->left_var,temp->read_stmt_var,temp->write_var,temp->count);
	    if(temp->parallel_stmt!=NULL)
	    cuda_postloop(temp->loop_index_new,temp->count);
	    in = fopen(infile, "r");
	   /* fdisplay_part2();
	    if(temp->parallel_stmt!=NULL)
	    cuda_function(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new,temp->parallel_stmt);*/
    }
	else if(AffineKernel=='y'   &&( !strcmp(affine_flag,"0") || !strcmp(affine_flag,"affineOnly" )))
	{
	   /* printMessage(8,"\n-------------------- Input program contains an affine loop\n");
	    // DEPENDENCE TESTING
	    Dependence_Testing_Interface(5,dependence_test,temp->read_var,temp->write_var,temp->loop_index_new);
	    CycleShrinking(5,shrinking,temp->read_var,temp->write_var,temp->loop_index_new,temp->stmt_var);
	    //Code Generation
	    cuda_kernel_declaration_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->count);
	    fdisplay_part1();*/
	    cuda_kernel_call_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->write_stmt_var,temp->count);
           id_max=0;
	    in = fopen(infile, "r");
	   // fdisplay_part2();
          
	   // cuda_kernel_definition_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->parallel_stmt,temp->count);
	}
temp=temp->next;
}	
// fdisplay_part3();
//fdisplay_part2();
end();
temp=head;
        while(temp!=NULL)
{
	AffineKernel='y';
	Affine_NonAffine_Test(temp-> write_var,temp-> read_var);
	if(AffineKernel=='n'  &&( !strcmp(affine_flag,"0") || !strcmp(affine_flag,"nonAffineOnly" )))
    { 
       // printMessage(8,"\n-------------------- Input program contains a non-affine loop\n");
       /* if(temp->parallel_stmt!=NULL)
	    cuda_function_DEF(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new);
	    fdisplay_part1();
	    if(temp->parallel_stmt!=NULL)
	    cuda_loop(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new,temp->left_var,temp->read_stmt_var,temp->write_var);
	    if(temp->parallel_stmt!=NULL)
	    cuda_postloop(temp->loop_index_new);
	    in = fopen(infile, "r");
	    fdisplay_part2();*/
	    if(temp->parallel_stmt!=NULL)
	    cuda_function(temp->read_var,temp->left_stmt_var,temp->stmt_var,temp->loop_index_new,temp->parallel_stmt,temp->count);
    }
	else if(AffineKernel=='y'  &&( !strcmp(affine_flag,"0") || !strcmp(affine_flag,"affineOnly" )))
	{
	   /* printMessage(8,"\n-------------------- Input program contains an affine loop\n");
	    // DEPENDENCE TESTING
	    Dependence_Testing_Interface(5,dependence_test,temp->read_var,temp->write_var,temp->loop_index_new);
	    CycleShrinking(5,shrinking,temp->read_var,temp->write_var,temp->loop_index_new,temp->stmt_var);
	    //Code Generation
	    cuda_kernel_declaration_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->count);
	    fdisplay_part1();
	    cuda_kernel_call_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->write_stmt_var,temp->count);
           id_max=0;
	    in = fopen(infile, "r");
	    fdisplay_part2();*/
	    cuda_kernel_definition_AFFINE(shrinking,temp->stmt_var,temp->loop_index_new,temp->parallel_stmt,temp->count);
	}
temp=temp->next;
}
}
