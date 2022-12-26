#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main (void) {
	int arr[5];
	srand(time(0));

	for (int i = 0; i < 5; i++) {
		arr[i] = (rand()%100)+1;
		printf("%d \n", arr[i]);
	}
	return 0;
}