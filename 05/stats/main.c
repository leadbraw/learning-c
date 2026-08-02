#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"

/* rewriting the tool from 03 to not use a fix sized buffer. */

int main(int argc, char* argv[]) { 
	int medianFlag = 0;
	if (argc > 2) {
		fprintf(stderr, "too many arguments. try again\n");
		return 1;
	} else if ((argc == 2) && strcmp(argv[1], "--median") == 0) {
		medianFlag = 1;
	} else if (argc == 2) {
	    fprintf(stderr, "unknown argument, try again\n");
	    return 1;
	}
	
    int capacity = 31250;
	double *arr = malloc(capacity * sizeof *arr); // 5 doubles to handle one million
	assert(arr != NULL);
	char buff[128];
	int size = 0;

	while (fgets(buff, sizeof buff, stdin) != NULL) {
	    char* endptr;
		double n = strtod(buff, &endptr);
		if (endptr == buff) continue; // nothing got parsed, skip line
		if (size >= capacity) {
		    capacity *= 2;
		    double *tmp = realloc(arr, capacity * sizeof *arr);
		    assert(tmp != NULL);
		    arr = tmp;
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
	free(arr);
	arr = NULL; // good habit
	return 0;
}
