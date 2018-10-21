#include <stdio.h>
#include <vector>
#include <string>
#include <boost/circular_buffer.hpp>

class BaseClass {
public:
    BaseClass() {
        printf("base create\n");
    }
    virtual ~BaseClass() {
        printf("base destroy\n");
    }

    virtual void hello() {
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

    void hello() override {

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
    int a = 1;
    uint16_t b = static_cast<uint16_t>(a);
    typedef boost::circular_buffer<int> circular_buffer;
    circular_buffer cb{3};
    cb.push_back(0);
    cb.push_back(1);
    cb.push_back(2);
    printf("size of cb = %d\n", cb.size());
    cb.push_back(3);
    cb.push_back(4);
    cb.push_back(5);
    printf("size of cb = %d\n", cb.size());
    FILE* f = fopen("/data/boot1", "rw");
    return 0;
}