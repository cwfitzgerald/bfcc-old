#pragma once

typedef enum {
	NOP, ADD, MV, PRINT, FPRNT, GET, LBK, RBK, CLR, FIND, CP, MUL
} symbol;

struct token {
	symbol type = NOP;
	int data = 0;
	int data2 = 0;
};