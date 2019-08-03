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
int i, j, rand1;
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
int action[i], treasure[i], victory[i];
for (i = 0; i < TESTCASE; i++){
action[i] = 0;
treasure[i] = 0;
victory[i] = 0;
}


for(i=0; i < TESTCASE; i++){

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


printf("Tribute: opponent reveals two cards off deck , \n for each action card revealed add two actions \n for each treasure add two coins, \n for each victory card draw two careds\n");

G.deckCount[0] = deckSize - handSize;
G.handCount[0] = handSize;
handBefore1 = G.handCount[0];
deckBefore1 = G.deckCount[0];


//printf("player one:deck: %d, hand %d\n", G.deckCount[0], G.handCount[0]);

G.deckCount[1] = deckSize - handSize;
G.handCount[1] = handSize;
G.discardCount[1] = 0;
memset(G.deck[1], 0, sizeof(int) * deckSize);
memset(G.hand[1], 0, sizeof(int) * handSize);

deckBefore2 = G.deckCount[1];
handBefore2 = G.handCount[1];
discardBefore2 = G.discardCount[1];


//int action, treasure, victory = 0;


for (j = 0; j < 2; j++){
/*
action[i] = 0;
victory[i] = 0;
treasure[i] =0;
*/
rand1 = rand() % 3;

//printf("rand = %d\n", rand1);

if (j == 0){
	if (rand1 == 0){
	G.deck[1][G.deckCount[1]-1] = estate;
	victory[i] +=  1;
	}	

	if (rand1 == 1){
	G.deck[1][G.deckCount[1]-1] = copper;
	treasure[i] += 1;
	}

	if (rand1 == 2){
	G.deck[1][G.deckCount[1]-1] = baron;
	action[i] += 1;
	}
}

if (j == 1){
	if (rand1 == 0){
	G.deck[1][G.deckCount[1]-2] = estate;
	victory[i] +=  1;
	}

	if (rand1 == 1){
	G.deck[1][G.deckCount[1]-2] = copper;
	treasure[i] += 1;
	}

	if (rand1 == 2){
	G.deck[1][G.deckCount[1]-2] = baron;
	action[i] += 1;
	}
}
}//end for

printf("#victory cards %d, #treasure cards %d, # action cards: %d\n", victory[i], treasure[i], action[i]);



//printf("player two: deck: %d, hand %d\n", G.deckCount[1], G.handCount[1]);


printf("pre-tribute\n");
printf("actions1: %d\n", G.numActions);
printf("coins1: %d\n", G.coins);
printf("discarded1: %d\n", G.discardCount[0]);
printf("handsize1: %d\n", G.handCount[0]);
printf("\n");
printf("discarded2: %d\n", G.discardCount[1]);
printf("handsize2: %d\n", G.handCount[1]);

cardEffect(tribute, choice1, choice2, choice3, &G, handPos, &bonus);
printf("player one: deck: %d, hand %d\n", G.deckCount[0], G.handCount[0]);
printf("player two: deck: %d, hand %d\n", G.deckCount[1], G.handCount[1]);

coinsAfter1 = G.coins;
discardAfter1 = G.discardCount[0];
actionsAfter1 = G.numActions;
handAfter1= G.handCount[0];
deckAfter1 = G.deckCount[0];

discardAfter2 = G.discardCount[1];
handAfter2= G.handCount[1];
deckAfter2 = G.deckCount[1];


printf("after minion1: \n");
printf("actions1: %d\n", G.numActions);
printf("coins1: %d\n", G.coins);
printf("discarded1: %d\n", G.discardCount[0]);
printf("handsize1: %d\n", G.handCount[0]);
printf("\n");
printf("discarded2: %d\n", G.discardCount[1]);
printf("handsize2: %d\n", G.handCount[1]);
printf("-----------------------------------\n");




	if (actionsAfter1 != actionsBefore1 +(2 * action[i])){
	printf("Action Failure: Expected %d actual: %d\n", actionsBefore1 + (2 * action[i]), actionsAfter1);
	actionFailure++;
	}

	if (coinsAfter1 != coinsBefore1 + (2 * treasure[i])){
	printf("Coin failure: expected %d, actual %d\n", coinsBefore1 + (2 * treasure[i]), coinsAfter1);
	coinFailure++;	
	}

	if(deckAfter1 != deckBefore1 - (2 * victory[i])){
	printf("Deck Error player 1: expected %d actual %d\n", deckBefore1 + (2 * victory[i]), deckAfter1);
	deckFailure++;
	}

	if(handAfter1 != handBefore1 + (2 * victory[i])){
	printf("hand error: player 1: expected %d actual: %d\n", handBefore1 + (2 * victory[i]), handAfter1);
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

printf("-------------------------");
}
//}


}//end for 



printf("\n\n");
return 0;

}//end main
