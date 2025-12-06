#include <bits/stdc++.h>

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

//PART 1
void part_1(ifstream& inp)
{
	string line;
	vector<pair<string, string>> ranges;
	getline(inp, line);
	vector<string> tokens = get_split(line, ',');
	for(string& token : tokens){
		vector<string> bounds = get_split(token, '-');
		ranges.push_back({bounds[0], bounds[1]});
	}

	uint64_t count = 0;
	for(auto& interval : ranges){
		int len = interval.first.length() / 2;
		uint64_t ilower = stoull(interval.first);
		uint64_t iupper = stoull(interval.second);
		string half = (interval.first.length() == 1) ? "0" : interval.first.substr(0, len);
		
		while (half.length() * 2 <= interval.second.length()){
			uint64_t ti = stoull(half + half);
			if (ilower <= ti && ti <= iupper){
				count += ti;
			} else if (ti >= iupper) {
				break;
			}
			half = to_string(stoull(half) + 1);
		}
	}
	cout << "Part 1: " << count << nl;
}

bool invalid(uint64_t test)
{
	string st = to_string(test);
	for(int i = 1; i <= st.length()/2; i++){
		if(st.length() % i == 0){
			bool check = true;
			string pattern = st.substr(0, i);
			for(int j = 1; j < st.length()/i; j++){
				//cout << test << " " << st.substr(j*i, i) << nl;
				if(st.substr(j*i, i) != pattern){
					check = false;
					break;
				}
			}
			if (check) {
				return true;
			}
		}
	}
	return false;
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	vector<pair<uint64_t, uint64_t>> ranges;
	getline(inp, line);
	vector<string> tokens = get_split(line, ',');
	for(string& token : tokens){
		vector<string> bounds = get_split(token, '-');
		ranges.push_back({stoull(bounds[0]), stoull(bounds[1])});
	}

	uint64_t count = 0;
	for(auto& interval : ranges){
		for(uint64_t i = interval.first; i <= interval.second; i++){
			if(invalid(i)){
				//cout << i << nl;
				count += i;
			}
		}
	}
	cout << "Part 2: " << count << nl;
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
