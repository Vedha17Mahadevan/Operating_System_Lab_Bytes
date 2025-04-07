//B23CS1262
//Vedha Mahadevan
// fork() basics - 28.01.2025


#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
	fork();
	printf("Hello World!\n");
	return 0;
}


/*OUTPUT

Hello World!
Hello World!

*/
