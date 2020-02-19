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
	queue_id=msgget(key, 0666 | IPC_CREAT);
	if(queue_id < 0)
	{
		perror("MSGGET error: ");
		exit(1);
	}
	msg.msg_id=1;
	msgrcv(queue_id, &msg, sizeof(msg), 1, 0);
	printf("Message from the other process is %s\n", msg.msg_text);
	printf("Destroying the Message Queue....\n");
	msgctl(queue_id, IPC_RMID, NULL);
	return 0;
}