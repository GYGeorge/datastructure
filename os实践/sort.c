#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define WORDCOUNT 10
#define CPU 2
#define CHILD (WORDCOUNT / CPU)
typedef struct {
    int *array;
    int start;
    int end;
} param;

void *worker(void *arg)
{
    int j, t;
    param *p;
    p = (struct param *) arg;
    // int *array = p->array;
    int n = p->end;
    int i = p->start;
    int min;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (p->array[j] < p->array[min]) {
                min = j;
            }                   //if
        }                       //for
        if (min != i) {
            t = p->array[min];
            p->array[min] = p->array[i];
            p->array[i] = t;
        }                       //if
    }                           //for
}

void merge(int *ar1, int *ar2, int *res)
{
    int i = 0, j = WORDCOUNT / 2, k = 0;
    while (i < (WORDCOUNT / 2) && j < WORDCOUNT) {
        if (ar1[i] <= ar2[j]) {
            res[k] = ar1[i];
            i++;
        } else {
            res[k] = ar2[j];
            j++;
        }
        k++;
    }
    while (i < (WORDCOUNT / 2))
        res[k++] = ar1[i++];
    while (j < WORDCOUNT )
        res[k++] = ar2[j++];

}

int main()
{
    int arr[WORDCOUNT] = { 19, 15, 12, 17, 18, 6, 8, 2, 1, 3 };
    pthread_t p[CPU];
    int i;
    param par[CPU];
    for (i = 0; i < CPU; i++) {
        param *_p;
        _p = &par[i];
        _p->array = arr;
        _p->start = i * CHILD;
        _p->end = (i + 1) * CHILD;
        
        pthread_create(&p[i], NULL, worker, _p);
    }
    pthread_join(p[0], NULL);
    pthread_join(p[1], NULL);
    int res[10];
    merge(par[0].array, par[1].array, res);

    for (i = 0; i < WORDCOUNT; i++)
        printf("%d,", res[i]);

}
