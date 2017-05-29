/*
* Scott Cooper
* CS 362 - Assignment 3
* cardtest4.c - Adventurer
*/

/*
* Include the following to your makefile:
*
* cardtest4: cardtest4.c dominion.o rngs.o
*       gcc -o cardtest4 -g cardtest1.c dominion.o rngs.o $(CFLSGS)
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
#define TESTCARD "Adventurer"

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
    int numPlayers = 2;
    int seed = 1000;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int handpos = 0;
    int bonus = 0;
    int i;
    
    int newCards = 2;
    int handSize, newHandSize;
    int deckSize, newDeckSize;
    int discardPileSize, newDiscardPileSize;
    
    int thisPlayer = 0;
    int nextPlayer = 1;
    
    int totalTests = 0, passedTests = 0;
    int nextPlayerTests = 0, nextPlayerTestsPassed = 0;
    int otherPlayersTestsPassed = 0;
    int victoryCards, newVictoryCards;
    int kingdomCards = 0, newKingdomCards = 0;
    int originalCoinCount, newCoinCount;
    
    
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy, council_room};
    
    
    // Initailiza a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    
    // Copy gameState into a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    // play Card
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    printf("--------------Testing Card: %s--------------\n", TESTCARD);
    
    
    // TEST 1: Current Players gets exactly 2 cards
    printf("TEST 1: current players gets 2 cards\n");
    handSize = numHandCards(&G);
    newHandSize = numHandCards(&testG);
    printf("Original Hand Size: %d\nNew Hand Size: %d\n", handSize, newHandSize);
    passedTests += assertTrue( newHandSize - handSize == newCards);
    totalTests++;
    
    // TEST #: Current Player Updated Coins
    printf("\nTEST 2: Curent Player Updated Coins\n");
    updateCoins(thisPlayer, &G, 0);
    originalCoinCount = G.coins;
    updateCoins(thisPlayer, &testG, 0);
    newCoinCount = testG.coins;
    printf("Original Coin Count: %d\nNewCoinCount: %d\n", originalCoinCount, newCoinCount);
    passedTests += assertTrue( newCoinCount > originalCoinCount);
    totalTests++;
    
    // TEST 4: No state changes for other players (check handsize, decksize, discardsize)
    printf("\nTEST 3: No State Chances For Other Players\n");
    while( nextPlayer < numPlayers)
    {
        //check handsize
        printf("\nHand Size: Player %d\n", nextPlayer);
        handSize = G.handCount[nextPlayer];
        newHandSize = testG.handCount[nextPlayer];
        printf("Original Hand Size: %d\nNew Hand Size: %d\n", handSize, newHandSize);
        nextPlayerTestsPassed += assertTrue(handSize == newHandSize);
        nextPlayerTests++;
        
        //check decksize
        printf("\nDeck Size: Player %d\n", nextPlayer);
        deckSize = G.deckCount[nextPlayer];
        newDeckSize = testG.deckCount[nextPlayer];
        printf("Original Draw Pile Size: %d\nNew Draw Pile Size: %d\n", deckSize, newDeckSize);
        nextPlayerTestsPassed += assertTrue(deckSize == newDeckSize);
        nextPlayerTests++;
        
        //check discard size
        printf("\nDiscard Size: Player %d\n", nextPlayer);
        discardPileSize = G.discardCount[nextPlayer];
        newDiscardPileSize = testG.discardCount[nextPlayer];
        printf("Original Discard Size: %d\nNew Discard Size: %d\n", discardPileSize, newDiscardPileSize);
        nextPlayerTestsPassed += assertTrue(discardPileSize == newDiscardPileSize);
        nextPlayerTests++;
        
        printf("\nPlayer %d\n", nextPlayer);
        otherPlayersTestsPassed += assertTrue(nextPlayerTestsPassed / nextPlayerTests);
        printf("\n");
        nextPlayer++;
    }
    printf("\nNo State Changes to Other Players\n");
    passedTests += assertTrue( otherPlayersTestsPassed/(numPlayers-1));
    totalTests++;
    
    // TEST 4: No state changes to Victory Card Piles
    printf("\nTEST 4: No Changes to Victory Cards\n");
    victoryCards = G.supplyCount[estate]+G.supplyCount[duchy]+G.supplyCount[province];
    newVictoryCards = testG.supplyCount[estate]+testG.supplyCount[duchy]+testG.supplyCount[province];
    printf("\nVictory Cards Original Count: %d\n Victory Cards New Count%d\n", victoryCards, newVictoryCards);
    passedTests += assertTrue( victoryCards == newVictoryCards);
    totalTests++;
    
    // TEST 5: No state changes to Kingdom Cards Piles
    printf("\nTEST 5: No Changes to Kingdom Card Piles");
    for(i = 0; i < 10; i++)
    {
        kingdomCards+= supplyCount(k[i], &G);
        newKingdomCards += supplyCount(k[i],&testG);
    }
    printf("\nKC Count: %d\nNew KC Count: %d\n", kingdomCards, newKingdomCards);
    passedTests += assertTrue( kingdomCards == newKingdomCards);
    totalTests++;
    
    
    // End of Testing Results
    printf("\nPassed Tests: %d:%d\n", passedTests, totalTests);
    if( passedTests/totalTests)
        printf("\n>>>>> SUCCESS: Testing Complete %s <<<<<\n", TESTCARD);
    else
        printf("\n>>>>> FAILURE: Testing Complete %s <<<<<\n", TESTCARD);
}

