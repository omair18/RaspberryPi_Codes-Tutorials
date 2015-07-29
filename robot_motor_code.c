#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <wiringPi.h>

#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3
#define DELAY 25

int main ()
{
	system("/bin/stty raw");

	wiringPiSetup();
	pinMode(LED0,OUTPUT);
	pinMode(LED1,OUTPUT);
	pinMode(LED2,OUTPUT);
	pinMode(LED3,OUTPUT);
	
	char input;
	while(1) {
		input = getchar();
		
		if(input == '\033') {
			getchar(); // ignore the next character
			switch(getchar()) {
				case 'A':
					printf("UP\n");
					digitalWrite(LED0,HIGH);
					delay(DELAY);
					digitalWrite(LED0,LOW);
					break;
				case 'B':
					printf("Down\n");
					digitalWrite(LED1,HIGH);
					delay(DELAY);
					digitalWrite(LED1,LOW);
					break;
				case 'C':
					printf("Right\n");
					digitalWrite(LED2,HIGH);
					delay(DELAY);
					digitalWrite(LED2,LOW);
					break;
				case 'D':
					printf("Left\n");
					digitalWrite(LED3,HIGH);
					delay(DELAY);
					digitalWrite(LED3,LOW);
					break;
			}
		}
		else if(input == 'q')
		{
			digitalWrite(LED0,LOW);
			digitalWrite(LED1,LOW);
			digitalWrite(LED2,LOW);
			digitalWrite(LED3,LOW);
			
			system("/bin/stty cooked");
			return 0;
		}

	}
}
