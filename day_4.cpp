#include <bits/stdc++.h>

#define newline printf("\n")
#define nl "\n"
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

int main()
{

	vector<string> fields = {"byr","iyr","eyr","hgt","hcl","ecl","pid","cid"};
	map<string, uc> pos;
	for(int i = 0; i < fields.size(); i++){
		pos.insert({fields[i], (1 << i)});
	}
	for(auto itr = pos.begin(); itr != pos.end(); itr++){
		cout << itr->first << " " << (int) itr->second << nl;
	}

	int count = 0;
	//ifstream inp("input");
	ifstream inp("temp");
	if(inp){
		string line;
		uc check = 0;	

		while(getline(inp, line)){
			if(line.empty()){
				//cout << "Check: " << check;
				if(check == 0x7f || check == 0xff){
					//cout << " Valid.";
					count++;
				}
				//cout << nl;
				check = 0;
			}
			vector<string> f = get_split(line, ' ');
			for(string s : f){
				check |= pos[s.substr(0, 3)];
				cout << (int) check << " ";
			}
			cout << nl;
		}
		if(check == 0x7f || check == 0xff){
			//cout << " Valid.";
			count++;
		}
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
	cout << "Valid passports: " << count << nl;
}
