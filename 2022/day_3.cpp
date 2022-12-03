#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << nl;
#define ll long long 
#define ui unsigned int
#define ul unsigned long
#define ull unsigned long long
#define pii pair<int, int>
#define pb push_back

using namespace std;

/**
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
**/

int get_priority(char c){
	return (c < 0x61) ? (c - 0x41 + 27) : (c - 0x60);
}

//PART 1 utilising a neat bitwise operation duplicate finder: https://dotnettutorials.net/lesson/finding-duplicates-in-a-string-using-bitwise-operations-in-c/
void part_1(ifstream& inp)
{
	string line;
	ll sum = 0;
	while(getline(inp, line)){
		bitset<72> items;
		int index = 0;
		for(char c : line){
			bitset<72> tmp{0x1};
			tmp <<= c - 0x41;

			if((tmp & items).any() && (index >= line.length()/2)){
				sum += get_priority(c);
				break;
			} else if(index < line.length()/2)
				items |= tmp;
			index++;
		}
	}
	cout << sum << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	ll sum = 0;
	int count = 0;
	bitset<72> group{0x0};
	bitset<72> common = bitset<72>().set();
	while(getline(inp, line)){
		for(char c : line){
			bitset<72> tmp{0x1};
			tmp <<= c - 0x41;
			group |= tmp;
		}
		common &= group; 
		group.reset();
		count++;
		if(count == 3){
			char c = 0;
			while(!common.test(++c)){
			}
			c += 0x41;
			//cout << count << " char " << c << nl;
			sum += get_priority(c);
			common = bitset<72>().set();
			count = 0;
		}
	}
	cout << sum << nl;
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
