//#include <bits/stdc++.h>
#include "bits.h"

#define nl "\n"
#define newline cout << nl;
#define ll long long 
#define ui unsigned int
#define ul unsigned long
#define uc unsigned char 

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

/**
byr (Birth Year)
iyr (Issue Year)
eyr (Expiration Year)
hgt (Height)
hcl (Hair Color)
ecl (Eye Color)
pid (Passport ID)
cid (Country ID)
**/

vector<string> valid_eye_colours = {"amb","blu","brn","gry","grn","hzl","oth"};

bool is_valid(int id, string val)
{
	bool check = true;
	if(!(id ^ 1)){
		int i = stoi(val);
		check = val.length() == 4 && i >= 1920 && i <= 2002;
	} else if(!(id ^ (1 << 1))){
		int i = stoi(val);
		check = val.length() == 4 && i >= 2010 && i <= 2020;
	} else if(!(id ^ (1 << 2))){
		int i = stoi(val);
		check = val.length() == 4 && i >= 2020 && i <= 2030;
	} else if(!(id ^ (1 << 3))){
		string end = val.substr(val.length() - 2, 2);
		if(end == "cm"){
			int num = stoi(val.substr(0, val.length() - 2));
			check = num >= 150 && num <= 193;
		} else if(end == "in"){
			int num = stoi(val.substr(0, val.length() - 2));
			check = num >= 59 && num <= 76;
		} else {
			check = false;
		}
	} else if(!(id ^ (1 << 4))){
		if(val[0] == '#' && val.length() == 7){
			for(char c : val.substr(1, val.length())){
				if(c < 0x30 || (c > 0x39 && c < 0x60) || c > 0x66){
					check = false;
					break;
				}
			}	
		} else {
			check = false;
		}
	} else if(!(id ^ (1 << 5))){
		if(find(begin(valid_eye_colours), end(valid_eye_colours), val) == end(valid_eye_colours)){
			check = false;
		}
	} else if(!(id ^ (1 << 6))){
		if(val.length() == 9){
			for(char c : val){
				if(c < 0x30 || c > 0x39){
					check = false;
					break;
				}
			}
		} else {
			check = false;
		}
	} 
	return check;
}

int main(int argc, char **argv)
{

	vector<string> fields = {"byr","iyr","eyr","hgt","hcl","ecl","pid","cid"};
	map<string, uc> pos;
	for(int i = 0; i < fields.size(); i++){
		pos.insert({fields[i], (1 << i)});
	}
	for(auto itr = pos.begin(); itr != pos.end(); itr++){
		cout << itr->first << " " << (int) itr->second << nl;
	}

	string input_file;
	if(argc < 2){
		cout << "No file argument. Using 'input'" << nl;
		input_file = "input";
	} else {
		input_file = argv[1];
	}
	int count = 0;
	ifstream inp(input_file);
	if(inp){
		string line;
		uc check = 0;	

		bool valid = true;
		while(getline(inp, line)){
			//cout << line << nl;
			if(line.empty()){
				count += valid && (check == 0x7f || check == 0xff);
				check = 0;
				valid = true;
			}
			vector<string> f = get_split(line, ' ');
			for(string s : f){
				vector<string> keys = get_split(s, ':');
				int id = pos[keys[0]];
				cout << keys[0] << " " << keys[1] << " ";
				cout << id << " ";
				bool result = is_valid(id, keys[1]);
				cout << (result ? "True" : "False") << nl;
				valid = valid && result;
				check |= id;
				//cout << (int) check << " ";
			}
			//cout << nl << (int) check << nl;
			cout << "VALID: " << valid << nl;
		}
		count += valid && (check == 0x7f || check == 0xff);
	} else {
		cout << "File does not exist." << nl;
		exit(2);
	}
	cout << "Valid passports: " << count << nl;
}
