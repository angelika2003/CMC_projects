#include <cstdio>
#include <cstring>
#include <iostream>

class String {
	int len;
	char *str;
public:
	String(int n = 1) { //конструктор 1
		str = new char[n];
		len = n;
		str[0] = '\0';
	}

	String(const char *s) { //конструктор 2
		len = strlen(s) + 1;
		str = new char[len];
		snprintf(str, len, "%s", s);
	}

	String (const String & s) { //конструктор копирования
		len = s.len;
		str = new char[len];
		snprintf(str, len, "%s", s.str);
	}

	~String() {
		delete []str;
	}


	void print() {
		std::cout<<str<< std::endl;
	}


	String& operator =(const String & s) {
		if (this == &s) {
			return *this;
		}

		delete str;
		str = new char[s.len];
		len = s.len;
		snprintf(str, len, "%s", s.str);

		return *this;
	}
};

/*
friend String operator +(const String &s1, const String &s2) {
	String tmp(s1.len + s2.len - 1);
	snprintf(tmp.str, tmp.len, "%s%s", s1.str, s2.str);

	return tmp;
}*/


int main() {
	String s1("abc"), s2("klmn"), s3;
	s3 = s1;

	s3.print();

	//s3 = s1 + s2;

	//s3.print();

	return 0;
}

