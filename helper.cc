auto findCycle = [&](int node) -> pair<int, int>{
	int ins = 0;
	int jns = 0;
	int a = next(node, ins);
	int b = next(node, jns);
	b = next(b, jns);
	while(a != b){
		a = next(a, ins);	
		b = next(b, jns);	
		b = next(b, jns);	
	}
	int mu = 0;
	a = node;
	ins = 0;
	while(a != b){
		a = next(a, ins);
		b = next(b, jns);
		mu++;
	}
	int lam = 1;
	b = next(a, ins);
	while(a != b){
		b = next(b, ins);
		lam++;
	}
	return {mu, lam};
};

uint64_t getLCM(vector<int>& nums)
{
	uint64_t lcm = 1;
	for(int n : nums){
		lcm = (lcm * n)/gcd(lcm, n);
	}
	return lcm;
};

vector<string> get_split(string line, char delimiter)
{
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

string add(string a, string b)
{
	string result;
	if(a.length() > b.length())
		swap(a, b);
	int carry = 0;
	int i;
	for(i = 0; i < a.length(); i++){
		int sum = (a[i] - '0') + (b[i] - '0') + carry;
		result.pb((sum % 10) + '0');
		carry = sum/10;
	}
	for(;i < b.length(); i++){
		int sum = (b[i] - '0') + carry;
		result.pb((sum % 10) + '0');
		carry = sum/10;
	}
	if(carry)
		result.pb(carry + '0');

	return result;
}

string multiply(string a, string b)
{
	string result(a.length() + b.length(), '0');
	int ai = 0, bi = 0;
	int i;
	for(i = 0; i < a.length(); i++){
		int carry = 0;
		int a1 = a[i] - '0';
		bi = 0;
		for(int j = 0; j < b.length(); j++){
			int b1 = b[j] - '0';	
			int sum = a1 * b1 + (result[ai + bi] - '0') + carry;
			carry = sum/10;
			result[ai + bi] = (sum % 10) + '0';
			bi++;
		}
		if(carry)
			result[ai + bi] += carry;
		ai++;
	}
	i = result.length() - 1;
	while(i >= 0 && result[i] == '0')
		i--;
	return result.substr(0, i + 1);
}

string divisible(string a, int b)
{
	string result;
	reverse(result.begin(), result.end());
	int i = 0;
	ui tmp = a[i] - '0';
	while(tmp < b){
		tmp = tmp * 10 + a[++i] - '0';
	}

	while(i < result.length()){
		result += (tmp / b) + '0';
		tmp = (tmp % b) * 10 + (a[++i] - '0');
	}
	if(!result.length())
		return "0";
	return result;
}
