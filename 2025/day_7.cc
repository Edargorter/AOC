#include <bits/stdc++.h>

#define nl "\n"
#define newline cout << "\n";

using namespace std;

inline bool is_valid(vector<string>& grid, int r, int c)
{
	return (r >= 0 && r < grid.size() && c >= 0 && c < grid[0].length());
}

//PART 1 
void part_1(ifstream& inp)
{
	string line;
	int s_pos;
	vector<string> grid;
	while(getline(inp, line)){
		for(int i = 0; i < line.length(); i++){
			if(line[i] == 'S'){
				s_pos = i;
			}
		}
		grid.push_back(line);
	}
	vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].length(), false));

	struct coord {
		int first;
		int second;
	};

	vector<coord> coords;
	coords.push_back({0, s_pos});
	uint64_t splits = 0;

	while(!coords.empty()){
		coord curr = coords.back();
		coords.pop_back();

		if(!is_valid(grid, curr.first, curr.second)){
			continue;
		}
		if(visited[curr.first][curr.second]) continue;
		visited[curr.first][curr.second] = true;

		char c = grid[curr.first][curr.second];
		if(c == '^'){
			coords.push_back({curr.first + 1, curr.second - 1});
			coords.push_back({curr.first + 1, curr.second + 1});
			splits++;
		} else {
			coords.push_back({curr.first + 1, curr.second});
		}
	}

	cout << "Part 1: " << splits << nl;
}

void print_beams(vector<uint64_t>& bms)
{
	for(int i = 0; i < bms.size(); i++){
		if(bms[i] > 0){
			cout << bms[i] << " ";
		}
	}
	newline;
}

//PART 2 
void part_2(ifstream& inp)
{
	string line;
	int s_pos;
	vector<string> grid;
	while(getline(inp, line)){
		for(int i = 0; i < line.length(); i++){
			if(line[i] == 'S'){
				s_pos = i;
			}
		}
		grid.push_back(line);
	}

	vector<uint64_t> beams(grid[0].length(), uint64_t(0));
	beams[s_pos] = 1;
	for(int i = 0; i < grid.size(); i++){
		vector<uint64_t> new_beams(beams.size(), uint64_t(0));
		for(int j = 0; j < beams.size(); j++){
			char c = grid[i][j];
			uint64_t num = beams[j];
			if(c == '^'){
				new_beams[j-1] += num;
				new_beams[j+1] += num;
			} else {
				new_beams[j] += num;
			}
		}
		beams = new_beams;
	}
	uint64_t paths = accumulate(beams.begin(), beams.end(), uint64_t(0));
	cout << "Part 2: " << paths << nl;
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
