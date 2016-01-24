#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "tokenizer.h"

using namespace std;

string load (ifstream &file);
void print_tokens(vector<token> list);
void help(char* name);
static volatile int keepRunning;