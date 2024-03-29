#include "interpreter.h"
#include <vector>
#include <tuple>
#include <iosfwd>

using namespace std;

bool loop_optimize(vector<token> &program, int start, int end);
void wipe(vector<token> &program, int start, int end, token tk);
void wipe(vector<token> &program, int start, int end, vector<token> tklist);

//Generic Optimizer Handler
vector<token> optimizer(vector<token> raw) {
	vector<token> final;

	//Run loop optimizer on the innermost loops
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

	//Clear NOPs and ADDs and MVs that do nothing, calculate offset
	int offset = 0;
	for (auto i : raw) {
		switch (i.type) {
			case NOP:
				break;

			case ADD:
				if (i.data)
					if (offset)
						i =  {ADD, i.data, offset};
				break;

			case MV:
				if (i.data){
					offset += i.data;
				}
				break;

			case PRINT:
			case GET:
			case CLR:
				i = token( {i.type, i.data, offset});
				break;

			default:
				if (offset) {
					final.push_back( {MV, offset, 0});
					offset = 0;
				}

		}
		if (i.type != NOP && i.type != MV)
			final.push_back(i);
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

//Optimize a loop from start to end, start and end including
//the brackets. 
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
		wipe(program, start, end,  {CLR, 0});

		return true;
	}

	//Check for a print-move command [.>] [.>>>] [>.>>]
	int before = 0;
	int after = 0;
	bk = true;
	if (end-start == 4) {
		if (program[start+1].type == MV) {

			before = program[start+1].data;

			if (program[start+2].type == PRINT) {
				if (program[start+3].type == MV) {

					after = program[start+3].data;
					bk = false;
				}
			}
		}
	}

	if (end-start == 3) 
		if (program[start+1].type == PRINT)
			if (program[start+2].type == MV) {
				after = program[start+2].data;
				bk = false;
			}

	if (!bk) {
		wipe(program, start, end,  {FPRNT, before, after});

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
		wipe(program, start, end,  {FIND, sum});

		return true;
	}
	
	//Check for a multiply or copy loop: [->>>>+<<+] [->>+>>+] [->+<]
	//Replace with CP or MUL commands then a CLR
	bk = false;
	vector<token> tklist; 
	int leftcell = 0;
	int rightcell = 0;
	int curcell = 0; 
	for (int i = start+1; i < end && !bk; i++) {
		switch (program[i].type) {
			case MV:
				curcell += program[i].data;
				if (leftcell > curcell)
					leftcell = curcell;
				if (rightcell < curcell)
					rightcell = curcell;
				break;
			case ADD:
				break;
				
			default:
				bk = true;
		}
	}
	
	if (!bk && curcell == 0) {
		std::vector<int> effects(rightcell-leftcell+1, 0);
		int offset = leftcell * -1;
		int ptr = offset;

		for (auto &i : effects)
			i = 0;
	
		for (int i = start+1; i < end && !bk; i++) {
			switch (program[i].type) {
				case ADD:
					effects[ptr] += program[i].data;
					break;
				case MV:
					ptr += program[i].data;
					break;
				default:
					bk = true;
					break;
			}
		}
		
		ptr = leftcell;
		for (auto &val : effects) {
			if (val != 0 && ptr != 0) {
				if (val == 1) 
					tklist.push_back( {CP, ptr, 0});
				else
					tklist.push_back( {MUL, ptr, val});
			}
			else if (ptr == 0 && val != -1) {
				bk = true;
				break; 
			}

			ptr++;
		}	
	
		if (!bk) {
			tklist.push_back( {CLR});

			wipe(program, start, end, tklist);
		
			return true;
		}
	}

	return false;
}

//Wipe an optimized loop by writing the command (or list of command)
//then fill the rest of the loop with NOP commands, as a later stage
//will optimize that away.
//Single Command:
void wipe(vector<token> &program, int start, int end, token tk) {
	program[start] = tk;

	for (int i = start+1; i <= end; i++) 
		program[i] =  {NOP};
}
//Multiple Commands:
void wipe(vector<token> &program, int start, int end, vector<token> tklist) {
	for (int i = 0; i < tklist.size(); i++) 
		program[start+i] = tklist[i];

	for (int i = start+tklist.size(); i <= end; i++) 
		program[i] =  {NOP};
}
