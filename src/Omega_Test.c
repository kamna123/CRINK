#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
//#include "cuda_y.h"
#include "GCD_Banerjee_Test.h"
#include "Omega_Test.h"
FILE *in_file;
int count_dep_var(struct StatementNode* read,char *var_name)
{
    int dep_var=0;
    while(read!=NULL)
    {
          if(!strcmp(var_name,read->stringNode->string))
                dep_var++;
          read=read->next;
    }
    return dep_var;
}

// Printing loop limits in input file for Omega Calculator
void print_loop_limits(struct StringNode* loop_limit,struct LoopIndexVar_New* loop_id)
{
    while(loop_limit!=NULL)
    {
        if(isLoopIndex(loop_limit,loop_id))
            fprintf(in_file,"%s11",loop_limit->string);
        else
            fprintf(in_file,"%s",loop_limit->string);
        loop_limit=loop_limit->next;
        }
}

//Printing the dependencies in the omega input file
void print_dependency(struct StatementNode* read,struct StatementNode* write,struct LoopIndexVar_New* loop_id,char *var_name,int total_read_var,int total_write_var)
{
    struct StringNode *read_string1,*write_string1,*read_string2,*write_string2;
    struct SizeNode *read_size,*write_size;
    struct StatementNode *read_temp,*write_temp,*read_var_temp,*write_var_temp;
    read_temp=read;
    write_temp=write;
    int read_count=0,write_index=1,read_index=1;
        while(write_temp!=NULL)
        {
            printMessage(5, "var=%s,w=%d,r=%d",var_name,write_index,read_index);
            if(!strcmp(var_name,write_temp->stringNode->string))
            {
                read_temp=read;
                read_index=1;
                while(read_temp!=NULL)
                {   
                    if(!strcmp(var_name,read_temp->stringNode->string))
                    {   
                        if(read_count)
                            fprintf(in_file," && ");
                        read_size=read_temp->stringNode->size;
                        write_size=write_temp->stringNode->size;
                        while(read_size!=NULL)
                        {
                            read_string2=read_size->sizeString;
                            write_string2=write_size->sizeString;
                            while(write_string2!=NULL)
                            {
                                if(isLoopIndex(write_string2,loop_id))
                                    fprintf(in_file,"%s1%d",write_string2->string,write_index);
                                else
                                    fprintf(in_file,"%s",write_string2->string);
                                write_string2=write_string2->next;
                            }
                            fprintf(in_file," = ");
                            while(read_string2!=NULL)
                            {
                                if(isLoopIndex(read_string2,loop_id))
                                    fprintf(in_file,"%s2%d",read_string2->string,read_index);
                                else
                                    fprintf(in_file,"%s",read_string2->string);
                                read_string2=read_string2->next;
                            }
                            if(read_size->next!=NULL)
                                fprintf(in_file," && ");
                            read_size=read_size->next;
                            write_size=write_size->next;
                        }
                        read_count++;
                        read_index++;
                    }
                    read_temp=read_temp->next;
                }
                write_index++; 
            } 
             
            write_temp=write_temp->next;
        }
}

