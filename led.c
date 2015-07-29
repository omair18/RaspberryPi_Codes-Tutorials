#include<wiringPi.h>
#include<unistd.h>
#include<termios.h>
#include<stdio.h>
#include<stdlib.h>

#define LED 4
int main ()
{
	system("/bin/stty raw");
	wiringPiSetup();

	pinMode(LED, OUTPUT);
	char input;

	digitalWrite(LED,HIGH);
	printf("LED TURNED ON\n");

	input = getchar();

	digitalWrite(LED,LOW);
	delay(14);
	system("/bin/stty cooked");

	return 0;
}

		
