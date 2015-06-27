#ifndef FDISPLAY
#define FDISPLAY
#include "cuda_y.h"
void fdisplay_find_loopId(struct LoopIndexVar_New* liv);
void fdisplay_update_loopId(struct LoopIndexVar_New* liv);
void fdisplay_updated_loop_index(char* string,struct LoopIndexVar_New* loop_index_new);
void fdisplay_SizeNode_updated_loop_index(struct SizeNode* size_node,struct LoopIndexVar_New* loop_index_new);
void fdisplay_StringNode_updated_loop_index(struct StringNode* str_node,struct LoopIndexVar_New* loop_index_new);
void fdisplay_SizeNode(struct SizeNode* size_node);
void fdisplay_StringNode(struct StringNode* str_node);
void fdisplay_SizeNode_1D(struct StringNode* str_node);
void fdisplay_StringNode_1D(struct StringNode* str_node);
void fdisplay_StatementNode_1D(struct StatementNode* stmt);
void fdisplay_type(int t);
void fdisplay_lowerLimitId(char* string);
void fdisplay_upperLimitId(char* string);
void fdisplay_differenceId(char* string);
void fdisplay_part1();
void fdisplay_part2();
void end();
#endif
