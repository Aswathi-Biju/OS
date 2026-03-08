#include <stdio.h>      // for printf
#include <pthread.h>    // for threads (producer and consumer)
#include <semaphore.h>  // for semaphore functions
#include <unistd.h>     // for sleep()

#define BUFFER_SIZE 5   // size of the shared buffer

int buffer[BUFFER_SIZE]; // shared buffer array
int in = 0;              // index where producer inserts item
int out = 0;             // index where consumer removes item

sem_t empty;  // counts empty slots in buffer
sem_t full;   // counts filled slots in buffer
sem_t mutex;  // ensures only one thread accesses buffer at a time


// Producer thread function
void *producer(void *arg)
{
    int item;

    // produce 10 items
    for(int i = 0; i < 10; i++)
    {
        item = i;  // produce an item

        sem_wait(&empty); // check if buffer has empty space
        sem_wait(&mutex); // lock buffer (critical section)

        buffer[in] = item; // place item into buffer
        printf("Produced: %d\n", item);

        in = (in + 1) % BUFFER_SIZE; // move to next buffer position (circular)

        sem_post(&mutex); // unlock buffer
        sem_post(&full);  // increase number of full slots

        sleep(1); // delay to simulate production time
    }
}


// Consumer thread function
void *consumer(void *arg)
{
    int item;

    // consume 10 items
    for(int i = 0; i < 10; i++)
    {
        sem_wait(&full);  // wait if buffer is empty
        sem_wait(&mutex); // lock buffer

        item = buffer[out]; // remove item from buffer
        printf("Consumed: %d\n", item);

        out = (out + 1) % BUFFER_SIZE; // move to next position

        sem_post(&mutex); // unlock buffer
        sem_post(&empty); // increase empty slots

        sleep(1); // delay to simulate consumption
    }
}


// Main function
int main()
{
    pthread_t p, c; // thread variables for producer and consumer

    // initialize semaphores
    sem_init(&mutex, 0, 1);          // mutex starts at 1 (unlocked)
    sem_init(&empty, 0, BUFFER_SIZE);// buffer initially empty
    sem_init(&full, 0, 0);           // no items initially

    // create producer thread
    pthread_create(&p, NULL, producer, NULL);

    // create consumer thread
    pthread_create(&c, NULL, consumer, NULL);

    // wait for producer thread to finish
    pthread_join(p, NULL);

    // wait for consumer thread to finish
    pthread_join(c, NULL);

    return 0; // end program
}
