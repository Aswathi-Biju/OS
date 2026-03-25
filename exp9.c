// #include<stdio.h>
// #include<stdlib.h>
// #include<time.h>
// #define n 10

// int fifo(int ref[], int f){
//     int frame[10], faults = 0, pos = 0;

//     for(int i=0; i<f; i++) frame[i] = -1;

//     for(int i=0; i<n; i++){
//         int found = 0;

//         for(int j=0; j<f; j++){
//             if(frame[j] == ref[i]) found = 1;
//         }

//         if(!found){
//             frame[pos] = ref[i];
//             pos = (pos + 1) % f;
//             faults++;
//         }
//     }
//     return faults;
// }

// int lru(int ref[], int f){
//     int frame[10], time[10], faults = 0, t = 0;

//     for(int i=0; i<f; i++){
//         frame[i] = -1;
//         time[i] = 0;
//     }

//     for(int i=0; i<n; i++){
//         int found = 0;

//         for(int j=0; j<f; j++){
//             if(frame[j] == ref[i]){
//                 t++;
//                 time[j] = t;
//                 found = 1;
//             }
//         }

//         if(!found){
//             int lru = 0;
//             for(int j=1; j<f; j++){
//                 if(time[j] < time[lru]) lru = j;
//             }

//             frame[lru] = ref[i];
//             t++;
//             time[lru] = t;
//             faults++;
//         }
//     }
//     return faults;
// }

// int optimal(int ref[], int f){
//     int frame[10], faults = 0;

//     for(int i=0; i<f; i++) frame[i] = -1;

//     for(int i=0; i<n; i++){
//         int found = 0;

//         for(int j=0; j<f; j++){
//             if(frame[j] == ref[i]) found = 1;
//         }

//         if(!found){
//             int pos = -1, far = i;

//             for(int j=0; j<f; j++){
//                 int k;
//                 for(k=i+1; k<n; k++){
//                     if(frame[j] == ref[k]) break;
//                 }

//                 if(k > far){
//                     far = k;
//                     pos = j;
//                 }
//             }

//             if(pos == -1) pos = 0;

//             frame[pos] = ref[i];
//             faults++;
//         }
//     }
//     return faults;
// }

// int main(){
//     int ref[n];
//     srand(time(0));
//     for(int i=0; i<n; i++){
//         ref[i] =  rand()%10;
//     }
//     printf("Reference String: ");
//     for(int i=0; i<n; i++){
//         printf("%d ", ref[i]);
//     }
//     printf("\n");
//     int f = (rand()%7)+1;
//     printf("Frame Size: %d\n", f);
//     printf("FIFO Faults: %d\n", fifo(ref,f));
//     printf("LRU Faults: %d\n", lru(ref,f));
//     printf("Optimal Faults: %d\n", optimal(ref,f));
//     return 0;
// }






// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// // FIFO
// int fifo(int pages[], int n, int f) {
//     int frames[10], faults = 0, pos = 0;

//     for (int i = 0; i < f; i++) frames[i] = -1;

//     for (int i = 0; i < n; i++) {
//         int found = 0;

//         for (int j = 0; j < f; j++) {
//             if (frames[j] == pages[i]) {
//                 found = 1;
//                 break;
//             }
//         }

//         if (!found) {
//             frames[pos] = pages[i];
//             pos = (pos + 1) % f;
//             faults++;
//         }
//     }
//     return faults;
// }

// // LRU
// int lru(int pages[], int n, int f) {
//     int frames[10], time[10], faults = 0;

//     for (int i = 0; i < f; i++) {
//         frames[i] = -1;
//         time[i] = -1;
//     }

//     for (int i = 0; i < n; i++) {
//         int found = 0;

//         for (int j = 0; j < f; j++) {
//             if (frames[j] == pages[i]) {
//                 time[j] = i;
//                 found = 1;
//                 break;
//             }
//         }

//         if (!found) {
//             int lru_index = 0;
//             for (int j = 1; j < f; j++) {
//                 if (time[j] < time[lru_index])
//                     lru_index = j;
//             }

//             frames[lru_index] = pages[i];
//             time[lru_index] = i;
//             faults++;
//         }
//     }
//     return faults;
// }

// // Optimal
// int optimal(int pages[], int n, int f) {
//     int frames[10], faults = 0;

//     for (int i = 0; i < f; i++) frames[i] = -1;

//     for (int i = 0; i < n; i++) {
//         int found = 0;

//         for (int j = 0; j < f; j++) {
//             if (frames[j] == pages[i]) {
//                 found = 1;
//                 break;
//             }
//         }

//         if (!found) {
//             int index = -1, farthest = -1;

//             for (int j = 0; j < f; j++) {
//                 int k;
//                 for (k = i + 1; k < n; k++) {
//                     if (frames[j] == pages[k])
//                         break;
//                 }

//                 if (k == n) {
//                     index = j;
//                     break;
//                 }

//                 if (k > farthest) {
//                     farthest = k;
//                     index = j;
//                 }
//             }

//             frames[index] = pages[i];
//             faults++;
//         }
//     }
//     return faults;
// }

// int main() {
//     int n, f;
//     int pages[100];

//     printf("Enter length of reference string: ");
//     scanf("%d", &n);

//     printf("Enter number of frames (1-7): ");
//     scanf("%d", &f);

//     srand(time(0));

//     printf("Reference string:\n");
//     for (int i = 0; i < n; i++) {
//         pages[i] = rand() % 10;
//         printf("%d ", pages[i]);
//     }

//     printf("\n");

//     printf("FIFO Page Faults: %d\n", fifo(pages, n, f));
//     printf("LRU Page Faults: %d\n", lru(pages, n, f));
//     printf("Optimal Page Faults: %d\n", optimal(pages, n, f));

//     return 0;
// }
// /*#include<stdio.h>
// #include<stdlib.h>
// #include<time.h>

// int main(){
// 	int n, frames;
// 	int ref[15];
// 	int i;
// 	printf("Enter length of the reference string: ");
// 	scanf("%d", &n);
// 	printf("Enter the no. of frames: ");
// 	scanf("%d", &frames);
// 	srand(time(0));
// 	for(i=0;i<n;i++){
// 		ref[i]=rand()%10;
// 	}
// 	printf("Reference String: ");
// 	for(i=0;i<n;i++){
// 		printf("%d ", ref[i]);
// 	}
// 	//FIFO
// 	//LRU
// 	// Optimal
// 	return 0;	
// }
// */
