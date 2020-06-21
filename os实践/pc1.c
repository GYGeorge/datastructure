#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#define CAPACITY 4
#define ITEM_COUNT (CAPACITY * 2)
#define ITEM_TYPE char
int buffer1[CAPACITY];
int buffer2[CAPACITY];
int in1;
int out1;
int in2;
int out2;
#define buffer1_is_empty  (in1 == out1)
#define buffer1_is_full ((in1 + 1) % CAPACITY == out1)
#define buffer2_is_empty  (in2 == out2)
#define buffer2_is_full  ((in2 + 1) % CAPACITY == out2)
int get1()
{   
    ITEM_TYPE item;
    item = buffer1[out1];
    out1 = (out1 + 1) % CAPACITY;
    return item;
}
int get2()
{   
    ITEM_TYPE item;
    item = buffer2[out2];
    out2 = (out2 + 1) % CAPACITY;
    return item;
}
void put1(ITEM_TYPE item)
{
    buffer1[in1] = item;
    in1 = (in1 + 1) % CAPACITY;
}
void put2(ITEM_TYPE item)
{
    buffer2[in2] = item;
    in2 = (in2 + 1) % CAPACITY;
}
pthread_mutex_t mutex, mutex2;
pthread_cond_t wait_empty1, wait_full1, wait_empty2, wait_full2;

void *consume(void* arg)
{
    int i;
    ITEM_TYPE item;
    for (i = 0; i < ITEM_COUNT; i++) {
        pthread_mutex_lock(&mutex2);
        while (buffer2_is_empty)
            pthread_cond_wait(&wait_full2, &mutex2);
        item = get2();
        printf("        consume out2 = %d,item = %c\n", out2, item);
        pthread_cond_signal(&wait_empty2);
        pthread_mutex_unlock(&mutex2);
    }//for
    return NULL;
}

void *compute(void* arg)
{   
    int i;
    ITEM_TYPE item;
    for ( i = 0; i < ITEM_COUNT; i++) {
        pthread_mutex_lock(&mutex);
        while (buffer1_is_empty)
            pthread_cond_wait(&wait_full1, &mutex);
        printf("    compute out1 %d\n", out1);
        item = get1(); 
        item += 'A' - 'a';
        pthread_cond_signal(&wait_empty1);
        pthread_mutex_unlock(&mutex);
        
        pthread_mutex_lock(&mutex2);
        while (buffer2_is_full)
            pthread_cond_wait(&wait_empty2, &mutex2);
        printf("    compute in2 %d\n", in2);
        put2(item);
        pthread_cond_signal(&wait_full2);
        pthread_mutex_unlock(&mutex2);
    }
}

void *produce(void* arg)
{
    int i;
    ITEM_TYPE item;
    for ( i = 0; i < ITEM_COUNT; i++) {
        pthread_mutex_lock(&mutex);
        while (buffer1_is_full)
            pthread_cond_wait(&wait_empty1, &mutex);
        item = 'a' + i;
        printf("produce: in1 = %d\n", in1);
        put1(item);
        
        pthread_cond_signal(&wait_full1); 
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t tid[2];
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutex2, NULL);
    pthread_cond_init(&wait_empty1, NULL);
    pthread_cond_init(&wait_full1, NULL);
    pthread_cond_init(&wait_empty2, NULL);
    pthread_cond_init(&wait_full2, NULL);

    pthread_create(&tid[0], NULL, consume, NULL);
    pthread_create(&tid[1], NULL, compute, NULL);
    
    produce(NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutex2);
    return 0;
}