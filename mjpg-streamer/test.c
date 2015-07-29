#include <stdio.h>
#include <stdlib.h>

int main () {
	
	int returnvalue;
	returnvalue = system("./mjpg-streamer.sh start");

	if(returnvalue != -1)
	{
		printf("Success \n");
	}
	
	if(getchar() == 'q')
	{
		system("./mjpg-streamer.sh stop");	
	}

	return 0;
}	
