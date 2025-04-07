//B23CS1262
//Vedha Mahadevan
//Dining Philosopher's Problem

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

#define NUM_PHILOSOPHERS 5

sem_t chopsticks[NUM_PHILOSOPHERS];
sem_t room;

void think(int id){
	printf("Philosopher %d is Thinking\n\n",id);
	sleep(1);
}

void eat(int id){
	printf("Philosopher %d is Eating\n\n",id);
	sleep(1);
}

void *philosopher(void *num){
	int id = *((int*)num);
	free(num);
	
	while(1){
		think(id);
		sem_wait(&room);
		
		printf("Philosopher %d is Trying to Pickup the Left Chopstick\n",id);
		sem_wait(&chopsticks[id]);
		printf("Philosopher %d has Picked up the Left Chopstick\n",id);
		
		printf("Philosopher %d is Trying to Pickup the Right Chopstick\n",id);
		sem_wait(&chopsticks[(id+1)%NUM_PHILOSOPHERS]);
		printf("Philosopher %d has Picked up the Right Chopstick\n",id);		
		
		eat(id);
		
		sem_post(&chopsticks[id]);
		printf("Philosopher %d has Dropped the Left Chopstick\n",id);
		
		sem_post(&chopsticks[(id+1)%NUM_PHILOSOPHERS]);
		printf("Philosopher %d has Dropped the Right Chopstick\n",id);	
		
		sem_post(&room);
	}
}

int main(){
	int i;
	pthread_t philosophers[NUM_PHILOSOPHERS];
	sem_init(&room, 0, NUM_PHILOSOPHERS);
	
	for(i=0; i<NUM_PHILOSOPHERS; i++){
		sem_init(&chopsticks[i], 0, 1);
	}
	
	for(i=0; i<NUM_PHILOSOPHERS; i++){
		int *id = malloc(sizeof(int));
		*id=i;	
		pthread_create(&philosophers[i], NULL, philosopher, id);
	}
	
	for(i=0; i<NUM_PHILOSOPHERS; i++){
		pthread_join(philosophers[i], NULL);
	}
	
	sem_destroy(&room);
	
	for(i=0; i<NUM_PHILOSOPHERS; i++){
		sem_destroy(&chopsticks[i]);
	}
	
	return 0;
}

/* OUTPUT

Philosopher 0 is Thinking

Philosopher 4 is Thinking

Philosopher 2 is Thinking

Philosopher 3 is Thinking

Philosopher 1 is Thinking

Philosopher 0 is Trying to Pickup the Left Chopstick
Philosopher 0 has Picked up the Left Chopstick
Philosopher 0 is Trying to Pickup the Right Chopstick
Philosopher 0 has Picked up the Right Chopstick
Philosopher 0 is Eating

Philosopher 2 is Trying to Pickup the Left Chopstick
Philosopher 2 has Picked up the Left Chopstick
Philosopher 2 is Trying to Pickup the Right Chopstick
Philosopher 2 has Picked up the Right Chopstick
Philosopher 2 is Eating

Philosopher 4 is Trying to Pickup the Left Chopstick
Philosopher 4 has Picked up the Left Chopstick
Philosopher 4 is Trying to Pickup the Right Chopstick
Philosopher 1 is Trying to Pickup the Left Chopstick
Philosopher 3 is Trying to Pickup the Left Chopstick
Philosopher 0 has Dropped the Left Chopstick
Philosopher 0 has Dropped the Right Chopstick
Philosopher 0 is Thinking

Philosopher 4 has Picked up the Right Chopstick
Philosopher 4 is Eating

Philosopher 2 has Dropped the Left Chopstick
Philosopher 2 has Dropped the Right Chopstick
Philosopher 2 is Thinking

Philosopher 3 has Picked up the Left Chopstick
Philosopher 3 is Trying to Pickup the Right Chopstick
Philosopher 1 has Picked up the Left Chopstick
Philosopher 1 is Trying to Pickup the Right Chopstick
Philosopher 1 has Picked up the Right Chopstick
Philosopher 1 is Eating

Philosopher 0 is Trying to Pickup the Left Chopstick
Philosopher 2 is Trying to Pickup the Left Chopstick
Philosopher 3 has Picked up the Right Chopstick
Philosopher 3 is Eating

*/
