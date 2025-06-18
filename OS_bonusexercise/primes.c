#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>
int isPrime(int num)
{
if(num<=1)
{
return 0;
}
for(int i=2;i*i<=num;i++)
{
if(num%i ==0)
{
return 0;
}
return 1;
}
}
void *prime_printer(void *arg) {
    int limit = *((int *)arg);
    free(arg); 
    printf("Primes up to %d: ", limit);
    for (int i = 2; i <= limit; i++) {
        if (isPrime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
    return NULL;
}
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int limit = atoi(argv[1]);
    if (limit < 2) {
        printf("No primes less than or equal to %d\n", limit);
        return 0;
    }
   int *limit_ptr = malloc(sizeof(int));
    *limit_ptr = limit;
    pthread_t thread;
    if (pthread_create(&thread, NULL, prime_printer, limit_ptr) != 0) {
        perror("Failed to create thread");
        free(limit_ptr);
        return 1;
    }
    pthread_join(thread, NULL);
    return 0;
}


