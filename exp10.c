// #include<stdio.h>
// #include<stdlib.h>
// #include<time.h>
// #define s 10
// #define m 5000

// void SSTF(int req[], int head){
//     int visited[s]={0};
//     int total = 0;
//     for(int i=0; i<s; i++){
//         int min=10000, index = -1;
//         for(int j = 0; j<s; j++){
//             if(!visited[j]){
//                 int dist = abs(head-req[j]);
//                 if(dist<min){
//                     min =  dist;
//                     index = j;
//                 }
//             }
//         }
//         visited[index] = 1;
//         total += min;
//         head = req[index];
//     }
//     printf("SSTF Total Seek Time: %d\n", total);
// }

// void LOOK(int req[], int head){
//     int total = 0;
//     for (int i=0; i<s-1; i++){
//         for(int j=0; j<s-i-1; j++){
//             if(req[j]>req[j+1]){
//                 int temp = req[j];
//                 req[j] = req[j+1];
//                 req[j+1] = temp;
//             }
//         }
//     }
//     int i;
//     int pos;
//     for(i = 0; i < s; i++){
//         if(req[i] >= head){
//             pos = i;
//             break;
//         }
//     }

//     // move right
//     for(i = pos; i < s; i++){
//         total += abs(head - req[i]);
//         head = req[i];
//     }

//     // move left
//     for(i = pos - 1; i >= 0; i--){
//         total += abs(head - req[i]);
//         head = req[i];
//     }
//     printf("LOOK Total Seek Time: %d\n", total);
// }

// void CSCAN(int req[], int head){
//     int total = 0;
//     for(int i=0; i<s-1; i++){
//         for(int j=0; j<s-i-1; j++){
//             if(req[j]>req[j+1]){
//                 int temp = req[j];
//                 req[j] = req[j+1];
//                 req[j+1] = temp;
//             }
//         }
//     }
//     int i;
//     int pos;
//     for(i = 0; i < s; i++){
//         if(req[i] >= head){
//             pos = i;
//             break;
//         }
//     }
//     // move right
//     for(i = pos; i < s; i++){
//         total += abs(head - req[i]);
//         head = req[i];
//     }

//     // go to end
//     total += abs(head - (m - 1));

//     // jump to start
//     total += (m - 1);
//     head = 0;

//     // service remaining
//     for(i = 0; i < pos; i++){
//         total += abs(head - req[i]);
//         head = req[i];
//     }
//     printf("CSCAN Total Seek Time: %d\n", total);
// }

// int main(){
//     int r1[s], r2[s], r3[s], head;
//     srand(time(0));
//     for(int i=0; i<s; i++){
//         r1[i]= rand()%m;
//     }
//     //r1 for SSTF, r2 for LOOK, r3 for CSCAN
//     for(int i=0; i<s; i++){
//         r2[i]=r1[i];
//         r3[i]=r1[i];
//     }
//     printf("Request: ");
//     for(int i=0;i<s; i++){
//         printf("%d ", r1[i]);
//     }
//     printf("\n");
//     head= rand()%m;
//     printf("Initial Head: %d\n", head);
//     SSTF(r1,head);
//     LOOK(r2,head);
//     CSCAN(r3,head);
//     return 0;
// }










// #include<stdio.h>
// #include<stdlib.h>
// #include<time.h>
// #define s 10
// #define m 5000

// void SSTF(int req[], int head){
//     int visited[s]={0};
//     int total = 0;
//     for(int i=0; i<s; i++){
//         int min=10000, index = -1;
//         for(int j = 0; j<s; j++){
//             if(!visited[j]){
//                 int dist = abs(head-req[j]);
//                 if(dist<min){
//                     min =  dist;
//                     index = j;
//                 }
//             }
//         }
//         visited[index] = 1;
//         total += min;
//         head = req[index];
//     }
//     printf("SSTF Total Seek Time: %d\n", total);
// }

// void LOOK(int req[], int head){

//     printf("LOOK Total Seek Time: \n");
// }

// void CSCAN(int req[], int head){

//     printf("CSCAN Total Seek Time: \n");
// }

