#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
//#include "cuda_y.h"
#include "GCD_Banerjee_Test.h"
#include "Dependence_Testing_Interface.h"
#include "Omega_Test.h"
void Dependence_Testing_Interface(int verbosity_no, char *test_name, struct StatementNode* read,struct StatementNode* write,struct LoopIndexVar_New* loop_id)
{
    int dependency_check=0;
    noOfNestedLoops=0;
    struct LoopIndexVar_New* loop_temp;
    loop_temp=loop_id;
    /****** COUTNING NO OF NESTED LOOPS ********/
    while(loop_temp!=NULL)
    {
        noOfNestedLoops++;
        loop_temp=loop_temp->next;
    }
    /******************************************/
    if(strcmp(test_name,"gcd")==0)
    {
	    if(GCD_Test(read,write,loop_id)) 
	    {
	        printMessage(10, "\n-------------------- GCD Test Output: Dependency may exist\n");
	        DependencyExists='y';
	        }
    	else    
	        printMessage(10, "\n-------------------- GCD Test Output: Dependency doesn't exist\n");
	        }
	else if(strcmp(test_name,"banerjee")==0)
    {
	    if(Banerjee_Test(read,write,loop_id))
	    {
	        printMessage(10, "\n-------------------- Banerjee Test Output: Dependency may exist\n");
	        DependencyExists='y';
	        }
    	else
	        printMessage(10, "\n-------------------- Banerjee Test Output: Dependency doesn't exist\n");
	        }
	else if(strcmp(test_name,"omega")==0)
    {
        if(Omega_Test(read_var,write_var,loop_index_new,stmt_var))
        {
	        printMessage(10, "\n-------------------- Omega Test Output: Dependency may exist\n");
	        DependencyExists='y';
	        }
    	else    
	        printMessage(10, "\n-------------------- Omega Test Output: Dependency doesn't exist\n");
    }
	    
	}    
