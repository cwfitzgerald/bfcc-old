#pragma once

#include <vector>
#include <string>

using namespace std;

typedef enum {
	ADD, MV, PRINT, GET, CLR
} bf_inst;

typedef struct {
	char type = 0;
	int data = 0;
} token;

vector<token> gen_tokens (string program);
