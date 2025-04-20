#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 5

struct data{
	int buffer[BUFFER_SIZE];
		sem_t empty,full,mutex;
}*shared_data;

int main(){
	int fd = shm_open("/shared", O_CREAT|O_RDWR, 0777);

	shared_data = mmap(NULL, sizeof(struct data), PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
	
	int index=0,item=0;
	
	while(item>-1){
		if(sem_trywait(&(shared_data->full))!=0){
			printf("\nBuffer is EMPTY!!\n");
			exit(0);
			sem_wait(&(shared_data->full));
		}
		
		sem_wait(&(shared_data->mutex));
		item=shared_data->buffer[index];
		printf("\nConsumer Consumed item : %d\n",item);
			
		index=(index+1)%BUFFER_SIZE;
		item-=1;
		item=(item+1)%BUFFER_SIZE;
			
		sem_post(&(shared_data->mutex));
		sem_post(&(shared_data->empty));
		sleep(1);
	}
	return 0;
}

/* OUTPUT


Consumer Consumed item : 83

Consumer Consumed item : 86

Consumer Consumed item : 77

Consumer Consumed item : 15

Consumer Consumed item : 93

Consumer Consumed item : 35

Consumer Consumed item : 86
^Z
[1]+  Stopped                 ./a.out

*/
