//B23CS1262
//Vedha Mahadevan
//Bankers Algorithm - 11.03.2025

#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define MAX 5

int available[MAX], max[MAX][MAX], allocation[MAX][MAX], need[MAX][MAX], safeseq[MAX];
int processes, resources;

void calculateNeed(){
	for(int i=0;i<processes;i++){
		for(int j=0;j<resources;j++){
			need[i][j]=max[i][j]-allocation[i][j];
		}
	}
}

int isSafe(){
	int work[MAX], finish[MAX]={0}, count=0;
	for(int i=0;i<resources;i++){
		work[i] = available[i];
	}
	while(count < processes){
		int found=0;
		for(int i=0;i<processes;i++){
			if(!finish[i]){
				int canAllocate = 1;
				for(int j=0;j<resources;j++){
					if(need[i][j] > work[j]){
						canAllocate=0;
						break;
					}
				}
				if (canAllocate){
					for(int j=0;j<resources;j++){
						work[j]+=allocation[i][j];
					}
					safeseq[count++]=i;
					finish[i]=1;
					found=1;
				}
			}
		}
			if(!found){
				return 0;
			}
		}
		printf("\nSafe Sequence : ");
		for(int i=0;i<processes;i++){
			printf("%d ",safeseq[i]);
		}
		printf("\n");
		return 1;
}
	

void requestResource(int pid){
	int request[MAX];
	printf("\nEnter Request for Resource R%d : ",pid);
	for(int i=0;i<resources;i++){
		scanf("%d",&request[i]);
	}
	for(int i=0;i<resources;i++){
		if(request[i]>need[pid][i] || request[i] > available[i]){
			printf("\nRequest cannot be granted\n");
			return;
		}
	}
		for(int i=0;i<resources;i++){
			available[i]-=request[i];
			allocation[pid][i]+=request[i];
			need[pid][i]-=request[i];
		}
		printf("\nChecking Safety\n");
			if(!isSafe()){
				printf("Not Safe");
				for(int i=0;i<resources;i++){
					available[i]-=request[i];
					allocation[pid][i]+=request[i];
					need[pid][i]+=request[i];
				}
			}
			else{
			printf("\nRequest Granted!!!\n");
	}
}

int main() {

	int choice;

	printf("Enter the number of Processes : ");
	scanf("%d",&processes);
	printf("\nEnter the number of Resources : ");
	scanf("%d",&resources);

	printf("\nEnter available resources : ");
	for(int i=0;i<resources;i++){
		scanf("%d",&available[i]);
	}
	
	printf("\nEnter the maximum resources for each process :\n");
	for(int i=0; i<processes ; i++){
		for(int j=0;j <resources; j++){
			scanf("%d", &max[i][j]);
		}
	}
	
	printf("\nEnter allocated resources for each process : \n");
	for(int i=0;i<processes;i++){
		for(int j=0;j<resources;j++){
			scanf("%d" ,&allocation[i][j]);
		}
	}
	
	calculateNeed();
	
	while(true){
		printf("\nMenu :\n");
		printf("1. Safety Algorithm\n");
		printf("2. Resource Request Algorithm\n");
		printf("3. Exit\n");
		
		printf("\nEnter choice : ");
		scanf("%d",&choice);
		
		if(choice==1){
			calculateNeed();
			if(!isSafe()){
				printf("System is in an unsafe state");
				return 0;
			}
		}
		
		else if(choice==2){
			int pid;
			printf("\nEnter process ID to request resources : ");
			scanf("%d",&pid);
			if( pid>=0 && pid < processes){
				requestResource(pid);
			}else{
				printf("Invalid Request!!");
			}
		}
	
		else if(choice==3){
			printf("\nExiting the Menu\n");
			break;
		}
		else{
			exit(0);
		}
	}

	return 0;
}

/* OUTPUT

Enter the number of Processes : 5

Enter the number of Resources : 3

Enter available resources : 3 2 2

Enter the maximum resources for each process :
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

Enter allocated resources for each process : 
0 1 0
2 0 0
3 0 2
2 1 1
0 2 2

Menu :
1. Safety Algorithm
2. Resource Request Algorithm
3. Exit

Enter choice : 1

Safe Sequence : 1 3 4 0 2 

Menu :
1. Safety Algorithm
2. Resource Request Algorithm
3. Exit

Enter choice : 2

Enter process ID to request resources : 1

Enter Request for Resource R1 : 1 0 2

Checking Safety

Safe Sequence : 1 3 4 0 2 

Request Granted!!!

Menu :
1. Safety Algorithm
2. Resource Request Algorithm
3. Exit

Enter choice : 3

Exiting the Menu

*/
