#include <unistd.h>
#include <stdio.h>
#include<limits.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGE 100

int isPageInFrames(int frames[], int page, int pageCount){
	
	for(int i=0; i<pageCount; i++){
		if(frames[i] == page){
			return i;
		}
	}
	return -1;
}

void fcfs(int pages[], int pageCount, int frameCount){
	
	int frames[MAX_FRAMES];
	int front=0;
	int pageFaults=0;

	for(int i=0; i<frameCount; i++){
		frames[i] = -1;
	}
	
	for(int i=0; i<pageCount; i++){
		if(isPageInFrames(frames,pages[i],frameCount)== -1){
			frames[front] = pages[i];
			printf("\nPage %d -> ",pages[i]);
			for(int j=0; j<frameCount; j++){
				printf("%d ",frames[j]);
			}
			front = (front+1)%frameCount;
			pageFaults++;
		}
		/*printf("\nPage %d -> ",pages[i]);
		
		for(int j=0; j<frameCount; j++){
			printf("%d ",frames[j]);
		}*/
	}
	
	printf("\n");
	
	printf("\nPage Faults : %d\n",pageFaults);	
}

void lru(int pages[], int pageCount, int frameCount){

	int frames[MAX_FRAMES], lastUsed[MAX_FRAMES];
	int pageFaults=0, time=0;
	int i,j;
	
	for(i=0; i<frameCount; i++){
		frames[i] = -1;
		lastUsed[i] = -1;
	}
	
	for(i=0; i<pageCount; i++){
		int pos = isPageInFrames(frames, pages[i], frameCount);
	
		if(pos == -1){
			int lruIndex = 0;
			
			for(j=1; j<frameCount;j++){
				if(lastUsed[j]<lastUsed[lruIndex])
					lruIndex=j;
			}
			
			frames[lruIndex] = pages[i];
			printf("\nPage %d -> ",pages[i]);
			for(int j=0; j<frameCount; j++){
				printf("%d ",frames[j]);
			}
			pageFaults++;
			lastUsed[lruIndex] = time++;
		}
		
		else {
			lastUsed[pos] = time++;
		}
		
		/*printf("\nPage %d -> ",pages[i]);
		for(j=0; j<frameCount; j++){
			printf("%d ",frames[j]);
		}*/
	}
	
	printf("\n");
	
	printf("\nPage Faults : %d\n",pageFaults);
}

void LFU(int pages[], int pageCount, int frameCount){

	int frames[MAX_FRAMES], freq[MAX_FRAMES], age[MAX_FRAMES];
	int pageFaults=0, time=0;
	int found;
	
	for(int i=0; i<frameCount; i++){
		frames[i] = -1;
		freq[i] = 0;
		age[i] = 0;
	}
	
	for(int i=0; i<pageCount; i++){
		//printf("\nPage %d -> ",pages[i]);
		int index = isPageInFrames(frames, pages[i], frameCount);
		if(index == -1){
			int replace_index = -1;
			int min_freq = 99999, oldest_age=-1;
			for(int j=0; j<frameCount; j++){
				if(frames[j]==-1){
					replace_index=j;
					break;
				}
				else if(freq[j]<min_freq || ((freq[j] == min_freq) && age[j]<oldest_age)){
					replace_index =j;
					min_freq = freq[j];
					oldest_age = age[j];
				}
			}
			frames[replace_index] = pages[i];
			freq[replace_index] = 1;
			age[replace_index] = i;
			pageFaults++;
			
			printf("\nPage %d -> ",pages[i]);
			
			for(int j=0; j<frameCount; j++){
				printf("%d ",frames[j]);
			}
		}
		else {
			freq[index]++;
		}
	}

	printf("\nPage Faults : %d\n",pageFaults);
}

