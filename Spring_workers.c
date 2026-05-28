//OS CEP of CS123 CS115 CS113
//Spring Workers

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define Crate_Size 12
#define PICKERS 3

int *tree;
int total_fruits;
int fruit_index = 0;

int crate[Crate_Size];
int crate_count = 0;

int complete = 0;

// Synchronization
pthread_mutex_t mutex;
pthread_cond_t crate_full;
pthread_cond_t crate_empty;

// Picker Function
void* picker(void* arg) {
    int id = *((int*)arg);

    while (1) {
        pthread_mutex_lock(&mutex);

        if (fruit_index >= total_fruits) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        int fruit = tree[fruit_index++];
        printf("Picker %d has picked the fruit %d\n", id, fruit);

        crate[crate_count++] = fruit;

        printf("Picker %d has placed the fruit %d in the crate, On Slot No. %d\n",
               id, fruit, crate_count);

        if (crate_count == Crate_Size) {
            printf("\nPicker %d sees crate as full, now moving to loader \n", id);
            pthread_cond_signal(&crate_full);

            while (crate_count == Crate_Size)
                pthread_cond_wait(&crate_empty, &mutex);
        }

        pthread_mutex_unlock(&mutex);
        usleep(100000);
    }

    printf("\nPicker %d has finished and Tree has no fruits now. \n", id);
    return NULL;
}

// Loader Function
void* loader(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        while (crate_count < Crate_Size && !complete) {
            pthread_cond_wait(&crate_full, &mutex);
        }

        if (crate_count > 0) {
            printf("\nLoading crate with %d fruits into the truck \n", crate_count);
            crate_count = 0;
            printf("Crate placed in Truck and New Crate is Provided \n\n");

            pthread_cond_broadcast(&crate_empty);
        }

        if (complete && crate_count == 0) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        pthread_mutex_unlock(&mutex);
    }

    printf("All Crates are Loaded.\n");
    return NULL;
}

int main() {
    pthread_t p[PICKERS], l;
    int ids[PICKERS];

    printf("\n\t OPERATING SYSTEMS CEP \n\t\t BY CS23123, CS23115, CS23113");
    printf("\n\n\t Problem: SPRING WORKERS \n\n");
    
    printf("Enter the Number of Fruits on Tree: ");
    scanf("%d", &total_fruits);

    // Allocate memory to the tree dynamically
    tree = (int*)malloc(sizeof(int) * total_fruits);

    // Initialize the tree
    for (int i = 0; i < total_fruits; i++)
        tree[i] = i + 1;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&crate_full, NULL);
    pthread_cond_init(&crate_empty, NULL);

    pthread_create(&l, NULL, loader, NULL);

    for (int i = 0; i < PICKERS; i++) {
        ids[i] = i + 1;
        pthread_create(&p[i], NULL, picker, &ids[i]);
    }

    for (int i = 0; i < PICKERS; i++)
        pthread_join(p[i], NULL);

    pthread_mutex_lock(&mutex);
    complete = 1;
    pthread_cond_signal(&crate_full);
    pthread_mutex_unlock(&mutex);

    pthread_join(l, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&crate_full);
    pthread_cond_destroy(&crate_empty);

    free(tree);

    printf("\nProcess Completed!\n");
    return 0;
}
