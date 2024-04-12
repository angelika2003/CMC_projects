#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>

namespace numbers {
class complex_stack {
    complex *ptr; //указатель на массив комплексных
    size_t used; //используется
    size_t alloc; //кол-во под которых память выделена
public:
    complex_stack(size_t u = 0, size_t a = 0) {
        used = u;
        alloc = a;
        ptr = static_cast<complex*>(::operator new(alloc * sizeof(complex)));
    }

    complex_stack(const complex_stack &v) {
        used = v.used;
        alloc = v.alloc;
        ptr = static_cast<complex*>(::operator new(alloc * sizeof(complex)));

        for (size_t i = 0; i < used; i++) {
            new(ptr + i)complex(v.ptr[i]);
        }
    }

    complex_stack(complex_stack&& v) {
        used = v.used;
        alloc = v.alloc;
        ptr = v.ptr;
        v.ptr = nullptr;
    }

    ~complex_stack() {
        for (size_t i = 0; i < used; i++) {
            ptr[i].~complex();
        }

        ::operator delete(ptr);
        used = 0;
        alloc = 0;
    }

    complex_stack& operator=(const complex_stack& x) {
        if (&x == this) {
            return *this;
        }

        for (size_t i = 0; i < used; i++) {
            ptr[i].~complex();
        }
        ::operator delete(ptr);

        used = x.used;
        alloc = x.alloc;

        ptr = static_cast<complex*>(::operator new(alloc * sizeof(complex)));
        for (size_t i = 0; i < used; i++) {
            new (ptr + i) complex(x.ptr[i]);
        }

        return *this;
    }

    size_t size() const {
        return used;
    }
    complex& operator [](size_t i) const {
        return ptr[i];
    }
    complex& operator +() const {
        return ptr[used - 1];
    }


    friend complex_stack operator << (const complex_stack v, const complex num);

    complex_stack operator ~() const {
        complex_stack ans(used - 1, alloc);
        for (size_t i = 0; i < used - 1; i++) {
            new(ans.ptr + i)complex(ptr[i]);
        }

        return ans;
    }
};

complex_stack operator << (const complex_stack v, const complex num) {
    size_t new_alloc = v.alloc;

    if (v.alloc == v.used) {
        new_alloc++;
        new_alloc *= 2;
    }

    complex_stack ans(v.used + 1, new_alloc);

    for (size_t i = 0; i < v.used; i++) {
        new (ans.ptr + i) complex(v[i]);
    }
    new (ans.ptr + v.used) complex(num);

    return ans;
}
}

