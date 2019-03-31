#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define	NLOOP	   	100
#define	Q_MAX	    16 

typedef struct queue_t {
  int		data[Q_MAX + 1];	
  int		nitem;		
  int		head;
  int		tail;
  pthread_mutex_t	mutex;
  pthread_cond_t	c_cond;	
  pthread_cond_t	p_cond;
}queue_t;

queue_t queue = {
	.mutex  = PTHREAD_MUTEX_INITIALIZER,
	.c_cond = PTHREAD_COND_INITIALIZER,
	.p_cond = PTHREAD_COND_INITIALIZER,
};

void put( int d ) 
{
	queue.data[queue.head] = d;
	queue.head = (queue.head+1)%(Q_MAX + 1);
	queue.nitem++;
}

int get() 
{
	int temp =  queue.data[queue.tail];
	queue.tail = (queue.tail+1)%(Q_MAX + 1);
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

int my_usleep(int min, int max)
{
	min *= 1000;
	max *= 1000;
	int r_n = rand() % (max - min + 1);
	usleep((r_n + min));
}

void * produce(void *vptr)
{
	int i;
	while (i != NLOOP) {
		pthread_mutex_lock(&queue.mutex);
		if (is_full()) {
			pthread_cond_wait(&queue.p_cond, &queue.mutex);
		}
		else {
			my_usleep(1, 5);
			put(i+1);
			printf("produce %d\n", i+1);
			pthread_cond_signal(&queue.c_cond);
			i++;
		}
		pthread_mutex_unlock(&queue.mutex);
	}
	return 0;
}

void * consume(void *vptr)
{
	int i = 0;
	while (i != NLOOP) {
		pthread_mutex_lock(&queue.mutex);
		if (is_empty()) {
			pthread_cond_wait(&queue.c_cond, &queue.mutex);
		}
		else {
			my_usleep(2, 3);
			printf("\t\tconsume %d\n", get());
			++i;
			pthread_cond_signal(&queue.p_cond);
		}
		pthread_mutex_unlock(&queue.mutex);
	}
	return 0;
}

int main(int argc, char **argv)
{
	pthread_t	tidA, tidB;
	srand(time(0));

	pthread_create(&tidA, 0, &produce, 0);
	pthread_create(&tidB, 0, &consume, 0);
	pthread_join(tidA, 0);
	pthread_join(tidB, 0);
	return 0;
}


