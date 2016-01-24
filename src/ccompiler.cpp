#include <string>
#include <iostream>
#include <fstream>
#include "tokenizer.h"

using namespace std;

//Don't judge me, I'm lazy with typing the same thing over and over
#define INDENT indenter(indent, out);

inline void indenter (int num, ostream& o) {
	for (int i = 0; i < num; i++)
		o << "\t";
}

bool bf_ccompiler(vector<token> input, char * outfile_name) {
	streambuf * buf;
	ofstream outfile;

	//TODO: Add error support
	if (outfile_name != NULL) {
		outfile.open(outfile_name);
		buf = outfile.rdbuf();
	}
	else 
		buf = cout.rdbuf();

	ostream out(buf);

	//////////////////////
	//Start the compiler//
	//////////////////////

	//Add header
	out << "#include <stdio.h>" << endl 
	//Add get char macro (stolen from esotope-bfc)
	    << "#define GETC() (fflush(stdout), fgetc(stdin))" << endl << endl
	//Add pointer check function
		<< "inline int ptr_check(int i) {" << endl
		<< "\tif (i >= 30000)" << endl
		<< "\t\ti -= 30000;" << endl
		<< "\telse if (i < 0)" << endl
		<< "\t\ti += 30000;" << endl
		<< "\treturn i;" << endl
		<< "}" << endl
	//Start main array
	    << "int main() {" << endl
	    << "\tchar  darray[30000] = {0};" << endl
	    << "\tint   dptr = 0;" << endl
	    << "\tint tmpptr = 0;" << endl
	    << "\tint      i = 0;" << endl;

	int indent = 1;

	for (auto& inst : input) {
		switch (inst.type) {
			case NOP: break;

			case ADD:
				INDENT
				if (inst.data2)
					out << "darray[ptr_check(dptr+"<<inst.data2<<")] += " << inst.data << ";" << endl;
				else
					out << "darray[dptr] += " << inst.data << ";" << endl;
				break;

			case MV:
				INDENT
				out << "dptr = ptr_check(dptr+" << inst.data << ");" << endl;
				break;

			case PRINT:
				if (inst.data > 1) {
					if (inst.data2) {
						INDENT
						out << "tmpptr = ptr_check(dptr+" << inst.data2 << ");" << endl;
					}

					INDENT
					out << "for (i = 0; i < " << inst.data << "; i++)" << endl;
					indent++;

					INDENT
					if (inst.data2)
						out << "putchar(darray[tmpptr]);" << endl;
					else 
						out << "putchar(darray[dptr]);" << endl;
					indent--;
				}
				else {
					INDENT
					if (inst.data2)
						out << "putchar(darray[ptr_check(dptr+" << inst.data2 << ")]);" << endl;
					else 
						out << "putchar(darray[dptr]);" << endl;
				}
				break;

			case FPRNT:
				INDENT
				out << "while (darray[dptr]) {" << endl;
				indent++;

				if (inst.data) {
					INDENT 
					out << "dptr += " << inst.data << ";" << endl;
					INDENT
					out << "dptr = ptr_check(dptr);" << endl;
				}

				INDENT
				out << "fputc(darray[dptr],stdout);" << endl;

				if (inst.data2) {
					INDENT 
					out << "dptr += " << inst.data2 << ";" << endl;
					INDENT
					out << "dptr = ptr_check(dptr);" << endl;
				}

				indent--;
				INDENT
				out << "}" << endl;
				break;

			case FIND:
				INDENT
				out << "while (darray[dptr]) " << endl;
				indent++;

				INDENT
				out << "dptr = ptr_check(dptr+" << inst.data << ");" << endl;
				indent--;
				break;


			case LBK:
				INDENT
				out << "while (darray[dptr]) {" << endl;
				indent++;
				break;

			case RBK:
				indent--;
				INDENT
				out << "}" << endl;
				break;

			case GET:
				INDENT
				out << "darray[ptr_check(dptr+"<<inst.data2<<")] = GETC();" << endl;
				break;

			case CLR:
				INDENT
				out << "darray[ptr_check(dptr+"<<inst.data2<<")] = 0;" << endl;
				break;

			case MUL:
				INDENT
				out << "darray[ptr_check(dptr+"<<inst.data<<")] += darray[dptr] * "<<inst.data2<< ";" << endl;
				break;

			case CP:
				INDENT
				out << "darray[ptr_check(dptr+"<<inst.data<<")] += darray[dptr];" << endl;
				break;

		}
	}

	out << "\treturn 1;" << endl
	    << "}" << endl;

	return true;
}