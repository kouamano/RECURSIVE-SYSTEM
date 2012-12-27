#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_function(void *arg) {
	double i;
	double j;
	for ( i=0; i<50000000; i++ ) {
			j += i;
		        //printf("Thread says hi!\n");
			//sleep(1);
	}
	return NULL;
}

int main(void) {
	int i;
	pthread_t mythread[10];
	for(i=0;i<4;i++){
		printf("i:%d",i);
		if ( pthread_create( &mythread[i], NULL, thread_function, NULL) ) {
			printf("error creating thread.");
			abort();
		}
	        exit(0);
	}

}
