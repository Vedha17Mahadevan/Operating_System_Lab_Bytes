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
	printf("\nFirst Come First Serve RESULTS : \n");
	//scheduling
	for(int i=0;i<n-1;i++){
		for(int j=0; j<n-i-1; j++){
			if(p[j].arrival > p[j+1].arrival){
				swap(&p[j],&p[j+1]);
			}
		}
	}
	
	printf("\nGantt Chart : \n");
	printf("| 0 |");
	
	//computing T.A & W.T
	for(int i=0;i<n;i++){
		if(completion_time < p[i].arrival){
			completion_time = p[i].arrival;
		}
		p[i].waiting = completion_time - p[i].arrival;
		p[i].turnaround = p[i].waiting + p[i].burst;
		completion_time += p[i].burst;
		printf(" P%d | %d |",p[i].pid,completion_time);
	}
	
	printf("\n");
	
	//Printing output
	printf("\npid\tB.T\tPr\tA.T\tT.A\tW.T\n");
	
	for(int i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].burst,p[i].priority,p[i].arrival,p[i].turnaround,p[i].waiting);
	}
	printf("\n");
}

//Shortest Job First Algorithm : SJF (Non Pre-emptive)
void sjf(struct Process p[], int n){
	int completion_time = 0, completed=0, min_index;
	printf("\nShortest Job First RESULTS : \n");
	
	for(int i=0; i<n; i++){
		p[i].remaining=p[i].burst;
	}
	
	printf("\nGantt Chart : \n");
	printf("| 0 |");
	
	while(completed<n){
		min_index = -1;
		for(int i=0; i<n; i++){
			if(p[i].arrival <= completion_time && p[i].remaining >0){
				if(min_index==-1 || p[i].burst < p[min_index].burst){
				 	min_index = i;
				 }
			}
		}
		
		if(min_index == -1){
			completion_time++;
			continue;
		}
		
		completion_time += p[min_index].burst;
		p[min_index].waiting = completion_time - p[min_index].arrival - p[min_index].burst;
		p[min_index].turnaround = p[min_index].waiting + p[min_index].burst;
		p[min_index].remaining =0;
		completed++;
		printf(" P%d | %d |",p[min_index].pid,completion_time);
	}
	
	printf("\n");
	
	//Printing output	
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
	printf("\nRound Robin RESULTS : \n");
	
	
	//scheduling & computing T.A & W.T
	for(int i=0;i<n;i++){
		p[i].remaining = p[i].burst;
	}
	
	printf("\nGantt Chart : \n");
	printf("| 0 |");
		
	while(completed < n){
		int executed = 0;
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
				executed = 1;
				printf(" P%d | %d |",p[i].pid,time);
			}
		}
		if(!executed){
			break;
		}
	}
		
	printf("\n");
		
	//Printing output
	printf("\npid\tB.T\tPr\tA.T\tT.A\tW.T\n");
	
	for(int i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].burst,p[i].priority,p[i].arrival,p[i].turnaround,p[i].waiting);
	}
	printf("\n");
}

//Priority Based Scheduling Algorithm
void priority(struct Process p[], int n){
	int completion_time = 0, completed=0, hp;
	printf("\nPriority Based Scheduling RESULTS : \n");
	
	for(int i=0; i<n; i++){
		p[i].remaining=p[i].burst;
	}
	
	printf("\nGantt Chart : \n");
	printf("| 0 |");
	
	while(completed<n){
		hp = -1;
		for(int i=0; i<n; i++){
			if(p[i].arrival <= completion_time && p[i].remaining >0){
				if(hp==-1 || p[i].burst < p[hp].burst){
				 	hp = i;
				 }
			}
		}
		
		if(hp == -1){
			completion_time++;
			continue;
		}
		
		completion_time += p[hp].burst;
		p[hp].waiting = completion_time - p[hp].arrival - p[hp].burst;
		p[hp].turnaround = p[hp].waiting + p[hp].burst;
		p[hp].remaining =0;
		completed++;
		printf(" P%d | %d |",p[hp].pid,completion_time);
	}
	
	printf("\n");
	
	//Printing output	
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

/* OUTPUT

Enter the number of processes : 5

Enter the Arrival time , Burst time and Priority of the process P0
Arrival Time : 0
Burst Time : 2
Priority : 2


Enter the Arrival time , Burst time and Priority of the process P1
Arrival Time : 1
Burst Time : 1
Priority : 1


Enter the Arrival time , Burst time and Priority of the process P2
Arrival Time : 2
Burst Time : 8
Priority : 4


Enter the Arrival time , Burst time and Priority of the process P3
Arrival Time : 3
Burst Time : 4
Priority : 2


Enter the Arrival time , Burst time and Priority of the process P4
Arrival Time : 4
Burst Time : 5
Priority : 3

Enter the Time Quantum : 2

First Come First Serve RESULTS : 

Gantt Chart : 
| 0 | P0 | 2 | P1 | 3 | P2 | 11 | P3 | 15 | P4 | 20 |

pid	B.T	Pr	A.T	T.A	W.T
0	2	2	0	2	0
1	1	1	1	2	1
2	8	4	2	9	1
3	4	2	3	12	8
4	5	3	4	16	11


Shortest Job First RESULTS : 

Gantt Chart
| 0 | P0 | 2 | P1 | 3 | P3 | 7 | P4 | 12 | P2 | 20 |

pid	B.T	Pr	A.T	T.A	W.T
0	2	2	0	2	0
1	1	1	1	2	1
2	8	4	2	18	10
3	4	2	3	4	0
4	5	3	4	8	3


Round Robin RESULTS : 

Gantt Chart : 
| 0 | P0 | 2 | P1 | 3 | P2 | 5 | P3 | 7 | P4 | 9 | P2 | 11 | P3 | 13 | P4 | 15 | P2 | 17 | P4 | 18 | P2 | 20 |

pid	B.T	Pr	A.T	T.A	W.T
0	2	2	0	2	0
1	1	1	1	2	1
2	8	4	2	18	10
3	4	2	3	10	6
4	5	3	4	14	9


Priority Based Scheduling RESULTS : 

Gantt Chart
| 0 | P0 | 2 | P1 | 3 | P3 | 7 | P4 | 12 | P2 | 20 |

pid	B.T	Pr	A.T	T.A	W.T
0	2	2	0	2	0
1	1	1	1	2	1
2	8	4	2	18	10
3	4	2	3	4	0
4	5	3	4	8	3

*/
