#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <wiringPi.h>
#define MOTOR11 0 //Motor1 terminal 1
#define MOTOR12 1// Motor1 terminal 2
#define MOTOR21 2 // Motor2 terminal 1
#define MOTOR22 3 // Motor2 terminal 2
#define LED 4 // Camera led's
#define SERVO1 6 //right wali pin 16 agay wali Up/down
#define SERVO2 5 // left wali pin 18 peechay wali right/left

#define PWM0 03 // 05
#define PWM1 60 // 60
#define DELAY 25

#define PWM 200
#define PWM_R 255
int main ()
{
	system("/bin/stty raw");

	printf("\nRUNNING CODE ( press 'q' to exit)\n");
	wiringPiSetup();

	pinMode(MOTOR11,OUTPUT);
	pinMode(MOTOR12,OUTPUT);
	pinMode(MOTOR21,OUTPUT);
	pinMode(MOTOR22,OUTPUT);
	pinMode(LED,OUTPUT);

	// set all pins to output mode
	softPwmCreate(MOTOR11,0,255);
	softPwmCreate(MOTOR12,0,255);
	softPwmCreate(MOTOR21,0,255);
	softPwmCreate(MOTOR22,0,255);

	pinMode(SERVO1,OUTPUT);
	pinMode(SERVO2,OUTPUT);
	
	softPwmCreate(SERVO1,0,255);
	softPwmCreate(SERVO2,0,255); 

	softPwmWrite(MOTOR11,0);
	softPwmWrite(MOTOR12,0);
	softPwmWrite(MOTOR21,0);
	softPwmWrite(MOTOR22,0);
	
	char input;

	while(1) {
		
		input=getchar();
		
		if(input== '\033') 
		{
			getchar(); // ignore the next character
			switch(getchar()) {
				case 'B':
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
				case 'A':
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
					softPwmWrite(MOTOR21,PWM_R);
					softPwmWrite(MOTOR22,0);
					softPwmWrite(MOTOR11,0);
					softPwmWrite(MOTOR12,PWM_R);
					delay(DELAY);
					//turn off motor
					softPwmWrite(MOTOR21,0);
					softPwmWrite(MOTOR12,0);
					break;
				case 'D':
					printf("LEFT\n");
					
					softPwmWrite(MOTOR11,PWM_R);
					softPwmWrite(MOTOR12,0);
					softPwmWrite(MOTOR21,0);
					softPwmWrite(MOTOR22,PWM_R);
					delay(DELAY);

					//turn off motor
					
					softPwmWrite(MOTOR11,0);
					softPwmWrite(MOTOR22,0); 
					break;
			}
		}

		else if (input != '\033')
		{
			switch(input) {
			
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
			case 'i':
				printf("Lights ON\n");
				digitalWrite(LED,HIGH);
				break;
			case 'o':
				printf("Lights OFF\n");
				digitalWrite(LED,LOW);
				delay(10);
				break;
			
			case 'q':
				printf("QUIT :O\n");
				system("/bin/stty cooked");
				system("./mjpg-streamer.sh stop");

				softPwmWrite(MOTOR11,0);
				softPwmWrite(MOTOR12,0);
				softPwmWrite(MOTOR21,0);
				softPwmWrite(MOTOR22,0);
				digitalWrite(LED,LOW);
				return 0;

			case '1':
				printf("Starting streaming\n");
				system("./mjpg-streamer.sh start");
				break;
			case '0':
				printf("Stopping streaming \n");
				system("./mjpg-streamer.sh stop");
				break;

				 
			}// end of switch
		}

	}

}
