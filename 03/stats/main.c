#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"

int main(int argc, char* argv[]) { 
	int medianFlag = 0;
	if (argc != 1 && argc > 2) {
		printf("too many arguments. try again\n");
		return 1;
	} else if ((argc == 2) && strcmp(argv[1], "--median") == 0) {
		medianFlag = 1;
	}

	double arr[10000];
	char buff[10000];
	int size = 0;

	while (fgets(buff, sizeof buff, stdin) != NULL) {
		double  n = strtol(buff, NULL, 10);   /* string to long, base 10 */
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
