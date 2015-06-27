#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
//#include "cuda_y.h"
#include "GCD_Banerjee_Test.h"
#include "Cycle_Shrinking.h"
#include "ExtendedCS.h"
//int Total_Phi;
struct Phi_Values *find_phi_values(struct SizeNode *dep_size,struct Phi_Values *lambda,struct LoopIndexVar_New* loop_node)
{
    struct Phi_Values *phi_value,phi_value_temp,*lambda_temp;
    struct StringNode *dep_string;
    char *loop_id;
    int flag=1;
    while(lambda!=NULL)
    {
        if(flag)
        {
            phi_value=(struct Phi_Values*)malloc(sizeof(struct Phi_Values));
            phi_value->loop_index=lambda->loop_index;
            phi_value->phi_val=lambda->phi_val;
            phi_value->next=NULL;
            lambda_temp=phi_value;
            flag=0;
            } 
        else
        {
            lambda_temp->next=(struct Phi_Values*)malloc(sizeof(struct Phi_Values));
            lambda_temp->next->loop_index=lambda->loop_index;
            lambda_temp->next->phi_val=lambda->phi_val;
            lambda_temp->next->next=NULL;
            lambda_temp=lambda_temp->next;
        }
        lambda=lambda->next;
    }
    while(dep_size!=NULL)
    {
            dep_string = dep_size->sizeString;
            lambda_temp=phi_value;
            int constt=0,var,sign=1;
            while(dep_string!=NULL)
            {
                if(isLoopIndex(dep_string,loop_node))
                {
                    loop_id=dep_string->string;
                    if((dep_string->next!=NULL)&&(!strcmp(dep_string->next->string,"*")))
                        dep_string=dep_string->next->next;
                }
                else if(!strcmp(dep_string->string,"*"));
                else if(!strcmp(dep_string->string,"+"))
                    sign=1;
                else if(!strcmp(dep_string->string,"-"))
                    sign=-1;
                else
                {
                    var=atoi(dep_string->string);
                    if(((dep_string->next==NULL))||((dep_string->next!=NULL)&&(strcmp(dep_string->next->string,"*"))))
                        constt=constt+(var*sign);
                }
                dep_string=dep_string->next;
            }
            while(lambda_temp!=NULL)
            {
                if(!strcmp(loop_id,lambda_temp->loop_index))
                    lambda_temp->phi_val=constt;
                lambda_temp=lambda_temp->next;
            }
            dep_size=dep_size->next;
    }
    return phi_value;
}

