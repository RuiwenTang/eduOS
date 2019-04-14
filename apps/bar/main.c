#include <stdlib.h>
#include <stdio.h>
int add(int a, int b);
int main(int argc, const char** argv) {
    printf("hello from bar\n");
    int ret = add(1, 2);
    printf("math ret = %d\n", ret);
    return 0;
}