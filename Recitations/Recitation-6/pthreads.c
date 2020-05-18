#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define BUFFER_SIZE 100

void* producer();
void* consumer();

pthread_cond_t buffer_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

FILE* file;
char buffer[BUFFER_SIZE];
int bufferIndex = 0, fileSize, currentSize = 0;

int main(int argc, char** argv) {
	file = fopen(argv[1], "r");
	if(file == NULL) {
		perror("Error opening file!\n");
		return(-1);
	}

	fseek(file, 0L, SEEK_END);
	fileSize = ftell(file);
	rewind(file);
	
    	pthread_t ptid, ctid;

    	pthread_create(&ptid, NULL, producer, NULL);
    	pthread_create(&ctid, NULL, consumer, NULL);

    	pthread_join(ptid, NULL);
    	pthread_join(ctid, NULL);

    	return 0;
}

void* producer() {
    	for (;;) {
        	pthread_mutex_lock(&mutex);
		char c = fgetc(file);
        	if (bufferIndex >= BUFFER_SIZE || c == EOF) {
        		bufferIndex = 0;
            		printf("DONE\n\n");
            		printf("Message Received: ");
            		pthread_cond_wait(&buffer_not_full, &mutex);
        	}
        	buffer[bufferIndex++] = c;
        	pthread_mutex_unlock(&mutex);
        	pthread_cond_signal(&buffer_not_empty);
	}
}

void* consumer() {
   	for (;;) {
        	pthread_mutex_lock(&mutex);
		printf("%c", buffer[bufferIndex]);
		bufferIndex++;
		currentSize++;
		if(bufferIndex >= BUFFER_SIZE) {
			bufferIndex = 0;
			printf("\n");
			pthread_cond_wait(&buffer_not_empty, &mutex);
		}
		else if(currentSize >= fileSize) {
			break;
		}
        	pthread_mutex_unlock(&mutex);
        	pthread_cond_signal(&buffer_not_full);
	}
}
