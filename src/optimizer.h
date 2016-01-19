#pragma once

#include "tokenizer.h"
#include <vector>

vector<token> optimizer(vector<token> raw);
bool loop_optimize(vector<token> &program, int start, int end);