CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)


#########

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)


#all: playdom player 

#Added by me
unittestresults: unittestresults dominion.o rngs.o
	gcc -o unittest1 -g -lm dominion.c rngs.c unittest1.c $(CFLAGS)
	unittest1 >> unittestresults.out
	gcc -o unittest2 -g -lm dominion.c rngs.c unitest2.c $(CFLAGS)
	unittest2 >> unittestresults.out
	gcc -o unittest3 -g -lm dominion.c rngs.c unitest3.c $(CFLAGS)
	unittest3 >> unittestresults.out
	gcc -o unittest4 -g -lm dominion.c rngs.c unitest4.c $(CFLAGS)
	unittest4 >> unittestresults.out
	gcc -o unittest5 -g -lm dominion.c rngs.c unitest5.c $(CFLAGS)
	unittest51 >> unittestresults.out
	gcc -o cardtest1 -g -lm dominion.c rngs.c cardtest1.c $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcc -o cardtest2 -g -lm dominion.c rngs.c cardtest2.c $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcc -o cardtest3 -g -lm dominion.c rngs.c cardtest3.c $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcc -o cardtest4 -g -lm dominion.c rngs.c cardtest4.c $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcc -o cardtest5 -g -lm dominion.c rngs.c cardtest5.c $(CFLAGS)
	cardtest5 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

all: playdom player

#unittestresults:
#	gcc -o unittest1 -g -lm unittest1.c dominion.c rngs.c $(CFLAGS)
#	unittest1 >> unittestresults.out
#	gcov dominion.c -b >> unittestresults.out
#	cat dominion.c.gcov >> unittestresults.out

#end Section added by me





clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
