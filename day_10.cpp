#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << nl;
#define ll long long 
#define ui unsigned int
#define ul unsigned long

using namespace std;

int main(int argc, char **argv)
{
	string input_file;
	if(argc < 2){
		cout << "No file arguemnt. Using 'input'" << nl;
		input_file = "input";
	} else {
		input_file = argv[1];
	}
	ifstream inp(input_file);
	vector<int> adp;
	if(inp){
		int temp;
		ll od = 0, td = 1;
		adp.push_back(0);
		while(inp >> temp){
			adp.push_back(temp);
		}
		sort(adp.begin(), adp.end());
		for(int i = 1; i < adp.size(); i++){
			int diff = adp[i] - adp[i-1];
			if(diff == 1)
				od++;
			else if(diff == 3)
				td++;
		}
		//PART 1
		cout << "PART 1: " << od * td << nl;

		//PART 2
		ll back_3 = 1;
		ll back_2 = back_3;
		ll back_1 = back_2 + (adp[2] <= 3);

		ll count;
		for(int i = 3; i < adp.size(); i++){
			cout << back_1 << nl;
			count = back_1;
			if(adp[i] - adp[i-2] <= 3)
				count += back_2;
			if(adp[i] - adp[i-3] <= 3)
				count += back_3;
			back_3 = back_2;
			back_2 = back_1;
			back_1 = count;
		}

		cout << "PART 2: " << count << nl;

	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
}
