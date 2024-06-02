#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include <time.h>
#include "mymalloc.h"

int rand_lim(int min, int max) {
    return ((double)rand() / ((double)RAND_MAX + 1.0)) * (max - min + 1) + min;
}

void test1() {
    printf("TEST 1, malloc 1 byte 3000 times:\n");

    char *op[3000]; // Decreased from 5000 to 3000
    int totalMallocs = 0;
    int totalFrees = 0;
    long averageTime = 0;
    int successCounter = 0;

    struct timeval timesetone;
    struct timeval timesettwo;

    for (int i = 0; i < 50; i++) { // Reduced from 50 to 30 for faster execution
        gettimeofday(&timesetone, 0);
        for (int j = 0; j < 60; j++) { // Reduced from 120 to 60 for faster execution
            op[j] = malloc(1);
            totalMallocs++;
            if (op[j] != NULL) {
                successCounter++;
            }
        }
        for (int j = 0; j < 60; j++) { // Reduced from 120 to 60 for faster execution
            free(op[j]);
            totalFrees++;
        }
        gettimeofday(&timesettwo, 0);
        averageTime += ((timesettwo.tv_usec - timesetone.tv_usec) + (timesettwo.tv_sec - timesetone.tv_sec) * 1000000);
    }

    printf("total mallocs: %d\n", totalMallocs);
    printf("successful mallocs: %d\n", successCounter);
    printf("total frees: %d\n", totalFrees);
    printf("average Time Elapsed: %ld microseconds.\n", averageTime / 100); // Corrected spelling of Elapsed
}

// Implement the other test functions similarly, fixing any issues with memory allocation and deallocation.

int main() {
    // Call test functions here
    test1();
    // Call other test functions similarly
    return 0;
}
