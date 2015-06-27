#ifndef GCD_BANERJEE
#define GCD_BANERJEE
#include "cuda_y.h"
int euclid_GCD(int a, int b);
int isLoopIndex(struct StringNode* index,struct LoopIndexVar_New* loop_id);
struct SizeNode* find_corresponding_read_dep_var(struct StringNode* write_string,struct StatementNode* read);
int GCD_Test(struct StatementNode* read,struct StatementNode* write,struct LoopIndexVar_New* loop_id);
int find_loop_level(struct StringNode* index,struct LoopIndexVar_New* loop_id);
int fill_coeff_array(int *arr,struct StringNode *stmt_string,struct LoopIndexVar_New* loop_id);
int positive_func(int x);
int negative_func(int x);
int Banerjee_Test(struct StatementNode* read,struct StatementNode* write,struct LoopIndexVar_New* loop_id);
#endif
