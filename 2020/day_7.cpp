#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << nl;
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

ll part_one(string input_file){
	ifstream inp(input_file);
	map<string, set<string> > contains;
	int count = 0;
	if(inp){
		string line;
		while(getline(inp, line)){
			vector<string> tokens = get_split(line, ',');
			vector<string> parent = get_split(tokens[0], ' ');
			string parent_bag = parent[0] + parent[1];
			//Children
			string child_bag = parent[5] + parent[6];
			vector<string> children;
			children.push_back(child_bag);
			for(int i = 1; i < tokens.size(); i++){
				vector<string> child = get_split(tokens[i], ' ');
				child_bag = child[2] + child[3];
				children.push_back(child_bag);
			}
			for(string child : children){
				if(contains.find(child) == contains.end()){
					set<string> new_set;
					contains.insert({child, new_set});
				}
				contains[child].insert(parent_bag);
			}
		}
		set<string> check;
		vector<string> children = {"shinygold"};
		for(int i = 0; i < children.size(); i++){
			for(string parent : contains[children[i]]){
				if(check.find(parent) == check.end())
					check.insert(parent);
				else
					continue;
				children.push_back(parent);
				count++;
			}
		}
		
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
	return count;
}

//PART 2
ll part_two(string input_file){
	ifstream inp(input_file);
	map<string, vector<pair<string, int>> > contains;
	ll count = 0;
	if(inp){
		string line;
		while(getline(inp, line)){
			vector<string> tokens = get_split(line, ',');
			vector<string> parent = get_split(tokens[0], ' ');
			string parent_bag = parent[0] + parent[1];
			//Children
			if(contains.find(parent_bag) == contains.end()){
				vector<pair<string, int>> new_vec;
				contains[parent_bag] = new_vec;
			}
			int num;
			string child_bag;
			if(parent[4] != "no"){
				num = stoi(parent[4]);	
				child_bag = parent[5] + parent[6];
				contains[parent_bag].push_back({child_bag, num});
			} else {
			}
			for(int i = 1; i < tokens.size(); i++){
				vector<string> child = get_split(tokens[i], ' ');
				num = stoi(child[1]);
				child_bag = child[2] + child[3];
				if(contains.find(child_bag) == contains.end()){
					vector<pair<string, int>> p_children;
					contains.insert({child_bag, p_children});
				}
				contains[parent_bag].push_back({child_bag, num});
			}
		}
		set<string> check;
		vector<pair<string, int>> parents = {{"shinygold", 1}};
		for(int i = 0; i < parents.size(); i++){
			for(pair<string, int> child : contains[parents[i].first]){
				parents.push_back({child.first, child.second * parents[i].second});
				count += parents[i].second * child.second;
			}
		}
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
	return count;
}

int main(int argc, char **argv)
{
	string input_file;
	if(argc < 2){
		cout << "No file argument. Using 'input'" << nl;
		input_file = "input";
	} else {
		input_file = argv[1];
	}
	cout << part_one(input_file) << nl;
	cout << part_two(input_file) << nl;
	return 0;
}
