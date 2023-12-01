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

struct step
{
	int valve;
	int sum;
	ull vls;
	int t;
};

void print_step(step* st, int index, int high)
{
	cout << "Valve: " << st->valve << " ";
	cout << "Sum: " << st->sum << " ";
	cout << "Time: " << st->t << " ";
	cout << "On: ";
	for(int i = 0; i < index; i++){
		if((st->vls >> i) & 1){
			cout << i;
			if(i < index - 1)
				cout << ", ";
		}
	}
	cout << " Hi: " << high;
	newline;
}

//Valve AA has flow rate=0; tunnels lead to valves DD, II, BB

//PART 1
void part_1(ifstream& inp)
{
	string line;
	vi rates;
	list<step*> valves;
	int time = 30;
	int index = 0;
	vvs leads;
	map<string, int> vmap;

	while(getline(inp, line)){
		vs tokens = get_split(line, ';');
		string val = tokens[0].substr(6, 2);
		vmap[val] = index;
		string rate = tokens[0];
		rates.pb(stoi(rate.substr(23, rate.length() - 23)));
		vs ls = get_split(tokens[1], ' ');
		leads.pb(vs());
		for(int li = 5; li < ls.size(); li++){
			string l = ls[li];
			if(li != ls.size() - 1)
				l = l.substr(0, 2);
			leads.back().pb(l);
		}
		index++;
	}
	int highest = 0;
	cout << "index: " << index << nl;

	valves.pb(new step{0, (ull) 0, (ull) 0, 0});
	int score = 0;
	while(!valves.empty()){
		step* s = valves.front();
		valves.pop_front();
		if(s->t > highest){
			highest = s->t;
			cout << "Size: " << valves.size() << " Highest: " << highest << nl;
		}
		//print_step(s, index, highest);
		if(s->t == time){
			score = max(s->sum, score);
		} else if(s->t < time){
			int sum_rates = 0;
			for(int i = 0; i < index; i++){
				sum_rates += ((s->vls >> i) & 1) * rates[i];
			}
			for(string l : leads[s->valve]){
				int lv = (ull) vmap[l];
				//ull test = (s->vls >> lv) & 1;
				ull test = s->vls & ((ull) 1 << lv);
				if(!test && rates[lv] > 0){
					valves.pb(new step{lv, s->sum + sum_rates, (s->vls | (1 << lv)), s->t + 2});
				} else {
					valves.pb(new step{lv, s->sum + sum_rates, s->vls, s->t + 1});
				}
			}
		}
	}
	cout << score << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	while(getline(inp, line)){
	}
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
