#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <chrono>
#include <assert.h>

using namespace std;

double len_seg = 0;

double f(double x) {
    return 4.0 / (1 + x * x);
}

struct args {
    double start;
    double *on_res;
    int n_in_thr;
};

void *job(void *arg) {
    double res = 0;
    struct args *p = (struct args *) arg;
    double a = p->start;
    int n_thr = p->n_in_thr; 
    for (int i = 0; i < n_thr; ++i) {
        res += f(a) * len_seg;
        a += len_seg;
    }
    *(p->on_res) = res;

    return NULL;
}

int main(int argc, char ** argv) {
    auto start = chrono::high_resolution_clock::now();

    int n_seg = stoi(argv[1]);
    int n = stoi(argv[2]);

    pthread_t thrs[n];
    struct args arg[n];

    int n_seg_for_thr = n_seg / n;
    len_seg = 1.0 / n_seg;
    double len = len_seg * n_seg_for_thr;

    double res[n];

    for (int i = 0; i < n - 1; ++i) {
        arg[i].start = i * len;
        arg[i].on_res = &res[i];
        arg[i].n_in_thr = n_seg_for_thr;
        assert(pthread_create(thrs + i, NULL, &job, arg + i) == 0);
    }

    arg[n - 1].start = (n - 1) * len;
    arg[n - 1].on_res = &res[n - 1];
    arg[n - 1].n_in_thr = n_seg_for_thr + n_seg % n;
    assert(pthread_create(thrs + n - 1, NULL, &job, arg + n - 1) == 0);


    double pi = 0;
    for (int i = 0; i < n; ++i) {
        assert(pthread_join(thrs[i], NULL) == 0);
        pi += res[i];
    }

    printf("%f\n", pi);


    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Elapsed time: " << duration.count() << " s" << endl;

    return 0;
}