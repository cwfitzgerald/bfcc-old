#include <string>
#include <iosfwd>
#include <fstream>
#include "tokenizer.h"

using namespace std;

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
		<< "\treturn i & 32767;" "\n"
		<< "}" << "\n"
	//Start main array
	    << "int main() {" << "\n"
	    << "\tchar  "<<darray_name<<"[32768] = {0};" << "\n"
	    << "\tint   "<<p_name<<" = 0;" << "\n"
	    << "\tint tmpptr = 0;" << "\n"
	    << "\tint      i = 0;" << "\n";

	int indent = 1;
	auto indenter = [&indent, &out](){for (int i = 0; i < indent; i++) out << "\t";};

	for (auto& inst : input) {
		switch (inst.type) {
			case NOP: break;

			case ADD:
				indenter();
				if (inst.data2)
					out << darray_name<<"["<<pf_name<<"("<<p_name<<"+"<<inst.data2<<")] += " << inst.data << ";" << "\n";
				else
					out << darray_name<<"["<<p_name<<"] += "<<inst.data<< ";" << "\n";
				break;

			case MV:
				indenter();
				out << ""<<p_name<<" = "<<pf_name<<"("<<p_name<<"+" << inst.data << ");" << "\n";
				break;

			case PRINT:
				if (inst.data > 1) {
					if (inst.data2) {
						indenter();
						out << "tmpptr = "<<pf_name<<"("<<p_name<<"+" << inst.data2 << ");" << "\n";
					}

					indenter();
					out << "for (i = 0; i < " << inst.data << "; i++)" << "\n";
					indent++;

					indenter();
					if (inst.data2)
						out << "putchar("<<darray_name<<"[tmpptr]);" << "\n";
					else 
						out << "putchar("<<darray_name<<"["<<p_name<<"]);" << "\n";
					indent--;
				}
				else {
					indenter();
					if (inst.data2)
						out << "putchar("<<darray_name<<"["<<pf_name<<"("<<p_name<<"+" << inst.data2 << ")]);" << "\n";
					else 
						out << "putchar("<<darray_name<<"["<<p_name<<"]);" << "\n";
				}
				break;

			case FPRNT:
				indenter();
				out << "while ("<<darray_name<<"["<<p_name<<"]) {" << "\n";
				indent++;

				if (inst.data) {
					indenter(); 
					out << ""<<p_name<<" += " << inst.data << ";" << "\n";
					indenter();
					out << ""<<p_name<<" = "<<pf_name<<"("<<p_name<<");" << "\n";
				}

				indenter();
				out << "fputc("<<darray_name<<"["<<p_name<<"],stdout);" << "\n";

				if (inst.data2) {
					indenter(); 
					out << ""<<p_name<<" += " << inst.data2 << ";" << "\n";
					indenter();
					out << ""<<p_name<<" = "<<pf_name<<"("<<p_name<<");" << "\n";
				}

				indent--;
				indenter();
				out << "}" << "\n";
				break;

			case FIND:
				indenter();
				out << "while ("<<darray_name<<"["<<p_name<<"]) " << "\n";
				indent++;

				indenter();
				out << ""<<p_name<<" = "<<pf_name<<"("<<p_name<<"+" << inst.data << ");" << "\n";
				indent--;
				break;


			case LBK:
				indenter();
				out << "while ("<<darray_name<<"["<<p_name<<"]) {" << "\n";
				indent++;
				break;

			case RBK:
				indent--;
				indenter();
				out << "}" << "\n";
				break;

			case GET:
				indenter();
				out << ""<<darray_name<<"["<<pf_name<<"("<<p_name<<"+"<<inst.data2<<")] = GETC();" << "\n";
				break;

			case CLR:
				indenter();
				out << ""<<darray_name<<"["<<pf_name<<"("<<p_name<<"+"<<inst.data2<<")] = 0;" << "\n";
				break;

			case MUL:
				indenter();
				out << ""<<darray_name<<"["<<pf_name<<"("<<p_name<<"+"<<inst.data<<")] += "<<darray_name<<"["<<p_name<<"] * "<<inst.data2<< ";" << "\n";
				break;

			case CP:
				indenter();
				out << ""<<darray_name<<"["<<pf_name<<"("<<p_name<<"+"<<inst.data<<")] += "<<darray_name<<"["<<p_name<<"];" << "\n";
				break;

		}
	}

	out << "\treturn 1;" << "\n"
	    << "}" << endl;

	return true;
}