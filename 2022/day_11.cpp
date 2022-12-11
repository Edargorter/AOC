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

ui gcd(ui a, ui b)
{
	if(!b) return a;
	return gcd(a, a % b);
}

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

struct monkey
{
	vector<ull> items;
	vs op;
	ui div;
	int tm;
	int fm;
};

//PART 1
void run_rounds(ifstream& inp, int rounds, ui divisor)
{
	string line;
	vector<monkey*> mks;
	while(getline(inp, line)){
		getline(inp, line);
		vector<ull> items;
		vs its = get_split(line.substr(18, line.length()), ',');
		for(string s : its)
			items.pb(stoi(s));
		getline(inp, line);
		vs opstring = get_split(line.substr(19, line.length()), ' ');
		vs op;
		op.pb(opstring[0]);
		op.pb(opstring[1]);
		op.pb(opstring[2]);
		getline(inp, line);
		ui div = stoi(line.substr(21, line.length()));
		getline(inp, line);
		int tm = stoi(line.substr(29, line.length()));
		getline(inp, line);
		int fm = stoi(line.substr(30, line.length()));
		monkey* nm = new monkey{items, op, div, tm, fm};
		mks.pb(nm);
		getline(inp, line);
	}
	int num_mk = mks.size();
	vector<ull> active(num_mk, 0);
	ui lcm = 1;

	for(monkey* mk : mks)
		lcm *= (lcm * mk->div) / gcd(lcm, mk->div);

	for(int r = 0; r < rounds; r++){
		for(int m = 0; m < num_mk; m++){
			monkey* mk = mks[m];
			active[m] += mk->items.size();
			ull a, b;
			for(int i = 0; i < mk->items.size(); i++){
				ull item = mk->items[i];
				ull result;
				if(mk->op[0] == "old")
					a = item;
				else
					a = stoi(mk->op[0]);
				if(mk->op[2] == "old")
					b = item;
				else
					b = stoi(mk->op[2]);
				if(mk->op[1] == "*"){
					result = (a * b) % lcm;
				} else {
					result = (a + b) % lcm;
				}
				result /= divisor;
				if(!(result % mk->div))
					mks[mk->tm]->items.pb(result);
				else
					mks[mk->fm]->items.pb(result);
			}
			mk->items.erase(mk->items.begin(), mk->items.end());
		}
	}
	sort(active.begin(), active.end());
	cout << active.back() * active[active.size() - 2] << nl;
}

//PART 1
void part_1(ifstream& inp)
{
	run_rounds(inp, 20, 3);
}

//PART 2
void part_2(ifstream& inp)
{
	run_rounds(inp, 10000, 1);
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
