#ifndef DEPENDENCY_ABSTRACTION
#define DEPENDENCY_ABSTRACTION
#include "cuda_y.h"

void remove_LoopIndexVar();
void remove_LoopIndexVar_New();
void get_dependency_var();
void get_read_var(struct StringNode* sn);
void get_write_var();
void get_left_read_write_stmt_var();
int is_match(char* id, struct StringNode* str);
int get_loop_index_dep(char* id);
void get_loop_index_start_end();
void empty();
#endif
