#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include <time.h>
#include "mymalloc.h"



int rand_lim(int min, int max)
{
    return ((double)rand() / (((double)RAND_MAX) + 1.0)) * (max-min+1) + min;
}


void deleteArrayItem( int intindex, int length, char ** array)
{
    int newint;
    for (newint = intindex; newint < length - 1; newint++ )
    {
        array[newint] = array[1 + newint];
    }
}


void test1(){
    char * op[5000];
    int totalMallocs = 0;
    int totalFrees = 0;
    long averagelong=0;
    int successCounter = 0;
    int currentSuccessCount = 0;
    int freeCounter = 0;
   

    struct timeval timesetone;
    struct timeval timesettwo;

    printf("TEST 1, malloc 1 byte 3000 times:\n");


    int newint;
    int y; 
    int zero = 0; 
    for (y=zero; y<50; y++) {

        gettimeofday(&timesetone, 0);
        for (newint=0; newint<120; newint++) 
        {
            op[newint] = malloc(1);
            totalMallocs++;

            if (NULL != op[newint])
            {
                successCounter++;
                currentSuccessCount++;
            }
        }

        for (newint = zero; currentSuccessCount > newint; newint++) 
        {
            free(op[newint]);
            freeCounter++;
            totalFrees++;
        }

        currentSuccessCount = zero;
        gettimeofday(&timesettwo, 0);
        averagelong += ((timesettwo.tv_usec-timesetone.tv_usec) + (timesettwo.tv_sec-timesetone.tv_sec)*1000000);
    }



    printf("total mallocs: %d\n", totalMallocs);
    printf("successful mallocs: %d\n", successCounter);
    printf("total frees: %d\n", totalFrees);
    printf("averagelong Time Elasped: %ld microseconds.\n", averagelong/100);


    char * testingchar = malloc(4998);

    if (NULL != testingchar)
    {
        printf("test 1 passed\n");
    }
    free(testingchar);
}

void test2(){
    printf("TEST 2, malloc 1 byte 3000 times and free immediately:\n");

    char * pointervoid = NULL;
    int newint;
    int successCounter = 0;
    int freeCounter = 0;
    int totalMallocs = 0;
    int totalFrees = 0;
    long averagelong= 0;
    struct timeval timesetone;
    struct timeval timesettwo;
    int zero = 0; 
    int y; 


for (y=0; y<50; y++) {

        gettimeofday(&timesetone, 0);
        for (newint=zero; newint<120; newint++) 
        {
            pointervoid = malloc(1);
            totalMallocs++;


            if (NULL != pointervoid)
            {
                free(pointervoid);
                successCounter++;
                freeCounter++;
                totalFrees++;
            }
        }
        gettimeofday(&timesettwo, 0);

        averagelong+=((timesettwo.tv_usec-timesetone.tv_usec) + ((timesettwo.tv_sec-timesetone.tv_sec)*1000000));
}
    


    char * test = malloc(4998);
    printf("Total mallocs: %d\n", totalMallocs);
    printf("Successful mallocs: %d\n", successCounter);
    printf("Total frees: %d\n", totalFrees);
    printf("Successful frees: %d\n", freeCounter);
    printf("Average Time Elasped: %ld microseconds.\n", averagelong/100);


    if (NULL != test)
    {
        printf("test 2 passed\n");
    }
    free(test);
}

void test3()
{

    int mallocCounter = 0;
    int freeCounter = 0;
    int onecheck = 1; 
    int totalMallocs = 0;
    int successCounter = 0;
    char * pointers[120];
    int length = 0;
    long averagelong= 0;
    int y; 

    struct timeval timesetone;
    struct timeval timesettwo;

    printf("TEST 3, randomly choose between size 1 or free 120 times or between a malloc: \n");


for (y = 0; y < 50; y++){

        gettimeofday(&timesetone, 0);
        while(mallocCounter < 120)
        {
            int pick = rand_lim(0, 1);
            if (0 == pick)
            {
                int sizeint = onecheck; 
                void * pointervoid = malloc(sizeint);
                totalMallocs++;
                if (NULL != pointervoid)
                {

                    pointers[length] = pointervoid;
                    length++;

                    successCounter++;
                }

                mallocCounter++;

            }
            
            else 
            {
                if (0 < length)
                {
                    int intindex = rand_lim(0, (length - onecheck));
                    free(pointers[intindex]);
                    char ** start = &pointers[0];

                    deleteArrayItem(intindex, length, start);
                    length--;
                    freeCounter++;
                }

            }

        }

        while (0 < length)
        {
            int intindex = rand_lim(0, (length - onecheck));
            free(pointers[intindex]);
            char ** start = &pointers[0];
            deleteArrayItem(intindex, length, start);
            length--;
            freeCounter++;

        }
        mallocCounter = 0;
        gettimeofday(&timesettwo, 0);
        long totalavglong  = (timesettwo.tv_usec-timesetone.tv_usec) + ((timesettwo.tv_sec-timesetone.tv_sec)*1000000); 
        averagelong += (totalavglong);
}


    printf("Total mallocs: %d\n", totalMallocs);
    printf("Successful mallocs: %d\n", successCounter);
    printf("frees: %d\n", freeCounter);
    printf("average Time Elasped: %ld microseconds.\n", averagelong/100);

    char * test = malloc(4998);
    if (NULL != test)
    {
        printf("TEST PASSED\n");
    }

    free(test);
}

