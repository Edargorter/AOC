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

//PART 1
void part_1(ifstream& inp)
{
	string line;
	vector<uint64_t> convert;
	getline(inp, line);
	vector<string> seed_str = get_split(line, ' ');
	for(int i = 1; i < seed_str.size(); i++){
		convert.push_back(stoull(seed_str[i]));
	}
	vector<bool> touched(convert.size(), false);
	bool skip = false;
	while(getline(inp, line)){
		if(line == ""){
			skip = true;
			continue;
		} 
		if(skip){
			for(int i = 0; i < convert.size(); i++){
				touched[i] = false;
			}
			skip = false;
			continue;
		}
		vector<string> sa = get_split(line, ' ');
		uint64_t ds = stoull(sa[0]);
		uint64_t ss = stoull(sa[1]);
		uint64_t range = stoull(sa[2]);
		for(int i = 0; i < convert.size(); i++){
			if(!touched[i] && convert[i] >= ss && convert[i] < ss + range){
				convert[i] = ds + (convert[i] - ss);
				touched[i] = true;
			} 
		}
	}
	uint64_t min = *min_element(convert.begin(), convert.end());
	cout << "Part 1: " << min << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	struct interval {
		uint64_t start;
		uint64_t end;
	};
	vector<interval> convert;
	getline(inp, line);
	vector<string> seed_str = get_split(line, ' ');
	int id_count = 0;
	for(int i = 1; i < seed_str.size(); i += 2){
		uint64_t start = stoull(seed_str[i]);
		uint64_t range = stoull(seed_str[i+1]);
		convert.push_back({start, start + range});
	}
	vector<vector<uint64_t>> mps;
	bool skip = false;

	auto update = [&](vector<vector<uint64_t>>& mappings){
		for(int i = 0; i < convert.size(); i++){
			newline;
			for(int j = 0; j < mappings.size(); j++){
				uint64_t dest = mappings[j][0];
				uint64_t src = mappings[j][1];
				uint64_t range = mappings[j][2];
				cout << " (" << convert[i].start << "," << convert[i].end << ") -> [" << dest << " " << src << " " << range << "]\n";

				/*
				  [start -------- end)
				[src -------- src+range)

				     [start -------- end)
				[src --- src+range)
				
				[start -------- end)
				     [src --- src+range)

				[start ------------- end)
				     [src - src+range)
				*/

				uint64_t src_max = src + range; // Max source val 
				if(convert[i].start >= src && convert[i].start < src_max){
					if(convert[i].end > src_max){
						convert.push_back({src_max, convert[i].end});
						convert[i].end = src_max;
					} 
					convert[i].start = dest + (convert[i].start - src);
					convert[i].end = dest + (convert[i].end - src);
					break;
				} else if(convert[i].start < src && src < convert[i].end){
					uint64_t new_range = 0;
					if(src_max < convert[i].end){
						new_range = range;
						convert.push_back({src_max, convert[i].end});
					} else {
						new_range = convert[i].end - src;
					}
					convert.push_back({src, src + new_range});
					convert[i].end = src;
					break;
				}
			}
		}
		mappings.clear();
	};

	while(true){
		auto& isline = getline(inp, line);
		if(!isline){
			update(mps);
			break;
		} else if(line[0] >= '0' && line[0] <= '9'){
			vector<string> sa = get_split(line, ' ');
			uint64_t ds = stoull(sa[0]);
			uint64_t ss = stoull(sa[1]);
			uint64_t range = stoull(sa[2]);
			mps.push_back({ds, ss, range});
		} else {
			if(mps.size()) update(mps);
			continue;
		}
	}
	uint64_t minl = convert[0].start;
	for(int i = 0; i < convert.size(); i++){
		cout << convert[i].start << " ";
		minl = min(convert[i].start, minl);
	}
	newline;
	cout << "Part 2: " << minl << nl;
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
