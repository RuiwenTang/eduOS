#include <eduos/syscall.h>

#include <stdio.h>


int main(int argc, char** argv) {

    char* p = (char*)0x1000000;
    *p = '0';
    printf("Demo Service start11\n");

    return 1;
}