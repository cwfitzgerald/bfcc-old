#include "tokenizer.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//Generate tokens in the form specified in the
//Intermediate Language Specificiation.
vector<token> gen_tokens (string program) {
	vector<token> tokenlist;
	token tk;

	vector<int> brack_stack;
	//Current token number, used for bracket matching
	int numtoken = 0;

	int charnum = 1;
	int linenum = 1;

	for (auto &i : program) {
		int leftbk;
		switch(i){
			//If it's a left bracket, add token
			//and add to the bracket stack.
			case '[': {
				tk = (token) {LBK, 0};
				brack_stack.push_back(numtoken);
				tokenlist.push_back(tk);
				break;
			}
			
			//If it's a right bracket, match up the bracket
			//with matching left bracket, then add token.
			case ']': {
				//If there's unmatched brackets, throw error.
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
			
			//Other symbols get combined into a single
			//token that can have multiple values
			//ex. ++++>>--
			//turns into (ADD,4) (MV,2) (ADD,-2)
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
			
			//Keep track of location in file
			case '\n': {
				linenum++;
				charnum = 1;
				break;
			}     
		}
		charnum++;
		numtoken = tokenlist.size();
	}
	
	//If there's an unmatched bracket, throw an error.
	if (brack_stack.size()) {
		throw "error: invalid token '['\nno matching ']' found";
	}

	return tokenlist;
}
