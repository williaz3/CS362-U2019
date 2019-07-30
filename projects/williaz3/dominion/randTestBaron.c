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
int i, j;
int seed = 1000;
int numPlayer= 2;
//int p, r, handCount;
int k[10] ={ adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
struct gameState G;

int deckSize, handSize, discardCount, handPos, bonus, choice1, choice2,choice3 = 0;
int actionsBefore1, actionsAfter1, estateError, estateCount, buysBefore1, buysAfter1, deckBefore1, deckAfter1, handBefore1, handAfter1, discardBefore1, discardAfter1, coinsBefore1, coinsAfter1;

//int passed;
int testFailed, buyError, deckFailure, handFailure, coinFailure, actionFailure, discardFail, testPassed, testError, totError = 0;

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
printf("Test %d Results\n",i);


G.numBuys = 1;
buysBefore1 = G.numBuys;
G.coins = 0;
G.discardCount[0] = 0;
memset(G.discard[0], 0, sizeof(int) * discardCount);
G.numActions = 1;
coinsBefore1 = G.coins;


discardBefore1 = G.discardCount[0];
actionsBefore1 = G.numActions;



G.deckCount[0] = deckSize;
memset(G.deck[0], 0, sizeof(int) * deckSize);
G.handCount[0] = handSize;
memset(G.hand[0], 0, sizeof(int) * handSize);
handBefore1 = G.handCount[0];
deckBefore1 = G.deckCount[0];


//printf("player one:deck: %d, hand %d\n", G.deckCount[0], G.handCount[0]);


//G.hand[0][handSize];

int addEstate = 0;
addEstate = rand() % 2;
if (addEstate == 1){
G.hand[0][0]= estate;
//G.handCount[0] = G.handCount[0] + 1;
}

if (addEstate == 1){
printf("estate card in hand, hand should go down one and coins increase 4\n");
}
if(addEstate != 1){
printf("no estate in hand, hand should increase by one and # estates should be one\n");
}



printf("pre-minion\n");
printf("player one: deck: %d, hand %d\n", G.deckCount[0], G.handCount[0]);
printf("actions1: %d\n", G.numActions);
printf("coins1: %d\n", G.coins);
printf("discarded1: %d\n", G.discardCount[0]);
printf("handsize1: %d\n", G.handCount[0]);
printf("\n");

cardEffect(baron, choice1, choice2, choice3, &G, handPos, &bonus);

buysAfter1 = G.numBuys;
coinsAfter1 = G.coins;
discardAfter1 = G.discardCount[0];
actionsAfter1 = G.numActions;
handAfter1= G.handCount[0];
deckAfter1 = G.deckCount[0];


printf("after minion1: \n");
printf("actions1: %d\n", G.numActions);
printf("coins1: %d\n", G.coins);
printf("discarded1: %d\n", G.discardCount[0]);
printf("handsize1: %d\n", G.handCount[0]);
printf("\n");
printf("-----------------------------------\n");



/*
deckFailure, handFailure, discardFail, testPassed, totError = 0;

printf("Choice1: gain2 coins, Choice 2: draw 4, other players with 4 or more cards discard adn draw 4\n");
p

*/

if (addEstate == 1){
	if(buysAfter1 != buysBefore1 +1){
	printf("Buys Failed: Expected %d, actal %d\n", buysBefore1, buysAfter1);
	buyError++;
	}

	if (actionsAfter1 != actionsBefore1 ){
	printf("Action Failure: Expected %d actual: %d\n", actionsBefore1 , actionsAfter1);
	actionFailure++;
	}


	if (coinsAfter1 != coinsBefore1 + 4 ){
	printf("Coin failure: expected %d, actual %d\n", coinsBefore1 + 4, coinsAfter1);
	coinFailure++;	
	}

	if(deckBefore1 != deckAfter1){
	printf("Deck Error player 1: expected %d actual %d\n", deckBefore1, deckAfter1);
	deckFailure++;
	}

	if(handAfter1 != handBefore1 -1 ){
	printf("hand error: player 1: expected %d actual: %d\n", handBefore1 -1 , handAfter1 );
	handFailure++;
	}

	

testError = buyError + actionFailure + coinFailure + deckFailure + handFailure; 
}


else{

	if(buysAfter1 != buysBefore1 +1){
	printf("Buys Failed: Expected %d, actal %d\n", buysBefore1, buysAfter1);
	buyError++;
	}

	if (actionsAfter1 != actionsBefore1 ){
	printf("Action Failure: Expected %d actual: %d\n", actionsBefore1 , actionsAfter1);
	actionFailure++;
	}


	if (coinsAfter1 != coinsBefore1 ){
	printf("Coin failure: expected %d, actual %d\n", coinsBefore1 , coinsAfter1);
	coinFailure++;	
	}

	if(deckBefore1 != deckAfter1){
	printf("Deck Error player 1: expected %d actual %d\n", deckBefore1, deckAfter1);
	deckFailure++;
	}

	if(handBefore1 + 1 != handAfter1){
	printf("hand error: player 1: expected %d actual: %d\n", handBefore1 + 1, handAfter1);
	handFailure++;
	}

	
/*
	for (j= 0; j < handSize; j++){
		if (G.hand[j] == estate){
		estateCount++;
		}

	
	if (estateCount >= 1){
	printf("Estate Error: player1 should have drawn an estate card\n");
	estateError++;
	}
*/
testError = buyError +estateError + actionFailure + coinFailure + deckFailure + handFailure; 
//totError = totError + testError;
}
//printf("tst eror: %d, totError: %d\n", testError, totError);



printf("\n");
printf("-------------------------");



	
}//end for 

printf("\n\n");
return 0;

}//end main
