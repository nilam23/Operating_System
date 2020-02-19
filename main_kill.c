#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
#include<wait.h>

void handle(int s)
{
	printf("From inside Handle function.\n");
	FILE *fp;
	fp=fopen("file.txt", "w");
	if(fp==NULL)
	{
		printf("File couldn't open.\n");
		exit(1);
	}
	int stat;
	pid_t pid, pid1;
	pid=fork();
	if(pid < 0)
	{
		perror("FORK error: ");
		exit(1);
	}
	else if(pid == 0)
	{
		printf("--CHILD--\n");
		printf("PID %d\n", getpid());
		printf("PPID %d\n", getppid());
		pid1=fork();
		if(pid1 < 0)
		{
			perror("FORK 2 error: ");
			exit(1);
		}
		else if(pid1 == 0)
		{
			printf("--GRANDCHILD--\n");
			printf("PID %d\n", getpid());
			printf("PPID %d\n", getppid());
			fprintf(fp, "%d", getpid());
			fclose(fp);
		}
		exit(0);
	}
	else
	{
		wait(&stat);
		printf("--PARENT--\n");
		printf("PID %d\n", getpid());
		printf("PPID %d\n", getppid());
		int p;
		fp=fopen("file.txt", "r");
		fscanf(fp, "%d", &p);
		printf("GC_PID %d\n", p);
	}
}
int main()
{
	printf("My PID %d\n", getpid());
	printf("Generating signal: \n");
	signal(SIGINT, handle);
	while(1);
	printf("After Infinite loop.\n");
	return 0;
}
