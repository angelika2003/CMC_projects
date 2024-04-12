#include <iostream>
using namespace std;

bool is_correct(char* s, int n) {
// только из 0 и 1
	for (int i = 0; i < n; i++) {
		if (s[i] != '0' && s[i] != '1') {
			return false;
		}
	}
	int i = 0;
// не начинается с 1
	if (s[i] == '1') {
		return false;
	}
// индекс первой единицы
	while (i < n && s[i] != '1') {
		i++;
	}
// все 0 нельзя
	if (i == n) {
		return false;
	}
// индекс сразу после первой цепочки
	while (i < n && s[i] == '1') {
		i++;
	}
	if (n % i != 0) {
		return false;
	}
	int j = i;
	while (j < n) {
		if (s[j] != s[j - i]) {
			return false;
		}
		j++;
	}
	return true;
}


int main() {
	int BUFFER_SIZE = 1000;
	char* s = new char[BUFFER_SIZE];
	int len = 0;
	char c;

	while ((c = getchar()) != EOF) {
		if (len + 2 == BUFFER_SIZE) {
			BUFFER_SIZE *= 2;
			s = (char*)realloc(s, sizeof(char) * BUFFER_SIZE);
		}

		if (c == '\n' || c == '\t' || c == ' ') {
			if (len != 0) {
				s[len] = '\0'; // добавляем нулевой символ в конец
				//cout << s << ": ";
				cout << is_correct(s, len) << endl;
				len = 0;
			}
		} else {
			//cout << "h" << c;
			s[len] = c;
			len++;
		}
	}

	if (len != 0) {
		s[len] = '\0';
		cout << is_correct(s, len) << endl;

	}

	free(s);
}