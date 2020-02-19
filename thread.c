#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
void *threadFunction()
{
	sleep(1);
	printf("Thread has been created.\n");
}
int main()
{
	printf("--Hello from MAIN--\n");
	pthread_t tid;
	printf("Creating a thread--\n");
	pthread_create(&tid, NULL, threadFunction, NULL);
	pthread_join(tid, NULL);
	printf("Return to MAIN again.\n");
	return 0;
}
