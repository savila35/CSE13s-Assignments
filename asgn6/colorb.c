#include "bmp.h"
#include "io.h"

#include <stdbool.h>
#include <unistd.h>

#define OPTIONS "hi:o:"
#define USAGE                                                                                      \
    "Usage: colorb -i infile -o outfile\n"                                                         \
    "       colorb -h\n"

int main(int argc, char **argv) {
    FILE *fin = NULL;
    FILE *fout = NULL;

    int opt;
    opterr = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': printf(USAGE); return 0;

        case 'i':
            fin = fopen(optarg, "rb");
            if (fin == NULL) {
                fprintf(stderr, "colorb:  error reading input file %s\n", optarg);
                return 1;
            }
            break;

        case 'o':
            fout = fopen(optarg, "wb");
            if (fout == NULL) {
                fprintf(stderr, "colorb:  error opening output file %s\n", optarg);
                return 1;
            }
            break;

        default:
            fprintf(stderr, "colorb:  unknown or poorly formatted option -%c\n", optopt);
            fprintf(stderr, USAGE);
            return 1;
        }
    }

    if (fin == NULL) {
        fprintf(stderr, "colorb:  -i option is required\n");
        fprintf(stderr, USAGE);
        return 1;
    }
    if (fout == NULL) {
        fprintf(stderr, "colorb:  -o option is required\n");
        fprintf(stderr, USAGE);
        return 1;
    }

    BMP *bmp = bmp_create(fin);
    fclose(fin);

    bmp_reduce_palette(bmp);

    bmp_write(bmp, fout);
    fclose(fout);

    bmp_free(&bmp);

    return 0;
}
