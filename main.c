#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long long int uint_t;

uint_t *alloc_array(uint_t size)
{
    uint_t *buffer = (uint_t *) malloc(size * sizeof(uint_t));
    return buffer;
}

void print_array(uint_t *array, uint_t size)
{
    unsigned int i = 0;
    for (i = 0; i < size; i++) {
        printf("%llu\t", array[i]);
    }

    printf("\n");
}

uint_t brute_force_count_inversions(uint_t *array, uint_t n)
{
    uint_t i = 0, j = 0;
    uint_t sum_inversions = 0;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (array[i] > array[j]) {
                sum_inversions += 1;
            }
        }
    }

    return sum_inversions;
}

uint_t *read_input()
{
    uint_t i = 0;
    uint_t size = 100000;
    uint_t *buffer = alloc_array(size);
    FILE *file = fopen("input.txt", "r");

    for (i = 0; i < size; i++) {
        fscanf(file, "%llu", &(buffer[i]));
    }

    fclose(file);
    return buffer;
}

uint_t merge_count_split_inversions(uint_t *array, uint_t start, uint_t middle, uint_t end)
{
    uint_t i = 0;
    uint_t left_pointer = start;
    uint_t right_pointer = middle + 1;
    uint_t size = end + 1;
    uint_t *tmp_array = alloc_array(size);

    uint_t split_inversions_sum = 0;
    uint_t current_split_inversions = 0;

    for (i = start; left_pointer <= middle && right_pointer <= end; i++) {
        if (array[left_pointer] <= array[right_pointer]) {
            tmp_array[i] = array[left_pointer];
            left_pointer++;
        } else {
            tmp_array[i] = array[right_pointer];
            right_pointer++;

            current_split_inversions = (middle + 1) - left_pointer;
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

uint_t merge_sort(uint_t *array, uint_t start, uint_t end)
{
    uint_t middle = (start + end)/2;

    if (start >= end) {
        return 0;
    }

    uint_t split_inversions_left = merge_sort(array, start, middle);
    uint_t split_inversions_right = merge_sort(array, middle + 1, end);
    uint_t split_inv = merge_count_split_inversions(array, start, middle, end);
    return split_inv + split_inversions_left + split_inversions_right;
}

int main(void)
{
    uint_t size = 100000;
    uint_t *array = read_input();

    uint_t brute_force_solution = brute_force_count_inversions(array, size);
    uint_t divide_conquer_solution = merge_sort(array, 0, size - 1);

    if (divide_conquer_solution == brute_force_solution) {
        printf("%llu\n", divide_conquer_solution);
        printf("CORRECT ANSWER!\n");
    } else {
        printf("Divide and Conquer returned %llu but expected was %llu\n", divide_conquer_solution, brute_force_solution);
    }

    free(array);
    return 0;
}
