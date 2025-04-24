#include <stdio.h>
#include <stdlib.h>


void sort_array(int *arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int tmp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = tmp;
        }
    }
}


double calculate_mean(int *arr, int n) {
    long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
    }
    return (double)sum / n;
}

double calculate_median(int *arr, int n) {
    sort_array(arr, n);
    if (n % 2 == 1) {
        return arr[n / 2];
    } else {
        return (arr[(n / 2) - 1] + arr[n / 2]) / 2.0;
    }
}

int* calculate_mode(int *arr, int n, int *mode_count) {
    sort_array(arr, n);
    int max_count = 1, curr_count = 1;

    for (int i = 1; i < n; ++i) {
        if (arr[i] == arr[i - 1]) {
            curr_count++;
        } else {
            if (curr_count > max_count) max_count = curr_count;
            curr_count = 1;
        }
    }
    if (curr_count > max_count) max_count = curr_count;


    int *modes = malloc(n * sizeof(int));
    *mode_count = 0;
    curr_count = 1;
    for (int i = 1; i <= n; ++i) {
        if (i < n && arr[i] == arr[i - 1]) {
            curr_count++;
        } else {
            if (curr_count == max_count) {
                modes[(*mode_count)++] = arr[i - 1];
            }
            curr_count = 1;
        }
    }
    return modes;
}

int main(void) {
    int n;
    printf("Enter the number of integers: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid count\n");
        return 1;
    }

    int *data = malloc(n * sizeof(int));
    if (!data) {
        perror("malloc");
        return 1;
    }

    printf("Enter %d integers (separated by spaces):\n", n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &data[i]);
    }

    double mean = calculate_mean(data, n);

    int *for_median = malloc(n * sizeof(int));
    int *for_mode   = malloc(n * sizeof(int));
    if (!for_median || !for_mode) {
        perror("malloc");
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        for_median[i] = data[i];
        for_mode[i]   = data[i];
    }

    double median = calculate_median(for_median, n);

    int mode_count;
    int *modes = calculate_mode(for_mode, n, &mode_count);

    printf("\nResults:\n");
    printf("Mean:   %.2f\n", mean);
    printf("Median: %.2f\n", median);
    printf("Mode%s: ", mode_count > 1 ? "s" : "");
    for (int i = 0; i < mode_count; ++i) {
        printf("%d%s", modes[i], (i < mode_count - 1 ? ", " : "\n"));
    }

    free(data);
    free(for_median);
    free(for_mode);
    free(modes);
    return 0;
}

