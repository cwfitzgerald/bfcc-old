#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include "interpreter.h"

using namespace std;

int main(int argc, char * argv[]) {
	char * filename = NULL;
	bool optimize = true;
	int verbose = 0;
	string outfile;

	if (argc == 1) {
		help(argv[0]);
		return 4;
	}

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
				//Flag for the infile
				case 'i':
					i++;
					filename = argv[i];
					break;

				//Optimize flags
				case 'O':
					if (argv[i][2] == 'n')
						optimize = false;
					break;

				case 'h':
				case 'H':
					help(argv[0]);
					return 0;

				//Print instructions
				case 'v':
				case 'V':
					if (argv[i][2] == '1' || argv[i][2] == '\0')
						verbose = 1;
					else if (argv[i][2] == '2')
						verbose = 2;
					break;

				default:
					cout << "Unrecognized argument: " << argv[i] << endl;
					return 4;
				
			}
		}
		else 
			filename = argv[i];
	}

	if (filename == NULL) {
		cout << "No specified input file." << endl;
		return 4;
	}




	ifstream bf_program (filename);
	if (!bf_program.is_open()) {
		cout << filename << " cannot be opened" << endl;
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
	if (optimize) token_list = optimizer(token_list);
	time_optimize = clock() - t;

	if (verbose == 2)
		print_tokens(token_list);

	t = clock();
	int total_loops = bf_interpreter (token_list);
	time_compute = clock() - t;

	if (verbose >= 1) {
		cout << "Compiled Instructions: " << token_list.size() << endl;
		cout << "Executed Instructions: " << total_loops << endl;
		cout << "    Executed/Compiled: " << (float) total_loops / token_list.size() << endl;
	}

	cout << endl << endl << "Load: " << ((float) time_load/CLOCKS_PER_SEC)*1000 << " ms" << endl;
	cout << "Tokenizer: " << ((float) time_tokenize/CLOCKS_PER_SEC)*1000 << " ms" << endl;
	if (optimize) cout << "Optimizer: " << ((float) time_optimize/CLOCKS_PER_SEC)*1000 << " ms" << endl;
	cout << "Interpreter: " <<  ((float) time_compute/CLOCKS_PER_SEC)*1000 << " ms" << endl;
	
}
