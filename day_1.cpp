#include <bits/stdc++.h>

#define newline printf("\n")
#define nl "\n"
#define ll long long 
#define ui unsigned int
#define ul unsigned long

using namespace std;

int main()
{
	vector<int> nums;
	ifstream inp("inp_1.txt");
	if(inp){
		int temp;
		while(inp >> temp)
			nums.push_back(temp);
	} else {
		cout << "File does not exist" << nl;
		exit(1);
	}

	//PART 1
	sort(nums.begin(), nums.end());

	bool found = false;
	int i;
	int diff, low, high, mid;
	for(i = 0; i < nums.size() - 1; i++){
		diff = 2020 - nums[i];
		low = i + 1, high = nums.size() - 1;
		mid = low + (high - low)/2;
		while(low != mid){
			if(nums[mid] > diff)
				high = mid;
			else if(nums[mid] < diff)
				low = mid;
			else {
				found = true;
				break;
			}
			mid = low + (high - low)/2;
		}

		if(found)
			break;
	}

	cout << nums[i] << " " << nums[mid] << nl;
	cout << nums[i] + nums[mid] << nl;
	cout << nums[i] * nums[mid] << nl;

	//PART 2

	found = false;
	int j;
	for(i = 1; i < nums.size(); i++){
		low = 0, high = i;
		mid = low + (high - low)/2;
	
		while(low != mid){
			if(nums[mid] + nums[i] < 2020)
				low = mid;
			else if(nums[mid] + nums[i] > 2020)
				high = mid;
			mid = low + (high - low)/2;
		}

		for(j = mid; j >= 0; j--){

			diff = 2020 - nums[j] - nums[i];
			low = i + 1, high = nums.size() - 1;
			mid = low + (high - low)/2;
			while(low != mid){
				if(nums[mid] > diff)
					high = mid;
				else if(nums[mid] < diff)
					low = mid;
				else {
					found = true;
					break;
				}
				mid = low + (high - low)/2;
			}
			if(found)
				break;
		}

		if(found)
			break;
	}

	cout << nums[i] << " " << nums[j] << " " << nums[mid] << nl;
	cout << nums[i] + nums[j] + nums[mid] << nl;
	cout << (long)nums[i] * (long)nums[j] * (long)nums[mid] << nl;

}
