#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include "interpreter.h"

using namespace std;

string load (ifstream &file) {
	string str;
	char c;
	while (file.get(c))
		str.push_back(c);

	return str;
}

int main(int argc, char * argv[]) {
	if (argc != 2) {
		cout << "Wrong amount of arguments" << endl;
		return 2;
	}

	ifstream bf_program (argv[1]);
	if (!bf_program.is_open()) {
		cout << "Inputted file cannot be opened" << endl;
		return 3;
	}

	clock_t t;
	int time_tokenize, time_optimize, time_compute, time_load;

	t = clock();
	string bf_str = load(bf_program);
	time_load = clock() - t;
	
	vector<token> token_list;
	try {
		t = clock();
		token_list = gen_tokens (bf_str);
		time_tokenize = clock() - t;
	}
	catch (const char * errstr) {
		cout << errstr << endl;
		return 1;
	}

	t = clock();
	token_list = optimizer(token_list);
	time_optimize = clock() - t;

	//print_tokens(token_list);

	t = clock();
	bf_interpreter (token_list);
	time_compute = clock() - t;

	cout << endl << endl << "Load: " << ((float) time_load/CLOCKS_PER_SEC)*1000 << " ms" << endl;
	cout << "Tokenizer: " << ((float) time_tokenize/CLOCKS_PER_SEC)*1000 << " ms" << endl;
	cout << "Optimizer: " << ((float) time_optimize/CLOCKS_PER_SEC)*1000 << " ms" << endl;
	cout << "Interpreter: " <<  ((float) time_compute/CLOCKS_PER_SEC)*1000 << " ms" << endl;
	
}
