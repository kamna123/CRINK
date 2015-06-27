#ifndef DEPENDENCE_INTERFACE
#define DEPENDENCE_INTERFACE
#include "cuda_y.h"
void Dependence_Testing_Interface(int verbosity_no, char *test_name, struct StatementNode* read,struct StatementNode* write,struct LoopIndexVar_New* loop_id);
#endif
