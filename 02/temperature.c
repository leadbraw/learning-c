#include <stdio.h>
int convertToF_int(int);
double convertToF(double);

int main(void) {
	printf("Celsius to Fahrenheit (int)\n");
	for (int i = 1; i <= 10; i++) {
		printf("Celsius: %d    Fahrenheit: %d\n", i * 10, convertToF_int(i*10));
	}
	printf("Celsius to Fahrenheit (double)\n");
	for (int i = 1; i <= 10; i++) {
		printf("Celsius: %f    Fahrenheit: %f\n", i * 10.0, convertToF(i*10));
	}
}
