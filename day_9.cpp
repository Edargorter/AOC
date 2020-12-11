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
		cout << "No file argument. Using 'input'" << nl;
		input_file = "input";
	} else {
		input_file = argv[1];
	}
	ifstream inp(input_file);
	vector<int> ni;
	if(inp){
		int x;
		while(inp >> x){
			ni.push_back(x);
		}
		int range = 25;
		int i;
		for(i = range; i < ni.size(); i++){
			x = ni[i];
			bool check = false;
			for(int j = i - range; j < i - 1; j++){
				for(int k = j + 1; k < i; k++){
					if(ni[j] + ni[k] == x){
						check = true;
						break;
					}
				}
			}
			if(!check){
				cout << "PART 1: " << x << nl;
				break;
			}
		}
		//PART 2
		vector<ll> pre = {ni[0]};
		for(int j = 1; j < i; j++)
			pre.push_back(pre[j - 1] + ni[j]);

		ll sum;
		bool found = false;
		int mid;
		int j;
		for(j = 0; j < i - 1; j++){
			int low = j, high = i - 1;
			mid = low + (high - low)/2;
			while(low != mid){
				sum = pre[mid] - pre[j] + ni[j];
				if(sum > x){
					high = mid;
				} else if(sum < x){
					low = mid;
				} else {
					found = true;
					break;
				}
				mid = low + (high - low)/2;
			}
			if(found)
				break;
		}
		vector<int> subarr;
		for(int k = j; k <= mid; k++)
			subarr.push_back(ni[k]);

		sort(subarr.begin(), subarr.end());

		cout << "PART 2: " << subarr[0] + subarr[subarr.size() - 1] << nl;
		
	} else {
		cout << "File does not exist." << nl;
		exit(1);
	}
}
