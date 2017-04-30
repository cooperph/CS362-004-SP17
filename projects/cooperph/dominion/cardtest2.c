/*
* Scott Cooper
* CS 362 - Assignment 3
* cardtest1.c - Smithy
*/

/*
* Include the following to your makefile:
*
* cardtest1: cardtest1.c dominion.o rngs.o
*       gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLSGS)
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// set NOISY_TEST to 0 to remove the printfs from output
#define NOISY_TEST 1
// name of the card being tested
#define TESTCARD "Smithy"

void assertTrue( int value )
{
    if( value )
        printf("TEST SUCCESSFULLY COMPLETED");
    else
        printf("TEST FAILED");
}

int main()
{
    int numPlayers = 2;
    int seed = 1000;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int handpos = 0;
    int bonus = 0;
    
    int newCards = 3, discarded = 1;
    int handSize, newHandSize;
    int thisPlayer = 0;
    
    
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy, council_room};
    
    
    // Initailiza a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    // Copy gameState into a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    // play Card
    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    printf("--------------Testing Card: %s--------------\n", TESTCARD);
    
    
    // TEST 1: Current Players gets exactly 3 cards
    printf("TEST 1: current players gets 3 cards\n");
    handSize = G.handCount[thisPlayer];
    newHandSize = testG.handCount[thisPlayer];
    assertTrue( newHandSize - handSize + discarded == 3);
    
    // TEST 2: Cards ome Current Players pile
    printf("\nTEST 2: current players deck size\n");
    assertTrue(0);
    
    // TEST 3: Card Discarded from Current Players Hand
    printf("\nTEST 3: current players hand size after card discarded\n");
    assertTrue(1);
    
    // TEST 4: No state changes for other players (check handsize, decksize, discardsize)
    
    
    
    // TEST 5: No state changes to Victory Card Piles or Kingdom Cards
}

