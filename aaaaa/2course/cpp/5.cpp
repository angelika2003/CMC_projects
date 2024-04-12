#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    uint32_t bytes[4];
    int skip;
    uint32_t num;

    if(!(cin >> hex >> skip)){
        return 0;
    }
    int cnt = 0;

    while ((cin >> hex >> bytes[0]) && (cin >> hex >> bytes[1]) &&
            (cin >> hex >> bytes[2]) && (cin >> hex >> bytes[3])) {

        cnt += 4;

        num = 0;
        num |= bytes[0];
        num <<= 8;
        num |= bytes[1];
        num <<= 8;
        num |= bytes[2];
        num <<= 8;
        num |= bytes[3];
        cout << num << endl;

        if (cnt % 16 == 0) {
            cnt = 0;
            cin >> hex >> skip;
        }
    }

    return 0;
}