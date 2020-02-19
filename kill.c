#include<stdio.h>
#include<signal.h>
int main()
{
	kill(7000, SIGINT);
	return 0;
}
