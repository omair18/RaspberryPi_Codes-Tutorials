#include<wiringPi.h>
#include<stdio.h>

int main ()
{
	wiringPiSetup();
	
	pinMode(0,OUTPUT);


	digitalWrite(0,HIGH);
	
	delay(100000);

	digitalWrite(0,LOW);
	return 0;
}	
	
	
