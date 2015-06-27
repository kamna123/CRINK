#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
//#include "cuda_y.h"
#include "GCD_Banerjee_Test.h"
// For GCD and Banerjee Test, will work for both single and multi-dimensional array

// Finding Euclid GCD
int euclid_GCD(int a, int b)
{
    if(b == 0)
       return a;
    else
       return euclid_GCD(b, (a%b));
}

// Identifying whether index is loop index or not
int isLoopIndex(struct StringNode* index,struct LoopIndexVar_New* loop_id)
{
    while(loop_id!=NULL){
        if(!strcmp(index->string,loop_id->loopIndex->string))
            return 1;
        else
            loop_id=loop_id->next;
    } 
    return 0;
}

// For given write_string finding the corresponding string in read dependence variable
struct SizeNode* find_corresponding_read_dep_var(struct StringNode* write_string,struct StatementNode* read)
{
    while(read)
    {
        if(!strcmp(write_string->string,read->stringNode->string))
            return read->stringNode->size;
        else
            read=read->next;
    }
}

// Performs GCD dependence test
int GCD_Test(struct StatementNode* read,struct StatementNode* write,struct LoopIndexVar_New* loop_id)
{
     
    struct StringNode *read_string, *write_string, *loop_id_string;
    struct SizeNode *read_size,*write_size;
    int a=0,b=0,c=0,d=0,var,sign=1,dependency=0,dimension=0,dep_exists=0;
    loop_id_string = loop_id->loopIndex;
    while(write)
    {
        write_size=write->stringNode->size;
        read_size=find_corresponding_read_dep_var(write->stringNode,read);
        dependency=0,dimension=0;
        while(write_size||read_size)      
        {
            write_string = write_size->sizeString;
            read_string=read_size->sizeString;
            a=0,b=0,c=0,d=0,var,sign=1;
            while(write_string!=NULL)
            {
                if(isLoopIndex(write_string,loop_id))
                    a=(a==0)?1:a;
                else if(!strcmp(write_string->string,"*"));
                else if(!strcmp(write_string->string,"+"))
                    sign=1;
                else if(!strcmp(write_string->string,"-"))
                    sign=-1;
                else
                {
                    var=atoi(write_string->string);
                    if((write_string->next==NULL)||(strcmp(write_string->next->string,"*")))
                        c=c+(var*sign);
                    else
                        a=(a>0)?euclid_GCD(a,var):var;
                }
                //printf("%s ",write_string->string);
                //printf("a=%d, b=%d, c=%d, d=%d, var=%d\n",a,b,c,d,var);
                write_string=write_string->next;
            }
            sign=1;
            while(read_string!=NULL)
            {
                if(isLoopIndex(read_string,loop_id))
                    b=(b==0)?1:(b*1);
                else if(!strcmp(read_string->string,"*"));
                else if(!strcmp(read_string->string,"+"))
                    sign=1;
                else if(!strcmp(read_string->string,"-"))
                    sign=-1;
                else
                {
                    var=atoi(read_string->string);
                    if((read_string->next==NULL)||(strcmp(read_string->next->string,"*")))
                        d=d+var*sign;
                    else
                        b=(b>0)?euclid_GCD(b,var):var;
                }
                read_string=read_string->next;
            }
            if(a==0&&b==0)    var=1;
            else if(b==0)   var=a;
            else if(a==0)   var=b;
            else var=euclid_GCD(a,b);
            dependency=(((d-c)%var)==0)?dependency+1:dependency; 
            dimension++;
            printMessage(5, "a=%d, b=%d, c=%d, d=%d, var=%d dependency=%d dimension=%d \n",a,b,c,d,var,dependency,dimension);
            read_size=read_size->next;
            write_size=write_size->next;
        }
        write=write->next;
        dep_exists=(dependency==dimension)?1:dep_exists;
    }
    if(dep_exists)      //dependency exist
        return 1;     
    else
        return 0;
       
}

// Find the level of loop. Outer loop has the smallest level and the innermost loop has the largest level.
int find_loop_level(struct StringNode* index,struct LoopIndexVar_New* loop_id)
{
    int i=0;
    while(loop_id!=NULL){
        if(!strcmp(index->string,loop_id->loopIndex->string))
            return i;
        else
            loop_id=loop_id->next;
        i++;
    }
}

// To fill the array arr with the coefficient of loop indices in the array subscript
int fill_coeff_array(int *arr,struct StringNode *stmt_string,struct LoopIndexVar_New* loop_id)
{
    int coeff=1,constt=0,var=0,sign=1;
    while(stmt_string!=NULL)
    {
        if(isLoopIndex(stmt_string,loop_id))
        {   
            arr[find_loop_level(stmt_string,loop_id)]=(coeff*sign);
            coeff=1;
            }
        else if(!strcmp(stmt_string->string,"*"));
        else if(!strcmp(stmt_string->string,"+"))
            sign=1;
        else if(!strcmp(stmt_string->string,"-"))
            sign=-1;
        else
        {
            var=atoi(stmt_string->string);
            if((stmt_string->next==NULL)||(strcmp(stmt_string->next->string,"*")))
                constt=constt+(var*sign);
            else
                coeff=(var*sign);
        }
        //printf("--- %s ---\n",stmt_string->string);
        //printf("str=%s constt=%d coeff=%d var=%d sign=%d\n",stmt_string->string,constt,coeff,var,sign);
        stmt_string=stmt_string->next;
    }//printf("\n");
    return constt;
}

int positive_func(int x)
{
    int result=(x>0)?x:0;
    return result;
}

int negative_func(int x)
{
    int result=(x<0)?-x:0;
    return result;
}

