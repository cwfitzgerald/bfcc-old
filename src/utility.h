#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "tokenizer.h"

std::string load (std::ifstream &file);
void print_tokens(std::vector<token> list);
void help(char* name);