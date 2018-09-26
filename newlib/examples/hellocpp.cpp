#include <stdio.h>
#include <vector>
#include <string>

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

    std::string str = "str";
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    return 0;
}