#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
//#include "cuda_y.h"
#include "GCD_Banerjee_Test.h"
#include "ExtendedCS.h"
int getLoopNo(char *str,struct LoopIndexVar_New* loop_id)
{
    int i=1;
    while(loop_id)
    {
        if(!strcmp(str,loop_id->loopIndex->string))
        {
            return i;
        }
        i++;
        loop_id=loop_id->next;
    }
}

void CalculateLambda(struct StringNode* depString,int *lambda)
{
    int constt,sign=1,index; 
    while(depString)
    {
        if(!strcmp(depString->string,"+"))  sign=1;
        else if(!strcmp(depString->string,"-")) sign=-1;
        else if(!strcmp(depString->string,"*")) ;
        else if(isLoopIndex(depString,loop_index_new))
        {
            index=getLoopNo(depString->string,loop_index_new);
            if(depString->next&&(!strcmp(depString->next->string,"*")))
            {
                lambda[index]=sign*atoi(depString->next->next->string);
                depString=depString->next->next;
            }
            else
                lambda[index]=sign;
        }
        else
        {
            constt=sign*atoi(depString->string);
            if(depString->next&&(!strcmp(depString->next->string,"*"))&&(isLoopIndex(depString->next->next,loop_index_new)))
            {
                index=getLoopNo(depString->next->next->string,loop_index_new);
                lambda[index]=constt;
                depString=depString->next->next;
            }
            else
            {    lambda[0]=lambda[0]+constt;
            //printf("3string:%s, value:%d\n",depString->string,lambda[0]);
            }
        }
        depString=depString->next;
    }
}

void extCS_VariableDistance_Lambda(struct StatementNode *read_var,struct StatementNode *write_var, struct LoopIndexVar_New* loop_id, struct Stmt_Var* stmt_var)
{
    int i;
    struct StatementNode *read,*write;
    struct StringNode *readString,*writeString;
    struct SizeNode *readSize,*writeSize;
    char *readVar,*writeVar;
    struct LoopIndexVar_New* loopTemp;
    struct ReferencePair *tailRefPair=NULL,*refPairTemp=NULL;
    struct DDV *tailDDV=NULL,*headDDV=NULL,*DDVtemp=NULL;
    struct DDV_Values *headDDVvalue=NULL,*tailDDVvalue=NULL,*DDVvaluesTemp=NULL;
    
    
    /******************* creating structure for Dependence Distance Vector ******************************/
    write=write_var;
    while(write)
    {
        writeString=write->stringNode;
        read=read_var;
        while(read)
        {
            readString=read->stringNode;
            if(!strcmp(writeString->string,readString->string))
            {
                refPairTemp=(struct ReferencePair*)malloc(sizeof(struct ReferencePair));
                refPairTemp->next=NULL;
                refPairTemp->ddv=NULL;
                if(tailRefPair)
                {
                    tailRefPair->next=refPairTemp;
                    tailRefPair=refPairTemp;
                }
                else
                    RefPair=tailRefPair=refPairTemp;
                loopTemp=loop_id;
                tailDDV=NULL;
                headDDV=NULL;
                noOfNestedLoops=0;
                while(loopTemp)
                {
                    DDVtemp=(struct DDV*)malloc(sizeof(struct DDV));
                    DDVtemp->ddv_values=NULL;
                    DDVtemp->next=NULL;
                    if(tailDDV)
                    {
                        tailDDV->next=DDVtemp;
                        tailDDV=DDVtemp;
                    }
                    else
                        DDVvector=headDDV=tailDDV=DDVtemp;
                    noOfNestedLoops++;
                    loopTemp=loopTemp->next;
                }
                tailRefPair->ddv=headDDV;
                DDVtemp=headDDV;
                while(DDVtemp)
                {
                    DDVvaluesTemp=(struct DDV_Values*)malloc(sizeof(struct DDV_Values));
                    DDVvaluesTemp->value=0;
                    DDVvaluesTemp->next=NULL;
                    headDDVvalue=tailDDVvalue=DDVvaluesTemp;
                    loopTemp=loop_id;
                    while(loopTemp)
                    {
                        tailDDVvalue->next=(struct DDV_Values*)malloc(sizeof(struct DDV_Values));
                        tailDDVvalue->next->value=0;
                        tailDDVvalue->next->next=NULL;
                        tailDDVvalue=tailDDVvalue->next;
                        loopTemp=loopTemp->next;
                    }
                    tailDDVvalue->next=(struct DDV_Values*)malloc(sizeof(struct DDV_Values));
                    tailDDVvalue->next->value=0;
                    tailDDVvalue->next->next=NULL;
                    DDVtemp->ddv_values=headDDVvalue;
                    DDVtemp=DDVtemp->next;
                }
            }
            read=read->next;
        }
        write=write->next;
    }
    /*****************************************************************************************************************/
    
    /************************* calculating DDV **********************************/
    
    int Fvalue[noOfNestedLoops+2],Gvalue[noOfNestedLoops+2],temp;
    write=write_var;
    refPairTemp=RefPair;
    while(write)
    {
        writeVar=write->stringNode->string;
        writeSize=write->stringNode->size;
        read=read_var;
        while(read)
        {
            readVar=read->stringNode->string;
            readSize=read->stringNode->size;
            if(!strcmp(readVar,writeVar))
            {
                DDVtemp=refPairTemp->ddv;
                temp=1;
                while(readSize)
                {   
                    readString=readSize->sizeString;
                    writeString=writeSize->sizeString;
                    for(i=0;i<=(noOfNestedLoops+1);i++)
                    {
                        Fvalue[i]=0;
                        Gvalue[i]=0;
                        }
                    CalculateLambda(readString,Gvalue);
                    CalculateLambda(writeString,Fvalue);
                    Fvalue[noOfNestedLoops+1]=Gvalue[temp];
                    for(i=0;i<=noOfNestedLoops;i++)
                        Fvalue[i]=Fvalue[i]-Gvalue[i];
                    DDVvaluesTemp=DDVtemp->ddv_values;
                    i=0;
                    while(DDVvaluesTemp)
                    {
                        DDVvaluesTemp->value=Fvalue[i++];
                        DDVvaluesTemp=DDVvaluesTemp->next;
                    }
                    temp++;
                    DDVtemp=DDVtemp->next;
                    writeSize=writeSize->next;
                    readSize=readSize->next;
                }
                refPairTemp=refPairTemp->next;
            }
            read=read->next;
        }
        write=write->next;
    }
    /*****************************************************************************************************************/
    
    /* For printing the value of reference pair
    refPairTemp=RefPair;
    while(refPairTemp)
    {
        DDVtemp=refPairTemp->ddv;
        while(DDVtemp)
        {
            DDVvaluesTemp=DDVtemp->ddv_values;
            while(DDVvaluesTemp)
            {
                printf("3: %d\n",DDVvaluesTemp->value);
                DDVvaluesTemp=DDVvaluesTemp->next;
            }
            DDVtemp=DDVtemp->next;
        }
        refPairTemp=refPairTemp->next;
    }
    */
}

void extCS_ConstantDistance_Lambda(struct StatementNode *read_var,struct StatementNode *write_var, struct LoopIndexVar_New* loop_id, struct Stmt_Var* stmt_var)
{
    //no need because it is exactly same as Simple_Loops_Code_Gen(read_var,write_var,loop_index_new,stmt_var); for calculating lambda_var
}
