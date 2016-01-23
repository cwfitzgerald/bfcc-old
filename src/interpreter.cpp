#include "interpreter.h"
#include <vector>
#include <iostream>
#include <array>

using namespace std;

inline int ptr_check(int i) {
	if (i >= 30000)
		i -= 30000;
	else if (i < 0)
		i += 30000;
	return i;
}

bool bf_interpreter(std::vector<token> &input) {
	array<char, 30000> data_array = {};
	int dptr = 0;
	unsigned long total_loops = 0;
	
	for (int iptr = 0; iptr < input.size(); iptr++) {
		auto &inst = input[iptr];

		switch (inst.type) {
			case MV:
				dptr += inst.data;
				dptr = ptr_check(dptr);
				break;

			case ADD:
				data_array[ptr_check(dptr+inst.data2)] += inst.data;
				break;

			case PRINT:
				for (int count = 0; count < inst.data; count++)
					cout << data_array[ptr_check(dptr+inst.data2)];
				break;

			case GET:
				for (int count = 0; count < inst.data; count++)
					cin.get(data_array[ptr_check(dptr+inst.data2)]);
				break;

			case LBK:
				if (data_array[dptr] == 0)
					iptr += inst.data;
				break;

			case RBK:
				if (data_array[dptr] != 0)
					iptr += inst.data;
				break;
				
			case CLR:
				data_array[ptr_check(dptr+inst.data2)] = 0;
				break;

			case FIND:
				while (data_array[dptr]) {
					dptr += inst.data;
					dptr = ptr_check(dptr);
				}
				break;

			case FPRNT:
				while (data_array[dptr]) {
					if (inst.data) {
						dptr += inst.data;
						dptr = ptr_check(dptr);
					}
					
					cout << data_array[dptr];

					if (inst.data2) {
						dptr += inst.data2;
						dptr = ptr_check(dptr);
					}
				}
				break;
				
			case CP: 
				data_array[ptr_check(dptr+inst.data)] += data_array[dptr];
				break;
			
			case MUL: {
				data_array[ptr_check(dptr+inst.data)] += inst.data2 * data_array[dptr];
				break;
			}

			case NOP:
				break;

		}
		total_loops++;
	}
	cout << "Total Instructions: " << total_loops << endl;
	
	
	return true;
}
