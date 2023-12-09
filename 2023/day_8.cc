#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << "\n";

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

//PARTS 1 and 2
void parts(ifstream& inp)
{
	string line;
	string instr;
	getline(inp, instr);

	struct dir {
		string s;
		int left;
		int right;
	};

	int index = 0;
	unordered_map<string, int> nodes;
	vector<dir> dirs;
	getline(inp, line);

	vector<int> as;

	while(getline(inp, line)){
		vector<string> lri = get_split(line, ' ');	
		string n = lri[0];
		string left = lri[2].substr(1, 3);
		string right = lri[3].substr(0, 3);
		if(nodes.find(left) == nodes.end()) nodes.insert({left, index++});
		if(nodes.find(right) == nodes.end()) nodes.insert({right, index++});
		if(nodes.find(n) == nodes.end()) nodes.insert({n, index++});
		dirs.resize(index, {"", -1,-1});
		dir* d = &dirs[nodes[n]];
		d->s = n;
		d->left = nodes[left];
		d->right = nodes[right];
		if(n.back() == 'A')	as.push_back(nodes[n]);
	}

	int node = nodes["AAA"];
	int finish = nodes["ZZZ"];
	int ins_index = 0;
	char ins;
	int steps = 0;
	while(node != finish){
		ins = instr[ins_index];
		dir* d = &dirs[node];
		node = (ins == 'L') ? d->left : d->right;
		ins_index = (ins_index + 1) % instr.length();
		steps++;
	}

	// Part 1

	cout << "Part 1: " << steps << nl;

	// Part 2

	vector<int> cycles;

	for(int i = 0; i < as.size(); i++){
		int node = as[i];
		int index = 0;
		int count = 0;
		char ins;
		dir* d = &dirs[node];
		while(d->s.back() != 'Z'){
			d = &dirs[node];
			ins = instr[index];
			node = (ins == 'L') ? d->left : d->right;
			index = (index + 1) % instr.length();
			count++;
		}
		cycles.push_back(count - 1);
	}

	uint64_t lcm = 1;
	for(int i = 0; i < cycles.size(); i++){
		lcm = (lcm * cycles[i]) / gcd(lcm, cycles[i]);
	}

	cout << "Part 2: " << lcm << nl;
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
