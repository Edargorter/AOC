#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define ll long long 
#define ui unsigned int
#define ul unsigned long
#define ull unsigned long long
#define pii pair<int, int>
#define pb push_back
#define vs vector<string>

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
	int sum = 0;
	while(getline(inp, line)){
		vs sections = get_split(line, ',');
		vs first_a = get_split(sections[0], '-');
		vs second_a = get_split(sections[1], '-');
		int aa = stoi(first_a[0]);
		int ab = stoi(first_a[1]);
		int ba = stoi(second_a[0]);
		int bb = stoi(second_a[1]);
		sum += ((ab <= bb) && (ba <= aa)) || ((bb <= ab) && (aa <= ba));
	}
	cout << sum << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	int sum = 0;
	while(getline(inp, line)){
		vs sections = get_split(line, ',');
		vs first_a = get_split(sections[0], '-');
		vs second_a = get_split(sections[1], '-');
		int aa = stoi(first_a[0]);
		int ab = stoi(first_a[1]);
		int ba = stoi(second_a[0]);
		int bb = stoi(second_a[1]);
		sum += ((ba <= ab) && (ab <= bb)) || ((aa <= bb) && (bb <= ab));
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
