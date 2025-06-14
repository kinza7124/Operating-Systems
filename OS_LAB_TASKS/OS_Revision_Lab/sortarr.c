#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10

int arr[SIZE];
pthread_mutex_t mutex;
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}
void merge(int *arr, int *left, int left_size, int *right, int right_size) {
    int i = 0, j = 0, k = 0;
    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < left_size) {
        arr[k++] = left[i++];
    }
    while (j < right_size) {
        arr[k++] = right[j++];
    }
}

void *sort_first_half(void *arg) {
    int half_size = SIZE / 2;
    qsort(arr, half_size, sizeof(int), compare);
    return NULL;
}

void *sort_second_half(void *arg) {
    int half_size = SIZE / 2;
    qsort(arr + half_size, half_size, sizeof(int), compare);
    return NULL;
}

int main() {
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100;
    }
    printf("Unsorted array:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, sort_first_half, NULL);
    pthread_create(&thread2, NULL, sort_second_half, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    int *left = arr;
    int *right = arr + SIZE / 2;
    int left_size = SIZE / 2;
    int right_size = SIZE - left_size;

    int *merged = (int *)malloc(sizeof(int) * SIZE);
    merge(merged, left, left_size, right, right_size);

    printf("Merged sorted array:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", merged[i]);
    }
    printf("\n");

    free(merged);

    return 0;
}

