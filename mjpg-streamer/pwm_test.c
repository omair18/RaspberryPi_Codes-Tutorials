#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <wiringPi.h>

#define SERVO_DOWN 23
#define SERVO_UP 24
#define DIFF 0.002


int main ()
{
	char input;
	char buffer[50];
	float value_down=0.146; //0.155; // 0.080 to 0.130 moves right, 0.130 to 0.220 moves left
	float value_up= 0.135; // 0.070 to 0.135 moves up, 0.135 to 0.195 moves down

	sprintf(buffer,"echo \"%d=%f\"> /dev/pi-blaster",SERVO_DOWN,value_down);
	system(buffer);
	printf("Waiting for 0.5 min \n");
	delay(5000);
	sprintf(buffer,"echo \"%d=%d\"> /dev/pi-blaster",SERVO_DOWN,0);
	system(buffer);
	printf("wait over \n");
	
	return 0;
}