#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
	pid_t pid;
	int fd[2];
	pipe(fd);
	
	pid = fork();
	
	if (pid > 0){
		close(fd[0]);
		char  buff[100] = "Hello World!";
		write(fd[1],buff,sizeof(buff));
		close(fd[1]);
	} 
	else if(pid == 0){
		close(fd[1]);
		char  buff1[100];
		read(fd[0],buff1,sizeof(buff1));
		printf("%s",buff1);
		close(fd[0]);
	}
	
	return 0;
}

/*OUTPUT

Hello World!

*/
