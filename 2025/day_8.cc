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

struct coord {
	int x;
	int y;
	int z;
};

struct node {
	int c_index;
	int num;
	node* parent;
};

inline node* get_root(node* curr)
{
	while(curr->parent != nullptr){
		curr = curr->parent;
	}
	return curr;
}

inline uint64_t dist(coord& a, coord& b)
{
	uint64_t res = pow(a.x - b.x, 2) + 
		pow(a.y - b.y, 2) + pow(a.z - b.z, 2);
	return res;
}

uint64_t get_prod(vector<node>& nodes)
{
	vector<int> counts;
	for(int i = 0; i < nodes.size(); i++){
		if(nodes[i].parent == nullptr){
			counts.push_back(nodes[i].num);
		}
	}
	sort(counts.begin(), counts.end(), std::greater<>());
	uint64_t prod = 1;
	int top = 3;
	for(int i = 0; i < top; i++) prod *= counts[i];
	return prod;
}

//PART 1 and 2
void part_1_and_2(ifstream& inp)
{
	string line;
	getline(inp, line);
	int limit = stoi(line);

	vector<coord> coords;
	while(getline(inp, line)){
		vector<string> res = get_split(line, ',');	
		coords.push_back({stoi(res[0]), stoi(res[1]), stoi(res[2])});
	}
	vector<int> circuit(coords.size(), 0);

	struct pair_dist {
		int first;
		int second;
		uint64_t dist;
	};

	vector<pair_dist> dists;
	for(int i = 0; i < coords.size()-1; i++){
		for(int j = i+1; j < coords.size(); j++){
			uint64_t d = dist(coords[i], coords[j]);
			dists.push_back({i,j,d});
		}
	}
	sort(dists.begin(), dists.end(), [](const auto& a, const auto& b){
		return a.dist < b.dist;
	});

	vector<node> nodes;
	for(int i = 0; i < coords.size(); i++){
		nodes.push_back({i, 1, nullptr});
	}
	
	uint64_t prod;
	int count = 0;
	for(int i = 0; i < dists.size(); i++){
		pair_dist pd = dists[i];
		
		node* first = get_root(&nodes[pd.first]);
		node* second = get_root(&nodes[pd.second]);

		if(first != second){
			first->num += second->num;
			second->parent = first;
			dists[i].dist = 0;
		} 

		count++;
		if(count == limit){
			prod = get_prod(nodes);
		}
	}

	cout << "Part 1: " << prod << nl;

	uint64_t x_prod;
	for(int i = dists.size() - 1; i >= 0; i--){
		if (dists[i].dist == 0){
			x_prod = uint64_t(coords[dists[i].first].x) * uint64_t(coords[dists[i].second].x);
			break;
		}
	}
	cout << "Part 2: " << x_prod << nl;
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
		part_1_and_2(inp);
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
	inp.close();
}
