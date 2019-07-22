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
int players[2]; 


for (i=0; i < MAX_HAND; i++){
coppers[i] = copper;
silvers[i] = silver;
golds[i] = gold;
}//end for 


int s0, s1, z = 0;

printf("Unit test 4: getWinners() \n");

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
		
        }
    
	if (p == 0){
	G.handCount[p] = handCount;
	memcpy(G.hand[p], coppers, sizeof(int) * handCount);
	
 

	updateCoins(p, &G, bonus); 
	s0 = scoreFor(p, &G);
	}	
	
	if (p == 1){
	G.handCount[p] = handCount;
	memcpy(G.hand[p], golds, sizeof(int) * handCount);
	updateCoins(p, &G, bonus); 
	s1 = scoreFor(p, &G);
	}	



}
	
	printf("Score P0: %d; Score P1: %d\n", s0, s1);
	
}












	if (errors == 0){

   printf("All tests passed!\n");
	}

    return 0;

}

