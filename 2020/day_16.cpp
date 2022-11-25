#include <bits/stdc++.h>
//#include "bits.h"
#include <unistd.h>

#define nl "\n"
#define newline cout << nl;
#define ll long long 
#define ui unsigned int
#define ul unsigned long
#define ull unsigned long long
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

bool cand_sort(const vector<int>& a, const vector<int>& b)
{
	return a.size() < b.size();
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
		vector<pair<string, pair<pii, pii>>> rules;

		//Rules 
		while(getline(inp, line)){
			if(line.empty())
				break;
			vector<string> tokens = get_split(line, ':');
			string field = tokens[0];
			tokens = get_split(tokens[1], ' ');
			vector<string> limits = get_split(tokens[1], '-');
			vector<string> limits2 = get_split(tokens[3], '-');
			pair<string, pair<pii, pii>> temp = {field, {{stoi(limits[0]), stoi(limits[1])}, {stoi(limits2[0]), stoi(limits2[1])}}};
			rules.pb(temp);
		}

		for(int r = 0; r < rules.size(); r++){
			pii a = rules[r].second.first;
			pii b = rules[r].second.second;
			cout << " RULE " << r << ": " << a.first << "-" << a.second << " --- " << b.first << "-" << b.second << nl;
		}

		//Your ticket
		getline(inp, line);
		getline(inp, line);
		vector<string> tokens = get_split(line, ',');
		vector<int> ticket;

		vector<vector<int>> valid_t;

		for(string t : tokens)
			ticket.pb(stoi(t));

		getline(inp, line);
		getline(inp, line);

		//Nearby tickets
		int count = 0;
		while(getline(inp, line)){
			cout << "Nearby ticket: " << line << nl;
			tokens = get_split(line, ',');
			vector<int> near;

			for(string t : tokens)
				near.pb(stoi(t));

			bool valid = true;

			for(int i = 0; i < near.size(); i++){
				int n = near[i];
				bool valid_field = false;
	
				for(int r = 0; r < rules.size(); r++){
					pii a = rules[r].second.first;
					pii b = rules[r].second.second;
					if((n >= a.first && n <= a.second) || (n >= b.first && n <= b.second)){
						valid_field = true;
					} 
				}

				if(!valid_field){
					count += n;
					valid = false;
				} 
			}
			if(valid)
				valid_t.pb(near);		
		}
		cout << "PART 1: " << count << nl;

		bool check[20][20] = {true};
		for(int i = 0; i < 20; i++)	
			memset(check[i], 1, 20);

		for(vector<int> t : valid_t){
			bool temp = false;
			for(int i = 0; i < rules.size(); i++){
				int n = t[i];
				for(int r = 0; r < rules.size(); r++){
					pii a = rules[r].second.first;
					pii b = rules[r].second.second;
					cout << n << " RULE " << r << ": " << a.first << "-" << a.second << " --- " << b.first << "-" << b.second << nl;
					if((n < a.first || n > a.second) && (n < b.first || n > b.second)){
						check[i][r] = false;
						cout << "ummm..." << nl;
					} else 
						temp = true;
				}
			}
			cout << temp << nl;
		}

		vector<int> pos;
		bool taken[20] = {false};

		vector<vector<int>> cands;
		for(int i = 0; i < rules.size(); i++){		
			vector<int> cand;
			for(int j = 0; j < rules.size(); j++){		
				if(check[i][j]){
					cand.pb(j);
				}
			}
			cands.pb(cand);
		}

		for(int i = 0; i < rules.size(); i++){		
			for(int j = 0; j < rules.size(); j++){		
				cout << check[i][j] << " ";
			}
			newline;
		}

		sort(cands.begin(), cands.end(), cand_sort);

		for(vector<int> cand : cands){
			for(int j : cand){
				if(!taken[j]){
					pos.pb(j);
					taken[j] = true;
					break;
				}
			}
		}

		cout << pos.size() << nl;
		for(int p : pos)
			cout << p << " ";
		newline;

		ull prod = 1;
		count = 0;
		for(int i = 0; i < ticket.size(); i++){
			pii a = rules[pos[i]].second.first;
			pii b = rules[pos[i]].second.second;
			cout << ticket[i] << " " << rules[pos[i]].first << " : " << a.first << "-" << a.second << "  " << b.first << "-" << b.second << nl;
			if(rules[pos[i]].first.substr(0, 9) == "departure"){
				count++;
				prod *= (ull) ticket[i];
				cout << prod << nl;
			}
		}
	
		
		cout << "PART 2: " << prod << nl;

	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
	inp.close();
}
