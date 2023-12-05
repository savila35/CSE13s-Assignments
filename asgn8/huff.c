#include "bitreader.h"
#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <stdio.h>

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
    return dequeue(q);
}

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;
    return 0;
}
