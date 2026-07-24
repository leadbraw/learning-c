#include <stdio.h>
#include <stdlib.h>
#include "stats.h"

int main(void) { 
	double arr[10000];
	char buff[10000];
	int size = 0;

	while (fgets(buff, sizeof buff, stdin) != NULL) {
		double  n = strtol(buff, NULL, 10);   /* string to long, base 10 */
		arr[size++] = n;
	}

	double min = minimum(arr, size);
	double max = maximum(arr, size);
	double meanResult = mean(arr, size);
	double stddevResult = stddev(arr, size, meanResult);
	printf("/=====| RESULTS |=====/\n");
	printf("size: %d\n", size);
	printf("minimum: %.3f\n", min);
	printf("maximum: %.3f\n", max);
	printf("mean: %.3f\n", meanResult);
	printf("standard deviation: %.3f\n", stddevResult);
	return 0;
}
