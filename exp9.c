#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
	int n, frames;
	int ref[15];
	int i;
	printf("Enter length of the reference string: ");
	scanf("%d", &n);
	printf("Enter the no. of frames: ");
	scanf("%d", &frames);
	srand(time(0));
	for(i=0;i<n;i++){
		ref[i]=rand()%10;
	}
	printf("Reference String: ");
	for(i=0;i<n;i++){
		printf("%d ", ref[i]);
	}
	//FIFO
	//LRU
	// Optimal
	return 0;	
}
