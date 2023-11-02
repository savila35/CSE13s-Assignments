#include <stdio.h>

#include "stats.h"
#include "set.h"
#include "insert.h"
#include "shell.h"
#include "heap.h"
#include "quick.h"
#include "batcher.h"

#define OPTIONS "Hahbsqin:p:r:"

#define USAGE 											\
	"SYNOPSIS\n"										\
	"   A collection of comparison-base sorting algorithms.\n\n"				\
	"USAGE\n"										\
	"   ./%s [-Hahbsqi] [-n length] [-p elements] [-r seed]\n\n"				\
	"OPTIONS\n"										\
	"   -H              Display program help and usage.\n"					\
	"   -a              Enable all sorts.\n"						\
	"   -h              Enable Heap Sort.\n"						\
	"   -b              Enable Batcher Sort.\n"						\
	"   -s              Enable Shell Sort.\n"						\
	"   -q              Enable Quick Sort.\n"						\
	"   -i              Enable Insertion Sort.\n"						\
	"   -n length       Specify number of array elements (default: 100).\n"			\
	"   -p elements     Specify number of elements to print (default: 100).\n"		\
	"   -r seed         Specify random seed (default: 13371453).\n"				\
	
int main(int argc,char **argv) {
	int opt;
	while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
		switch (opt) {
			case "H": 
				printf(USAGE, argv[0]);
				return 0;
				break;
			case "a":
				break;
			case "h":
				break;
			case "b":
				break;
			case "s":
				break;
			case "q":
				break;
			case "i":
				break;
			case "n":
				break;
			case "p":
			case "r":
				break;
			default:
				print(USAGE, argv[0]);
				return 1;

	return 0;
}
