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

bool in_bounds(int r, int c, int rows, int cols)
{
	return r >= 0 && r < rows && c >= 0 && c < cols;
}

bool drop(vector<vector<bool>>& grid, int row, int col)
{
	if(grid[row][col])
		return false;
	int maxr = grid.size();
	int maxc = grid[0].size();
	while(in_bounds(row, col, maxr, maxc)){
		bool left = in_bounds(row + 1, col - 1, maxr, maxc);
		bool right = in_bounds(row + 1, col + 1, maxr, maxc);
		bool down = in_bounds(row + 1, col, maxr, maxc);
		if(down && grid[row + 1][col]){
			if(left && !grid[row + 1][col - 1]){
				row++;
				col--;
			} else if(right && !grid[row + 1][col + 1]){
				row++;
				col++;
			} else if(left && right){
				grid[row][col] = true;
				return true;
			} else {
				return false;
			}
		} else if(down && !grid[row + 1][col]){
			row++;
		} else if(down){
			grid[row][col] = true;
			return true;
		} else {
			return false;
		}
	}
	return false;	
}

void print_grid(vector<vector<bool>>& grid, vector<vector<pair<int, int>>> pts, int sc)
{
	vs tp(grid.size(), string(grid[0].size(), '.'));;
		
	for(vector<pair<int, int>> vp : pts){
		for(int i = 1; i < vp.size(); i++){
			int r_diff = vp[i].first - vp[i-1].first;
			int c_diff = vp[i].second- vp[i-1].second;

			int r_dir = (r_diff < 0) ? -1 : 1;
			int c_dir = (c_diff < 0) ? -1 : 1;

			int r, c;
			c = vp[i-1].second;
			for(r = vp[i-1].first; r != vp[i].first + r_dir; r += r_dir){
				int col = c - sc;
				tp[r][col] = '#';
			}
			r = vp[i-1].first;
			for(c = vp[i-1].second; c != vp[i].second + c_dir; c += c_dir){
				int col = c - sc;
				tp[r][col] = '#';
			}
		}
	}
	for(int i = 0; i < tp.size(); i++){
		for(int j = 0; j < tp[i].length(); j++){
			if(tp[i][j] != '#' && grid[i][j])
				tp[i][j] = 'o';
		}
	}
	for(int i = 0; i < tp.size(); i++){
		for(int j = 0; j < tp[i].length(); j++)
			cout << tp[i][j];
		newline;
	}
}

//Both parts 
void parts(ifstream& inp)
{
	string line;
	vector<vector<pair<int, int>>> pts;
	int er = 0, sc = 1e9, ec = 0;
	while(getline(inp, line)){
		vector<pair<int, int>> p;
		vs points = get_split(line, ' ');
		for(int i = -1; i < (int) points.size() - 1; i += 2){
			vs coords = get_split(points[i + 1], ',');
			int row = stoi(coords[1]);
			int col = stoi(coords[0]);
			p.pb({row, col});
			sc = min(sc, col);
			er = max(er, row);
			ec = max(ec, col);
		}
		pts.pb(p);
	}

	//int maxc = ec - sc + 1; //Part 1
	int maxc = ec - sc + 1 + 3000; //Part 2
	vector<vector<bool>> grid(er + 3, vector<bool>(maxc));

	for(vector<pair<int, int>> vp : pts){
		for(int i = 1; i < vp.size(); i++){
			int r_diff = vp[i].first - vp[i-1].first;
			int c_diff = vp[i].second- vp[i-1].second;

			int r_dir = (r_diff < 0) ? -1 : 1;
			int c_dir = (c_diff < 0) ? -1 : 1;

			int r, c;
			c = vp[i-1].second;
			for(r = vp[i-1].first; r != vp[i].first + r_dir; r += r_dir){
				int col = c - sc + 1500;
				grid[r][col] = true;
			}
			r = vp[i-1].first;
			for(c = vp[i-1].second; c != vp[i].second + c_dir; c += c_dir){
				int col = c - sc + 1500;
				grid[r][col] = true;
			}
		}
	}

	//Part 2
	for(int c = 0; c < grid[0].size(); c++)
		grid[grid.size() - 1][c] = true;

	int count = 0;
	while(drop(grid, 0, 500 - sc + 1500))
		count++;	
	
	//print_grid(grid, pts, sc);
	cout << count << nl;
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
		parts(inp);
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
	inp.close();
}
