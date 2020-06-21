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
typedef struct {
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} sema_t;
void sema_init(sema_t * sema, int value)
{
    sema->value = value;
    pthread_mutex_init(&sema->mutex, NULL);
    pthread_cond_init(&sema->cond, NULL);
}

void sema_wait(sema_t * sema)
{
    pthread_mutex_lock(&sema->mutex);
    while (sema->value <= 0)
        pthread_cond_wait(&sema->cond, &sema->mutex);
    sema->value--;
    pthread_mutex_unlock(&sema->mutex);
}

void sema_signal(sema_t * sema)
{
    pthread_mutex_lock(&sema->mutex);
    ++sema->value;
    pthread_cond_signal(&sema->cond);
    pthread_mutex_unlock(&sema->mutex);
}

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

sema_t sema_mutex1, sema_mutex2;
sema_t emptybuffer1, emptybuffer2;
sema_t fullbuffer1, fullbuffer2;

void *compute(void *arg)
{
    int i;
    int item;

    for (i = 0; i < ITEM_COUNT; i++) {
        sema_wait(&fullbuffer1);
        sema_wait(&sema_mutex1);
        item = get1();
        item += 'A' - 'a';
        printf("    compute item: %c\n", item);
        sema_signal(&sema_mutex1);
        sema_signal(&emptybuffer1);

        sema_wait(&emptybuffer2);
        sema_wait(&sema_mutex2);
        put2(item);
        sema_signal(&sema_mutex2);
        sema_signal(&fullbuffer2);
    }

}

void *consume(void *arg)
{
    int i;
    int item;

    for (i = 0; i < ITEM_COUNT; i++) {
        sema_wait(&fullbuffer2);
        sema_wait(&sema_mutex2);

        item = get2();
        printf("    consume item: %c\n", item);

        sema_signal(&sema_mutex2);
        sema_signal(&emptybuffer2);
    }
}

void *produce(void *arg)
{
    int i;
    int item;

    for (i = 0; i < ITEM_COUNT; i++) {
        sema_wait(&emptybuffer1);
        sema_wait(&sema_mutex1);

        item = i + 'a';
        put1(item);
        printf("produce item: %c\n", item);

        sema_signal(&sema_mutex1);
        sema_signal(&fullbuffer1);
    }

}

int main()
{
    pthread_t tid[2];
    sema_init(&sema_mutex1, 1);
    sema_init(&sema_mutex2, 1);
    sema_init(&emptybuffer1, CAPACITY - 1);
    sema_init(&emptybuffer2, CAPACITY - 1);
    sema_init(&fullbuffer1, 0);
    sema_init(&fullbuffer2, 0);

    pthread_create(&tid[0], NULL, consume, NULL);
    pthread_create(&tid[1], NULL, compute, NULL);
    produce(NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    return 0;

}
