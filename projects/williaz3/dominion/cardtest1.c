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

printf("Unit test 1: initalizeGame()\n");
//initalize game w/ two players and test variables that would be asssigned
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
//error handling to check various values set by initlaize game based on # players: 2
	int errors = 0;

	if (G.supplyCount[curse] != 10){
		printf("Curse not set in initalizeGame()\n");
		errors++;
		} 
		if (G.supplyCount[estate] != 8){
		printf("Estate not  set in initalizeGame()\n");
		errors++;

		} 
		if (G.supplyCount[duchy] != 8){
		printf("Duchy not set in initalizeGame()\n");
		errors++;

		} 
		if (G.supplyCount[province] != 8){
		printf("Province not set in initalizeGame()\n");
		errors++;

		} 
		if (G.supplyCount[copper] != (60 - 7 * numPlayer)){
		printf("Copper not set in initalizeGame()\n");
		errors++;

		} 
		if (G.supplyCount[silver] != 40){
		printf("Silver not set in initalizeGame()\n");
		errors++;

		} 

		if (G.supplyCount[gold] != 30){
		printf("Gold not set in initalizeGame()\n");
		errors++;

		} 
	//print if no errors in two player initalized game
	if(errors == 0){
	printf("initalizeGame() w/ two players: success\n");
	}	



//Initlaize game with three players and test output
errors =0; //reset error counter for three person initialization
numPlayer =3; 
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
//error handiing if one of our values not set to expectations; prints error based on what value not set
	if (G.supplyCount[curse] != 20){
		printf("Curse not set in initalizeGame()\n");
		errors++;
		} 
		if (G.supplyCount[estate] != 12){
		printf("Estate not  set in initalizeGame()\n");
		errors++;

		} 
		if (G.supplyCount[duchy] != 12){
		printf("Duchy not set in initalizeGame()\n");
		errors++;

		} 
		if (G.supplyCount[province] != 12){
		printf("Province not set in initalizeGame()\n");
		errors++;

		} 
		if (G.supplyCount[copper] != (60 - 7 * numPlayer)){
		printf("Copper not set in initalizeGame()\n");
		errors++;

		} 
		if (G.supplyCount[silver] != 40){
		printf("Silver not set in initalizeGame()\n");
		errors++;

		} 

		if (G.supplyCount[gold] != 30){
		printf("Gold not set in initalizeGame()\n");
		errors++;

		} 
//if no errors in three person initalization, print message	
	if(errors == 0){
	printf("initalizeGame() w/ three players: success\n");
	}	
//If we had a perfect run print full success message
if (errors == 0){

   printf("All tests passed!\n");
	}
    return 0;

}

