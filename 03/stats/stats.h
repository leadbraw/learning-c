#ifndef STATS_H
#define STATS_H

#include <stddef.h>   /* for size_t */

double mean(const double *arr, size_t n);
double minimum(const double *arr, size_t n);
double maximum(const double *arr, size_t n);
double stddev(const double *arr, size_t n, double mean);

#endif
