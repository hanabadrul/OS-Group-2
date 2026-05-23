#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define MEALS_TO_EAT 3

// Mutexes represent the chopsticks
pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];

void *philosopher(void *num) {
    int id = *(int *)num;
    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;

    for (int i = 0; i < MEALS_TO_EAT; i++) {
        // 1. Thinking
        printf("Philosopher %d is thinking.\n", id);
        sleep(1); // Simulate time spent thinking

        // 2. Picking up chopsticks (Deadlock Avoidance Strategy)
        // The last philosopher picks up the right chopstick first to break the cycle.
        if (id == NUM_PHILOSOPHERS - 1) {
            pthread_mutex_lock(&chopsticks[right_chopstick]);
            printf("Philosopher %d picked up right chopstick %d.\n", id, right_chopstick);
            
            pthread_mutex_lock(&chopsticks[left_chopstick]);
            printf("Philosopher %d picked up left chopstick %d.\n", id, left_chopstick);
        } else {
            // All other philosophers pick up the left chopstick first.
            pthread_mutex_lock(&chopsticks[left_chopstick]);
            printf("Philosopher %d picked up left chopstick %d.\n", id, left_chopstick);
            
            pthread_mutex_lock(&chopsticks[right_chopstick]);
            printf("Philosopher %d picked up right chopstick %d.\n", id, right_chopstick);
        }

        // 3. Eating
        printf("Philosopher %d is EATING meal %d.\n", id, i + 1);
        sleep(1); // Simulate time spent eating

        // 4. Putting down chopsticks
        pthread_mutex_unlock(&chopsticks[left_chopstick]);
        pthread_mutex_unlock(&chopsticks[right_chopstick]);
        printf("Philosopher %d put down both chopsticks.\n", id);
    }
    
    printf("Philosopher %d is full and leaving the table.\n", id);
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize the mutexes (chopsticks)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (pthread_mutex_init(&chopsticks[i], NULL) != 0) {
            printf("Mutex initialization failed.\n");
            return 1;
        }
    }

    // Create the philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        if (pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]) != 0) {
            printf("Thread creation failed.\n");
            return 1;
        }
    }

    // Wait for all philosophers to finish eating
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy the mutexes to free resources
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    printf("All philosophers have finished dining. Simulation complete.\n");
    return 0;
}