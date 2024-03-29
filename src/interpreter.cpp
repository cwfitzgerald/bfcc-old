#include "interpreter.h"
#include <vector>
#include <ostream>
#include <iostream>
#include <array>

using namespace std;

//Check if data pointer is within bounds
//if it isn't, then loop back to other side
inline int ptr_check(int i) {
	return i & 32767;
}

int bf_interpreter(vector<token> &input, ostream& out) {
	//Create data array, and zero it.
	array<char, 32768> data_array;
	for (auto &i : data_array)
		i = 0;
	int dptr = 0;
	unsigned long total_loops = 0;
	
	//Loop through the instructions
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
					out << data_array[ptr_check(dptr+inst.data2)];
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
	
	return total_loops;
}
