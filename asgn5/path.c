#include "path.h"

#include <assert.h>
#include <stdlib.h>

struct path;
typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->vertices = stack_create(capacity);
    p->total_weight = 0;
    return p;
}

void path_free(Path **pp) {
    if (pp != NULL && *pp != NULL) {
        if ((*pp)->vertices) {
            stack_free(&(*pp)->vertices);
            (*pp)->vertices = NULL;
        }
        free(*pp);
    }
    if (pp != NULL) {
        *pp = NULL;
    }
}

uint32_t path_vertices(const Path *p) {
    uint32_t v = stack_size(p->vertices);
    return v;
}

uint32_t path_distance(const Path *p) {
    uint32_t d = p->total_weight;
    return d;
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    if (stack_empty(p->vertices)) {
        stack_push(p->vertices, val);
        return;
    }
    uint32_t start;
    stack_peek(p->vertices, &start);
    stack_push(p->vertices, val);
    p->total_weight += graph_get_weight(g, start, val);
}

uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t end;
    assert(stack_pop(p->vertices, &end));
    if (stack_size(p->vertices) <= 1) {
        p->total_weight = 0;
        return end;
    }
    uint32_t start;
    stack_peek(p->vertices, &start);
    p->total_weight -= graph_get_weight(g, start, end);
    return end;
}

void path_copy(Path *dst, const Path *src) {
    dst->total_weight = src->total_weight;
    stack_copy(dst->vertices, src->vertices);
}

void path_print(const Path *p, FILE *f, const Graph *g) {
    char **names = graph_get_names(g);
    uint32_t v;
    uint32_t l = stack_size(p->vertices);
    uint32_t *reverse = calloc(l, sizeof(uint32_t));
    int i = l - 1;
    while (stack_size(p->vertices) > 0) {
        assert(stack_pop(p->vertices, &v));
        reverse[i] = v;
        i--;
    }
    for (uint32_t j = 0; j < l; j++) {
        fprintf(f, "%s\n", names[reverse[j]]);
    }
    free(reverse);
}
