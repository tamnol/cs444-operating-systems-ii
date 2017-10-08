#include <stdio.h>
#include "test.h"

int main(int argc, char **argv)
{
    int i;

    mtrand_init();

    printf("testval equals %d\n", testval);
    printf("testproc() equals %d\n", testproc());

    if (supports_rdrand() == true) {
        printf("supports rdrand\n");
        printf("random number is %d\n", rdrand());
    } else {
        printf("does not support rdrand\n");
        printf("pseudorandom number is %d\n", mtrand());
    }

    return 0;
}

void mtrand_init()
{
    int seed = time(NULL);
    init_genrand(seed);
}

int mtrand()
{
    return genrand_int32();
}
