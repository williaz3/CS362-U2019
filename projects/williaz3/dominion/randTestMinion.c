#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <assert.h>
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
int TESTCASE = 10;
int i;
int seed = 1000;
int numPlayer= 2;
//int p, r, handCount;
int k[10] ={ adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
struct gameState G;

int deckSize, handSize, handPos, bonus, choice1, choice2,choice3 = 0;
int actionsBefore1, actionsAfter1, deckBefore1, deckAfter1, handBefore1, handAfter1, discardBefore1, discardAfter1, coinsBefore1, coinsAfter1;
int deckBefore2, deckAfter2, handBefore2, handAfter2, discardBefore2, discardAfter2;

//int passed;
int testFailed, deckFailure, handFailure, coinFailure, actionFailure, discardFail, testPassed, testError, totError = 0;

srand(time(NULL));

for(i=0; i < TESTCASE; i++){
int coins =0;

memset(&G, 23, sizeof(struct gameState));
initializeGame(numPlayer, k , seed, &G);
deckSize = rand()% 40;
if (deckSize <= 7){
deckSize = 7; 
}

handSize = rand()% 7;

if (handSize == 0 ){
handSize = 1;
}
printf("-----------------------------------");
printf("\n");

G.coins = 0;
G.discardCount[0] = 0;
G.numActions = 1;
coinsBefore1 = G.coins;
discardBefore1 = G.discardCount[0];
actionsBefore1 = G.numActions;

choice1 = rand()%2; // set to either 0 or1 at random
if (choice1 == 0){
choice2 = 1;
}
if (choice1 == 1){
choice2 = 0;
}

printf("Choice1: gain2 coins, Choice 2: draw 4, other players with 4 or more cards discard adn draw 4\n");
printf("choice1: %d, choice2: %d\n", choice1, choice2);

G.deckCount[0] = deckSize - handSize;
G.handCount[0] = handSize;
handBefore1 = G.handCount[0];
deckBefore1 = G.deckCount[0];


//printf("player one:deck: %d, hand %d\n", G.deckCount[0], G.handCount[0]);

G.deckCount[1] = deckSize - handSize;
G.handCount[1] = handSize;
G.discardCount[1] = 0;

deckBefore2 = G.deckCount[1];
handBefore2 = G.handCount[1];
discardBefore2 = G.discardCount[1];

//printf("player two: deck: %d, hand %d\n", G.deckCount[1], G.handCount[1]);

/*
printf("pre-minion\n");
printf("actions1: %d\n", G.numActions);
printf("coins1: %d\n", G.coins);
printf("discarded1: %d\n", G.discardCount[0]);
printf("handsize1: %d\n", G.handCount[0]);
printf("\n");
printf("discarded2: %d\n", G.discardCount[1]);
printf("handsize2: %d\n", G.handCount[1]);
*/
cardEffect(minion, choice1, choice2, choice3, &G, handPos, &bonus);
//printf("player one: deck: %d, hand %d\n", G.deckCount[0], G.handCount[0]);
//printf("player two: deck: %d, hand %d\n", G.deckCount[1], G.handCount[1]);

coinsAfter1 = G.coins;
discardAfter1 = G.discardCount[0];
actionsAfter1 = G.numActions;
handAfter1= G.handCount[0];


deckAfter1 = G.deckCount[0];

discardAfter2 = G.discardCount[1];
handAfter2= G.handCount[1];
deckAfter2 = G.deckCount[1];

if (G.handCount[1] >= 5){
printf("Player2 has 5 or more cards in hand, should equal 4 after minion resolves\n");
}



/*
printf("after minion1: \n");
printf("actions1: %d\n", G.numActions);
printf("coins1: %d\n", G.coins);
printf("discarded1: %d\n", G.discardCount[0]);
printf("handsize1: %d\n", G.handCount[0]);
printf("\n");
printf("discarded2: %d\n", G.discardCount[1]);
printf("handsize2: %d\n", G.handCount[1]);
printf("-----------------------------------");
*/


/*
deckFailure, handFailure, discardFail, testPassed, totError = 0;

printf("Choice1: gain2 coins, Choice 2: draw 4, other players with 4 or more cards discard adn draw 4\n");
p

*/

if (choice1 ==1){
	if (actionsAfter1 != actionsBefore1 + 1){
	printf("Action Failure: Expected %d actual: %d\n", actionsBefore1 + 1, actionsAfter1);
	actionFailure++;
	}

	if (coinsAfter1 != coinsBefore1 + 2){
	printf("Coin failure: expected %d, actual %d\n", coinsBefore1 + 2, coinsAfter1);
	coinFailure++;	
	}

	if(deckBefore1 != deckAfter1){
	printf("Deck Error player 1: expected %d actual %d\n", deckBefore1, deckAfter1);
	deckFailure++;
	}

	if(handBefore1 != handAfter1){
	printf("hand error: player 1: expected %d actual: %d\n", handBefore1, handAfter1);
	handFailure++;
	}

	if(deckBefore2 != deckAfter2){
	printf("Deck Error: expected: %d actual: %d\n", deckBefore2, deckAfter2);
	deckFailure++;
	}
	if(handBefore2 != handAfter2){
	printf("hand error: player 2: expected %d actual: %d\n", handBefore2, handAfter2);
	handFailure++;
	}

testError = actionFailure + coinFailure + deckFailure + handFailure; 
//totError = totError + testError;

//printf("tst eror: %d, totError: %d\n", testError, totError);
/*	
if (testError == 0){
testPassed++;
}
else{
testFailed++;
}
*/

printf("Test REsults \n");	
if (testError == 0){
testPassed++;
printf("Succesful test\n");

}
else{
//testFailed++;
printf("Failed Test\n", testError);

}


printf("\n");
printf("-------------------------");
}

if (choice2 == 1){
	if (actionsAfter1 != actionsBefore1 + 1){
	printf("Action Failure: expected %d, actual: %d\n", actionsBefore1 +1, actionsAfter1);
	actionFailure++;
	}

	if (coinsAfter1 != coinsBefore1){
	printf("Coin failure: expected %d actual: %d\n", coinsBefore1, coinsAfter1);
	coinFailure++;	
	}

	if(deckAfter1 != deckBefore1 -4){
	printf("Deck Error player 1: expected %d, %d\n", deckBefore1 -4, deckAfter1);
	deckFailure++;
	}

	if( handAfter1 == 4){
	printf("hand error: player 1: expcted %d actual %d\n", 4, handAfter1);
	handFailure++;
	}

	//checks other player has more than 5 cards in hand before checking for errors
	if (handBefore2 >= 5){
	if(deckAfter2 != deckBefore2 -4 ){
	printf("player2: Deck Error: expected %d actual %d\n", deckBefore2- 4, deckAfter2);
	deckFailure++;
	}
	if(handAfter2 == 4){
	printf("hand error: player 2: expected %d, actual %d\n", 4, handAfter2);
	handFailure++;
	}
	}
	
	else{
	if(deckBefore2 != deckAfter2){
	printf("Deck Error player 2: expected %d actual %d\n", deckBefore2, deckAfter2);
	deckFailure++;
	}

	if( handAfter2 != handBefore2 ){
	printf("hand error: player 2: expected %d actual %d\n", handBefore2, handAfter2);
	handFailure++;
	}
	}


testError = actionFailure + coinFailure + deckFailure + handFailure; 
//totError = totError + testError;
//printf("tst eror: %d, totError: %d\n", testError, totError);


printf("Test REsults \n");	
if (testError == 0){
testPassed++;
printf("Succesful test\n");

}
else{
//testFailed++;
printf("Failed Test\n", testError);

}


printf("\n");
printf("-------------------------");




}
	
}//end for 

printf("\n\n");
return 0;

}//end main
