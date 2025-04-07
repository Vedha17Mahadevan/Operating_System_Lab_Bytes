//B23CS1262
//Vedha Mahadevan
//Shared Memory_1 - 11.02.2025

#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>

int main(){

	int shm_id;
	shm_id = shm_open("/chat", O_CREAT|O_RDWR ,0666);
	ftruncate(shm_id,4096);
	
	pid_t pid = fork();
	
	if (pid > 0){
		char *ptr = mmap(NULL, 4096, PROT_WRITE, MAP_SHARED, shm_id, 0);
		fgets(ptr, sizeof(ptr), stdin);
		//*ptr = "Hello World!";
	}
	else if (pid == 0){
		sleep(3);
		char *ptr1 = mmap(NULL, 4096, PROT_READ, MAP_SHARED, shm_id, 0);
		printf("%s",ptr1);
		munmap(ptr1, 4096);
	}
	shm_unlink("/chat");

	return 0;
}

/* OUTPUT
 
 hi

*/
