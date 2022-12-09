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

void rope(ifstream& inp, int n)
{
	string line;
	set<pair<int, int>> pos;
	assert(n > 1);
	vector<pair<int, int>> nodes(n, {4, 0});
	unordered_map<string, pair<int, int>> dir = {{"R", {0, 1}},
									{"L", {0, -1}},
									{"U", {-1, 0}},
									{"D", {1, 0}}};
	while(getline(inp, line)){
		vs move = get_split(line, ' ');
		pair<int, int> moveto = dir[move[0]];
		for(int i = 0; i < stoi(move[1]); i++){
			nodes.front().first += moveto.first;
			nodes.front().second += moveto.second;

			for(int j = 1; j < n; j++){
				int diff_y = nodes[j - 1].first - nodes[j].first;
				int diff_x = nodes[j - 1].second - nodes[j].second;

				if(abs(diff_y) > 1 && abs(diff_x) > 1){
					nodes[j].first += diff_y/2;
					nodes[j].second += diff_x/2;
				} else if(abs(diff_y) > 1){
					nodes[j].first += diff_y/2;
					nodes[j].second += diff_x;
				} else if(abs(diff_x) > 1){
					nodes[j].first += diff_y;
					nodes[j].second += diff_x/2;
				}
			}
			pos.insert(nodes.back());
		}
	}
	cout << pos.size() << nl;
}

//PART 1
void part_1(ifstream& inp)
{
	rope(inp, 2);	
}

//PART 2
void part_2(ifstream& inp)
{
	rope(inp, 10);	
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
