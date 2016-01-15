#include "tokenizer.h"
#include <vector>
#include <string>

using namespace std;

vector<token> gen_tokens (string program) {
	vector<token> final;
	token tk;

	vector<int> brack_stack;
	bool first = true;
	int numtoken = 0;

	int charnum = 1;
	int linenum = 1;

	for (auto &i : program) {
		if (first){
			first = false;
			switch (i){
				case '[': 
					tk = (token) {i, 0};
					brack_stack.push_back(numtoken);
					final.push_back(tk);
					break;
					
				case ']':
					throw "Invalid token ']' at Line " + to_string(linenum) + ", Char: " + to_string(charnum);
					break;
					
				case '\n':
					linenum++;
					charnum = 1;
					first = true;
					break;
					
				case '+': case '-': case '<': case '>': case ',': case '.':
					tk = (token) {i, 1};
					final.push_back(tk);
					break;
					
				default:
					first = true;
					break;
			}
		}
		else {
			int leftbk;
			switch(i){
				case '[':
					tk = (token) {i, 0};
					brack_stack.push_back(numtoken);
					final.push_back(tk);
					break;
					
				case ']':
					if (!brack_stack.size()) {
						throw "Invalid token ']' at Line " + to_string(linenum) + ", Char: " + to_string(charnum) + "\nNo matching bracket";
					}

					leftbk = brack_stack.back(); 	//Place of matching bracket
					brack_stack.pop_back();			//Pop value from stack
					
					tk = (token) {i, leftbk};		//Add token with redirect.
					final[leftbk].data = numtoken;	//Add redirect to matching bracket
					final.push_back(tk);
					break;
					
				case '\n':
					linenum++;
					charnum = 1;
					break;
					
				case '+': case '-': case '<': case '>': case ',': case '.':
					auto& lastoken = final[numtoken-1];
					if (lastoken.type == i)
						lastoken.data++;
					else {
						tk = (token) {i, 1};
						final.push_back(tk);
					}
					break;                                         
			}
		}
		charnum++;
		numtoken = final.size();
	}

	return final;
}
