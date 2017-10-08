extern int testval;

typedef enum {
    false,
    true
} bool;

extern bool testproc();

extern bool supports_rdrand();

extern int rdrand();

void mtrand_init();
int mtrand();

int rand_between(int x, int y);
