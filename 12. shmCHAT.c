#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

struct Shared {
	char childmsg[100];
	char parentmsg[100];
	int turn;
};

int main(){

	struct Shared *shrmemory;
	
	int shm_id;
	pid_t pid = fork();
	
	shm_id = shm_open("/chat", O_CREAT|O_RDWR, 0666);
	ftruncate(shm_id, 4096);
	
	shrmemory = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, shm_id, 0);
	shrmemory->turn = 0;
	
	if(pid == 0){
		while(1){
			while(shrmemory->turn != 1){
				sleep(1);
			}
			printf("Child Reads message : %s", shrmemory->parentmsg);
			printf("\nChild : ");
			fgets(shrmemory->childmsg, sizeof(shrmemory->childmsg), stdin);
			shrmemory->turn=0;
		}
	}
	
	else if (pid>0) {
		while(1){
			while(shrmemory->turn != 0){
				sleep(1);
			}
			printf("\nParent : ");
			fgets(shrmemory->parentmsg, sizeof(shrmemory->parentmsg), stdin);
			
			if (strcmp(shrmemory->parentmsg,"exit\n") == 0) {
				break;
			}
			shrmemory->turn = 1;
			while(shrmemory->turn !=0){
				sleep(1);
			}
			if (strcmp(shrmemory->childmsg,"exit\n") == 0) {
				break;
			}
			
			printf("Parent reads message : %s",shrmemory->childmsg);
		}
	}
	
	else	{
		printf("Fork creation FAILED!!!");
	}
	
	munmap(shrmemory, 4096);
	shm_unlink("/chat");
	
	return 0;
}
