#include <iostream>
#include <iomanip>

#include <algorithm>
#include <map>
#include <string>
#include <cstring>
#include <set>

#include <iomanip>
#include <iostream>
#include <cstdio>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <set>
#include <functional>


using std::string;
using std::vector;
using std::map;
using std::function;
namespace numbers {
bool is_operation(string x) {
    if ((x == "+") || (x == "-") || (x == "*") || (x == "/") || (x == "!") || (x == ";") || (x == "~") || (x == "#")) {
        return true;
    }
    return false;
}

bool is_z(string x) {
    if (x == "z") {
        return true;
    }
    return false;
}

complex eval(const vector<string> &args, const complex &z) {
    complex_stack stack;
    map<string, function<complex_stack(complex_stack& stack)>> operations;

    operations["+"] = [](complex_stack & stack) {
        complex num_1 = +stack;
        stack = ~stack;
        complex num_2 = +stack;
        stack = ~stack;
        num_2 += num_1;

        stack = stack << num_2;
        return stack;
    };

    operations["-"] = [](complex_stack & stack) {
        complex num_1 = +stack;
        stack = ~stack;
        complex num_2 = +stack;
        stack = ~stack;
        num_2 -= num_1;

        stack = stack << num_2;
        return stack;
    };

    operations["*"] = [](complex_stack & stack) {
        complex num_1 = +stack;
        stack = ~stack;
        complex num_2 = +stack;
        stack = ~stack;
        num_2 *= num_1;

        stack = stack << num_2;
        return stack;
    };

    operations["/"] = [](complex_stack & stack) {
        complex num_1 = +stack;
        stack = ~stack;
        complex num_2 = +stack;
        stack = ~stack;
        num_2 /= num_1;

        stack = stack << num_2;
        return stack;
    };

    operations["!"] = [](complex_stack & stack) {
        complex tmp = +stack;
        stack = stack << tmp;
        return stack;
    };

    operations[";"] = [](complex_stack & stack) {
        stack = ~stack;
        return stack;
    };
    operations["~"] = [](complex_stack & stack) {
        complex tmp = +stack;
        stack = ~stack;
        tmp = ~tmp;
        stack = stack << tmp;
        return stack;
    };
    operations["#"] = [](complex_stack & stack) {
        complex tmp = +stack;
        stack = ~stack;
        tmp = -tmp;
        stack = stack << tmp;
        return stack;
    };

    for (size_t i = 0; i < args.size(); i++) {
        if (is_operation(args[i])) {
            stack = operations[args[i]](stack);//operations[args[i]]как раз нужная функция, применяем к stack
        } else if (is_z(args[i])) {
            stack = stack << z; //просто тоже добавим его в стек
        } else {
            complex num(args[i]);
            stack = stack << num;
        }
    }

    return +stack;
}
}
