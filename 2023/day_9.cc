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

//PARTS 1 and 2
void parts(ifstream& inp)
{
	string line;
	long totfor = 0;
	long totback = 0;
	while(getline(inp, line)){
		vector<string> str_seq = get_split(line, ' ');
		vector<int> seq;
		seq.push_back(0);
		for(int i = 0; i < str_seq.size(); i++)
			seq.push_back(stoi(str_seq[i]));
		vector<vector<int>> diff;
		diff.push_back(seq);
		diff.push_back({0});
		int index = 1;
		int limit = diff[0].size();
		bool allzero = true;
		for(int i = 2; i < limit; i++){
			int diff_val = diff[index-1][i] - diff[index-1][i-1];
			diff[index].push_back(diff_val);
			allzero = allzero && (diff_val == 0);
			if(i == limit - 1){
				if(allzero) break;
				allzero = true;
				limit--;
				diff.push_back({0});
				index++;
				i = 1;
			}
		}
		if(diff.size() > 2){
			limit = diff[diff.size() - 2].size();
			for(index = diff.size() - 2; index >= 0; index--){
				diff[index].push_back(diff[index][limit-1] + diff[index+1].back());
				diff[index][0] = diff[index][1] - diff[index+1][0];
				limit++;
			}
		}
		totfor += diff[0].back();
		totback += diff[0].front();
	}
	cout << "Part 1: " << totfor << nl;
	cout << "Part 2: " << totback << nl;
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
		parts(inp);
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
	inp.close();
}
