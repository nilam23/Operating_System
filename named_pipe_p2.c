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
	int fd = open("fifo_pipe", O_RDWR);
	if(fd < 0)
	{
		perror("OPEN error: ");
		exit(1);
	}
	char str[SIZE], buffer[SIZE];
	printf("Enter a string to send to the Prog1: ");
	scanf("%s", str);
	write(fd, str, strlen(str)+1);
	sleep(1);
	memset(buffer, 0x0, sizeof(buffer));
	read(fd, buffer, sizeof(buffer));
	printf("Ack from Prog1 is %s\n", buffer);
	return 0;
}