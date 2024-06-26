#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void print_hex(char *buffer, long len) {
    for (int i = 1; i <= 16; i++) {
        if (i > len) {
            printf("  ");
        } else {
            printf("%02x", (unsigned char) buffer[i - 1]);
        }
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
    long res = read(fdin, &buffer, 16);
    int index = 0;
    while (1) {
        if (res == 0) {
            close(fdin);
            return 0;
        }
        if (res == 16) {
            printf("%08x: ", index);
            print_hex(buffer, 16);
            for (int i = 0; i < 16; i++) {
                if (32 > buffer[i] || buffer[i] > 126) {
                    buffer[i] = '.';
                }
            }
            printf("%s\n", buffer);
            memset(buffer, '\0', 16 * sizeof(char));
            res = 0;
            index += 16;
        }

        if (res == -1) {
            return 1;
        }

        long temp = read(fdin, buffer + res, 16 - (unsigned long) res);
        if (temp == 0) {
            break;
        }
        if (temp == -1) {
            return 1;
        }
        res += temp;
    }

    if (res > 0) {
        printf("%08x: ", index);
        print_hex(buffer, res);
        for (int j = 0; j < res; j++) {
            if (32 > buffer[j] || buffer[j] > 126) {
                buffer[j] = '.';
            }
        }
        printf("%s\n", buffer);
    }
    close(fdin);
    return 0;
}
