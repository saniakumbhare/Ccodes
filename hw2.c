// Created by AJ DiLeo
// For use in CS211 Fall 2023 ONLY

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#define MAX_BIT_POSITION 32

// Cache for storing FizzBuzz results for each bit position
char cache[MAX_BIT_POSITION][3];
// Initialize the cache with FizzBuzz results
void preComputeResults() {
    // TODO: For every possible position, pre-compute its corresponding string output
	// Make sure to handle the case where you will not replace the bit with Z, R, or U
	// Your advancedBitwiseFizzBuzz() code should know when to use the replacement and when to use the bit
    // Use 'Z' for numbers divisible by 3 and 5, 'R' for divisible by 3, and 'U' for divisible by 5
    for (int i = 0; i < MAX_BIT_POSITION; ++i) 
    {
        if (i == 31) 
        {
            strcpy(cache[i], "S");
        } else if (i % 3 == 0 && i % 5 == 0)   {
            strcpy(cache[i], "Z");
        } else if (i % 3 == 0)   {
            strcpy(cache[i], "R");
        } else if (i % 5 == 0)    {
            strcpy(cache[i], "U");
        } else     {
            sprintf(cache[i], "%d", (i & 1));
        }
    }
}
// Retrieve the FizzBuzz result for a specific bit position
char* getFizzBuzzForBit(int position) {
    // TODO: Return the FizzBuzz result for the given position from the cache
    return cache[position];
}
// Perform the advanced Bitwise FizzBuzz logic on the given number
void advancedBitwiseFizzBuzz(int32_t N) {
    // TODO: Implement the advanced Bitwise FizzBuzz logic
    // - For each bit in the number, apply the FizzBuzz logic
    // - Replace the MSb with 'S' if it's set
    // - Print each bit or its FizzBuzz result
    // - Format the output with a space every four bits
	// Each bitstring should be outputted from Left -> Right, MSb -> LSb
	// Index 0 of the bitstring should be the LSb
	// E.g., 
	// 1  0  0 1 0 0 0 1 1 1 0 0   <=== bitstring
	// 11 10 9 8 7 6 5 4 3 2 1 0   <=== indices
    int i = 31;
    while (i >= 0) 
    {
    int bit = (N >> i) & 1;
    char* result;
    if (i == 31 && N < 0)  {
        result = "S";
    } else if (bit == 1)  {
        if (i % 3 == 0 && i % 5 == 0) {
            result = "Z";
        } else if (i % 3 == 0)  {
            result = "R";
        } else if (i % 5 == 0)  {
            result = "U";
             } else {
            result = "1";
        }
    } else 
    {
        result = "0";
   }
    printf("%s", result);
    if (i % 4 == 0)
        printf(" ");

    --i;
}
    printf("\n");
}
// Main function to run the program
int main(int argc, char *argv[]) {
    // TODO: Parse the command line argument to get the input number
    // Use strtol to convert the string to a long integer
    // Check if the number is within the range of a 32-bit signed integer
    // If not, print "Number out of range for a 32-bit integer" and return
    // If so, initialize the cache and call advancedBitwiseFizzBuzz with the parsed number
    if (argc != 2) 
    {
        printf("Usage: %s <int32>\n", argv[0]);
        return 1;
    }
    char* endPtr;
    long long number = strtoll(argv[1], &endPtr, 10);
    if (*endPtr != '\0' || number < INT_MIN || number > INT_MAX) 
    {
        printf("Number out of range for a 32-bit integer\n");
        return 1;
    }
    preComputeResults();
    advancedBitwiseFizzBuzz((int32_t)number);
    return 0;
}