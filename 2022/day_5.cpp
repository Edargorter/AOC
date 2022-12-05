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

//PART 1 and 2
void get_stack(ifstream& inp, vs& stack)
{
	string line;
	vs grid;
	int size;
	while(getline(inp, line)){
		if(line != ""){
			grid.pb(line);
		} else {
			vs nums = get_split(grid.back(), ' ');
			size = stoi(nums.back());
			for(int i = 0; i < size; i++){
				string si = "";
				for(int j = grid.size() - 2; j >= 0; j--){
					char c = grid[j][i*4 + 1];
					if(c != ' ')
						si += c;
				}
				stack.pb(si);
			}
			break;
		}
	}
}

//PART 1
void part_1(ifstream& inp)
{
	vs stack;
	get_stack(inp, stack);
	string line;

	while(getline(inp, line)){
		vs inst = get_split(line, ' ');
		int num = stoi(inst[1]);
		int src = stoi(inst[3]);
		int dst = stoi(inst[5]);
		for(int i = 0; i < num; i++){
			stack[dst - 1] += stack[src - 1].back();
			stack[src - 1].pop_back();
		}
	}
	for(int i = 0; i < stack.size() ; i++)
		cout << stack[i].back();
	newline;
}

//PART 2
void part_2(ifstream& inp)
{
	vs stack;
	get_stack(inp, stack);
	string line;

	while(getline(inp, line)){
		vs inst = get_split(line, ' ');
		int num = stoi(inst[1]);
		int src = stoi(inst[3]);
		int dst = stoi(inst[5]);
		stack[dst - 1] += stack[src - 1].substr(stack[src - 1].length() - num, num);
		stack[src - 1].erase(stack[src - 1].length() - num, num);
	}
	for(int i = 0; i < stack.size(); i++)
		cout << stack[i].back();
	newline;
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
