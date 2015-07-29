#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <wiringPi.h>

#define servo_down 23
#define servo_up 24
#define DIFF 0.002

int main ()
{
	char input;
	char buffer[50];
	float value_down=0.146; //0.155; // 0.080 to 0.130 moves right, 0.130 to 0.220 moves left
	float value_up= 0.135; // 0.070 to 0.135 moves up, 0.135 to 0.195 moves down

	/* servos coming to default position */
//servo down
	sprintf(buffer,"echo \"%d=%f\"> /dev/pi-blaster",servo_down,value_down);
	system(buffer);		
	
//servo up		
	sprintf(buffer,"echo \"%d=%f\"> /dev/pi-blaster",servo_up,value_up);
	system(buffer);	
	


	system("/bin/stty raw");
	
	while(1)
	{
		input = getchar();
		
		switch(input)
		{
			case 'f': // move right
				if(value_down > 0.079)
				{
					value_down = value_down-DIFF;
					sprintf(buffer,"echo \"%d=%f\"> /dev/pi-blaster",servo_down,value_down);
					system(buffer);		
					//printf("%s\n",buffer);
					break;
				}
				else
					sprintf(buffer,"echo \"%d=0\">/dev/pi-blaster",servo_down);
					system(buffer);
					//printf("%s\n",buffer);
					break;
			case 's': // move left
				if(value_down < 0.220)
				{
					value_down = value_down+DIFF;
					sprintf(buffer,"echo \"%d=%f\"> /dev/pi-blaster",servo_down,value_down);
					system(buffer);
					//printf("%s\n",buffer);
					break;
				}
				else
					sprintf(buffer,"echo \"%d=0\">/dev/pi-blaster",servo_down);
					system(buffer);
					//printf("%s\n",buffer);
					break;
			
			case 'e': // move up
				if(value_up > 0.069)
				{
					value_up = value_up-DIFF;
					sprintf(buffer,"echo \"%d=%f\"> /dev/pi-blaster",servo_up,value_up);
					system(buffer);		
					//printf("%s\n",buffer);
					break;
				}
				else
					sprintf(buffer,"echo \"%d=0\">/dev/pi-blaster",servo_up);
					system(buffer);
					//printf("%s\n",buffer);
					break;
			case 'd': // move down
				if(value_up < 0.196)
				{
					value_up = value_up+DIFF;
					sprintf(buffer,"echo \"%d=%f\"> /dev/pi-blaster",servo_up,value_up);
					system(buffer);
					//printf("%s\n",buffer);
					break;
				}
				else
					sprintf(buffer,"echo \"%d=0\">/dev/pi-blaster",servo_up);
					system(buffer);
					//printf("%s\n",buffer);
					break;
			
			case 'q':
				system("/bin/stty cooked");
				return 0;
				break;
		}
	}
	
	system("/bin/stty cooked");
	return 0;
	
}