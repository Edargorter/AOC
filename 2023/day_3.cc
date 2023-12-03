#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << "\n";

using namespace std;

//PART 1
void part_1(ifstream& inp)
{
	string line;
	vector<string> grid;
	while(getline(inp, line)){
		grid.push_back(line);
	}
	auto issymbol = [&](char c) -> bool {
		return ((c < '0' || c > '9') && c != '.');
	};
	uint32_t tot = 0;
	for(int i = 0; i < grid.size(); i++){
		bool isnum = false;
		bool ispart = false;
		bool prev = false;
		string num = "";
		for(int j = 0; j < grid[i].length(); j++){
			char c = grid[i][j];
			bool haspart = false;
			bool proc = false;
			haspart |= (i > 0) && issymbol(grid[i-1][j]);
			haspart |= (i < grid.size() - 1) && issymbol(grid[i+1][j]);
			if(c >= '0' && c <= '9'){
				isnum = true;
				num += c;
				ispart |= haspart;
				ispart |= prev;
				proc = j == grid[i].length() - 1;
			} else {
				haspart |= issymbol(grid[i][j]);
				proc = true;
				ispart |= isnum && haspart;
			}
			if(proc){
				if(ispart){
					tot += stoi(num);
					ispart = false;
				}
				num = "";
				isnum = false;
			}
			prev = haspart;
		}
	}
	cout << "Part 1: " << tot << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	vector<string> grid;
	while(getline(inp, line)){
		grid.push_back(line);
	}
	auto isnum = [&](char c){
		return c >= '0' && c <= '9';
	};
	uint64_t tot = 0;
	for(int i = 0; i < grid.size(); i++){
		for(int j = 0; j < grid[i].length(); j++){
			char c = grid[i][j];

			if(c == '*'){
				vector<pair<int, int>> coords;
				int count = 0;
				for(int y = -1; y <= 1; y++){
					int ny = i + y;
					if(ny < 0 || ny >= grid.size()) continue;
					bool innum = false;
					for(int x = -1; x <= 1; x++){
						int nx = j + x;
						if(nx < 0 || nx >= grid[i].length()) continue;
						if(isnum(grid[ny][nx])){
							if(!innum){
								if(count < 2) coords.push_back({ny, nx});
								count++;
							}
							innum = true;					
						} else if(innum){
							innum = false;
						}
					}
				}
				if(count == 2){
					uint32_t product = 1;
					for(int c = 0; c < coords.size(); c++){
						int y = coords[c].first;
						int left = coords[c].second - 1;
						int right = coords[c].second + 1;
						while(left >= 0 && isnum(grid[y][left])) left--;
						while(right < grid[i].length() && isnum(grid[y][right])) right++;
						product *= stoi(grid[y].substr(left + 1, right - left + 1));
					}
					tot += product;
				}
			}
		}
	}
	cout << "Part 2: " << tot << nl;
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
