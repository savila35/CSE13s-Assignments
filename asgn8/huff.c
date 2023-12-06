#include "bitreader.h"
#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <stdio.h>
#include <unistd.h>

#define OPTIONS "hi:o:"
#define USAGE   "Usage: huff -i infile -o outfile\n       huff -h\n"

typedef struct Code {
    uint64_t code;
    uint8_t code_length;
} Code;

uint32_t fill_histogram(FILE *fin, uint32_t *histogram) {
    uint32_t filesize = 0;
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }
    ++histogram[0];
    ++histogram[0xff];
    int byte;
    while ((byte = fgetc(fin)) != EOF) {
        ++histogram[byte];
        ++filesize;
    }
    return filesize;
}

Node *create_tree(uint32_t *histogram, uint16_t *num_leaves) {
    PriorityQueue *q = pq_create();
    for (int i = 0; i < 256; i++) {
        if (histogram[i] != 0) {
            Node *nd = node_create((uint8_t) i, histogram[i]);
            enqueue(q, nd);
            (*num_leaves)++;
        }
    }

    while (!pq_size_is_1(q)) {
        Node *left = dequeue(q);
        Node *right = dequeue(q);
        Node *node = node_create(0, left->weight + right->weight);
        node->left = left;
        node->right = right;
        enqueue(q, node);
    }
    Node *last = dequeue(q);
    pq_free(&q);
    return last;
}

void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length) {
    if (node->left != NULL) {
        fill_code_table(code_table, node->left, code, code_length + 1);
        code |= (uint64_t) 1 << code_length;
        fill_code_table(code_table, node->right, code, code_length + 1);
    } else {
        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
    if (node->left == NULL) {
        bit_write_bit(outbuf, 1);
        bit_write_uint8(outbuf, node->symbol);
    } else {
        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, 0);
    }
}

void huff_compress_file(BitWriter *outbuf, FILE *fin, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table) {
    bit_write_uint8(outbuf, 'H');
    bit_write_uint8(outbuf, 'C');
    bit_write_uint32(outbuf, filesize);
    bit_write_uint16(outbuf, num_leaves);
    huff_write_tree(outbuf, code_tree);
    while (1) {
        int b = fgetc(fin);
        if (b == EOF) {
            break;
        }
        uint64_t code = code_table[b].code;
        uint8_t code_length = code_table[b].code_length;
        for (int i = 0; i < code_length; i++) {
            bit_write_bit(outbuf, (code & 1));
            code >>= 1;
        }
    }
}

int main(int argc, char **argv) {
    FILE *fin = NULL;
    char *fout = NULL;

    int opt;
    opterr = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': printf(USAGE); return 0;
        case 'i':
            fin = fopen(optarg, "rb");
            if (fin == NULL) {
                fprintf(stderr, "huff:  error reading input file %s\n", optarg);
                fprintf(stderr, USAGE);
                return 1;
            }
            break;
        case 'o':
            fout = optarg;
            if (fout == NULL) {
                fprintf(stderr, "huff:  error opening output file %s\n", optarg);
                fprintf(stderr, USAGE);
                return 1;
            }
            break;

        default:
            fprintf(stderr, "huff:  unknown or poorly formatted option -%c\n", optopt);
            fprintf(stderr, USAGE);
            return 1;
        }
    }

    if (fin == NULL) {
        fprintf(stderr, "huff:  -i option is required\n");
        fprintf(stderr, USAGE);
        return 1;
    }
    if (fout == NULL) {
        fprintf(stderr, "huff:  -o option is required\n");
        fprintf(stderr, USAGE);
        return 1;
    }

    uint32_t histogram[256] = { 0 };
    uint32_t filesize = fill_histogram(fin, histogram);
    uint16_t num_leaves = 0;
    Node *tree = create_tree(histogram, &num_leaves);

    Code code_table[256];
    fill_code_table(code_table, tree, 0, 0);

    BitWriter *outbuf = bit_write_open(fout);

    fseek(fin, 0, SEEK_SET);
    huff_compress_file(outbuf, fin, filesize, num_leaves, tree, code_table);

    fclose(fin);
    node_free(&tree);
    bit_write_close(&outbuf);
    return 0;
}
