#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msg_buffer{
	long msg_id;
	char msg_text[100];
}msg;
int main()
{
	key_t key;
	int queue_id;
	key=ftok("file_queue", 1);
	if(key < 0)
	{
		perror("FTOK error: ");
		exit(1);
	}
	queue_id=msgget(key, 0666);
	if(queue_id < 0)
	{
		perror("MSGGET error: ");
		exit(1);
	}
	msg.msg_id=1;
	printf("Enter the message to be sent to the other program: ");
	scanf("%s", msg.msg_text);
	msgsnd(queue_id, &msg, sizeof(msg), 0);
	return 0;
}