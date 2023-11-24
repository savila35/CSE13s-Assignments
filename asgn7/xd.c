#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void print_binary(int num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num & (1 << i)));
    }
    printf(": ");
}

void print_hex(char *buffer, int len) {
    for (int i = 1; i <= len; i++) {
        printf("%02x", (unsigned char) buffer[i - 1]);
        if (i % 2 == 0) {
            printf(" ");
        }
    }
    printf(" ");
}

int main(int argc, char **argv) {
    if (argc > 2) {
        return 1;
    }

    int fdin = 0;

    if (argc == 2) {
        fdin = open(argv[1], O_RDONLY, 0);
        if (fdin == -1) {
            return 1;
        }
    }

    char buffer[17] = "";
    int res = read(fdin, &buffer, 16);
    int index = 0;
    while (1) {
        if (res == 0) {
            return 0;
        }
        if (res == 16) {
            print_binary(index);
            print_hex(buffer, 16);
            for (int i = 0; i < 16; i++) {
                if (32 > buffer[i] || buffer[i] > 126) {
                    buffer[i] = '.';
                }
            }
            printf("%s\n", buffer);
            memset(buffer, '\0', 16);
            res = 0;
            index++;
        }

        if (res == -1) {
            return 1;
        }

        int temp = read(fdin, buffer + res, 16 - res);
        if (temp == 0) {
            break;
        }
        res += temp;
    }

    print_binary(index);
    print_hex(buffer, res);
    for (int k = 1; k <= 16 - res; k++) {
        printf("  ");
        if (k % 2) {
            printf(" ");
        }
    }
    for (int j = 0; j < res; j++) {
        if (32 > buffer[j] || buffer[j] > 126) {
            buffer[j] = '.';
        }
    }
    printf("%s\n", buffer);
    return 0;
}
