//B23CS1262
//Vedha Mahadevan
// fork() 3 - 28.01.2025

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
	pid_t pid;
	
	pid = fork();
	
	if (pid > 0){
		printf("Parent Process ID is : %d\t%d\n",getpid(),getppid());
	} 
	else if(pid == 0){
		printf("Child Process ID is  : %d\t%d\n",getpid(),getppid());
	}
	
	return 0;
}

/*OUTPUT

Parent Process ID is : 3150	2672
Child Process ID is  : 3151	3150

*/
