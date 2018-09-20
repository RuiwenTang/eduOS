#include <stdio.h>

class BaseClass {
public:
    BaseClass() {
        printf("base create\n");
    }
    virtual ~BaseClass() {
        printf("base destroy\n");
    }
};


class SubClass: public BaseClass {
public:
    SubClass() {
        printf("Sub create\n");
    }
    virtual ~SubClass() {
        printf("Sub destroy\n");
    }
};


int main(int argc, char const** argv) {

    // printf("Hello World CPP!!!!\n");
    BaseClass* p = new SubClass();
    delete p;

    return 0;
}