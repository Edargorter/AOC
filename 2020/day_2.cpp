#include <bits/stdc++.h>

#define newline printf("\n")
#define nl "\n"
#define ll long long 
#define ui unsigned int
#define ul unsigned long

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
int get_num_valid(){
	ifstream inp("input");
	int count = 0;
	if(inp){
		string line;
		while(getline(inp, line)){
			int occ = 0;
			vector<string> tokens = get_split(line, ' ');
			vector<string> nums = get_split(tokens[0], '-');
			int low = stoi(nums[0]);
			int high = stoi(nums[1]);
			char cc = tokens[1].at(0);
			for(char c : tokens[2])
				occ += (c == cc);
			if(occ >= low && occ <= high)
				count++;
		}
	} else {
		cout << "File does not exist" << nl;
		exit(1);
	}
	return count; 
}

//PART 2
int get_num_valid2(){
	ifstream inp("input");
	int count = 0;
	if(inp){
		string line;
		while(getline(inp, line)){
			vector<string> tokens = get_split(line, ' ');
			vector<string> nums = get_split(tokens[0], '-');
			int first = stoi(nums[0]) - 1;
			int second = stoi(nums[1]) - 1;
			char cc = tokens[1].at(0);
			count += (tokens[2][first] == cc) ^ (tokens[2][second] == cc);
		}
	} else {
		cout << "File does not exist" << nl;
		exit(1);
	}
	return count; 
}

int main()
{
	cout << "#1 Valid strings " << get_num_valid() << nl;
	cout << "#2 Valid strings " << get_num_valid2() << nl;
}
