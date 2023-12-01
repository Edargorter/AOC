#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << "\n";

using namespace std;

//PART 1
void part_1(ifstream& inp)
{
	unsigned long tot = 0;
	string line;
	while(getline(inp, line)){
		bool first = false, last = false;
		int len = line.length();
		for(int i = 0; i < len; i++){
			if(!first && line[i] >= '0' && line[i] <= '9'){
				tot += 10*(line[i] - '0');
				first = true;
			}
			if(!last && line[len - i - 1] >= '0' && line[len - i - 1] <= '9'){
				tot += line[len - i - 1] - '0';
				last = true;
			}
			if(first && last) break;
		}
	}
	cout << "Part 1: " << tot << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	unsigned long tot = 0;
	vector<string> words = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	string line;
	while(getline(inp, line)){
		vector<int> nums;
		for(int i = 0; i < line.length(); i++){
			if(line[i] >= '0' && line[i] <= '9'){
				nums.push_back(line[i] - '0');
			} else {
				for(int j = 0; j < words.size(); j++){
					if(words[j].length() <= line.length() - i){
						string ss = line.substr(i, words[j].length());
						if(ss == words[j]){
							nums.push_back(j + 1);
							break;
						}
					}
				}
			}
		}
		if(!nums.empty()){
			tot += 10*nums.front();
			tot += nums.back();
		}
	}
	cout << "Part 2: " << tot << nl;
}

int main(int argc, char **argv)
{
	string input_file;
	if(argc < 2){
		//cerr << "No file argument. Using 'input'" << nl;
		input_file = "input";
	} else {
		input_file = argv[1];
	}
	ifstream inp(input_file);
	if(inp){
		part_1(inp);

		inp.clear();
		inp.seekg(0);

		part_2(inp);
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
	inp.close();
}
