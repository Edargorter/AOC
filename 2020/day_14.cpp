#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << nl;
#define ll long long 
#define ui unsigned int
#define ul unsigned long
#define ull unsigned long long

using namespace std;

vector<string> get_split(string line, char delimiter){
	vector<string> info; string word = "";
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

int main(int argc, char **argv)
{
	string input_file;
	if(argc < 2){
		cout << "No file argument. Using 'input'" << nl;
		input_file = "input";
	} else {
		input_file = argv[1];
	}
	ifstream inp(input_file);
	map<int, ull> mem;
	if(inp){
		string line;
		ull sum = 0;
		string mask;
		while(getline(inp, line)){
			vector<string> tokens = get_split(line, ' ');
			if(tokens[0] == "mask"){
				mask = tokens[2];
				cout << "New mask: " << mask << nl;
			} else {
				int addr = stoi(tokens[0].substr(4, tokens[0].length() - 5));
				ull v = stoull(tokens[2]);
//				cout << "Mask: " << mask << nl;
				cout << "V prev " << v << " size: " << sizeof(v);
				for(int i = 0; i < 36; i++){
					if(mask[35 - i] != 'X'){
						ull bit = ((ull)(mask[35 - i] == '1')) << i;
						cout << "Bit: " << bit << nl;
						//ull bit = (mask[35 - i] - '0') << i;
						v = (v & ~bit) | bit;
					} 
				}
				cout << " V next " << v << nl;
				mem[addr] = v;
			}
		}
		for(const auto &p : mem){
			sum += p.second;	
		}

		/**
		PART 1:  10717676595607
		PART 2:  3974538275659
		**/

		cout << "PART 1: " << sum << nl;
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
	inp.close();
}
