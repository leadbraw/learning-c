#include <stdio.h>

// These definitions are for fahrenheit.c
int convertToF_int(int);
double convertToF(double);

// Print celsius vs fahrenheit in increments of 10, 10-100. compares int and double math.
int main(void) {
	printf("Celsius to Fahrenheit (int)\n");
	for (int i = 1; i <= 10; i++) {
		printf("Celsius: %d    Fahrenheit: %d\n", i * 10, convertToF_int(i*10));
	}
	printf("Celsius to Fahrenheit (double)\n");
	for (int i = 1; i <= 10; i++) {
		printf("Celsius: %f    Fahrenheit: %f\n", i * 10.0, convertToF(i*10));
	}

	return 0;
}
