#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "token.h"

std::string load (std::ifstream &file);
void print_tokens(const std::vector<token>& list);
void help(char* name);