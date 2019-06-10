
#include <boost/pool/object_pool.hpp>
#include <iostream>
#include <string>

class Demo {
public:
    Demo() = default;
    std::string name;
};

extern "C" int get_num();
extern "C" void* run(void*) { return nullptr; }

int main(int argc, const char** argv) {
    boost::object_pool<Demo> oPool;
    Demo* d1 = oPool.malloc();
    std::cout << d1->name << std::endl;
    std::cout << "Hello World : " << get_num() << std::endl;
    return 0;
}