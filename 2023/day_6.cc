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

//PART 1
void part_1(ifstream& inp)
{
	string line;
	getline(inp, line);
	vector<string> stimes = get_split(line, ' ');
	getline(inp, line);
	vector<string> sdists = get_split(line, ' ');
	vector<int> times;
	vector<int> dists;
	for(int i = 1; i < stimes.size(); i++){
		times.push_back(stoi(stimes[i]));
		dists.push_back(stoi(sdists[i]));
	}
	uint64_t prod = 1;
	for(int i = 0; i < times.size(); i++){
		int index = 0;
		int n = 0;
		int time = times[i];
		int record = dists[i];
		while((time - index) * index <= record) index++;
		while((time - index) * index > record){
			index++;
			n++;
		}
		prod *= n;
	}
	cout << "Part 1: " << prod << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	getline(inp, line);
	vector<string> stimes = get_split(line, ' ');
	getline(inp, line);
	vector<string> sdists = get_split(line, ' ');
	uint64_t time = 0;
	uint64_t dist = 0;
	for(int i = 1; i < stimes.size(); i++){
		for(int j = 0; j < stimes[i].length(); j++) time = 10 * time + uint64_t(stimes[i][j] - '0');
		for(int j = 0; j < sdists[i].length(); j++) dist = 10 * dist + uint64_t(sdists[i][j] - '0');
	}
	int index = 0;
	uint64_t n = 0;
	while((time - index) * index <= dist) index++;
	int left = index, right = time;
	int mid = 0;
	while(left < right){
		mid = left + (right - left)/2;
		uint64_t val = (time - mid) * mid;
		if(val >= dist){
			left = mid + 1;
		} else {
			right = mid;
		}
	}
	cout << "Part 2: " << mid - index << nl;
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
