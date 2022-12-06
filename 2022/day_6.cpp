#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << "\n";
#define ll long long 
#define ui unsigned int
#define ul unsigned long
#define ull unsigned long long
#define pii pair<int, int>
#define pb push_back
#define vs vector<string>
#define vvs vector<vector<string>>
#define vi vector<int>
#define vvi vector<vector<int>>

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
int len = 4;

//PART 1
void part_1(ifstream& inp)
{
	string line;
	int count = 0;
	unordered_map<char, int> ls;
	while(getline(inp, line)){
		for(int i = 0; i < line.length(); i++){
			if(ls.size() == len){
				cout << i << nl;
				break;
			}
			ls[line[i]]++;
			if(i >= len){
				ls[line[i - len]]--;
				if(!ls[line[i - len]])
					ls.erase(line[i - len]);
			}
		}
	}
}

//PART 2
void part_2(ifstream& inp)
{
	len = 14;
	part_1(inp);
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
