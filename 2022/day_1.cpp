#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << nl;
#define ll long long 
#define ui unsigned int
#define ul unsigned long
#define ull unsigned long long
#define pii pair<int, int>
#define pb push_back

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

//PART 1
void part_1(ifstream& inp)
{
	string line;
	ll max = 0;
	ll sum = 0;
	while(getline(inp, line)){
		if(line == ""){
			if(sum > max)
				max = sum;
			sum = 0;
		} else 
			sum += stoi(line);	
	}
	if(!max)
		max = sum;
	cout << max << nl;
}

void comp_three(ll& first, ll& second, ll& third, ll cand)
{
	if(cand > first){
		third = second;
		second = first; 
		first = cand;
	} else if(cand > second){
		third = second;
		second = cand;
	} else if(cand > third){
		third = cand;
	}
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	ll first, second, third = 0;
	ll sum = 0;
	while(getline(inp, line)){
		//cout << first << " " << second << " " << third << nl;
		if(line == ""){
			comp_three(first, second, third, sum);
			sum = 0;
		} else 
			sum += stoi(line);	
	}
	comp_three(first, second, third, sum);

	cout << first + second + third << nl;
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
