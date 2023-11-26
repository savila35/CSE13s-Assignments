#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#define X(x) printf("%08x: ", (int) x)
#define r(o) return o
void p(char *b, long l) {
    for (long i = 1; i <= 16; i++) {
        printf(i > l ? "  " : "%02x",(unsigned char) b[i - 1]), printf(i % 2 == 0 ? " " : "");
    }
    printf(" ");
    for (long j = 0; j < l; j++) {
        printf((32 > b[j] || b[j] > 126) ? "." : "%c", b[j]);
    }
    printf("\n");
}
int main(int c, char **v) {
    if (c > 2)
        r(1);
    int f = c == 2 ? open(v[1], O_RDONLY, 0) : 0;
    if (f == -1)
        r(1);
    char b[17] = "";
    long r = read(f, &b, 16), x = 0, t;
    while (1) {
        if (r == 0)
            break;
        if (r < 0)
            r(1);
        if (r == 16) {
            X(x), p(b, 16), r = 0, x += 16;
        }
        t = read(f, b + r, 16 - (size_t) r);
        if (t == 0)
            break;
        r += t;
    }
    if (r > 0) {
        X(x), p(b, r);
    }
    r(0);
}
