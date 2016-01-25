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

bool bf_ccompiler(vector<token> input, ostream& out) {
	//////////////////////
	//Start the compiler//
	//////////////////////

	//Names for different objects
	char  darray_name[] = "d";
	char  pf_name[] = "c";
	char  p_name[] = "p";

	//Add header
	out << "#include <stdio.h>" << endl 
	//Add get char macro (stolen from esotope-bfc)
	    << "#define GETC() (fflush(stdout), fgetc(stdin))" << endl << endl
	//Add pointer check function
		<< "inline int "<<pf_name<<"(int i) {" << endl
		<< "\tif (i >= 30000)" << endl
		<< "\t\ti -= 30000;" << endl
		<< "\telse if (i < 0)" << endl
		<< "\t\ti += 30000;" << endl
		<< "\treturn i;" << endl
		<< "}" << endl
	//Start main array
	    << "int main() {" << endl
	    << "\tchar  "<<darray_name<<"[30000] = {0};" << endl
	    << "\tint   "<<p_name<<" = 0;" << endl
	    << "\tint tmpptr = 0;" << endl
	    << "\tint      i = 0;" << endl;

	int indent = 1;

	for (auto& inst : input) {
		switch (inst.type) {
			case NOP: break;

			case ADD:
				INDENT
				if (inst.data2)
					out << darray_name<<"["<<pf_name<<"("<<p_name<<"+"<<inst.data2<<")] += " << inst.data << ";" << endl;
				else
					out << darray_name<<"["<<p_name<<"] += "<<inst.data<< ";" << endl;
				break;

			case MV:
				INDENT
				out << ""<<p_name<<" = "<<pf_name<<"("<<p_name<<"+" << inst.data << ");" << endl;
				break;

			case PRINT:
				if (inst.data > 1) {
					if (inst.data2) {
						INDENT
						out << "tmpptr = "<<pf_name<<"("<<p_name<<"+" << inst.data2 << ");" << endl;
					}

					INDENT
					out << "for (i = 0; i < " << inst.data << "; i++)" << endl;
					indent++;

					INDENT
					if (inst.data2)
						out << "putchar("<<darray_name<<"[tmpptr]);" << endl;
					else 
						out << "putchar("<<darray_name<<"["<<p_name<<"]);" << endl;
					indent--;
				}
				else {
					INDENT
					if (inst.data2)
						out << "putchar("<<darray_name<<"["<<pf_name<<"("<<p_name<<"+" << inst.data2 << ")]);" << endl;
					else 
						out << "putchar("<<darray_name<<"["<<p_name<<"]);" << endl;
				}
				break;

			case FPRNT:
				INDENT
				out << "while ("<<darray_name<<"["<<p_name<<"]) {" << endl;
				indent++;

				if (inst.data) {
					INDENT 
					out << ""<<p_name<<" += " << inst.data << ";" << endl;
					INDENT
					out << ""<<p_name<<" = "<<pf_name<<"("<<p_name<<");" << endl;
				}

				INDENT
				out << "fputc("<<darray_name<<"["<<p_name<<"],stdout);" << endl;

				if (inst.data2) {
					INDENT 
					out << ""<<p_name<<" += " << inst.data2 << ";" << endl;
					INDENT
					out << ""<<p_name<<" = "<<pf_name<<"("<<p_name<<");" << endl;
				}

				indent--;
				INDENT
				out << "}" << endl;
				break;

			case FIND:
				INDENT
				out << "while ("<<darray_name<<"["<<p_name<<"]) " << endl;
				indent++;

				INDENT
				out << ""<<p_name<<" = "<<pf_name<<"("<<p_name<<"+" << inst.data << ");" << endl;
				indent--;
				break;


			case LBK:
				INDENT
				out << "while ("<<darray_name<<"["<<p_name<<"]) {" << endl;
				indent++;
				break;

			case RBK:
				indent--;
				INDENT
				out << "}" << endl;
				break;

			case GET:
				INDENT
				out << ""<<darray_name<<"["<<pf_name<<"("<<p_name<<"+"<<inst.data2<<")] = GETC();" << endl;
				break;

			case CLR:
				INDENT
				out << ""<<darray_name<<"["<<pf_name<<"("<<p_name<<"+"<<inst.data2<<")] = 0;" << endl;
				break;

			case MUL:
				INDENT
				out << ""<<darray_name<<"["<<pf_name<<"("<<p_name<<"+"<<inst.data<<")] += "<<darray_name<<"["<<p_name<<"] * "<<inst.data2<< ";" << endl;
				break;

			case CP:
				INDENT
				out << ""<<darray_name<<"["<<pf_name<<"("<<p_name<<"+"<<inst.data<<")] += "<<darray_name<<"["<<p_name<<"];" << endl;
				break;

		}
	}

	out << "\treturn 1;" << endl
	    << "}" << endl;

	return true;
}