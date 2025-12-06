#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << "\n";

using namespace std;

vector<string> get_split(string line, char delimiter)
{
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

void get_min_intervals(vector<pair<uint64_t, uint64_t>>& intervals, vector<pair<uint64_t, uint64_t>>& min_intervals)
{
	sort(intervals.begin(), intervals.end());
	uint64_t left = intervals[0].first;
	uint64_t right = intervals[0].second;
	for(int i = 1; i < intervals.size(); i++){
		if(intervals[i].first <= right){
			right = max(intervals[i].second, right);
		} else {
			min_intervals.push_back({left, right});	
			left = intervals[i].first;
			right = intervals[i].second;
		}
	}
	min_intervals.push_back({left, right});	
}

//PART 1
void part_1(ifstream& inp)
{
	string line;
	vector<pair<uint64_t, uint64_t>> ranges;
	while(getline(inp, line)){
		if(line == ""){
			break;
		}
		vector<string> r = get_split(line, '-');
		ranges.push_back({stoull(r[0]), stoull(r[1])});
	}
	vector<pair<uint64_t,uint64_t>> min_ranges;
	get_min_intervals(ranges, min_ranges);
	vector<uint64_t> ing;
	while(getline(inp, line)){
		ing.push_back(stoull(line));	
	}
	int count = 0;
	for(uint64_t i : ing){
		for(auto& range : min_ranges){
			if(i >= range.first && i <= range.second){
				count++;
				break;
			}
		}
	}
	cout << "Part 1: " << count << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	vector<pair<uint64_t, uint64_t>> ranges;
	while(getline(inp, line)){
		if(line == ""){
			break;
		}
		vector<string> r = get_split(line, '-');
		ranges.push_back({stoull(r[0]), stoull(r[1])});
	}
	vector<pair<uint64_t,uint64_t>> min_ranges;
	get_min_intervals(ranges, min_ranges);
	uint64_t tot_ing = 0;
	for(auto& range : min_ranges){
		tot_ing += range.second - range.first + 1;
	}
	cout << "Part 2: " << tot_ing << nl;
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
