#include "tokenizer.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void print_tokens(vector<token> list) {
	for (auto &i : list) {
		switch (i.type) {
			case NOP:   cout << "  NOP: "; 			 break;
			case ADD:   cout << "  ADD: " << i.data; break;
			case MV:    cout << "   MV: " << i.data; break;
			case PRINT: cout << "PRINT: " << i.data; break;
			case GET:   cout << "  GET: " << i.data; break;
			case LBK:   cout << "  LBK: " << i.data; break;
			case RBK:   cout << "  RBK: " << i.data; break;
			case CLR:   cout << "  CLR: ";			 break;
			case FIND:  cout << " FIND: " << i.data; break;
			case CP:    cout << "   CP: " << i.data << "\t" << i.data2; break;
			case MUL:   cout << "  MUL: " << i.data << "\t" << i.data2; break;
		}
		cout << endl;
	}
}

vector<token> gen_tokens (string program) {
	vector<token> tokenlist;
	token tk;

	vector<int> brack_stack;
	int numtoken = 0;

	int charnum = 1;
	int linenum = 1;

	for (auto &i : program) {
		int leftbk;
		switch(i){
			case '[': {
				tk = (token) {LBK, 0};
				brack_stack.push_back(numtoken);
				tokenlist.push_back(tk);
				break;
			}
				
			case ']': {
				if (!brack_stack.size()) {
					throw "error: invalid token ']' at Line " + to_string(linenum) + ", Char: " + to_string(charnum) + "\nNo matching '[' bracket";
				}

				leftbk = brack_stack.back(); 				//Place of matching bracket
				brack_stack.pop_back();						//Pop value from stack
				
				tk = (token) {RBK, leftbk-numtoken};		//Add token with redirect.
				tokenlist[leftbk].data = numtoken-leftbk;	//Add redirect to matching bracket
				tokenlist.push_back(tk);
				break;
			}
				
			case '+': case '-': case '<': case '>': case ',': case '.': {
				symbol tt = NOP;
				int multi = 1;
				
				switch (i) {
					case '-':
						multi = -1;
					case '+':
						tt = ADD;
						break;
						
					case '<':
						multi = -1;
					case '>':
						tt = MV;
						break;
						
					case '.':
						tt = PRINT;
						break;
					case ',':
						tt = GET;
						break;
				}
				
				if (tokenlist.size() && tokenlist.back().type == tt) {
					auto& lasttoken = tokenlist.back();
					
					if (lasttoken.type == tt)
						lasttoken.data += multi;
				}
				else 
					tokenlist.push_back((token) {tt, multi});
				
				break;  
			}
				
			case '\n': {
				linenum++;
				charnum = 1;
				break;   
			}                                    
		}
		charnum++;
		numtoken = tokenlist.size();
	}
	
	if (brack_stack.size()) {
		throw "error: invalid token '['\nno matching ']' found";
	}

	return tokenlist;
}
