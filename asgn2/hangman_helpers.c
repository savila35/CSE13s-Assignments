#include "hangman_helpers.h"

bool is_lowercase_letter(char c) {
    if (97 < c && c < 122) {
        return 1;
    }
    return 0;
}

bool validate_secret(const char *secret) {
    if (strlen(secret) > MAX_LENGTH) {
        printf("the secret phrase is over 256 characters");
        exit(1);
    }
    while (*secret != '\0') {
        if ((97 > *secret || *secret > 122) && (*secret != 32 && *secret != 39 && *secret != 45)) {
            printf("invalid character: '%c'\n", *secret);
            printf("the secret phrase must contain only lowercase letters, spaces, hyphens, and "
                   "apostrophes\n");
            exit(1);
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
    printf("Guess a letter: ");
    int i = getchar();
    char c = (char) i;
    return c;
}
