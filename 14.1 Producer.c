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
	ftruncate(fd, sizeof(struct data));
	shared_data = mmap(NULL, sizeof(struct data), PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
	
	sem_init(&(shared_data->mutex),1,1);
	sem_init(&(shared_data->full),1,0);
	sem_init(&(shared_data->empty),1,BUFFER_SIZE);
	
	int index=0,item=0,n;
	
	while(1){
		if(sem_trywait(&(shared_data->empty))!=0){
			printf("\nBuffer is FULL!!!\n");
			exit(0);
			sem_wait(&(shared_data->empty));
		}
	
		int item = rand()%100;
		sem_wait(&(shared_data->mutex));
		shared_data->buffer[index]=item;
		printf("\nProducer Produced item : %d\n",item);
		
		index=(index+1)%BUFFER_SIZE;
		item=(item+1)%BUFFER_SIZE;
			
		sem_post(&(shared_data->mutex));
		sem_post(&(shared_data->full));
		sleep(1);
	}
	return 0;
}		


/* OUTPUT

Producer Produced item : 83

Producer Produced item : 86

Producer Produced item : 77

Producer Produced item : 15

Producer Produced item : 93

Producer Produced item : 35

Producer Produced item : 86

Producer Produced item : 92

Producer Produced item : 49

Producer Produced item : 21

Producer Produced item : 62

Producer Produced item : 27

Buffer is FULL!!!

*/
