#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "hdi:o:"

#define USAGE                                                                                      \
    "Usage: tsp [options]\n\n"                                                                     \
    "-i infile    Specify the input file path containing the cities and edges\n"                   \
    "             of a graph. If not specified, the default input should be\n"                     \
    "             set as stdin.\n\n"                                                               \
    "-o outfile   Specify the output file path to print to. If not specified,\n"                   \
    "             the default output should be set as stdout.\n\n"                                 \
    "-d           Specifies the graph to be directed.\n"                                           \
    "-h           Prints out a help message describing the purpose of the\n"                       \
    "             graph and the command-line options it accepts, exiting the\n"                    \
    "             program afterwards.\n"

void dfs(Graph *g, Path *curr_path, uint32_t curr_vertex, Path *short_path) {
    graph_visit_vertex(g, curr_vertex);
    path_add(curr_path, curr_vertex, g);

    //check if visited every vertex
    if (path_vertices(curr_path) == graph_vertices(g)) {
        //check if edge from ending vertex back to start vertex(0)
        if (graph_get_weight(g, curr_vertex, START_VERTEX) == 0) {
            path_remove(curr_path, g);
            graph_unvisit_vertex(g, curr_vertex);
            return;
        }
        path_add(curr_path, START_VERTEX, g);

        if (path_distance(short_path) == 0) {
            path_copy(short_path, curr_path);
        }

        if (path_distance(curr_path) <= path_distance(short_path)) {
            path_copy(short_path, curr_path);
        }
        path_remove(curr_path, g);
        path_remove(curr_path, g);
        graph_unvisit_vertex(g, curr_vertex);

        return;
    }

    for (uint32_t i = 0; i < graph_vertices(g); i++) {
        if (graph_get_weight(g, curr_vertex, i) != 0) {
            if (!graph_visited(g, i)) {
                dfs(g, curr_path, i, short_path);
            }
        }
    }

    path_remove(curr_path, g);
    graph_unvisit_vertex(g, curr_vertex);
}

int main(int argc, char **argv) {
    bool directed = false;
    bool dash_i = false;
    bool dash_o = false;
    char *infile_name;
    char *outfile_name;

    int opt;
    opterr = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf(USAGE);
            return 0;
            break;
        case 'd': directed = true; break;
        case 'i':
            infile_name = optarg;
            dash_i = true;
            break;
        case 'o':
            outfile_name = optarg;
            dash_o = true;
            break;
        default:
            fprintf(stderr, "tsp:  unknown or poorly formatted option -%c\n", optopt);
            fprintf(stderr, USAGE);
            return 1;
        }
    }

    FILE *infile = stdin;
    if (dash_i) {
        infile = fopen(infile_name, "r");
        if (infile == NULL) {
            fprintf(stderr, "tsp:  error reading input file %s\n", infile_name);
            fprintf(stderr, USAGE);
            return 1;
        }
    }

    FILE *outfile = stdout;
    if (dash_o) {
        outfile = fopen(outfile_name, "w");
        if (outfile == NULL) {
            fprintf(stderr, "tsp:  error reading output file %s\n", outfile_name);
            return 1;
        }
    }

    uint32_t num_vertices;
    if (fscanf(infile, "%" PRId32, &num_vertices) != 1) {
        fprintf(stderr, "tsp:  error reading number of vertices\n");
        return 1;
    }

    Graph *g = graph_create(num_vertices, directed);

    char name[100];
    for (uint32_t i = 0; i < num_vertices; i++) {
        fgets(name, 100, infile);
        if (name[0] == '\n') {
            fgets(name, 100, infile);
        }

        unsigned long ln = strlen(name) - 1;
        if (name[ln] == '\n') {
            name[ln] = '\0';
        }
        graph_add_vertex(g, name, i);
    }

    uint32_t num_edges;
    if (fscanf(infile, "%" PRId32, &num_edges) != 1) {
        fprintf(stderr, "tsp:  error reading number of edges\n");
        return 1;
    }

    uint32_t start;
    uint32_t end;
    uint32_t weight;
    for (uint32_t j = 0; j < num_edges; j++) {
        if (fscanf(infile, "%d %d %d", &start, &end, &weight) != 3) {
            fprintf(stderr, "tsp:  error reading edge\n");
            return 1;
        }

        //	printf("adding weight[%d][%d}: %d\n", start,end,weight);
        graph_add_edge(g, start, end, weight);
    }

    Path *current_path = path_create(num_vertices + 1);
    Path *shortest_path = path_create(num_vertices + 1);

    dfs(g, current_path, START_VERTEX, shortest_path);

    if (path_distance(shortest_path) == 0) {
        fprintf(outfile, "No path found! Alissa is lost!\n");
        return 0;
    }

    fprintf(outfile, "Alissa starts at:\n");
    path_print(shortest_path, outfile, g);
    fprintf(outfile, "Total Distance: ");
    fprintf(outfile, "%" PRId32, path_distance(shortest_path));
    fprintf(outfile, "\n");

    path_free(&shortest_path);
    path_free(&current_path);
    graph_free(&g);

    fclose(infile);
    fclose(outfile);

    return 0;
}
