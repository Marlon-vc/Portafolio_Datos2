#include <iostream>
#include <chrono>
#include <ctime>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1 ; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int part_index = partition(arr, low, high);
        quicksort(arr, low, part_index - 1);
        quicksort(arr, part_index + 1, high);
    }
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

void fill(int arr[], int size) {
    srand(84398273);

    for (int i=0; i<size; i++) {
        arr[i] = rand();
    }
}

int main() {
    int arr[1270];
    fill(arr, 1270);

    int n = sizeof(arr) / sizeof(arr[0]);
    //print_array(arr, n);
    auto start = std::chrono::system_clock::now();
    quicksort(arr, 0, n - 1);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> seconds = end - start;
    std::cout << "Terminado en:" << seconds.count() << "s\n";
    //print_array(arr, n);
    return 0;
}