#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
//#include "cuda_y.h"
#include "Loop_Normalization.h"
// Checks whether a given string is a variable name
int isVariable(char *name,int *b_val,struct Var* variable)
{
    struct Var* variable_temp;
    variable_temp=variable;
    while(variable_temp!=NULL)
    {
        if(!strcmp(name,variable_temp->identifier->string))
        {
            *b_val=variable_temp->var_value;
            return 1;
            }
        variable_temp=variable_temp->next;
    }
    return 0;
}

// Function to normalize a loop 
void loop_normalization(int verbosity_no, struct StatementNode* stmt,struct Var* variable, struct LoopIndexVar_New* loop_id) //here, stmt=parallel_stmt, loop_id=loop_index_new
{
    char *a,*b,*c;
    int a_val=0,b_val=0,c_val=0,prev_val=1,sign=1;
    struct LoopIndexVar_New* loop_temp;
    struct StatementNode* stmt_temp;
    struct SizeNode* stmt_size;
    struct StringNode *stmt_string1,*stmt_string2,*prev=NULL,*curr=NULL,*last=NULL,*temp=NULL;
    loop_temp=loop_id;
    
    // Loop normalization
    while(loop_temp!=NULL)
    {
        a=loop_temp->L->string;     // a: lower limit of the loop
        b=loop_temp->U->string;     // b: upper limit of the loop
        c=loop_temp->D->string;     // c: loop increment/decrement value
        loop_temp->L->string="0";   // Set the lower limit of loop to be 0
        loop_temp->D->string="1";   // Set the increment/decrement value of loop to be 1
        if(!isVariable(a,&a_val,variable)) // a_val: if lower limit of loop is a variable then a_val will contain its corresponding value
            a_val=atoi(a);
        if(!isVariable(b,&b_val,variable)) // b_val: if upper limit of loop is a variable then b_val will contain its corresponding value
            b_val=atoi(b);
        c_val=atoi(c);
        if(loop_temp->op=='+') // calculating new upper limit of the loop if increment/decrement operator is '+'
            b_val=(b_val-a_val)/c_val; 
        else                   // calculating new upper limit of the loop if increment/decrement operator is '-'
            b_val=(a_val-b_val)/c_val;
        if(loop_temp->relop==2) //changing the relational operator to '<' if it was '>'
            loop_temp->relop=1;
        else if(loop_temp->relop==4) //changing the relational operator to '<=' if it was '>='
            loop_temp->relop=3;
        char str[10];
        //sprintf(str, "%d", b_val); //sprintf() converts integer to string
        loop_temp->U->string=(char*)malloc(sizeof(char)*10);
        sprintf(loop_temp->U->string, "%d", b_val); //updating loop upper limit with b_val
        //printf("a_val=%d,b_val=%d,c_val=%d,str=%s\n",a_val,b_val,c_val,loop_temp->U->string);
        
        stmt_temp=stmt;
        while(stmt_temp!=NULL)
        {
        // updating array indices for each normalized loop
        stmt_string1=stmt_temp->stringNode;
        while(stmt_string1!=NULL)
        {
            //printf("1:%s\n",stmt_string1->string);
            stmt_size=stmt_string1->size;
            while(stmt_size!=NULL)
            {
                stmt_string2=stmt_size->sizeString;
                //printf("2:%s\n",stmt_string2->string);
                prev=NULL;
                curr=NULL;
                temp=NULL;
                prev_val=1;
                sign=1;
                // consider array index 3-2*i+5 in loop 'for(i=4;i<=20;i+=6)'
                while(stmt_string2!=NULL)
                {
                    if(!strcmp(stmt_string2->string,"+"))
                        sign=1;
                    else if(!strcmp(stmt_string2->string,"-"))
                        sign=-1;
                    if(stmt_string2->next&&(!strcmp(stmt_string2->next->string,"*"))) //comes when stmt_string2 points to 2*i
                    {
                        if((!isLoopIndex(stmt_string2,loop_id))&&(strcmp(stmt_string2->string,"*"))&&(strcmp(stmt_string2->string,"+"))&&(strcmp(stmt_string2->string,"-"))&&(!strcmp(stmt_string2->next->next->string,loop_temp->loopIndex->string)))
                        {
                            VariableDependenceDist='y';
                            prev_val=atoi(stmt_string2->string);                     // pre_val: 2 (out of 2*i)
                            if(a_val)
                            {
                                curr=(struct StringNode*)malloc(sizeof(struct StringNode));
                                curr->string=(char*)malloc(sizeof(char)*10);
                                sprintf(curr->string, "%d", a_val*prev_val);
                                curr->size=NULL;                                    //create node curr with value 4*2 
                                last=(struct StringNode*)malloc(sizeof(struct StringNode));
                                if(loop_temp->op=='+')
                                    last->string=(sign>0)?"+":"-";
                                else
                                    last->string=(sign>0)?"-":"+";
                                last->size=NULL;                                   // create node last with value '-'
                                curr->next=last;                                   // curr node will become '8'->'-'
                            }
                            //if(c_val!=1)
                            //{
                                stmt_string2->string=(char*)malloc(sizeof(char)*10);
                                sprintf(stmt_string2->string, "%d", c_val*prev_val); // update 2*i to 6*2*i
                                if(curr)
                                    curr->next->next=stmt_string2;                 //curr will become '8'->'-'->'12'->'*'->'i'
                           // }
                            if(curr)
                            {
                                if(prev)
                                    prev->next=curr;
                                else
                                    stmt_size->sizeString=curr;
                                }
                            stmt_string2=stmt_string2->next->next; // if curr exist then stmt_string2 will point to '+' out of 3-8-12*i+5             
                        }
                        //if array index is 3-i*2+5
                        else if((!strcmp(stmt_string2->string,loop_temp->loopIndex->string))&&(!isLoopIndex(stmt_string2->next->next,loop_id))&&(strcmp(stmt_string2->next->next->string,"*"))&&(strcmp(stmt_string2->next->next->string,"+"))&&(strcmp(stmt_string2->next->next->string,"-")))
                        {
                            VariableDependenceDist='y';
                            prev_val=atoi(stmt_string2->next->next->string);
                            if(a_val)
                            {
                                curr=(struct StringNode*)malloc(sizeof(struct StringNode));
                                curr->string=(char*)malloc(sizeof(char)*10);
                                sprintf(curr->string, "%d", a_val*prev_val);
                                curr->size=NULL;
                                last=(struct StringNode*)malloc(sizeof(struct StringNode));
                                if(loop_temp->op=='+')
                                    last->string=(sign>0)?"+":"-";
                                else
                                    last->string=(sign>0)?"-":"+";
                                last->size=NULL;
                                curr->next=last;
                                //printf("%s, %s\n",curr->string,last->string);
                            }   
                            //if(c_val!=1)
                            {
                                temp=(struct StringNode*)malloc(sizeof(struct StringNode));
                                temp->string=(char*)malloc(sizeof(char)*10);
                                sprintf(temp->string, "%d", c_val*prev_val);
                                temp->size=NULL;
                                last=(struct StringNode*)malloc(sizeof(struct StringNode));
                                last->string="*";
                                last->size=NULL;
                                temp->next=last;
                                //printf("%s, %s\n",temp->string,last->string);
                                if(curr)
                                    curr->next->next=temp;
                                else
                                    curr=temp;
                            }   
                            if(curr)
                            {
                                if(prev)
                                    prev->next=curr;
                                else
                                    stmt_size->sizeString=curr;
                                last->next=stmt_string2;
                                }
                            stmt_string2->next=stmt_string2->next->next->next;
                            }
                        }
                    // if array index is 3-i+5
                    else if(!strcmp(stmt_string2->string,loop_temp->loopIndex->string))
                    {
                        //printf("3:%s\n",stmt_string2->string);
                        if(a_val)
                        {
                            curr=(struct StringNode*)malloc(sizeof(struct StringNode));
                            //sprintf(str, "%d", a_val*prev_val);
                            curr->string=a;
                            curr->size=NULL;
                            last=(struct StringNode*)malloc(sizeof(struct StringNode));
                            if(loop_temp->op=='+')
                                    last->string=(sign>0)?"+":"-";
                            else
                                    last->string=(sign>0)?"-":"+";
                            last->size=NULL;
                            curr->next=last;
                            //printf("%s, %s\n",curr->string,last->string);
                        }
                        if(c_val!=1)
                        {
                            temp=(struct StringNode*)malloc(sizeof(struct StringNode));
                            //sprintf(str, "%d", c_val*prev_val);
                            temp->string=c;
                            temp->size=NULL;
                            last=(struct StringNode*)malloc(sizeof(struct StringNode));
                            last->string="*";
                            last->size=NULL;
                            temp->next=last;
                            //printf("%s, %s\n",temp->string,last->string);
                            if(curr)
                                curr->next->next=temp;
                            else
                                curr=temp;
                        }
                        if(curr)
                        {
                            if(prev)
                                prev->next=curr;
                            else
                                stmt_size->sizeString=curr;
                            last->next=stmt_string2;
                            }
                    }
                    prev=stmt_string2;
                    curr=NULL;
                    last=NULL;
                    stmt_string2=stmt_string2->next;
                }
                stmt_size=stmt_size->next;
            }
            stmt_string1=stmt_string1->next;
        }
        stmt_temp=stmt_temp->next;
        }
        if(loop_temp->op=='-')
           loop_temp->op='+';
    loop_temp=loop_temp->next;    
    }
    
    /*loop_temp=loop_id;
    while(loop_temp!=NULL)
    {
        printf("%s:[%s,%s],D=%s,op=%c,relop=%d\n",loop_temp->loopIndex->string,loop_temp->L->string,loop_temp->U->string,loop_temp->D->string,loop_temp->op,loop_temp->relop);
        loop_temp=loop_temp->next;
    }*/
    
}
