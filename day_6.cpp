#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << nl;
#define ll long long 
#define ui unsigned int
#define ul unsigned long

using namespace std;

int main(int argc, char **argv)
{
	string input_file;
	if(argc < 2){
		cout << "No file arguemnt. Using 'input'" << nl;
		input_file = "input";
	} else {
		input_file = argv[1];
	}
	map<char, int> present;
	int count_1 = 0;
	int count_2 = 0;
	ifstream inp(input_file);
	if(inp){
		string line;
		int group = 0;
		while(getline(inp, line)){
			if(line.empty()){
				for(const auto &el : present){
					count_1++;
					if(el.second == group)
						count_2++;
				}
				present.clear();
				group = 0;
			} else {
				group += 1;
			}
			for(char c : line){
				auto it = present.find(c);
				if(it == present.end()){
					present.insert({c, 1});
				} else {
					it->second++;
				}
			}
		}

		for(const auto &el : present){
			count_1++;
			if(el.second == group)
				count_2++;
		}
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
	cout << "PART 1: " << count_1 << nl;
	cout << "PART 2: " << count_2 << nl;
}
