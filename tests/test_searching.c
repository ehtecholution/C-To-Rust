#include <stdio.h>
#include <assert.h>
#include "../src/algorithms/searching.h"

void test_binary_search() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    assert(binary_search(arr, 0, n-1, 7) == 3);
    assert(binary_search(arr, 0, n-1, 15) == 7);
    assert(binary_search(arr, 0, n-1, 1) == 0);
    assert(binary_search(arr, 0, n-1, 10) == -1);
    
    printf("Binary search test passed.\n");
}

void test_interpolation_search() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    assert(interpolation_search(arr, 0, n-1, 7) == 3);
    assert(interpolation_search(arr, 0, n-1, 15) == 7);
    assert(interpolation_search(arr, 0, n-1, 1) == 0);
    assert(interpolation_search(arr, 0, n-1, 10) == -1);
    
    printf("Interpolation search test passed.\n");
}

int main() {
    test_binary_search();
    test_interpolation_search();
    printf("All searching algorithm tests passed.\n");
    return 0;
}