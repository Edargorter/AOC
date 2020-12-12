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
	//{'E', 'S', 'W', 'N'};
	map<char, int> dir_map = {{'E',0}, {'S',1}, {'W',2}, {'N',3}};
	if(inp){
		string line;
		int dir = 0;
		int x = 0, y = 0;
		vector<string> instr;
		while(getline(inp, line)){
			instr.push_back(line);
		}
		//PART 1
		for(string line : instr){
			char d = line[0];
			int val = stoi(line.substr(1,line.length()-1));
			if(d == 'L'){
				dir = (4 + dir - val/90) % 4;
			} else if(d == 'R'){
				dir = (dir + val/90) % 4;
			} else if(d == 'F'){
				if(dir == 0)
					x += val;
				else if(dir == 1)
					y -= val;
				else if(dir == 2)
					x -= val;
				else if(dir == 3)
					y += val;
			} else if(d == 'N'){
				y += val;
			} else if(d == 'S'){
				y -= val;
			} else if(d == 'E'){
				x += val;
			} else if(d == 'W'){
				x -= val;
			}
		}
		cout << "PART 1: " << abs(x) + abs(y) << nl;

		//PART 2
		int wx = 10, wy = 1;
		x = 0, y = 0;
		for(string line : instr){
			char d = line[0];
			int val = stoi(line.substr(1,line.length()-1));
			if(d == 'N'){
				wy += val;
			} else if(d == 'S'){
				wy -= val;
			} else if(d == 'E'){
				wx += val;
			} else if(d == 'W'){
				wx -= val;
			} else if(d == 'F'){
				x += wx*val;
				y += wy*val;
			} else if(d == 'R'){
				for(int i = 0; i < val/90; i++){
					int temp = wx;
					wx = wy;
					wy = -temp;
				}
			} else if(d == 'L'){
				for(int i = 0; i < val/90; i++){
					int temp = wx;
					wx = -wy;
					wy = temp;
				}
			}
		}
		cout << "PART 2: " << abs(x) + abs(y) << nl;
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
}
