#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <assert.h>
#include "rngs.h"
#include<stdio.h>


int main(){

int i;
int seed = 1000;
int numPlayer = 2; 
int maxBonus = 10;
int p, r, handCount;
int bonus;
int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
struct gameState G;
int maxHandCount = 5; 

int coppers[MAX_HAND];
int silvers[MAX_HAND];
int golds[MAX_HAND];


int errors = 0;

for (i=0; i < MAX_HAND; i++){
coppers[i] = copper;
silvers[i] = silver;
golds[i] = gold;
}//end for 

printf("Unit test 2: Minion\n");

for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
#if (NOISY_TEST == 1)
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
	


 
           }
        }
    

	int handPos, choice1, choice2, choice3;	
	int p0coin, p1coin, p0hand, p1hand;

	if (p == 1){
	printf("player 2 coin check\n");
	printf("Pre minion(): num actions: %d coins: %d handCount: %d\n", G.numActions, G.coins, G.handCount[p]);			
	p1coin = G.coins;
	p1hand = G.handCount[p];
	choice1 = 1;
	choice2 = 0;
	}
	if (p == 0){
	p0coin = G.coins;
	p0hand = G.handCount[p];
	printf("player1 hand check\n");
	printf("pre-minion() num actions: %d coins: %d handCount: %d\n", G.numActions, G.coins, G.handCount[p]);			
	choice1 = 0;
	choice2 = 1;
	}
		cardEffect(minion, choice1,  choice2, choice3, &G, handPos,&bonus);
	
	
	


	printf("post minion(): num actions: %d coins: %d handCount: %d\n", G.numActions, G.coins, G.handCount[p]);			

	if (p==1){
	if (G.numActions != 2){
	printf("player two: wrong number actions, expected 2, actual : %d\n", G.numActions);
	errors++;
	}
	if(G.coins != p1coin + 2){
	printf("player two: wrong number coins, expected %d, actual: %d\n", p1coin + 2, G.coins);
	errors++;
	}
	if(G.handCount[p] != p1hand){
	printf("player two: wrong number cards, expected 4, actual: %d\n", G.handCount[p]);
	errors++;	
	}

	}
	
	if (p==0){
	if (G.numActions != 2){
	printf("player one: wrong number actions, expected 2, actual : %d\n", G.numActions);
	errors++;
	}
	if(G.coins != p0coin ){
	printf("player one: wrong number coins, expected %d, actual: %d\n", p0coin , G.coins);
	errors++;
	}
	if(G.handCount[p] != 4){
	printf("player one: wrong number cards, expected 4, actual: %d\n", G.handCount[p]);
	errors++;	
	}

	}




}
	if(errors == 0){
    printf("All tests passed!\n");
	}
   return 0;

}

