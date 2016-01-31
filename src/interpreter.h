#pragma once

#include <vector>
#include <fstream>
#include "token.h"

int bf_interpreter(std::vector<token>& input, std::ostream& out);
