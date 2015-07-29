#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <softPwm.h>

int main (void)
{
int enableA = 0;
int pin = 1;
int x=0;

if (wiringPiSetup() == -1)
	exit (1);

printf ("Raspberry Pi SoftwarePWM HBridge Test\n");

softPwmCreate (enableA, 0,255);
pinMode (pin, OUTPUT);

while (1){
	softPwmWrite (enableA, 80);
	delay (47);

	}

	return 0;
}
