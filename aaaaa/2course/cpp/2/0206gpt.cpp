#include <string>
#include <stdexcept>

class StringView {
public:
	StringView(std::string& s, size_t begin = 0, size_t count = std::string::npos) {
		if (begin >= s.size()) {
			m_begin = m_end = 0;
			return;
		}
		m_begin = begin;
		if (count == std::string::npos || count > s.size() - begin) {
			count = s.size() - begin;
		}
		m_end = m_begin + count;
		m_str = &s;
	}

	StringView(const StringView& sv, size_t begin = 0, size_t count = std::string::npos) {
		if (begin >= sv.size()) {
			m_begin = m_end = 0;
			return;
		}
		m_begin = sv.m_begin + begin;
		if (count == std::string::npos || count > sv.size() - begin) {
			count = sv.size() - begin;
		}
		m_end = m_begin + count;
		m_str = sv.m_str;
	}

	StringView& operator=(const StringView&) = delete;

	size_t length() const { return m_end - m_begin; }
	size_t size() const { return length(); }

	char operator[](size_t index) const {
		return (*m_str)[m_begin + index];
	}

	std::string str(size_t begin = 0, size_t count = std::string::npos) const {
		if (begin >= length()) {
			return "";
		}
		if (count == std::string::npos || count > length() - begin) {
			count = length() - begin;
		}
		return m_str->substr(m_begin + begin, count);
	}

	const char* data() const {
		return m_str->data() + m_begin;
	}

	const char* begin() const {
		return data();
	}

	const char* end() const {
		return data() + length();
	}

	bool operator==(const StringView& other) const {
		if (length() != other.length()) {
			return false;
		}
		for (size_t i = 0; i < length(); i++) {
			if ((*m_str)[m_begin + i] != (*other.m_str)[other.m_begin + i]) {
				return false;
			}
		}
		return true;
	}

	bool operator!=(const StringView& other) const {
		return !(*this == other);
	}

	bool operator<(const StringView& other) const {
		size_t i = 0;
		while (true) {
			if (i >= length() && i >= other.length()) {
				return false;
			}
			if (i >= length()) {
				return true;
			}
			if (i >= other.length()) {
				return false;
			}
			if ((*m_str)[m_begin + i] < (*other.m_str)[other.m_begin + i]) {
				return true;
			} else if ((*m_str)[m_begin + i] > (*other.m_str)[other.m_begin + i]) {
				return false;
			}
			i++;
		}
	}

	bool operator<=(const StringView& other) const {
		return (*this < other) || (*this == other);
	}

	bool operator>(const StringView& other) const {
		return !(*this <= other);
	}

	bool operator>=(const StringView& other) const {
		return !(*this < other);
	}
private:
	const std::string* m_str = nullptr;
	size_t m_begin = 0;
	size_t m_end = 0;
};