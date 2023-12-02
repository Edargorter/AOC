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

//PART 1 and 2
void part_1_2(ifstream& inp)
{
	vector<string> rgb_str = {"red", "green", "blue"};
	vector<int> rgb = {12, 13, 14};
	uint32_t ids = 0;
	uint64_t power_sum = 0;
	string line;
	while(getline(inp, line)){
		vector<int> rgb_sum(3, 0);
		vector<string> game = get_split(line, ':');
		vector<string> game_spl = get_split(game[0], ' ');
		int id = stoi(game_spl[1]);
		string num = "";
		for(int i = 0; i < game[1].length(); i++){
			char c = game[1][i];	
			if(c >= '0' && c <= '9'){
				num += c;	
			} else {
				for(int j = 0; j < rgb_str.size(); j++){
					string ss = game[1].substr(i, rgb_str[j].length());
					if(ss == rgb_str[j]){
						rgb_sum[j] = max(rgb_sum[j], stoi(num));
						num = "";
						i += rgb_str[j].length();
						break;
					}
				}
			}
		}
		bool possible = true;
		uint32_t power = 1;
		for(int i = 0; i < rgb.size(); i++){
			power *= rgb_sum[i];
			if(rgb_sum[i] > rgb[i]){
				possible = false;
			}
		}
		power_sum += power;
		if(possible){
			ids += id;
		}
	}
	cout << "Part 1: " << ids << nl;
	cout << "Part 2: " << power_sum << nl;
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
		part_1_2(inp);
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
	inp.close();
}
