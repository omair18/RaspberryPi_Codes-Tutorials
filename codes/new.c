#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <wiringPi.h>
#define MOTOR11 0 //Motor1 terminal 1
#define MOTOR12 1// Motor1 terminal 2
#define MOTOR21 2 // Motor2 terminal 1
#define MOTOR22 3 // Motor2 terminal 2
#define DELAY 25
#define PWM 80
int main ()
{
	system("/bin/stty raw");

	printf("\nRUNNING CODE\n");
	wiringPiSetup();
	// set all pins to output mode
	softPwmCreate(MOTOR11,0,255);
	softPwmCreate(MOTOR12,0,255);
	softPwmCreate(MOTOR21,0,255);
	softPwmCreate(MOTOR22,0,255);

	softPwmWrite(MOTOR11,0);
	softPwmWrite(MOTOR12,0);
	softPwmWrite(MOTOR21,0);
	softPwmWrite(MOTOR22,0);

	while(1) {

		if(getchar() == '\033') {
			getchar(); // ignore the next character
			switch(getchar()) {
				case 'A':
					printf("FORWARD\n");
					softPwmWrite(MOTOR11,PWM);
					softPwmWrite(MOTOR21,PWM);
					softPwmWrite(MOTOR12,0);
					softPwmWrite(MOTOR22,0);
					delay(DELAY);
					//turn off both motors now, so that they work only when we hit button
					softPwmWrite(MOTOR11,0);
					softPwmWrite(MOTOR21,0);
					break;
				case 'B':
					printf("BACKWARD\n");
					softPwmWrite(MOTOR12,PWM);
					softPwmWrite(MOTOR22,PWM);
					softPwmWrite(MOTOR11,0);
					softPwmWrite(MOTOR21,0);
					delay(DELAY);
					//turn off both motors, so that they work only when we hit button
					softPwmWrite(MOTOR12,0);
					softPwmWrite(MOTOR22,0);
					break;
				case 'C':
					//printf("Right\n");
					printf("RIGHT\n");
					softPwmWrite(MOTOR21,PWM);
					softPwmWrite(MOTOR22,0);
					softPwmWrite(MOTOR11,0);
					softPwmWrite(MOTOR12,0);
					delay(DELAY);
					//turn off motor
					softPwmWrite(MOTOR21,0);
					break;
				case 'D':
					printf("LEFT\n");
					softPwmWrite(MOTOR11,PWM);
					softPwmWrite(MOTOR12,0);
					softPwmWrite(MOTOR21,0);
					softPwmWrite(MOTOR22,0);
					delay(DELAY);
					//turn off motor
					softPwmWrite(MOTOR11,0);
					break;
			}
		}
		else if (getchar() == 'q') {
			system("/bin/stty cooked");
			return 0; 
		}

	}

}
