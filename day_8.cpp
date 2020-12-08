#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << nl;
#define ll long long 
#define ui unsigned int
#define ul unsigned long

using namespace std;

vector<string> get_split(string line, char delimiter){
	vector<string> info;
	string word = "";
	bool check = false;
	for(int i = 0; i < line.length(); i++){
		if(line[i] == delimiter){
			if(!check){
				check = true;
				info.push_back(word);
				word = "";
			}
		} else {
			word += line[i];
			check = false;
			if(i == line.length() - 1)
				info.push_back(word);
		}
	}
	return info;
}

vector<string> cmd;
ll acc = 0;

bool run_seq()
{
	bool completed = true;
	bool ran[cmd.size()] = {false};
	for(int i = 0; i < cmd.size(); i++){
		if(ran[i]){
			completed = false;
			break;
		}
		ran[i] = true;
		vector<string> tokens = get_split(cmd[i], ' ');
		string f = tokens[0];
		string s = tokens[1];

		int num = (s.substr(0,1) == "+" ? 1 : -1) * stoi(s.substr(1,s.length() - 1));
		if(f == "acc"){
			acc += num;
		} else if(f == "jmp"){
			i += num - 1;
		}
	}
	return completed;
}

int main(int argc, char **argv)
{
	string input_file;
	if(argc < 2){
		cout << "No file arguemnt. Using 'input'" << nl;
		input_file = "input";
	} else {
		input_file = argv[1];
	}
	ifstream inp(input_file);
	if(inp){
		string line;
		while(getline(inp, line)){
			cmd.push_back(line);
		}

		//PART 1
		run_seq();
		cout << "PART 1: " << acc << nl;

		//PART 2
		for(int i = 0; i < cmd.size(); i++){
			string instr = cmd[i].substr(0,3);
			string remain = cmd[i].substr(3, cmd[i].length() - 3);
			string pre;
			if(instr == "jmp"){
				pre = "nop";
			} else if(instr == "nop"){
				pre = "jmp";
			} else {
				continue;
			}
			cmd[i] = pre + remain;
			acc = 0;
			bool result = run_seq();
			if(result){
				cout << "PART 2: " << acc << nl;
				break;
			}
			cmd[i] = ((pre == "jmp") ? "nop" : "jmp") + remain;
		}
		
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
}
