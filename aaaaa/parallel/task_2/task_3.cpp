#include <papi.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <chrono>
#include <assert.h>
#include <errno.h>
#include <sys/time.h>

using namespace std;

void
handle_error(int retval, const char *str)
{
    if (retval != PAPI_OK) {
        fprintf(stderr,
                "%s: PAPI error %d: %s\n",
                str, retval, PAPI_strerror(retval));
        exit(1);
    }
}

int main(int argc, char ** argv) {


    FILE * f_1 = fopen(argv[1], "rb+");
    FILE * f_2 = fopen(argv[2], "rb+");
    FILE * f_3 = fopen(argv[3], "wb+");

    char *eptr = NULL;
    int mode = strtol(argv[4], &eptr, 10);



    int32_t n;
    if (!fread(&n, sizeof(int32_t), 1, f_1)) {
        cout << "Error: fread() failed" << endl;
        return 1;
    }
    if (!fread(&n, sizeof(int32_t), 1, f_2)) {
        cout << "Error: fread() failed" << endl;
        return 1;
    }


    int32_t *A = (int32_t *)calloc(n * n, sizeof(*A));
    int32_t *B = (int32_t *)calloc(n * n, sizeof(*A));
    int32_t *C = (int32_t *)calloc(n * n, sizeof(*A));


    if (!fread(A, sizeof(int32_t), n * n, f_1)) {
        cout << "Error: fread() failed" << endl;
        return 1;
    }

    if (!fread(B, sizeof(int32_t), n * n, f_2)) {
        cout << "Error: fread() failed" << endl;
        return 1;
    }

    int i, j, k;


////////////////////////////////////////////////////

    int event_set = PAPI_NULL, retval;
    long long values[2];

    retval = PAPI_library_init(PAPI_VER_CURRENT);

    if (retval != PAPI_VER_CURRENT) {
        fprintf(stderr, "PAPI library init error!\n");
        exit(1);
    }

    handle_error(PAPI_create_eventset(&event_set), "create eventset");

    handle_error(PAPI_add_event(event_set, PAPI_L1_DCM), "add PAPI_L1_DCM");
    handle_error(PAPI_add_event(event_set, PAPI_L2_DCM), "add PAPI_L2_DCM");


    handle_error(PAPI_start(event_set), "papi start");



    if (mode == 0) {

        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                int32_t sum = 0;
                for (k = 0; k < n; ++k) {
                    sum += A[i * n + k] * B[k * n + j];
                }
                C[i * n + j] = sum;
            }
        }

    } else if (mode == 1) {
        for (i = 0; i < n; ++i) {
            for (k = 0; k < n; ++k) {
                for (j = 0; j < n; ++j) {
                    C[i * n + j] += A[i * n + k]* B[k * n + j];
                }
            }
        }

    } else if (mode == 2) {
        for (k = 0; k < n; ++k) {
            for (i = 0; i < n; ++i) {
                for (j = 0; j < n; ++j) {
                    C[i * n + j] += A[i * n + k] * B[k * n + j];
                }
            }
        }

    } else if (mode == 3) {
        for (j = 0; j < n; ++j) {
            for (i = 0; i < n; ++i) {
                int32_t sum = 0;
                for (k = 0; k < n; ++k) {
                    sum += A[i * n + k] * B[k * n + j];
                }
                C[i * n + j] = sum;
            }
        }

    } else if (mode == 4) {
        for (j = 0; j < n; ++j) {
            for (k = 0; k < n; ++k) {
                for (i = 0; i < n; ++i) {
                    C[i * n + j] += A[i * n + k] * B[k * n + j];
                }
            }
        }

    } else {
        for (k = 0; k < n; ++k) {
            for (j = 0; j < n; ++j) {
                for (i = 0; i < n; ++i) {
                    C[i * n + j] += A[i * n + k] * B[k * n + j];
                }
            }
        }

    }

    handle_error(PAPI_stop(event_set, values), "papi stop");

    printf("PAPI_L1_DCM = %lld\n"
           "PAPI_L2_DCM = %lld\n",
           values[0],
           values[1]);

    fwrite(&n, sizeof(int32_t), 1, f_3);
    fwrite(C, sizeof(int32_t), n * n, f_3);

    free(A);
    free(B);
    free(C);

    return 0;
}