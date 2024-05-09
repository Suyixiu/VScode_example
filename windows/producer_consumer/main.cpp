// #include <stdio.h>
// #include <pthread.h>
// #include <semaphore.h>

// sem_t empty, full;     // 定义全局同步信号量empty，full
// pthread_mutex_t mutex; // 定义一个全局互斥量，在不同函数中
// int buffer_count = 0;  // 定义一个全局变量，表示管道内得产品数目

// void *producer(void *arg); // 生产者线程
// void *consumer(void *arg); // 消费者线程

// int main(int argc, char *argv[])
// {
//     pthread_t thrd_prod, thrd_cons;

//     pthread_mutex_init(&mutex, NULL); // 初始化互斥量
//     sem_init(&empty, 0, 5);           // 初始化empty信号量
//     sem_init(&full, 0, 0);            // 初始化full信号量
//     // 创建生产者和消费者线程
//     if (pthread_create(&thrd_prod, NULL, producer,
//                        NULL) != 0)
//         printf("thread create failed.");

//     if (pthread_create(&thrd_cons, NULL, consumer,
//                        NULL) != 0)
//         printf("thread create failed.");

//     // 等待线程结束
//     if (pthread_join(thrd_prod, NULL) != 0)
//         printf(" wait thread failed.");
//     if (pthread_join(thrd_cons, NULL) != 0)
//         printf(" wait thread failed.");
//     sem_destroy(&full);            // 释放同步量
//     sem_destroy(&empty);           // 释放同步量
//     pthread_mutex_destroy(&mutex); // 关闭互斥量

//     system("pause");

//     return 0;
// }

// void *producer(void *arg)
// {
//     while (1)
//     {
//         sem_wait(&empty);           // empty-1
//         pthread_mutex_lock(&mutex); // 加锁
//         // 成功占有互斥量，接下来可以对缓冲区（仓库）进行生产
//         // 操作
//         printf(" producer put a product to buffer.");
//         buffer_count++;
//         printf("the buffer_count is %d\n", buffer_count);
//         pthread_mutex_unlock(&mutex); // 解锁
//         sem_post(&full);              // full+1
//     }
// }
// void *consumer(void *arg)
// {
//     while (1)
//     {
//         sem_wait(&full);            // full-1
//         pthread_mutex_lock(&mutex); // 加锁
//         // 成功占有互斥量，接下来可以对缓冲区（仓库）进行取出
//         // 操作
//         printf(" consumer get a product from buffer.");
//         buffer_count--;
//         printf("the buffer_count is %d\n", buffer_count);
//         pthread_mutex_unlock(&mutex); // 解锁
//         sem_post(&empty);             // empty-1
//     }
// }

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define BUFFER_SIZE 10
#define LOOP_COUNT  30

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t mutex;
sem_t full;
sem_t empty;

void *producer(void *arg)
{
    int item = 0;
    for (int i = 0; i < LOOP_COUNT; i++)
    {
        sleep(1);

        item++;           // 生成随机数作为生产的物品
        sem_wait(&empty); // 等待缓冲区非空
        sem_wait(&mutex); // 获取互斥锁
        buffer[in] = item;
        printf("Produced: %d, index: %d\n", item, in);
        printf("                                                        buffer: ");
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            printf("%d ", buffer[i]);
        }
        printf("\n");
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&mutex); // 释放互斥锁
        sem_post(&full);  // 通知缓冲区已满
    }
}

void *consumer(void *arg)
{
    int item;
    /* 第一帧用作warmup发送30次 */
    sem_wait(&full);  // 等待缓冲区非空
    sem_wait(&mutex); // 获取互斥锁
    item = buffer[out];
    buffer[out] = -1;
    printf("first            Consumed: %d, index: %d\n", item, out);
    printf("                                                        buffer: ");
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        printf("%d ", buffer[i]);
    }
    printf("\n");
    sleep(10);
    out = (out + 1) % BUFFER_SIZE;
    sem_post(&mutex); // 释放互斥锁
    sem_post(&empty); // 通知缓冲区已空


    for (int i = 0; i < LOOP_COUNT; i++)
    {
        sleep(4);

        sem_wait(&full);  // 等待缓冲区非空
        sem_wait(&mutex); // 获取互斥锁
        item = buffer[out];
        buffer[out] = -1;
        printf("                    Consumed: %d, index: %d\n", item, out);
        printf("                                                        buffer: ");
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            printf("%d ", buffer[i]);
        }
        printf("\n");
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&mutex); // 释放互斥锁
        sem_post(&empty); // 通知缓冲区已空
    }
}

int main()
{
    pthread_t producer_thread, consumer_thread;

    // 初始化信号量
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    // 创建生产者和消费者线程
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // 等待线程结束
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // 销毁信号量
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    system("pause");

    return 0;
}
