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
	vs grid;
	while(getline(inp, line)){
		grid.pb(line);
	}
	ui num_vis = 0;
	int max = -1;
	int tree;
	int r_len = grid.size();
	int c_len = grid[0].size();
	vector<vector<bool>> vis(r_len, vector<bool>(c_len, false));

	for(int i = 0; i < r_len; i++){
		max = -1;
		for(int j = 0; j < c_len; j++){
			tree = grid[i][j] - '0';
			if(tree > max){
				max = tree;
				if(!vis[i][j]){
					num_vis++;
					vis[i][j] = true;
				}
			}
		}
		max = -1;
		for(int j = c_len - 1; j >= 0; j--){
			tree = grid[i][j] - '0';
			if(tree > max){
				max = tree;
				if(!vis[i][j]){
					num_vis++;
					vis[i][j] = true;
				}
			}
		}
	}
	for(int i = 0; i < c_len; i++){
		max = -1;
		for(int j = 0; j < r_len; j++){
			tree = grid[j][i] - '0';
			if(tree > max){
				if(!vis[j][i]){
					num_vis++;
					vis[j][i] = true;
				}
				max = tree;
			}
		}
		max = -1;
		for(int j = r_len - 1; j >= 0; j--){
			tree = grid[j][i] - '0';
			if(tree > max){
				max = tree;
				if(!vis[j][i]){
					num_vis++;
					vis[j][i] = true;
				}
			}
		}
	}
	cout << num_vis << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	vvi grid;
	while(getline(inp, line)){
		grid.pb(vi());
		for(char c : line)
			grid.back().pb(c - '0');
	}
	int r_len = grid.size();
	int c_len = grid[0].size();
	int max = 0;

	for(int i = 0; i < r_len; i++){
		for(int j = 0; j < c_len; j++){
			int tree = grid[i][j];
			int r = 0, l = 0, u = 0, d = 0;
			for(int k = j + 1; k < c_len; k++){
				r++;
				if(grid[i][k] >= tree)
					break;
			}
			for(int k = j - 1; k >= 0; k--){
				l++;
				if(grid[i][k] >= tree)
					break;
			}
			for(int k = i - 1; k >= 0; k--){
				u++;
				if(grid[k][j] >= tree)
					break;
			}
			for(int k = i + 1; k < r_len; k++){
				d++;
				if(grid[k][j] >= tree)
					break;
			}
			int vis = r*l*u*d;
			if(vis > max)
				max = vis;
		}
	}
	cout << max << nl;
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
