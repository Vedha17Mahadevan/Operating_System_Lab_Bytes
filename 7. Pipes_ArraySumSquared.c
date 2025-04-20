
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 10

int main() {
	
	pid_t pid1, pid2;
	int a[MAX] , b[MAX];
	int fd1[2], fd2[2], fd3[2];
	int n,status,i;
	int sum=0;
	
	printf("Enter array limit : ");
	scanf("%d", &n);
	
	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
	
	pid1 = fork();
	
	if(pid1 == 0){
	
		close(fd1[1]);
		read(fd1[0],b,n*sizeof(int));
		close(fd1[0]);
		
		/*printf("\nEnter the Array elements : \n");
		for(i=0;i<n;i++){
			scanf("%d",&b[i]);
		}*/
		
		printf("\nThe Original Array : ");
		for(i=0;i<n;i++){
			printf("%d ",b[i]);
			b[i] = b[i] * b[i];
		}
		printf("\n");
		
		printf("\nThe Squared Array : ");
		for(i=0;i<n;i++){
			printf("%d ",b[i]);
		}
		printf("\n");
		
		pid2 = fork();
		if(pid2 == 0) {
			//int sum = 0;
			
			close(fd2[1]);
			read(fd2[0],b,n*sizeof(int));
			close(fd2[0]);
			
			for(i=0;i<n;i++){
				sum += b[i];
			}
			printf("\nSum of elements of the Array : %d",sum);
		}
		
		//printf("\nSum of elements of the Array : %d",sum);
		printf("\n");
		close(fd3[0]);
		write(fd3[1],b,n*sizeof(int));
		close(fd3[1]);
	}
	
	else if (pid1 > 0) {
		//int sum;
		printf("\nEnter the Elements of the Array : \n");
		for(i=0;i<n;i++){
			scanf("%d",&a[i]);
			//sum += a[i];
		}
		/*printf("\nSum of elements of the Array : %d",sum);
		printf("\n");*/
		close(fd1[0]);
		write(fd1[1],a,n*sizeof(int));
		close(fd1[1]);
		//wait(&status);
		close(fd3[1]);
		read(fd3[0], &sum, sizeof(sum));
		close(fd3[0]);
	}
	
	else{
		printf("\nProcess FAILED!");
	}
	return 0;
}

/* OUTPUT

Enter array limit : 5

Enter the Elements of the Array : 
1
2
3
4
5

The Original Array : 1 2 3 4 5 

The Squared Array : 1 4 9 16 25 


Sum of elements of the Array : 55

*/
