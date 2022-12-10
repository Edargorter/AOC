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

void incr(ll& cycle, ll& val, ll& sum)
{
	cycle++;
	if(cycle % 40 == 20)
		sum += cycle * val;
}

//PART 1
void part_1(ifstream& inp)
{
	string line;
	ll sum = 0;
	ll cycle = 0;
	string op;
	ll val = 1;
	while(getline(inp, line)){
		vs instr = get_split(line, ' ');
		string op = instr[0];
		if(op == "noop")
			incr(cycle, val, sum);
		else if(op == "addx"){
			incr(cycle, val, sum);
			incr(cycle, val, sum);
			val += stoi(instr[1]);
		}
	}
	cout << sum << nl;
}

void draw(vector<bitset<40>>& sc, int& pos, int& cycle)
{
	bitset<40> tmp(0x8000000000);
	bitset<40> sprite(0xe000000000);
	sc[cycle/40] |= ((tmp >> (cycle % 40)) & (sprite >> pos - 1));
	cycle++;
}

void render(vector<bitset<40>>& sc)
{
	for(bitset<40> b : sc){
		for(int i = 0; i < 40; i++)
			cout << (b.test(39 - i) ? "#" : " ");
		newline;
	}
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	vector<bitset<40>> sc(6, bitset<40>());
	int pos = 1;
	int cycle = 0;
	string op;
	while(getline(inp, line)){
		vs instr = get_split(line, ' ');
		string op = instr[0];
		if(op == "noop")
			draw(sc, pos, cycle);	
		else if(op == "addx"){
			draw(sc, pos, cycle);	
			draw(sc, pos, cycle);	
			pos += stoi(instr[1]);
		}
	}
	render(sc);
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
