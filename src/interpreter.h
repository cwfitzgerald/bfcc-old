#pragma once

#include "tokenizer.h"
#include "compiler.h"
#include "optimizer.h"
#include "utility.h"
#include <vector>
#include <ostream>

using namespace std;

int bf_interpreter(vector<token>& input, ostream& out);
