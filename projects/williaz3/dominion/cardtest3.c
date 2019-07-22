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

printf("Unit test 3: endTurn()\n");
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
	printf("Two Player testing\n");
	int errors = 0;
	//checks gamestate to see # of players turn
	int whose = whoseTurn(&G);

	//printf("Whose: %d\n", whose);	
	
	//error handling to make sure endTurn goees off and returns the expected outcome 0
	int init = endTurn(&G);
	if (init != 0){
	printf("error inital run with endTurn()\n");
	errors++;
	}

	int whose2 = whoseTurn(&G);
	//printf("Whose: %d\n", whose2);	
	
	if (whose2 != whose +1){
	printf("endTurn error: plyaer expected: %d, actual: %d\n", whose2, whose);
	errors++;
	}
	printf("endTurn() player0 to player1: Success\n");

	whose = whose2;
	//printf("whose: %d\n", whose);
	//error handling to make sure endTurn goees off and returns the expected outcome 0
	init = endTurn(&G);
	if (init != 0){
	printf("error inital run with endTurn()\n");
	errors++;
	}

	whose2 = whoseTurn(&G);
	//printf("Whose: %d\n", whose2);	
	
	if (whose2 != whose - 1){
	printf("endTurn error: plyaer expected: %d, actual: %d\n", whose2, whose);
	errors++;
	}
	printf("endTurn() player1 to player0: Success\n");

/* ------------------------------------------------------------------------ */
//initlaize three player game
printf("Three player testing\n");
numPlayer = 3;
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
	 errors = 0;
	//checks gamestate to see # of players turn
	 
	//player 0 to 1
	whose = whoseTurn(&G);

	//printf("Whose: %d\n", whose);	
	
	//error handling to make sure endTurn goees off and returns the expected outcome 0
	init = endTurn(&G);
	if (init != 0){
	printf("error inital run with endTurn()\n");
	errors++;
	}

	whose2 = whoseTurn(&G);
	//printf("Whose: %d\n", whose2);	
	
	if (whose2 != whose +1){
	printf("endTurn error: plyaer expected: %d, actual: %d\n", whose2, whose);
	errors++;
	}
	printf("endTurn() player0 to player1: Success\n");


	//Player 1 to 2
	whose = whose2;
	//printf("whose: %d\n", whose);
	//error handling to make sure endTurn goees off and returns the expected outcome 0
	init = endTurn(&G);
	if (init != 0){
	printf("error inital run with endTurn()\n");
	errors++;
	}

	whose2 = whoseTurn(&G);
	//printf("Whose: %d\n", whose2);	
	
	if (whose2 != whose + 1){
	printf("endTurn error: plyaer expected: %d, actual: %d\n", whose2, whose);
	errors++;
	}
	printf("endTurn() player1 to player2: Success\n");


	//player 2 to 0
	whose = whose2;
	//printf("whose: %d\n", whose);
	//error handling to make sure endTurn goees off and returns the expected outcome 0
	init = endTurn(&G);
	if (init != 0){
	printf("error inital run with endTurn()\n");
	errors++;
	}

	whose2 = whoseTurn(&G);
	//printf("Whose: %d\n", whose2);	
	
	if (whose2 != 0){
	printf("endTurn error: plyaer expected: %d, actual: %d\n", whose2, whose);
	errors++;
	}
	printf("endTurn() player2 to player0: Success\n");

	//player 0 to 1
	whose = whose2;
	//printf("whose: %d\n", whose);
	//error handling to make sure endTurn goees off and returns the expected outcome 0
	init = endTurn(&G);
	if (init != 0){
	printf("error inital run with endTurn()\n");
	errors++;
	}

	whose2 = whoseTurn(&G);
	//printf("Whose: %d\n", whose2);	
	
	if (whose2 != whose + 1){
	printf("endTurn error: plyaer expected: %d, actual: %d\n", whose2, whose);
	errors++;
	}
	printf("endTurn() player0 to player1: Success\n");








	if (errors == 0){

   printf("All tests passed!\n");
	}
    return 0;

}

