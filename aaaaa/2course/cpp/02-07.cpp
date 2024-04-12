#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Matrix {
    vector<vector<int>> a;
public:
    Matrix() {
        vector<vector<int>> ans(3);
        for (int i = 0; i < 3; i++) {
            vector<int> tmp(3);
            ans[i] = tmp;
        }
        a = ans;
    }
    int &operator[](int i, int j) {
        return a[i][j];
    }
    vector<vector<int>>::iterator begin() {
        return a.begin();
    }

    vector<vector<int>>::iterator end() {
        return a.end();
    }
};