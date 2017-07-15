#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread(void *vargp);
void recurse(pthread_t tid, pthread_t tids[], int T, int max);

int main(int argc, char* argv[]) {
	int N = atoi(argv[1]); //Get number of threads we want
	int max = (2 << N - 1) - 2;
	pthread_t tids[max];
	recurse(tids[0], tids, 0, max);
	
	printf("Thread 0 Done\n");
	
	exit(0);
}

void *thread(void *vargp){
	printf("Thread ");
	printf("%d", *(int*) vargp);
	printf(" Done\n");
	return NULL;
}

void recurse(pthread_t tid, pthread_t tids[], int T, int max){
	int T1 = 2*T + 1;
	int T2 = 2*T + 2;
	
	if (T1 > max)
		return;
	
	int *ptr1 = &T1;
	int *ptr2 = &T2;
	
	recurse(tids[T1], tids, T1, max);
	recurse(tids[T2], tids, T2, max);
	
	pthread_create(&tids[T1], NULL, thread, ptr1);
	pthread_join(tids[T1], NULL);
	pthread_create(&tids[T2], NULL, thread, ptr2);
	pthread_join(tids[T2], NULL);
}