// Omega dependence test
int Omega_Test(struct StatementNode* read,struct StatementNode* write,struct LoopIndexVar_New* loop_id,struct Stmt_Var* statement_var)
{
   // FILE *in_file  = fopen("/omega/omega_calc/obj/omega_input.in", "w"); // read only 
    //FILE *in_file  = fopen("omega_input.in", "w"); // read only
    in_file  = fopen("omega_input.in", "w"); // read only
    // test for files not existing.
    if (in_file == NULL) 
    {   
          printMessage(10, "Error! Could not open file\n"); 
          exit(-1);  
          } 
    struct LoopIndexVar_New* loop_id_temp;
    struct Stmt_Var *dep_var;
    struct StringNode *read_string1,*write_string1,*read_string2,*write_string2,*loop_limit;
    struct SizeNode *read_size,*write_size;
    struct StatementNode *read_temp,*write_temp;
    loop_id_temp=loop_id;
    int no_of_loops=0,no_of_dep_var=0,no_of_dep_var_temp=0,no_of_loops_temp=0;
    while(loop_id_temp!=NULL)
    {
        no_of_loops++;
        loop_id_temp=loop_id_temp->next;
    }
    dep_var=statement_var;
    while(dep_var!=NULL){
        no_of_dep_var++;
		dep_var = dep_var->next;
	}
	no_of_dep_var_temp=no_of_dep_var;
	no_of_loops_temp=no_of_loops;
	printMessage(5, "%d %d\n",no_of_loops,no_of_dep_var);
	int tuple_set=1,total_read_var=0,total_write_var=0,total_read_var_temp=0,total_write_var_temp=0,read_index=0,write_index=0;
	dep_var=statement_var;
	while(dep_var!=NULL)
	{
	    
	    total_read_var=count_dep_var(read,dep_var->var->identifier->string);
	    total_write_var=count_dep_var(write,dep_var->var->identifier->string);
	    if(total_read_var==0&&total_write_var==0) 
	    {
	        dep_var=dep_var->next;
	        continue;
	    }  
	    fprintf(in_file,"T%d := {[",tuple_set);    // print "T1 := {["
	    printMessage(5, "read_var=%d write_var=%d",total_read_var,total_write_var);
	    loop_id_temp=loop_id;                      // print "i11,i12,i21,i22,i23,j11,j12,j21,j22,j23"
	    while(loop_id_temp!=NULL)
	    {
	        read_index=0;
	        write_index=0;
	        total_read_var_temp=total_read_var;
	        total_write_var_temp=total_write_var;
	        while(total_write_var_temp!=0)
	        {
	            fprintf(in_file,"%s1%d,",loop_id_temp->loopIndex->string,++write_index);
	            total_write_var_temp--;
	            }
	        while(total_read_var_temp!=0)
	        {
	            fprintf(in_file,"%s2%d",loop_id_temp->loopIndex->string,++read_index);
	            total_read_var_temp--;
	            if(total_read_var_temp!=0||loop_id_temp->next!=NULL)
	                fprintf(in_file,",");    
	        }
	        loop_id_temp=loop_id_temp->next;
	    }
	    fprintf(in_file,"]: ");                 // print "]: "
	    loop_id_temp=loop_id;
	    while(loop_id_temp!=NULL)       // print "2 <= i11,i21,i22 <= 20 && i11 <= j11,j21,j22 <= 20 && "
	    {
	        write_index=0;
	        read_index=0;
	        print_loop_limits(loop_id_temp->L,loop_id);
	        fprintf(in_file," <= ");//%s1,%s2 <= ",loop_id_temp->loopIndex->string,loop_id_temp->loopIndex->string);
	        total_read_var_temp=total_read_var;
	        total_write_var_temp=total_write_var;
	        while(total_write_var_temp!=0)
	        {
	            fprintf(in_file,"%s1%d,",loop_id_temp->loopIndex->string,++write_index);
	            total_write_var_temp--;
	            }
	        while(total_read_var_temp!=0)
	        {
	            fprintf(in_file,"%s2%d",loop_id_temp->loopIndex->string,++read_index);
	            total_read_var_temp--;
	            if(total_read_var_temp!=0)
	                fprintf(in_file,",");    
	        }
	        fprintf(in_file," <= ");
	        print_loop_limits(loop_id_temp->U,loop_id);
	        fprintf(in_file," && ");
	        loop_id_temp=loop_id_temp->next;
	    }
	    printMessage(5, "%s\n",dep_var->var->identifier->string);
	    print_dependency(read,write,loop_id,dep_var->var->identifier->string,total_read_var,total_write_var);
	    fprintf(in_file,"};\nT%d;\n",tuple_set);    //print "}; T1;"
	    tuple_set++;
	    dep_var=dep_var->next;
	}
	fclose(in_file);
	int status = system("../../omega/omega_calc/obj/./oc omega_input.in > omega_output.txt");
	FILE *read_file  = fopen("omega_output.txt", "r"); 
    if (read_file == NULL) 
    {   
          printMessage(10, "Error! Could not open file\n"); 
          exit(-1); 
          }  
	char line[300];
    char *check=NULL; 
    while ( fgets( line, 200, read_file ) != NULL ) 
    { 
          if(line[0]=='{') 
          {
                check=strstr(line,"FALSE");
                if(check!=NULL)
                {
                    return 0;
                    }
          }

          }
	return 1;
}
