#include "bitreader.h"
#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <stdio.h>
#include <unistd.h>

#define OPTIONS "hi:o:"
#define USAGE   "Usage: dehuff -i infile -o outfile\n       dehuff -h\n"

void dehuff_decompress_file(FILE *fout, BitReader *inbuf) {
    Node *stack[64];
    int stack_top = -1;
    uint8_t type1 = bit_read_uint8(inbuf);
    uint8_t type2 = bit_read_uint8(inbuf);
    assert(type1 == 'H');
    assert(type2 == 'C');
    uint32_t filesize = bit_read_uint32(inbuf);
    uint16_t num_leaves = bit_read_uint16(inbuf);
    int num_nodes = 2 * num_leaves - 1;
    Node *node;
    for (int i = 0; i < num_nodes; i++) {
        uint8_t bit = bit_read_bit(inbuf);
        if (bit == 1) {
            uint8_t symbol = bit_read_uint8(inbuf);
            node = node_create(symbol, 0);
        } else {
            node = node_create(0, 0);
            node->right = stack[stack_top--];
            node->left = stack[stack_top--];
        }
        printf("stack top: %d\n", stack_top);
        stack[++stack_top] = node;
    }
    Node *code_tree = stack[stack_top--];
    for (uint32_t j = 0; j < filesize; j++) {
        node = code_tree;
        while (1) {
            uint8_t bit = bit_read_bit(inbuf);
            if (bit == 0) {
                node = node->left;
            } else {
                node = node->right;
            }
            if (node->left == NULL && node->right == NULL) {
                break;
            }
            fputc(node->symbol, fout);
        }
    }
}

int main(int argc, char **argv) {
    char *fin = NULL;
    FILE *fout = NULL;

    int opt;
    opterr = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': printf(USAGE); return 0;
        case 'i':
            fin = optarg;
            if (fin == NULL) {
                fprintf(stderr, "dehuff:  error reading input file %s\n", optarg);
                fprintf(stderr, USAGE);
                return 1;
            }
            break;
        case 'o':
            fout = fopen(optarg, "wb");
            if (fout == NULL) {
                fprintf(stderr, "dehuff:  error opening output file %s\n", optarg);
                fprintf(stderr, USAGE);
                return 1;
            }
            break;

        default:
            fprintf(stderr, "dehuff:  unknown or poorly formatted option -%c\n", optopt);
            fprintf(stderr, USAGE);
            return 1;
        }
    }

    if (fin == NULL) {
        fprintf(stderr, "dehuff:  -i option is required\n");
        fprintf(stderr, USAGE);
        return 1;
    }
    if (fout == NULL) {
        fprintf(stderr, "dehuff:  -o option is required\n");
        fprintf(stderr, USAGE);
        return 1;
    }

    BitReader *inbuf = bit_read_open(fin);
    dehuff_decompress_file(fout, inbuf);

    fclose(fout);
    bit_read_close(&inbuf);
    return 0;
}
