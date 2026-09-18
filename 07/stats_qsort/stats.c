#include "stats.h"
#include <math.h>
#include <stdlib.h>

// used for qsort in median
static int cmp_double(const void *a, const void *b) {
    double x = *(const double *)a, y = *(const double *)b;
    return (x > y) - (x < y);      // -1/0/1 without subtraction overflow tricks
}

double mean(const double *arr, size_t n) {
    double sum = 0.0;
    for (size_t i = 0; i < n; i++) {
    	sum += arr[i];
	}
    return sum / (double)n; 
}

double minimum(const double *arr, size_t n) {
	double min = arr[0];
	for (size_t i = 1; i < n; i++) {
		if (arr[i] < min) {
			min = arr[i];
		}
	}
	return min;
}

double maximum(const double *arr, size_t n) {
	double max = arr[0];
	for (size_t i = 1; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
			
}

double stddev(const double *arr, size_t n, const double mean_val) {
	double squaredDiffSum = 0.0;
    for (size_t i = 0; i < n; i++) {
        double diff = arr[i] - mean_val;
        squaredDiffSum += diff * diff;
    }

    return sqrt(squaredDiffSum / (n - 1));
}

double median(double *arr, size_t n) {
	// side effect: sorts arr
    
    qsort(arr, n, sizeof(double), cmp_double);
    
// 	// insertion sort. This takes me back.
// 	for (size_t i = 1; i < n; i++) {
// 		double key = arr[i];
// 		int j = i - 1;
// 
// 		while (j >= 0 && arr[j] > key) {
// 			arr[j + 1] = arr[j];
// 			j -= 1;
// 		}
// 		arr[j + 1] = key;
// 	}

	// odd or even element count
	double result = (n % 2 != 0) ? arr[n / 2] : (arr[(n - 1) / 2] + arr[n / 2]) / 2.0;
	return result;
}
