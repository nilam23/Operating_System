#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
int main()
{
	FILE *fp;
	fp=fopen("fork_file.txt", "w");
	if(fp==NULL)
	{
		printf("Error in file opening.\n");
		exit(1);
	}
	int status;
	pid_t pid1, pid2;
	pid1=fork();
	if(pid1 < 0)
	{
		perror("FORK error: ");
		exit(1);
	}
	else if(pid1 == 0)
	{
		printf("--CHILD REGION.--\n");
		printf("PID of child is %d\n", getpid());
		printf("PID of it's parent is %d\n", getppid());
		if((pid2=fork()) == 0)
		{
			printf("\n--GRANDCHILD REGION--\n");
			printf("My roll no is CSB17041\n");
			printf("PID of grandchild is %d\n", getpid());
			printf("PID of it's parent is %d\n", getppid());
			fprintf(fp, "%d", getpid());
			fclose(fp);
		}
		exit(0);
	}
	else
	{
		wait(&status);
		printf("\n--PARENT REGION.--\n");
		printf("PID of parent is %d\n", getpid());
		printf("PID of it's child is %d\n", pid1);
		printf("PID of it's parent is %d\n", getppid());
		int grand_pid;
		fp=fopen("fork_file.txt", "r");
		if(fp==NULL)
		{
			printf("Error in file opening (2).\n");
			exit(1);
		}
		fscanf(fp, "%d", &grand_pid);
		printf("PID of grandchild is %d\n", grand_pid);
	}
}