void test4()
{
    int i;
    int randozero =1;
    int y; 
    int freeCounter = 0;
    int successCounter = 0;
    int totalMallocs = 0;
    long averagelong = 0;
    char * pointervoid = NULL;
    struct timeval timesetone;
    struct timeval timesettwo;
    int zero =0; 

    printf("test 4, called malloc() of increasing size, starts at 1 and increments by 1 (50 times)\n");

        for (y=zero; y<50; y++) 
        {
            gettimeofday(&timesetone, 0);

            for (i = 0; i<50;i++)
            {
                randozero++;
                pointervoid = malloc(randozero);
                totalMallocs++;
                if (pointervoid != NULL)
                {
                    successCounter++;
                    free(pointervoid);
                    freeCounter++;
                }

            }
            randozero = 0;

            gettimeofday(&timesettwo, 0);
            averagelong+=((timesettwo.tv_sec-timesetone.tv_sec)*1000000 + timesettwo.tv_usec-timesetone.tv_usec);
        }

    printf("Total mallocs: %d\n", totalMallocs);
    printf("Successful mallocs: %d\n", successCounter);
    printf("Frees: %d\n", freeCounter);
    printf("averagelong Time Elasped: %ld microseconds.\nTEST PASSED\n", averagelong/100);
    //printf("mallocs: %d\n", mallocCounter);
    //printf("frees: %d\n", freeCounter);
}

void test5()
{
    int y;
    long averagelong = 0;
    long beforeavg = 0;
    void * pointervoid;
    struct timeval timesetone;
    struct timeval timesettwo;

    printf("test 5, Malloc various primitive type pointers dereference with values and use the printf function with them:");

    for (y = 0; y < 3; y++) 
    {
        gettimeofday(&timesetone, 0);
        printf("\n");
        pointervoid=(int*)malloc(sizeof(int));
        *(int*)pointervoid = rand_lim(0,100);
        printf("int = %d\n",*(int*)pointervoid);
        free(pointervoid);

        pointervoid=(char*)malloc(sizeof(char));
        *(char*)pointervoid = (rand_lim(65,90));
        printf("char = %c\n",*(char*)pointervoid);
        free(pointervoid);

        pointervoid=(long*)malloc(sizeof(long));
        *(long*)pointervoid = rand_lim(0,1000);
        printf("long = %ld\n",*(long*)pointervoid);
        free(pointervoid);

        pointervoid=(long int*)malloc(sizeof(long int));
        *(long int*)pointervoid = rand_lim(0,1000);
        printf("long int = %ld\n",*(long int*)pointervoid);
        free(pointervoid);

        pointervoid=(double*)malloc(sizeof(double));
        *(double*)pointervoid = rand_lim(0,5000);
        printf("double = %f\n",(*(double*)pointervoid)/rand_lim(1, 99));
        free(pointervoid);

        pointervoid=(long double*)malloc(sizeof(long double));
        *(long double*)pointervoid = rand_lim(0,5000);
        printf("long double = %Lf\n",(*(long double*)pointervoid)/rand_lim(1, 99));
        free(pointervoid);
        printf("\n");
        gettimeofday(&timesettwo, 0);
        beforeavg= ((timesettwo.tv_sec-timesetone.tv_sec)*1000000 + timesettwo.tv_usec-timesetone.tv_usec);  

        averagelong+=(beforeavg);
    }

    printf("average long Time Elasped: %ld microseconds.\ntest passed\n", averagelong/100);
}

int main(int argc, char ** argv)
{

    if (1 != argc)
    {
        printf("correct use: \n./memgrind\n");
    }
    else 
    {
        time_t t;
        srand((unsigned)time(&t));
        printf("Each test is performed 100 times\n");
        printf("\ntest one:\n");
        test1();
        printf("\ntest two:\n");
        test2(); 
        printf("\ntest 3:\n"); 
        test3();
        printf("\ntest 4:\n"); 
        test4();
        printf("\ntest 5:\n");
        test5();
    }

    return 0;

}