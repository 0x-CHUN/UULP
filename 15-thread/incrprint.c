#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM 5

int counter = 0;

void *print_count(void *);

int main(int argc, char const *argv[]) {
    pthread_t t1;

    pthread_create(&t1, NULL, print_count, NULL);
    for (int i = 0; i < NUM; i++) {
        counter++;
        sleep(1);
    }
    pthread_join(t1, NULL);
    return 0;
}

void *print_count(void *m) {
    for (int i = 0; i < NUM; i += 1) {
        printf("count = %d\n", counter);
        sleep(1);
    }
    return NULL;
}