struct Phi_Values *Simple_Loops_Code_Gen(struct StatementNode* read,struct StatementNode* write,struct LoopIndexVar_New* loop_id,struct Stmt_Var* statement_var)
{
    struct Phi_Values *lambda,*lambda_temp,*read_phi_values,*write_phi_values,*write_phi_values_temp;
    struct LoopIndexVar_New* loop_id_temp;
    loop_id_temp=loop_id;
    int flag=1;
    while(loop_id_temp!=NULL)
    {
        if(flag)
        {
            lambda=(struct Phi_Values*)malloc(sizeof(struct Phi_Values));
            lambda->loop_index=loop_id_temp->loopIndex->string;
            lambda->phi_val=0;
            lambda->next=NULL;
            lambda_temp=lambda;
            flag=0;
            }
        else
        {
            lambda_temp->next=(struct Phi_Values*)malloc(sizeof(struct Phi_Values));
            lambda_temp->next->loop_index=loop_id_temp->loopIndex->string;
            lambda_temp->next->phi_val=0;
            lambda_temp->next->next=NULL;
            lambda_temp=lambda_temp->next;
        }
        loop_id_temp=loop_id_temp->next;
        Total_Phi++;
    }
    struct StatementNode* write_temp,*read_temp;
    struct SizeNode *write_size,*read_size;
    int constt=0;
    write_temp=write;
    while(write_temp!=NULL)
    {
        write_size=write_temp->stringNode->size;
        write_phi_values=find_phi_values(write_size,lambda,loop_id);
        
        read_temp=read;
        while(read_temp!=NULL)
        {
            if(!strcmp(read_temp->stringNode->string,write_temp->stringNode->string))
            {
                read_size=read_temp->stringNode->size;
                read_phi_values=find_phi_values(read_size,lambda,loop_id);
                lambda_temp=lambda;
                write_phi_values_temp=write_phi_values;
                while(read_phi_values!=NULL)
                {
                    constt=abs((read_phi_values->phi_val)-(write_phi_values_temp->phi_val));
                    //printf("%d,%s: %d,%s %d\n",constt,read_phi_values->loop_index,read_phi_values->phi_val,write_phi_values->loop_index,write_phi_values->phi_val);
                    lambda_temp->phi_val=(lambda_temp->phi_val==0||lambda_temp->phi_val>constt)?constt:lambda_temp->phi_val;
                    read_phi_values=read_phi_values->next;
                    write_phi_values_temp=write_phi_values_temp->next;
                    lambda_temp=lambda_temp->next;
                }
            }
            read_temp=read_temp->next;
        }
        write_temp=write_temp->next;
    }
    lambda_temp=lambda;
    printMessage(8, "\n-------------------- Reduction Factor (Lambda) simple: < ");
    while(lambda_temp!=NULL)
    {
        //printMessage(8, "phi value: %s, %d\n",lambda_temp->loop_index,lambda_temp->phi_val);
        printMessage(8, "%d",lambda_temp->phi_val);
        lambda_temp=lambda_temp->next;
        if(lambda_temp)
            printMessage(8, ", ");
    }
    printMessage(8, ">\n");
    return lambda;
}


//function to find the true dependence distance and then finding the value of lambda
struct Phi_Values *True_Dependence_Lambda(struct StatementNode* read,struct StatementNode* write,struct LoopIndexVar_New* loopId,struct Stmt_Var* statement_var)
{
    struct StatementNode *readStatementNode,*writeStatementNode;
    struct SizeNode *readSize,*writeSize;
    struct StringNode *readString,*writeString,*writeSizeString,*readSizeString;
    struct LoopIndexVar_New *loopIdTemp,*loopIdTemp1;
    struct Phi_Values *minPhiValue;
    minPhiValue=(struct Phi_Values*)malloc(sizeof(struct Phi_Values));
    minPhiValue->phi_val=32767;
    //minPhiValue->loop_index=(struct char*)malloc(20*sizeof(struct char));
    minPhiValue->next=NULL;
    int temp;
    writeStatementNode=write;
    while(writeStatementNode!=NULL)
    {
        writeString=writeStatementNode->stringNode;
        readStatementNode=read;
        while(readStatementNode!=NULL)
        {
            readString=readStatementNode->stringNode;
            if(!strcmp(readString->string,writeString->string))
            {
                readSize=readString->size;
                writeSize=writeString->size;
                loopIdTemp=loopId->next;
                int phi_value=0;
                while(readSize!=NULL)
                {
                    readSizeString=readSize->sizeString;
                    writeSizeString=writeSize->sizeString;
                    int c=0,d=0,var,sign=1,constt=0;
                    while(writeSizeString!=NULL)
                    {
                        if(isLoopIndex(writeSizeString,loopId))
                        {
                            if((writeSizeString->next!=NULL)&&(!strcmp(writeSizeString->next->string,"*")))
                               writeSizeString=writeSizeString->next->next;
                        }
                        else if(!strcmp(writeSizeString->string,"*"));
                        else if(!strcmp(writeSizeString->string,"+"))
                           sign=1;
                        else if(!strcmp(writeSizeString->string,"-"))
                           sign=-1;
                        else
                        {
                            var=atoi(writeSizeString->string);
                            if(((writeSizeString->next==NULL))||((writeSizeString->next!=NULL)&&(strcmp(writeSizeString->next->string,"*"))))
                               c=c+(var*sign);
                        }
                        writeSizeString=writeSizeString->next;
                    }
                    sign=1;
                    while(readSizeString!=NULL)
                    {
                        if(isLoopIndex(readSizeString,loopId))
                        {
                            if((readSizeString->next!=NULL)&&(!strcmp(readSizeString->next->string,"*")))
                               readSizeString=readSizeString->next->next;
                        }
                        else if(!strcmp(readSizeString->string,"*"));
                        else if(!strcmp(readSizeString->string,"+"))
                           sign=1;
                        else if(!strcmp(readSizeString->string,"-"))
                           sign=-1;
                        else
                        {
                            var=atoi(readSizeString->string);
                            if(((readSizeString->next==NULL))||((readSizeString->next!=NULL)&&(strcmp(readSizeString->next->string,"*"))))
                               d=d+(var*sign);
                        }
                        readSizeString=readSizeString->next;
                    }
                    constt=abs(d-c);
                    temp=1;
                    loopIdTemp1=loopIdTemp;
                    while(loopIdTemp1!=NULL)
                    {
                        temp=temp*((atoi(loopIdTemp1->U->string))-(atoi(loopIdTemp1->L->string)));
                        loopIdTemp1=loopIdTemp1->next;
                    }
                    if(loopIdTemp)
                        loopIdTemp=loopIdTemp->next;
                    readSize=readSize->next;
                    writeSize=writeSize->next;
                    phi_value=phi_value+(constt*temp);
                    //printf("## d: %d, c: %d, constt: %d, temp: %d, phi_value: %d ##\n",d,c,constt,temp,phi_value); 
                }
                if(phi_value<minPhiValue->phi_val)
                {
                    minPhiValue->phi_val=phi_value;
                    minPhiValue->loop_index=readString->string;
                }
            }
            readStatementNode=readStatementNode->next;
        }
        writeStatementNode=writeStatementNode->next;
    }
    //printf("## %s: %d ##\n",minPhiValue->loop_index,minPhiValue->phi_val);
    printMessage(8, "\n-------------------- Reduction Factor (Lambda) selective: <%d>\n",minPhiValue->phi_val);
    return minPhiValue;
}

