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

bool drop(vector<vector<bool>>& grid)
{
	return true;	
}

//PART 1
void part_1(ifstream& inp)
{
	string line;
	vector<vector<pair<int, int>>> pts;
	int sr = 1e9, er = 0, sc = 1e9, ec = 0;
	while(getline(inp, line)){
		vector<pair<int, int>> p;
		vs points = get_split(line, ' ');
		for(int i = -1; i < (int) points.size() - 1; i += 2){
			vs coords = get_split(points[i + 1], ',');
			int row = stoi(coords[1]);
			int col = stoi(coords[0]);
			p.pb({row, col});
			sr = min(sr, row);
			sc = min(sc, col);
			er = max(er, row);
			ec = max(ec, col);
		}
		pts.pb(p);
	}
	cout << sr << " " << sc << nl;
	cout << er << " " << ec << nl;
	vector<vector<bool>> grid(er - sr, vector<bool>(ec - sc));
	cout << grid.size() << " " << grid[0].size() << nl;

	for(vector<pair<int, int>> vp : pts){
		for(int i = 1; i < vp.size(); i++){
			cout << vp[i].first <<  " "  << vp[i].second << " " << vp[i-1].first << " " << vp[i-1].second << nl;
			int r_diff = vp[i].first - vp[i-1].first;
			int c_diff = vp[i].second- vp[i-1].second;

			int r_dir = (r_diff < 0) ? -1 : 1;
			int c_dir = (c_diff < 0) ? -1 : 1;

			cout << r_diff << " " << c_diff << nl;
			cout << r_dir << " " << c_dir << nl;

			int r, c;
			c = vp[i-1].second;
			for(r = vp[i-1].first; r != vp[i].first; r += r_dir){
				grid[r - sr][c - sc] = true;
			}
			r = vp[i-1].first;
			for(c = vp[i-1].second; c != vp[i].second; c += c_dir){
				grid[r - sr][c - sc] = true;
			}
		}
	}
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	while(getline(inp, line)){
	}
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
