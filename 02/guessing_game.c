#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* User guesses a random number 1-100. Program prints higher/lower, tells them how many
attempts it took, then asks if they want to play again. */
int main(void) {
	srand((unsigned)time(NULL)); // seed rng
	char line[128];
	do {
		int number = rand() % 100 + 1; // 1-100 inclusive
		int guess = 0;
		int attempts = 0;
		while (guess != number) {
			printf("Guess the number (1-100): ");
			if (fgets(line, sizeof line, stdin) != NULL) {
				guess = (int) strtol(line, NULL, 10);
				attempts++;
				if (guess < number) {
					printf("Go higher!\n");
				} else if (guess > number) {
					printf("Go lower!\n");
				}
			} else {
				return 0; // EOF will cause infinite loop otherwise.
			}
		}
		printf("You got it! The magic number was %d, you got it in %d attempt(s)!\n", number, attempts);
		printf("Want to play again? (y/n): ");
		if (fgets(line, sizeof line, stdin) == NULL) break;
	} while (line[0] == 'y');
	return 0;
}
