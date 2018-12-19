#include "mbed.h"

DigitalOut led1(LED1);

#define NUM_BYTES 100

RawSerial u1(P1_8, P0_4);  // tx, rx

/* Globals */
char input[NUM_BYTES];
int idx;

void readcallback()  {
    char newc = u1.getc();
    input[idx++] = newc;
}

int main()
{
	int i;
	u1.attach (&readcallback);
	u1.printf ("Blinky print!\n\r");

    	while(1) {
        	led1 = 1;
        	wait(0.2);
	        led1 = 0;
	        wait(0.2);

		/* Racy, fix it */
		if (idx != 0) {
			for (i=0; i<idx; i++) {
				u1.printf("%c", input[i]);
			}
			idx = 0;
		}
	}
}
