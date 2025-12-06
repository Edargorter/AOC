#include <bits/stdc++.h>

#define nl "\n"
#define newline cout << "\n";
#define ROLL '@'

using namespace std;

inline bool valid(vector<string>& grid, int i, int j)
{
	return (i >= 0 && i < grid.size() && j >= 0 && j < grid[0].length());
}

bool check(vector<string>& grid, int i, int j)
{
	int count = 0;
	for(int di = -1; di <= 1; di++){
		for(int dj = -1; dj <= 1; dj++){
			if (di == 0 && dj == 0) continue;
			if(valid(grid,i+di,j+dj)){
				count += (grid[i+di][j+dj] == ROLL);
			}
		}
	}
	return count < 4;
}

//PART 1
void part_1(ifstream& inp)
{
	string line;
	vector<string> grid;
	while(getline(inp, line)){
		grid.push_back(line);
	}
	int num = 0;
	for(int i = 0; i < grid.size(); i++){
		for(int j = 0; j < grid[i].length(); j++){
			if (grid[i][j] == '@')
				num += check(grid, i, j);
		}
	}
	cout << "Part 1: " << num << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	vector<pair<int, int>> to_remove;
	vector<string> grid;
	while(getline(inp, line)){
		grid.push_back(line);
	}
	int num = 0;
	do {
		for(auto& cd : to_remove){
			grid[cd.first][cd.second] = '.';
		}
		to_remove.clear();
		for(int i = 0; i < grid.size(); i++){
			for(int j = 0; j < grid[i].length(); j++){
				if (grid[i][j] == '@'){
					if(check(grid, i, j))
						to_remove.push_back({i,j});
				}
			}
		}
		num += to_remove.size();
	} while (!to_remove.empty());
	cout << "Part 2: " << num << nl;
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
