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
