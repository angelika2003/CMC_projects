#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>

namespace numbers {
    class complex_stack {
        complex *ptr; //указатель на массив комплексных
        size_t used; //используется
        size_t allocated; //кол-во под которых память выделена
    public:
        complex_stack(size_t u = 0, size_t a = 0) {
            used = u;
            allocated = a;
            ptr = static_cast<complex*>(::operator new(allocated * sizeof(complex)));
        }
        
        //конструктор копирования
        complex_stack(const complex_stack &v) {
            used = v.used;
            allocated = v.allocated;
            ptr = static_cast<complex*>(::operator new(allocated * sizeof(complex)));
            
            for (size_t i = 0; i < used; i++) {
                new(ptr + i) complex(v.ptr[i]);
            }
        }
        
        //деструктор
        ~complex_stack() {
            for (size_t i = 0; i < used; i++) {
                ptr[i].~complex(); //в цикле вызываем деструктор для каждого комплексного
            }
            
            used = 0;
            allocated = 0;
            
            ::operator delete(ptr);
        }
        
        size_t size() const {
            return used;
        }

        complex& operator[](size_t i) const {
            return ptr[i];
        }

        complex operator+() const {
            return ptr[used - 1];
        }
        
        complex_stack(complex_stack&& s) {
            allocated = s.allocated;
            ptr = s.ptr;
            used = s.used;
            s.ptr = nullptr;
        }
        
        friend complex_stack operator<<(const complex_stack stack, const complex num);
        
        complex_stack operator~() const {
            complex_stack new_stack(used - 1, allocated);
            
            for (size_t i = 0; i < used - 1; i++) {
                new (new_stack.ptr + i) complex(ptr[i]);
            }
            
            return new_stack;
        }
        
        complex_stack& operator=(const complex_stack& cure) {
            if (&cure == this) {
                return *this;
            }

            for (size_t i = 0; i < used; i++) {
                ptr[i].~complex();
            }
            
            ::operator delete(ptr);

            used = cure.used;
            allocated = cure.allocated;
            ptr = static_cast<complex*>(::operator new(allocated * sizeof(complex)));
            
            for (size_t i = 0; i < used; i++) {
                new (ptr + i) complex(cure.ptr[i]);
            }

            return *this;
        }
    };

    complex_stack operator<<(const complex_stack stack, const complex num) {
        size_t new_size = stack.allocated;
        
        if (stack.used == 0) {
            new_size++;
        }
        
        if (stack.used == stack.allocated) {
            new_size *= 3;
        }
        
        complex_stack new_stack(stack.used + 1, new_size);
        
        for (size_t i = 0; i < stack.used; i++) {
            new (new_stack.ptr + i) complex(stack[i]);
        }
        
        new (new_stack.ptr + stack.used) complex(num);
        
        return new_stack;
    }
};