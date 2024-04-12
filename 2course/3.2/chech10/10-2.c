#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <sys/mman.h>

enum 
{ 
    MUILTIPLICATOR = 1103515245, 
    INCREMENT = 12345, 
    MOD = 1 << 31 
};



typedef struct RandomGenerator 
{
    unsigned int xn;
    const struct RandomOperations* ops;
} RandomGenerator;


//struct RandomOperations: destroy|next,  с нашими функциями
typedef struct RandomOperations 
{
    void(*destroy)(RandomGenerator* rr);
    int(*next)(RandomGenerator* rr);
} RandomOperations;


//destroy & next:
void destroy(RandomGenerator* rr) {
    if (rr == NULL){
        return;
    }

    free(rr);
    return;
}

int next(RandomGenerator* rr) {
    if (rr == NULL){
        return 0;
    }

    rr->xn = (MUILTIPLICATOR * rr->xn + INCREMENT) % MOD;

    return rr->xn;
}


static RandomOperations operations = {destroy, next};
//функция возвр заполненную структуру RandomGenerator, с которой можно работать
RandomGenerator *random_create(int seed) {
    RandomGenerator* rr = (RandomGenerator*) calloc (1, sizeof(*rr));

    if (rr == NULL){
        return NULL;
    }

    rr->xn = seed;
    rr->ops = &operations;

    return rr;
}