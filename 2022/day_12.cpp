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

int bfs(vs& grid, int start_y, int start_x, int goal_y, int goal_x)
{
	int y_dim = grid.size();
	int x_dim = grid[0].size();

	list<pair<int, int>> coords;
	vector<vector<bool>> visited(y_dim, vector<bool>(x_dim, false));
	vi depth;
	int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	coords.pb({start_y, start_x});
	visited[start_y][start_x] = true;
	depth.pb(0);
	int index = 0;
	bool found = false;

	while(!coords.empty()){
		pair<int, int> curr = coords.front();
		coords.pop_front();
		if(curr.first == goal_y && curr.second == goal_x){
			found = true;
			break;
		}
		for(int i = 0; i < 4; i++){
			int ny = curr.first + dir[i][0];
			int nx = curr.second + dir[i][1];
			if(ny < y_dim && ny >= 0 && nx < x_dim && nx >= 0){
				if(!visited[ny][nx] && grid[ny][nx] <= grid[curr.first][curr.second] + 1){
					coords.pb({ny, nx});	
					depth.pb(depth[index] + 1);
					visited[ny][nx] = true;
				}
			}
		}
		index++;
	}
	return found ? depth[index] : 1e9;
}

//PARTS 1 and 2
void parts(ifstream& inp)
{
	string line;
	vs grid;
	int y, x;
	int gy, gx;
	int count = 0;
	vector<pair<int, int>> as;
	while(getline(inp, line)){
		grid.pb(line);
		for(int i = 0; i < line.length(); i++){
			if(line[i] == 'S'){
				y = count;
				x = i;
			}
			if(line[i] == 'E'){
				gy = count;
				gx = i;
			}
			if(line[i] == 'a')
				as.pb({count, i});
		}
		count++;
	}

	grid[y][x] = 'a';
	grid[gy][gx] = 'z';

	cout << bfs(grid, y, x, gy, gx) << nl;

	int shortest = 1e8;
	for(pair<int, int> a : as)
		shortest = min(shortest, bfs(grid, a.first, a.second, gy, gx));
	cout << shortest << nl;
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
