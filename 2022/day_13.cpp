#include <bits/stdc++.h>
#include <unistd.h>
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

using namespace std;

struct token
{
	int val;
	vector<token*> ts;
};

token* get_tokens(string a)
{
	string val = "";
	vector<token*> tks(1, new token{-1, vector<token*>()});
	for(char c : a){
		if(c == '['){
			token* t = new token{-1, vector<token*>()};
			tks.back()->ts.pb(t);
			tks.pb(t);
		} else if(c == ']'){
			token* t;
			if(val != ""){
				t = new token{stoi(val), vector<token*>()};
				tks.back()->ts.pb(t);
				val = "";
			} else
				t = new token{-1, vector<token*>()};
			tks.pop_back();
		} else if(c == ','){
			if(val != ""){
				token* t = new token{stoi(val), vector<token*>()};
				tks.back()->ts.pb(t);
				val = "";
			} 
		} else {
			val += c;
		}
	}
	return tks.front();
}

void print_token(token* t)
{
	for(int i = 0; i < t->ts.size(); i++){
		token* tt = t->ts[i];
		if(tt->val != -1)
			cout << tt->val;
		else {
			cout << "[";
			print_token(tt);
			cout << "]";
		}
		if(i < t->ts.size() - 1)
			cout << ",";
	}
}

bool compare(string a, string b)
{
	token* atks = get_tokens(a);
	token* btks = get_tokens(b);

	vector<token*> as;
	vector<token*> bs;
	as.pb(atks);
	bs.pb(btks);
	vi aindex;
	vi bindex;

	bool yes = false;

	int i = 0, j = 0;

	while(i < as.back()->ts.size() && j < bs.back()->ts.size()){
		token* at = as.back()->ts[i];
		token* bt = bs.back()->ts[j];
		if(at->val != -1){
			if(bt->val != -1){
				if(at->val < bt->val){
					yes = true;
					break;
				} else if(at->val > bt->val){
					break;
				}
				i++;
				j++;
			} else {
				//[[2, 2 ...
				//[[[3, 4 ...
				vector<token*> nts;
				nts.pb(at);
				token* t = new token{-1, nts};
				as.back()->ts[i] = t;
			}
		} else {
			if(bt->val != -1){
				vector<token*> nts;
				nts.pb(bt);
				token* t = new token{-1, nts};
				bs.back()->ts[j] = t;
			} else {
				as.pb(at);
				aindex.pb(i + 1);
				i = 0;
				bs.pb(bt);
				bindex.pb(j + 1);
				j = 0;
			}
		}
		if(i == as.back()->ts.size() && j == bs.back()->ts.size()){
			as.pop_back();
			bs.pop_back();
			i = aindex.back();
			j = bindex.back();
			aindex.pop_back();
			bindex.pop_back();
		} 
		if(i == as.back()->ts.size()){
			yes = true;
			break;
		} else if(j == bs.back()->ts.size()){
			break;
		}
	}
	return yes;
}

//PART 1
void part_1(ifstream& inp)
{
	string a;
	string b;
	int ordered = 0;
	int index = 1;

	while(getline(inp, a)){
		getline(inp, b);
		if(compare(a, b))
			ordered += index;
		index++;
		getline(inp, a);
	}
	cout << ordered << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	string a, b;
	vs pkts;
	while(getline(inp, a)){
		getline(inp, b);
		pkts.pb(a);
		pkts.pb(b);
		getline(inp, a);
	}
	pkts.pb("[[2]]");
	pkts.pb("[[6]]");
	sort(pkts.begin(), pkts.end(), compare);
	int ans = 1;
	for(int i = 0; i < pkts.size(); i++){
		if(pkts[i] == "[[2]]" || pkts[i] == "[[6]]")
			ans *= i + 1;
	}
	cout << ans << nl;
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
