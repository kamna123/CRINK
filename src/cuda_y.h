#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES
/*#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>*/
struct Var{
	int type;
	struct StringNode* identifier;
	int var_value;
	struct Var* next;
};

struct Stmt_Var{
	struct Var* var;
	struct Stmt_Var* next;
};


extern struct Var* variables;
extern struct Var* original_variables;
extern struct Var* variables_temp;
extern struct Stmt_Var* stmt_var;
extern struct Stmt_Var* left_stmt_var;
extern struct Stmt_Var* write_stmt_var;
extern struct Stmt_Var* read_stmt_var;

// no use
struct LoopIndexVar {
	struct StringNode* loopIndex;
	struct StringNode* size;
	struct LoopIndexVar* next;
};
extern struct LoopIndexVar* loop_index;

struct StrNode{
	char string[10];
	struct StrNode* next;
};

FILE* out, *in;
extern char DependencyExists;
extern int id_max;
extern int line_num;
extern int start_num;
extern int end_num;
extern int Total_Phi;
extern int type;
extern int noOfNestedLoops;
extern int verbosity;
extern char VariableDependenceDist;
extern char AffineKernel;

extern struct StatementNode* left_var;
extern struct StatementNode* write_var;
extern struct StatementNode* read_var;
extern struct StatementNode* parallel_stmt;

struct StatementNode {
	struct StatementNode* next;
	struct StringNode* stringNode;
};

struct StringNode {
	char* string;
	struct StringNode* next;
	struct SizeNode* size;
};
struct Count_Loops
{  int count;
  // struct StatementNode* count;
  struct StatementNode* parallel_stmt;
  struct Stmt_Var* stmt_var;
struct Stmt_Var* left_stmt_var;
struct Stmt_Var* write_stmt_var;
struct Stmt_Var* read_stmt_var;
struct LoopIndexVar* loop_index;
struct StatementNode* left_var;
struct StatementNode* write_var;
struct StatementNode* read_var;
struct Var* variables;
struct LoopIndexVar_New* loop_index_new;
struct Phi_Values* lambda_var;
 struct Count_Loops* next;
};
struct SizeNode {
	struct StringNode* sizeString;
	struct SizeNode* next;
};

extern struct Count_Loops* head;

struct LoopIndexVar_New {
	struct StringNode* loopIndex;
	struct StringNode* L;
	struct StringNode* U;
	struct StringNode* D;
	char op;
	// + : increment, -: decrement
	int relop;
	// < is 1 , > is 2
	// <= is 3, >= is 4
	struct LoopIndexVar_New* next;
};
extern struct LoopIndexVar_New* loop_index_new;
extern struct LoopIndexVar_New* loopIndex_temp;
extern struct LoopIndexVar_New* loop_index_new_start;
extern struct LoopIndexVar_New* loop_index_new_end;
;

// no use
struct ParallelData {
	struct LoopIndexVar_New* loop_index;
	struct StatementNode* parallel_stmt;
	struct StatementNode* left_var;
	struct StatementNode* write_var;
	struct StatementNode* read_var;
	struct Stmt_Var* stmt_var;
	struct Stmt_Var* left_stmt_var;
	struct Stmt_Var* write_stmt_var;
	struct Stmt_Var* read_stmt_var;
	int start_num;
	int end_num;
	struct ParallelData* next;
};

struct Phi_Values
{
    char *loop_index;
    int phi_val;
    struct Phi_Values *next;
};
extern struct Phi_Values* lambda_var;

struct ReferencePair
{
    struct DDV *ddv;
    struct ReferencePair *next;
};

struct DDV
{
    struct DDV_Values *ddv_values;
    struct DDV *next;
};

struct DDV_Values
{
    int value;
    struct DDV_Values *next;
};

extern struct ReferencePair *RefPair;
extern struct DDV *DDVvector;
// no use
extern struct ParallelData* parallel_data;
#endif
