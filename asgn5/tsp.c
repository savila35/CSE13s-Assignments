#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "graph.h"
#include "stack.h"
#include "path.h"

#define OPTIONS "hdi:o:"

#define USAGE \
	"Usage: tsp [options]\n\n" \
	"-i infile    Specify the input file path containing the cities and edges\n" \
	"             of a graph. If not specified, the default input should be\n" \
	"             set as stdin.\n\n" \
	"-o outfile   Specify the output file path to print to. If not specified,\n" \
	"             the default output should be set as stdout.\n\n" \
	"-d           Specifies the graph to be directed.\n" \
	"-h           Prints out a help message describing the purpose of the\n" \
	"             graph and the command-line options it accepts, exiting the\n" \
	"             program afterwards.\n"


int main(int argc, char **argv) {
	bool directed = false;
	bool dash_i = false;
	bool dash_o = false;
	char *infile_name;
	char *outfile_name;

	int opt;
	while ((opt = getopt(argc, argv, OPTIONS)) != 1) {
		switch (opt) {
			case 'h': 
				printf(USAGE);
				return 0;
				break;
			case 'd':
				directed = true;
				break;
			case 'i':
				printf("%s\n", optarg);
				infile_name = optarg;
				dash_i = true;
				break;
			case 'o':
				outfile_name = optarg;
				dash_o = true;
				break;
			default: 
				printf("opt: %d, here\n", opt);
				fprintf(stderr, USAGE);
				return 1;
		}
	}
	(void) directed;
	(void) dash_i;	
	(void) dash_o;
	(void) infile_name;
	(void) outfile_name;	
	return 0;
}
