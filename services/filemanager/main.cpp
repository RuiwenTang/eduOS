#include <stdio.h>
#include <string>
#include <boost/circular_buffer.hpp>

typedef boost::circular_buffer<int> circular_buffer;

int main(int argc, char const *argv[])
{
    
    circular_buffer cb{3};
    /* code */
    return 0;
}
