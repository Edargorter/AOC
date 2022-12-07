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

#define N 70000000
#define F 30000000

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

struct file
{
	string name;
	int size;
};

struct directory
{
	string name;
	vector<directory*> subdirs;
	vector<file*> files;
};

int get_dir_size(vector<pair<directory*, ui>>& fs, directory* dir)
{
	ui size = 0;
	for(file* f : dir->files)
		size += f->size;
	for(directory* subdir : dir->subdirs)
		size += get_dir_size(fs, subdir);
	fs.pb({dir, size});
	return size;
}

void pwd(directory* dir, int count)
{
	for(int i = 0; i < count; i++)
		cout << "-";
	cout << dir->name << nl;
	for(struct directory* subdir : dir->subdirs)
		pwd(subdir, count + 1);
}

directory* get_root(ifstream& inp)
{
	string line;
	string dir = "";
	vector<directory*> dirs;
	string l = "";
	while(getline(inp, line)){
		vs op = get_split(line, ' ');	
		if(op[0] == "$"){
			if(op[1] == "cd"){
				if(op[2] == ".."){
					dirs.pop_back();
				} else {
					directory* cand = nullptr;
					if(!dirs.empty()){
						bool found = false;
						for(directory* d : dirs.back()->subdirs){
							if(d->name == op[2]){
								cand = d;
								break;
							}
						}
						if(!cand){
							cand = new directory{op[2], vector<directory*>(), vector<file*>()};
							(dirs.back()->subdirs).pb(cand);
						} 
					} else {
						cand = new directory{op[2], vector<directory*>(), vector<file*>()};
					}
					dirs.pb(cand);
				}
			} else if(op[1] == "ls"){
				continue;
			}
		} else if(op[0] == "dir"){
			continue;
		} else {
			bool found = false;
			for(file* f : dirs.back()->files){
				if(f->name == op[1]){
					found = true;
					break;
				}
			}
			if(!found){
				file* cand = new file{op[1], stoi(op[0])};
				(dirs.back()->files).pb(cand);
			}
		}
	}
	return dirs.front();
}

//PART 1
void part_1(ifstream& inp)
{
	directory* root = get_root(inp);
	//pwd(root, 0);
	vector<pair<directory*, ui>> fs;
	get_dir_size(fs, root);
	ui cap = 0;
	for(int i = 0; i < fs.size(); i++)
		if(fs[i].second <= 100000)
			cap += fs[i].second;
	cout << cap << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	directory* root = get_root(inp);
	vector<pair<directory*, ui>> fs;
	ui size = get_dir_size(fs, root);
	ui needed = size - (N - F);
	string name;
	ui min = N;
	for(int i = 0; i < fs.size(); i++){
		if(fs[i].second >= needed && fs[i].second < min){
			min = fs[i].second;
			name = fs[i].first->name;
		}
	}
	cout << min << nl;
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
