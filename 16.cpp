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
		vector<pair<string, vector<pii>>> rule_limits;

		//Rules 
		while(getline(inp, line)){
			if(line.empty())
				break;
			vector<string> tokens = get_split(line, ':');
			string field = tokens[0];
			vector<pii> r_limits;
			tokens = get_split(tokens[1], ' ');
			vector<string> limits = get_split(tokens[1], '-');
			rules.pb({field, stoi(limits[0]), stoi(limits[1])});
			r_limits.pb({stoi(limits[0]), stoi(limits[1])});
			limits = get_split(tokens[3], '-');
			rules.pb({field, stoi(limits[0]), stoi(limits[1])});
			r_limits.pb({stoi(limits[0]), stoi(limits[1])});
			rule_limits.pb({field, r_limits});
			cout << "okay" << nl;
		}

		sort(rules.begin(), rules.end(), rule_sort);

		//Your ticket
		getline(inp, line);
		getline(inp, line);
		vector<string> tokens = get_split(line, ',');
		vector<int> ticket;

		for(string t : tokens)
			ticket.pb(stoi(t));

		getline(inp, line);
		getline(inp, line);

		vector<vector<pii>> limits;

		cout << "here" << nl;

		//Nearby tickets
		int count = 0;
		while(getline(inp, line)){
			tokens = get_split(line, ',');
			vector<int> near;
			vector<pii> cand;

			for(string t : tokens)
				near.pb(stoi(t));

			bool valid = true;

			for(int i = 0; i < near.size(); i++){
				int nt = near[i];
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
							med = temp;
							found = true;
							break;
						}
					}
				}
				if(!found){
					int temp = med;
					for(;temp >= 0, nt >= rules[temp].low; temp--){
						if(nt <= rules[temp].high){
							med = temp;
							found = true;
							break;
						}
					}
				}
				if(!found){
					count += nt;
					valid = false;
				} else {
					cand.pb({rules[med].low, rules[med].high});
				}
			}
			if(valid){
				for(int j = 0; j < cand.size(); j++){
					if(limits[j].empty()){
						limits[j].pb(cand[j]);
					} else if(!(limits[j][0].first == cand[j].first && limits[j][0].second == cand[j].second)){
						limits[j].pb(cand[j]);
					}
				}
			}
		}
		cout << "PART 1: " << count << nl;

		vector<string> fields;

		for(vector<pii> f : limits){
			for(pair<string, vector<pii>> r_sl: rule_limits){
				vector<pii> r_limits = r_sl.second;
				if(f[0].first == r_limits[0].first && f[0].second == r_limits[0].second
				 && f[1].first == r_limits[1].first && f[1].second == r_limits[1].second){
					fields.pb(r_sl.first);
					break;
				}
			}
		}

		ll prod = 1;
		for(int i = 0; i < ticket.size(); i++){
			if(fields[i].substr(0, 9) == "departure")
				prod *= ticket[i];
		}

		cout << "PART 2: " << prod << nl;

	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
	inp.close();
}
