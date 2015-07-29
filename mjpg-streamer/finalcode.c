#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <wiringPi.h>

#define MOTOR11 0 //Motor1 terminal 1
#define MOTOR12 1// Motor1 terminal 2
#define MOTOR21 2 // Motor2 terminal 1
#define MOTOR22 3 // Motor2 terminal 2

#define SERVO_DOWN 25
#define SERVO_UP 24
#define DIFF 0.002


#define DELAY 25
#define DELAY_SERVO 10

#define PWM 200
#define PWM_R 255

int main ()
{
	char input;
	char buffer[50];
	float value_down=0.146; //0.155; // 0.080 to 0.130 moves right, 0.130 to 0.220 moves left
	float value_up= 0.135; // 0.070 to 0.135 moves up, 0.135 to 0.195 moves down

	/* servos coming to default position */
//servo down
	sprintf(buffer,"echo \"%d=%f\"> /dev/pi-blaster",SERVO_DOWN,value_down);
	system(buffer);	
	delay(DELAY_SERVO);	
	sprintf(buffer,"echo \"%d=%d\"> /dev/pi-blaster",SERVO_DOWN,0);
	system(buffer);	
	printf("VALUE ZERO \n");
//servo up		
	sprintf(buffer,"echo \"%d=%f\"> /dev/pi-blaster",SERVO_UP,value_up);
	system(buffer);	
	delay(DELAY_SERVO);
	sprintf(buffer,"echo \"%d=%d\"> /dev/pi-blaster",SERVO_UP,0);
	system(buffer);	
	printf("VALUE 2 ZERO \n");
	
	
	system("/bin/stty raw");

	printf("\nRUNNING CODE ( press 'q' to exit)\n");
	wiringPiSetup();

	pinMode(MOTOR11,OUTPUT);
	pinMode(MOTOR12,OUTPUT);
	pinMode(MOTOR21,OUTPUT);
	pinMode(MOTOR22,OUTPUT);

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
				case 'D':
					
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
				case 'C':
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
			}// end of switch
		}// end of if

		else if (input != '\033')
		{
			switch(input)
			{
			case 'f': // move right
				if(value_down > 0.079)
				{
					value_down = value_down-DIFF;
					sprintf(buffer,"echo \"%d=%f\"> /dev/pi-blaster",SERVO_DOWN,value_down);
					system(buffer);
					delay(DELAY_SERVO);
					sprintf(buffer,"echo \"%d=%d\"> /dev/pi-blaster",SERVO_DOWN,0);
					system(buffer);
					break;
				}
				else
					sprintf(buffer,"echo \"%d=0\">/dev/pi-blaster",SERVO_DOWN);
					system(buffer);
					break;
			case 's': // move left
				if(value_down < 0.220)
				{
					value_down = value_down+DIFF;
					sprintf(buffer,"echo \"%d=%f\"> /dev/pi-blaster",SERVO_DOWN,value_down);
					system(buffer);
					delay(DELAY_SERVO);
					sprintf(buffer,"echo \"%d=%d\"> /dev/pi-blaster",SERVO_DOWN,0);
					system(buffer);
					break;
				}
				else
					sprintf(buffer,"echo \"%d=0\">/dev/pi-blaster",SERVO_DOWN);
					system(buffer);
					break;
			
			case 'e': // move up
				if(value_up > 0.069)
				{
					value_up = value_up-DIFF;
					sprintf(buffer,"echo \"%d=%f\"> /dev/pi-blaster",SERVO_UP,value_up);
					system(buffer);
					delay(DELAY_SERVO);
					sprintf(buffer,"echo \"%d=%d\"> /dev/pi-blaster",SERVO_UP,0);
					system(buffer);
					break;
				}
				else
					sprintf(buffer,"echo \"%d=0\">/dev/pi-blaster",SERVO_UP);
					system(buffer);
					break;
			case 'd': // move down
				if(value_up < 0.196)
				{
					value_up = value_up+DIFF;
					sprintf(buffer,"echo \"%d=%f\"> /dev/pi-blaster",SERVO_UP,value_up);
					system(buffer);
					delay(DELAY_SERVO);
					sprintf(buffer,"echo \"%d=%d\"> /dev/pi-blaster",SERVO_UP,0);
					system(buffer);
					
					break;
				}
				else
					sprintf(buffer,"echo \"%d=0\">/dev/pi-blaster",SERVO_UP);
					system(buffer);
					//printf("%s\n",buffer);
					break;
			
			case 'q':
				printf("EXIT\n");
				system("/bin/stty cooked");
				/* release pwm pins */
				sprintf(buffer,"echo \"release %d\">/dev/pi-blaster",SERVO_UP);
				system(buffer);
				sprintf(buffer,"echo \"release %d\">/dev/pi-blaster",SERVO_DOWN);
				system(buffer);

				system("./mjpg-streamer.sh stop");

				return 0;
				break;
			case 'r':
				printf("RESET ALL PINS \n");
				sprintf(buffer,"echo \"%d=%d\"> /dev/pi-blaster",SERVO_UP,0);
				system(buffer);
				sprintf(buffer,"echo \"%d=%d\"> /dev/pi-blaster",SERVO_DOWN,0);
				system(buffer);
				softPwmWrite(MOTOR11,0);
				softPwmWrite(MOTOR12,0); 
				softPwmWrite(MOTOR21,0);
				softPwmWrite(MOTOR22,0); 
				break;

			case '1':
				printf("Starting streaming\n");
				system("./mjpg-streamer.sh start");
				break;
			case '0':
				printf("Stopping streaming \n");
				system("./mjpg-streamer.sh stop");
				break;

				 
			}// end of switch
		}// end of else-if

	} // end of while

} // end of main