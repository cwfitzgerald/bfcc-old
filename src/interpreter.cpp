#include "interpreter.h"
#include <vector>
#include <iostream>
#include <array>

using namespace std;

bool bf_interpreter(std::vector<token> input) {
	array<char, 30000> data_array = {};
	int dptr = 0;
	
	for (int iptr = 0; iptr < input.size(); iptr++) {
		auto &inst = input[iptr];

		//cout << "inst: " << inst.type << ":" << inst.data << " dptr: " << dptr << " iptr: " << iptr << endl;
		//for (int i = 0; i < 5; ++i) 
		//	cout << (int) data_array[i] << " ";
		//cout << endl;

		switch (inst.type) {
			case '>':
				dptr += inst.data;
				if (dptr >= 30000)
					dptr -= 30000;
				break;

			case '<':
				dptr -= inst.data;
				if (dptr < 0)
					dptr += 30000;
				break;

			case '+':
				data_array[dptr] += inst.data;
				break;

			case '-':
				data_array[dptr] -= inst.data;
				break;

			case '.':
				for (int count = 0; count < inst.data; count++)
					cout << data_array[dptr];
				break;

			case ',':
				for (int count = 0; count < inst.data; count++)
					cin.get(data_array[dptr]);
				break;

			case '[':
				if (data_array[dptr] == 0)
					iptr = inst.data;
				break;

			case ']':
				if (data_array[dptr] != 0)
					iptr = inst.data;
				break;

		}
	}
	
	
	return true;
}
