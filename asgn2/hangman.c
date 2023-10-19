#include <stdio.h>
#include "hangman_helpers.h"

int main(int argc, char **argv) {
    if (argc != 2) { // check for correct arguments
        printf("wrong number of arguments\n");
        printf("usage: %s <secret word or phrase>\n", argv[0]);
        printf("if the secret is multiple words, you must quote it\n");
        exit(1);
    }

    validate_secret(argv[1]);

    int game_over = 0;
    int mistakes = 0;
    int wrong_letters[26] = { 0 };
    int index = 0;

    int guessed[strlen(argv[1])];
    for (unsigned long i = 0; i < strlen(argv[1]); i++) {
        guessed[i] = 0;
    }

    while (!game_over) {
        printf("%s", CLEAR_SCREEN);
        printf("%s", arts[mistakes]);
        printf("\n\nPhrase: ");

        for (unsigned long j = 0; j < strlen(argv[1]); j++) {
            if (guessed[j] == 1 || string_contains_character(punctuation, *argv[1])) {
                printf("%c", argv[1][j]);
                fflush(stdout);
            } else {
                printf("_");
                fflush(stdout);
            }
        }

        printf("\n");

        printf("%c", *argv[1]);
        // print eliminated letters
        printf("Eliminated: ");
        fflush(stdout);
        for (int k = 0; k < 26; k++) {
            if (wrong_letters[k]) {
                printf("%c", k + 97);
            }
        }
        printf("\n");

        // this part is fucked
        int c;
        char guess = read_letter();
        while (97 > guess || guess > 122) {
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            guess = read_letter();
        }

        // check if guess in secret phrase
        if (!string_contains_character(argv[1], guess)) {
            index = guess - 97;
            wrong_letters[index] = 1;
            ++mistakes;
        } else {
            for (unsigned long t = 0; t < strlen(argv[1]); t++) {
                if (guess == argv[1][t]) {
                    printf("correct\n");
                    guessed[t] = 1;
                }
                printf("%c, %c, %d\n", guess, argv[1][t], guessed[t]);
            }
        }
        // if all guessed == 1 then winner
        // else if mistakes == losing mistake? then loser
    }

    return 0;
}
