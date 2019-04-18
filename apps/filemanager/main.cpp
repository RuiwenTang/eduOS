#include <stdio.h>
#include <string>
#include <boost/circular_buffer.hpp>

typedef boost::circular_buffer<int> circular_buffer;

class BaseClass {
public:
    virtual ~BaseClass() {}

    virtual void hello() = 0;
};


class SubClass: public BaseClass {
public:
    SubClass(): name("sub class") {}
    virtual ~SubClass() {}
    virtual void hello() override {
        printf("name = %s\n", this->name.c_str());
    }
private:
    std::string name;
};

int main(int argc, char const *argv[])
{
    
    circular_buffer cb{3};
    /* code */
    printf("1\n");
    cb.push_back(1);
    printf("cb.size = %d\n", cb.size());

    BaseClass* b = new SubClass();
    b->hello();
    delete b;

    return 0;
}
