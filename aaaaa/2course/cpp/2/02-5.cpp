#include <iostream>
#include <string>

using namespace std;

class BinaryNumber
{
    string number;
public:
    BinaryNumber(const string &s) {
        number = s;
    }
    operator string () const {
        return number;
    }

    const BinaryNumber &operator++() {
        string tmp = "0" + number;
        int index = tmp.length() - 1;

        while (tmp[index] != '0') {
            tmp[index] = '0';
            index--;
        }
        tmp[index] = '1';

        if (tmp[0] == '0') {
            number = tmp.substr(1);
        } else {
            number = tmp;
        }

        return *this;
    }
};
