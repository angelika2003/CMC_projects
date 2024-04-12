#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <papi.h>

void handle_error(int retval, const char* str) {
	if (retval != PAPI_OK) {
		fprintf(stderr, "%s: PAPI error %d: %s\n", str, retval, PAPI_strerror(retval));
		exit(1);
	}
}

int main(int argc, char** argv)
{
    if (argc != 5)
    {
        printf("Not enough command line arguments provided.");
        return 1;
    }

    int n, i, j, k;
    int type = atoi(argv[4]);

    int event_set = PAPI_NULL, retval;
    long long values[2];

    FILE *a, *b, *c;
    int32_t **matrixA, **matrixB, **matrixC;

    retval = PAPI_library_init(PAPI_VER_CURRENT);
    if (retval != PAPI_VER_CURRENT) 
    {
        fprintf(stderr, "PAPI_libraty_init error!\n");
	exit(1);
    }

    a = fopen(argv[1], "rb");
    fread(&n, sizeof(int32_t), 1, a);
    matrixA = (int32_t**)malloc(n*sizeof(int32_t*));
    for (i = 0; i < n; i++)
    {
        *(matrixA + i) = (int32_t*)malloc(n*sizeof(int32_t));
    }
    for (i = 0; i < n; i++)
    {
        fread(*(matrixA + i), sizeof(int32_t), n, a);
    }
    fclose(a);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (matrixA[i][j] > 100 || matrixA[i][j] < -100)
            {
                printf("Number is out of range.");
                return 1;
            }
        }
    }

    b = fopen(argv[2], "rb");
    fread(&n, sizeof(int32_t), 1, b);
    matrixB = (int32_t**)malloc(n*sizeof(int32_t*));
    for (i = 0; i < n; i++)
    {
        *(matrixB + i) = (int32_t*)malloc(n*sizeof(int32_t));
    }
    for (i = 0; i < n; i++)
    {
        fread(*(matrixB + i), sizeof(int32_t), n, b);
    }
    fclose(b);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (matrixB[i][j] > 100 || matrixB[i][j] < -100)
            {
                printf("Number is out of range.");
                return 1;
            }
        }
    }

    c = fopen(argv[3], "wb");
    matrixC = (int32_t**)malloc(n*sizeof(int32_t*));
    for (i = 0; i < n; i++)
    {
        *(matrixC + i) = (int32_t*)malloc(n*sizeof(int32_t));
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            matrixC[i][j] = 0;
        }
    }
    fclose(c);

    handle_error(PAPI_create_eventset(&event_set), "create eventset");

    handle_error(PAPI_add_event(event_set, PAPI_L1_DCM), "add PAPI_L1_DCM");
    handle_error(PAPI_add_event(event_set, PAPI_L2_DCM), "add PAPI_L2_DCM");

    handle_error(PAPI_start(event_set), "papi start");

    clock_t start, end;
    double time = 0;

    if (type == 0)
    {
        start = clock();
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                for (k = 0; k < n; k++)
                {
                    matrixC[i][j] += matrixA[i][k]*matrixB[k][j];
                }
            }
        }
    }
    else if (type == 1)
    {
        start = clock();
        for (i = 0; i < n; i++)
        {
            for (k = 0; k < n; k++)
            {
                for (j = 0; j < n; j++)
                {
                    matrixC[i][j] += matrixA[i][k]*matrixB[k][j];
                }
            }
        }
    }
    else if (type == 2)
    {
        start = clock();
        for (k = 0; k < n; k++)
        {
            for (i = 0; i < n; i++)
            {
                for (j = 0; j < n; j++)
                {
                    matrixC[i][j] += matrixA[i][k]*matrixB[k][j];
                }
            }
        }
    }
    else if (type == 3)
    {
        start = clock();
        for (j = 0; j < n; j++)
        {
            for (i = 0; i < n; i++)
            {
                for (k = 0; k < n; k++)
                {
                    matrixC[i][j] += matrixA[i][k]*matrixB[k][j];
                }
            }
        }
    }
    else if (type == 4)
    {
        start = clock();
        for (j = 0; j < n; j++)
        {
            for (k = 0; k < n; k++)
            {
                for (i = 0; i < n; i++)
                {
                    matrixC[i][j] += matrixA[i][k]*matrixB[k][j];
                }
            }
        }
    }
    else if (type == 5)
    {
        start = clock();
        for (k = 0; k < n; k++)
        {
            for (j = 0; j < n; j++)
            {
                for (i = 0; i < n; i++)
                {
                    matrixC[i][j] += matrixA[i][k]*matrixB[k][j];
                }
            }
        }
    }
    else
    {
        return 1;
    }
    end = clock();
    time = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Elapsed time = %lf s\n", time);

 /*   for (i = 0; i < n; i++)
 *       {
 *               for (j = 0; j < n; j++)
 *                       {
 *                                   printf("%d ", matrixC[i][j]);
 *                                           }
 *                                                   printf("\n");
 *                                                       }   */
    
    handle_error(PAPI_stop(event_set, values), "papi stop");
    printf("PAPI_L1_DCM = %lld\n" "PAPI_L2_DCM = %lld\n", values[0], values[1]);

    c = fopen(argv[3], "wb");
    fwrite(&n, sizeof(int32_t), 1, c);
    for (i = 0; i < n; i++)
    {
        fwrite(*(matrixC + i), sizeof(int32_t), n, c);
    }
    fclose(c);

    for (i = 0; i < n; i++)
    {
        free(matrixA[i]);
        free(matrixB[i]);
        free(matrixC[i]);
    }

    free(matrixA);
    free(matrixB);
    free(matrixC);

    return 0;
    
}