// int main(){
//     int r1[s], r2[s], r3[s], head;
//     //r1 for SSTF, r2 for LOOK, r3 for CSCAN
//     for(int i=0; i<s; i++){
//         r2[i]=r1[i];
//         r3[i]=r1[i];
//     }
//     srand(time(0));
//     for(int i=0; i<s; i++){
//         r1[i]= rand()%m;
//     }
//     printf("Request: ");
//     for(int i=0;i<s; i++){
//         printf("%d ", r1[i]);
//     }
//     printf("\n");
//     head= rand()%m;
//     printf("Initial Head: %d\n", head);
//     SSTF(r1,head);
//     LOOK(r2,head);
//     CSCAN(r3,head);
//     return 0;
// }

















// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// #define SIZE 10
// #define MAX 5000

// // Function to print requests
// void printRequests(int req[]) {
//     printf("Requests: ");
//     for (int i = 0; i < SIZE; i++)
//         printf("%d ", req[i]);
//     printf("\n");
// }

// // ---------------- SSTF ----------------
// void SSTF(int req[], int head) {
//     int visited[SIZE] = {0};
//     int total = 0;

//     for (int i = 0; i < SIZE; i++) {
//         int min = 10000, index = -1;

//         for (int j = 0; j < SIZE; j++) {
//             if (!visited[j]) {
//                 int dist = abs(head - req[j]);
//                 if (dist < min) {
//                     min = dist;
//                     index = j;
//                 }
//             }
//         }

//         visited[index] = 1;
//         total += min;
//         head = req[index];
//     }

//     printf("SSTF Total Head Movement = %d\n", total);
// }

// // ---------------- LOOK ----------------
// void LOOK(int req[], int head) {
//     int total = 0;

//     // sort requests
//     for (int i = 0; i < SIZE - 1; i++) {
//         for (int j = 0; j < SIZE - i - 1; j++) {
//             if (req[j] > req[j + 1]) {
//                 int temp = req[j];
//                 req[j] = req[j + 1];
//                 req[j + 1] = temp;
//             }
//         }
//     }

//     int i;
//     // move right first
//     for (i = 0; i < SIZE; i++) {
//         if (req[i] >= head) {
//             total += abs(head - req[i]);
//             head = req[i];
//         }
//     }

//     // then move left
//     for (i = SIZE - 1; i >= 0; i--) {
//         if (req[i] < head) {
//             total += abs(head - req[i]);
//             head = req[i];
//         }
//     }

//     printf("LOOK Total Head Movement = %d\n", total);
// }

// // ---------------- CSCAN ----------------
// void CSCAN(int req[], int head) {
//     int total = 0;

//     // sort requests
//     for (int i = 0; i < SIZE - 1; i++) {
//         for (int j = 0; j < SIZE - i - 1; j++) {
//             if (req[j] > req[j + 1]) {
//                 int temp = req[j];
//                 req[j] = req[j + 1];
//                 req[j + 1] = temp;
//             }
//         }
//     }

//     int i;

//     // move right
//     for (i = 0; i < SIZE; i++) {
//         if (req[i] >= head) {
//             total += abs(head - req[i]);
//             head = req[i];
//         }
//     }

//     // go to end (4999)
//     total += abs(head - (MAX - 1));
//     head = 0;

//     // service from beginning
//     for (i = 0; i < SIZE; i++) {
//         if (req[i] < head) {
//             total += abs(head - req[i]);
//             head = req[i];
//         }
//     }

//     printf("CSCAN Total Head Movement = %d\n", total);
// }

// // ---------------- MAIN ----------------
// int main() {
//     int req[SIZE];
//     int head;

//     printf("Enter initial head position: ");
//     scanf("%d", &head);

//     srand(time(0));

//     // generate random requests
//     for (int i = 0; i < SIZE; i++) {
//         req[i] = rand() % MAX;
//     }

//     printRequests(req);

//     SSTF(req, head);

//     // need separate copies because sorting changes array
//     int req2[SIZE], req3[SIZE];
//     for (int i = 0; i < SIZE; i++) {
//         req2[i] = req[i];
//         req3[i] = req[i];
//     }

//     LOOK(req2, head);
//     CSCAN(req3, head);

//     return 0;
// }
