#include "names.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {

    /* Create a new type called "Position"
	 * enum defines constants SIDE, RAZORBACK, etc.
	 * where SIDE == 0, RAZORBACK == 1, etc.
	 */
    typedef enum { SIDE = 0, RAZORBACK = 10, TROTTER = 10, SNOUTER = 15, JOWLER = 5 } Position;
    // define const array pig
    const Position pig[7] = {
        SIDE,
        SIDE,
        RAZORBACK,
        TROTTER,
        SNOUTER,
        JOWLER,
        JOWLER,
    };

    // prompt and set num of players
    int num_players = 2;
    printf("Number of players (2 to 10)? ");
    int scanf_result = scanf("%d", &num_players);
    //validate range of input
    if (scanf_result < 1 || num_players < 2 || num_players > 10) {
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        num_players = 2;
    }

    // prompt and set seed
    unsigned seed = 2023;
    printf("Random-number seed? ");
    scanf_result = scanf("%u", &seed);
    // validate seed
    if (scanf_result < 1) {
        fprintf(stderr, "Invalid seed. Using 2023 instead.\n");
        seed = 2023;
    }
    srandom(seed);

    //set player scores in array
    int player_scores[num_players];
    for (int i = 0; i < num_players; ++i) {
        player_scores[i] = 0;
    }

    //game loop
    int game_over = 0;
    int turn_over = 0;
    int roll = 0;
    while (!game_over) {
        for (int j = 0; j < num_players; j++) { // go through players
            printf("%s\n", player_name[j]);
            turn_over = 0;
            while (!turn_over) { // turn loop
                roll = random() % 7;
                player_scores[j] += pig[roll];
                printf(" rolls %d, has %d\n", pig[roll], player_scores[j]);
                if (pig[roll] == SIDE) {
                    turn_over = 1;
                }
                if (player_scores[j] >= 100) {
                    printf("%s won!\n", player_name[j]);
                    turn_over = 1;
                    game_over = 1;
                    j = num_players;
                }
            }
        }
    }
    return 0;
}
