#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>

int main(){

	int shm_id, status;
	shm_id = shm_open("/chat", O_CREAT|O_RDWR ,0666);
	ftruncate(shm_id,4096);
	
	pid_t pid = fork();
	
	if (pid > 0){
	
		printf("Parent Write : ");
		char *ptr = mmap(NULL, 4096, PROT_WRITE, MAP_SHARED, shm_id, 0);
		fgets(ptr, sizeof(ptr), stdin);
		
		wait(&status);
		
		char *ptr3 = mmap(NULL, 4096, PROT_READ, MAP_SHARED, shm_id, 0);
		printf("Parent Read : %s",ptr3);
		munmap(ptr3, 4096);
		//*ptr = "Hello World!";
	}
	else if (pid == 0){
		sleep(3);
		char *ptr1 = mmap(NULL, 4096, PROT_READ, MAP_SHARED, shm_id, 0);
		printf("Child Read : %s",ptr1);
		
		printf("Child Write : ");
		char *ptr2 = mmap(NULL, 4096, PROT_WRITE, MAP_SHARED, shm_id, 0);
		fgets(ptr2, sizeof(ptr2), stdin);
		munmap(ptr1, 4096);
	}
	shm_unlink("/chat");

	return 0;
}

/* OUTPUT

Parent Write : Hi
Child Read : Hi
Child Write : Hello
Parent Read : Hello

*/




/*
//B23CS1262
//Vedha Mahadevan
//CPU Scheduling Algorithms - 25.02.2025

#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

struct Process {
	int pid, priority, arrival, burst, waiting, turnaround, remaining;
};

//Swap Function
void swap(struct Process* a, struct Process* b){
	struct Process temp = *a;
	*a=*b;
	*b= temp;	
}


//First Come First Serve Algorithm : FCFS

void fcfs(struct Process p[], int n){
	int completion_time = 0;
	
	//scheduling
	for(int i=0;i<n-1;i++){
		for(int j=0; j<n-i-1; j++){
			if(p[j].arrival > p[j+1].arrival){
				swap(&p[j],&p[j+1]);
			}
		}
	}
	
	//computing T.A & W.T
	for(int i=0;i<n;i++){
		if(completion_time < p[i].arrival){
			completion_time = p[i].arrival;
		}
		p[i].waiting = completion_time - p[i].arrival;
		p[i].turnaround = p[i].waiting + p[i].burst;
		completion_time += p[i].burst;
	}
	
	//Printing output
	printf("\nFirst Come First Serve RESULTS : \n");
	
	printf("\npid\tB.T\tPr\tA.T\tT.A\tW.T\n");
	
	for(int i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].burst,p[i].priority,p[i].arrival,p[i].turnaround,p[i].waiting);
	}
	printf("\n");
}

//Shortest Job First Algorithm : SJF (Non Pre-emptive)
void sjf(struct Process p[], int n){
	int completion_time = 0;
	
	//scheduling
	for(int i=0;i<n-1;i++){
		for(int j=i+1; j<n; j++){
			if((p[j].arrival <= p[i].arrival && p[j].burst<p[i].burst) || (p[i].arrival == p[j].arrival && p[j].burst < p[i].burst)){
				swap(&p[i],&p[j]);
			}
		}
	}
	
	//computing T.A & W.T
	for(int i=0;i<n;i++){
		if(completion_time < p[i].arrival){
			completion_time = p[i].arrival;
		}
		p[i].waiting = completion_time - p[i].arrival;
		p[i].turnaround = p[i].waiting + p[i].burst;
		completion_time += p[i].burst;
	}
	
	//Printing output
	printf("\nShortest Job First RESULTS : \n");
	
	printf("\npid\tB.T\tPr\tA.T\tT.A\tW.T\n");
	
	for(int i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].burst,p[i].priority,p[i].arrival,p[i].turnaround,p[i].waiting);
	}
	printf("\n");
}

//Round Robin Algorithm : RR (Pre-emptive)
void round_robin(struct Process p[], int n, int time_slice){
	int time=0;
	int completed=0;
	
	//scheduling & computing T.A & W.T
	for(int i=0;i<n;i++){
		p[i].remaining = p[i].burst;
	}
		
		while(completed < n){
			for(int i=0;i<n;i++){
				if(p[i].remaining > 0){
					if(p[i].remaining > time_slice){
						time += time_slice;
						p[i].remaining -= time_slice;
					}
					else{
						time += p[i].remaining;
						p[i].waiting = time - p[i].arrival - p[i].burst;
						p[i].turnaround = p[i].waiting + p[i].burst;
						p[i].remaining=0;
						completed++;
					}
				}
			}
		}
		
	//Printing output
	printf("\nRound Robin RESULTS : \n");
	
	printf("\npid\tB.T\tPr\tA.T\tT.A\tW.T\n");
	
	for(int i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].burst,p[i].priority,p[i].arrival,p[i].turnaround,p[i].waiting);
	}
	printf("\n");
}

//Priority Based Scheduling Algorithm
void priority(struct Process p[], int n){
	int completion_time = 0;
	
	//scheduling
	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			if(p[j].priority < p[i].priority){
				swap(&p[i],&p[j]);
			}
		}
	}
	
	//computing T.A & W.T
	for(int i=0;i<n;i++){
		if(completion_time < p[i].arrival){
			completion_time = p[i].arrival;
		}
		
		p[i].waiting = completion_time - p[i].arrival;
		p[i].turnaround = p[i].waiting + p[i].burst;
		completion_time += p[i].burst;
	}
	
	//Printing output
	printf("\nPriority Based Scheduling RESULTS : \n");
	
	printf("\npid\tB.T\tPr\tA.T\tT.A\tW.T\n");
	
	for(int i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].burst,p[i].priority,p[i].arrival,p[i].turnaround,p[i].waiting);
	}
	printf("\n");
}

int main(){
	int n, time_slice;
	
	printf("Enter the number of processes : ");
	scanf("%d",&n);
	
	struct Process p[n];
	
	for(int i=0;i<n;i++){
		printf("\nEnter the Arrival time , Burst time and Priority of the process P%d\n",i);
		p[i].pid = i;
		printf("Arrival Time : ");
		scanf("%d",&p[i].arrival);
		printf("Burst Time : ");
		scanf("%d",&p[i].burst);
		printf("Priority : ");
		scanf("%d",&p[i].priority);
		printf("\n");
	}
	
	printf("Enter the Time Quantum : ");
	scanf("%d",&time_slice);
	
	fcfs(p,n);
	sjf(p,n);
	round_robin(p,n,time_slice);
	priority(p,n);
	
	return 0;
}
*/
