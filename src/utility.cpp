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
			case NOP:   cout << "  NOP: "; 			 break;
			case ADD:   cout << "  ADD: " << i.data << "\t" << i.data2; break;
			case MV:    cout << "   MV: " << i.data << "\t" << i.data2; break;
			case PRINT: cout << "PRINT: " << i.data << "\t" << i.data2; break;
			case GET:   cout << "  GET: " << i.data << "\t" << i.data2; break;
			case LBK:   cout << "  LBK: " << i.data << "\t" << i.data2; break;
			case RBK:   cout << "  RBK: " << i.data << "\t" << i.data2; break;
			case CLR:   cout << "  CLR: " << i.data2;			 break;
			case FIND:  cout << " FIND: " << i.data << "\t" << i.data2; break;
			case CP:    cout << "   CP: " << i.data << "\t" << i.data2; break;
			case MUL:   cout << "  MUL: " << i.data << "\t" << i.data2; break;
			case FPRNT: cout << "FPRNT: " << i.data << "\t" << i.data2; break;
		}
		cout << endl;
	}
}

void help(char name[]) {
	cout << name << " [infile] [-i infile][options]" << endl << endl;

	cout 
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