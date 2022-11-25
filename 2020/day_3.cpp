#include <bits/stdc++.h>

#define newline printf("\n")
#define nl "\n"
#define ll long long 
#define ui unsigned int
#define ul unsigned long

using namespace std;

/**
Right 1, down 1.
Right 3, down 1. 
Right 5, down 1.
Right 7, down 1.
Right 1, down 2.
**/

int main()
{
	ifstream inp("input");
	vector<string> grid;
	if(inp){
		string line;
		while(getline(inp, line)){
			grid.push_back(line);	
		}
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}

	pair<int, int> slopes[] = {{1,1},{1,3},{1,5},{1,7},{2,1}};
	ll prod = 1;

	int width = grid[0].length();
	for(int i = 0; i < 5; i++){
		int x_change = slopes[i].second;
		int y_change = slopes[i].first;
		ll trees = 0;
		int x = 0;
		int y = 0;
		while(true){
			trees += (grid[y][x] == '#');
			x = (x + x_change) % width;
			y += y_change;
			if(y >= grid.size()) 
				break;
		}
		prod *= trees;
	}
	// PART 1: for second slope
	// PART 2:
	cout << "Product of discovered trees: " << prod << nl;
}
