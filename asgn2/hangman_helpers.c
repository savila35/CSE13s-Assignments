#include "hangman_helpers.h"

bool is_lowercase_letter(char c) {
    if (97 <= c && c <= 122) {
        return 1;
    }
    return 0;
}

bool validate_secret(const char *secret) {
    if (strlen(secret) > MAX_LENGTH) {
        printf("the secret phrase is over 256 characters");
	return 0;
    }
    while (*secret != '\0') {
        if ((97 > *secret || *secret > 122) && (*secret != 32 && *secret != 39 && *secret != 45)) {
            printf("invalid character: '%c'\n", *secret);
            printf("the secret phrase must contain only lowercase letters, spaces, hyphens, and "
                   "apostrophes\n");
	    return 0;
        }
        ++secret;
    }
    return 1;
}

bool string_contains_character(const char *s, char c) {
    while (*s != '\0') {
        if (c == *s) {
            return 1;
        }
        ++s;
    }
    return 0;
}

char read_letter(void) {
    char c = ' ';
    do {
        if (c != '\n') {
            printf("Guess a letter: ");
        }
        c = (char) getchar();
    } while (!is_lowercase_letter(c));
    return (char) c;
}

bool all_letters_guessed(int guessed[], unsigned long len) {
    int all_guessed = 1;
    for (unsigned long i = 0; i < len; i++) {
        if (!guessed[i]) {
            all_guessed = 0;
            return all_guessed;
        }
    }
    return all_guessed;
}

void print_screen(
    int mistakes, int guessed[], unsigned long len, const char *secret, int eliminated[]) {
    printf("%s", CLEAR_SCREEN);
    printf("%s\n\n", arts[mistakes]);
    printf("    Phrase: "); // print phrase
    for (unsigned long i = 0; i < len; i++) {
        if (guessed[i]) {
            printf("%c", *secret);
        } else {
            printf("_");
        }
        ++secret;
    }
    printf("\n");
    printf("Eliminated: ");
    for (int i = 0; i < 26; i++) {
        if (eliminated[i] == 1) {
            printf("%c", i + 97);
        }
    }
    printf("\n\n");
}
