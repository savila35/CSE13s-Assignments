#include "io.h"

#include <stdlib.h>

void read_uint8(FILE *fin, uint8_t *px) {
    int result = fgetc(fin);
    if (result == EOF) {
        fprintf(stderr, "error reading file\n");
        exit(1);
    }
    *px = (uint8_t) result;
}

void read_uint16(FILE *fin, uint16_t *px) {
    read_uint8(fin, (uint8_t *) px);
    uint16_t x;
    read_uint8(fin, (uint8_t *) &x);
    x = x << 8;
    *px = *px | x;
}

void read_uint32(FILE *fin, uint32_t *px) {
    read_uint16(fin, (uint16_t *) px);
    uint32_t x;
    read_uint16(fin, (uint16_t *) &x);
    x = x << 16;
    *px = *px | x;
}

void write_uint8(FILE *fout, uint8_t x) {
    int result = fputc(x, fout);
    if (result == EOF) {
        fprintf(stderr, "error writing file\n");
        exit(1);
    }
}

void write_uint16(FILE *fout, uint16_t x) {
    write_uint8(fout, (uint8_t) x);
    write_uint8(fout, x >> 8);
}

void write_uint32(FILE *fout, uint32_t x) {
    write_uint16(fout, (uint16_t) x);
    write_uint16(fout, x >> 16);
}
