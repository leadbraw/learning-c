#include "stats.h"
#include <math.h>

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

	// insertion sort. This takes me back.
	for (size_t i = 1; i < n; i++) {
		double key = arr[i];
		int j = i - 1;

		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j -= 1;
		}
		arr[j + 1] = key;
	}

	// odd or even element count
	double result = (n % 2 != 0) ? arr[n / 2] : (arr[(n - 1) / 2] + arr[n / 2]) / 2.0;
	return result;
}
