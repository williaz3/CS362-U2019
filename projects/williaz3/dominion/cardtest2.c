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

for (i=0; i < MAX_HAND; i++){
coppers[i] = copper;
silvers[i] = silver;
golds[i] = gold;
}//end for 

printf("Unit test 2: shuffle()\n");
//initlaize two player game
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
    }
}

//set error handling and set starting values for deck count of player one(0) and two (1)
	int errors = 0;
	int d0 = G.deckCount[0];
	int d1 = G.deckCount[1];

	printf("pre-deck count p0: %d and p1: %d\n", d0, d1);
	//shuffle player one's deck	
	shuffle(0, &G);
	//if deck count off after shuffle print error
	if (d0 != G.deckCount[0]){
	printf("Deck count 0 not same after shuffle: expected %d \n", d0 + 1);
	errors++;
	}

	//shuffle player two's deck
	shuffle(1, &G);
	//if deck count off alfter shuffle, print error
	if (d1 != G.deckCount[1]){
	printf("Deck count 1 not same after shuffle: expected %d \n", d1 +1);
	errors++;
	}

	printf("post-deck count p0: %d and p1: %d\n", d0, d1);
	
//if no errors print success message
	if (errors == 0){

   printf("All tests passed!\n");
	}
    return 0;

}

