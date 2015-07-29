#include <fcntl.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>

int main () {
	int fd = open("/dev/input/event0",O_RDONLY);
	char test[1000]={0};
	read(fd,test,1000);
	printf("test = %s\n",test);
	getchar();
}
