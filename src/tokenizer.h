#pragma once

#include <vector>
#include <string>

typedef enum {
	NOP, ADD, MV, PRINT, FPRNT, GET, LBK, RBK, CLR, FIND, CP, MUL
} symbol;

typedef struct {
	symbol type = NOP;
	int data = 0;
	int data2 = 0;
} token;

std::vector<token> gen_tokens (std::string program);
void print_tokens(std::vector<token> list);
