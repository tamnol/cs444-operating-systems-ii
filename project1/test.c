#include <stdio.h>
#include "test.h"

int main(int argc, char **argv)
{
    printf("testval equals %d\n", testval);
    printf("testproc() equals %d\n", testproc());

    if (supports_rdrand() == true)
        printf("supports rdrand\n");
    else
        printf("does not support rdrand\n");

    return 0;
}
