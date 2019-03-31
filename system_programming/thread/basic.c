#include <unistd.h>
#include <pthread.h>

#include <stdio.h>
#include <string.h>


int n = 0;

pthread_mutex_t mutex;
void *thread_routine(void *arg)
{
	int i;
	int local_ret = 0;
	for (i = 0; i < 10000; ++i) {
		local_ret++;
	}
	pthread_mutex_lock(&mutex);
	n += local_ret;
	pthread_mutex_unlock(&mutex);
	return 0;
}

pthread_cond_signal

int main(void)
{
	int i;
	void *ret;
	pthread_t thread[3];
	pthread_mutex_init(&mutex, 0);

	for (i = 0; i < 3; ++i) {
		pthread_create(&thread[i], NULL, thread_routine, NULL);
	}
	for (i = 0; i < 3; ++i) {
		pthread_join(thread[i], NULL);
	}
	printf("%d\n", n);
}

