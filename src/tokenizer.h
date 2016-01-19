#pragma once

#include <vector>
#include <string>

using namespace std;

typedef enum {
	NOP, ADD, MV, PRINT, GET, LBK, RBK, CLR, FIND, CP, MUL
} symbol;

typedef struct {
	symbol type = NOP;
	int data = 0;
	int data2 = 0;
} token;

vector<token> gen_tokens (string program);
void print_tokens(vector<token> list);
