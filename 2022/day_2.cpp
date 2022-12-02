#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define ll long long 
#define ui unsigned int
#define ul unsigned long
#define ull unsigned long long
#define pii pair<int, int>
#define pb push_back

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
	string o, r;
	ll score = 0;
	while(getline(inp, line)){
		vector<string> lin = get_split(line, ' ');
		o = lin[0];
		r = lin[1];
		if(o == "A"){
			if(r == "X")
				score += 1 + 3;
			else if(r == "Y")	
				score += 2 + 6;	
			else 
				score += 3;
		} else if(o == "B"){
			if(r == "Z")
				score += 3 + 6;
			else if(r == "Y")
				score += 2 + 3;
			else
				score += 1;
		} else if(o == "C"){
			if(r == "X")
				score += 1 + 6;	
			else if(r == "Z")
				score += 3 + 3;
			else
				score += 2;
		}
	}
	cout << score << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	string o, r;
	ll score = 0;
	while(getline(inp, line)){
		vector<string> lin = get_split(line, ' ');
		o = lin[0];
		r = lin[1];
		if(o == "A"){
			if(r == "X")
				score += 3;
			else if(r == "Y")	
				score += 1 + 3;	
			else 
				score += 2 + 6;
		} else if(o == "B"){
			if(r == "X")
				score += 1;
			else if(r == "Y")
				score += 2 + 3;
			else
				score += 3 + 6;
		} else if(o == "C"){
			if(r == "X")
				score += 2;
			else if(r == "Y")
				score += 3 + 3;
			else
				score += 1 + 6;
		}
	}
	cout << score << nl;
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
