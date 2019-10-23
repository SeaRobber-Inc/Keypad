#include "PJ_RPI.h"
#include <stdio.h>

#define GPIO_PULL *(gpio.addr+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio.addr+38) // Pull up/pull down clock

int main()
{
	if(map_peripheral(&gpio) == -1) 
	{
       	 	printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        	return -1;
    	}

	
	//Init in/out
	INP_GPIO(17); // rij 1
	INP_GPIO(18); // rij 2
	INP_GPIO(27); // rij 3
	INP_GPIO(22); // rij 4

	INP_GPIO(5); // kollom 1
	INP_GPIO(6); // kollom 2
	INP_GPIO(13); // kollom 3
	INP_GPIO(12); // kollom 4

	INP_GPIO(23); // Relay
	
	//outputs
	OUT_GPIO(17);
	OUT_GPIO(18);	
	OUT_GPIO(27);
	OUT_GPIO(22);
	OUT_GPIO(23);


	//pullup
	GPIO_PULL = 2;
	usleep(100);
	// clock on GPIO 24 & 25 (bit 24 & 25 set)
	GPIO_PULLCLK0 = (1 << 5) | ( 1 << 6) | ( 1 << 13) | ( 1 << 12);
	usleep(100);
	GPIO_PULL = 0;
	GPIO_PULLCLK0 = 0;

	// set rows high
	GPIO_SET = 1 << 17;
	GPIO_SET = 1 << 18;
	GPIO_SET = 1 << 27;
	GPIO_SET = 1 << 22;
	GPIO_SET = 1 << 23; // relay

	int count = 0;
	char code[] = {'5','4','3','2','1'};
	char input[] = {'0','0','0','0','0'};
	while(1)
	{
		if(count >= 5){
			if(strcmp(code, input) == 0){
				// Correcte code
				printf("\nLaunch code correct!\r\n");
				GPIO_SET = 0 << 23;
				for (int i = 0; i < sizeof(input); i++)
				{
					input[i] = '0';	
				}
				count = 0;
			}
			else
			{
				// Foute code
				printf("\nWrong code, try again!\r\n");
				for (int i = 0; i < sizeof(input); i++)
				{
					input[i] = '0';	
				}
				count = 0;
			}
			
		}

		for( int a = 0; a < 4; a++ ){
			if(a == 0){
				GPIO_CLR = 1 << 17;
				//printf("Checking row 1\r\n");
				if(!(GPIO_READ(5))){
					// Enter
					usleep(100 *1000);
					
					printf("Knop 1 actief\r\n");
				}
				if(!(GPIO_READ(6))){
					printf("Knop 2 actief\r\n");
					usleep(100 *1000);
				}

				if(!(GPIO_READ(13))){
					printf("Knop 3 actief\r\n");
					usleep(100 *1000);
				}

				if(!(GPIO_READ(12))){
					// Clear input
					// printf("Knop 4 actief\r\n");
					for (int i = 0; i < sizeof(input); i++)
					{
						input[i] = '0';	
					}
					
					usleep(100 *1000);
				}
				GPIO_SET = 1 << 17;
				usleep(100);
			}
			else if (a == 1){
				//printf("Checking row 2\r\n");
				GPIO_CLR = 1 << 18;
				if(!(GPIO_READ(5))){
					usleep(100 *100);
					printf("Knop 5 actief\r\n");
				}
				if(!(GPIO_READ(6))){
					// Cijfer 9
					//printf("Knop 6 actief\r\n");

					input[count] = '9';
					count++;
					usleep(100 *100);
				}

				if(!(GPIO_READ(13))){
					// Cijfer 8
					//printf("Knop 7 actief\r\n");

					input[count] = '8';
					count++;
					usleep(100 *100);
				}

				if(!(GPIO_READ(12))){
					// Cijfer 7
					//printf("Knop 8 actief\r\n");

					input[count] = '7';
					count++;
					usleep(100 *100);
				}
				GPIO_SET = 1 << 18;
				usleep(100);
			}
			else if (a == 2){
				//printf("Checking row 3\r\n");
				GPIO_CLR = 1 << 27;
				if(!(GPIO_READ(5))){
					usleep(100 *100);
					printf("Knop 9 actief\r\n");
				}
				if(!(GPIO_READ(6))){
					// Cijfer 6
					//printf("Knop 10 actief\r\n");

					input[count] = '6';
					count++;
					usleep(100 *100);
				}

				if(!(GPIO_READ(13))){
					// Cijfer 5
					//printf("Knop 11 actief\r\n");

					input[count] = '5';
					count++;
					usleep(100 *100);
				}

				if(!(GPIO_READ(12))){
					// Cijfer 4
					//printf("Knop 12 actief\r\n");

					input[count] = '4';
					count++;
					usleep(100 *100);
				}
				GPIO_SET = 1 << 27;
				usleep(100);
			}
			else if (a == 3){
				//printf("Checking row 4\r\n");
				GPIO_CLR = 1 << 22;
				if(!(GPIO_READ(5))){
					usleep(100 *100);
					printf("Knop 13 actief\r\n");
				}
				if(!(GPIO_READ(6))){
					//Cijfer 3
					//printf("Knop 14 actief\r\n");

					input[count] = '3';
					count++;
					usleep(100 *100);
				}

				if(!(GPIO_READ(13))){
					// Cijfer 2
					//printf("Knop 15 actief\r\n");

					input[count] = '2';
					count++;
					usleep(100 *100);
				}

				if(!(GPIO_READ(12))){
					//Cijfer 1
					//printf("Knop 16 actief\r\n");

					input[count] = '1';
					count++;
					usleep(100 *100);
				}
				GPIO_SET = 1 << 22;
				usleep(100);
			}
			printf("\r%s", input);
			fflush(stdout);
			sleep(1);	
		}
	}

	return 0;	

}
