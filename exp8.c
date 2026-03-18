#include<stdio.h>
int main(){
	int n,m,i,j,k;
	printf("Enter no. of processes: ");
	scanf("%d", &n);
	printf("Enter no. of recources: ");
	scanf("%d", &m);
	int alloc[10][10], max[10][10], need[10][10], avail[10];
	printf("Enter Allocation Matrix:\n");
	for(i = 0; i < n; i++) {
        	for(j = 0; j < m; j++) {
            	scanf("%d", &alloc[i][j]);
        	}
    	}
    	printf("Enter Maximum Matrix:\n");
	for(i = 0; i < n; i++) {
        	for(j = 0; j < m; j++) {
            		scanf("%d", &max[i][j]);
        	}
    	}
    	printf("Enter Available Matrix:\n");
        for(i = 0; i < m; i++) {
            scanf("%d", &avail[i]);
    	}
	for(i = 0; i < n; i++) {
        	for(j = 0; j < m; j++) {
            		need[i][j]=max[i][j] - alloc[i][j];
        	}
    	}
    	int finish[10]={0};
    	int safeseq[10];
    	int work[10];
    	for(i=0; i<m; i++){
    		work[i]= avail[i];
    	}
    	//if flag is 1 that means available needs to be updated
    	int count =0;
    	while(count<n){
    		int found = 0 ;
    		for(i=0;i<n;i++){
    		if(finish[i]==0){
    			int flag = 1;
    				
    			for(j=0; j<m;j++){
    				if(need[i][j]>work[j]){
    					flag=0;
    					break;
    				}
    			}
    			if(flag==1){
    				for(k=0; k<m; k++){
    					work[k]= work[k] + alloc[i][k];	
    				}
    				safeseq[count]=i;
    				count++;
    				finish[i]=1;
    				found=1;
    			}
    		}
    		}
    		if(found == 0) {
         		printf("\nSystem is not safe (Deadlock possible)\n");
        	}
    	}
    	printf("\nSystem is safe\nSafe sequence:\n");
        for(i=0;i<n;i++){
        	printf("P%d ", safeseq[i]);
        }
        printf("\n");
    	return 0;
}
