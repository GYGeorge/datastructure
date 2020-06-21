#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#define NR_TOTAL 100
#define NR_CPU 2
#define NR_CHILD (NR_TOTAL / NR_CPU)
#define NUMBER 100

typedef struct {
    double *array;
    int start;
    int end;
} param;

typedef struct {
    double sum;
} result;

void *compute(void *arg)
{
    param *param;
    result *result;
    double sum = 0.0;
    int i;

    param = (struct param *) arg;
    for (i = param->start; i < param->end; i++)
        sum += param->array[i];

    result = malloc(sizeof(result));
    result->sum = sum;
    return result;
}

int main()
{
    pthread_t worker[NR_CPU];
    param p[NR_CPU];
    int i;
    double array[NUMBER];
    double j = 1.0;
    for (i = 0; i < NUMBER; i++, j = -j) {
        array[i] = j / (2.0 * i + 1.0);
    }
    for (i = 0; i < NR_CPU; i++) {
        param *_p;
        _p = &p[i];
        _p->array = array;
        _p->start = i * NR_CHILD;
        _p->end = (i + 1) * NR_CHILD;
        pthread_create(&worker[i], NULL, compute, _p);
    }
    double sum = 0.0;
    for (i = 0; i < NR_CPU; i++) {
        result *res;
        pthread_join(worker[i], (void **) &res);
        sum += res->sum;
        free(res);
    }
    sum *= 4;
    printf("sum = %f\n", sum);
    return 0;


}
