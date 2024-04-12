#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstring>

using namespace std;

class StringView {
	size_t len;
	size_t start;
	std::string *str_p;

public:
	StringView & operator=(const StringView & str_view) = delete;

	size_t get_start() const {
		return start;
	}

	size_t size() const {
		return len;
	}

	size_t length() const {
		return len;
	}

	StringView(string &s, size_t begin = 0, size_t count = string::npos) {
		str_p = &s;
		if (begin >= s.length()) {
			len = 0;
			start = 0;
			return;
		}

		start = begin;

		if (s.length() - start < count) {
			len = s.length() - start;
		} else {
			len = count;
		}

	}

	StringView(const StringView &sv, size_t begin = 0, size_t count = string::npos) {
		str_p = sv.str_p;
		if (begin >= sv.len) {
			len = 0;
			start = 0;
			return;
		}
		start = begin + sv.start;

		if (sv.len - begin < count) {
			len = sv.len - begin;
		} else {
			len = count;
		}

	}


	char & operator[](int i) const {
		return (*str_p)[start + i];
	}

	std::string str(size_t begin = 0, size_t count = std::string::npos) const {
		if (begin >= length()) {
			return "";
		}
		if (count == std::string::npos || count > length() - begin) {
			count = length() - begin;
		}
		return str_p->std::string::substr(start + begin, count);
	}

	using iterator = typename string::iterator;
	iterator begin() { return (*str_p).begin(); }
	iterator end() { return (*str_p).end(); }
	using const_iterator = typename string::const_iterator;
	const_iterator cbegin() const { return (*str_p).begin(); }
	const_iterator cend() const { return (*str_p).end(); }
	using reverse_iterator = typename string::reverse_iterator;
	reverse_iterator rbegin() { return (*str_p).rbegin(); }
	reverse_iterator rend() { return (*str_p).rend(); }
	using const_reverse_iterator = typename string::const_reverse_iterator;
	const_reverse_iterator crbegin() { return (*str_p).crbegin(); }
	const_reverse_iterator crend() { return (*str_p).crend(); }

	bool operator==(const StringView & other) const {
		return this->str() == other.str();
	}
	bool operator!=(const StringView & other) const {
		return !(*this == other);
	}
	bool operator<(const StringView & other) const {
		return this->str() < other.str();
	}
	bool operator<=(const StringView & other) const {
		return (*this < other) || (*this == other);
	}
	bool operator>(const StringView & other) const {
		return !(*this <= other);
	}
	bool operator>=(const StringView & other) const {
		return !(*this < other);
	}

	char & at (size_t i) {
		if (i >= this->len) {
			throw std::out_of_range("");
		}

		return (*str_p)[start + i];
	}

	const char & at (size_t i) const {
		if (i >= this->len) {
			throw std::out_of_range("");
		}
		return (*str_p)[start + i];
	}

};










