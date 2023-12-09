#include <bits/stdc++.h>
//#include "bits.h"

#define nl "\n"
#define newline cout << "\n";

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

//Five of a kind, Four of a kind, full house, three of a kind, two pair, one pair, high card 

int getType(string card, bool joker)
{
	assert(card.length() == 5);
	string distinct = "";
	vector<int> occ;
	int jokers = 0;
	for(int i = 0; i < card.length(); i++){
		char c = card[i];
		if(joker && c == 'J'){
			jokers++;
			continue;
		}
		bool dup = false;
		for(int j = 0; j < distinct.length(); j++){
			if(c == distinct[j]){
				dup = true;
				occ[j]++;
				break;
			} 
		}
		if(!dup){
			distinct += c;
			occ.push_back(1);
		}
	}

	int type = 0;
	int os = occ.size();
	if(joker && (jokers > 0)){
		switch(jokers){
			case 5: case 4:
				type = 7;
				break;
			case 3:	
				if(os == 2) type = 6;
				else type = 7;
				break;
			case 2:
				if(os == 3) type = 4;
				else if(os == 2) type = 6;
				else type = 7;
				break;
			case 1:
				if(os == 4) type = 2;
				else if(os == 3) type = 4;
				else if(os == 2) {
					if(occ[0] == occ[1]) type = 5;
					else type = 6;
				}
				else type = 7;
				break;
		}
	} else {
		switch(os) {
			case 1: // Five of a kind 
				type = 7;
				break;
			case 2:
				if((occ[0] | occ[1]) == 5) type = 6; // Four of a kind
				else type = 5; // Full house
				break;
			case 3:
				if(occ[0] & occ[1] & occ[2] & 1) type = 4; // Three of a kind
				else type = 3; // Two pair
				break;
			case 4:
				type = 2; // One pair
				break;
			case 5:
				type = 1; // High card
				break;
		}
	}
	return type;
}

struct hand_bid {
	string orig;
	string hand;
	int type;
	int bid;
};

uint64_t processHands(vector<hand_bid>& hb)
{
	sort(hb.begin(), hb.end(), [](const hand_bid& a, const hand_bid& b){
		if(a.type == b.type){
			return lexicographical_compare(a.hand.begin(), a.hand.end(), b.hand.begin(), b.hand.end());
		} 
		return a.type < b.type;
	});

	uint64_t tot = 0;
	for(int i = 0; i < hb.size(); i++){
		tot += (i + 1) * hb[i].bid;			
	}
	return tot;
}

//PART 1
void part_1(ifstream& inp)
{
	string line;
	unordered_map<char, char> comap;
	string cards = "23456789TJQKA";
	vector<char> ranks(cards.length());
	iota(ranks.begin(), ranks.end(), 0x41);

	for(int i = 0; i < cards.length(); i++){
		comap.insert({cards[i], ranks[i]});
	}

	auto translate = [&](string hand){
		for(int i = 0; i < hand.length(); i++){
			hand[i] = comap[hand[i]];
		}
		return hand;
	};

	vector<hand_bid> hb;

	while(getline(inp, line)){
		vector<string> data = get_split(line, ' ');
		int d_type = getType(data[0], false);
		hb.push_back({data[0], translate(data[0]), d_type, stoi(data[1])});
	}

	uint64_t tot = processHands(hb);

	cout << "Part 1: " << tot << nl;
}

//PART 2
void part_2(ifstream& inp)
{
	string line;
	unordered_map<char, char> comap;
	string cards = "J23456789TQKA";
	vector<char> ranks(cards.length());
	iota(ranks.begin(), ranks.end(), 0x41);

	for(int i = 0; i < cards.length(); i++){
		comap.insert({cards[i], ranks[i]});
	}

	auto translate = [&](string hand){
		assert(hand.length() == 5);
		for(int i = 0; i < hand.length(); i++){
			hand[i] = comap[hand[i]];
		}
		return hand;
	};

	vector<hand_bid> hb;

	while(getline(inp, line)){
		vector<string> data = get_split(line, ' ');
		int d_type = getType(data[0], true);
		hb.push_back({data[0], translate(data[0]), d_type, stoi(data[1])});
	}

	uint64_t tot = processHands(hb);

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
