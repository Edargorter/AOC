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

inline int dist(int r1, int c1, int r2, int c2)
{
	return abs(r2 - r1) + abs(c2 - c1);
}

bool compare(pii a, pii b)
{
	return a.first < b.first;
}

vector<pii> get_intervals(vector<pii>& ss, map<pii, pii>& bs, set<pii>& uniq_b, int row)
{
	vector<pii> dists; 

	for(pii sen : ss){
		pii bec = bs[sen];
		int bdist = dist(sen.first, sen.second, bec.first, bec.second);
		int left = sen.second;
		int right = sen.second;
		if(dist(row, right, sen.first, sen.second) > bdist)
			continue;
		while(dist(row, right, sen.first, sen.second) < bdist){
			right++;
		}
		while(dist(row, left, sen.first, sen.second) <= bdist){
			left--;
		}
		dists.pb({left, right});
	}

	sort(dists.begin(), dists.end(), compare);
	vector<pii> intervals;

	int right = -1e8;
	int left = -1e8;
	for(int i = 0; i < dists.size(); i++){
		left = max(right, dists[i].first);
		right = max(right, dists[i].second);
		intervals.pb({left, right});
		for(pii b : uniq_b){
			if(b.first == row && (b.second > left && b.second <= right)){
				intervals.pop_back();
				if(b.second > left + 1)
					intervals.pb({left, b.second - 1});
				if(b.second < right)
					intervals.pb({b.second, right});
			}
		}
	}
	return intervals;
}


//PART 1
void answer(ifstream& inp)
{
	string line;
	vector<pii> ss;
	map<pii, pii> bs;
	set<pii> uniq_b;

	while(getline(inp, line)){
		vs tokens = get_split(line, ' ');

		vs sensor_r = get_split(tokens[3], '=');
		vs sensor_c = get_split(tokens[2], '=');
		vs beacon_r = get_split(tokens[9], '=');
		vs beacon_c = get_split(tokens[8], '=');

		pii sen = {stoi(sensor_r[1].substr(0, sensor_r[1].length() - 1)),
				stoi(sensor_c[1].substr(0, sensor_c[1].length() - 1))};

		ss.pb(sen);

		bs[sen] = {stoi(beacon_r[1]),
				stoi(beacon_c[1].substr(0, beacon_c[1].length() - 1))};

		uniq_b.insert(bs[sen]);
	}

	vector<pii> result = get_intervals(ss, bs, uniq_b, 2000000);

	int count = 0;

	for(pii p : result)
		count += p.second - p.first;

	cout << count << nl;

	long limit = 4000000;

	vi dists;
	for(int i = 0; i < ss.size(); i++){
		pii s = ss[i];
		pii b = bs[s];
		int d = dist(b.first, b.second, s.first, s.second);
		dists.pb(d);
	}

	int dir[4][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

	for(int sen = 0; sen < ss.size(); sen++){
		pii s = ss[sen];
		int d = dists[sen];
		for(int r = 0; r <= d + 1; r++){
			int c = (d + 1) - r;
			bool found = true;
			for(int k = 0; k < 4; k++){
				long row = s.first + r*dir[k][0];
				long col = s.second + c*dir[k][1];
				assert(dist(s.first, s.second, row, col) == d + 1);
				if(!(row >= 0 && row <= limit && col >= 0 && col <= limit))
					continue;
				found = false;
				for(int i = 0; i < ss.size(); i++){
					if(dist(ss[i].first, ss[i].second, row, col) <= dists[i]){
						found = true;
						break;
					}
				}
				if(!found){
					cout << col * 4000000 + row << nl;
					return;
				}
			}
		}
	}
}

//PARTS 1 and 2
void parts(ifstream& inp)
{
	answer(inp);
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
