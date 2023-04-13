#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int n;
    int exit_flag;
    sem_t num_sem;
    sem_t fizz_sem;
    sem_t buzz_sem;
    sem_t both_sem;
} FizzBuzz;

FizzBuzz* fizzBuzzCreate(int n) {
    FizzBuzz* obj = (FizzBuzz*) malloc(sizeof(FizzBuzz));
    obj->n = n;
    obj->exit_flag = 0;
    sem_init(&obj->num_sem, 0, 0);
    sem_init(&obj->fizz_sem, 0, 0);
    sem_init(&obj->buzz_sem, 0, 0);
    sem_init(&obj->both_sem, 0, 0);
    return obj;
}

// printFizz() outputs "fizz".
void fizz(FizzBuzz* obj) {
    while (1) {
        sem_wait(&obj->fizz_sem);
        if (obj->exit_flag) {
            break;
        }
        // printf("fizz ");
        printFizz();
        sem_post(&obj->num_sem);
    }
}

// printBuzz() outputs "buzz".
void buzz(FizzBuzz* obj) {
    while (1) {
        sem_wait(&obj->buzz_sem);
        if (obj->exit_flag) {
            break;
        }
        // printf("buzz ");
        printBuzz();
        sem_post(&obj->num_sem);
    }
}

// printFizzBuzz() outputs "fizzbuzz".
void fizzbuzz(FizzBuzz* obj) {
    while (1) {
        sem_wait(&obj->both_sem);
        if (obj->exit_flag) {
            break;
        }
        // printf("fizzbuzz ");
        printFizzBuzz();
        sem_post(&obj->num_sem);
    }
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.
void number(FizzBuzz* obj) {
    for (int i = 1; i <= obj->n; i++) {
        if (i % 15 == 0) {
            sem_post(&obj->both_sem);
            sem_wait(&obj->num_sem);
        } else if (i % 3 == 0) {
            sem_post(&obj->fizz_sem);
            sem_wait(&obj->num_sem);
        } else if (i % 5 == 0) {
            sem_post(&obj->buzz_sem);
            sem_wait(&obj->num_sem);
        } else {
            // printf("%d ", i);
            printNumber(i);            
        }
    }
    obj->exit_flag = 1;
    sem_post(&obj->fizz_sem);
    sem_post(&obj->buzz_sem);
    sem_post(&obj->both_sem);
    return;
}

void fizzBuzzFree(FizzBuzz* obj) {
    sem_destroy(&obj->num_sem);
    sem_destroy(&obj->fizz_sem);
    sem_destroy(&obj->buzz_sem);
    sem_destroy(&obj->both_sem);
    free(obj);
}

// void main()
// {
//     pthread_t tid_num;
//     pthread_t tid_fizz;
//     pthread_t tid_buzz;
//     pthread_t tid_both;

//     FizzBuzz* obj = fizzBuzzCreate(16);

//     pthread_create(&tid_fizz, 0, fizz, obj);
//     pthread_create(&tid_buzz, 0, buzz, obj);
//     pthread_create(&tid_both, 0, fizzbuzz, obj);
//     pthread_create(&tid_num, 0, number, obj);

//     printf("after thread create\n");
//     pthread_join(tid_num, 0);
//     pthread_join(tid_fizz, 0);
//     pthread_join(tid_buzz, 0);
//     pthread_join(tid_both, 0);

//     printf("after thread join\n");

//     fizzBuzzFree(obj);
//     printf("free\n");
//     return;
// }