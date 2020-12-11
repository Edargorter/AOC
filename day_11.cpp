#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << nl;
#define ll long long 
#define ui unsigned int
#define ul unsigned long

using namespace std;

vector<string> seats;

int get_occ_immediate(int r, int c)
{
	int occ = 0;
	for(int i = r - 1; i <= r + 1; i++){
		for(int j = c - 1; j <= c + 1; j++){
			if(i < 0 || i >= seats.size() || j < 0 || j >= seats[0].size() || (i == r && j == c))
				continue;
			if(seats[i][j] == '#')
				occ++;
		}
	}
	return occ;
}

int get_occ_dist(int r, int c)
{
	int occ = 0;
	for(int i = -1; i <= 1; i++){
		for(int j = -1; j <= 1; j++){
			if(!(i | j))
				continue;
			int curr_r = r + i, curr_c = c + j;
			while(curr_r >= 0 && curr_r < seats.size() && curr_c >= 0 && curr_c < seats[0].size()){
				if(seats[curr_r][curr_c] == '#'){
					occ++;
					break;
				} else if(seats[curr_r][curr_c] == 'L'){
					break;
				}
				curr_r += i;
				curr_c += j;
			}
		}
	}
	return occ;
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
	if(inp){
		string line;
		while(getline(inp, line)){
			seats.push_back(line);
		}
		vector<string> next(seats);
		vector<string> cp(seats);

		//PART 1
		bool changed = true;
		while(changed){
			changed = false;
			for(int i = 0; i < seats.size(); i++){
				for(int j = 0; j < seats[0].length(); j++){
					char c = seats[i][j];
					char nc = c;
					int occ = get_occ_immediate(i, j);
					if(c == 'L' && occ == 0)
						nc = '#';
					if(c == '#' && occ >= 4)
						nc = 'L';
					if(nc != seats[i][j])
						changed = true;
					next[i][j] = nc;
				}
			}
			seats.assign(next.begin(), next.end());
		}
		int count = 0;
		for(int i = 0; i < seats.size(); i++)
			for(int j = 0; j < seats[i].length(); j++)
				if(seats[i][j] == '#')
					count++;

		cout << "PART 1: " << count << nl;

		//PART 2
		changed = true;
		seats.assign(cp.begin(), cp.end());

		while(changed){
			changed = false;
			for(int i = 0; i < seats.size(); i++){
				for(int j = 0; j < seats[0].length(); j++){
					char c = seats[i][j];
					char nc = c;
					int occ = get_occ_dist(i, j);
					if(c == 'L' && occ == 0)
						nc = '#';
					if(c == '#' && occ >= 5)
						nc = 'L';
					if(nc != seats[i][j])
						changed = true;
					next[i][j] = nc;
				}
			}
			seats.assign(next.begin(), next.end());
		}
		count = 0;
		for(int i = 0; i < seats.size(); i++)
			for(int j = 0; j < seats[0].length(); j++)
				if(seats[i][j] == '#')
					count++;

		cout << "PART 2: " << count << nl;


	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
}
