/*
 * Scott Cooper
 * CS 362 - Assignment 3
 * unittest2.c - numHandCards()
 */

/*
 * Include the following to your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *       gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLSGS)
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
#define TESTFUNCTION "numHandCards()"

int assertTrue( int value )
{
    if( value )
    {
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
        return 1;
    }
    else
        printf("\tTEST FAILED\n");
    return 0;
}

int main()
{
    int seed = 2000;
    int player, numPlayers = 2;
    int handcount, maxHandCount = 10;
    int playerHandSize;
    int totalTests = 0, passedTests = 0;

    struct gameState G;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy, council_room};
    
    // Initailiza a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    
    printf("--------------Testing Function: %s--------------\n", TESTFUNCTION);
    
    //Loop to determine if numHandCount works correctly
    for( player = 0; player < numPlayers; player++)
    {
        for(handcount = 1; handcount <= maxHandCount; handcount++)
        {
            printf("\nPlayer: %d\nExpected Handcount: %d", player+1, handcount);
            G.whoseTurn = player;
            G.handCount[player] = handcount;
            printf("\nPlayer's handcount: %d", G.handCount[player]);
            playerHandSize = numHandCards(&G);
            printf("\nHandcount: %d", playerHandSize);
            passedTests += assertTrue(handcount == playerHandSize);
            totalTests++;
        }// handcount loop
        
    }// player look
   
    // End of Testing Results
    printf("\nPassed Tests: %d:%d\n", passedTests, totalTests);
    if( passedTests/totalTests)
        printf("\n>>>>> SUCCESS: Testing Complete %s <<<<<\n", TESTFUNCTION);
    else
        printf("\n>>>>> FAILURE: Testing Complete %s <<<<<\n", TESTFUNCTION);
    
    return 0;
}
