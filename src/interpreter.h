#pragma once

#include "tokenizer.h"
#include "compiler.h"
#include "optimizer.h"
#include "utility.h"
#include <vector>
#include <ostream>


int bf_interpreter(std::vector<token>& input, std::ostream& out);
