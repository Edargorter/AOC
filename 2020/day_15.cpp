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
	vector<int> nums;
	if(inp){
		string line;
		while(getline(inp, line)){
			vector<string> tokens = get_split(line, ',');
			map<int, int> index;
			int curr;
			int i;
			for(i = 0; i < tokens.size() - 1; i++){
				curr = stoi(tokens[i]);	
				cout << "TURN " << i + 1 << ": " << curr << nl;
				index[curr] = i;
			}
			curr = stoi(tokens[tokens.size() - 1]);
			int stop = 30000000;
			int next;
			for(;i < stop - 1; i++){
				if(!(i % 1000000))
					cout << "TURN " << i + 1 << ": " << curr << nl;
				bool found = (index.find(curr) != index.end());
				if(found)
					next = i - index[curr];
				else
					next = 0;
				index[curr] = i;
				curr = next;
			}
			cout << "PART 1: " << curr << nl;
		}
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
	inp.close();
}
