/*
 * Scott Cooper
 * CS 362 - Assignment 3
 * unittest2.c - buyCard()
 */

/*
 * Include the following to your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *       gcc -o unittest2 -g unittest1.c dominion.o rngs.o $(CFLSGS)
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
#define TESTFUNCTION "buyCard()"

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
    int numPlayers = 2;
    //int maxHandCount = 10;
    int playerHandSize, newPlayerHandSize;
    int totalTests = 0, passedTests = 0;
    int coinsCount, newCoinsCount;
    struct gameState G;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy, council_room};
    
    // Initailiza a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    
    printf("--------------Testing Function: %s--------------\n", TESTFUNCTION);
    
    G.coins = 6;
    
    //TEST 1: No buy rounds left
    printf("\nTest1: Not Enough Buy Rounds");
    G.numBuys = 0;
    //playerHandSize = numHandCards(&G);
    playerHandSize = G.discardCount[0];
    coinsCount = G.coins;
    buyCard( 7, &G);
    //newPlayerHandSize = numHandCards(&G);
    newPlayerHandSize = G.discardCount[0];
    newCoinsCount = G.coins;
    printf("\nOld Discard Count: %d\nNew Discard Count: %d", playerHandSize, newPlayerHandSize);
    printf("\nCoins: %d\nNew Coins: %d", coinsCount, newCoinsCount);
    passedTests += assertTrue(!(newPlayerHandSize-playerHandSize == 1));
    totalTests++;
    
    
    
    //TEST 2: Card is gone from pile
    printf("\nTest2: Card is not available");
    G.supplyCount[adventurer] = 0;
    G.numBuys = 1;
    //playerHandSize = numHandCards(&G);
    playerHandSize = G.discardCount[0];
    coinsCount = G.coins;
    buyCard( 7, &G);
    //newPlayerHandSize = numHandCards(&G);
    newPlayerHandSize = G.discardCount[0];
    newCoinsCount = G.coins;
    printf("\nOld Discard Count: %d\nNew Discard Count: %d", playerHandSize, newPlayerHandSize);
    printf("\nCoins: %d\nNew Coins: %d", coinsCount, newCoinsCount);;
    passedTests += assertTrue(!(newPlayerHandSize-playerHandSize == 1));
    totalTests++;
    
    
    //TEST 3: Not enough money
    printf("\nNot enough money to buy card");
    G.supplyCount[adventurer] = 5;
    G.coins = 4;
    //playerHandSize = numHandCards(&G);
    playerHandSize = G.discardCount[0];
    coinsCount = G.coins;
    buyCard( 7, &G);
    //newPlayerHandSize = numHandCards(&G);
    newPlayerHandSize = G.discardCount[0];
    newCoinsCount = G.coins;    printf("\nOld Discard Count: %d\nNew Discard Count: %d", playerHandSize, newPlayerHandSize);
    printf("\nCoins: %d\nNew Coins: %d", coinsCount, newCoinsCount);
    passedTests += assertTrue(!(newPlayerHandSize-playerHandSize == 1));
    totalTests++;
    
    
    
    //TEST 4: normal working order
    printf("\nNormal working order");
    G.coins = 6;
    //playerHandSize = numHandCards(&G);
    playerHandSize = G.discardCount[0];
    coinsCount = G.coins;
    buyCard( 7, &G);
    //newPlayerHandSize = numHandCards(&G);
    newPlayerHandSize = G.discardCount[0];
    newCoinsCount = G.coins;
    printf("\nOld Discard Count: %d\nNew Discard Count: %d", playerHandSize, newPlayerHandSize);
    printf("\nCoins: %d\nNew Coins: %d", coinsCount, newCoinsCount);
    passedTests += assertTrue((newPlayerHandSize-playerHandSize == 1));
    totalTests++;
    
    

    // End of Testing Results
    printf("\nPassed Tests: %d:%d\n", passedTests, totalTests);
    if( passedTests/totalTests)
        printf("\n>>>>> SUCCESS: Testing Complete %s <<<<<\n", TESTFUNCTION);
    else
        printf("\n>>>>> FAILURE: Testing Complete %s <<<<<\n", TESTFUNCTION);
    
    return 0;
}
