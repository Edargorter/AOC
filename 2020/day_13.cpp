#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << nl
#define ll long long 
#define ui unsigned int
#define ul unsigned long

using namespace std;

ll mod_pow(ll a, ll b, ll n)
{
	ll result = 1, y = a;
	while(b){
		if(b & 1)
			result = (result * y) % n;
		y = (y * y) % n;
		b >>= 1;
	}
	return result % n;
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
		ll et;
		vector<pair<ll, ll>> times;
		getline(inp, line);
		et = stoll(line);
		getline(inp, line);
		vector<string> tokens = get_split(line, ',');

		for(int i = 0; i < tokens.size(); i++){
			if(tokens[i] != "x"){
				ll p = (ll) stoll(tokens[i]);
				ll ni = (p - (i % p)) % p;
				times.push_back({stoll(tokens[i]), ni});
			}
		}

		//PART 1

		int min_time = 1e9;
		ll id = times[0].first;
		for(pair<ll, ll> p : times){
			ll time = p.first;
			if(et % time){
				ll temp = et + time - (et % time);
				if(temp < min_time){
					min_time = temp;
					id = time;
				}
			} else { 
				min_time = et;
				id = time;
				break;
			}
		}
		cout << "PART 1: " << id * (min_time - et) << nl;

		//PART 2 (Chinese Remainder Theorem stuff)

		ll prod = 1;
		for(int i = 0; i < times.size(); i++)
			prod *= times[i].first;

		ll result = 0;
		for(int i = 0; i < times.size(); i++){
			ll p = prod / times[i].first;
			ll po = mod_pow(p % times[i].first, times[i].first - 2, times[i].first);
			result += po * times[i].second * p;
			result %= prod;
		}

		cout << "PART 2: " << result % prod << nl;
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
	inp.close();
}
