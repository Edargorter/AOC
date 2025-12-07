#include <bits/stdc++.h>

#define nl "\n"
#define newline cout << "\n";

using namespace std;

vector<string> get_split(string line, char delimiter)
{
	vector<string> info;
	string word = "";
	int pos = 0;
	int len = 0;
	bool inword = false;
	for(int i = 0; i < line.length(); i++){
		if(line[i] == delimiter){
			if (inword) {
				info.push_back(line.substr(pos, len));
				inword = false;
			}
		} else {
			if (!inword) {
				pos = i;
				len = 0;
			}
			len++;
			inword = true;
			if(i == line.length() - 1)
				info.push_back(line.substr(pos, len));
		}
	}
	return info;
}

uint64_t apply_op(vector<vector<uint64_t>>& vals, int index, string op)
{
	uint64_t res = vals[0][index];
	for(int i = 1; i < vals.size(); i++){
		uint64_t cur = vals[i][index];
		res = (op == "+") ? res + cur : res * cur;
	}
	return res;
}

//PART 1
void part_1(ifstream& inp)
{
	string line;
	vector<vector<uint64_t>> nums;
	vector<string> ops;
	while(getline(inp, line)){
		vector<string> res = get_split(line, ' ');
		if(res[0] == "*" || res[0] == "+"){
			ops	= res;
			break;
		}
		vector<uint64_t> lnums;
		for(int i = 0; i < res.size(); i++){
			lnums.push_back(stoull(res[i]));
		}
		nums.push_back(lnums);
	}
	uint64_t tot = 0;
	for(int i = 0; i < nums[0].size(); i++){
		uint64_t res = apply_op(nums, i, ops[i]);
		tot += res;
	}
	cout << "Part 1: " << tot << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	vector<string> nums;
	vector<string> ops;
	while(getline(inp, line)){
		if(line[0] == '*' || line[0] == '+'){
			ops = get_split(line, ' ');
			break;
		}
		nums.push_back(line);
	}
	uint64_t tot = 0;
	uint64_t res = 0;
	int op_ind = ops.size() - 1;
	string op = ops[op_ind--];
	for(int i = nums[0].size()-1; i >= 0; i--){
		bool incalc = false;
		uint64_t c_num = 0;
		for(int j = 0; j < nums.size(); j++){
			char c = nums[j][i];
			if(c != ' '){
				incalc = true;
				c_num = 10*c_num + c - '0';
			}
		}
		if(!incalc){
			op = ops[op_ind--];
			tot += res;
			res = (op == "+") ? 0 : 1;
		} else {
			res = (op == "+") ? res + c_num : res * c_num;
		}
	}
	tot += res;
	cout << "Part 2: " << tot << nl;
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
