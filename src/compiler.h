#pragma once

#include <vector>
#include <fstream>
#include "token.h"

bool bf_ccompiler(const std::vector<token>& input, std::ostream& out);