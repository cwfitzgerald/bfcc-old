#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "tokenizer.h"

using namespace std;

//Load a string from a file, including all extra characters
string load (ifstream &file) {
	string str;
	char c;
	while (file.get(c))
		str.push_back(c);

	return str;
}

//Print token names and data
void print_tokens(const vector<token>& list) {
	for (auto &i : list) {
		switch (i.type) {
			case NOP:   cerr << "  NOP: "; 			 break;
			case ADD:   cerr << "  ADD: " << i.data << "\t" << i.data2; break;
			case MV:    cerr << "   MV: " << i.data << "\t" << i.data2; break;
			case PRINT: cerr << "PRINT: " << i.data << "\t" << i.data2; break;
			case GET:   cerr << "  GET: " << i.data << "\t" << i.data2; break;
			case LBK:   cerr << "  LBK: " << i.data << "\t" << i.data2; break;
			case RBK:   cerr << "  RBK: " << i.data << "\t" << i.data2; break;
			case CLR:   cerr << "  CLR: " << i.data2;			 break;
			case FIND:  cerr << " FIND: " << i.data << "\t" << i.data2; break;
			case CP:    cerr << "   CP: " << i.data << "\t" << i.data2; break;
			case MUL:   cerr << "  MUL: " << i.data << "\t" << i.data2; break;
			case FPRNT: cerr << "FPRNT: " << i.data << "\t" << i.data2; break;
		}
		cerr << "\n";
	}
}

//Help options
void help(char name[]) {
	cerr << name << " [infile] [-i infile][options]" << "\n" << "\n";

	cerr 
	<< "Options:" << "\n"
	<< "  -h/H" <<  "\t\t\tDisplay this help message" << "\n"
	<< "  -i [filename]\t\tSet input file" << "\n"
	<< "  -On"  <<  "\t\t\tTurn off Optimization" << "\n"
	<< "  -v/V(0/1/2)  \t\tVerbosity settings " << "\n"
	<<            "\t\t\t\t0 = No verbose output" << "\n"
	<<            "\t\t\t\t1 = Output instruction/execution counts" << "\n"
	<<            "\t\t\t\t2 = 1 and list all instructions before the program runs" << endl
	;
}