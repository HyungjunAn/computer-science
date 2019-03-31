#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <ctype.h>

#define	Q_MAX	    16

typedef struct queue_t {
	int		data[Q_MAX];	
	int		nitem;		
	int		head;
	int		tail;
	pthread_mutex_t	mutex;
	pthread_cond_t	c_cond;	
	pthread_cond_t	p_cond;
}queue_t;

queue_t queue = {
	.mutex = PTHREAD_MUTEX_INITIALIZER,
	.c_cond = PTHREAD_COND_INITIALIZER,
	.p_cond = PTHREAD_COND_INITIALIZER,
};

void put( int d ) 
{
	queue.data[queue.head] = d;
	queue.head = (queue.head+1)%Q_MAX;
	queue.nitem++;
}

int get() 
{
	int temp =  queue.data[queue.tail];
	queue.tail = (queue.tail+1)%Q_MAX;
	queue.nitem--;
	return temp;
}

int is_empty( )
{
	return queue.nitem == 0;
}

int is_full( )
{
	return queue.nitem ==  Q_MAX;
}
void * produce(void *vptr)
{
	int	i;
	int ch;
	FILE* fp;

	fp = fopen(vptr, "r");
	if (fp == NULL) {
		fprintf(stderr, "file open error...\n");
		exit(1);
	}
	
	while (1) {
		pthread_mutex_lock(&queue.mutex);
		if (is_full()) {
			pthread_cond_wait(&queue.p_cond, &queue.mutex);
		}
		ch = fgetc(fp);
		if (islower(ch)) {
			printf("produce %c -> %c\n", ch, ch + 'A' - 'a');
			ch = ch + 'A' - 'a';
		} else if (isupper(ch)) {
			printf("produce %c -> %c\n", ch, ch);
		} else if (isspace(ch)) {
			printf("produce space\n");
		} else if (ch == EOF) {
			printf("produce EOF\n");
		}
		put(ch);
		pthread_cond_signal(&queue.c_cond);
		pthread_mutex_unlock(&queue.mutex);
		if (ch == EOF) {
			break;
		}
	}
	fclose(fp);
	return 0;
}

void * consume(void *vptr)
{
	FILE* fp;
	int ch;

	fp = fopen(vptr, "w");
	if (fp == NULL) {
		fprintf(stderr, "file open error..\n");
		exit(1);
	}

	while (1) {
		pthread_mutex_lock(&queue.mutex);
		if (is_empty()) {
			pthread_cond_wait(&queue.c_cond, &queue.mutex);
		}
		ch = get();
		if (ch == EOF) {
			break;
		}
		if (isalpha(ch)) {
			printf("\t\tconsume %c\n", ch);
		} else if (isspace(ch)) {
			printf("\t\tconsume space\n");
		}
		fputc(ch, fp);
		pthread_cond_signal(&queue.p_cond);
		pthread_mutex_unlock(&queue.mutex);
	}
	fclose(fp);
	return 0;
}

int main(int argc, char **argv)
{
	int	n;
	pthread_t tidA, tidB;
	int fd1, fd2;

	if (argc != 3) {
		fprintf(stderr, "Usage: ./a.out <input> <output>\n");
		return 1;
	}

	pthread_create(&tidA, 0, &produce, (void*)argv[1]);
	pthread_create(&tidB, 0, &consume, (void*)argv[2]);

	pthread_join(tidA, 0);
	pthread_join(tidB, 0);
	return 0;
}



