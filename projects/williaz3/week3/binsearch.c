#include <stdio.h>
#include <assert.h>
int binsearch(int a[], int n, int x){
int low = 0;
int high = n-1;
int mid;

while (low<= high){

mid = (low +high)/2;
if (a[mid] == x){
	return mid;
	}
else if (x < a[mid]){
	high = mid -1;
	}
else{
	low = mid +1;
	}
}

return -1;
}//end bin search


void test(){
int a[7] = {2, 4, 6, 8, 10, 12, 14 };
int e_i = binsearch(a, 7, 4);
assert(e_i == 1);
e_i = binsearch(a, 7,2);
assert(e_i == 0);
e_i = binsearch(a, 7, 10);
assert(e_i == 4);
e_i = binsearch(a, 7, 14);
assert(e_i == 6);
e_i = binsearch(a,7,28);
assert(e_i == -1);


}//end test

int main(){
test();
return 0;
}
