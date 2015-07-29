#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <wiringPi.h>

#define MOTOR11 0 //Motor1 terminal 1
#define MOTOR12 1// Motor1 terminal 2
#define MOTOR21 2 // Motor2 terminal 1
#define MOTOR22 3 // Motor2 terminal 2
#define DELAY 30 

int main ()
{

	system("/bin/stty raw");


	printf("\nRUNNING CODE\n");
	wiringPiSetup();
	// set all pins to output mode
	pinMode(MOTOR11,OUTPUT);
	pinMode(MOTOR12,OUTPUT);
	
	pinMode(MOTOR21,OUTPUT);
	pinMode(MOTOR22,OUTPUT);
	

	while(1) {

		if(getchar() == '\033') {
			getchar(); // ignore the next character
			switch(getchar()) {
				case 'A':
					printf("FORWARD\n");
				

					digitalWrite(MOTOR11,HIGH);
					digitalWrite(MOTOR21,HIGH);
					digitalWrite(MOTOR12,LOW);
					digitalWrite(MOTOR22,LOW);
					delay(DELAY);
					//turn off both motors now, so that they work only when we hit button
					digitalWrite(MOTOR11,LOW);
					digitalWrite(MOTOR21,LOW);
					break;
				case 'B':
					printf("BACKWARD\n");
					digitalWrite(MOTOR12,HIGH);
					digitalWrite(MOTOR22,HIGH);
					digitalWrite(MOTOR11,LOW);
					digitalWrite(MOTOR21,LOW);
					delay(DELAY);
					//turn off both motors, so that they work only when we hit button
					digitalWrite(MOTOR12,LOW);
					digitalWrite(MOTOR22,LOW);
					break;
				case 'C':
					//printf("Right\n");
					printf("RIGHT\n");
					digitalWrite(MOTOR21,HIGH);
					digitalWrite(MOTOR22,LOW);
					digitalWrite(MOTOR11,LOW);
					digitalWrite(MOTOR12,LOW);
					delay(DELAY);
					//turn off motor
					digitalWrite(MOTOR21,LOW);
					break;
				case 'D':
					printf("LEFT\n");
					digitalWrite(MOTOR11,HIGH);
					digitalWrite(MOTOR12,LOW);
					digitalWrite(MOTOR21,LOW);
					digitalWrite(MOTOR22,LOW);
					delay(DELAY);
					//turn off motor
					digitalWrite(MOTOR11,LOW);
					break;
			}
		}
		else if (getchar() == 'q' || getchar() == '\r') {
			system("/bin/stty cooked");
			return 0; 
		}

	}

	system("/bin/stty cooked");

	return 0;
}
