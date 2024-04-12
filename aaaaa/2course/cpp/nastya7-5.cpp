#include <cassert>
#include <iostream>

class Figure {
   public:
    virtual bool equals(const Figure* f) const = 0;
    virtual ~Figure() {}
};

class Rectangle : public Figure {
    int a;
    int b;

   public:
    Rectangle(int x1, int x2) {
        a = x1;
        b = x2;
    }
    bool equals(const Figure* f) const {
        const Rectangle* tmp = dynamic_cast<const Rectangle*>(f);
        if ((tmp) && (tmp->a == a && tmp->b == b)) {
            return true;
        }
        return false;
    }
};

class Triangle : public Figure {
    int a;
    int b;
    int c;

   public:
    Triangle(int x1, int x2, int x3) {
        a = x1;
        b = x2;
        c = x3;
    }
    bool equals(const Figure* f) const {
        const Triangle* tmp = dynamic_cast<const Triangle*>(f);
        if ((tmp) && (tmp->a == a && tmp->b == b && tmp->c == c)) {
            return true;
        }
        return false;
    }
};