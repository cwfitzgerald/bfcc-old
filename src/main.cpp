#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
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
	int time_tokenize, time_compute;

	string bf_str = load(bf_program);
	
	vector<token> token_list;
	try {
		t = clock();
		token_list = gen_tokens (bf_str);
		time_tokenize = clock() - t;
	}
	catch (string errstr) {
		cout << errstr << endl;
		return 1;
	}

	//for (auto &i : token_list) 
		//cout << i.type << ": " << i.data << endl;

	t = clock();
	bf_interpreter (token_list);
	time_compute = clock() - t;
		
	cout << endl << "Tokenizer: " << (float) time_tokenize/CLOCKS_PER_SEC << " sec" << endl;
	cout << "Interpreter: " << (float) time_compute/CLOCKS_PER_SEC << " sec" << endl;
	
}
