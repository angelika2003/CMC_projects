#include <iostream>
#include <stack>

using namespace std;

bool is_operator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int main() {
	string str;
	cin >> str;

	stack <string> s;

	for (size_t i = 0; i < str.length(); i++) {
		if (is_operator(str[i])) {
			string op1 = s.top();
			s.pop();

			string op2 = s.top();
			s.pop();

			string tmp = "(" + op2 + str[i] + op1 + ")";
			s.push(tmp);
		} else {
			s.push(string(1, str[i]));
		}
	}
	cout << s.top();
}