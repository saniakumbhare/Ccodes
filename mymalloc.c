#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

// Define constants
#define MEMLENGTH 4096

// Define memory array
static char memory[MEMLENGTH];

// Define memory block structure
typedef struct Block {
    size_t size;
    int free;
    struct Block *next;
} Block;

// Initialize the memory array
static void initialize_memory() {
    Block *initial = (Block *)memory;
    initial->size = MEMLENGTH - sizeof(Block);
    initial->free = 1;
    initial->next = NULL;
}

// Allocate memory from the memory array
void *mymalloc(size_t size, char *file, int line) {
    static int initialized = 0;
    if (!initialized) {
        initialize_memory();
        initialized = 1;
    }

    Block *curr = (Block *)memory;
    Block *best_fit = NULL;

    // Find the best fit block
    while (curr != NULL) {
        if (curr->free && curr->size >= size && (best_fit == NULL || curr->size < best_fit->size)) {
            best_fit = curr;
        }
        curr = curr->next;
    }

    // Allocate memory from the best fit block
    if (best_fit != NULL) {
        // Split the block if there's enough space
        if (best_fit->size >= size + sizeof(Block)) {
            Block *new_block = (Block *)((char *)best_fit + sizeof(Block) + size);
            new_block->size = best_fit->size - size - sizeof(Block);
            new_block->free = 1;
            new_block->next = best_fit->next;
            best_fit->next = new_block;
            best_fit->size = size;
        }
        best_fit->free = 0;
        return (void *)(best_fit + 1);
    }

    // Unable to allocate memory
    fprintf(stderr, "Memory allocation error at %s:%d\n", file, line);
    return NULL;
}

// Free memory in the memory array
void myfree(void *ptr, char *file, int line) {
    if (ptr == NULL) {
        fprintf(stderr, "Attempting to free a NULL pointer at %s:%d\n", file, line);
        return;
    }

    Block *block_to_free = (Block *)((char *)ptr - sizeof(Block));
    if (block_to_free->free) {
        fprintf(stderr, "Attempting to free an already freed pointer at %s:%d\n", file, line);
        return;
    }

    block_to_free->free = 1;

    // Coalesce adjacent free blocks
    Block *curr = (Block *)memory;
    while (curr != NULL && curr->next != NULL) {
        if (curr->free && curr->next->free) {
            curr->size += sizeof(Block) + curr->next->size;
            curr->next = curr->next->next;
        }
        curr = curr->next;
    }
}
