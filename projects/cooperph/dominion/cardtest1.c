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
    
    int newCards = 3, discarded = 1;
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
    newHandSize = testG.handCount[thisPlayer]+1;
    printf("Original Hand Size: %d\nNew Hand Size: %d\n", handSize, newHandSize);
    passedTests += assertTrue( newHandSize - handSize == newCards);
    totalTests++;
    
    // TEST 2: Cards from Current Players pile
    printf("\nTEST 2: current players deck size\n");
    deckSize = G.deckCount[thisPlayer];
    newDeckSize = testG.deckCount[thisPlayer];
    printf("Original Draw Pile Size: %d\nNew Draw Pile Size: %d\n", deckSize, newDeckSize);
    passedTests += assertTrue( deckSize - newDeckSize == newCards );
    totalTests++;
    
    // TEST 3: Card Discarded from Current Players Hand
    printf("\nTEST 3: Current Players Card Discarded\n");
    discardPileSize = G.handCount[thisPlayer];
    newDiscardPileSize = testG.handCount[thisPlayer];
    printf("Original Hand Size: %d\nNew Hand Size: %d\n", discardPileSize, newDiscardPileSize);
    passedTests += assertTrue(newDiscardPileSize - discardPileSize + discarded - newCards == 0);
    totalTests++;
    
    // TEST 4: No state changes for other players (check handsize, decksize, discardsize)
    printf("\nTEST 4: No State Chances For Other Players\n");
    while( nextPlayer < numPlayers)
    {
        //check handsize
        printf("\nHand Size: Player %d\n", nextPlayer);
        handSize = G.handCount[nextPlayer];
        newHandSize = testG.handCount[nextPlayer]+1;
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
    
    // TEST 5: No state changes to Victory Card Piles
    printf("\nTEST 5: No Changes to Victory Cards\n");
    victoryCards = G.supplyCount[estate]+G.supplyCount[duchy]+G.supplyCount[province];
    newVictoryCards = testG.supplyCount[estate]+testG.supplyCount[duchy]+testG.supplyCount[province];
    printf("\nVictory Cards Original Count: %d\n Victory Cards New Count%d\n", victoryCards, newVictoryCards);
    passedTests += assertTrue( victoryCards == newVictoryCards);
    totalTests++;
    
    // TEST 6: No state changes to Kingdom Cards Piles
    printf("\nTEST 6: No Changes to Kingdom Card Piles");
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

