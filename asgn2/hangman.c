#include "hangman_helpers.h"

#include <stdio.h>

int main(int argc, char **argv) {

    // check for correct arguments
    if (argc != 2) {
        printf("wrong number of arguments\n");
        printf("usage: %s <secret word or phrase>\n", argv[0]);
        printf("if the secret is multiple words, you must quote it\n");
        exit(1);
    }

    if (!validate_secret(argv[1])) {
        return 0;
    }

    unsigned long len = strlen(argv[1]); // length of secret phrase

    int guessed[len]; // list of bools: true if letter at index guessed
    for (unsigned long i = 0; i < len; i++) {
        if (string_contains_character(punctuation, argv[1][i])) {
            guessed[i] = 1;
        } else {
            guessed[i] = 0;
        }
    }

    int mistakes = 0; // mistake counter

    int eliminated[26] = { 0 }; // list of bools w/ len of alphabet: true if letter eliminated
    int elim_index = 0;

    char guess = ' ';
    int valid_guess = 0;

    // game loop
    while (mistakes < LOSING_MISTAKE && !all_letters_guessed(guessed, len)) {

        print_screen(mistakes, guessed, len, argv[1], eliminated);

        do {
            do {
                if (guess != '\n') {
                    printf("Guess a letter: ");
                }
                guess = read_letter();
            } while (!is_lowercase_letter(guess));

            if (!string_contains_character(argv[1], guess)) {
                elim_index = guess - 97;
                if (eliminated[elim_index]) {
                    valid_guess = 0;
                    continue;
                } else {
                    eliminated[elim_index] = 1;
                    mistakes++;
                    valid_guess = 1;
                }
            } else {
                valid_guess = 1;
                for (unsigned long i = 0; i < len; i++) {
                    if (guess == argv[1][i]) {
                        if (guessed[i] == 1) {
                            valid_guess = 0;
                            continue;
                        } else {
                            guessed[i] = 1;
                        }
                    }
                }
            }
        } while (!valid_guess);
    }
    if (mistakes >= LOSING_MISTAKE) {
        print_screen(mistakes, guessed, len, argv[1], eliminated);
        printf("You lose! The secret phrase was: %s\n", argv[1]);
    } else {
        print_screen(mistakes, guessed, len, argv[1], eliminated);
        printf("You win! The secret phrase was: %s\n", argv[1]);
    }

    return 0;
}
