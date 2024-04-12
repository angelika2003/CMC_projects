#include <cstdio>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <list>
#include <cassert>


using namespace std;

class our_string{
    string s;
public:
    our_string(const string &str){
        s = str;
    }

    ~our_string(){
        cout << s << endl;
    }

};

void f(){
    try{
        string str;
        if (cin >> str){
            our_string s = our_string(str);
            f();
            throw 1;
        }
    } catch (...){}

}

int main(){
    f();
}