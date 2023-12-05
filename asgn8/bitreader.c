#include "bitreader.h"

#include <stdio.h>
#include <stdlib.h>

struct BitReader {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitReader *bit_read_open(const char *filename) {
    BitReader *br = (BitReader *) malloc(sizeof(BitReader));
    if (br == NULL) {
        return NULL;
    }
    br->underlying_stream = fopen(filename, "rb");
    if (br->underlying_stream == NULL) {
        free(br);
        br = NULL;
        return NULL;
    }
    br->byte = 0;
    br->bit_position = 8;
    return br;
}

void bit_read_close(BitReader **pbuf) {
    if (*pbuf != NULL) {
        if (fclose((*pbuf)->underlying_stream) == EOF) {
            fprintf(stderr, "error closing buffer\n");
            exit(1);
        }
        free(*pbuf);
        *pbuf = NULL;
    }
}

uint8_t bit_read_bit(BitReader *buf) {
    if (buf->bit_position > 7) {
        int t = fgetc(buf->underlying_stream);
        if (t == EOF) {
            fprintf(stderr, "error reading from buffer\n");
            exit(1);
        }
        buf->byte = (uint8_t) t;
        buf->bit_position = 0;
    }
    uint8_t bit = 1 & (buf->byte >> buf->bit_position);
    buf->bit_position++;
    return bit;
}

uint8_t bit_read_uint8(BitReader *buf) {
    uint8_t byte = 0;
    for (int i = 0; i < 8; i++) {
        byte |= (uint8_t) (bit_read_bit(buf) << i);
    }
    return byte;
}

uint16_t bit_read_uint16(BitReader *buf) {
    uint16_t byte = 0;
    for (int i = 0; i < 16; i++) {
        byte |= (uint16_t) (bit_read_bit(buf) << i);
    }
    return byte;
}

uint32_t bit_read_uint32(BitReader *buf) {
    uint32_t byte = 0;
    for (int i = 0; i < 32; i++) {
        byte |= (uint32_t) (bit_read_bit(buf) << i);
    }
    return byte;
}
