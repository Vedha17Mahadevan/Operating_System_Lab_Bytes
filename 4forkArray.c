//B23CS1262
//Vedha Mahadevan
// fork() array - 28.01.2025

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
	pid_t pid;
	int n,a[10],i;
	int sum=0;
	
	printf("Enter array limit : ");
	scanf("%d", &n);
	
	printf("Enter elements of the array : ");
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}

	printf("The array : ");
	for(i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
	
	pid = fork();
	
	if (pid > 0){
		printf("Parent Process\t");
		printf("Squared Array : ");
		for(i=0;i<n;i++){
			a[i]*=a[i];
			printf("%d ",a[i]);
		}
		printf("\n");
	} 
	else if(pid == 0){
		printf("Child Process\t");
		for(i=0;i<n;i++){
			sum += a[i];
		}
		printf("Sum of Elements of the Array : %d\n",sum);
	}
	
	return 0;
}

/*OUTPUT

Enter array limit : 5
Enter elements of the array : 1
2
3
4
5
The array : 1 2 3 4 5 
Parent Process	Squared Array : 1 4 9 16 25 
Child Process	Sum of Elements of the Array : 15

*/
