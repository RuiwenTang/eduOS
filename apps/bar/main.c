#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int add(int a, int b);
int main(int argc, const char** argv) {
    printf("hello from bar\n");
    int ret = add(1, 2);
    printf("math ret = %d\n", ret);
    pid_t pid = getpid();

    
    printf("pid = %d\n", pid);
    return 0;
}