#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << nl;
#define ll long long 
#define ui unsigned int
#define ul unsigned long

using namespace std;

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
	if(inp){
		string s;
		vector<int> seats;
		int row, col;
		while(getline(inp, s)){
			row = 0, col = 0;
			for(int i = 0; i < 7; i++){
				if(s[i] == 'B')
					row += (1 << (6 - i));
			}
			for(int i = 7; i < s.length(); i++){
				if(s[i] == 'R')
					col += (1 << (2 - i + 7));
			}
			cout << row << " " << col << nl;
			seats.push_back(row * 8 + col);
		}
		sort(seats.begin(), seats.end());
		//PART 1
		cout << seats.back() << nl;
		//PART 2
		for(int i = 1; i < seats.size(); i++){
			if(seats[i] > seats[i - 1] + 1){
				cout << "Seat: " << seats[i] - 1 << nl;
				break;
			}
		}

	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
}
