/*
 * Scott Cooper
 * CS 362 - Assignment 3
 * unittest1.c - updateCoins()
 */

/*
 * Include the following to your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *       gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLSGS)
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
#define TESTFUNCTION "updateCoins()"

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
    int i, player, handCount;
    int seed = 2000;
    int numPlayers = 2;
    int bonus, maxBonus = 5;
    int maxHandCount = 10;
    int expectedCoins, newCoins;
    int totalTests = 0, passedTests = 0;
    struct gameState G;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy, council_room};

    int coppers[maxHandCount], silvers[maxHandCount], golds[maxHandCount];
    //fill each hand with all of said treasure
    for( i = 0; i < maxHandCount; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
    
    printf("--------------Testing Function: %s--------------\n", TESTFUNCTION);
    
    //loop through all players
    for( player = 0; player < numPlayers; player++)
    {
        //loop through all different handcounts
        for(handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for( bonus = 0; bonus < maxBonus; bonus++)
            {
                //set up gamestate
                printf("\nPlayer#: %d\tTreasureCards: %d\tBonus: %d\n", player+1, handCount, bonus);
                memset(&G, 23, sizeof(struct gameState)); //clear the memory of game state
                initializeGame(numPlayers, k, seed, &G); // initialize a new game
                G.handCount[player] = handCount;    //set the hand count
                
                //Copper Coins
                memcpy(G.hand[player], coppers, sizeof(int) * handCount);
                printf("\nCopper Coins");
                expectedCoins = 1*handCount + bonus;
                printf("\n Expected: %d", expectedCoins);
                updateCoins(player, &G, bonus);
                newCoins = G.coins;
                printf("\n Actual: %d", newCoins);
                passedTests += assertTrue(expectedCoins == newCoins);
                totalTests++;
                
                //Silver Coins
                memcpy(G.hand[player], silvers, sizeof(int) * handCount);
                printf("\nSilver Coins");
                expectedCoins = 2*handCount + bonus;
                printf("\n Expected: %d", expectedCoins);
                updateCoins(player, &G, bonus);
                newCoins = G.coins;
                printf("\n Actual: %d", newCoins);
                passedTests += assertTrue(expectedCoins == newCoins);
                totalTests++;
                
                //Gold Coins
                memcpy(G.hand[player], golds, sizeof(int) * handCount);
                printf("\nGold Coins");
                expectedCoins = 3*handCount + bonus;
                printf("\n Expected: %d", expectedCoins);
                updateCoins(player, &G, bonus);
                newCoins = G.coins;
                printf("\n Actual: %d", newCoins);
                passedTests += assertTrue(expectedCoins == newCoins);
                totalTests++;
                
            }//bonus loop
            
        }//hancount loop
        
    } //players loop
       
    // End of Testing Results
    printf("\nPassed Tests: %d:%d\n", passedTests, totalTests);
    if( passedTests/totalTests)
        printf("\n>>>>> SUCCESS: Testing Complete %s <<<<<\n\n", TESTFUNCTION);
    else
        printf("\n>>>>> FAILURE: Testing Complete %s <<<<<\n\n", TESTFUNCTION);
    
    
    
}