void CycleShrinking(int verbosity_no, char *shrinking,struct StatementNode* read_var,struct StatementNode* write_var,struct LoopIndexVar_New* loop_index_new,struct Stmt_Var* stmt_var)
{
    if(VariableDependenceDist=='n')
    {
        if((!strcmp(shrinking,"simple"))||(!strcmp(shrinking,"selective")))
            if((!strcmp(shrinking,"selective"))&&(noOfNestedLoops<2))
            {
                printMessage(10, "Oops!! Selective shrinking can't be applied on Single nested loop\n");
               // exit(0);
                }
            else
                lambda_var=Simple_Loops_Code_Gen(read_var,write_var,loop_index_new,stmt_var);
        else if(!strcmp(shrinking,"true_dependence"))
            if(noOfNestedLoops<2)
            {
                printMessage(10, "Oops!! True dependence shrinking can't be applied on Single nested loop\n");
               // exit(0);
                }
            else
                lambda_var=True_Dependence_Lambda(read_var,write_var,loop_index_new,stmt_var);
        else if(!strcmp(shrinking,"extShrinking1"))
            lambda_var=Simple_Loops_Code_Gen(read_var,write_var,loop_index_new,stmt_var);
            //extCS_ConstantDistance_Lambda(read_var,write_var,loop_index_new,stmt_var);
        else
        {
            printMessage(10, "Oops!! Wrong input. Please give simple, selective, true_dependence or extShrinking1 as input.\n");
           // exit(0);
        }
     }
     else 
     {
        if(!strcmp(shrinking,"extShrinking2"))
            extCS_VariableDistance_Lambda(read_var,write_var,loop_index_new,stmt_var);
        else
        {
            printMessage(10, "Oops!! Code Generation for Variable Dependence Distance can only happen through Extended Cycle Shrinking \n");
           // exit(0);
        }
        
     }
}
