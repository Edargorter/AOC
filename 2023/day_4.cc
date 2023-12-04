#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << "\n";

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

//PART 1
void part_1(ifstream& inp)
{
	string line;
	uint64_t tot = 0;
	while(getline(inp, line)){
		vector<string> card = get_split(line, ' ');		
		bool check = false;
		uint64_t points = 0;
		unordered_set<int> nums;
		for(int i = 2; i < card.size(); i++){
			string s = card[i];
			if(s == "|"){
				check = true;
			} else if(check){
				auto it = nums.find(stoi(s));
				if(it != nums.end()){
					points = (!points) ? 1 : (points << 1);
				}
			} else {
				nums.insert(stoi(s));
			}
		}
		tot += points;
	}
	cout << "Part 1: " << tot << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	vector<int> copies;
	uint64_t tot = 0;
	int curr = 0;
	while(getline(inp, line)){
		vector<string> card = get_split(line, ' ');		
		bool check = false;
		uint64_t points = 0;
		unordered_set<int> nums;
		for(int i = 2; i < card.size(); i++){
			string s = card[i];
			if(s == "|"){
				check = true;
			} else if(check){
				auto it = nums.find(stoi(s));
				if(it != nums.end()){
					points++;
				}
			} else {
				nums.insert(stoi(s));
			}
		}
		copies.resize(max(copies.size(), curr + 1 + points), 1);
		for(int i = 1; i <= points; i++){
			copies[curr + i] += copies[curr];
		}
		tot += copies[curr];	
		curr++;
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
