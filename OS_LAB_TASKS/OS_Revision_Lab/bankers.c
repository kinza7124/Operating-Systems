#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_TELLERS 3 
#define NUM_CUSTOMERS 10 

int account_balance = 1000;
pthread_mutex_t balance_lock;
void* serve_customer(void* teller_id) {
    int id = *((int*)teller_id);
    // lets assume serving 10 customers
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        int transaction_type = rand() % 2; 
        int transaction_amount = rand() % 200 + 1; 
        pthread_mutex_lock(&balance_lock);
        if (transaction_type == 0) { 
            account_balance += transaction_amount;
            printf("Teller %d deposited $%d. New balance: $%d\n", id, transaction_amount, account_balance);
        } else { 
            if (account_balance >= transaction_amount) {
                account_balance -= transaction_amount;
                printf("Teller %d withdrew $%d. New balance: $%d\n", id, transaction_amount, account_balance);
            } else {
                printf("Teller %d tried to withdraw $%d, but insufficient funds. Balance: $%d\n", id, transaction_amount, account_balance);
            }
        }
        pthread_mutex_unlock(&balance_lock);
        // Simulate time taken to serve a customer
        usleep((rand() % 1500 + 500) * 1000); 
    }

    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_mutex_init(&balance_lock, NULL);
    pthread_t tellers[NUM_TELLERS];
    int teller_ids[NUM_TELLERS];  

    for (int i = 0; i < NUM_TELLERS; i++) {
        teller_ids[i] = i + 1;  
        if (pthread_create(&tellers[i], NULL, serve_customer, (void*)&teller_ids[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }
    for (int i = 0; i < NUM_TELLERS; i++) {
        pthread_join(tellers[i], NULL);
    }

    printf("Final account balance: $%d\n", account_balance);
    pthread_mutex_destroy(&balance_lock);

    return 0;
}

