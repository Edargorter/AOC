#include <bits/stdc++.h>
//#include "bits.h"
#include <unistd.h>

#define nl "\n"
#define newline cout << nl;
#define ll long long 
#define ui unsigned int
#define ul unsigned long
#define pii pair<int, int>
#define pb push_back

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

struct rule
{
	string field;
	int low;
	int high;
};

bool rule_sort(const struct rule& a, const struct rule& b)
{
	return a.low < b.low;
}

int main(int argc, char **argv)
{
	string input_file;
	if(argc < 2){
		cout << "No file argument. Using 'input'" << nl;
		input_file = "input";
	} else {
		input_file = argv[1];
	}
	ifstream inp(input_file);
	if(inp){
		string line;
		vector<rule> rules;

		//Rules 
		while(getline(inp, line)){
			if(line.empty())
				break;
			vector<string> tokens = get_split(line, ':');
			string field = tokens[0];
			tokens = get_split(tokens[1], ' ');
			vector<string> limits = get_split(tokens[1], '-');
			rules.pb({field, stoi(limits[0]), stoi(limits[1])});
			limits = get_split(tokens[3], '-');
			rules.pb({field, stoi(limits[0]), stoi(limits[1])});
		}

		sort(rules.begin(), rules.end(), rule_sort);

		//Your ticket
		getline(inp, line);
		getline(inp, line);
		vector<string> tokens = get_split(line, ',');
		vector<int> ticket;

		for(string t : tokens)
			ticket.pb(stoi(t));

		sort(ticket.begin(), ticket.end());
		getline(inp, line);
		getline(inp, line);

		
		//Nearby tickets
		int count = 0;
		while(getline(inp, line)){
			tokens = get_split(line, ',');
			vector<int> near_ticket;

			for(string t : tokens)
				near.pb(stoi(t));

			bool valid = true;
			for(int nt : near){
				int low = 0;
				int high = rules.size();
				int med = low + (high - low)/2;
				int prev_med = med - 1;
				bool found = false;

				while(med != prev_med){
					//cout << "NT: " << nt << " med:" << med << " high: " << high << " low: " << low << " rule:" << rules[med].low << "-" << rules[med].high << nl;
					prev_med = med;
					if(nt >= rules[med].low && nt <= rules[med].high){
						found = true;
						break;
					} else if(nt < rules[med].low){
						high = med;
					} else {
						low = med;
					}
					med = low + (high - low)/2;
				}
				if(found){
					int temp = med;
					found = false;
					for(;temp < rules.size(), nt >= rules[temp].low; temp++){
						if(nt <= rules[temp].high){
							found = true;
							break;
						}
					}
				}
				if(!found){
					int temp = med;
					for(;temp >= 0, nt >= rules[temp].low; temp--){
						if(nt <= rules[temp].high){
							found = true;
							break;
						}
					}
				}
				if(!found){
					count += nt;
					valid = false;
				}
			}
			if(valid){
				//TOOD	
			}
		}
		cout << "PART 1: " << count << nl;



		cout << "PART 2: " << ans << nl;
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
	inp.close();
}
