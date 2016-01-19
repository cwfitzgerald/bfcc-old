#include "interpreter.h"
#include "vector"
#include "tuple"
#include <iostream>

typedef struct {
	vector<int> effects;
	int move_sum;
} loop;

void wipe(vector<token> &program, int start, int end, token tk) {
	program[start] = tk;

	for (int i = start+1; i <= end; i++) 
		program[i] = (token) {NOP};
}

vector<token> optimizer(vector<token> raw) {
	vector<token> final;

	//Optimize only the most nested loops
	int it = 0;
	symbol last = NOP;
	for (auto &i : raw) {
		if (i.type == RBK && last == LBK) {
			loop_optimize(raw, it+i.data, it);
			last = RBK;
		}

		if (i.type == LBK)
			last = LBK;

		it++;
	}

	//Clear NOPs and ADDs and MVs that do nothing
	for (auto &i : raw) {
		switch (i.type) {
			case NOP:
				break;
			case ADD:
			case MV:
				if (!i.data)
					break;
			default:
				final.push_back(i);
		}
	}

	//Rematch brackets
	vector<int> brack_stack;
	for (int i = 0; i < final.size(); i++) {
		if (final[i].type == LBK)
			brack_stack.push_back(i);

		else if (final[i].type == RBK) {
			int lbk_pos = brack_stack.back();

			final[i].data = lbk_pos - i;
			final[lbk_pos].data = i - lbk_pos;

			brack_stack.pop_back();
		}

	}
	
	return final;
}

bool loop_optimize(vector<token> &program, int start, int end) {

	//Check for a clear loop (iterates until it reaches 0): [-] [+] [--+] etc.
	//Replace with CLR command
	int sum = 0;
	bool bk = false;
	for (int i = start+1; i < end && !bk; i++) {
		switch (program[i].type){
			case ADD:
				sum += program[i].data;
				break;

			case NOP:
				break;

			default:
				bk = true;
				break;
		}
	}


	if (sum && !bk) {
		wipe(program, start, end, (token) {CLR, 0});

		return true;
	}

	//Check for a move till empty loop: [>>>>>] [<<<<<] [>>><<]
	//Replace with FIND command
	sum = 0;
	bk = false;
	for (int i = start+1; i < end && !bk; i++) {
		switch (program[i].type){
			case MV:
				sum += program[i].data;
				break;

			case NOP:
				break;

			default:
				bk = true;
				break;
		}
	}

	if (sum && !bk) {
		wipe(program, start, end, (token) {FIND, sum});

		return true;
	}
	
	//Check for a multiply or copy loop: [->>>>+<<+] [->>+>>+] [->+<]
	//Replace with CP or MUL commands then a CLR
	sum = 0;
	bk = false;
	vector<token> tklist; 
	for (int i = start+1; i < end && !bk; i++) {
		if (i == start+1) {
			if (program[i].type == ADD && program[i].data == -1);
			else {
				bk = true;
				break;
			}
		}
		else {
			switch (program[i].type) {
				case ADD:
					if (sum) {
						if (program[i].data == 1) 
							tklist.push_back((token) {CP, sum, 0});
						else 
							tklist.push_back((token) {MUL, sum, program[i].data});
					}
					else
						bk = true;
					break;
				case MV:
					sum += program[i].data;
					break;
				default:
					bk = true;
					break;
			}
		}
	}
	
	if (sum == 0 && !bk) {
		tklist.push_back((token) {CLR});
		for (int i = 0; i <= tklist.size(); i++)
			program[start+i] = tklist[i];
			

		for (int i = start+tklist.size(); i <= end; i++) 
			program[i] = (token) {NOP};
			
		return true;
	}

	return false;
}