// Banerjee Dependence Test
int Banerjee_Test(struct StatementNode* read,struct StatementNode* write,struct LoopIndexVar_New* loop_id)
{
    struct LoopIndexVar_New* loop_id_temp;
    struct StringNode *read_string, *write_string;
    struct SizeNode *read_size,*write_size;
    loop_id_temp=loop_id;
    int no_of_loops=0,i,c,d;
    while(loop_id_temp!=NULL)
    {
        no_of_loops++;
        loop_id_temp=loop_id_temp->next;
    }
    printMessage(5, "No of loops: %d\n",no_of_loops);
    int a_i[no_of_loops],b_i[no_of_loops],lower_limits[no_of_loops],upper_limits[no_of_loops];
    int a_neg[no_of_loops],a_pos[no_of_loops],b_neg[no_of_loops],b_pos[no_of_loops];
    int LB_less=0,UB_less=0,LB_greater=0,UB_greater=0,LB_equal=0,UB_equal=0,dep_exists=0;
    int dependency,dimension;
    loop_id_temp=loop_id;
    i=0;
    // To fill the array lower_limits[] and upper_limits[] with the lower limit and upper limits of the loops 
    while(loop_id_temp!=NULL)
    {
        lower_limits[i]=atoi(loop_id->L->string);
        upper_limits[i]=atoi(loop_id->U->string);
        i++;
        loop_id_temp=loop_id_temp->next;
    }
    while(write)
    {
        write_size=write->stringNode->size;
        read_size=find_corresponding_read_dep_var(write->stringNode,read);
        dependency=0,dimension=0;
        while(write_size||read_size)      
        {
            write_string = write_size->sizeString;
            read_string=read_size->sizeString;
            for(i=0;i<no_of_loops;i++)
            {
                a_i[i]=0;
                b_i[i]=0;
            }
            c=fill_coeff_array(a_i,write_string,loop_id);
            d=fill_coeff_array(b_i,read_string,loop_id);
            LB_less=0,UB_less=0,LB_greater=0,UB_greater=0,LB_equal=0,UB_equal=0;
            /*Printing the obtained matrix
            printf("Lower limits array\n");
            for(i=0;i<no_of_loops;i++)
                printf("%d ",lower_limits[i]);
            printf("\n");
            printf("Upper limits array\n");
            for(i=0;i<no_of_loops;i++)
                printf("%d ",upper_limits[i]);
            printf("\n");
            printf("a_i array\n");
            for(i=0;i<no_of_loops;i++)
                printf("%d ",a_i[i]);
            printf("\n");
            printf("b_i array\n");
            for(i=0;i<no_of_loops;i++)
                printf("%d ",b_i[i]);
            printf("\nc=%d d=%d\n",c,d);
            //////////////////////////////////*/
            for(i=0;i<no_of_loops;i++)
            {
                a_neg[i]=(a_i[i]<0)?-a_i[i]:0;              //negative function of a_i[]
                a_pos[i]=(a_i[i]>0)?a_i[i]:0;               //positive function of a_i[]
                b_neg[i]=(b_i[i]<0)?-b_i[i]:0;              //negative function of b_i[]
                b_pos[i]=(b_i[i]>0)?b_i[i]:0;               //positive function of b_i[]
            }
            
            for(i=0;i<no_of_loops;i++)
            {
                LB_less+=(-1)*positive_func(a_neg[i]+b_i[i])*(upper_limits[i]-1)+(negative_func(a_neg[i]+b_i[i])+a_pos[i])*lower_limits[i]-b_i[i];
                UB_less+=positive_func(a_pos[i]-b_i[i])*(upper_limits[i]-1)+(negative_func(a_pos[i]-b_i[i])+a_neg[i])*lower_limits[i]-b_i[i];
                LB_equal+=(-1)*negative_func(a_i[i]-b_i[i])*upper_limits[i]+positive_func(a_i[i]-b_i[i])*lower_limits[i];
                UB_equal+=positive_func(a_i[i]-b_i[i])*upper_limits[i]-negative_func(a_i[i]-b_i[i])*lower_limits[i];
                LB_greater+=(-1)*negative_func(a_i[i]-b_pos[i])*(upper_limits[i]-1)+(positive_func(a_i[i]-b_pos[i])+b_neg[i])*lower_limits[i]+a_i[i];
                UB_greater+=positive_func(a_i[i]+b_neg[i])*(upper_limits[i]-1)-(negative_func(a_i[i]+b_neg[i])+b_pos[i])*lower_limits[i]+a_i[i];
        
            }
            printMessage(5, "c=%d d=%d\n",c,d);
            printMessage(5, "LB_less=%d UB_less=%d\n",LB_less,UB_less);
            printMessage(5, "LB_equal=%d UB_equal=%d\n",LB_equal,UB_equal);
            printMessage(5, "LB_greater=%d UB_greater=%d\n",LB_greater,UB_greater);
            int flag=0;
            if((d-c)>=LB_less&&(d-c)<=UB_less)
            {
                flag=1;
                //*less=1;
            }
            if((d-c)>=LB_greater&&(d-c)<=UB_greater)
            {
                flag=1;
                //*greater=1;
            }
            if((d-c)>=LB_equal&&(d-c)<=UB_equal)
            {
                flag=1;
                //*equal=1;
            }
            dependency=(flag==1)?dependency+1:dependency; 
            dimension++;
            printMessage(5, "dependency=%d dimension=%d\n",dependency,dimension);
            read_size=read_size->next;
            write_size=write_size->next;
        }
        dep_exists=(dependency==dimension)?1:dep_exists;
        write=write->next;
    }
    if(dep_exists)      //dependency exist
        return 1;     
    else
        return 0;
}
