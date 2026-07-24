#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"

#define CAPACITY 10000

int main(int argc, char* argv[]) { 
	int medianFlag = 0;
	if (argc > 2) {
		fprintf(stderr, "too many arguments. try again\n");
		return 1;
	} else if ((argc == 2) && strcmp(argv[1], "--median") == 0) {
		medianFlag = 1;
	} else if (argc == 2) {
	    fprintf(stderr, "unknown argument, try again\n");
	}

	double arr[10000];
	char buff[128];
	int size = 0;

	while (fgets(buff, sizeof buff, stdin) != NULL) {
	    char* endptr;
		double n = strtod(buff, &endptr);
		if (endptr == buff) continue; // nothing got parsed, skip line
		if (size >= CAPACITY) {
		    fprintf(stderr, "too many numbers, max is %d\n", CAPACITY);
		    return 1;
		}
		arr[size++] = n;
	}

	if (size == 0) {
		printf("Nothing! Too bad!\n");
		return 0;
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
	if (medianFlag == 1) printf("median: %.3f\n", median(arr, size));
	printf("standard deviation: %.3f\n", stddevResult);
	return 0;
}
