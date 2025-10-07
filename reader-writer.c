
 #include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int read_count = 0;            // number of readers currently reading
sem_t mutex;                   // semaphore for read_count access
sem_t write_lock;              // semaphore for writers

void* reader(void* arg) {
    int id = *((int*)arg);

        // Entry section
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&write_lock);   // first reader locks writers
        }
        sem_post(&mutex);

        // Critical section (reading)
        printf("reader %d is reading...\n", id);
        sleep(1);

        // Exit section
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&write_lock);   // last reader unlocks writers
        }
        sem_post(&mutex);

   printf("reader %d done reading\n",id);
    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);
        
        sem_wait(&write_lock);

        // Critical section (writing)
        printf("writer %d is writing...\n", id);
        sleep(2);

        // Exit section
        sem_post(&write_lock);

        printf("writer %d done writing\n",id);
    return NULL;
}

int main() {
    pthread_t r[5], w[3];
    int reader_ids[5] = {1,2,3,4,5};
    int writer_ids[3] = {1,2,3};
     sem_init(&mutex, 0, 1);
    sem_init(&write_lock, 0, 1);
    // create reader threads
     for (int i = 0; i < 5; i++) {
        pthread_create(&r[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&w[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(r[i], NULL);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(w[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&write_lock);

    return 0;
}
