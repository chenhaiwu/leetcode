#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>

typedef struct {
    int n;
    pthread_mutex_t task1lock;
    pthread_mutex_t task2lock;
} FooBar;

FooBar* fooBarCreate(int n) {
    FooBar* obj = (FooBar*) malloc(sizeof(FooBar));
    obj->n = n;
    pthread_mutex_init(&obj->task1lock, NULL);
    pthread_mutex_init(&obj->task2lock, NULL);
    pthread_mutex_lock(&obj->task2lock);
    return obj;
}

void foo(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&obj->task1lock);
        // printFoo() outputs "foo". Do not change or remove this line.
        printFoo();
        // printf("foo");
        pthread_mutex_unlock(&obj->task2lock);
    }
}

void bar(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&obj->task2lock);
        // printBar() outputs "bar". Do not change or remove this line.
        printBar();
        // printf("boo\n");
        pthread_mutex_unlock(&obj->task1lock);
    }
}

void fooBarFree(FooBar* obj) {
    free(obj);
}

// void main()
// {
//     pthread_t tid_foo;
//     pthread_t tid_bar;

//     FooBar* obj = fooBarCreate(16);

//     pthread_create(&tid_foo, 0, foo, obj);
//     pthread_create(&tid_bar, 0, bar, obj);

//     pthread_join(tid_foo, 0);
//     pthread_join(tid_bar, 0);

//     fooBarFree(obj);
// }