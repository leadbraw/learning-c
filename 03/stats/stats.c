#include "stats.h"
#include <float.h>
#include <math.h>

double mean(const double *arr, size_t n) {
    double sum = 0.0;
    for (size_t i = 0; i < n; i++) {
    	sum += arr[i];
	}
    return sum / (double)n; 
}

double minimum(const double *arr, size_t n) {
	double min = DBL_MAX;
	for (size_t i = 0; i < n; i++) {
		if (arr[i] < min) {
			min = arr[i];
		}
	}
	return min;
}

double maximum(const double *arr, size_t n) {
	double max = DBL_MIN;
	for (size_t i = 0; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
			
}

double stddev(const double *arr, size_t n, const double mean) {
	double squaredDiffSum = 0.0;
    for (size_t i = 0; i < n; i++) {
        double diff = arr[i] - mean;
        squaredDiffSum += diff * diff;
    }

    return sqrt(squaredDiffSum / n);
}
