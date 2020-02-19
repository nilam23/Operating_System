#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int main()
{
	key_t key;
	int shm_id;
	key=ftok("file_shm", 1);
	if(key < 0)
	{
		perror("FTOK error: ");
		exit(1);
	}
	shm_id=shmget(key, 1024, 0666);
	if(shm_id < 0)
	{
		perror("SHMGET error: ");
		exit(1);
	}
	char *str=(char *) shmat(shm_id, (void *)0, 0);
	printf("String received from the other program is %s\n", str);
	shmdt(str);
	shmctl(shm_id, IPC_RMID, NULL);
	return 0;
}
