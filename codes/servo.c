#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <softPwm.h>

#define SERVO1 0 
#define SERVO2 1
#define DELAY 25 
#define PWM0 05 // 05
#define PWM1 60 // 60

int main (int argc, char *argv[])
{
	system("/bin/stty raw");

	if(wiringPiSetup() == -1)
	exit(1);
	
	
	pinMode(SERVO1,OUTPUT);
	pinMode(SERVO2,OUTPUT);
	
	
	softPwmCreate(SERVO1,0,255);
	softPwmCreate(SERVO2,0,255); 
	

	printf("\nServo PWM code running \n");

	while(1) {	
	
		switch(getchar()) {
			
			case 'f':
				printf("Moving Right\n");
				softPwmWrite(SERVO1,PWM0);
				delay(DELAY);
				softPwmWrite(SERVO1,0);
				break;
			case 's':
				printf("Moving Left\n");
				softPwmWrite(SERVO1,PWM1);
				delay(DELAY);
				softPwmWrite(SERVO1,0);
				break;
			case 'e':
				printf("Moving Up \n");
				softPwmWrite(SERVO2,PWM0);
				delay(DELAY);
				softPwmWrite(SERVO2,0);
				break;	
			case 'd':
				printf("Moving Down\n");
				softPwmWrite(SERVO2,PWM1);
				delay(DELAY);
				softPwmWrite(SERVO2,0);
				break;	
			case 'q':
				printf("Quit\n");
				softPwmWrite(SERVO1,0);
				softPwmWrite(SERVO2,0);
				system("/bin/stty cooked");
				return 0;	
			}// end of switch
	

	}// end of while

	
	
} //end of main
