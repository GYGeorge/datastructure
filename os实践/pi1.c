#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#define NUMBER 1000000

double workeroutput = 0.0;
void *worker(void *arg)
{
    double* a = arg;
    int i;
    for (i = 0; i < (NUMBER / 2); i++) {
        workeroutput += a[i];
    }                           //for
}
double masteroutput = 0.0;
void *master(void *arg)
{
    double* a = arg;
    int i;
    for (i = (NUMBER / 2) ; i < NUMBER; i++) {
        masteroutput += a[i];
    }                           //for
}
int main()
{
    double num[NUMBER];
    int i;
    double j = 1.0;
    for (i = 0; i < NUMBER; i++, j = -j) {
        num[i] = j / (2.0 * i + 1.0);
    }
        
    pthread_t tid;
    pthread_create(&tid, NULL, &worker, num);
    master(num);
    pthread_join(tid, NULL);
    double sum = 4.0 * (masteroutput + workeroutput);
    printf("%f \n", sum);
}
