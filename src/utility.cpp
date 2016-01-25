#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "tokenizer.h"

string load (ifstream &file) {
	string str;
	char c;
	while (file.get(c))
		str.push_back(c);

	return str;
}

void print_tokens(vector<token> list) {
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
		cerr << endl;
	}
}

void help(char name[]) {
	cerr << name << " [infile] [-i infile][options]" << endl << endl;

	cerr 
	<< "Options:" << endl
	<< "  -h/H" <<  "\t\t\tDisplay this help message" << endl
	<< "  -i [filename]\t\tSet input file" << endl
	<< "  -On"  <<  "\t\t\tTurn off Optimization" << endl
	<< "  -v/V(0/1/2)  \t\tVerbosity settings " << endl
	<<            "\t\t\t\t0 = No verbose output" << endl
	<<            "\t\t\t\t1 = Output instruction/execution counts" << endl
	<<            "\t\t\t\t2 = 1 and list all instructions before the program runs" << endl
	;
}