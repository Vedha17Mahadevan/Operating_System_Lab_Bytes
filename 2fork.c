//B23CS1262
//Vedha Mahadevan
// fork() 2 - 28.01.2025

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
	pid_t pid;
	
	pid = fork();
	
	if (pid > 0){
		printf("Hello!!\n");
	} 
	else if(pid == 0){
		printf("Bye!!\n");
	}
	
	return 0;
}

/*OUTPUT

Hello!!
Bye!!

*/
