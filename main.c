#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *alloc_array(int size)
{
    int *buffer = (int *) malloc(size * sizeof(int));
    return buffer;
}

void print_array(int *array, int size)
{
    int i = 0;
    for (i = 0; i < size; i++) {
        printf("%d\t", array[i]);
    }

    printf("\n");
}

int brute_force_count_inversions(int *array, int n)
{
    int i = 0, j = 0;
    int sum_inversions = 0;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (array[i] > array[j]) {
                sum_inversions += 1;
            }
        }
    }

    return sum_inversions;
}

int merge_count_split_inversions(int *array, int start, int middle, int end)
{
    int i = 0;
    int left_pointer = start;
    int right_pointer = middle + 1;
    int size = end + 1;
    int *tmp_array = alloc_array(size);

    int split_inversions_sum = 0;
    int current_split_inversions = 0;

    for (i = start; left_pointer <= middle && right_pointer <= end; i++) {
        if (array[left_pointer] <= array[right_pointer]) {
            tmp_array[i] = array[left_pointer];
            left_pointer++;
        } else {
            tmp_array[i] = array[right_pointer];
            right_pointer++;

            current_split_inversions = (middle + 1) - left_pointer; // +1 talvez suma
            split_inversions_sum += current_split_inversions;
        }
    }

    while (left_pointer <= middle) {
        tmp_array[i] = array[left_pointer];
        left_pointer++;
        i++;
    }

    while (right_pointer <= end) {
        tmp_array[i] = array[right_pointer];
        right_pointer++;
        i++;
    }

    for (i = start; i <= end; i++) {
        array[i] = tmp_array[i];
    }

    free(tmp_array);

    return split_inversions_sum;
}

int merge_sort(int *array, int start, int end)
{
    int middle = (start + end)/2;

    if (start >= end) {
        return 0;
    }

    int split_inversions_left = merge_sort(array, start, middle);
    int split_inversions_right = merge_sort(array, middle + 1, end);
    int split_inv = merge_count_split_inversions(array, start, middle, end);
    return split_inv + split_inversions_left + split_inversions_right;
}

int main(void)
{
    int i =0;
    int size = 0;
    scanf("%d", &size);
    int *array = alloc_array(size);

    srand(time(NULL));
    for (i = 0; i < size; i++) {
        array[i] = rand() % 100000;
    }

    int brute_force_solution = brute_force_count_inversions(array, size);
    int divide_conquer_solution = merge_sort(array, 0, size - 1);

    // print_array(array, size);

    if (divide_conquer_solution == brute_force_solution) {
        printf("CORRECT ANSWER!\n");
    } else {
        printf("Divide and Conquer returned %d but expected was %d\n", divide_conquer_solution, brute_force_solution);
    }

    return 0;
}