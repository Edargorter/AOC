#include <bits/stdc++.h>
//#include "bits.h"

#define newline printf("\n")
#define nl "\n"
#define ll long long 
#define ui unsigned int
#define ul unsigned long

using namespace std;

/**
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
**/

int main(int argc, char **argv)
{
	string input_file;
	if(argc < 1){
		cout << "No file arguemnt. Using 'input'" << nl;
		input_file = "input";
	} else {
		input_file = argv[1];
	}
	ifstream inp(input_file);
	if(inp){
		int temp;
		while(inp >> temp){
		}
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
}
