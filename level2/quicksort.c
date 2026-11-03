#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Level 2: Debugging Inconsistencies (fixed)
 *
 * - All functions use snake_case naming.
 * - Every function that can fail returns a status code checked by the caller.
 * - Array size is derived once instead of hardcoded in several places.
 * - Allocated memory is always freed.
 */

#define MAX_SIZE 1000

static void swap_elements(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static int partition_array(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap_elements(&arr[i], &arr[j]);
        }
    }
    swap_elements(&arr[i + 1], &arr[high]);
    return i + 1;
}

static void quick_sort_range(int arr[], int low, int high) {
    if (low < high) {
        int pivot_index = partition_array(arr, low, high);
        quick_sort_range(arr, low, pivot_index - 1);
        quick_sort_range(arr, pivot_index + 1, high);
    }
}

/* Public entry point: sorts the whole array. Returns 0 on success, -1 on bad input. */
static int quick_sort(int arr[], size_t size) {
    if (arr == NULL || size > MAX_SIZE) {
        return -1;
    }
    if (size > 1) {
        quick_sort_range(arr, 0, (int)size - 1);
    }
    return 0;
}

static void print_array(const char *label, const int arr[], size_t size) {
    printf("%s\n", label);
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    const int initial_values[] = {10, 7, 8, 9, 1, 5, 2, 3, 4, 6};
    const size_t size = sizeof(initial_values) / sizeof(initial_values[0]);

    int *data = malloc(size * sizeof(*data));
    if (data == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }
    memcpy(data, initial_values, size * sizeof(*data));

    print_array("Original array:", data, size);

    if (quick_sort(data, size) != 0) {
        fprintf(stderr, "Error: invalid input to quick_sort\n");
        free(data);
        return EXIT_FAILURE;
    }

    print_array("Sorted array:", data, size);

    free(data);
    return EXIT_SUCCESS;
}
