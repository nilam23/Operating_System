#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#define SIZE 1000
int main()
{
	mknod("fifo_pipe", S_IFIFO | 0666, 0);
	int fd = open("fifo_pipe", O_RDWR);
	if(fd < 0)
	{
		perror("OPEN error: ");
		exit(1);
	}
	char buffer[SIZE];
	memset(buffer, 0x0, sizeof(buffer));
	read(fd, buffer, sizeof(buffer));
	printf("String received from the Prog2 is %s\n", buffer);
	memset(buffer, 0x0, sizeof(buffer));
	strcpy(buffer, "Thanks");
	write(fd, buffer, strlen(buffer)+1);
	return 0;
}
