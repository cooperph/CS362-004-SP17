/*
* Scott Cooper
* CS 362 - Assignment 4
* randomtestadventurer.c - Adventurer
*/

/*
* Include the following to your makefile:
*
* randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
*       gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLSGS)
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// set NOISY_TEST to 0 to remove the printfs from output
#define NOISY_TEST 1
// name of the card being tested
#define TESTCARD "Adventurer"

int main()
{
    int numPlayers = 2;
    int thisPlayer = 0;
    int seed;
    int numRuns = 100000;
    int i;
    int count;
    int maxHandSize = 10, minHandSize = 5;
    int tempHand[maxHandSize];
    int testFail = 0, testPass = 0;
    int tempFail = 0;
    
    //testing variables
    int treasureInHand = 0;
    int treasureInDeck = 0;
    int treasureInDiscard = 0;
    int totalTreasure;
    int GTotalCards;
    int testGTotalCards;
    
    //Random variables
    int randHandCards;
    int randDeckCards;
    int randDiscardCards;
    
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy, council_room}; //tribute
    
    // seed the random number generator
    srand( time(NULL) );
    seed = 1000;
    
    printf("\n-------- Random Test Card: %s ---------", TESTCARD);
    printf("\n1");
    
    for( i=0; i < numRuns; i++)
    {
printf("\nTEST NUMBER: %d", i+1);
        
        //initialize a gamestate
        //initializeGame(numPlayers, k, seed, &G);
        initializeGame(numPlayers, k, seed, &G);

        //Set up the number of cards in a players hand
        randHandCards = rand() % (maxHandSize - minHandSize + 1) + minHandSize;
        G.handCount[thisPlayer] = randHandCards;
        
        //fill the hand with random cards, adventurer in the first slot
        G.hand[thisPlayer][0] = adventurer;
        count = 0;

        //Set up the number of cards in a players deck
        randDeckCards = rand() % (maxHandSize - minHandSize + 1) + minHandSize;
        G.deckCount[thisPlayer] = randDeckCards;
        
        // set up the number of cards in a players discard pile
        randDiscardCards = rand() % (maxHandSize - minHandSize + 1) + minHandSize;
        G.discardCount[thisPlayer] = randDiscardCards;
        
        //total number of treasure cards in play and total card count from G
        totalTreasure = treasureInHand + treasureInDeck + treasureInDiscard;
        GTotalCards = G.handCount[thisPlayer] + G.deckCount[thisPlayer] + G.discardCount[thisPlayer];
        
        //Copy game state and play the card
        memcpy(&testG, &G, sizeof(struct gameState));
        playAdventurer(&G, thisPlayer);
        
        //get total card count of testG
        testGTotalCards = testG.handCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer];
        
        //totalCards are the same from before and after
        if(GTotalCards != testGTotalCards)
        {
            //test fail
            printf("\nFAIL: GCards: %d\ttestGCards: %d", GTotalCards, testGTotalCards);
            tempFail++;
        }
        
        //testG have 2 more treasures in hand
        // count to see that deckTresure + discardTreasure > 2
        if(treasureInDeck + treasureInDiscard >= 2)
        {
            if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + 1)
            {
                //test fail
                printf("\nFAIL: GHand: %d\t testGHand: %d", G.handCount[thisPlayer], testG.handCount[thisPlayer]);
                tempFail++;
            }
        }
        
        //no change to coins
        if(G.coins != testG.coins)
        {
            printf("\nFAIL: GCoins: %d\ttestGCoins: %d", G.coins, testG.coins);
            tempFail++;
        }
        
        if(tempFail)
        {
            testFail++;
            printf("\tFAILURE");
        }
        else
        {
            testPass++;
            printf("\tPASSED");
        }
        
    }// i < numRuns
    
    //output results
    printf("\nTotal Tests: %d\tPASSED: %d\tFAILED: %d\n", numRuns, testPass, testFail);
    
    return 0;
    
}

