#include <bits/stdc++.h>

#define nl "\n"
#define newline cout << "\n";

using namespace std;

//PART 1
void part_1(ifstream& inp)
{
	string line;
	int tot = 0;
	int limit = 2;
	while(getline(inp, line)){
		vector<int> arr;
		for(int i = 0; i < line.length(); i++){
			arr.push_back(line[i] - '0');
		}
		int index = 0;
		int num = 0;
		for(int j = 0; j < limit && index < arr.size(); j++){
			int maxn = arr[index];
			for (int i = index; i <= arr.size() - limit + j; i++) {
				if(arr[i] > maxn){
					maxn = arr[i];
					index = i;
				}
			}
			num = (num*10) + maxn;
			cout << maxn << " ";
			index += 1;
		}
		newline;
		tot += num;
	}
	cout << "Part 1: " << tot << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	uint64_t tot = 0;
	int limit = 12;
	while(getline(inp, line)){
		vector<int> arr;
		for(int i = 0; i < line.length(); i++){
			arr.push_back(line[i] - '0');
		}
		int index = 0;
		uint64_t num = 0;
		for(int j = 0; j < limit && index < arr.size(); j++){
			int maxn = arr[index];
			for (int i = index; i <= arr.size() - limit + j; i++) {
				if(arr[i] > maxn){
					maxn = arr[i];
					index = i;
				}
			}
			num = (num*10) + maxn;
			cout << maxn << " ";
			index += 1;
		}
		newline;
		tot += num;
	}
	cout << "Part 1: " << tot << nl;
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
