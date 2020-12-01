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
}
