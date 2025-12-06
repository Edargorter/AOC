#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << "\n";
#define DIAL_LEN 100

using namespace std;

//PART 1
void part_1(ifstream& inp)
{
	string line;
	int pos = 50;
	int count = 0;
	while(getline(inp, line)){
		char dir = line[0];
		int rot = stoi(line.substr(1));
		pos = (pos + (dir == 'L' ? -rot : rot)) % DIAL_LEN;
		count += (pos == 0);
	}
	cout << "Part 1: " << count << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	int pos = 50;
	int count = 0;
	while(getline(inp, line)){
		char dir = line[0];
		int rot = stoi(line.substr(1));
		bool forwards = dir == 'R';
		int num = rot / DIAL_LEN;
		num += (pos != 0) && ((rot % DIAL_LEN) >= (forwards ? (DIAL_LEN - pos) : pos));
		cout << "dir: " << dir << " pos: " << pos << " rot: " << rot << " num: " << num << nl;
		pos = forwards ? pos + rot : pos - (rot % DIAL_LEN) + DIAL_LEN;
		pos %= DIAL_LEN;
		count += num;
	}
	cout << "Part 2: " << count << nl;
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