int main(){
	int pages[MAX_FRAMES], pageCount, frameCount, x, choice;
	
	printf("\nEnter the number of FRAMES : ");
	scanf("%d",&frameCount);
	
	printf("\nEnter the number of PAGES : ");
	scanf("%d",&pageCount);
	
	printf("\nEnter the page sequence : ");
	for(x=0;x<pageCount;x++){
		scanf("%d",&pages[x]);
	}
	
	while(1){
	
		printf("\nPage Replacement Algorithms :");
		printf("\n1. First Come First Serve (FCFS)");
		printf("\n2. Least Recently Used (LRU)");
		printf("\n3. Least Frequently Used (LFU)");
		printf("\n4. Exit");
		
		printf("\nEnter your choice (1/2/3/4) : ");
		scanf("%d",&choice);
		
		if(choice==1){
			printf("\nFirst Come First Serve (FCFS)");
			fcfs(pages, pageCount, frameCount);
		}
		
		else if(choice==2){
			printf("\nLeast Recently Used (LRU)");
			lru(pages, pageCount, frameCount);
		}
		
		else if(choice==3){
		printf("\nLeast Frequently Used (LFU)");
			LFU(pages, pageCount, frameCount);
		}
		
		else if(choice==4){
			printf("Exiting Menu!\n");
			exit(0);
		}
		
		else{
			printf("Invalid choice! TRY AGAIN");
		}
	}
	
	return 0;
}


/* OUTPUT

Enter the number of FRAMES : 3

Enter the number of PAGES : 20

Enter the page sequence : 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1

Page Replacement Algorithms :
1. First Come First Serve (FCFS)
2. Least Recently Used (LRU)
3. Least Frequently Used (LFU)
4. Exit
Enter your choice (1/2/3/4) : 1

First Come First Serve (FCFS)
Page 7 -> 7 -1 -1 
Page 0 -> 7 0 -1 
Page 1 -> 7 0 1 
Page 2 -> 2 0 1 
Page 3 -> 2 3 1 
Page 0 -> 2 3 0 
Page 4 -> 4 3 0 
Page 2 -> 4 2 0 
Page 3 -> 4 2 3 
Page 0 -> 0 2 3 
Page 1 -> 0 1 3 
Page 2 -> 0 1 2 
Page 7 -> 7 1 2 
Page 0 -> 7 0 2 
Page 1 -> 7 0 1 

Page Faults : 15

Page Replacement Algorithms :
1. First Come First Serve (FCFS)
2. Least Recently Used (LRU)
3. Least Frequently Used (LFU)
4. Exit
Enter your choice (1/2/3/4) : 2

Least Recently Used (LRU)
Page 7 -> 7 -1 -1 
Page 0 -> 7 0 -1 
Page 1 -> 7 0 1 
Page 2 -> 2 0 1 
Page 3 -> 2 0 3 
Page 4 -> 4 0 3 
Page 2 -> 4 0 2 
Page 3 -> 4 3 2 
Page 0 -> 0 3 2 
Page 1 -> 1 3 2 
Page 0 -> 1 0 2 
Page 7 -> 1 0 7 

Page Faults : 12

Page Replacement Algorithms :
1. First Come First Serve (FCFS)
2. Least Recently Used (LRU)
3. Least Frequently Used (LFU)
4. Exit
Enter your choice (1/2/3/4) : 3

Least Frequently Used (LFU)
Page 7 -> 7 -1 -1 
Page 0 -> 7 0 -1 
Page 1 -> 7 0 1 
Page 2 -> 2 0 1 
Page 3 -> 2 0 3 
Page 4 -> 4 0 3 
Page 2 -> 4 0 2 
Page 3 -> 3 0 2 
Page 1 -> 3 0 1 
Page 2 -> 3 0 2 
Page 1 -> 3 0 1 
Page 7 -> 3 0 7 
Page 1 -> 3 0 1 
Page Faults : 13

Page Replacement Algorithms :
1. First Come First Serve (FCFS)
2. Least Recently Used (LRU)
3. Least Frequently Used (LFU)
4. Exit
Enter your choice (1/2/3/4) : 4
Exiting Menu!

*/
