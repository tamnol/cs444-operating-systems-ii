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

    printf("random integers between 2 and 9 are");
    for (i=0; i<100; ++i)
        printf(" %d", rand_between(2,9));
    printf("\n");

    return 0;
}
