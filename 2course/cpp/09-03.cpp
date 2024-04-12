#include <string>
#include <iostream>
using namespace std;

bool is_correct(const string& str) {
	int a_count = 0;
	int b_count = 0;
	int zero_count = 0;
	int one_count = 0;

	int n = (int)str.length();
	//cout<<n;
	int i = 0;

	while (str[i] == 'a') {
		a_count++;
		i++;
	}
	while (str[i] == '0') {
		zero_count++;
		i++;
	}
	while (str[i] == 'b') {
		b_count++;
		i++;
	}

	while (str[i] == '1') {
		one_count++;
		i++;
	}
	if(i!=n){
		return false;
	}

	if(a_count != b_count){
		return false;
	}

	if (zero_count != one_count){
		return false;
	}
	return (a_count > 0) && (zero_count > 0);
}

int main() {
	string str;
	while (cin >> str) {
		cout << is_correct(str) << endl;
	}

}



