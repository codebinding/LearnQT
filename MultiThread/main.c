#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void *long_loop(void *arg);

char message[] = "Hello World";

int main(void)
{
    int res;
    pthread_t my_thread;
    void *my_thread_return;

    res = pthread_create(&my_thread, NULL, long_loop, (void *)message);
    if( res != 0){

        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for thread to finish...\n");

    res = pthread_join(my_thread, &my_thread_return);
    if( res !=0 ){

        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    printf("Thread joined, it returned %s\n", (char *)my_thread_return);
    printf("Message is now %s\n", message);
    exit(EXIT_SUCCESS);
}

void *long_loop(void *arg){

    int i;

    printf("Thread is running, argument was %s\n", (char *)arg);

    for( i=0;i<10;i++ ){

        printf("%d\n", i);
        usleep(800000);
    }

    strcpy(message, "Bye");
    pthread_exit("Thank you for the CPU time");
}
