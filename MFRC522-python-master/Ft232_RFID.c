/*
* Project name:ft232 brekaout board testing / RFID 125khz 

* Copyright
(c) Researchdesignlab.com
* Test configuration:
BOARD: RASPBERRY PI 

*/


#include <stdio.h>
#include <stddef.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

unsigned char rx_buffer[100];
unsigned char test[64];
unsigned char number[64];
unsigned char number_check[64]="+918123902188";
int count,i,flag,k;

int main()
{


int fd,f;

//IN CASE OF RASPBERRY PI THE FILE NAME IS /dev/AMA0

if((fd = open("/dev/hidraw0", O_RDWR | O_NOCTTY )) < 0)// ttyUSB*  changes as devices plugged in and out.  
{
printf("Unable to open uart1 access.\n");
}

while(1)
{
read(fd, rx_buffer,100);
printf("%d\n",rx_buffer);
}
}
