#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int main(){

int i;
for (i=0; i < 10000; i++){

int n = (rand()%(93)) + 32; 
printf("n: %d\n", n);
}



return 0;
}
