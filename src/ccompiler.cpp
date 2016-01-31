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

bool bf_ccompiler(const vector<token>& input, ostream& out) {
	//////////////////////
	//Start the compiler//
	//////////////////////

	//Names for different objects
	char  darray_name[] = "d";
	char  pf_name[] = "c";
	char  p_name[] = "p";

	//Add header
	out << "#include <stdio.h>" << "\n" 
	//Add get char macro (stolen from esotope-bfc)
	    << "#define GETC() (fflush(stdout), fgetc(stdin))" << "\n" << "\n"
	//Add pointer check function
		<< "inline int "<<pf_name<<"(int i) {" << "\n"
		<< "\tif (i >= 30000)" << "\n"
		<< "\t\ti -= 30000;" << "\n"
		<< "\telse if (i < 0)" << "\n"
		<< "\t\ti += 30000;" << "\n"
		<< "\treturn i;" << "\n"
		<< "}" << "\n"
	//Start main array
	    << "int main() {" << "\n"
	    << "\tchar  "<<darray_name<<"[30000] = {0};" << "\n"
	    << "\tint   "<<p_name<<" = 0;" << "\n"
	    << "\tint tmpptr = 0;" << "\n"
	    << "\tint      i = 0;" << "\n";

	int indent = 1;

	for (auto& inst : input) {
		switch (inst.type) {
			case NOP: break;

			case ADD:
				INDENT
				if (inst.data2)
					out << darray_name<<"["<<pf_name<<"("<<p_name<<"+"<<inst.data2<<")] += " << inst.data << ";" << "\n";
				else
					out << darray_name<<"["<<p_name<<"] += "<<inst.data<< ";" << "\n";
				break;

			case MV:
				INDENT
				out << ""<<p_name<<" = "<<pf_name<<"("<<p_name<<"+" << inst.data << ");" << "\n";
				break;

			case PRINT:
				if (inst.data > 1) {
					if (inst.data2) {
						INDENT
						out << "tmpptr = "<<pf_name<<"("<<p_name<<"+" << inst.data2 << ");" << "\n";
					}

					INDENT
					out << "for (i = 0; i < " << inst.data << "; i++)" << "\n";
					indent++;

					INDENT
					if (inst.data2)
						out << "putchar("<<darray_name<<"[tmpptr]);" << "\n";
					else 
						out << "putchar("<<darray_name<<"["<<p_name<<"]);" << "\n";
					indent--;
				}
				else {
					INDENT
					if (inst.data2)
						out << "putchar("<<darray_name<<"["<<pf_name<<"("<<p_name<<"+" << inst.data2 << ")]);" << "\n";
					else 
						out << "putchar("<<darray_name<<"["<<p_name<<"]);" << "\n";
				}
				break;

			case FPRNT:
				INDENT
				out << "while ("<<darray_name<<"["<<p_name<<"]) {" << "\n";
				indent++;

				if (inst.data) {
					INDENT 
					out << ""<<p_name<<" += " << inst.data << ";" << "\n";
					INDENT
					out << ""<<p_name<<" = "<<pf_name<<"("<<p_name<<");" << "\n";
				}

				INDENT
				out << "fputc("<<darray_name<<"["<<p_name<<"],stdout);" << "\n";

				if (inst.data2) {
					INDENT 
					out << ""<<p_name<<" += " << inst.data2 << ";" << "\n";
					INDENT
					out << ""<<p_name<<" = "<<pf_name<<"("<<p_name<<");" << "\n";
				}

				indent--;
				INDENT
				out << "}" << "\n";
				break;

			case FIND:
				INDENT
				out << "while ("<<darray_name<<"["<<p_name<<"]) " << "\n";
				indent++;

				INDENT
				out << ""<<p_name<<" = "<<pf_name<<"("<<p_name<<"+" << inst.data << ");" << "\n";
				indent--;
				break;


			case LBK:
				INDENT
				out << "while ("<<darray_name<<"["<<p_name<<"]) {" << "\n";
				indent++;
				break;

			case RBK:
				indent--;
				INDENT
				out << "}" << "\n";
				break;

			case GET:
				INDENT
				out << ""<<darray_name<<"["<<pf_name<<"("<<p_name<<"+"<<inst.data2<<")] = GETC();" << "\n";
				break;

			case CLR:
				INDENT
				out << ""<<darray_name<<"["<<pf_name<<"("<<p_name<<"+"<<inst.data2<<")] = 0;" << "\n";
				break;

			case MUL:
				INDENT
				out << ""<<darray_name<<"["<<pf_name<<"("<<p_name<<"+"<<inst.data<<")] += "<<darray_name<<"["<<p_name<<"] * "<<inst.data2<< ";" << "\n";
				break;

			case CP:
				INDENT
				out << ""<<darray_name<<"["<<pf_name<<"("<<p_name<<"+"<<inst.data<<")] += "<<darray_name<<"["<<p_name<<"];" << "\n";
				break;

		}
	}

	out << "\treturn 1;" << "\n"
	    << "}" << endl;

	return true;
}